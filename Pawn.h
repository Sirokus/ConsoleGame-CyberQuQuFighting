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
		MaxHP = HP;//�������ֵ
		AliveNum = 0;//���غ���
		BlockMaxNum = 2;//���Ѱ·���ɹ�����(�������л�Ŀ��)

		Target = nullptr;
		isDead = false;
		BlockedNum = 0;//��ǰѰ·���ɹ�����
	}

	//ÿִ֡���߼���������Ϊ��
	void Tick()
	{
		if (isDead) return;//��������ִ�в���

		AliveNum++;//���غ�����

		//Target�����ڻ���������Ѱ���µ�Ŀ��
		if (!Target || Target->isDead)
		{
			FindTarget();//Ѱ��Ŀ��

			//����־���л㱨
			if (Target)
			{
				InfoList::Instance->addInfo(icon, "Find Target is " + Target->icon, Team);
			}
			else
			{
				InfoList::Instance->addInfo(icon, "Target Not Find", Team);
			}
		}

		//���Ŀ���Ƿ����
		if (Target && !Target->isDead)
		{
			//���Ŀ���Ƿ��ڷ�Χ��
			if (isTargetInRange())
			{
				Attack();//��������
			}
			else
			{
				MoveToTarget();//��Ŀ���ƶ�����
			}
		}
	}

	//Ѱ����Ϊ
	void FindTarget();//Ѱ��Ŀ��
	void MoveToTarget();//�ƶ���Ŀ��
	bool MoveTo(int x, int y);//�ƶ���λ�ã������Ƿ��ƶ��ɹ�

	//������Ϊ
	bool Attack();//����
	void TakeDamage(int delta);//�յ��˺�
	void Dead();//����

	//�߼�����
	float getDistance(Pawn* Target);//��ȡ������Pawn�ľ���
	bool isTargetInRange();//�ж�Ŀ���Ƿ��ڹ�����Χ��

	//ս�����
	int Team;//�����ʶ
	Pawn* Target;//Ŀ��
	int HP, ATK, DEF;//Ѫ������������������
	float Range;//������Χ

	//����
	int MaxHP;//�������ֵ
	int AliveNum;//���ʱ��
	bool isDead;//�Ƿ���
	int BlockMaxNum;//���Ѱ·���ɹ�����
	int BlockedNum;//��Ѱ·������������ָ�������������ѡ��Ŀ��

	//ս����¼
	int KillNum = 0;//ɱ����

	//��Ⱦ(����̨ͼ�α�ʾ)
	int x, y;//����
	string icon;//���
};

//Pawn������غ���
//��������Pawn
Pawn* spawnPawn(int x, int y, string icon, int Team = 0, int HP = 100, int ATK = 25, int DEF = 25, float Range = 1.5f);

//��������Pawn
void spawnPawnLine(int x1, int y1, int x2, int y2, string icon, int Team = 0, int HP = 100, int ATK = 25, int DEF = 25, float Range = 1.5f);

//��Բ����Pawn
void spawnPawnCircle(int x, int y, int radius, string icon, int Team = 0, int HP = 100, int ATK = 25, int DEF = 25, float Range = 1.5f);

//����������
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
		//��δ������ִ�в���
		if (!isValid)return;

		//�ȼ���Ƿ�ﵽ����������������Ϊ-1��Ϊ������
		if (MaxSpawnCount == -1 || SpawnCount < MaxSpawnCount)
		{
			//�����ʱ�Ƿ�ﵽ�����ʱ
			if (TimeDelay < MaxTimeDelay)
			{
				TimeDelay++;//û�ﵽ�����ۼ�
			}
			else
			{
				TimeDelay = 0;//�ﵽ��������ʱ

				for (int i = x - 1; i <= x + 1; i++)
				{
					for (int j = y - 1; j <= y + 1; j++)
					{
						//���ô洢��ģ��Pawn����һ��Pawn
						Pawn* pawn = spawnPawn(i, j, TempPawn.icon, TempPawn.Team, TempPawn.HP, TempPawn.ATK, TempPawn.DEF, TempPawn.Range);

						//����Ƿ����ɳɹ�
						if (pawn)
						{
							//�ɹ����ۼӼ��������˳�ѭ��
							SpawnCount++;
							return;
						}
					}
				}
			}
		}
		else if (SpawnCount >= MaxSpawnCount)
		{
			//�ﵽ�����������ʱ�������Ϊ������(������)
			isValid = false;
		}
	}

	Pawn TempPawn;//ģ��Pawn�����մ�Pawn��������

	bool isValid;//�Ƿ���ã������ý��ᱻ����

	int MaxTimeDelay;//������ɼ��ʱ��
	int MaxSpawnCount;//�������������Ĭ��Ϊ-1����Ϊ����

	int TimeDelay;//��ǰ���ʱ��
	int SpawnCount;//��ǰ��������

	int x, y;//������λ��
	string icon;//���������
};

//��������غ���
//����������
PawnSpawner* spawnSpawner(int x, int y, string icon, const Pawn& pawn, int MaxTimeDelay = 1, int MaxSpawnCount = -1);











