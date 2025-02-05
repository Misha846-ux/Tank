#include "Player.h"

Player::Player() {
	delete this->brush;
	this->brush = gcnew SolidBrush(Color::Orange);
	this->look = -1;
}

void Player::setEnemyList(MyList<Enemy>^ enemyLink) {
	this->enemyList = enemyLink;
}

void Player::setEnemyCount(int^ enemyCount) {
	this->enemyCount = enemyCount;
}

void Player::setWallsList(MyList<Wall>^ enemyLink) {
	this->wallsList = enemyLink;
}

void Player::setWallsCount(int^ enemyCount) {
	this->wallsCount = enemyCount;
}

bool Player::isNextCellEmpty(int look) {
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

void Player::shot() {
	Point newPosition = this->position;
	//up
	if (this->look == -1) {
		while (newPosition.Y > 0) {
			newPosition.Y -= this->size;
			for (int i = 1; i <= *this->enemyCount; i++) {
				if (newPosition == this->enemyList->getEnemyFromPosition(i)->getPosition()) {
					if (*this->enemyList->getEnemyFromPosition(i)->getAlive() == true) {
						delete this->enemyList->getEnemyFromPosition(i)->getBrush();
						this->enemyList->getEnemyFromPosition(i)->setAlive(false);
						this->enemyList->getEnemyFromPosition(i)->setBrush(gcnew SolidBrush(Color::White));
						return;
					}
					else {
						this->enemyList->deleteFromPosition(i);
						*this->enemyCount -= 1;
						return;
					}
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
			for (int i = 1; i <= *this->enemyCount; i++) {
				if (newPosition == this->enemyList->getEnemyFromPosition(i)->getPosition()) {
					if (*this->enemyList->getEnemyFromPosition(i)->getAlive() == true) {
						delete this->enemyList->getEnemyFromPosition(i)->getBrush();
						this->enemyList->getEnemyFromPosition(i)->setAlive(false);
						this->enemyList->getEnemyFromPosition(i)->setBrush(gcnew SolidBrush(Color::White));
						return;
					}
					else {
						this->enemyList->deleteFromPosition(i);
						*this->enemyCount -= 1;
						return;
					}
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
			for (int i = 1; i <= *this->enemyCount; i++) {
				if (*this->enemyList->getEnemyFromPosition(i)->getAlive() == true) {
					delete this->enemyList->getEnemyFromPosition(i)->getBrush();
					this->enemyList->getEnemyFromPosition(i)->setAlive(false);
					this->enemyList->getEnemyFromPosition(i)->setBrush(gcnew SolidBrush(Color::White));
					return;
				}
				else {
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
			for (int i = 1; i <= *this->enemyCount; i++) {
				if (*this->enemyList->getEnemyFromPosition(i)->getAlive() == true) {
					delete this->enemyList->getEnemyFromPosition(i)->getBrush();
					this->enemyList->getEnemyFromPosition(i)->setAlive(false);
					this->enemyList->getEnemyFromPosition(i)->setBrush(gcnew SolidBrush(Color::White));
					return;
				}
				else {
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

void Player::playerAction(KeyEventArgs^ e) {
	switch (e->KeyCode)
	{
	case Keys::W:
		this->look = -1;
		if (this->isNextCellEmpty(this->look)) {
			this->position.Y -= this->size;
		}
		break;
	case Keys::S:
		this->look = 1;
		if (this->isNextCellEmpty(this->look)) {
			this->position.Y += this->size;
		}
		break;
	case Keys::A:
		this->look = -2;
		if (this->isNextCellEmpty(this->look)) {
			this->position.X -= this->size;
		}
		break;
	case Keys::D:
		this->look = 2;
		if (this->isNextCellEmpty(this->look)) {
			this->position.X += this->size;
		}
		break;
	case Keys::Space:
		this->shot();
		break;
	default:
		break;
	}
}