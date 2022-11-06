//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;
#include <deque>



class PotentialTile;
class Comparable;
class TilePath;


class PathTile
{ //=========================================================================================================================
private:
	shared_ptr<TilePath> outerInstance = nullptr;


public:
	int tileX = 0;
	int tileY = 0;


	PathTile(shared_ptr<TilePath> outerInstance, int tileX, int tileY);


	int getX();


	int getY();


	int hashCode();


	//bool equals(void* other);
};

//=========================================================================================================================

class TilePath
{ //=========================================================================================================================
private:
	shared_ptr<PathFinder> outerInstance = nullptr;


public:
	deque<shared_ptr<PathTile>>* pathTiles = new deque<shared_ptr<PathTile>>();


	TilePath(shared_ptr<PathFinder> outerInstance);


	int getLength();


	shared_ptr<PathTile> getTileForPathIndex(int index);


	int getTileXForPathIndex(int index);


	int getTileYForPathIndex(int index);


	void addPathTileToEnd(int x, int y);


	void addPathTileToBeginning(int x, int y);


	bool doesPathContain(int tileX, int tileY);

	//=========================================================================================================================
public:
};

class SortedList
{ //=========================================================================================================================
private:
	shared_ptr<PathFinder> outerInstance = nullptr;

public:
	SortedList(shared_ptr<PathFinder> outerInstance);

	/// <summary>
	/// The list of elements </summary>
private:
	ArrayList<shared_ptr<PotentialTile>> list;// = make_shared<ArrayList><shared_ptr<PotentialTile>>();


	/// <summary>
	/// Retrieve the first element from the list
	/// </summary>
	/// <returns> The first element from the list </returns>
public:
	shared_ptr<PotentialTile> first();


	/// <summary>
	/// Empty the list
	/// </summary>
	void clear();


	void addAndSort(shared_ptr<PotentialTile> o);


	void remove(shared_ptr<PotentialTile> o);


	int size();


	bool contains(shared_ptr<PotentialTile> o);
};

class PotentialTile
{ //=========================================================================================================================
public:
	shared_ptr<PathFinder> outerInstance = nullptr;


	/// <summary>
	/// The x coordinate of the node </summary>
	int x = 0;
	/// <summary>
	/// The y coordinate of the node </summary>
	int y = 0;
	/// <summary>
	/// The path cost for this node </summary>
	float cumulativePathCost = 0;
	/// <summary>
	/// The parent of this node, how we reached it in the search </summary>
	shared_ptr<PotentialTile> parent;
	/// <summary>
	/// The heuristic cost of this node </summary>
	float heuristicCost = 0;
	/// <summary>
	/// The search depth of this node </summary>
	int depth = 0;


	//=========================================================================================================================
public:
	PotentialTile(int x, int y);


	//=========================================================================================================================
	int setParentTile(shared_ptr<PotentialTile> parent);


	/// <seealso cref= Comparable#compareTo(Object) </seealso>
	//=========================================================================================================================
	int compareTo(shared_ptr<PotentialTile> o);
};


class PathFinder
{ //=========================================================================================================================


	//=========================================================================================================================
private:


	/// <summary>
	/// A single node in the search graph
	/// </summary>
	//=========================================================================================================================


public:
	shared_ptr<TilePath> path = nullptr;

private:
	ArrayList<shared_ptr<PotentialTile>> blockedPotentialTilesList;// = make_shared<ArrayList><shared_ptr<PotentialTile>>();
	shared_ptr<SortedList> openPotentialTilesList = make_shared<SortedList>(this);

	//ArrayList<ArrayList<shared_ptr<PotentialTile>>>* potentialTiles = make_shared<ArrayList><ArrayList<shared_ptr<PotentialTile>>>();
	vector<shared_ptr<PotentialTile>> potentialTiles;// = nullptr;
	bool* checkedTileArray = nullptr;


	int maxSearchDistance = 0;
	bool allowDiagMovement = false;

public:
	shared_ptr<Entity> e = nullptr;


	int w = 0;
	int h = 0;


	//=========================================================================================================================
	PathFinder(shared_ptr<Entity> e, float middleStartXPixelsHQ, float middleStartYPixelsHQ, float finishXPixelsHQ, float finishYPixelsHQ, int mapWidthTiles1X, int mapHeightTiles1X);


	//=========================================================================================================================
	shared_ptr<TilePath> findPath(int startTileX, int startTileY, int toTileX, int toTileY);


	//=========================================================================================================================
	bool isTileBlocked(int tileX, int tileY);


private:
	int minCost = 0;
	//=========================================================================================================================
public:
	int getHeuristicCost(int tileX, int tileY, int endTileX, int endTileY);

	//=========================================================================================================================
	int getTileTypeCost(int fromTileX, int fromTileY, int toTileX, int toTileY);


	//=========================================================================================================================
	void setTileChecked(int tileX, int tileY);


	//=========================================================================================================================
	bool wasTileChecked(int tileX, int tileY);


	//=========================================================================================================================
protected:
	bool isValidLocation(int currentTileX, int currentTileY, int checkTileX, int checkTileY);
};

