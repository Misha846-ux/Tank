#pragma once
#include "Player.h"
#include <time.h>
#include "Creature.h"
#include "Enemy.h"
#include <time.h>
#include <stdlib.h>
#include "Node.h"
#include "MyList.h"
#include "Wall.h"

using namespace std;


namespace Test {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		virtual void onPaint(System::Object^ obj, PaintEventArgs^ e) override {
			Graphics^ g = e->Graphics;
			for (int i = 1; i <= *enemyCount; i++) {
				Enemy^ cell = enemy->getEnemyFromPosition(i);
				g->FillRectangle(cell->getBrush(), cell->getX(), cell->getY(), cell->getSize(), cell->getSize());
			}
			for (int i = 1; i <= *wallsCount; i++) {
				Wall^ cell = walls->getEnemyFromPosition(i);
				g->FillRectangle(cell->getBrush(), cell->getX(), cell->getY(), cell->getSize(), cell->getSize());
			}
			g->FillRectangle(player->getBrush(), player->getX(), player->getY(), player->getSize(), player->getSize());
			
		}
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		int^ enemyCount;
		Player^ player;
		MyList<Enemy>^ enemy;
		MyList<Wall>^ walls;
		int^ wallsCount;
		Timer^ timer;
		int turn;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(500, 500);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			// 
			// MyForm
			// 
			this->player = gcnew Player();
			this->enemy = gcnew MyList<Enemy>();
			this->walls = gcnew MyList<Wall>();
			this->enemyCount = 5;
			this->wallsCount = 100;
			for (int i = 1; i <= *wallsCount; i++) {
				this->walls->addToHead();
			}
			for (int i = 1; i <= *enemyCount; i++) {
				this->enemy->addToHead();
			}

			for (int i = 1; i <= *enemyCount; i++) {
				this->enemy->getEnemyFromPosition(i)->setEnemyList(this->enemy);
				this->enemy->getEnemyFromPosition(i)->setEnemyCount(this->enemyCount);
			}
			for (int i = 1; i <= *enemyCount; i++) {
				this->enemy->getEnemyFromPosition(i)->setWallsList(this->walls);
				this->enemy->getEnemyFromPosition(i)->setWallsCount(this->wallsCount);
			}


			this->player->setEnemyList(this->enemy);
			this->player->setEnemyCount(enemyCount);
			this->player->setWallsList(this->walls);
			this->player->setWallsCount(wallsCount);
			this->player->setBoardSize(Point(this->ClientSize.Width, this->ClientSize.Height));

			this->turn = 1;
			placeObjects();
			player->setNewPosition(Point(10, 10));
			timer = gcnew Timer();
			timer->Interval = 200;
			timer->Tick += gcnew EventHandler(this, &MyForm::onTimerTick);
			timer->Start();
			this->Paint += gcnew PaintEventHandler(this, &MyForm::onPaint);			
			this->KeyDown += gcnew KeyEventHandler(this, &MyForm::action);

			

		}
#pragma endregion
		bool isEmpty(Point testPoint) {
			if (testPoint == this->player->getPosition()) {
				return false;
			}
			for (int i = 1; i <= *enemyCount; i++) {
				if (testPoint == this->enemy->getEnemyFromPosition(i)->getPosition()) {
					return false;
				}
			}
			for (int i = 1; i <= *wallsCount; i++) {
				if (testPoint == this->walls->getEnemyFromPosition(i)->getPosition()) {
					return false;
				}
			}
			return true;
		}

		void placeObjects() {
			srand(time(NULL));
			int i = 1;
			while (i <= *enemyCount) {
				Enemy^ cell = enemy->getEnemyFromPosition(i);
				int maxX = this->ClientSize.Width / cell->getSize();
				int maxY = this->ClientSize.Height / cell->getSize();
				Point testPoint = Point(rand() % maxX * cell->getSize(), rand() % maxY * cell->getSize());
				if (isEmpty(testPoint) == true) {
					cell->setNewPosition(testPoint);
					i++;
				}
			}
			i = 1;
			while (i <= *wallsCount) {
				Wall^ cell = walls->getEnemyFromPosition(i);
				int maxX = this->ClientSize.Width / cell->getSize();
				int maxY = this->ClientSize.Height / cell->getSize();
				Point testPoint = Point((rand() % (maxX - 0 + 0) + 0) * cell->getSize(), (rand() % (maxY - 0 + 0) + 0) * cell->getSize());
				if (isEmpty(testPoint) == true) {
					cell->setNewPosition(testPoint);
					i++;
				}
			}
		}
		void onTimerTick(Object^ obj, EventArgs^ e) {
			if (this->turn % 2 == 0) {
				for (int i = 1; i <= *enemyCount; i++) {
					enemy->getEnemyFromPosition(i)->enemyAction(player->getPosition(), player->getAlive());
				}
				this->turn++;
			}
			if (*this->player->getAlive() == false) {
				timer->Stop();
				MessageBox::Show("You lose!!");
				return;
			}
			this->Invalidate();
		}
		void action(Object^ obj, KeyEventArgs^ e) {
			if (this->turn % 2 != 0) {
				player->playerAction(e);
				this->turn++;
			}
			
		}
	};
}
