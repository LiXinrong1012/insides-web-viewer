#include "standardviewgroupaction.h"

#include "StandardViewGroupAction.h"
#include "ui_EmptyView.h"

#include "ViewFactory.h"
#include "viewframe.h"
#include "view.h"
#include "activeviewobject.h"

#include <QMenu>
#include <QPushButton>
#include <QSet>
#include <QShortcut>


using namespace Base;


namespace Base{

//-----------------------------------------------------------------------------
StandardViewGroupAction::StandardViewGroupAction(QObject* parentObject)
  : Superclass(parentObject)
{

}

//-----------------------------------------------------------------------------
StandardViewGroupAction::~StandardViewGroupAction()
{
}


//-----------------------------------------------------------------------------
bool StandardViewGroupAction::connect(ViewFrame *frame, View *view)
{
  Q_ASSERT(frame != NULL);

  //frame->contextMenu()->addSeparator();
  //QMenu* convertMenu = frame->contextMenu()->addMenu("Convert To ...");
  //QObject::connect(convertMenu, SIGNAL(aboutToShow()),
  //  this, SLOT(aboutToShowConvertMenu()));

  // add toolbars
  if(view){
	  frame->removeTitleBarActions();
	  QList<QAction*> aclist=view->getActionList();
	  int n=aclist.size()-1;
	  for(int i=n;i>=0;--i)
		  frame->addTitleBarAction(aclist[i]);
  }

  if (view == NULL)
    {
    // Setup the UI shown when no view is present in the frame.
    QWidget* empty_frame = new QWidget(frame);
    this->setupEmptyFrame(empty_frame);
    frame->setCentralWidget(empty_frame);
    return true;
    }


  return true;
}

//-----------------------------------------------------------------------------
bool StandardViewGroupAction::disconnect(ViewFrame *frame, View * view)
{
  frame->removeTitleBarActions(); 
  return true;
}

//-----------------------------------------------------------------------------
namespace
{
  struct ViewType
    {
    QString Label;
    QString Name;
    };

  bool ViewTypeComparator(const ViewType& one, const ViewType& two)
    {
    return one.Label.toLower() < two.Label.toLower();
    }

  static QList<ViewType> availableViewTypes()
    {
    QList<ViewType> views;

	ViewFactory* factory=ViewFactory::instance();
	std::list<QString> viewtypelist=factory->CanProduce();

    foreach (QString vi, viewtypelist)
      {
        ViewType info;
        info.Label = vi;
        info.Name = vi;
        views.push_back(info);
	}
    qSort(views.begin(), views.end(), ViewTypeComparator);
    return views;
    }
} 

//-----------------------------------------------------------------------------
void StandardViewGroupAction::aboutToShowConvertMenu()
{
  QMenu* menu = qobject_cast<QMenu*>(this->sender());
  if (menu)
    {
    menu->clear();
    QList<ViewType> views = availableViewTypes();
    foreach (const ViewType& type, views)
      {
      QAction* view_action = new QAction(type.Label, menu);
      view_action->setProperty("PV_VIEW_TYPE", type.Name);
      view_action->setProperty("PV_VIEW_LABEL", type.Label);
      view_action->setProperty("PV_COMMAND", "Convert To");
      menu->addAction(view_action);
      QObject::connect(view_action, SIGNAL(triggered()),
        this, SLOT(invoked()), Qt::QueuedConnection);
      }
    }
}

//-----------------------------------------------------------------------------
void StandardViewGroupAction::setupEmptyFrame(QWidget* frame)
{
  Ui::EmptyView ui;
  ui.setupUi(frame);

  QList<ViewType> views = availableViewTypes();
  foreach (const ViewType& type, views)
    {
    QPushButton* button = new QPushButton(type.Label, ui.ConvertActionsFrame);
    button->setObjectName(type.Name);
    button->setProperty("PV_VIEW_TYPE", type.Name);
    button->setProperty("PV_VIEW_LABEL", type.Label);
    button->setProperty("PV_COMMAND", "Create");

    QObject::connect(button, SIGNAL(clicked()),
      this, SLOT(invoked()), Qt::QueuedConnection);
    ui.ConvertActionsFrame->layout()->addWidget(button);
    }
}

//-----------------------------------------------------------------------------
void StandardViewGroupAction::invoked()
{
	QObject* osender = this->sender();
	if (!osender)
		return;

  // either create a new view, or convert the existing one.
  // This slot is called either from an action in the "Convert To" menu, or from
  // the buttons on an empty frame.
  QString type = osender->property("PV_VIEW_TYPE").toString();
  QString label = osender->property("PV_VIEW_LABEL").toString();
  QString command = osender->property("PV_COMMAND").toString();

	View* cur=ActiveViewObject::instance()->activeView();
	ViewLayoutManager* layoutManager=ActiveViewObject::instance()->currentViewLayoutManager();

	// destroy active-view, if present (implying convert was called).
	if(cur )
		delete cur;
	Base::ViewFactory* viewFactory=Base::ViewFactory::instance();
	View* view=(View*)viewFactory->Produce(type);
	emit viewAdded(view);
  //if (type != "None")
  //  {
  //  builder->createView(type, pqActiveObjects::instance().activeServer());
  //  }

}


//-----------------------------------------------------------------------------
namespace
{
  inline QAction* findActiveAction(const QString& name)
    {
    //View* activeView = pqActiveObjects::instance().activeView();
    //if (activeView && activeView->getWidget() &&
    //  activeView->getWidget()->parentWidget())
    //  {
    //  return activeView->getWidget()->parentWidget()->findChild<QAction*>(name);
    //  }
    //return NULL;
    }

  inline void triggerAction(const QString& name)
    {
    QAction* atcn = findActiveAction(name);
    if (atcn)
      {
      atcn->trigger();
      }
    }
}





//-----------------------------------------------------------------------------
void StandardViewGroupAction::manageGroupExclusivity(QAction* curAction)
{
  if (!curAction || !curAction->isChecked())
    {
    return;
    }

  QActionGroup* group = qobject_cast<QActionGroup*>(this->sender());
  foreach (QAction* groupAction, group->actions())
    {
    if (groupAction != curAction && groupAction->isChecked())
      {
      groupAction->setChecked(false);
      }
    }
}

}	//end namespace Base