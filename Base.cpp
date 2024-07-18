#include "Base.h"

//游戏运行标志
bool Flag = 1;
//运行回合数
int Rounds = 0;
//自动运行标志
bool bAuto = false;
//胜利阵营的数组下标
int VictoryCampID = -1;
//自动运行速度，以毫秒记，1000 ms = 1s
int AutoSpeed = 200;

int World[MAPW * MAPH] = { NONE };
string Wall = "@@";

vector<Pawn*> pawns;
vector<Pawn*> MoveList;
queue<Pawn*> Deads;
queue<Pawn*> FinalDeads;
vector<PawnSpawner*> spawners;

void gotoxy(int x, int y)
{
	if (x<0 || y<0 || x>CONW || y>CONH) return;//若输入的x,y超出范围则不执行

	COORD coord;
	coord.X = x * 2;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void RandomMoveList()
{
	vector<Pawn*> pawn(pawns);//复制一份pawns
	MoveList.clear();//初始化顺序表

	//将复制的vector数组中的元素逐个随机获取并插入到MoveList，然后弹出
	srand(time(0));
	for (int i = pawn.size(); i > 0; i--)
	{
		int id = rand() % i;
		MoveList.push_back(pawn[id]);
		pawn.erase(pawn.begin() + id);
	}
}

std::string IconSelector(int i)
{
	switch (i)
	{
	case 0:
		return "▲";
	case 1:
		return "▼";
	case 2:
		return "●";
	case 3:
		return "◆";
	case 4:
		return "■";
	case 5:
		return "★";
	case 6:
		return "◎";
	case 7:
		return "@";
	case 8:
		return "△";
	case 9:
		return "▽";
	case 10:
		return "○";
	case 11:
		return "◇";
	case 12:
		return "□";
	case 13:
		return "☆";
	case 14:
		return "¤";
	case 15:
		return "×";
	case 16:
		return "+";
	case 17:
		return "//";
	case 18:
		return "*";
	case 19:
		return "=";
	default:
		return "DE";
	}
}

void ResetAll()
{
	//将角色数组存储的指针指向的空间全部释放，再清空数组
	for (auto it : pawns)
	{
		delete it;
	}
	pawns.clear();

	//先将Deads（死亡缓存队列）的元素推入FinalDeads死亡队列，再执行删除
	while (!Deads.empty())
	{
		FinalDeads.push(Deads.front());
		Deads.pop();
	}
	while (!FinalDeads.empty())
	{
		delete FinalDeads.front();
		FinalDeads.pop();
	}

	//和pawns数组一样的方式清理生成器
	for (auto it : spawners)
	{
		delete it;
	}
	spawners.clear();

	//重置用于检测单位重叠的世界数组
	for (int i = 0; i < MAPW * MAPH; i++)
	{
		World[i] = NONE;
	}

	//重置所有全局变量
	Flag = 1;
	Rounds = 0;
	bAuto = false;
	VictoryCampID = -1;
	AutoSpeed = 200;
}

