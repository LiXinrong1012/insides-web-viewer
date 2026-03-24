#include "ViewLayoutManager.h"

#include <assert.h>
#include <algorithm>
#include <vector>
#include <QWeakPointer>
#include <QDataStream>
#include <QFile>

#include "view.h"

#include "ViewFactory.h"
#include "Console.h"

namespace Base{


class ViewLayoutManager::vtkInternals
{
public:
  struct Cell
    {
    ViewLayoutManager::Direction Direction;
    double SplitFraction;
    QWeakPointer<View> ViewProxy;

    Cell() :
      Direction(ViewLayoutManager::NONE),
      SplitFraction(0.5)
	  //, ViewProxy(NULL)
    {
    }
    };


  bool IsCellValid(int location)
    {
    if (location < 0 ||
      location >= static_cast<int>(this->KDTree.size()))
      {
      return false;
      }

    if (location == 0)
      {
      return true;
      }

    // now verify that every parent node for location is a split cell.
    int parent = (static_cast<int>(location) - 1) / 2;
    while (this->KDTree[parent].Direction != ViewLayoutManager::NONE)
      {
      if (parent == 0)
        {
        return true;
        }

      parent = (static_cast<int>(parent) - 1) / 2;
      }

    return false;
    }

  void MoveSubtree(int destination, int source)
    {
    assert(destination >= 0 && source >= 0);

    // we only support moving a subtree "up".
    assert(destination < source);

    if (source >= static_cast<int>(this->KDTree.size()) ||
      destination >= static_cast<int>(this->KDTree.size()))
      {
      return;
      }

    Cell source_cell = this->KDTree[source];
    this->KDTree[source] = Cell();
    this->MoveSubtree(2*destination+1, 2*source+1);
    this->MoveSubtree(2*destination+2, 2*source+2);
    this->KDTree[destination] = source_cell;
    }

  void Shrink()
    {
    size_t max_index = this->GetMaxChildIndex(0);
    assert(max_index < this->KDTree.size());
    this->KDTree.resize(max_index + 1);
    }

  void UpdateViewPositions(int root=0, int posx=0, int posy=0)
    {
    if (root == 0)
      {
      this->Sizes.resize(this->KDTree.size() * 2);
      this->ComputeSizes();
      }

    const Cell& cell = this->KDTree[root];
    if (cell.Direction == ViewLayoutManager::NONE)
      {
      if (cell.ViewProxy)
        {
        int pos[2] = { posx, posy };
        //vtkSMPropertyHelper(cell.ViewProxy, "ViewPosition").Set(pos, 2);
       // cell.ViewProxy->UpdateProperty("ViewPosition");
        }
      //cout << "View Position: " << cell.ViewProxy  << " = "
      //  << posx << "," << posy << endl;
      }
    else
      {
      // root is a split-cell. Determine sizes for the two children.
      const int *size = &this->Sizes[2* (2*root+1)];

      if (cell.Direction == ViewLayoutManager::HORIZONTAL)
        {
        this->UpdateViewPositions(2*root+1, posx, posy);
        this->UpdateViewPositions(2*root+2, posx + size[0], posy);
        }
      else // cell.Direction == VERTICAL
        {
        this->UpdateViewPositions(2*root+1, posx, posy);
        this->UpdateViewPositions(2*root+2, posx, posy + size[1]);
        }
      }
    }

  typedef std::vector<Cell> KDTreeType;
  KDTreeType KDTree;

private:
  size_t GetMaxChildIndex(size_t parent)
    {
    if (this->KDTree[parent].Direction == ViewLayoutManager::NONE)
      {
      return parent;
      }

    size_t child1 = this->GetMaxChildIndex(2*parent + 1);
    size_t child2 = this->GetMaxChildIndex(2*parent + 2);
    return max(child1, child2);
    }

  // temporary vector uses by ComputeSizes() and allocated by
  // UpdateViewPositions().
  std::vector<int> Sizes;

  const int *ComputeSizes(int root=0)
    {
    assert(2*root+1 < static_cast<int>(this->Sizes.size()));

    const Cell& cell = this->KDTree[root];
    if (cell.Direction == ViewLayoutManager::NONE)
      {
      int size[2] = {0, 0};
      if (cell.ViewProxy)
        {
        //vtkSMPropertyHelper(cell.ViewProxy, "ViewSize").Get(size, 2);
        }
      this->Sizes[2*root] = size[0];
      this->Sizes[2*root + 1] = size[1];
      return &this->Sizes[2*root];
      }

    const int *size0 = this->ComputeSizes(2*root+1);
    const int *size1 = this->ComputeSizes(2*root+2);

    // now double the width (or height) based on the split direction.
    if (cell.Direction == ViewLayoutManager::HORIZONTAL)
      {
      this->Sizes[2*root] = size0[0] + size1[0];
      this->Sizes[2*root + 1] = max(size0[1], size1[1]);
      }
    else
      {
      this->Sizes[2*root] = max(size0[0], size1[0]);
      this->Sizes[2*root + 1] = size0[1] + size1[1];
      }
    return &this->Sizes[2*root];
    }
};

//----------------------------------------------------------------------------
ViewLayoutManager::ViewLayoutManager() :
  MaximizedCell(-1),
  Internals(new vtkInternals()),
  BlockUpdate(false)
{

  // Push the root element.
  this->Internals->KDTree.resize(1);
}

//----------------------------------------------------------------------------
ViewLayoutManager::~ViewLayoutManager()
{
  delete this->Internals;
  this->Internals = NULL;
}

//----------------------------------------------------------------------------
void ViewLayoutManager::Reset()
{
  this->Internals->KDTree.clear();
  this->Internals->KDTree.resize(1);
}

//----------------------------------------------------------------------------
//void ViewLayoutManager::LoadState(
//  const vtkSMMessage* message, vtkSMProxyLocator* locator)
//{
//  this->Superclass::LoadState(message, locator);
//
//  if (message->ExtensionSize(ProxyState::user_data) != 1)
//    {
//    // vtkWarningMacro("Missing ViewLayoutState");
//    return;
//    }
//
//  const ProxyState_UserData& user_data =
//    message->GetExtension(ProxyState::user_data, 0);
//  if (user_data.key() != "ViewLayoutState")
//    {
//    //vtkWarningMacro("Unexpected user_data. Expecting ViewLayoutState.");
//    return;
//    }
//
//  this->Internals->KDTree.clear();
//  this->Internals->KDTree.resize(user_data.variant_size());
//
//  for (int cc=0; cc < user_data.variant_size(); cc++)
//    {
//    vtkInternals::Cell &cell = this->Internals->KDTree[cc];
//    const Variant& value = user_data.variant(cc);
//
//    cell.SplitFraction = value.float64(0);
//
//    switch (value.integer(0))
//      {
//    case HORIZONTAL:
//      cell.Direction = HORIZONTAL;
//      break;
//
//    case VERTICAL:
//      cell.Direction = VERTICAL;
//      break;
//
//    case NONE:
//    default:
//      cell.Direction = NONE;
//      }
//
//    if (locator && vtkSMProxyProperty::CanCreateProxy())
//      {
//      cell.ViewProxy = locator->LocateProxy(value.proxy_global_id(0));
//      }
//    else
//      {
//      cell.ViewProxy = vtkSMViewProxy::SafeDownCast(
//        this->GetSession()->GetRemoteObject(value.proxy_global_id(0)));
//      }
//    }
//
//  // let the world know that the layout has been reconfigured.
//  this->InvokeEvent(vtkCommand::ConfigureEvent);
//}


//
////----------------------------------------------------------------------------
//vtkPVXMLElement* ViewLayoutManager::SaveXMLState(
//  vtkPVXMLElement* root, vtkSMPropertyIterator* iter)
//{
//  vtkPVXMLElement* element = this->Superclass::SaveXMLState(root, iter);
//  if (!element)
//    {
//    return NULL;
//    }
//
//  vtkPVXMLElement* layout = vtkPVXMLElement::New();
//  layout->SetName("Layout");
//  layout->AddAttribute("number_of_elements",
//    static_cast<int>(this->Internals->KDTree.size()));
//  element->AddNestedElement(layout);
//  layout->Delete();
//
//  for (size_t cc=0; cc < this->Internals->KDTree.size(); cc++)
//    {
//    const vtkInternals::Cell &cell = this->Internals->KDTree[cc];
//
//    vtkPVXMLElement* item = vtkPVXMLElement::New();
//    item->SetName("Item");
//    item->AddAttribute("direction", static_cast<int>(cell.Direction));
//    item->AddAttribute("fraction", cell.SplitFraction);
//    item->AddAttribute("view", (cell.ViewProxy?
//      static_cast<unsigned int>(cell.ViewProxy->GetGlobalID()) : 0));
//    layout->AddNestedElement(item);
//    item->Delete();
//    }
//
//  return element;
//}

////----------------------------------------------------------------------------
//int ViewLayoutManager::LoadXMLState(
//  vtkPVXMLElement* element, vtkSMProxyLocator* locator)
//{
//  if (!this->Superclass::LoadXMLState(element, locator))
//    {
//    return 0;
//    }
//
//  if (!locator)
//    {
//    return 1;
//    }
//
//  vtkPVXMLElement* layout = element->FindNestedElementByName("Layout");
//  int number_of_elements = 0;
//  if (!layout->GetScalarAttribute("number_of_elements", &number_of_elements) ||
//    (number_of_elements <= 0))
//    {
//    vtkErrorMacro("Missing (or invalid) 'number_of_elements' attribute.");
//    return 0;
//    }
//
//  if (static_cast<int>(layout->GetNumberOfNestedElements()) != number_of_elements)
//    {
//    vtkErrorMacro("Mismatch in number_of_elements and nested elements.");
//    return 0;
//    }
//
//  this->Internals->KDTree.clear();
//  this->Internals->KDTree.resize(number_of_elements);
//  for (unsigned int cc = 0; cc < layout->GetNumberOfNestedElements(); cc++)
//    {
//    vtkPVXMLElement* item = layout->GetNestedElement(cc);
//    if (item == NULL || item->GetName() == NULL ||
//      strcmp(item->GetName(), "Item") != 0)
//      {
//      vtkErrorMacro("Invalid nested element at index : " << cc);
//      return 0;
//      }
//    int direction, viewid;
//    double fraction;
//    if (!item->GetScalarAttribute("direction", &direction) ||
//      !item->GetScalarAttribute("fraction", &fraction) ||
//      !item->GetScalarAttribute("view", &viewid))
//      {
//      vtkErrorMacro("Invalid nested element at index : " << cc);
//      return 0;
//      }
//    vtkInternals::Cell &cell = this->Internals->KDTree[cc];
//    cell.Direction = ((direction == NONE)? NONE : (
//        (direction == HORIZONTAL)? HORIZONTAL : VERTICAL));
//    cell.SplitFraction = fraction;
//    if (viewid)
//      {
//      cell.ViewProxy = locator->LocateProxy(viewid);
//      }
//    else
//      {
//      cell.ViewProxy = NULL;
//      }
//    }
//  return 1;
//}

//----------------------------------------------------------------------------
int ViewLayoutManager::Split(int location, int direction, double fraction)
{
  if (!this->Internals->IsCellValid(location))
    {
    //vtkErrorMacro("Invalid location '" << location << "' specified.");
    return 0;
    }

  // we don't get by value, since we resize the vector.
  vtkInternals::Cell cell = this->Internals->KDTree[location];
  if (cell.Direction != NONE)
    {
    //vtkErrorMacro("Cell identified by location '" << location
      //<< "' is already split. Cannot split the cell again.");
    return 0;
    }

  if (direction <= NONE || direction > HORIZONTAL)
    {
    //vtkErrorMacro("Invalid direction : " << direction);
    return 0;
    }

  if (fraction < 0.0 || fraction > 1.0)
    {
    //vtkErrorMacro("Invalid fraction : " << fraction
    //  << ". Must be in the range [0, 1]");
    return 0;
    }

  cell.Direction = (direction == VERTICAL)? VERTICAL : HORIZONTAL;
  cell.SplitFraction = fraction;

  // ensure that both the children (2i+1), (2i+2) can fit in the KDTree.
  if ( (2*location + 2) >= static_cast<int>(this->Internals->KDTree.size()))
    {
    this->Internals->KDTree.resize(2*location + 2 + 1);
    }

  int child_location = (2*location + 1);
  if (cell.ViewProxy)
    {
    vtkInternals::Cell &child = this->Internals->KDTree[child_location];
    child.ViewProxy = cell.ViewProxy;
    cell.ViewProxy.clear();
    }
  this->Internals->KDTree[location] = cell;
  this->MaximizedCell = -1;
  return child_location;
}

//----------------------------------------------------------------------------
bool ViewLayoutManager::AssignView(int location, View* view)
{
	if (view == NULL)
	{
		return false;
	}
	
	if (!this->Internals->IsCellValid(location))
    {
		//vtkErrorMacro("Invalid location '" << location << "' specified.");
		return false;
    }

	vtkInternals::Cell &cell = this->Internals->KDTree[location];
	if (cell.Direction != NONE)
    {
		//vtkErrorMacro("Cell is not a leaf '" << location << "'."
		//" Cannot assign a view to it.");
		return false;
    }

	if (!cell.ViewProxy.isNull()  && cell.ViewProxy.data() != view)
    {
		//vtkErrorMacro("Cell is not empty.");
		return false;
    }

	if (cell.ViewProxy.data() == view)
    {
		// nothing to do.
		return true;
    }

	cell.ViewProxy = QWeakPointer<View>(view);

  //if (view->property("ViewSize"))
    {
    // every time view-size changes, we update the view positions for all views.
    //view->GetProperty("ViewSize")->AddObserver(
      //vtkCommand::ModifiedEvent, this->Internals->Observer);
    }

  return true;
}

//----------------------------------------------------------------------------
int ViewLayoutManager::AssignViewToAnyCell(
  View* view, int location_hint)
{
  if (!view)
    {
    return 0;
    }

  if (location_hint < 0)
    {
    location_hint = 0;
    }

  // If location_hint refers to an empty cell, use it.
  if (this->Internals->IsCellValid(location_hint))
    {
    int empty_cell = this->GetEmptyCell(location_hint);
    if (empty_cell >= 0)
      {
      return this->AssignView(empty_cell, view);
      }
    }
  else
    {
    // make location_hint a valid location.
    location_hint = 0;
    }

  // Find any empty cell.
  int empty_cell = this->GetEmptyCell(0);
  if (empty_cell >= 0)
    {
    return this->AssignView(empty_cell, view);
    }

  // No empty cell found, split a view, starting with the location_hint.
  Direction direction = HORIZONTAL;

  int parent = this->GetParent(location_hint);
  if (parent >= 0)
    {
    direction = this->GetSplitDirection(parent) == HORIZONTAL?
      VERTICAL: HORIZONTAL;
    }
  int split_cell = this->GetSplittableCell(location_hint, direction);
  assert(split_cell >= 0);

  bool prev = this->SetBlockUpdate(true);
  int new_cell = this->Split(split_cell, direction, 0.5);
  this->SetBlockUpdate(prev);

  if (this->GetView(new_cell) == NULL)
    {
    return this->AssignView(new_cell, view);
    }

  return this->AssignView(new_cell + 1, view);
}

//----------------------------------------------------------------------------
bool ViewLayoutManager::RemoveView(int index)
{
  return this->RemoveView(this->GetView(index)) != -1;
}

//----------------------------------------------------------------------------
int ViewLayoutManager::RemoveView(View* view)
{
  if (!view)
    {
    return -1;
    }

  int index = 0;
  for (vtkInternals::KDTreeType::iterator iter =
    this->Internals->KDTree.begin();
    iter != this->Internals->KDTree.end(); ++iter, ++index)
    {
    if (iter->ViewProxy.data() == view)
      {
      //if (iter->ViewProxy->GetProperty("ViewSize"))
      //  {
      //  iter->ViewProxy->GetProperty("ViewSize")->RemoveObserver(
      //    this->Internals->Observer);
      //  }
      iter->ViewProxy.clear();
      //this->UpdateState();
      return index;
      }
    }

  return -1;
}

//----------------------------------------------------------------------------
bool ViewLayoutManager::SwapCells(int location1, int location2)
{
  if (!this->Internals->IsCellValid(location1) ||
    !this->Internals->IsCellValid(location2))
    {
    //vtkErrorMacro("Invalid locations specified.");
    return false;
    }

  vtkInternals::Cell &cell1 = this->Internals->KDTree[location1];
  vtkInternals::Cell &cell2 = this->Internals->KDTree[location2];
  if (cell1.Direction == NONE && cell2.Direction == NONE)
    {
    QWeakPointer<View> temp1 = cell1.ViewProxy;
    cell1.ViewProxy = cell2.ViewProxy;
    cell2.ViewProxy = temp1;
    //this->UpdateState();
    return true;
    }

  return false;
}

//----------------------------------------------------------------------------
bool ViewLayoutManager::Collapse(int location)
{
  if (!this->Internals->IsCellValid(location))
    {
    //vtkErrorMacro("Invalid location '" << location << "' specified.");
    return false;
    }

  vtkInternals::Cell &cell = this->Internals->KDTree[location];
  if (cell.Direction != NONE)
    {
    //vtkErrorMacro("Only leaf cells can be collapsed.");
    return false;
    }
  
  if (cell.ViewProxy != NULL)
    {
    //vtkErrorMacro("Only empty cells can be collapsed.");
    return false;
    }

  if (location == 0)
    {
    // sure, trying to collapse the root node...whatever!!!
    return true;
    }

  int parent = (location - 1) / 2;
  int sibling = ((location % 2) == 0)? (2*parent + 1) : (2*parent + 2);

  this->Internals->MoveSubtree(parent, sibling);
  this->Internals->Shrink();
  this->MaximizedCell = -1;
  //this->UpdateState();
  return true;
}

//----------------------------------------------------------------------------
bool ViewLayoutManager::IsSplitCell(int location)
{
  if (!this->Internals->IsCellValid(location))
    {
    //vtkErrorMacro("Invalid location '" << location << "' specified.");
    return false;
    }

  const vtkInternals::Cell &cell = this->Internals->KDTree[location];
  return (cell.Direction != NONE);
}

//----------------------------------------------------------------------------
int ViewLayoutManager::GetEmptyCell(int root)
{
  vtkInternals::Cell &cell = this->Internals->KDTree[root];
  if (cell.Direction == NONE && cell.ViewProxy == NULL)
    {
    return root;
    }
  else if (cell.Direction == HORIZONTAL ||
    cell.Direction == VERTICAL)
    {
    int child0 = 2*root + 1;
    int empty_cell = this->GetEmptyCell(child0);
    if (empty_cell >= 0)
      {
      return empty_cell;
      }
    int child1 = 2*root + 2;
    empty_cell = this->GetEmptyCell(child1);
    if (empty_cell >= 0)
      {
      return empty_cell;
      }
    }
  return -1;
}

//----------------------------------------------------------------------------
int ViewLayoutManager::GetSplittableCell(int root,
  ViewLayoutManager::Direction& suggested_direction)
{
  vtkInternals::Cell &cell = this->Internals->KDTree[root];
  if (cell.Direction == NONE)
    {
    return root;
    }
  else if (cell.Direction == HORIZONTAL ||
    cell.Direction == VERTICAL)
    {
    suggested_direction = cell.Direction == HORIZONTAL?
      VERTICAL : HORIZONTAL;
    int child0 = 2*root + 1;
    return this->GetSplittableCell(child0, suggested_direction);
    }
  return -1;
}

//----------------------------------------------------------------------------
ViewLayoutManager::Direction ViewLayoutManager::GetSplitDirection(
  int location)
{
  if (!this->Internals->IsCellValid(location))
    {
    ;//vtkErrorMacro("Invalid location '" << location << "' specified.");
    return NONE;
    }

  return this->Internals->KDTree[location].Direction;
}

//----------------------------------------------------------------------------
double ViewLayoutManager::GetSplitFraction(int location)
{
  if (!this->Internals->IsCellValid(location))
    {
    ;//vtkErrorMacro("Invalid location '" << location << "' specified.");
    return NONE;
    }

  return this->Internals->KDTree[location].SplitFraction;
}

//----------------------------------------------------------------------------
View* ViewLayoutManager::GetView(int location)
{
  if (!this->Internals->IsCellValid(location))
    {
    //vtkErrorMacro("Invalid location '" << location << "' specified.");
    return NULL;
    }

  return this->Internals->KDTree[location].ViewProxy.data();
}

//----------------------------------------------------------------------------
int ViewLayoutManager::GetViewLocation(View* view)
{
  int index = 0;
  for (vtkInternals::KDTreeType::iterator iter =
    this->Internals->KDTree.begin();
    iter != this->Internals->KDTree.end(); ++iter, ++index)
    {
    if (iter->ViewProxy.data() == view)
      {
      return index;
      }
    }
  return -1;
}

//----------------------------------------------------------------------------
bool ViewLayoutManager::SetSplitFraction(int location, double val)
{
  if (val < 0.0 || val > 1.0)
    {
    //vtkErrorMacro("Invalid fraction : " << val
      //<< ". Must be in the range [0, 1]");
    return 0;
    }

  if (!this->IsSplitCell(location))
    {
    return false;
    }

  if (this->Internals->KDTree[location].SplitFraction != val)
    {
    this->Internals->KDTree[location].SplitFraction = val;
    this->MaximizedCell = -1;
    //this->UpdateState();
    }

  return true;
}

//----------------------------------------------------------------------------
void ViewLayoutManager::UpdateViewPositions()
{
  if (this->MaximizedCell == -1)
    {
    this->Internals->UpdateViewPositions();
    }
  else
    {
    // simply set all ViewPositions to 0.
    for (vtkInternals::KDTreeType::iterator iter =
      this->Internals->KDTree.begin();
      iter != this->Internals->KDTree.end();
      ++iter)
      {
      //if (iter->ViewProxy.GetPointer() != NULL)
        {
        int pos[2] = {0, 0};
        //vtkSMPropertyHelper(iter->ViewProxy, "ViewPosition").Set(pos, 2);
        //iter->ViewProxy->UpdateProperty("ViewPosition");
        }
      }
    }
}


//----------------------------------------------------------------------------
bool ViewLayoutManager::MaximizeCell(int location)
{
  if (this->Internals->IsCellValid(location) == false ||
    this->IsSplitCell(location))
    {
    return false;
    }

  this->MaximizedCell = location;
  return true;
}

//----------------------------------------------------------------------------
void ViewLayoutManager::RestoreMaximizedState()
{
  if (this->MaximizedCell != -1)
    {
    this->MaximizedCell = -1;
    }
}

int ViewLayoutManager::GetMaximizedCell()
{
	return MaximizedCell;
}

void ViewLayoutManager::SaveAllState( const QString& fileName )
{
	QFile file(fileName);
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);   // we will serialize the data into the file

	qint32 version=1;
	out<<version;

	// 窗口数目
	out<<qint32(Internals->KDTree.size());

	for (size_t cc=0; cc < this->Internals->KDTree.size(); cc++)
	{
		const vtkInternals::Cell &cell = this->Internals->KDTree[cc];

		out<<static_cast<qint32>(cell.Direction);
		out<<cell.SplitFraction;
		if(cell.ViewProxy){
			out<<(qint32)1;
			out<<cell.ViewProxy.data()->getViewType();

			qint64 flagPos=out.device()->pos();
			out<<(qint64)0;
			qint64 startPos=out.device()->pos();
			cell.ViewProxy.data()->saveState(out);
			qint64 stopPos=out.device()->pos();
			out.device()->seek(flagPos);
			out<<stopPos-startPos;
			out.device()->seek(stopPos);
		}
		else{
			out<<(qint32)0;
		}
	}
}

void ViewLayoutManager::LoadAllState( const QString& fileName )
{
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);   // we will serialize the data into the file

	qint32 version;
	in>>version;

	// 数目
	qint32 viewSize;
	in>>viewSize;

	Internals->KDTree.clear();
	Internals->KDTree.resize(viewSize);

	qint32 tmp;

	for (size_t cc=0; cc < viewSize; cc++)
	{
		vtkInternals::Cell &cell = this->Internals->KDTree[cc];
		in>>tmp;
		cell.Direction = ViewLayoutManager::Direction(tmp);
		in>>cell.SplitFraction;
		in>>tmp;
		if(tmp!=0)
		{
			QString viewType;
			in>>viewType;
			qint64 viewDataSize;
			in>>viewDataSize;
			qint64 currentPos=in.device()->pos();

			View* newView=(View*)ViewFactory::instance()->Produce(viewType);
			if(newView){
				newView->loadState(in,viewDataSize);
				AssignView(cc,newView);
			}
			else{
				Base::Console().Error("Unknown view type: %s",viewType.toStdString().c_str());
			}

			in.device()->seek(currentPos+viewDataSize);
		}
	}

}

}	//end namespace Base