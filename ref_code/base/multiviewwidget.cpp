#include "multiviewwidget.h"
#include <QPointer>
#include <QtCore>
#include "viewframe.h"
#include "ViewLayoutManager.h"


#include "ViewFrame.h"
#include "View.h"

#include <QVariant>
#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QMap>
#include <QPointer>
#include <QSplitter>
#include <QVBoxLayout>
#include <QVector>

#include "standardviewgroupaction.h"
#include "activeviewobject.h"


namespace Base{

class MultiViewWidget::pqInternals
{
public:
  QVector<QPointer<QWidget> > Widgets;

  // This map is used to avoid reassigning frames. Once a view is assigned a
  // frame, we preserve that frame as long as possible.
  QMap<View*, QPointer<ViewFrame> > ViewFrames;

  unsigned long ObserverId;
  ViewLayoutManager*	LayoutManager;
  QPointer<ViewFrame> ActiveFrame;
  StandardViewGroupAction*	ViewGroupAction;

  pqInternals() : ObserverId(0)
    {
		LayoutManager=new ViewLayoutManager();
		ViewGroupAction=new StandardViewGroupAction();

		ActiveViewObject::instance()->setLayoutManager(LayoutManager);
    }

  ~pqInternals()
    {
		delete LayoutManager;
		delete ViewGroupAction;
    }

  void setMaximizedWidget(QWidget* wdg)
    {
    ViewFrame* frame = qobject_cast<ViewFrame*>(wdg);
    if (frame)
      {
      frame->setStandardButtons(ViewFrame::Restore);
      }
    if (this->MaximizedWidget)
      {
      this->MaximizedWidget->setStandardButtons(
        ViewFrame::SplitVertical |
        ViewFrame::SplitHorizontal |
        ViewFrame::Maximize |
        ViewFrame::Close);
      }
    this->MaximizedWidget = frame;
    }

private:
  QPointer<ViewFrame> MaximizedWidget;
};

//-----------------------------------------------------------------------------
namespace
{

  /// A simple subclass of QBoxLayout mimicking the layout style of a QSplitter
  /// with just 2 widgets.
  class pqSplitterLayout : public QBoxLayout
  {
  double SplitFraction;
public:

  pqSplitterLayout(QBoxLayout::Direction dir, QWidget* parentWdg)
    : QBoxLayout(dir, parentWdg), SplitFraction(0.5)
    {
    this->setContentsMargins(0, 0, 0,0);
    this->setSpacing(0);
    };

  virtual ~pqSplitterLayout()
    {
    }

  void setSplitFraction(double val) { this->SplitFraction = val; }

  virtual void setGeometry(const QRect& rect)
    {
    this->QLayout::setGeometry(rect);

    Q_ASSERT(this->count() <= 2);

    int offset = 0;
    double fractions[2] = { this->SplitFraction, 1.0 - this->SplitFraction };
    for (int cc=0; cc < this->count(); cc++)
      {
      QLayoutItem* item = this->itemAt(cc);
      if (this->direction() == LeftToRight)
        {
        item->setGeometry(
          QRect(offset + rect.x(), rect.y(),
            static_cast<int>(fractions[cc] * rect.width()), rect.height()));
        offset += static_cast<int>(fractions[cc] * rect.width());
        }
      else if (this->direction() == TopToBottom)
        {
        item->setGeometry(
          QRect(rect.x(), offset + rect.y(),
            rect.width(), static_cast<int>(fractions[cc] * rect.height())));
        offset += static_cast<int>(fractions[cc] * rect.height());
        }
      }
    }
  };
}

//-----------------------------------------------------------------------------
MultiViewWidget::MultiViewWidget(QWidget * parentObject, Qt::WindowFlags f)
: Superclass(parentObject, f),
  Internals( new pqInternals()),
  DecorationsVisible(true)
{
  qApp->installEventFilter(this);

  connect(Internals->ViewGroupAction,SIGNAL(viewAdded(View*)),
	  this,SLOT(assignToFrame(View*)));
  //int max_index;
  //createWidget(0,layoutManager(),this,max_index);
  //QObject::connect(&pqActiveObjects::instance(),
    //SIGNAL(viewChanged(pqView*)), this, SLOT(markActive(pqView*)));
}

//-----------------------------------------------------------------------------
MultiViewWidget::~MultiViewWidget()
{
		this->destroyAllViews();
	delete this->Internals;
  this->Internals = NULL;
}

//-----------------------------------------------------------------------------
bool MultiViewWidget::isViewAssigned(View* view) const
{
  return (view && this->Internals->LayoutManager &&
    this->Internals->LayoutManager->GetViewLocation(view) != -1);
}

//-----------------------------------------------------------------------------
void MultiViewWidget::viewAdded(View* view)
{
  if (view && this->Internals->LayoutManager &&
    this->Internals->LayoutManager->GetViewLocation(
      view) != -1)
    {
    // a pqview was created for a view that this layout knows about. we have to
    // reload the layout to ensure that the view gets placed correctly.
    ViewFrame* frame = this->Internals->ViewFrames[view];
    if (frame)
      {
      QWidget* viewWidget = view->getWidget();
      frame->setCentralWidget(viewWidget);
      viewWidget->setParent(frame);
      }
    else
      {
      this->reload();
      }
    }
}


//-----------------------------------------------------------------------------
ViewLayoutManager* MultiViewWidget::layoutManager() const
{
  return this->Internals->LayoutManager;
}

//-----------------------------------------------------------------------------
bool MultiViewWidget::eventFilter(QObject* caller, QEvent* evt)
{
  if (evt->type() == QEvent::MouseButtonPress)
    {
    QWidget* wdg = qobject_cast<QWidget*>(caller);
    if (wdg && this->isAncestorOf(wdg))
      {
      // If the new widget that is getting the focus is a child widget of any of the
      // frames, then the frame should be made active.
      foreach (QWidget* frame_or_splitter, this->Internals->Widgets)
        {
        ViewFrame* frame =
          qobject_cast<ViewFrame*>(frame_or_splitter);
        if (frame && frame->isAncestorOf(wdg))
          {
          this->makeActive(frame);
          }
        }
      }
    }

  return this->Superclass::eventFilter(caller, evt);
}


//-----------------------------------------------------------------------------
void MultiViewWidget::assignToFrame(View* view)
{
  if (this->layoutManager() && view)
    {
    int active_index = 0;
    if (this->Internals->ActiveFrame)
      {
      active_index =
        this->Internals->ActiveFrame->property("FRAME_INDEX").toInt();
      }
    this->layoutManager()->AssignViewToAnyCell(view, active_index);
    }
	reload();
	ActiveViewObject::instance()->setActiveView(view);
}

//-----------------------------------------------------------------------------
void MultiViewWidget::makeFrameActive()
{
  /// note MultiViewWidget::markActive(ViewFrame*) fires a signal that
  /// results in this method being called. So we need to ensure that we don't
  /// do anything silly here that could cause infinite recursion.
  if (!this->Internals->ActiveFrame)
    {
    foreach (QWidget* wdg, this->Internals->Widgets)
      {
      ViewFrame* frame = qobject_cast<ViewFrame*>(wdg);
      if (frame)
        {
        this->makeActive(frame);
        break;
        }
      }
    }

  if (this->layoutManager())
    {
    ;//this->layoutManager()->ShowViewsOnTileDisplay();
    }

}

//-----------------------------------------------------------------------------
void MultiViewWidget::markActive(View* view)
{
   if (view &&
    this->Internals->ViewFrames.contains(view))
     {
     this->markActive(this->Internals->ViewFrames[view]);
     }
   else
     {
     this->markActive(static_cast<ViewFrame*>(NULL));
     }
}

//-----------------------------------------------------------------------------
void MultiViewWidget::markActive(ViewFrame* frame)
{
  if (this->Internals->ActiveFrame)
    {
    this->Internals->ActiveFrame->setBorderVisibility(false);
    }
  this->Internals->ActiveFrame = frame;
  if (frame)
    {
    frame->setBorderVisibility(true);
    // indicate to the world that a frame on this widget has been activated.
    // pqTabbedMultiViewWidget listens to this signal to raise that tab.
    emit this->frameActivated();
    // NOTE: this signal will result in call to makeFrameActive().
    }
}

//-----------------------------------------------------------------------------
void MultiViewWidget::makeActive(ViewFrame* frame)
{
  if (this->Internals->ActiveFrame != frame)
    {
    View* view = NULL;
    if (frame)
      {
      int index = frame->property("FRAME_INDEX").toInt();
      view = (this->layoutManager()->GetView(index));
      }
		ActiveViewObject::instance()->setActiveView(view);
		
    // this needs to called only when view == null since in that case when
    // markActive(pqView*) slot is called, we have no idea what frame is really
    // to be made active.
    this->markActive(frame);
    }
}

//-----------------------------------------------------------------------------
void MultiViewWidget::lockViewSize(const QSize& viewSize)
{
  if (this->LockViewSize != viewSize)
    {
    this->LockViewSize = viewSize;
    this->reload();
    }
}

//-----------------------------------------------------------------------------
ViewFrame* MultiViewWidget::newFrame(View* view)
{
  ViewFrame* frame = new ViewFrame(this);
  QObject::connect(frame, SIGNAL(buttonPressed(int)),
    this, SLOT(standardButtonPressed(int)));
  QObject::connect(frame, SIGNAL(swapPositions(const QString&)),
    this, SLOT(swapPositions(const QString&)), Qt::QueuedConnection);

  // it's possible that pqview is NULL, if the view proxy hasnt been registered
  // yet. This happens often when initialization state is being loaded in
  // collaborative sessions.
  if (view )
    {
    QWidget* viewWidget = view->getWidget();
    frame->setCentralWidget(viewWidget);
    viewWidget->setParent(frame);
    }


  return frame;
}

//-----------------------------------------------------------------------------
QWidget* MultiViewWidget::createWidget(
  int index, ViewLayoutManager* vlayout, QWidget* parentWdg,
  int& max_index)
{
  if (this->Internals->Widgets.size() <= static_cast<int>(index))
    {
    this->Internals->Widgets.resize(index+1);
    }

  ViewLayoutManager::Direction direction = vlayout->GetSplitDirection(index);
  switch (direction)
    {
  case ViewLayoutManager::NONE:
      {
      View* view = vlayout->GetView(index);
      ViewFrame* frame = view?
        this->Internals->ViewFrames[view] : NULL;
      if (!frame)
        {
        frame = this->newFrame(view);
        if (view)
          {
          this->Internals->ViewFrames[view] = frame;
          }
        }
      Q_ASSERT(frame != NULL);

      frame->setParent(parentWdg);
      this->Internals->Widgets[index] = frame;
      frame->setObjectName(QString("Frame.%1").arg(index));
      frame->setProperty("FRAME_INDEX", QVariant(index));
      frame->setDecorationsVisibility(this->DecorationsVisible);

	  Internals->ViewGroupAction->connect(frame,view);
	  QWidget* centralWidget=frame->centralWidget();


	  if(centralWidget){
		  if (this->LockViewSize.isEmpty()) 
			  centralWidget->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
		  else 
			  centralWidget->setMaximumSize(this->LockViewSize);
	  }


      if (max_index < index) { max_index = index; }
      return frame;
      }

  case ViewLayoutManager::VERTICAL:
  case ViewLayoutManager::HORIZONTAL:
    if (this->DecorationsVisible)
      {
      QSplitter* splitter = qobject_cast<QSplitter*>(
        this->Internals->Widgets[index]);
      if (!splitter)
        {
        splitter = new QSplitter(parentWdg);
        }
      Q_ASSERT(splitter);
      splitter->setParent(parentWdg);
      splitter->setHandleWidth(this->DecorationsVisible? 3 : 1);
      this->Internals->Widgets[index] = splitter;
      splitter->setObjectName(QString("Splitter.%1").arg(index));
      splitter->setProperty("FRAME_INDEX", QVariant(index));
      splitter->setOpaqueResize(false);
      splitter->setOrientation(
        direction == ViewLayoutManager::VERTICAL?
        Qt::Vertical : Qt::Horizontal);
      splitter->addWidget(
        this->createWidget(vlayout->GetFirstChild(index), vlayout, splitter,
          max_index));
      splitter->addWidget(
        this->createWidget(vlayout->GetSecondChild(index), vlayout, splitter,
          max_index));

      // set the sizes are percentage. QSplitter uses the initially specified
      // sizes as reference.
      QList<int> sizes;
      sizes << static_cast<int>(vlayout->GetSplitFraction(index) * 10000);
      sizes << static_cast<int>((1.0 - vlayout->GetSplitFraction(index)) * 10000);
      splitter->setSizes(sizes);

      // FIXME: Don't like this as this QueuedConnection may cause multiple
      // renders.
      QObject::disconnect(splitter, SIGNAL(splitterMoved(int, int)),
        this, SLOT(splitterMoved()));
      QObject::connect(splitter, SIGNAL(splitterMoved(int, int)),
        this, SLOT(splitterMoved()), Qt::QueuedConnection);
      if (max_index < index) { max_index = index; }
      return splitter;
      }
    else
      {
      QWidget* container = new QWidget(parentWdg);
      pqSplitterLayout* slayout = new pqSplitterLayout(
        direction == ViewLayoutManager::VERTICAL?
        pqSplitterLayout::TopToBottom :
        pqSplitterLayout::LeftToRight,
        container);
      slayout->setSplitFraction(vlayout->GetSplitFraction(index));
      container->setLayout(slayout);
      container->setObjectName(QString("Container.%1").arg(index));
      slayout->addWidget(
        this->createWidget(vlayout->GetFirstChild(index), vlayout, container,
          max_index));
      slayout->addWidget(
        this->createWidget(vlayout->GetSecondChild(index), vlayout, container,
          max_index));
      if (max_index < index) { max_index = index; }
      return container;
      }
    break;
    }
  return NULL;
}

//-----------------------------------------------------------------------------
void MultiViewWidget::reload()
{
  ViewLayoutManager* vlayout = this->layoutManager();
  if (!vlayout)
    {
    return;
    }

  QWidget *cleaner = new QWidget();
  foreach (QWidget* widget, this->Internals->Widgets)
    {
    if (widget)
      {
      widget->setParent(cleaner);
      }
    }
  int max_index=0;
  QWidget* child = this->createWidget(0, vlayout, this, max_index);
  delete cleaner;
  cleaner = NULL;

  delete this->layout();

  // resize Widgets to remove any obsolete indices. These indices weren't
  // touched at all during the last call to createWidget().
  this->Internals->Widgets.resize(max_index+1);

  QVBoxLayout* vbox = new QVBoxLayout(this);
  vbox->setContentsMargins(0, 0, 0, 0);
  vbox->addWidget(child);
  this->setLayout(vbox);

  int maximized_cell = vlayout->GetMaximizedCell();
  this->Internals->setMaximizedWidget(NULL);
  for (int cc = 0; cc < this->Internals->Widgets.size(); cc++)
    {
    ViewFrame* frame = qobject_cast<ViewFrame*>(
      this->Internals->Widgets[cc]);
    if (frame)
      {
      bool visibility = true;
      if (cc == maximized_cell)
        {
        this->Internals->setMaximizedWidget(frame);
        }
      else if (maximized_cell != -1)
        {
        visibility = false;
        }
      frame->setVisible(visibility);
      }
    }

  // ensure the active view is marked appropriately.
//  this->markActive(pqActiveObjects::instance().activeView());

  // Cleanup deleted objects. "cleaner" helps us avoid any dangling widgets and
  // deletes them whwn delete cleaner is called. Now we prune internal
  // datastructures to get rid of these NULL ptrs.

  // remove any deleted view frames.
  QMutableMapIterator<View*, QPointer<ViewFrame> > iter(
      this->Internals->ViewFrames);
  while (iter.hasNext())
    {
    iter.next();
    if (iter.value() == NULL)
      {
      // since we are in the process of destroying the view, cancel any pending
      // render requests. This addresses a Windows issue where the view would
      // occassionally popout and render when undoing the creation of the view
      // or closing it.
      View* view = (iter.key());
      if (view)
        {
        //view->cancelPendingRenders();
        }
      iter.remove();
      }
    }

  // we let the GUI updated immediately. This is needed since when a new view is
  // created (for example), it may depend on the size of the view during its
  // initialization to ensure camera is reset correctly.
  QCoreApplication::sendPostedEvents();
}

//-----------------------------------------------------------------------------
void MultiViewWidget::standardButtonPressed(int button)
{
  QWidget* frame = qobject_cast<QWidget*>(this->sender());
  QVariant index = frame? frame->property("FRAME_INDEX") : QVariant();
  if (!index.isValid() || this->layoutManager() == NULL)
    {
    return;
    }

  switch (button)
    {
  case ViewFrame::SplitVertical:
  case ViewFrame::SplitHorizontal:
      {
      int new_index = this->layoutManager()->Split(index.toInt(),
        (button == ViewFrame::SplitVertical?
         ViewLayoutManager::VERTICAL : ViewLayoutManager::HORIZONTAL),
        0.5);
	  //RenderView* rview=new RenderView();
	  //layoutManager()->AssignView(new_index+1,rview);
	  reload();
      this->makeActive(qobject_cast<ViewFrame*>(
          this->Internals->Widgets[new_index + 1]));
      }
    break;

  case ViewFrame::Maximize:
    this->layoutManager()->MaximizeCell(index.toInt());
	reload();
    break;

  case ViewFrame::Restore:
    this->layoutManager()->RestoreMaximizedState();
	reload();
    break;

  case ViewFrame::Close:
      {
      View* viewProxy =
        this->layoutManager()->GetView(index.toInt());
      if (viewProxy)
        {
        this->layoutManager()->RemoveView(viewProxy);
		delete viewProxy;
        }
      if (index.toInt() != 0)
        {
        int location = index.toInt();
        int parent_idx = ViewLayoutManager::GetParent(location);
        this->layoutManager()->Collapse(location);
        this->makeActive(qobject_cast<ViewFrame*>(
            this->Internals->Widgets[parent_idx]));
        }
      }
    break;
    }

  reload();
}

//-----------------------------------------------------------------------------
void MultiViewWidget::destroyAllViews()
{
  QList<View*> views = this->viewProxies();
  foreach (View* view, views)
    {
    if (view)
      {
		  delete view;
      }
    }
}

//-----------------------------------------------------------------------------
void MultiViewWidget::splitterMoved()
{
  QSplitter* splitter = qobject_cast<QSplitter*>(this->sender());
  QVariant index = splitter? splitter->property("FRAME_INDEX") : QVariant();
  if (index.isValid() && this->layoutManager())
    {
    QList<int> sizes = splitter->sizes();
    if (sizes.size() == 2)
      {
      double fraction = sizes[0] * 1.0 / (sizes[0] + sizes[1]);
      this->layoutManager()->SetSplitFraction(index.toInt(), fraction);
      }
    }
}

//-----------------------------------------------------------------------------
void MultiViewWidget::setDecorationsVisible(bool val)
{
  if (this->DecorationsVisible == val)
    {
    return;
    }

  this->DecorationsVisible = val;
  this->reload();
}

//-----------------------------------------------------------------------------
//int MultiViewWidget::prepareForCapture(int dx, int dy)
//{
//  QSize requestedSize(dx, dy);
//  QSize mySize = this->size();
//
//  int magnification =  pqView::computeMagnification(requestedSize, mySize);
//  this->setMaximumSize(mySize);
//  this->resize(mySize);
//  this->setDecorationsVisible(false);
//  pqEventDispatcher::processEventsAndWait(1);
//  return magnification;
//}

//-----------------------------------------------------------------------------
//void MultiViewWidget::cleanupAfterCapture()
//{
//  this->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
//  this->setDecorationsVisible(true);
//}

//-----------------------------------------------------------------------------
//vtkImageData* MultiViewWidget::captureImage(int dx, int dy)
//{
//  int magnification = this->prepareForCapture(dx, dy);
//  vtkImageData* image = this->layoutManager()->CaptureWindow(magnification);
//  this->cleanupAfterCapture();
//  return image;
//}

//-----------------------------------------------------------------------------
void MultiViewWidget::swapPositions(const QString& uid_str)
{
  QUuid other (uid_str);

  ViewLayoutManager* vlayout = this->layoutManager();
  ViewFrame* senderFrame = qobject_cast<ViewFrame*>(this->sender());
  if (!senderFrame || !vlayout)
    {
    return;
    }

  ViewFrame* swapWith = NULL;
  foreach (QWidget* wdg, this->Internals->Widgets)
    {
    ViewFrame* frame = qobject_cast<ViewFrame*>(wdg);
    if (frame && frame->uniqueID() == other)
      {
      swapWith = frame;
      break;
      }
    }

  if (!swapWith)
    {
    return;
    }

  int id1 = senderFrame->property("FRAME_INDEX").toInt();
  int id2 = swapWith->property("FRAME_INDEX").toInt();
  View* view1 = vlayout->GetView(id1);
  View* view2 = vlayout->GetView(id2);

  if (view1 == NULL && view2 == NULL)
    {
    return;
    }

  vlayout->SwapCells(id1, id2);
  this->reload();
}

//-----------------------------------------------------------------------------
void MultiViewWidget::reset()
{
  this->layoutManager()->Reset();
}

//-----------------------------------------------------------------------------
QList<View*> MultiViewWidget::viewProxies() const
{
  return this->Internals->ViewFrames.keys();
}


}	//end namespace Base