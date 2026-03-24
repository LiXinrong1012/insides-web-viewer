#ifndef VIEWFRAME_H
#define VIEWFRAME_H

#include "base/base_global.h"
#include <QtCore/qglobal.h>
#include <QtGlobal>
#include <QWidget>
#include <QPointer>
#include <QMap>
#include <QUuid>

class QDragEnterEvent;
class QDragMoveEvent;
class QDropEvent;
class QMenu;
class QToolButton;


namespace Base{

/*!
*	From Paraview.
*	@author Jerry He
*	@date	2014.3.26
*/
/// pqViewFrame is used to represent a frame for any ParaView view shown in the
/// pqMultiViewWidget. A frame has title-bar that can be used to show arbitrary
/// buttons, as well as a border that can be used to indicate if the frame is
/// active.
class BASE_EXPORT ViewFrame : public QWidget
{
  Q_OBJECT
  typedef QWidget Superclass;
public:
  ViewFrame(QWidget* parent=0);
  virtual ~ViewFrame();

  /// Get/Set the window title. If not empty, the title is shown in the
  /// title-bar.
  void setTitle(const QString& text) { this->Title = text; }
  const QString& title() const { return this->Title; }

  /// Get/Set the central widget shown in this frame.
  void setCentralWidget(QWidget* widget);
  QWidget* centralWidget() const;

  /// Get/Set the border BorderColor. The border is only drawn when the
  /// borderVisibility is set to true.
  void setBorderColor(const QColor& clr) { this->BorderColor = clr; }
  const QColor& borderColor() const { return this->BorderColor; }

  /// Get/Set the border visibility.
  bool isBorderVisible() const { return this->BorderVisible; }

  /// Get whether the title-bar is shown.
  bool isTitleBarVisible() const { return this->TitleBarVisible; }

  enum StandardButton
    {
    NoButton          =0x0000,
    SplitVertical     =0x0001,
    SplitHorizontal   =0x0002,
    Maximize          =0x0004,
    Restore           =0x0008,
    Close             =0x0010
    };

  Q_DECLARE_FLAGS(StandardButtons, StandardButton);

  /// This holds the collection of standard buttons the frame should show in the
  /// title-bar.
  void setStandardButtons(StandardButtons buttons);
  StandardButtons standardButtons() const { return this->Buttons; }

  /// One can add arbitrary actions to be shown on the title bar.
  void addTitleBarAction(QAction* action);
  QAction* addTitleBarAction(const QString& title);
  QAction* addTitleBarAction(const QIcon& icon, const QString& title);

  /// remove all added custom title-bar actions.
  void removeTitleBarActions();

  /// Provides access to the context menu.
  QMenu* contextMenu() const
    { return this->ContextMenu; }

  /// provides access to the unique id assigned to the frame.
  QUuid uniqueID() const
    { return this->UniqueID; }

signals:
  /// fired when a standard button is pressed.
  void buttonPressed(int button);

  /// fired when one of the custom title-bar actions is triggered.
  void actionTriggered(QAction* action);

  /// Fired to indicate the positions for the two frames need to be swapped.
  void swapPositions(const QString& other);
  
public slots:
  /// set whether the border is visible.
  void setBorderVisibility(bool val) 
    {
    this->BorderVisible = val;
    this->updateLayout();
    }

  /// set whether the title-bar is visible.
  void setTitleBarVisibility(bool val)
    {
    this->TitleBarVisible = val;
    this->updateLayout();
    }

  void setDecorationsVisibility(bool val)
    {
    this->DecorationsVisible = val;
    this->updateLayout();
    }

  /// event filter to handle drag/drop events.
  virtual bool eventFilter(QObject*, QEvent*);

protected:
  /// updates the layout.
  void updateLayout();
  void updateTitleBar();
  void paintEvent(QPaintEvent* event);

  /// methods to manage drag-drop.
  void drag();
  void dragEnter(QDragEnterEvent*);
  void dragMove(QDragMoveEvent*);
  void drop(QDropEvent*);

protected slots:
  void buttonClicked();
  void contextMenuRequested(const QPoint&);

protected:
  bool DecorationsVisible;
  bool TitleBarVisible;
  bool BorderVisible;
  QColor BorderColor;
  QString Title;
  StandardButtons Buttons;
  QPointer<QWidget> CentralWidget;
  QPointer<QWidget> TitleBar;
  QMenu* ContextMenu;
  QUuid UniqueID;
  QPoint DragStartPosition;
  QList<QToolButton*> ToolButtons;
  QMap<StandardButton, QPointer<QToolButton> > StandardToolButtons;

private:
  Q_DISABLE_COPY(ViewFrame)

  /// creates a tool button for the action.
  QToolButton* createButton(QAction* action);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ViewFrame::StandardButtons);



}	//end namespace Base

#endif // VIEWFRAME_H
