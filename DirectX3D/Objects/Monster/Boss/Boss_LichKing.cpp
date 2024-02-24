﻿#include "Framework.h"
#include "Boss_LichKing.h"

Boss_LichKing::Boss_LichKing()
{
	transform = new Transform();

	lichking = new ModelAnimator("LichKing");
	lichking->SetParent(transform);

	lichking->ReadClip("Walking");
	lichking->ReadClip("Attack_1");
	lichking->ReadClip("Idle");
	lichking->ReadClip("Hit");
	lichking->ReadClip("Die");
	lichking->ReadClip("Casting");

	lichking->Scale() *= 0.015f;
	lichking->Update();
	lichking->SetTag("LichKing");

	myCollider = new SphereCollider();
	myCollider->SetParent(transform);
	myCollider->Scale() *= 150.5f;
	myCollider->Pos().y += 100;
	myCollider->UpdateWorld();
	
	atk_serch = new SphereCollider();
	atk_serch->SetParent(transform);
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
		lichking->GetClip((int)ATTACK)->SetEvent(bind(&Boss_LichKing::End_ATK, this), 0.9f);
		lichking->GetClip((int)HIT)->SetEvent(bind(&Boss_LichKing::End_HIT, this), 0.9f);
		lichking->GetClip((int)DIE)->SetEvent(bind(&Boss_LichKing::End_DIE, this), 0.9f);
		lichking->GetClip((int)CASTING)->SetEvent(bind(&Boss_LichKing::End_CAST, this), 0.9f);
	}

	SetState(IDLE);

	characterData = CH->GetCharcterData();
	FOR(characterData.size())
	{
		character_Damage_Data.push_back(0.0f);
	}

	lich_SkillList.push_back(new Lich_001_Necrotic_Plague(this));
	lich_SkillList.push_back(new Lich_002_Infest(this));
	lich_SkillList.push_back(new Lich_003_Summon_Drudge_Ghouls(this));
	lich_SkillList.push_back(new Lich_004_Summon_Shambling_Horror(this));
	lich_SkillList.push_back(new Lich_005_Remorseless_Winter(this));

	target = CH->GetPlayerData();

	fieldzero = new SphereCollider();
	fieldzero->Scale() *= 0.001f;
	fieldzero->UpdateWorld();
}
Boss_LichKing::~Boss_LichKing()
{
	delete mainHand;
	delete Frost;
	delete myCollider;
	delete Frost_Collider;
	delete atk_serch;
	delete fieldzero;
	delete lichking;

	for (Lich_000_Base* lich : lich_SkillList)
		delete lich;
}

void Boss_LichKing::Update()
{
	if (!transform->Active()) return;

	// 공격이나 스킬 사용후 잠깐의 휴식을 주기 위한 부분?
	if (lasting)
	{
		lasting_time -= DELTA;
		if (lasting_time >= 0) 
		{
			mainHand->SetWorld(lichking->GetTransformByNode(24));
			Frost->UpdateWorld();
			lichking->Update();

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
	else if (vidul < 0.7f)
	{
		phaseTwo();
	}

	if (KEY_DOWN('C'))
		Lich_Stat.cur_hp -= 1000;

	Moving();
	Attack();
	targetActiveSerch();

	for (int i = 0; i < lich_SkillList.size(); i++)
	{
		lich_SkillList[i]->Update();
	}
	mainHand->SetWorld(lichking->GetTransformByNode(24));
	Frost->UpdateWorld();
	myCollider->UpdateWorld();
	Frost_Collider->UpdateWorld();
	lichking->Update();
}

void Boss_LichKing::PreRender()
{
	
}

void Boss_LichKing::Render()
{
	if (!transform->Active()) return;

	Frost->Render();
	myCollider->Render();
	Frost_Collider->Render();
	atk_serch->Render();
	lichking->Render();

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
	if (ImGui::TreeNode((lichking->GetTag()).c_str()))
	{
		transform->GUIRender();

		string Mtag = "Lich_";
		ImGui::Text((Mtag + "_HP : " + to_string(Lich_Stat.cur_hp)).c_str());
		ImGui::Text((Mtag + "_HP_ratio : " + to_string(Lich_Stat.cur_hp / Lich_Stat.Max_hp)).c_str());
		ImGui::Text((Mtag + "_MP : " + to_string(Lich_Stat.damage)).c_str());

		ImGui::TreePop();
	}
}

void Boss_LichKing::Spawn(Vector3 pos)
{
}

void Boss_LichKing::Hit(float amount)
{
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
	lichking->PlayClip(state);
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
	if (target == nullptr || first != 0) return;

	Vector3 direction = (target->GlobalPos() - transform->GlobalPos()).GetNormalized();

	transform->Rot().y = atan2(direction.x, direction.z) + XM_PI;
	transform->Pos() += direction * Lich_Stat.moveSpeed  * DELTA;
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
	transform->SetActive(false);
	lichking->SetActive(false);
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
	//if (!lich_SkillList[1]->GetCoolTime())
	//{
	//	SetState(CASTING);
	//	lich_SkillList[1]->UseSkill(target);
	//}
	//if (!lich_SkillList[2]->GetCoolTime())
	//{
	//	SetState(CASTING);
	//	lich_SkillList[2]->UseSkill();
	//}
	//if (!lich_SkillList[3]->GetCoolTime())
	//{
	//	SetState(CASTING);
	//	lich_SkillList[3]->UseSkill();
	//}
}
void Boss_LichKing::phaseTwo()
{
	if (first == 0)
	{
		first++;
		fieldzero->Scale() *= 0.01f;
	}

	if (!fieldzero->IsCollision(myCollider))
	{
		Vector3 direction = (fieldzero->GlobalPos() - transform->GlobalPos()).GetNormalized();

		transform->Rot().y = atan2(direction.x, direction.z) + XM_PI;
		transform->Pos() += direction * Lich_Stat.moveSpeed * DELTA;
		SetState(WALKING);
	}
	else
	{
		if (!lich_SkillList[4]->GetCoolTime())
		{
			SetState(IDLE);
			lich_SkillList[4]->UseSkill();
		}
	}
}