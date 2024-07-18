#include <iostream>
#include <string>
#include <conio.h>

#include "Base.h"
#include "Pawn.h"
#include "InfoList.h"
using namespace std;

//共计1391行左右的代码量！！！

//程序初始化
void Init()
{
	srand(time(0));

	InfoList::Instance->x = 0;
	InfoList::Instance->y = MAPH + 3;


	string s = "mode con cols=" + to_string(CONW) + " lines=" + to_string(CONH);
	system(s.c_str());
}


//每次重试时调用此函数
void GameInit()
{
	//重置全局变量和
	ResetAll();
	InfoList::Instance->ResetAll();

	//清空画面并显示信息表和地图边框
	system("cls");
	InfoList::Instance->Init();
	RenderMap();

	GameEditor();//可能会打印多余语句，在操作完成后再清空一次屏幕

	system("cls");
	InfoList::Instance->Init();
}
//游戏编辑器
void GameEditor()
{
	//设置控制台前背景色
	system("color 70");

	//该函数将会在程序中询问读取存档
	RunSaveMode();

	//在此处输入自己的编辑器生成代码，以下为示例
	spawnPawnCircle(0, 0, 20, "兵");
	spawnPawnCircle(MAPW, MAPH, 20, "卒", 1);



}
void RunSaveMode()
{
	//请求输入存档号
	gotoxy(MAPW / 6, MAPH / 2 + 1);
	cout << "(其他数字视为不使用存档)";
	gotoxy(MAPW/6, MAPH / 2);
	cout << "请输入欲读取的存档 1~8 ：";
	
	//输入的数将用于调用下面的函数
	int input;
	cin >> input;
	ReadSaveSlot(input);
}
void ReadSaveSlot(int i)
{
	//该函数包含了八个风格迥异的预设的场景，可直接运行使用，也可当做示例来创建自己的场景
	// 
	//存档一.图形主题，测试函数用
	//该示例包含了所有的生成函数
	//1.生成单个Pawn
	//2.按线生成Pawn
	//3.按圆生成Pawn
	//4.创建一个生成器进行持续生成Pawn
	if (i == 1)
	{
		InfoList::Instance->LevelName = "图形主题";

		spawnPawnLine(1, 1, 1, 39, "■", 0);

		spawnPawnLine(10, 1, 10, 39, "▲", 1);

		spawnPawnLine(20, 1, 20, 39, "★", 2);

		spawnPawnCircle(39, 1, 10, "○", 3);

		spawnPawn(2, 2, "※", 4);

		spawnSpawner(38, 38, "圈", Pawn(0, 0, "●", 5), 2, 30);
	}
	//存档二.兵民骑三方混战
	else if (i == 2)
	{
		InfoList::Instance->LevelName = "兵民骑三方混战";

		spawnPawnCircle(1, 1, 15, "兵", 0, 150, 50, 30, 2);

		spawnPawnCircle(20, 20, 10, "民", 1, 50, 15, 15);

		spawnPawnLine(38, 1, 38, 39, "骑", 2, 250, 80, 50);
		spawnPawnLine(37, 1, 37, 39, "骑", 2, 250, 80, 50);
	}
	//存档三.生成器大战
	else if (i == 3)
	{
		InfoList::Instance->LevelName = "生成器大战";

		spawnSpawner(1, 1, "一", Pawn(0, 0, "■", 0), 1, 100);
		spawnPawnCircle(1, 1, 10, "■", 0);

		spawnSpawner(39, 1, "二", Pawn(0, 0, "●", 1), 1, 100);
		spawnPawnCircle(39, 1, 10, "●", 1);

		spawnSpawner(1, 39, "三", Pawn(0, 0, "★", 2), 1, 100);
		spawnPawnCircle(1, 39, 10, "★", 2);

		spawnSpawner(39, 39, "四", Pawn(0, 0, "▲", 3), 1, 100);
		spawnPawnCircle(39, 39, 10, "▲", 3);

		spawnSpawner(20, 20, "五", Pawn(0, 0, "※", 4), 1, 100);
		spawnPawnCircle(20, 20, 10, "※", 4);

		spawnSpawner(1, 20, "六", Pawn(0, 0, "☆", 5), 1, 150);
		spawnSpawner(20, 1, "七", Pawn(0, 0, "◇", 6), 1, 150);
		spawnSpawner(39, 20, "八", Pawn(0, 0, "○", 7), 1, 150);
		spawnSpawner(20, 39, "九", Pawn(0, 0, "▽", 8), 1, 150);
	}
	//存档四.生成器大混战
	else if (i == 4)
	{
		InfoList::Instance->LevelName = "生成器大混战";

		spawnSpawner(1, 1, "一", Pawn(0, 0, IconSelector(0), 0), 1, 100);

		spawnSpawner(39, 1, "二", Pawn(0, 0, IconSelector(1), 1), 1, 100);

		spawnSpawner(1, 39, "三", Pawn(0, 0, IconSelector(2), 2), 1, 100);

		spawnSpawner(39, 39, "四", Pawn(0, 0, IconSelector(3), 3), 1, 100);

		spawnSpawner(20, 20, "五", Pawn(0, 0, IconSelector(4), 4), 1, 100);

		spawnSpawner(1, 20, "六", Pawn(0, 0, IconSelector(5), 5), 1, 150);

		spawnSpawner(20, 1, "七", Pawn(0, 0, IconSelector(6), 6), 1, 150);

		spawnSpawner(39, 20, "八", Pawn(0, 0, IconSelector(7), 7), 1, 150);

		spawnSpawner(20, 39, "九", Pawn(0, 0, IconSelector(8), 8), 1, 150);

		spawnSpawner(10, 10, "十", Pawn(0, 0, IconSelector(9), 9), 1, 150);

		spawnSpawner(10, 30, "十一", Pawn(0, 0, IconSelector(10), 10), 1, 150);

		spawnSpawner(30, 10, "十二", Pawn(0, 0, IconSelector(11), 11), 1, 150);

		spawnSpawner(30, 30, "十三", Pawn(0, 0, IconSelector(12), 12), 1, 150);
	}
	//存档五.两方会战
	else if (i == 5)
	{
		InfoList::Instance->LevelName = "两方会战";

		for (int i = 1; i <= 39; i += 3)
		{
			spawnSpawner(1, i, "营", Pawn(0, 0, "兵", 0, 50), 1, 20);
		}

		for (int i = 1; i < 3; i++)
		{
			spawnPawnLine(i, 1, i, 39, "兵", 0, 50);
		}
		spawnPawnLine(4, 1, 4, 39, "马", 0, 250, 100, 50, 2);


		for (int i = 1; i <= 39; i += 3)
		{
			spawnSpawner(39, i, "帐", Pawn(0, 0, "卒", 1, 50), 1, 20);
		}

		for (int i = 39; i > 37; i--)
		{
			spawnPawnLine(i, 1, i, 39, "卒", 1, 50);
		}
		spawnPawnLine(36, 1, 36, 39, "骑", 1, 250, 100, 50, 2);
	}
	//存档六.丧尸狂潮
	else if (i == 6)
	{
		InfoList::Instance->LevelName = "丧尸狂潮";

		spawnPawnCircle(20, 20, 3, "人", 0, 100, 90, 5, 10);

		int num = 100;
		spawnSpawner(1, 1, "巢", Pawn(0, 0, "尸", 1), 1, num);
		spawnSpawner(39, 1, "巢", Pawn(0, 0, "尸", 1), 1, num);
		spawnSpawner(1, 39, "巢", Pawn(0, 0, "尸", 1), 1, num);
		spawnSpawner(39, 39, "巢", Pawn(0, 0, "尸", 1), 1, num);
		spawnSpawner(1, 20, "巢", Pawn(0, 0, "尸", 1), 1, num);
		spawnSpawner(20, 1, "巢", Pawn(0, 0, "尸", 1), 1, num);
		spawnSpawner(39, 20, "巢", Pawn(0, 0, "尸", 1), 1, num);
		spawnSpawner(20, 39, "巢", Pawn(0, 0, "尸", 1), 1, num);
	}
	//存档7.诛神之战
	else if (i == 7)
	{
		InfoList::Instance->LevelName = "诛神之战";

		spawnPawn(20, 5, "神", 0, 2000, 200, 100, 2);

		spawnPawnCircle(20, 1, 10, "仆", 0, 200, 50, 50);

		for (int i = 1; i < 39; i += 3)
		{
			spawnSpawner(i, 39, "营", Pawn(0, 0, "人", 1), 1, 35);
		}
		spawnPawnCircle(1, 39, 20, "人", 1);

		spawnPawnCircle(39, 39, 20, "人", 1);
	}
	//存档8.假三国无双
	else if (i == 8)
	{
		InfoList::Instance->LevelName = "假三国无双";

		spawnPawn(15, 5, "魏将", 0, 2000, 200, 100, 2);
		spawnPawn(25, 5, "蜀将", 1, 2000, 200, 100, 2);
		spawnPawn(20, 18, "吴将", 2, 2000, 200, 100, 2);

		spawnPawnCircle(1, 15, 15, "魏", 0);
		spawnPawnCircle(39, 15, 15, "蜀", 1);
		spawnPawnCircle(20, 30, 10, "吴", 2);
	}
	//都不是视为不使用存档，名称空置
	else
	{
		InfoList::Instance->LevelName = "----";
	}
}

//每帧接收输入
void Input()
{
	if (bAuto)
	{
		Sleep(AutoSpeed);//自动模式下延时0.5秒刷新一次
	}

	if (!bAuto || _kbhit())//接收输入,使用A键进行切换
	{
		int i = _getch();

		if (i == 'a' || i == 'A')
		{
			bAuto = !bAuto;
		}
		else if (i == 's' || i == 'S')
		{
			AutoSpeed = clamp(AutoSpeed - 100, 0, 400);
		}
		else if (i == 'd' || i == 'D')
		{
			AutoSpeed = clamp(AutoSpeed + 100, 0, 400);
		}
	}
}

//每帧逻辑更新
void Logic()
{
	RandomMoveList();//随机移动顺序表

	//将死亡缓存队列对象推入真正的死亡队列(这个操作让对象死亡延迟到第二帧结束，防止有的对象持有其无效引用)
	while (!Deads.empty())
	{
		FinalDeads.push(Deads.front());
		Deads.pop();
	}

	//执行所有生成器操作
	for (auto it : spawners)
	{
		it->Tick();
	}
	//进行生成器的删除与遍历操作
	for (auto it = spawners.begin(); it != spawners.end();)
	{
		if ((*it)->isValid)//检查是否有效
		{
			(*it)->Tick();
			it++;
		}
		else
		{
			World[(*it)->y * MAPW + (*it)->x] = NONE;

			gotoxy((*it)->x, (*it)->y);
			cout << "      ";

			it = spawners.erase(it);
		}
	}

	//执行所有的Pawn的Tick操作
	for (auto it : MoveList)
	{
		it->Tick();
	}

	//在所有的逻辑运算完成后，进行死亡Pawn的删除操作
	while (!FinalDeads.empty())
	{
		delete FinalDeads.front();
		FinalDeads.pop();
	}
	
	CheckEnd();
}
void CheckEnd()
{
	int count = 0;
	int ID, Team;
	for (int i = 0; i < InfoList::Instance->Camps.size(); i++)
	{
		if (InfoList::Instance->Camps[i]->AliveCount != 0)
		{
			count++;
			ID = i;
			Team = InfoList::Instance->Camps[i]->ID;
		}
	}

	if (count == 1)
	{
		for (int i = 0; i < spawners.size(); i++)
		{
			if (spawners[i]->TempPawn.Team != Team)
			{
				return;
			}
		}

		VictoryCampID = ID;

		Flag = 0;
	}
}

//每帧渲染
void Render()
{
	//进行所有Pawn的渲染操作
	for (int i = 0; i < pawns.size(); i++)
	{
		Pawn* p = pawns[i];
		gotoxy(p->x, p->y);
		cout << p->icon;
	}

	//进行所有Spawner的渲染操作
	for (int i = 0; i < spawners.size(); i++)
	{
		PawnSpawner* p = spawners[i];
		gotoxy(p->x, p->y);
		cout << p->icon;
	}

	RenderMap();//重新渲染地图边框
	RenderWorld();//渲染逻辑层，用于展示阻挡,辅助显示，一般不需要

	InfoList::Instance->displayInfo();//渲染日志信息
	InfoList::Instance->displayCamp();//渲染阵营信息

	//在地图右下角显示当前回合数
	gotoxy(MAPW + 3, MAPH);
	cout << "回合数：" << Rounds++;
	//在地图右下角显示当前模式
	cout << " 当前模式（按A切换）：" << (bAuto ? "自动模式" : "手动模式");
	gotoxy(MAPW + 3, MAPH + 1);
	cout << "当前时间间隔('S','D'键变速)：" << (float)AutoSpeed / 1000;
}
void RenderMap()
{
	for (int i = 0; i <= MAPH; i++)
	{
		for (int j = 0; j <= MAPW; j++)
		{
			gotoxy(j, i);
			if (i == 0 || j == 0 || i == MAPH || j == MAPW) cout << Wall;
		}
	}
}
void RenderWorld()
{
	int x = MAPW + 3;
	for (int h = 0; h < MAPH; h++)
	{
		for (int w = 0; w < MAPW; w++)
		{
			gotoxy(x + w, h);
			cout << (World[h * MAPW + w] ? to_string(World[h * MAPW + w]) : " ");
		}
	}
}

//游戏结束
void End()
{
	Camp* camp = InfoList::Instance->Camps[VictoryCampID];

	//计算全局信息
	int SpawnCount = 0;

	for (auto& it : InfoList::Instance->Camps)
	{
		SpawnCount += it->AliveCount + it->DeadCount;
	}

	//播报战局统计信息
	InfoList::Instance->addInfo("GM", "==================================================");
	InfoList::Instance->addInfo("GM", "一共死亡了 " + to_string(SpawnCount - camp->AliveCount) + " 个单位。");
	InfoList::Instance->addInfo("GM", "本次一共有 " + to_string(SpawnCount) + " 个单位参加。");

	//播报胜利信息
	InfoList::Instance->addInfo("GM", "==================================================");
	InfoList::Instance->addInfo("GM", "They K/D is " + to_string(camp->KD) + " !");
	InfoList::Instance->addInfo("GM", "They Lost " + to_string(camp->KillCount) + " Soldiers!");
	InfoList::Instance->addInfo("GM", "They Best Soldier Killed " + to_string(camp->BestPersonalKill) + " Enemies!");
	InfoList::Instance->addInfo("GM", "They Killed " + to_string(camp->KillCount) + " Enemies!");
	InfoList::Instance->addInfo("GM", "They Still Have " + to_string(camp->AliveCount) + " Alive!");
	InfoList::Instance->addInfo("GM", "Winner is " + to_string(camp->ID) + "：" + camp->icon);
	InfoList::Instance->addInfo("GM", "Game End! Now Rounds is " + to_string(Rounds));
	
	//系统提示
	InfoList::Instance->addInfo("System", "按下Q键退出！");

	Render();//刷新最后一帧

	//当且仅当按下Q键时退出
	int i = _getch();
	while (i != 'q' && i != 'Q')
	{
		i = _getch();
	}

	//清空画面并显示信息表和地图边框
	system("cls");
	InfoList::Instance->Init();
	RenderMap();

	gotoxy(MAPW / 6, MAPH / 2 - 1);
	cout << "Thanks For Play！:)" << endl;
}

int main()
{
	Init();//系统初始化

	int input = 1;
	while (input == 1)
	{
		GameInit();//游戏每次重试的初始化

		Render();//渲染第一帧

		while (Flag)
		{
			Input();//接收输入

			Logic();//逻辑运算

			Render();//渲染
		}

		End();//结算

		//输入选择是否终止
		gotoxy(MAPW / 6, MAPH / 2 + 1);
		cout << "是否重试？ 1 ：同意，2：拒绝  ：";
		cin >> input;
	}

	system("color 0F");
	return 0;
}