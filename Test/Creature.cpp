#include "Creature.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;

Creature::Creature() {
	this->position = Point(100, 100);
	this->alive = gcnew bool(true);
	this->size = 10;
}

Creature::Creature(int positionX, int positionY) {
	this->position = Point(positionX, positionY);
	this->size = 10;
}

void Creature::setNewPosition(Point obj) {
	this->position = obj;
}


Point Creature::getPosition() {
	return this->position;
}

int Creature::getX() {
	return this->position.X;
}

int Creature::getY() {
	return this->position.Y;
}

bool^ Creature::getAlive() {
	return this->alive;
}

int Creature::getLook() {
	return this->look;
}

int Creature::getSize() {
	return this->size;
}

Brush^ Creature::getBrush() {
	return this->brush;
}

void Creature::setBrush(Brush^ obj) {
	this->brush = obj;
}

void Creature::setAlive(bool alive) {
	*this->alive = alive;
}

void Creature::setLook(int look) {
	this->look = look;
}

void Creature::setSize(int size) {
	this->size = size;
}

void Creature::setBoardSize(Point boardSize) {
	this->boardSize = boardSize;
}