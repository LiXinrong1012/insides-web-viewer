#include "viewframe.h"


#include <QAction>
#include <QApplication>
#include <QDrag>
#include <QHBoxLayout>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QStyle>
#include <QToolButton>
#include <QVBoxLayout>

#if WIN32
# include "process.h"
# define getpid _getpid
#else
# include "unistd.h"
#endif

#include "Console.h"


namespace Base{


/**
  Using pqSetName, you can create and initialize Qt objects without having to create a bunch of temporaries:
  
  \code
  menu->addAction("Open") << pqSetName("FileOpenMenu");
  \endcode
 
  \sa pqSetData, pqConnect
*/
  
struct  pqSetName
{
  pqSetName(const QString& name):Name(name){}
  const QString Name;

private:
  void operator=(const pqSetName&);
};

/// Sets a Qt object's name
template<typename T>
T* operator<<(T* LHS, const pqSetName& RHS)
{
  LHS->setObjectName(RHS.Name);
  return LHS;
}



#define PEN_WIDTH 2




//-----------------------------------------------------------------------------
ViewFrame::ViewFrame(QWidget* parentObject)
  : Superclass(parentObject),
  DecorationsVisible(true),
  TitleBarVisible(true),
  BorderVisible(false),
  BorderColor(QColor("blue")),
  Buttons(SplitVertical | SplitHorizontal | Maximize | Close),
  TitleBar(new QWidget(this)),
  ContextMenu(new QMenu(this->TitleBar)),
  UniqueID(QUuid::createUuid())
{
  // to allow an empty frame to work with the focus stuff
  this->setFocusPolicy(Qt::ClickFocus);

  QVBoxLayout* vbox = new QVBoxLayout(this);
  this->setLayout(vbox);

  this->TitleBar->setObjectName("TitleBar");
  this->TitleBar->setAcceptDrops(true);
  this->TitleBar->setContextMenuPolicy(Qt::CustomContextMenu);
  QObject::connect(
    this->TitleBar, SIGNAL(customContextMenuRequested(const QPoint&)),
    this, SLOT(contextMenuRequested(const QPoint&)));

  // limits the titlebar's height.
  this->TitleBar->setMaximumSize(16777215, 18);
  this->TitleBar->installEventFilter(this);

  // Create standard buttons.
  this->StandardToolButtons[SplitVertical] =
    this->createButton(new QAction(
        QIcon(":/resources/paraviewicon/SplitViewVertical.png"), "Split Vertical", this)
      << pqSetName("SplitVertical"));
  this->StandardToolButtons[SplitHorizontal] =
    this->createButton(new QAction(
        QIcon(":/resources/paraviewicon/SplitViewHorizontal.png"), "Split Horizontal", this)
      << pqSetName("SplitHorizontal"));
  this->StandardToolButtons[Maximize] =
    this->createButton(new QAction(
        QIcon(this->style()->standardPixmap(QStyle::SP_TitleBarMaxButton)),
        "Maximize", this) <<pqSetName("Maximize"));
  this->StandardToolButtons[Restore] =
    this->createButton(new QAction(
        QIcon(this->style()->standardPixmap(QStyle::SP_TitleBarNormalButton)),
        "Restore", this) << pqSetName("Minimize"));
  this->StandardToolButtons[Close] =
    this->createButton(new QAction(
        QIcon(this->style()->standardPixmap(QStyle::SP_TitleBarCloseButton)),
        "Close", this) << pqSetName("Close"));

  this->updateTitleBar();
  this->updateLayout();

  this->ContextMenu->setObjectName("FrameContextMenu");
  this->ContextMenu->addAction(
    this->StandardToolButtons[SplitHorizontal]->defaultAction());
  this->ContextMenu->addAction(
    this->StandardToolButtons[SplitVertical]->defaultAction());
  this->ContextMenu->addAction(
    this->StandardToolButtons[Close]->defaultAction());
}

//-----------------------------------------------------------------------------
ViewFrame::~ViewFrame()
{
  delete this->TitleBar;
}

//-----------------------------------------------------------------------------
void ViewFrame::setCentralWidget(QWidget* widget)
{
  this->CentralWidget = widget;
  this->updateLayout();
}

//-----------------------------------------------------------------------------
QWidget* ViewFrame::centralWidget() const
{
  return this->CentralWidget;
}

//-----------------------------------------------------------------------------
void ViewFrame::updateLayout()
{
  QVBoxLayout* vbox = new QVBoxLayout();
  if ((!this->TitleBarVisible && !this->BorderVisible) ||
    !this->DecorationsVisible)
    {
    vbox->setMargin(0);
    vbox->setSpacing(0);
    }
  else
    {
    vbox->setMargin(PEN_WIDTH);
    vbox->setSpacing(PEN_WIDTH);
    }

  if (this->TitleBarVisible && this->DecorationsVisible)
    {
    vbox->addWidget(this->TitleBar);
    }

  if (this->CentralWidget)
    {
    vbox->addWidget(this->CentralWidget);
    }
  else
    {
    vbox->addStretch();
    }

  delete this->layout();
  this->setLayout(vbox);
}

//-----------------------------------------------------------------------------
void ViewFrame::updateTitleBar()
{
  QHBoxLayout* hbox = new QHBoxLayout(); 
  hbox->setMargin(0);
  hbox->setSpacing(0);
  foreach (QToolButton* toolButton, this->ToolButtons)
    {
    hbox->addWidget(toolButton);
    }
  hbox->addStretch();
  foreach (QToolButton* button, this->StandardToolButtons)
    {
    button->hide();
    }
  if (this->standardButtons() & SplitHorizontal)
    {
    QToolButton* button = this->StandardToolButtons[SplitHorizontal];
    hbox->addWidget(button);
    button->show();
    }
  if (this->standardButtons() & SplitVertical)
    {
    QToolButton* button = this->StandardToolButtons[SplitVertical];
    hbox->addWidget(button);
    button->show();
    }

  if (this->standardButtons() & Maximize)
    {
    QToolButton* button = this->StandardToolButtons[Maximize];
    hbox->addWidget(button);
    button->show();
    }
  if (this->standardButtons() & Restore)
    {
    QToolButton* button = this->StandardToolButtons[Restore];
    hbox->addWidget(button);
    button->show();
    }
  if (this->standardButtons() & Close)
    {
    QToolButton* button = this->StandardToolButtons[Close];
    hbox->addWidget(button);
    button->show();
    }

  delete this->TitleBar->layout();
  this->TitleBar->setLayout(hbox);
}

//-----------------------------------------------------------------------------
void ViewFrame::paintEvent(QPaintEvent* evt)
{
  this->Superclass::paintEvent(evt);

  if (this->BorderVisible && this->DecorationsVisible)
    {
    QPainter painter(this);
    QPen pen;
    pen.setColor(this->BorderColor);
    pen.setWidth(PEN_WIDTH);
    painter.setPen(pen);
    QRect borderRect = this->contentsRect();
    if (this->isTitleBarVisible())
      {
      QLayoutItem* titlebar = this->layout()->itemAt(0);
      borderRect.adjust(-PEN_WIDTH/2+2, 
        titlebar->geometry().height()+4-PEN_WIDTH/2, 
        PEN_WIDTH/2-2, 
        PEN_WIDTH/2-2);
      }
    else
      {
      borderRect.adjust(
        -PEN_WIDTH/2+2, PEN_WIDTH/2, PEN_WIDTH/2-2, PEN_WIDTH/2-2);
      }
    painter.drawRect(borderRect);
    }
}

//-----------------------------------------------------------------------------
void ViewFrame::setStandardButtons(StandardButtons buttons)
{
  if (this->Buttons != buttons)
    {
    this->Buttons = buttons;
    this->updateTitleBar();
    }
}

//-----------------------------------------------------------------------------
QToolButton* ViewFrame::createButton(QAction* action)
{
  QToolButton* toolButton = new QToolButton(this);
  toolButton->setDefaultAction(action);
  toolButton->setObjectName(action->objectName());
  toolButton->setIcon(action->icon());

  QObject::connect(toolButton, SIGNAL(triggered(QAction*)),
    this, SLOT(buttonClicked()), Qt::QueuedConnection);
  return toolButton;
}

//-----------------------------------------------------------------------------
void ViewFrame::buttonClicked()
{
  QToolButton* toolButton = qobject_cast<QToolButton*>(this->sender());
  if (toolButton)
    {
    if (this->ToolButtons.contains(toolButton))
      {
      emit this->actionTriggered(toolButton->defaultAction());
      }

    StandardButton key = this->StandardToolButtons.key(toolButton, NoButton);
    if (key != NoButton)
      {
      emit this->buttonPressed(key);
      }
    }
}

//-----------------------------------------------------------------------------
void ViewFrame::addTitleBarAction(QAction* action)
{
  this->ToolButtons.push_front(this->createButton(action));
  this->updateTitleBar();
}

//-----------------------------------------------------------------------------
QAction* ViewFrame::addTitleBarAction(const QString& titlestr)
{
  QAction* action = new QAction(titlestr, this);
  action->setObjectName(titlestr);
  this->addTitleBarAction(action);
  return action;
}

//-----------------------------------------------------------------------------
QAction* ViewFrame::addTitleBarAction(const QIcon& icon, const QString& titlestr)
{
  QAction* action = new QAction(icon, titlestr, this);
  action->setObjectName(titlestr);
  this->addTitleBarAction(action);
  return action;
}

//-----------------------------------------------------------------------------
void ViewFrame::removeTitleBarActions()
{
  foreach (QToolButton* button, this->ToolButtons)
    {
    delete button;
    }
  this->ToolButtons.clear();
}

//-----------------------------------------------------------------------------
void ViewFrame::contextMenuRequested(const QPoint& point)
{
  this->setFocus(Qt::OtherFocusReason);
  this->ContextMenu->exec(this->TitleBar->mapToGlobal(point));
}

//-----------------------------------------------------------------------------
bool ViewFrame::eventFilter(QObject* caller, QEvent* evt)
{
  if (evt->type() == QEvent::MouseButtonPress)
    {     
    QMouseEvent *mouseEvent=(QMouseEvent*)evt;
    if (mouseEvent->button() == Qt::LeftButton)
      {
      this->DragStartPosition = mouseEvent->pos();
      }
    }
  else if(evt->type() == QEvent::MouseMove)
    {
	//Console().Log("In here: mouse move");
    QMouseEvent *mouseEvent=(QMouseEvent*)evt;
    if ((mouseEvent->buttons() & Qt::LeftButton) &&
      (mouseEvent->pos() - this->DragStartPosition).manhattanLength()
      >= QApplication::startDragDistance())
      {
      this->drag();
      }
    }
  else if(evt->type() == QEvent::DragEnter)
    {
    QDragEnterEvent* de=reinterpret_cast<QDragEnterEvent*>(evt);
    this->dragEnter(de);
    }
  else if(evt->type() == QEvent::DragMove)
    {
	//Console().Log("In here: drop move");
    QDragMoveEvent* de=reinterpret_cast<QDragMoveEvent*>(evt);
    this->dragMove(de);
	//Console().Log("In here: drag move");
    }
  else if(evt->type() == QEvent::Drop)
    {
	//Console().Log("In here: drop");
    QDropEvent* de=reinterpret_cast<QDropEvent*>(evt);
    this->drop(de);
    }

	//Console().Log("In here: aaa");

  return this->Superclass::eventFilter(caller, evt);
}

//-----------------------------------------------------------------------------
void ViewFrame::drag()
{
	QPixmap pixmap(":/pqWidgets/Icons/pqWindow16.png");

	QByteArray output;
	QDataStream dataStream(&output, QIODevice::WriteOnly);
	dataStream << this->uniqueID();

	QMimeData *mimeData = new QMimeData;
	QString mimeType = QString("application/paraview3/%1").arg(getpid());
	mimeData->setData(mimeType, output);

	QDrag *dragObj = new QDrag(this);
	dragObj->setMimeData(mimeData);
	dragObj->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
	dragObj->setPixmap(pixmap);
	dragObj->start();
}

//-----------------------------------------------------------------------------
void ViewFrame::dragEnter(QDragEnterEvent* evt)
{
  QString mimeType = QString("application/paraview3/%1").arg(getpid());
  //Console().Log("drag enter = %s",mimeType.toStdString().c_str());
  if (evt->mimeData()->hasFormat(mimeType))
    {
    evt->accept();
    }
  else
    {
    evt->ignore();
    }
}

//-----------------------------------------------------------------------------
void ViewFrame::dragMove(QDragMoveEvent* evt)
{
  QString mimeType = QString("application/paraview3/%1").arg(getpid());
  //Console().Log("drag move = %s",mimeType.toStdString().c_str());
  if (evt->mimeData()->hasFormat(mimeType))
    {
    evt->accept();
    }
  else
    {
    evt->ignore();
    }
}

//-----------------------------------------------------------------------------
void ViewFrame::drop(QDropEvent* evt)
{
  QString mimeType = QString("application/paraview3/%1").arg(getpid());
  if (evt->mimeData()->hasFormat(mimeType))
    {
    QByteArray input= evt->mimeData()->data(mimeType);
    QDataStream dataStream(&input, QIODevice::ReadOnly);
    QUuid otherUID;
    dataStream>>otherUID;
    if (otherUID != this->uniqueID())
      {
      this->swapPositions(otherUID.toString());
      }
    evt->accept();
    }
  else
    {
    evt->ignore();
    }
}


}	//end namespace Base