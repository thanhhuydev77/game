#include "Grid.h"

Grid *Grid::_instance = NULL;
void Grid::insertlistgrid(int id, int left, int right)
{
	gridround griden;
	griden.Id = id;
	griden.Left = left;
	griden.Right = right;
	listgrid.push_back(griden);
}
//void Grid::insert(int gridnumber, CGameObject * object)
//{
//	
//	this->object[gridnumber].push_back(object);
//}
Grid * Grid::getInstace()
{
	if (_instance == nullptr)
		_instance = new Grid();

	return _instance ;
}

Grid::Grid()
{
}

vector<int> Grid::checkingrid()
{
	vector<int> ingrid;
	ingrid.clear();
	RECT check = Camera::getInstance()->GetBound();
	// check where camera
	for (int i = 0; i < listgrid.size(); i++)
	{
		//check left in which grid
		if (check.left >= listgrid[i].Left && check.left <= listgrid[i].Right)
			ingrid.push_back(listgrid[i].Id);

	
		if (check.right >= listgrid[i].Left && check.right <= listgrid[i].Right && listgrid[i].Id != ingrid[0])
			ingrid.push_back(listgrid[i].Id);
	}
	return ingrid;
}

//vector<CGameObject*> Grid::getlistobject()
//{
//	vector<CGameObject*> list;
//	list.clear();
//	//list id grid
//	vector<int> currentgrid = checkingrid();
//	for (int i = 0; i < currentgrid.size(); i++)
//	{
//		for (int j = 0; j<(object[i].size()); j++)
//		{
//			list.push_back(object[i][j]);
//		}
//	}
//	return list;
//}

bool Grid::isincurrentGrid(CGameObject * object)
{
	vector<int> currentgrid = checkingrid();
	for (int i = 0; i < object->getlistgrid().size(); i++)
	{
		for (int j = 0; j < currentgrid.size(); j++)
			if ((object->getlistgrid())[i] == currentgrid[j])
				return true;
	}
	return false;
}

Grid::~Grid()
{
}
