#include "Pawn.h"

void Pawn::FindTarget()//寻找目标
{
	float distance = 9999;
	Pawn* temp = nullptr;
	for (auto it : MoveList)
	{
		if (it->Team != Team && getDistance(it) < distance)//要求不为同一组且距离最短
		{
			distance = getDistance(it);
			temp = it;
		}
	}

	//将目标设置为遍历到的目标，没遍历到则为空指针
	Target = temp;
}

void Pawn::MoveToTarget()//向目标移动（一次向周围八方向移动一格）
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

	if (!MoveTo(x, y))//尝试直接移动是否成功
	{
		srand(time(0));

		int randX = rand() % 3 - 1;// -1 ~ 1
		int randY = rand() % 3 - 1;// -1 ~ 1

		MoveTo(this->x + randX, this->y + randY);//不成功则随机向周围八个方向移动
	}
}

bool Pawn::MoveTo(int x, int y)//移动到指定位置
{
	if (x <= 0 || y <= 0 || x >= MAPW || y >= MAPH || World[y * MAPW + x] != NONE)//检查移动是否合法
	{
		//不合法将累加本次阻挡并检查是否大于等于最大阻挡次数
		//若是，则重置阻挡次数与target指针，等待下一次重新选择
		if (++BlockedNum >= BlockMaxNum)
		{
			BlockedNum = 0;
			Target = nullptr;
		}

		//移动受阻，向日志进行汇报
		InfoList::Instance->addInfo(icon, "Move Blocked!", Team);

		return false;
	}

	World[this->y * MAPW + this->x] = NONE;

	//这两行用于在地图上清除已显示在屏幕上的上一步的icon，防止产生拖尾
	gotoxy(this->x, this->y);
	for (int i = 0; i < icon.size(); i++)
	{
		cout << " ";
	}
	
	this->x = x;
	this->y = y;

	World[this->y * MAPW + this->x] = PAWN;

	//成功移动，向日志进行汇报
	InfoList::Instance->addInfo(icon, "Move To " + to_string(x) + " " + to_string(y), Team);

	return true;
}

float Pawn::getDistance(Pawn* Target)//获取到给定Pawn的距离
{
	float distance = (x - Target->x) * (x - Target->x) + (y - Target->y) * (y - Target->y);
	distance = sqrt(distance);

	return distance;
}

bool Pawn::isTargetInRange()//判断目标是否在攻击范围内
{
	return getDistance(Target) <= Range;
}

bool Pawn::Attack()
{
	if (!Target) return false;

	//使用伤害公式计算伤害，最终造成伤害与攻击力与目标防御力相关
	//10防 ： 减伤 28%
	//25防 ： 减伤 50%
	//50防 ： 减伤 66.6%
	//75防 ： 减伤 75%
	int damage = ATK * (1 - (float)Target->DEF / (float)(Target->DEF + 25));

	Target->TakeDamage(damage);

	if (Target->isDead)//造成伤害后立即检查是否死亡
	{
		KillNum++;//杀敌计数器加一

		//向阵营报告战绩
		InfoList::Instance->UpdateCampKill(Team, KillNum);

		//向日志进行汇报战绩
		InfoList::Instance->addInfo(icon, "Killed " + Target->icon, Team);

		Target = nullptr;//该Target已死亡则设置为空表示Target无效，下次循环会寻找新Target
	}
	else
	{
		//向日志进行汇报伤害情况
		InfoList::Instance->addInfo(icon, "Attack " + Target->icon + " Damage = " + to_string(damage) + " ,Enemy Remain " + to_string(Target->HP) + " HP", Team);
	}

	return true;
}

void Pawn::TakeDamage(int delta)
{
	if (isDead)return;

	HP -= delta;
	HP = clamp(HP, 0, MaxHP);//保证HP在0到MaxHP之间

	if (HP <= 0) Dead();//若HP小于等于0，调用死亡函数，进行死亡处理
}

void Pawn::Dead()
{
	pawns.erase(remove(pawns.begin(), pawns.end(), this), pawns.end());//将自身从pawn数组中去除

	isDead = true;//设置自身存活标志位，防止多余操作，同时也可被对本Pawn存活状态感兴趣的对象调用

	World[this->y * MAPW + this->x] = NONE;//取消自身在world数组中的碰撞占用，使其他Pawn可移动到本位置

	//这几行用于在地图上清除已显示在屏幕上的自身icon
	gotoxy(this->x, this->y);
	for (int i = 0; i < icon.size(); i++)
	{
		cout << " ";
	}

	Deads.push(this);//将自身加入死亡队列，即延迟到所有Tick完成后再销毁

	//向日志进行报告
	InfoList::Instance->addInfo(icon, "Dead! KillNum = " + to_string(KillNum) +
		" AliveNum = " + to_string(AliveNum), Team);
	//向阵营报告
	InfoList::Instance->UpdateCampDead(Team);
}

Pawn* spawnPawn(int x, int y, string icon, int Team /*= 0*/, int HP /*= 100*/, int ATK /*= 25*/, int DEF /*= 25*/, float Range /*= 1.5f*/)
{
	//位置越界或者已被阻挡则不操作，返回空指针
	if (x <= 0 || x >= MAPW || y <= 0 || y >= MAPH || World[y * MAPW + x] != NONE)return nullptr;

	//创建新的Pawn对象，失败也返回空指针
	Pawn* p = new Pawn(x, y, icon, Team, HP, ATK, DEF, Range);
	if (!p) return nullptr;

	pawns.push_back(p);//将新对象加入全局数组
	InfoList::Instance->addInfo(icon, "spawned!", Team);
	InfoList::Instance->addToCamp(p->Team, p->icon);//将新对象加入对应阵营
	World[y * MAPW + x] = PAWN;//对应位置设置阻挡

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

	spawners.push_back(spawner);//加入生成器数组
	World[y * MAPW + x] = OBJECT;//对应位置设置阻挡

	return spawner;
}

