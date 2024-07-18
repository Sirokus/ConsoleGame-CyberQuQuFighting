#pragma once
#include <iostream>
#include <vector>
#include "Base.h"
#include <string>
using namespace std;

//��Ӫ�ṹ�����ڼ�¼ͬ��Ӫ��Ϣ��������Pawnʱ����Team��ֵ�Զ����������
struct Camp
{
	int ID;//��Ӫ���
	string icon;//��Ӫͼ��

	int KillCount;//��Ӫɱ��ͳ��
	int BestPersonalKill;//��Ѹ���ɱ��

	int AliveCount;//��Ӫ�������ͳ��
	int DeadCount;//��Ӫ��������ͳ��

	float KD;//��ӪKD��
};

class InfoList
{
public:
	void Init();

	//��Ϣ���в���
	void addInfo(string Id, string Info, int Team = -1);//�����Ϣ�����Ķ����ʾ���Ժ��ԣ�Ĭ��ֵ-1����������ʾ
	void displayInfo();//��ʾ��Ϣ

	//��Ӫ���в���
	void addToCamp(int id, string icon);//��ӵ���Ӫ������˭Ҫ������Ӫ�Լ���Ӫid
	void UpdateCampKill(int id,int PawnKillCount);//ɱ�е��ñ�����
	void UpdateCampDead(int id);//�������ñ�����
	void UpdateCampKD(int id);//������ӪKD��Ϣ
	void displayCamp();//��ʾ��Ӫ��Ϣ

	void ResetAll();//��ʼ��

	static InfoList* Instance;//����
	vector<string> Infos;//��־��Ϣ����
	vector<Camp*> Camps;//��Ӫ����

	int x, y;//������Ϣ
	string LevelName;
	long long count;//����Ϣ����
	int MaxLength = 25;//�����ʾ���������������洢������
	int MaxWidth = (MAPW * 2 > 50 ? MAPW * 2 : 50);
private:
	InfoList() { count = 0; }
};



