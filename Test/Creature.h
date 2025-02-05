#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;
//-1 up
// 1 down
//-2 left
// 2 right
ref class Creature
{
protected:

	Point position;
	Point boardSize;
	Brush^ brush;
	bool^ alive;
	int size;
	int look;
public:
	Creature();
	Creature(int positionX, int positionY);
	void setNewPosition(Point obj);
	Point getPosition();
	int getLook();
	bool^ getAlive();
	int getX();
	int getY();
	int getSize();
	Brush^ getBrush();
	void setBrush(Brush^ obj);
	void setAlive(bool alive);
	void setSize(int size);
	void setLook(int look);
	void setBoardSize(Point boardSize);
};

