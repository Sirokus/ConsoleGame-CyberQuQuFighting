#include "Pawn.h"

void Pawn::FindTarget()//Ѱ��Ŀ��
{
	float distance = 9999;
	Pawn* temp = nullptr;
	for (auto it : MoveList)
	{
		if (it->Team != Team && getDistance(it) < distance)//Ҫ��Ϊͬһ���Ҿ������
		{
			distance = getDistance(it);
			temp = it;
		}
	}

	//��Ŀ������Ϊ��������Ŀ�꣬û��������Ϊ��ָ��
	Target = temp;
}

void Pawn::MoveToTarget()//��Ŀ���ƶ���һ������Χ�˷����ƶ�һ��
{
	if (!Target)return;

	int Tx = Target->x;
	int Ty = Target->y;
	int x = this->x;
	int y = this->y;

	if (Tx != x)
	{
		if (Tx > x) x++;
		else x--;
	}
	if (Ty != y)
	{
		if (Ty > y)y++;
		else y--;
	}

	if (!MoveTo(x, y))//����ֱ���ƶ��Ƿ�ɹ�
	{
		srand(time(0));

		int randX = rand() % 3 - 1;// -1 ~ 1
		int randY = rand() % 3 - 1;// -1 ~ 1

		MoveTo(this->x + randX, this->y + randY);//���ɹ����������Χ�˸������ƶ�
	}
}

bool Pawn::MoveTo(int x, int y)//�ƶ���ָ��λ��
{
	if (x <= 0 || y <= 0 || x >= MAPW || y >= MAPH || World[y * MAPW + x] != NONE)//����ƶ��Ƿ�Ϸ�
	{
		//���Ϸ����ۼӱ����赲������Ƿ���ڵ�������赲����
		//���ǣ��������赲������targetָ�룬�ȴ���һ������ѡ��
		if (++BlockedNum >= BlockMaxNum)
		{
			BlockedNum = 0;
			Target = nullptr;
		}

		//�ƶ����裬����־���л㱨
		InfoList::Instance->addInfo(icon, "Move Blocked!", Team);

		return false;
	}

	World[this->y * MAPW + this->x] = NONE;

	//�����������ڵ�ͼ���������ʾ����Ļ�ϵ���һ����icon����ֹ������β
	gotoxy(this->x, this->y);
	for (int i = 0; i < icon.size(); i++)
	{
		cout << " ";
	}
	
	this->x = x;
	this->y = y;

	World[this->y * MAPW + this->x] = PAWN;

	//�ɹ��ƶ�������־���л㱨
	InfoList::Instance->addInfo(icon, "Move To " + to_string(x) + " " + to_string(y), Team);

	return true;
}

float Pawn::getDistance(Pawn* Target)//��ȡ������Pawn�ľ���
{
	float distance = (x - Target->x) * (x - Target->x) + (y - Target->y) * (y - Target->y);
	distance = sqrt(distance);

	return distance;
}

bool Pawn::isTargetInRange()//�ж�Ŀ���Ƿ��ڹ�����Χ��
{
	return getDistance(Target) <= Range;
}

bool Pawn::Attack()
{
	if (!Target) return false;

	//ʹ���˺���ʽ�����˺�����������˺��빥������Ŀ����������
	//10�� �� ���� 28%
	//25�� �� ���� 50%
	//50�� �� ���� 66.6%
	//75�� �� ���� 75%
	int damage = ATK * (1 - (float)Target->DEF / (float)(Target->DEF + 25));

	Target->TakeDamage(damage);

	if (Target->isDead)//����˺�����������Ƿ�����
	{
		KillNum++;//ɱ�м�������һ

		//����Ӫ����ս��
		InfoList::Instance->UpdateCampKill(Team, KillNum);

		//����־���л㱨ս��
		InfoList::Instance->addInfo(icon, "Killed " + Target->icon, Team);

		Target = nullptr;//��Target������������Ϊ�ձ�ʾTarget��Ч���´�ѭ����Ѱ����Target
	}
	else
	{
		//����־���л㱨�˺����
		InfoList::Instance->addInfo(icon, "Attack " + Target->icon + " Damage = " + to_string(damage) + " ,Enemy Remain " + to_string(Target->HP) + " HP", Team);
	}

	return true;
}

void Pawn::TakeDamage(int delta)
{
	if (isDead)return;

	HP -= delta;
	HP = clamp(HP, 0, MaxHP);//��֤HP��0��MaxHP֮��

	if (HP <= 0) Dead();//��HPС�ڵ���0����������������������������
}

void Pawn::Dead()
{
	pawns.erase(remove(pawns.begin(), pawns.end(), this), pawns.end());//�������pawn������ȥ��

	isDead = true;//�����������־λ����ֹ���������ͬʱҲ�ɱ��Ա�Pawn���״̬����Ȥ�Ķ������

	World[this->y * MAPW + this->x] = NONE;//ȡ��������world�����е���ײռ�ã�ʹ����Pawn���ƶ�����λ��

	//�⼸�������ڵ�ͼ���������ʾ����Ļ�ϵ�����icon
	gotoxy(this->x, this->y);
	for (int i = 0; i < icon.size(); i++)
	{
		cout << " ";
	}

	Deads.push(this);//����������������У����ӳٵ�����Tick��ɺ�������

	//����־���б���
	InfoList::Instance->addInfo(icon, "Dead! KillNum = " + to_string(KillNum) +
		" AliveNum = " + to_string(AliveNum), Team);
	//����Ӫ����
	InfoList::Instance->UpdateCampDead(Team);
}

Pawn* spawnPawn(int x, int y, string icon, int Team /*= 0*/, int HP /*= 100*/, int ATK /*= 25*/, int DEF /*= 25*/, float Range /*= 1.5f*/)
{
	//λ��Խ������ѱ��赲�򲻲��������ؿ�ָ��
	if (x <= 0 || x >= MAPW || y <= 0 || y >= MAPH || World[y * MAPW + x] != NONE)return nullptr;

	//�����µ�Pawn����ʧ��Ҳ���ؿ�ָ��
	Pawn* p = new Pawn(x, y, icon, Team, HP, ATK, DEF, Range);
	if (!p) return nullptr;

	pawns.push_back(p);//���¶������ȫ������
	InfoList::Instance->addInfo(icon, "spawned!", Team);
	InfoList::Instance->addToCamp(p->Team, p->icon);//���¶�������Ӧ��Ӫ
	World[y * MAPW + x] = PAWN;//��Ӧλ�������赲

	return p;
}

void spawnPawnLine(int x1, int y1, int x2, int y2, string icon, int Team /*= 0*/, int HP /*= 100*/, int ATK /*= 25*/, int DEF /*= 25*/, float Range /*= 1.5f*/)
{
	spawnPawn(x1, y1, icon, Team, HP, ATK, DEF, Range);

	while (x1 != x2 || y1 != y2)
	{
		if (x1 != x2)
		{
			if (x1 > x2) x1--;
			else x1++;
		}
		if (y1 != y2)
		{
			if (y1 > y2) y1--;
			else y1++;
		}

		spawnPawn(x1, y1, icon, Team, HP, ATK, DEF, Range);
	}
}

void spawnPawnCircle(int x, int y, int radius, string icon, int Team /*= 0*/, int HP /*= 100*/, int ATK /*= 25*/, int DEF /*= 25*/, float Range /*= 1.5f*/)
{
	for (int i = -radius; i <= radius; i++)
	{
		for (int j = -radius; j <= radius; j++)
		{
			if (abs(j) + abs(i) <= radius)
				spawnPawn(x + i, y + j, icon, Team, HP, ATK, DEF, Range);
		}
	}
}

PawnSpawner* spawnSpawner(int x, int y, string icon, const Pawn& pawn, int MaxTimeDelay /*= 1*/, int MaxSpawnCount /*= -1*/)
{
	if (x <= 0 || x >= MAPW || y <= 0 || y >= MAPH || World[y * MAPW + x] != NONE)return nullptr;

	PawnSpawner* spawner = new PawnSpawner(x, y, icon, pawn, MaxTimeDelay, MaxSpawnCount);
	if (!spawner)return nullptr;

	spawners.push_back(spawner);//��������������
	World[y * MAPW + x] = OBJECT;//��Ӧλ�������赲

	return spawner;
}

