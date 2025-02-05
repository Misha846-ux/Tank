#pragma once
#include "Creature.h"
#include <time.h>
#include <stdlib.h>
#include "MyList.h"
#include "Wall.h"

ref class Enemy: public Creature
{
private:
	MyList<Enemy>^ enemyList;
	MyList<Wall>^ wallsList;
	int^ wallsCount;
	int^ enemyCount;
public:
	Enemy();
	Enemy(const Enemy^ obj);
	void operator=(Enemy obj);
	void setEnemyList(MyList<Enemy>^ enemyLink);
	void setEnemyCount(int^ enemyCount);
	void setWallsList(MyList<Wall>^ enemyLink);
	bool isPlayerOnLine(Point playerPosition);
	void setWallsCount(int^ enemyCount);
	void shot(Point playerPosition, bool^ playerLive);
	void enemyAction(Point playerPosition, bool^ playerLive);
	bool isNextCellEmpty(int look, Point playerPosition);
};
#pragma endregion
