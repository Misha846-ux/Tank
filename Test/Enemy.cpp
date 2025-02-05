#include "Enemy.h"
#include <time.h>
#include <stdlib.h>
Enemy::Enemy() {
	this->brush = gcnew SolidBrush(Color::Red);
	this->enemyCount = 0;
}

Enemy::Enemy(const Enemy^ obj) {
	this->alive = obj->alive;
	this->brush = obj->brush;
	this->look = obj->look;
	this->position = obj->position;
	this->size = obj->look;
}

void Enemy::operator=(Enemy obj) {
	this->alive = obj.alive;
	this->brush = obj.brush;
	this->look = obj.look;
	this->position = obj.position;
	this->size = obj.look;
}

void Enemy::setEnemyList(MyList<Enemy>^ enemyLink) {
	this->enemyList = enemyLink;
}

void Enemy::setEnemyCount(int^ enemyCount) {
	this->enemyCount = enemyCount;
}

void Enemy::setWallsList(MyList<Wall>^ enemyLink) {
	this->wallsList = enemyLink;
}

void Enemy::setWallsCount(int^ enemyCount) {
	this->wallsCount = enemyCount;
}

bool Enemy::isNextCellEmpty(int look, Point playerPosition) {
	//up
	Point newPosition = this->position;
	if (look == -1) {
		newPosition.Y -= this->size;
	}
	// down
	else if (look == 1) {
		newPosition.Y += this->size;
	}
	//left
	else if (look == -2) {
		newPosition.X -= this->size;
	}
	//right
	else if (look == 2) {
		newPosition.X += this->size;
	}
	if (newPosition == playerPosition) {
		return false;
	}
	for (int i = 1; i <= *this->enemyCount; i++) {
		if (newPosition == this->enemyList->getEnemyFromPosition(i)->getPosition()) {
			return false;
		}
	}
	for (int i = 1; i <= *this->wallsCount; i++) {
		if (newPosition == this->wallsList->getEnemyFromPosition(i)->getPosition()) {
			return false;
		}
	}
	return true;
}

bool Enemy::isPlayerOnLine(Point playerPosition) {
	Point newPosition = this->position;

	if (this->look == -1) {
		while (newPosition.Y > 0) {
			newPosition.Y -= this->size;
			if (newPosition == playerPosition) {
				return true;
			}
		}
		return false;
	}
	// down
	else if (this->look == 1) {
		while (newPosition.Y < this->boardSize.Y) {
			newPosition.Y += this->size;
			if (newPosition == playerPosition) {
				return true;
			}
		}
		return false;
	}
	//left
	else if (this->look == -2) {
		while (newPosition.X > 0) {
			newPosition.X -= this->size;
			if (newPosition == playerPosition) {
				return true;
			}
		}
		return false;
	}
	//right
	else if (this->look == 2) {
		while (newPosition.X < this->boardSize.X) {
			newPosition.X += this->size;
			if (newPosition == playerPosition) {
				return true;
			}
		}
		return false;
	}
}

void Enemy::shot(Point playerPosition, bool^ playerLive) {
	Point newPosition = this->position;
	//up
	if (this->look == -1) {
		while (newPosition.Y > 0) {
			newPosition.Y -= this->size;
			if (newPosition == playerPosition) {
				*playerLive = false;
				return;
			}
			for (int i = 1; i <= *this->enemyCount; i++) {
				if (newPosition == this->enemyList->getEnemyFromPosition(i)->getPosition()) {
					this->enemyList->deleteFromPosition(i);
					*this->enemyCount -= 1;
					return;
				}
			}
			for (int i = 1; i <= *this->wallsCount; i++) {
				if (newPosition == this->wallsList->getEnemyFromPosition(i)->getPosition()) {
					this->wallsList->deleteFromPosition(i);
					*this->wallsCount -= 1;
					return;
				}
			}
		}
		return;
	}
	// down
	else if (this->look == 1) {
		while (newPosition.Y < this->boardSize.Y) {
			newPosition.Y += this->size;
			if (newPosition == playerPosition) {
				*playerLive = false;
				return;
			}
			for (int i = 1; i <= *this->enemyCount; i++) {
				if (newPosition == this->enemyList->getEnemyFromPosition(i)->getPosition()) {
					this->enemyList->deleteFromPosition(i);
					*this->enemyCount -= 1;
					return;
				}
			}
			for (int i = 1; i <= *this->wallsCount; i++) {
				if (newPosition == this->wallsList->getEnemyFromPosition(i)->getPosition()) {
					this->wallsList->deleteFromPosition(i);
					*this->wallsCount -= 1;
					return;
				}
			}
		}
		return;
	}
	//left
	else if (this->look == -2) {
		while (newPosition.X > 0) {
			newPosition.X -= this->size;
			if (newPosition == playerPosition) {
				*playerLive = false;
				return;
			}
			for (int i = 1; i <= *this->enemyCount; i++) {
				if (newPosition == this->enemyList->getEnemyFromPosition(i)->getPosition()) {
					this->enemyList->deleteFromPosition(i);
					*this->enemyCount -= 1;
					return;
				}
			}
			for (int i = 1; i <= *this->wallsCount; i++) {
				if (newPosition == this->wallsList->getEnemyFromPosition(i)->getPosition()) {
					this->wallsList->deleteFromPosition(i);
					*this->wallsCount -= 1;
					return;
				}
			}
		}
		return;
	}
	//right
	else if (this->look == 2) {
		while (newPosition.X < this->boardSize.X) {
			newPosition.X += this->size;
			if (newPosition == playerPosition) {
				*playerLive = false;
				return;
			}
			for (int i = 1; i <= *this->enemyCount; i++) {
				if (newPosition == this->enemyList->getEnemyFromPosition(i)->getPosition()) {
					this->enemyList->deleteFromPosition(i);
					*this->enemyCount -= 1;
					return;
				}
			}
			for (int i = 1; i <= *this->wallsCount; i++) {
				if (newPosition == this->wallsList->getEnemyFromPosition(i)->getPosition()) {
					this->wallsList->deleteFromPosition(i);
					*this->wallsCount -= 1;
					return;
				}
			}
		}
		return;
	}
}

void Enemy::enemyAction(Point playerPosition, bool^ playerLive) {
	if (*this->alive == true) {
		if (this->isPlayerOnLine(playerPosition) == true) {
			this->shot(playerPosition, playerLive);
		}
		else {
			srand(time(NULL));
			int randNum = rand() % (20 - 1 + 1) + 1;
			if (randNum > 9) {
				if (playerPosition.X > this->position.X) {
					this->look = 2;
					if (this->isNextCellEmpty(this->look, playerPosition)) {
						this->position.X += this->size;
					}
				}
				else if (playerPosition.X < this->position.X) {
					this->look = -2;
					if (this->isNextCellEmpty(this->look, playerPosition)) {
						this->position.X -= this->size;
					}
				}
				else if (playerPosition.X == this->position.X) {
					if (playerPosition.Y > this->position.Y) {
						this->look = 1;
						if (this->isNextCellEmpty(this->look, playerPosition)) {
							this->position.Y += this->size;
						}
					}
					else if (playerPosition.Y < this->position.Y) {
						this->look = -1;
						if (this->isNextCellEmpty(this->look, playerPosition)) {
							this->position.Y -= this->size;
						}
					}
				}
			}
			else {
				if (playerPosition.Y > this->position.Y) {
					this->look = 1;
					if (this->isNextCellEmpty(this->look, playerPosition)) {
						this->position.Y += this->size;
					}
				}
				else if (playerPosition.Y < this->position.Y) {
					this->look = -1;
					if (this->isNextCellEmpty(this->look, playerPosition)) {
						this->position.Y -= this->size;
					}
				}
				else if (playerPosition.Y == this->position.Y) {
					if (playerPosition.X > this->position.X) {
						this->look = 2;
						if (this->isNextCellEmpty(this->look, playerPosition)) {
							this->position.X += this->size;
						}
					}
					else if (playerPosition.X < this->position.X) {
						this->look = -2;
						if (this->isNextCellEmpty(this->look, playerPosition)) {
							this->position.X -= this->size;
						}
					}
				}
			}
		}
	}
}

