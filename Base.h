#pragma once
#include <vector>
#include <string>
#include <queue>
#include <Windows.h>
#include <time.h>
using namespace std;

//��ͼ��С(ʵ�ʿ����ɶ���ķ�ΧҪС��һȦ��
//�����ڴ˶���40*40�ĵ�ͼ��ʵ�ʿ�������Ϊ x�� 1~39  y�� 1~39
#define MAPW 40
#define MAPH 40

//����̨���ڴ�С
#define CONW MAPW * 4 + 10
#define CONH MAPH * 2 + 10

//��Ϸ���б�־
extern bool Flag;
//���лغ���
extern int Rounds;
//�Զ����б�־
extern bool bAuto;
//ʤ����Ӫ�������±�
extern int VictoryCampID;
//�Զ������ٶȣ��Ժ���ǣ�1000 ms = 1s
extern int AutoSpeed;

//��ͼ����������
enum Object
{
	NONE,
	OBJECT,
	PAWN
};
extern int World[MAPW * MAPH];//��ͼ���飬���ڼ�ⵥλ�Ƿ��ص�
extern string Wall;//ǽ������ַ�



class Pawn;//���ƶ���λ��ǰ������
extern vector<Pawn*> pawns;//Pawn��ʵ������
extern vector<Pawn*> MoveList;//Pawn���ƶ�˳������

extern queue<Pawn*> Deads;//Pawn��Ԥ����������(���棬���������ʱ������λ�Ѳ����ã��ڱ�֤��������������λ�����õĵ�λ���任��Ŀ���Ż�ת������������)
extern queue<Pawn*> FinalDeads;//Pawn����������������

class PawnSpawner;//��������ǰ���������������ǿ��Գ�������Pawn�ĵ�λ��
extern vector<PawnSpawner*> spawners;//��������ʵ������



//���ߺ���
void gotoxy(int x, int y);//����̨����ƶ�����x,y����
void RandomMoveList();//������ҽ�ɫ�ƶ�˳���
string IconSelector(int i);//��ID����Ԥ���Icon
void ResetAll();//�������¿�ʼ��Ϸʱ��ʼ��ȫ�ֱ���



//�������ĺ����ڴ˴�����
void Init();//��ʼ��

void GameInit();//��Ϸ��ʼ����ÿ������ʱ�ĳ�ʼ����
void GameEditor();//��Ϸ�༭������������ɵ��ڴ˺�����ִ��
void RunSaveMode();//��������Ļ�ϴ�ӡ��ʾ�������浵���ж�ȡ
void ReadSaveSlot(int i);//ʵ�ʽ��ж�ȡ�����ĺ���

void Input();//ÿ֡�����������

void Logic();//ÿ֡�����߼�
void CheckEnd();//����Ƿ�ﵽʤ������

void Render();//ÿ֡���»���
void RenderMap();//���Ƶ�ͼ�߿�
void RenderWorld();//�����ұߵ��߼��赲��

void End();//����ʱ���õĺ���