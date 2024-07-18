#pragma once
#include "Base.h"
#include <algorithm>
#include <iostream>
#include "InfoList.h"
using namespace std;

class Pawn
{
public:
	Pawn(int x, int y, string icon, int Team, int HP = 100, int ATK = 25, int DEF = 25, float Range = 1.5f) : x(x), y(y), icon(icon), Team(Team), HP(HP), ATK(ATK), DEF(DEF), Range(Range)
	{ 
		MaxHP = HP;//最大生命值
		AliveNum = 0;//存活回合数
		BlockMaxNum = 2;//最大寻路不成功次数(超过会切换目标)

		Target = nullptr;
		isDead = false;
		BlockedNum = 0;//当前寻路不成功次数
	}

	//每帧执行逻辑（简易行为）
	void Tick()
	{
		if (isDead) return;//已死亡则不执行操作

		AliveNum++;//存活回合自增

		//Target不存在或已死亡将寻找新的目标
		if (!Target || Target->isDead)
		{
			FindTarget();//寻找目标

			//向日志进行汇报
			if (Target)
			{
				InfoList::Instance->addInfo(icon, "Find Target is " + Target->icon, Team);
			}
			else
			{
				InfoList::Instance->addInfo(icon, "Target Not Find", Team);
			}
		}

		//检查目标是否可用
		if (Target && !Target->isDead)
		{
			//检查目标是否在范围内
			if (isTargetInRange())
			{
				Attack();//进攻函数
			}
			else
			{
				MoveToTarget();//向目标移动函数
			}
		}
	}

	//寻找行为
	void FindTarget();//寻找目标
	void MoveToTarget();//移动到目标
	bool MoveTo(int x, int y);//移动到位置，返回是否移动成功

	//攻击行为
	bool Attack();//攻击
	void TakeDamage(int delta);//收到伤害
	void Dead();//死亡

	//逻辑函数
	float getDistance(Pawn* Target);//获取到给定Pawn的距离
	bool isTargetInRange();//判断目标是否在攻击范围内

	//战斗相关
	int Team;//队伍标识
	Pawn* Target;//目标
	int HP, ATK, DEF;//血量，攻击力，防御力
	float Range;//攻击范围

	//属性
	int MaxHP;//最大生命值
	int AliveNum;//存活时长
	bool isDead;//是否存活
	int BlockMaxNum;//最大寻路不成功次数
	int BlockedNum;//若寻路遭遇阻拦超出指定次数则会重新选定目标

	//战斗记录
	int KillNum = 0;//杀敌数

	//渲染(控制台图形表示)
	int x, y;//坐标
	string icon;//外观
};

//Pawn生成相关函数
//单个生成Pawn
Pawn* spawnPawn(int x, int y, string icon, int Team = 0, int HP = 100, int ATK = 25, int DEF = 25, float Range = 1.5f);

//按线生成Pawn
void spawnPawnLine(int x1, int y1, int x2, int y2, string icon, int Team = 0, int HP = 100, int ATK = 25, int DEF = 25, float Range = 1.5f);

//按圆生成Pawn
void spawnPawnCircle(int x, int y, int radius, string icon, int Team = 0, int HP = 100, int ATK = 25, int DEF = 25, float Range = 1.5f);

//生成器对象
class PawnSpawner
{
public:
	PawnSpawner(int x, int y, string icon, const Pawn& pawn, int MaxTimeDelay = 1, int MaxSpawnCount = -1) :x(x), y(y), icon(icon), TempPawn(pawn), MaxTimeDelay(MaxTimeDelay), MaxSpawnCount(MaxSpawnCount)
	{
		TimeDelay = 0;
		SpawnCount = 0;

		isValid = true;
	}

	void Tick()
	{
		//若未激活则不执行操作
		if (!isValid)return;

		//先检查是否达到最大生成数，若最大为-1则为无限制
		if (MaxSpawnCount == -1 || SpawnCount < MaxSpawnCount)
		{
			//检查延时是否达到最大延时
			if (TimeDelay < MaxTimeDelay)
			{
				TimeDelay++;//没达到继续累计
			}
			else
			{
				TimeDelay = 0;//达到后重置延时

				for (int i = x - 1; i <= x + 1; i++)
				{
					for (int j = y - 1; j <= y + 1; j++)
					{
						//利用存储的模板Pawn生成一个Pawn
						Pawn* pawn = spawnPawn(i, j, TempPawn.icon, TempPawn.Team, TempPawn.HP, TempPawn.ATK, TempPawn.DEF, TempPawn.Range);

						//检查是否生成成功
						if (pawn)
						{
							//成功则累加计数器并退出循环
							SpawnCount++;
							return;
						}
					}
				}
			}
		}
		else if (SpawnCount >= MaxSpawnCount)
		{
			//达到最大生成数量时标记自身为不可用(待销毁)
			isValid = false;
		}
	}

	Pawn TempPawn;//模板Pawn，按照此Pawn进行生成

	bool isValid;//是否可用，不可用将会被销毁

	int MaxTimeDelay;//最大生成间隔时间
	int MaxSpawnCount;//最大生成数量，默认为-1，即为无限

	int TimeDelay;//当前间隔时间
	int SpawnCount;//当前生成数量

	int x, y;//生成器位置
	string icon;//生成器外观
};

//生成器相关函数
//生成生成器
PawnSpawner* spawnSpawner(int x, int y, string icon, const Pawn& pawn, int MaxTimeDelay = 1, int MaxSpawnCount = -1);











