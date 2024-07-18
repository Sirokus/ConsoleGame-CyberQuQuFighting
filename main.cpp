#include <iostream>
#include <string>
#include <conio.h>

#include "Base.h"
#include "Pawn.h"
#include "InfoList.h"
using namespace std;

//����1391�����ҵĴ�����������

//�����ʼ��
void Init()
{
	srand(time(0));

	InfoList::Instance->x = 0;
	InfoList::Instance->y = MAPH + 3;


	string s = "mode con cols=" + to_string(CONW) + " lines=" + to_string(CONH);
	system(s.c_str());
}


//ÿ������ʱ���ô˺���
void GameInit()
{
	//����ȫ�ֱ�����
	ResetAll();
	InfoList::Instance->ResetAll();

	//��ջ��沢��ʾ��Ϣ��͵�ͼ�߿�
	system("cls");
	InfoList::Instance->Init();
	RenderMap();

	GameEditor();//���ܻ��ӡ������䣬�ڲ�����ɺ������һ����Ļ

	system("cls");
	InfoList::Instance->Init();
}
//��Ϸ�༭��
void GameEditor()
{
	//���ÿ���̨ǰ����ɫ
	system("color 70");

	//�ú��������ڳ�����ѯ�ʶ�ȡ�浵
	RunSaveMode();

	//�ڴ˴������Լ��ı༭�����ɴ��룬����Ϊʾ��
	spawnPawnCircle(0, 0, 20, "��");
	spawnPawnCircle(MAPW, MAPH, 20, "��", 1);



}
void RunSaveMode()
{
	//��������浵��
	gotoxy(MAPW / 6, MAPH / 2 + 1);
	cout << "(����������Ϊ��ʹ�ô浵)";
	gotoxy(MAPW/6, MAPH / 2);
	cout << "����������ȡ�Ĵ浵 1~8 ��";
	
	//������������ڵ�������ĺ���
	int input;
	cin >> input;
	ReadSaveSlot(input);
}
void ReadSaveSlot(int i)
{
	//�ú��������˰˸���������Ԥ��ĳ�������ֱ������ʹ�ã�Ҳ�ɵ���ʾ���������Լ��ĳ���
	// 
	//�浵һ.ͼ�����⣬���Ժ�����
	//��ʾ�����������е����ɺ���
	//1.���ɵ���Pawn
	//2.��������Pawn
	//3.��Բ����Pawn
	//4.����һ�����������г�������Pawn
	if (i == 1)
	{
		InfoList::Instance->LevelName = "ͼ������";

		spawnPawnLine(1, 1, 1, 39, "��", 0);

		spawnPawnLine(10, 1, 10, 39, "��", 1);

		spawnPawnLine(20, 1, 20, 39, "��", 2);

		spawnPawnCircle(39, 1, 10, "��", 3);

		spawnPawn(2, 2, "��", 4);

		spawnSpawner(38, 38, "Ȧ", Pawn(0, 0, "��", 5), 2, 30);
	}
	//�浵��.������������ս
	else if (i == 2)
	{
		InfoList::Instance->LevelName = "������������ս";

		spawnPawnCircle(1, 1, 15, "��", 0, 150, 50, 30, 2);

		spawnPawnCircle(20, 20, 10, "��", 1, 50, 15, 15);

		spawnPawnLine(38, 1, 38, 39, "��", 2, 250, 80, 50);
		spawnPawnLine(37, 1, 37, 39, "��", 2, 250, 80, 50);
	}
	//�浵��.��������ս
	else if (i == 3)
	{
		InfoList::Instance->LevelName = "��������ս";

		spawnSpawner(1, 1, "һ", Pawn(0, 0, "��", 0), 1, 100);
		spawnPawnCircle(1, 1, 10, "��", 0);

		spawnSpawner(39, 1, "��", Pawn(0, 0, "��", 1), 1, 100);
		spawnPawnCircle(39, 1, 10, "��", 1);

		spawnSpawner(1, 39, "��", Pawn(0, 0, "��", 2), 1, 100);
		spawnPawnCircle(1, 39, 10, "��", 2);

		spawnSpawner(39, 39, "��", Pawn(0, 0, "��", 3), 1, 100);
		spawnPawnCircle(39, 39, 10, "��", 3);

		spawnSpawner(20, 20, "��", Pawn(0, 0, "��", 4), 1, 100);
		spawnPawnCircle(20, 20, 10, "��", 4);

		spawnSpawner(1, 20, "��", Pawn(0, 0, "��", 5), 1, 150);
		spawnSpawner(20, 1, "��", Pawn(0, 0, "��", 6), 1, 150);
		spawnSpawner(39, 20, "��", Pawn(0, 0, "��", 7), 1, 150);
		spawnSpawner(20, 39, "��", Pawn(0, 0, "��", 8), 1, 150);
	}
	//�浵��.���������ս
	else if (i == 4)
	{
		InfoList::Instance->LevelName = "���������ս";

		spawnSpawner(1, 1, "һ", Pawn(0, 0, IconSelector(0), 0), 1, 100);

		spawnSpawner(39, 1, "��", Pawn(0, 0, IconSelector(1), 1), 1, 100);

		spawnSpawner(1, 39, "��", Pawn(0, 0, IconSelector(2), 2), 1, 100);

		spawnSpawner(39, 39, "��", Pawn(0, 0, IconSelector(3), 3), 1, 100);

		spawnSpawner(20, 20, "��", Pawn(0, 0, IconSelector(4), 4), 1, 100);

		spawnSpawner(1, 20, "��", Pawn(0, 0, IconSelector(5), 5), 1, 150);

		spawnSpawner(20, 1, "��", Pawn(0, 0, IconSelector(6), 6), 1, 150);

		spawnSpawner(39, 20, "��", Pawn(0, 0, IconSelector(7), 7), 1, 150);

		spawnSpawner(20, 39, "��", Pawn(0, 0, IconSelector(8), 8), 1, 150);

		spawnSpawner(10, 10, "ʮ", Pawn(0, 0, IconSelector(9), 9), 1, 150);

		spawnSpawner(10, 30, "ʮһ", Pawn(0, 0, IconSelector(10), 10), 1, 150);

		spawnSpawner(30, 10, "ʮ��", Pawn(0, 0, IconSelector(11), 11), 1, 150);

		spawnSpawner(30, 30, "ʮ��", Pawn(0, 0, IconSelector(12), 12), 1, 150);
	}
	//�浵��.������ս
	else if (i == 5)
	{
		InfoList::Instance->LevelName = "������ս";

		for (int i = 1; i <= 39; i += 3)
		{
			spawnSpawner(1, i, "Ӫ", Pawn(0, 0, "��", 0, 50), 1, 20);
		}

		for (int i = 1; i < 3; i++)
		{
			spawnPawnLine(i, 1, i, 39, "��", 0, 50);
		}
		spawnPawnLine(4, 1, 4, 39, "��", 0, 250, 100, 50, 2);


		for (int i = 1; i <= 39; i += 3)
		{
			spawnSpawner(39, i, "��", Pawn(0, 0, "��", 1, 50), 1, 20);
		}

		for (int i = 39; i > 37; i--)
		{
			spawnPawnLine(i, 1, i, 39, "��", 1, 50);
		}
		spawnPawnLine(36, 1, 36, 39, "��", 1, 250, 100, 50, 2);
	}
	//�浵��.ɥʬ��
	else if (i == 6)
	{
		InfoList::Instance->LevelName = "ɥʬ��";

		spawnPawnCircle(20, 20, 3, "��", 0, 100, 90, 5, 10);

		int num = 100;
		spawnSpawner(1, 1, "��", Pawn(0, 0, "ʬ", 1), 1, num);
		spawnSpawner(39, 1, "��", Pawn(0, 0, "ʬ", 1), 1, num);
		spawnSpawner(1, 39, "��", Pawn(0, 0, "ʬ", 1), 1, num);
		spawnSpawner(39, 39, "��", Pawn(0, 0, "ʬ", 1), 1, num);
		spawnSpawner(1, 20, "��", Pawn(0, 0, "ʬ", 1), 1, num);
		spawnSpawner(20, 1, "��", Pawn(0, 0, "ʬ", 1), 1, num);
		spawnSpawner(39, 20, "��", Pawn(0, 0, "ʬ", 1), 1, num);
		spawnSpawner(20, 39, "��", Pawn(0, 0, "ʬ", 1), 1, num);
	}
	//�浵7.����֮ս
	else if (i == 7)
	{
		InfoList::Instance->LevelName = "����֮ս";

		spawnPawn(20, 5, "��", 0, 2000, 200, 100, 2);

		spawnPawnCircle(20, 1, 10, "��", 0, 200, 50, 50);

		for (int i = 1; i < 39; i += 3)
		{
			spawnSpawner(i, 39, "Ӫ", Pawn(0, 0, "��", 1), 1, 35);
		}
		spawnPawnCircle(1, 39, 20, "��", 1);

		spawnPawnCircle(39, 39, 20, "��", 1);
	}
	//�浵8.��������˫
	else if (i == 8)
	{
		InfoList::Instance->LevelName = "��������˫";

		spawnPawn(15, 5, "κ��", 0, 2000, 200, 100, 2);
		spawnPawn(25, 5, "��", 1, 2000, 200, 100, 2);
		spawnPawn(20, 18, "�⽫", 2, 2000, 200, 100, 2);

		spawnPawnCircle(1, 15, 15, "κ", 0);
		spawnPawnCircle(39, 15, 15, "��", 1);
		spawnPawnCircle(20, 30, 10, "��", 2);
	}
	//��������Ϊ��ʹ�ô浵�����ƿ���
	else
	{
		InfoList::Instance->LevelName = "----";
	}
}

//ÿ֡��������
void Input()
{
	if (bAuto)
	{
		Sleep(AutoSpeed);//�Զ�ģʽ����ʱ0.5��ˢ��һ��
	}

	if (!bAuto || _kbhit())//��������,ʹ��A�������л�
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

//ÿ֡�߼�����
void Logic()
{
	RandomMoveList();//����ƶ�˳���

	//������������ж���������������������(��������ö��������ӳٵ��ڶ�֡��������ֹ�еĶ����������Ч����)
	while (!Deads.empty())
	{
		FinalDeads.push(Deads.front());
		Deads.pop();
	}

	//ִ����������������
	for (auto it : spawners)
	{
		it->Tick();
	}
	//������������ɾ�����������
	for (auto it = spawners.begin(); it != spawners.end();)
	{
		if ((*it)->isValid)//����Ƿ���Ч
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

	//ִ�����е�Pawn��Tick����
	for (auto it : MoveList)
	{
		it->Tick();
	}

	//�����е��߼�������ɺ󣬽�������Pawn��ɾ������
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

//ÿ֡��Ⱦ
void Render()
{
	//��������Pawn����Ⱦ����
	for (int i = 0; i < pawns.size(); i++)
	{
		Pawn* p = pawns[i];
		gotoxy(p->x, p->y);
		cout << p->icon;
	}

	//��������Spawner����Ⱦ����
	for (int i = 0; i < spawners.size(); i++)
	{
		PawnSpawner* p = spawners[i];
		gotoxy(p->x, p->y);
		cout << p->icon;
	}

	RenderMap();//������Ⱦ��ͼ�߿�
	RenderWorld();//��Ⱦ�߼��㣬����չʾ�赲,������ʾ��һ�㲻��Ҫ

	InfoList::Instance->displayInfo();//��Ⱦ��־��Ϣ
	InfoList::Instance->displayCamp();//��Ⱦ��Ӫ��Ϣ

	//�ڵ�ͼ���½���ʾ��ǰ�غ���
	gotoxy(MAPW + 3, MAPH);
	cout << "�غ�����" << Rounds++;
	//�ڵ�ͼ���½���ʾ��ǰģʽ
	cout << " ��ǰģʽ����A�л�����" << (bAuto ? "�Զ�ģʽ" : "�ֶ�ģʽ");
	gotoxy(MAPW + 3, MAPH + 1);
	cout << "��ǰʱ����('S','D'������)��" << (float)AutoSpeed / 1000;
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

//��Ϸ����
void End()
{
	Camp* camp = InfoList::Instance->Camps[VictoryCampID];

	//����ȫ����Ϣ
	int SpawnCount = 0;

	for (auto& it : InfoList::Instance->Camps)
	{
		SpawnCount += it->AliveCount + it->DeadCount;
	}

	//����ս��ͳ����Ϣ
	InfoList::Instance->addInfo("GM", "==================================================");
	InfoList::Instance->addInfo("GM", "һ�������� " + to_string(SpawnCount - camp->AliveCount) + " ����λ��");
	InfoList::Instance->addInfo("GM", "����һ���� " + to_string(SpawnCount) + " ����λ�μӡ�");

	//����ʤ����Ϣ
	InfoList::Instance->addInfo("GM", "==================================================");
	InfoList::Instance->addInfo("GM", "They K/D is " + to_string(camp->KD) + " !");
	InfoList::Instance->addInfo("GM", "They Lost " + to_string(camp->KillCount) + " Soldiers!");
	InfoList::Instance->addInfo("GM", "They Best Soldier Killed " + to_string(camp->BestPersonalKill) + " Enemies!");
	InfoList::Instance->addInfo("GM", "They Killed " + to_string(camp->KillCount) + " Enemies!");
	InfoList::Instance->addInfo("GM", "They Still Have " + to_string(camp->AliveCount) + " Alive!");
	InfoList::Instance->addInfo("GM", "Winner is " + to_string(camp->ID) + "��" + camp->icon);
	InfoList::Instance->addInfo("GM", "Game End! Now Rounds is " + to_string(Rounds));
	
	//ϵͳ��ʾ
	InfoList::Instance->addInfo("System", "����Q���˳���");

	Render();//ˢ�����һ֡

	//���ҽ�������Q��ʱ�˳�
	int i = _getch();
	while (i != 'q' && i != 'Q')
	{
		i = _getch();
	}

	//��ջ��沢��ʾ��Ϣ��͵�ͼ�߿�
	system("cls");
	InfoList::Instance->Init();
	RenderMap();

	gotoxy(MAPW / 6, MAPH / 2 - 1);
	cout << "Thanks For Play��:)" << endl;
}

int main()
{
	Init();//ϵͳ��ʼ��

	int input = 1;
	while (input == 1)
	{
		GameInit();//��Ϸÿ�����Եĳ�ʼ��

		Render();//��Ⱦ��һ֡

		while (Flag)
		{
			Input();//��������

			Logic();//�߼�����

			Render();//��Ⱦ
		}

		End();//����

		//����ѡ���Ƿ���ֹ
		gotoxy(MAPW / 6, MAPH / 2 + 1);
		cout << "�Ƿ����ԣ� 1 ��ͬ�⣬2���ܾ�  ��";
		cin >> input;
	}

	system("color 0F");
	return 0;
}