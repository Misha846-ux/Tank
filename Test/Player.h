#pragma once
#include "Creature.h"
#include "Enemy.h"
#include "MyList.h"
#include "Wall.h"

ref class Player: public Creature
{
private:
	MyList<Enemy>^ enemyList;
	MyList<Wall>^ wallsList;
	int^ wallsCount;
	int^ enemyCount;
public:
	Player();
	void playerAction(KeyEventArgs^ e);
	void setEnemyList(MyList<Enemy>^ enemyLink);
	void setEnemyCount(int^ enemyCount);
	void setWallsList(MyList<Wall>^ enemyLink);
	void setWallsCount(int^ enemyCount);
	void shot();
	bool isNextCellEmpty(int look);
};
#pragma endregion

