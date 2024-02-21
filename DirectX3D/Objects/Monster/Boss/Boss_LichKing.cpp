#include "Framework.h"
#include "Boss_LichKing.h"

Boss_LichKing::Boss_LichKing() : ModelAnimator("LichKing")
{
	ReadClip("Walking");
	ReadClip("Attack_1");
	ReadClip("Idle");
	ReadClip("Hit");
	ReadClip("Die");
	ReadClip("Casting");

	Scale() *= 0.015f;
	ModelAnimator::Update();

	myCollider = new SphereCollider();
	myCollider->SetParent(this);
	myCollider->Scale() *= 150.5f;
	myCollider->Pos().y += 100;
	myCollider->UpdateWorld();
	
	atk_serch = new SphereCollider();
	atk_serch->SetParent(this);
	atk_serch->Scale() *= 1200;
	atk_serch->UpdateWorld();

	mainHand = new Transform();

	Frost = new Model("Frostmourne");
	Frost->SetParent(mainHand);
	Frost->Scale() *= 100.5f;
	Frost_Collider = new SphereCollider();
	Frost_Collider->SetParent(Frost);
	Frost_Collider->Scale() *= 0.5f;
	Frost_Collider->Pos() = Vector3(1);
	Frost_Collider->SetActive(false);

	{
		GetClip((int)ATTACK)->SetEvent(bind(&Boss_LichKing::End_ATK, this), 0.9f);
		GetClip((int)HIT)->SetEvent(bind(&Boss_LichKing::End_HIT, this), 0.9f);
		GetClip((int)DIE)->SetEvent(bind(&Boss_LichKing::End_DIE, this), 0.9f);
		GetClip((int)CASTING)->SetEvent(bind(&Boss_LichKing::End_CAST, this), 0.9f);
	}

	SetState(IDLE);

	characterData = CH->GetCharcterData();
	FOR(characterData.size())
	{
		character_Damage_Data.push_back(0.0f);
	}

	lich_SkillList.push_back(new Lich_001_Necrotic_Plague(this));
	//lich_SkillList.push_back(new Lich_002_Infest(this));
	lich_SkillList.push_back(new Lich_003_Summon_Drudge_Ghouls(this));

	target = CH->GetPlayerData();
}
Boss_LichKing::~Boss_LichKing()
{
	delete mainHand;
	delete Frost;
	delete myCollider;
	delete Frost_Collider;
	delete atk_serch;

	for (Lich_000_Base* lich : lich_SkillList)
		delete lich;
}

void Boss_LichKing::Update()
{
	if (!isActive) return;

	// 공격이나 스킬 사용후 잠깐의 휴식을 주기 위한 부분?
	if (lasting)
	{
		lasting_time -= DELTA;
		if (lasting_time >= 0) 
		{
			mainHand->SetWorld(GetTransformByNode(24));
			Frost->UpdateWorld();
			ModelAnimator::Update();

			for (int i = 0; i < lich_SkillList.size(); i++)
			{
				lich_SkillList[i]->Update();
			}
			return;
		}
		else
		{
			lasting = false;
			lasting_time = Max_lasting_time;
		}
	}
	// 체력 비율을 내기 위한 변수
	float vidul = Lich_Stat.cur_hp / Lich_Stat.Max_hp;
	if (vidul >= 0.7f)
	{
		phaseOne();
	}

	Moving();
	Attack();
	targetActiveSerch();

	for (int i = 0; i < lich_SkillList.size(); i++)
	{
		lich_SkillList[i]->Update();
	}
	mainHand->SetWorld(GetTransformByNode(24));
	Frost->UpdateWorld();
	myCollider->UpdateWorld();
	Frost_Collider->UpdateWorld();
	ModelAnimator::Update();
}

void Boss_LichKing::PreRender()
{
	
}

void Boss_LichKing::Render()
{
	if (!isActive) return;

	Frost->Render();
	myCollider->Render();
	Frost_Collider->Render();
	atk_serch->Render();
	ModelAnimator::Render();

	float Yvalue = 300;
	FOR(character_Damage_Data.size())
	{
		string userData = to_string(character_Damage_Data[i]);
		Font::Get()->RenderText(userData, { WIN_WIDTH - 20, WIN_HEIGHT - Yvalue });
		Yvalue += 100;
	}
	for (int i = 0; i < lich_SkillList.size(); i++)
	{
		lich_SkillList[i]->Render();
	}
}

void Boss_LichKing::PostRender()
{
	
}

void Boss_LichKing::GUIRender()
{
	Transform::GUIRender();
}

void Boss_LichKing::SetState(State state)
{
	if (state == curState) return;
	if (state == ATTACK)
	{
		Frost->Rot().z = XM_PI * 0.5f;
	}
	else
	{
		Frost->Rot().z = XM_PI;
	}

	curState = state;
	PlayClip(state);
}

void Boss_LichKing::Hit(float damage, int targetNumber)
{
	float damage_armor = damage - Lich_Stat.Armor;
	
	if (damage_armor > 0)
	{
		Lich_Stat.Max_hp -= damage_armor;
		character_Damage_Data[targetNumber] = damage_armor;
	}	

	if (Lich_Stat.cur_hp <= 0)
	{
		SetState(DIE);
	}
	else
	{
		SetState(IDLE);
	}
}

void Boss_LichKing::Moving()
{
	if (curState == ATTACK || curState == CASTING || curState == HIT || curState == DIE) return;
	if (target == nullptr) return;

	Vector3 direction = (target->GlobalPos() - GlobalPos()).GetNormalized();

	Rot().y = atan2(direction.x, direction.z) + XM_PI;
	Pos() += direction * Lich_Stat.moveSpeed  * DELTA;
	SetState(WALKING);
}
void Boss_LichKing::Attack()
{
	if (curState == HIT || curState == DIE) return;

	if (myCollider->IsCollision(target->GetCollider()))
	{
		Frost_Collider->SetActive(true);
		SetState(ATTACK);
	}
}

void Boss_LichKing::End_ATK()
{
	SetState(IDLE);
	Frost_Collider->SetActive(false);

	atk_serch->UpdateWorld();
	float atk_leng = FLT_MAX;
	CH_Base_ver2* lom = nullptr;
	for (int i = 0; i < characterData.size(); ++i)
	{
		if (atk_serch->IsCollision(characterData[i]->GetCollider()))
		{
			Vector3 leng = characterData[i]->GlobalPos() - atk_serch->GlobalPos();
			float min = leng.Length();

			if (atk_leng >= min)
			{
				atk_leng = min;
				lom = characterData[i];
			}
		}
	}

	if (lom != nullptr)
	{
		target = lom;
		lasting = true;
	}
}
void Boss_LichKing::End_HIT()
{
	SetState(IDLE);
}
void Boss_LichKing::End_DIE()
{
	isActive = false;
}
void Boss_LichKing::End_CAST()
{
	SetState(IDLE);
	Frost_Collider->SetActive(false);

	atk_serch->UpdateWorld();
	float atk_leng = FLT_MAX;
	CH_Base_ver2* lom = nullptr;
	for (int i = 0; i < characterData.size(); ++i)
	{
		if (atk_serch->IsCollision(characterData[i]->GetCollider()))
		{
			Vector3 leng = characterData[i]->GlobalPos() - atk_serch->GlobalPos();
			float min = leng.Length();

			if (atk_leng >= min)
			{
				atk_leng = min;
				lom = characterData[i];
			}
		}
	}

	if (lom != nullptr)
	{
		target = lom;
		lasting = true;
	}
}

void Boss_LichKing::targetActiveSerch()
{
	if (!target->GetCollider()->Active())
	{
		atk_serch->UpdateWorld();
		float atk_leng = FLT_MAX;
		vector<CH_Base_ver2*> characterData = CH->GetCharcterData();
		CH_Base_ver2* lom = nullptr;
		for (int i = 0; i < characterData.size(); ++i)
		{
			if (!characterData[i]->GetCollider()->Active()) continue;
			if (atk_serch->IsCollision(characterData[i]->GetCollider()))
			{
				Vector3 leng = characterData[i]->GlobalPos() - atk_serch->GlobalPos();
				float min = leng.Length();

				if (atk_leng >= min)
				{
					atk_leng = min;
					lom = characterData[i];
				}
			}
		}
		if (lom != nullptr)
		{
			target = lom;
			lasting = true;
		}
	}
}

void Boss_LichKing::phaseOne()
{
	//if (!lich_SkillList[0]->GetCoolTime())
	//{
	//	SetState(CASTING);
	//	lich_SkillList[0]->UseSkill(target);
	//}
	if (!lich_SkillList[1]->GetCoolTime())
	{
		SetState(CASTING);
		lich_SkillList[1]->UseSkill();
	}
}