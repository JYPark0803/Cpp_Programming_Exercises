#pragma once
#include "Canvas.h"
#include "VariousMonsters.h"
#include "Human.h"
#include "Matrix.h"
#include <windows.h>
#define MAXMONS 8

class MonsterWorld
{
	Matrix world;
	int xMax, yMax, nMon, nMove;
	Monster* pMon[MAXMONS];
	Canvas	canvas;

	int& Map(int x, int y) { return world.elem(x, y); }
	bool isDone() { return countItems() == 0; }
	int countItems()
	{
		int nItems = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) nItems++;
		return nItems;
	}

	void print()
	{
		canvas.clear();
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) canvas.draw(x, y, "■");
		for (int i = 0; i < nMon; i++)
			pMon[i]->draw(canvas);
		canvas.print("[ Monster World (신인류의 탄생) ]");

		cerr << " 전체 이동 횟수 = " << nMove << endl;
		cerr << " 남은 아이템 수 = " << countItems() << endl;
		for (int i = 0; i < nMon; i++)
			pMon[i]->print();
	}

public:
	MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h)
	{
		nMon = 0;
		nMove = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++) Map(x, y) = 1;
	}
	~MonsterWorld()
	{
		for (int i = 0; i < nMon; i++)
			delete pMon[i];
	}

	void add(Monster* m)
	{
		if (nMon < MAXMONS)
			pMon[nMon++] = m;
	}

	void play(int maxwalk, int wait)
	{
		print();
		cerr << " 엔터를 누르세요...";
		getchar();
		for (int i = 0; i < maxwalk; i++)
		{
			for (int k = 0; k < nMon - 2; k++)
				pMon[k]->move(world.Data(), xMax, yMax);

			if (_kbhit())
			{
				unsigned char ch = _getche();
				if (ch == 224)
				{
					ch = _getche();
					((Tuman*)(pMon[nMon - 1]))->move(world.Data(), xMax, yMax, ch);
				}
				else
					((Tuman*)(pMon[nMon - 2]))->move(world.Data(), xMax, yMax, ch);
			}
			nMove++;
			print();
			if (isDone()) break;
			Sleep(wait);
		}
	}
};