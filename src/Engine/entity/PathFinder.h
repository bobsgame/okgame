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
	sp<TilePath> outerInstance = nullptr;


public:
	int tileX = 0;
	int tileY = 0;


	PathTile(sp<TilePath> outerInstance, int tileX, int tileY);


	int getX();


	int getY();


	int hashCode();


	//bool equals(void* other);
};

//=========================================================================================================================

class TilePath
{ //=========================================================================================================================
private:
	sp<PathFinder> outerInstance = nullptr;


public:
	deque<sp<PathTile>>* pathTiles = new deque<sp<PathTile>>();


	TilePath(sp<PathFinder> outerInstance);


	int getLength();


	sp<PathTile> getTileForPathIndex(int index);


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
	sp<PathFinder> outerInstance = nullptr;

public:
	SortedList(sp<PathFinder> outerInstance);

	/// <summary>
	/// The list of elements </summary>
private:
	vector<sp<PotentialTile>> list;// = ms<ArrayList><sp<PotentialTile>>();


	/// <summary>
	/// Retrieve the first element from the list
	/// </summary>
	/// <returns> The first element from the list </returns>
public:
	sp<PotentialTile> first();


	/// <summary>
	/// Empty the list
	/// </summary>
	void clear();


	void addAndSort(sp<PotentialTile> o);


	void remove(sp<PotentialTile> o);


	int size();


	bool contains(sp<PotentialTile> o);
};

class PotentialTile
{ //=========================================================================================================================
public:
	sp<PathFinder> outerInstance = nullptr;


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
	sp<PotentialTile> parent;
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
	int setParentTile(sp<PotentialTile> parent);


	/// <seealso cref= Comparable#compareTo(Object) </seealso>
	//=========================================================================================================================
	int compareTo(sp<PotentialTile> o);
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
	sp<TilePath> path = nullptr;

private:
	vector<sp<PotentialTile>> blockedPotentialTilesList;// = ms<ArrayList><sp<PotentialTile>>();
	sp<SortedList> openPotentialTilesList = ms<SortedList>(this);

	//ArrayList<ArrayList<sp<PotentialTile>>>* potentialTiles = ms<ArrayList><ArrayList<sp<PotentialTile>>>();
	vector<sp<PotentialTile>> potentialTiles;// = nullptr;
	bool* checkedTileArray = nullptr;


	int maxSearchDistance = 0;
	bool allowDiagMovement = false;

public:
	sp<Entity> e = nullptr;


	int w = 0;
	int h = 0;


	//=========================================================================================================================
	PathFinder(sp<Entity> e, float middleStartXPixelsHQ, float middleStartYPixelsHQ, float finishXPixelsHQ, float finishYPixelsHQ, int mapWidthTiles1X, int mapHeightTiles1X);


	//=========================================================================================================================
	sp<TilePath> findPath(int startTileX, int startTileY, int toTileX, int toTileY);


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

