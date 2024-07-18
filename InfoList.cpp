#include "InfoList.h"
#include <iomanip>

InfoList* InfoList::Instance = new InfoList;

void InfoList::Init()
{
	gotoxy(x, y - 2);
	cout << " ID Team Icon	 LEVEL NAME : " << LevelName << endl;
	cout << "---------------";

	int x = this->x + MaxWidth / 2 + 2;
	int y = this->y;

	gotoxy(x, y);
	cout << "Camp ID";
	y++;
	gotoxy(x, y);
	cout << "--------------------";
	y++;
	gotoxy(x, y);
	cout << "KillCount";
	y++;
	gotoxy(x, y);
	cout << "BestPersonalKill";
	y++;
	gotoxy(x, y);
	cout << "--------------------";
	y++;
	gotoxy(x, y);
	cout << "AliveCount";
	y++;
	gotoxy(x, y);
	cout << "DeadCount";
	y++;
	gotoxy(x, y);
	cout << "--------------------";
	y++;
	gotoxy(x, y);
	cout << "K/D";
}

void InfoList::addInfo(string Id, string Info, int Team)
{
	string info = "��" + to_string(count++) + "��" + (Team == -1 ? "" : to_string(Team)) + "  " + Id + " : " + Info;

	int len = info.size();
	if (len > MaxWidth)
		info = info.substr(0, MaxWidth);
	
	Infos.push_back(info);
}

void InfoList::displayInfo()
{
	gotoxy(x, y);
	int num = 0;//������
	for (int i = Infos.size() - 1; i >= 0 && num < MaxLength; i--)
	{
		cout << Infos[i];

		for (int j = Infos[i].size(); j < MaxWidth; j++) cout << " ";
		cout << "|" << endl;

		num++;
	}

	if (Infos.size() > 25)
	{
		Infos.erase(Infos.begin(), Infos.end() - MaxLength);
	}
}

void InfoList::addToCamp(int id, string icon)
{
	//����Ƿ���ڴ�id��Camp
	for (auto& it : Camps)
	{
		if (it->ID == id)
		{
			it->AliveCount++;

			return;
		}
	}

	//���������½�һ��
	Camp* camp = new Camp;
	camp->ID = id;
	camp->icon = icon;
	camp->KillCount = 0;
	camp->AliveCount = 1;
	camp->DeadCount = 0;
	camp->BestPersonalKill = 0;
	camp->KD = 1;

	Camps.push_back(camp);
}

void InfoList::UpdateCampKill(int id,int PawnKillCount)
{
	for (auto& it : Camps)
	{
		if (it->ID == id)//Ѱ�Ҷ�Ӧ��Ӫ
		{
			it->KillCount++;//ɱ������һ

			//�������ɱ����������Ӫ��Ѹ���ɱ����������֮
			if (PawnKillCount > it->BestPersonalKill)
			{
				it->BestPersonalKill = PawnKillCount;
			}

			UpdateCampKD(id);

			return;
		}
	}
}

void InfoList::UpdateCampDead(int id)
{
	for (auto& it : Camps)
	{
		if (it->ID == id)//Ѱ�Ҷ�Ӧ��Ӫ
		{
			it->AliveCount--;

			it->DeadCount++;

			UpdateCampKD(id);

			return;
		}
	}
}

void InfoList::UpdateCampKD(int id)
{
	for (auto& it : Camps)
	{
		if (it->ID == id)//Ѱ�Ҷ�Ӧ��Ӫ
		{
			float k = it->KillCount ? it->KillCount : 1;
			float d = it->DeadCount ? it->DeadCount : 1;

			it->KD = k / d;
		}
	}
}

//�����ڸ�ʽ����ʾCamp��ֵ
//�������ذ汾�����������ʽ�ı仯��int�汾���������float�汾�̶���ʾС�����һλ
void disCampNumXY(int x, int y, int num)
{
	gotoxy(x, y);
	cout << "      ";
	gotoxy(x, y);
	cout << "| ";
	cout << (num > 9999 ? 9999 : num);//��ֹ��ʾ���ִ�����λ�����
}
void disCampNumXY(int x, int y, float num)
{
	gotoxy(x, y);
	cout << "        ";
	gotoxy(x, y);
	cout << "| ";
	cout << fixed << setprecision(1) << (num > 9999 ? 9999 : num);//��ֹ��ʾ���ִ�����λ�����
}
void InfoList::displayCamp()
{
	//������������FirstX��FirstY�������¼ÿ�еĵ�һ���е�λ��
	int Fx = this->x + MaxWidth / 2 + 12;
	int Fy = this->y;
	int num = 0;//ѭ�������м�¼��ǰ�е�������

	for (int i = 0; i < Camps.size();)
	{
		//�����н�������ѭ�����ڵı���x��y���г����޸�
		int x = Fx + num * 4;
		int y = Fy;
		num++;

		//���Խ������õ���һ��
		if (x * 2 + 8 > CONW)
		{
			Fx = this->x + MaxWidth / 2 + 2;
			Fy += 10;
			num = 0;

			continue;
		}


		disCampNumXY(x, y, Camps[i]->ID);
		cout << " " << Camps[i]->icon;

		y++;
		gotoxy(x, y);
		cout << "--------";

		y++;
		disCampNumXY(x, y, Camps[i]->KillCount);

		y++;
		disCampNumXY(x, y, Camps[i]->BestPersonalKill);

		y++;
		gotoxy(x, y);
		cout << "--------";

		y++;
		disCampNumXY(x, y, Camps[i]->AliveCount);

		y++;
		disCampNumXY(x, y, Camps[i]->DeadCount);

		y++;
		gotoxy(x, y);
		cout << "--------";

		y++;
		disCampNumXY(x, y, Camps[i]->KD);

		i++;
	}
}

void InfoList::ResetAll()
{
	count = 0;
	Infos.clear();
	Camps.clear();
	LevelName = "----";
}
