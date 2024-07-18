#pragma once
#include <iostream>
#include <vector>
#include "Base.h"
#include <string>
using namespace std;

//阵营结构，用于记录同阵营信息，在生成Pawn时根据Team的值自动创建或加入
struct Camp
{
	int ID;//阵营编号
	string icon;//阵营图标

	int KillCount;//阵营杀敌统计
	int BestPersonalKill;//最佳个人杀敌

	int AliveCount;//阵营存活人数统计
	int DeadCount;//阵营死亡人数统计

	float KD;//阵营KD比
};

class InfoList
{
public:
	void Init();

	//消息队列操作
	void addInfo(string Id, string Info, int Team = -1);//添加消息，最后的队伍表示可以忽略，默认值-1即代表不会显示
	void displayInfo();//显示消息

	//阵营队列操作
	void addToCamp(int id, string icon);//添加到阵营，输入谁要进入阵营以及阵营id
	void UpdateCampKill(int id,int PawnKillCount);//杀敌调用本函数
	void UpdateCampDead(int id);//死亡调用本函数
	void UpdateCampKD(int id);//更新阵营KD信息
	void displayCamp();//显示阵营信息

	void ResetAll();//初始化

	static InfoList* Instance;//单例
	vector<string> Infos;//日志消息队列
	vector<Camp*> Camps;//阵营队列

	int x, y;//坐标信息
	string LevelName;
	long long count;//总消息数量
	int MaxLength = 25;//最大显示数量（不限制最大存储数量）
	int MaxWidth = (MAPW * 2 > 50 ? MAPW * 2 : 50);
private:
	InfoList() { count = 0; }
};



