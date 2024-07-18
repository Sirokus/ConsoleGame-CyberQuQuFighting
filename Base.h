#pragma once
#include <vector>
#include <string>
#include <queue>
#include <Windows.h>
#include <time.h>
using namespace std;

//地图大小(实际可生成对象的范围要小上一圈）
//比如在此定义40*40的地图，实际可用坐标为 x： 1~39  y： 1~39
#define MAPW 40
#define MAPH 40

//控制台窗口大小
#define CONW MAPW * 4 + 10
#define CONH MAPH * 2 + 10

//游戏运行标志
extern bool Flag;
//运行回合数
extern int Rounds;
//自动运行标志
extern bool bAuto;
//胜利阵营的数组下标
extern int VictoryCampID;
//自动运行速度，以毫秒记，1000 ms = 1s
extern int AutoSpeed;

//地图内物体种类
enum Object
{
	NONE,
	OBJECT,
	PAWN
};
extern int World[MAPW * MAPH];//地图数组，用于检测单位是否重叠
extern string Wall;//墙的外观字符



class Pawn;//可移动单位的前向声明
extern vector<Pawn*> pawns;//Pawn的实体数组
extern vector<Pawn*> MoveList;//Pawn的移动顺序数组

extern queue<Pawn*> Deads;//Pawn的预备死亡队列(缓存，进入此数组时即代表单位已不可用，在保证后续持有死亡单位的引用的单位都变换了目标后才会转入真死亡队列)
extern queue<Pawn*> FinalDeads;//Pawn的真正の死亡队列

class PawnSpawner;//生成器的前向声明（生成器是可以持续生成Pawn的单位）
extern vector<PawnSpawner*> spawners;//生成器的实体数组



//工具函数
void gotoxy(int x, int y);//控制台光标移动到（x,y）处
void RandomMoveList();//随机打乱角色移动顺序表
string IconSelector(int i);//按ID返回预设的Icon
void ResetAll();//负责重新开始游戏时初始化全局变量



//主函数的函数在此处声明
void Init();//初始化

void GameInit();//游戏初始化（每次重试时的初始化）
void GameEditor();//游戏编辑器，物体的生成等在此函数内执行
void RunSaveMode();//负责在屏幕上打印提示玩家输入存档进行读取
void ReadSaveSlot(int i);//实际进行读取操作的函数

void Input();//每帧处理玩家输入

void Logic();//每帧更新逻辑
void CheckEnd();//检查是否达到胜利条件

void Render();//每帧更新画面
void RenderMap();//绘制地图边框
void RenderWorld();//绘制右边的逻辑阻挡层

void End();//结束时调用的函数