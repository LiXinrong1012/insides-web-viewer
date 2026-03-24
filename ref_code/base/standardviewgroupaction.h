#ifndef STANDARDVIEWGROUPACTION_H
#define STANDARDVIEWGROUPACTION_H

#include "base/base_global.h"
#include <QActionGroup>
#include <QPointer> // needed for QPointer 

class QWidget;
class QShortcut;

namespace Base{
class ViewFrame;
class View;


/// pqStandardViewFrameActionGroup is a pqViewFrameActionGroup subclass that
/// handles the buttons to be rendered on the left-side of the view-frame for
/// standard views in ParaView including the Render View and Chart views.
class  BASE_EXPORT StandardViewGroupAction : public QActionGroup
{
  Q_OBJECT
  typedef QActionGroup Superclass;
public:
  StandardViewGroupAction(QObject* parent=0);
  virtual ~StandardViewGroupAction();

  /// Tries to add/remove this group's actions to/from the frame if the
  /// view type is supported. Returns whether or not they were.
  virtual bool connect(ViewFrame *frame, View *view);
  virtual bool disconnect(ViewFrame *frame, View *view);
  void setupEmptyFrame(QWidget* frame);

signals:
  void viewAdded(View* view);

protected slots:
  /// Called before the "Convert To" menu is shown. We populate the menu with
  /// actions for available view types.
  void aboutToShowConvertMenu();

  /// This slot is called either from an action in the "Convert To" menu, or from
  /// the buttons on an empty frame.
  void invoked();



  /// If a QAction is added to an exclusive QActionGroup, then a checked action
  /// cannot be unchecked by clicking on it. We need that to work. Hence, we
  /// manually manage the exclusivity of the action group.
  void manageGroupExclusivity(QAction*);

protected:
  

private:
  Q_DISABLE_COPY(StandardViewGroupAction)

  QPointer<QShortcut> ShortCutSurfaceCells;
  QPointer<QShortcut> ShortCutSurfacePoints;
  QPointer<QShortcut> ShortCutFrustumCells;
  QPointer<QShortcut> ShortCutFrustumPoints;
  QPointer<QShortcut> ShortCutBlocks;
};


}//end namespace Base

#endif // STANDARDVIEWGROUPACTION_H
