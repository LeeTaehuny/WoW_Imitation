﻿#include "Framework.h"
#include "Boss_LichKing.h"

Boss_LichKing::Boss_LichKing()
{
	type = LICH;

	Audio::Get()->Add("bossScene_atk", "Sounds/BossScene/lichking/attack_01.ogg", false, false, true);
	Audio::Get()->Add("bossScene_hit", "Sounds/BossScene/lichking/hit_01.ogg", false, false, true);
	Audio::Get()->Add("bossScene_die", "Sounds/BossScene/lichking/die_01.ogg", false, false, true);
	Audio::Get()->Add("bossScene_iceDown", "Sounds/BossScene/BGM/ice_down.ogg");

	transform = new Transform();
	transform->Scale() *= 2;

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

	collider = new CapsuleCollider();
	collider->SetParent(transform);
	collider->Pos().y += 1;
	collider->UpdateWorld();

	attackRange = new SphereCollider();
	attackRange->SetParent(transform);
	attackRange->Scale() *= 5;

	atk_serch = new SphereCollider();
	atk_serch->SetParent(transform);
	atk_serch->Scale() *= 100;
	atk_serch->UpdateWorld();

	mainHand = new Transform();

	Frost = new Model("Frostmourne");
	Frost->SetParent(mainHand);
	Frost->Scale() *= 100.5f;
	Frost_Collider = new BoxCollider();
	Frost_Collider->SetParent(transform);
	Frost_Collider->Scale() = Vector3(2.5f, 5, 5);
	Frost_Collider->Pos() = Vector3(0, 0, -2);
	Frost_Collider->SetActive(false);

	{
		lichking->GetClip((int)ATTACK)->SetEvent(bind(&Boss_LichKing::End_ATK, this), 0.9f);
		lichking->GetClip((int)HIT)->SetEvent(bind(&Boss_LichKing::End_HIT, this), 0.9f);
		lichking->GetClip((int)DIE)->SetEvent(bind(&Boss_LichKing::End_DIE, this), 0.9f);
		lichking->GetClip((int)CASTING)->SetEvent(bind(&Boss_LichKing::End_CAST, this), 0.9f);
	}

	SetState(IDLE);

	characterData = CH->GetCharcterData();

	lich_SkillList.push_back(new Lich_001_Necrotic_Plague(this));
	lich_SkillList.push_back(new Lich_002_Infest(this));
	lich_SkillList.push_back(new Lich_003_Summon_Drudge_Ghouls(this));
	lich_SkillList.push_back(new Lich_004_Summon_Shambling_Horror(this));
	lich_SkillList.push_back(new Lich_005_Remorseless_Winter(this));
	lich_SkillList.push_back(new Lick_006_Summon_IceSphere(this));
	lich_SkillList.push_back(new Lich_007_Defile(this));
	lich_SkillList.push_back(new Lick_008_Summon_Dark_Valkyr(this));

	target = CH->GetPlayerData();

	fieldzero = new SphereCollider();
	fieldzero->Scale() *= 0.001f;
	fieldzero->UpdateWorld();

	lasting = true;
	moveSpeed = 2;
	maxHP = 20000.0f;
	curHP = maxHP;
	Lich_Stat.damage = 300.0f;

	hitText.resize(20);

	frame = new Quad(L"Textures/UI/lich_hp_bar.png");
	frame->Pos() = Vector3(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.9f);
	frame->Scale() *= 1.25f;
	frame->UpdateWorld();

	face = new Quad(L"Textures/UI/lichpace.png");
	face->SetParent(frame);
	face->Scale() *= 0.1f;
	face->Pos().x -= 152;
	face->UpdateWorld();

	hp_bar = new ProgressBar(L"Textures/UI/hp_bar.png", L"Textures/UI/hp_bar_BG.png");
	hp_bar->SetParent(frame);
	hp_bar->Pos().x += 5;
	hp_bar->Pos().y -= 1;
	hp_bar->Scale().x *= 0.9f;
	hp_bar->UpdateWorld();
}
Boss_LichKing::~Boss_LichKing()
{
	delete mainHand;
	delete Frost;
	delete collider;
	delete Frost_Collider;
	delete attackTarget_serch;
	delete fieldzero;
	delete lichking;
	delete frame;
	delete hp_bar;
	delete face;

	delete attackRange;
	delete root;
	delete targetTransform;
	delete attackBumwe;

	for (Lich_000_Base* lich : lich_SkillList)
		delete lich;
}

void Boss_LichKing::Update()
{
	vidul = curHP / maxHP;
	hp_bar->SetAmount(vidul);
	hp_bar->UpdateWorld();

	if (!transform->Active()) return;
	if (curState == DIE)
	{
		lichking->Update();
		return;
	}

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

	switch (phase)
	{
	case 1:
		phaseOne();
		break;

	case 2:
		phaseSait();
		break;

	case 3:
		phaseTwo();
		break;

	case 4:
		phaseSait2();
		break;

	case 5:
		phaseThree();
		break;

	default:
		break;
	}

	Moving();
	Attack();
	targetActiveSerch();

	for (int i = 0; i < lich_SkillList.size(); i++)
	{
		lich_SkillList[i]->Update();
	}
	mainHand->SetWorld(lichking->GetTransformByNode(24));
	Frost->UpdateWorld();
	collider->UpdateWorld();
	Frost_Collider->UpdateWorld();
	transform->UpdateWorld();
	lichking->Update();
}

void Boss_LichKing::PreRender()
{

}

void Boss_LichKing::Render()
{
	if (!transform->Active()) return;

	Frost->Render();
	collider->Render();
	Frost_Collider->Render();
	atk_serch->Render();
	lichking->Render();
	attackRange->Render();

	float Yvalue = 300;
	for (int i = 0; i < lich_SkillList.size(); i++)
	{
		lich_SkillList[i]->Render();
	}
}

void Boss_LichKing::PostRender()
{
	if (!transform->Active()) return;

	hp_bar->Render();
	face->Render();
	frame->Render();

	int imvola = vidul * 100;
	if (imvola < 0) imvola = 0;
	string rito = to_string(imvola);
	Font::Get()->RenderText(rito, { 645, 652 });

	for (HitDesc& hit : hitText)
	{
		// 출력 Off면 출력 X
		if (!hit.isPrint) continue;

		// 지속시간 감소 및 출력 여부 체크
		hit.duration -= DELTA;

		if (hit.duration <= 0.0f)
		{
			hit.isPrint = false;
		}

		// 몬스터의 위치 구하기
		Vector3 screenPos = CAM->WorldToScreen(collider->GlobalPos());
		// 출력 (남은 시간에 비례해서 점점 올라가게 설정하기)
		Font::Get()->RenderText(hit.damage, { screenPos.x + 15.0f , screenPos.y - (50.0f * hit.duration) + 55.0f });
	}
}

void Boss_LichKing::GUIRender()
{
	if (ImGui::TreeNode((lichking->GetTag()).c_str()))
	{
		transform->GUIRender();

		string Mtag = "Lich_";
		ImGui::Text((Mtag + "_HP : " + to_string(curHP)).c_str());
		ImGui::Text((Mtag + "_HP_ratio : " + to_string(curHP / maxHP)).c_str());
		ImGui::Text((Mtag + "_MP : " + to_string(Atk)).c_str());

		ImGui::TreePop();
	}
}

void Boss_LichKing::Spawn(Vector3 pos)
{
	transform->SetActive(true);
	collider->SetActive(true);
	SetState(IDLE);
	curHP = maxHP;
	transform->Pos() = pos;
}

void Boss_LichKing::Hit(float amount)
{
	float damage_armor = amount - Lich_Stat.Armor;

	if (damage_armor > 0)
	{
		curHP -= damage_armor;
	}

	if (curHP <= 0)
	{
		if (die_one_sound == 0)
		{
			SetState(DIE);
			Audio::Get()->Play("bossScene_die", transform->Pos(), 1.0f);
			die_one_sound++;
		}
	}
	else
	{
		Audio::Get()->Play("bossScene_hit", transform->Pos(), 1.0f);
	}

	for (int i = 0; i < hitText.size(); i++)
	{
		// 출력 off 상태이면
		if (!hitText[i].isPrint)
		{
			// 출력 설정하기
			hitText[i].isPrint = true;
			hitText[i].duration = 1.0f;
			hitText[i].damage = to_string((int)amount);

			break;
		}
	}
}

void Boss_LichKing::SetState(State state)
{
	if (state == curState) return;
	if (curState == DIE) return;

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

void Boss_LichKing::resetBut()
{
	first = 0;
	thr_first = 0;
	for_first = 0;
	sumon1 = 3;
	skill1 = 7;
	fiv_first = 0;
	siitpha = false;
}

void Boss_LichKing::Moving()
{
	if (curState == ATTACK || curState == CASTING || curState == HIT || curState == DIE) return;
	if (target == nullptr || phase == 2 || phase == 4) return;

	Vector3 direction = (target->GlobalPos() - transform->GlobalPos()).GetNormalized();

	transform->Rot().y = atan2(direction.x, direction.z) + XM_PI;
	transform->Pos() += direction * moveSpeed * DELTA;
	SetState(WALKING);
}
void Boss_LichKing::Attack()
{
	if (curState == DIE || curState == CASTING || siitpha) return;

	if (curState != ATTACK)
	{
		attackRange->UpdateWorld();
		if (attackRange->IsCollision(target->GetCollider()))
		{
			if (atk_one_sound == 0)
			{
				atk_one_sound++;
			}
			Frost_Collider->SetActive(true);
			SetState(ATTACK);
			atk_del = Max_atk_del;
		}
	}

	if (atk_one_sound != 0)
	{
		atk_sound_Time -= DELTA;
		if (atk_sound_Time <= 0)
		{
			atk_sound_Time = Max_atk_sound_Time;
			Audio::Get()->Play("bossScene_atk", transform->Pos(), 1.0f);
			atk_one_sound = 0;
		}
	}

	if (Frost_Collider->Active())
	{
		atk_del -= DELTA;
		if (atk_del <= 0)
		{
			atk_del = Max_atk_del;
			if (Frost_Collider->IsCollision(target->GetCollider()))
			{
				target->OnHit(Lich_Stat.damage);
				Frost_Collider->SetActive(false);
			}
		}
	}
	else atk_del = Max_atk_del;
}

void Boss_LichKing::End_ATK()
{
	SetState(IDLE);
	Frost_Collider->SetActive(false);

	{
		atk_serch->UpdateWorld();
		float atk_leng = FLT_MAX;
		CH_Base_ver2* lom = CH->GetPlayerData();
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
		target = lom;
		lasting = true;
	}
	atk_one_sound = 0;
}
void Boss_LichKing::End_HIT()
{
	SetState(IDLE);
	hit_one_sound = 0;
}
void Boss_LichKing::End_DIE()
{
	transform->SetActive(false);
	lichking->SetActive(false);
	SetState(IDLE);
	die_one_sound = 0;
}
void Boss_LichKing::End_CAST()
{
	SetState(IDLE);
	Frost_Collider->SetActive(false);

	{
		atk_serch->UpdateWorld();
		float atk_leng = FLT_MAX;
		CH_Base_ver2* lom = CH->GetPlayerData();
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
		target = lom;
		lasting = true;
	}

	if (phase == 3 && thr_first == 1)
	{
		lasting = false;
		lasting_time = Max_lasting_time;

		thr_first++;
		Audio::Get()->Play("bossScene_iceDown");
		map->SetPhase(1);
	}
	if (phase == 4 && for_first == 1)
	{
		lasting = false;
		lasting_time = Max_lasting_time;

		for_first++;
		map->SetPhase(2);
	}
	if (phase == 5 && fiv_first == 1)
	{
		lasting = false;
		lasting_time = Max_lasting_time;

		fiv_first++;
		Audio::Get()->Play("bossScene_iceDown");
		map->SetPhase(3);
	}
}

void Boss_LichKing::targetActiveSerch()
{
	if (!target) return;
	if (!target->GetCollider()->Active())
	{
		atk_serch->UpdateWorld();
		float atk_leng = FLT_MAX;
		vector<CH_Base_ver2*> characterData = CH->GetCharcterData();
		CH_Base_ver2* lom = CH->GetPlayerData();
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
		target = lom;
		lasting = true;
	}
}

void Boss_LichKing::phaseOne()
{
	if (vidul < 0.7f)
	{
		phase = 2;
		return;
	}

	if (!lich_SkillList[0]->GetCoolTime())
	{
		SetState(CASTING);
		lich_SkillList[0]->UseSkill(target);
	}
	if (!lich_SkillList[2]->GetCoolTime())
	{
		SetState(CASTING);
		lich_SkillList[2]->UseSkill();
	}
	if (!lich_SkillList[3]->GetCoolTime())
	{
		SetState(CASTING);
		lich_SkillList[3]->UseSkill();
	}
}
void Boss_LichKing::phaseSait()
{
	if (first == 0)
	{
		first++;
		fieldzero->Scale() *= 0.01f;
	}

	if (!fieldzero->IsCollision(collider))
	{
		Vector3 direction = (fieldzero->GlobalPos() - transform->GlobalPos()).GetNormalized();

		transform->Rot().y = atan2(direction.x, direction.z) + XM_PI;
		transform->Pos() += direction * (moveSpeed * 5) * DELTA;
		SetState(WALKING);
	}
	else
	{
		if (Lich_005_Remorseless_Winter* c = dynamic_cast<Lich_005_Remorseless_Winter*>(lich_SkillList[4]))
		{
			if (c->GetSkillEnd() && phase == 2)
			{
				phase++;
				siitpha = false;
				c->ChangeSkillEnd();
				return;
			}

			if (!c->GetCoolTime())
			{
				siitpha = true;
				SetState(IDLE);
				c->UseSkill();
			}
		}

		if (!lich_SkillList[5]->GetCoolTime() && lich_SkillList[4]->GetisRun())
		{
			lich_SkillList[5]->UseSkill();
		}
	}
}
void Boss_LichKing::phaseTwo()
{
	if (thr_first <= 1)
	{
		thr_first = 1;
		SetState(CASTING);
	}
	if (thr_first != 2) return;

	if (vidul < 0.4f)
	{
		phase = 4;
		return;
	}

	if (!lich_SkillList[6]->GetCoolTime() || !lich_SkillList[6]->GetisRun())
	{
		SetState(CASTING);
		lich_SkillList[6]->UseSkill(target);
	}

	if (!lich_SkillList[7]->GetCoolTime())
	{
		SetState(CASTING);
		lich_SkillList[7]->UseSkill(target);
	}
}
void Boss_LichKing::phaseSait2()
{
	if (curState == CASTING) return;
	if (!fieldzero->IsCollision(collider))
	{
		Vector3 direction = (fieldzero->GlobalPos() - transform->GlobalPos()).GetNormalized();

		transform->Rot().y = atan2(direction.x, direction.z) + XM_PI;
		transform->Pos() += direction * (moveSpeed * 5) * DELTA;
		SetState(WALKING);
	}
	else
	{
		if (for_first <= 1)
		{
			for_first = 1;
			SetState(CASTING);
		}
		if (for_first != 2) return;

		if (Lich_005_Remorseless_Winter* c = dynamic_cast<Lich_005_Remorseless_Winter*>(lich_SkillList[4]))
		{
			if (c->GetSkillEnd())
			{
				phase++;
				siitpha = false;
				c->ChangeSkillEnd();
				return;
			}

			if (!c->GetCoolTime())
			{
				SetState(IDLE);
				siitpha = true;
				c->UseSkill();
			}
		}

		if (!lich_SkillList[5]->GetCoolTime() && lich_SkillList[4]->GetisRun())
		{
			lich_SkillList[5]->UseSkill();
		}
	}
}
void Boss_LichKing::phaseThree()
{
	if (fiv_first <= 1)
	{
		fiv_first = 1;
		SetState(CASTING);
	}
	if (fiv_first != 2) return;

	sumon1 -= DELTA;
	if (sumon1 <= 0)
	{
		sumon1 = 0;
		return;
	}
	if (!lich_SkillList[3]->GetCoolTime())
	{
		SetState(CASTING);
		lich_SkillList[3]->UseSkill();
	}

	skill1 -= DELTA;
	if (skill1 <= 0)
	{
		skill1 = 0;
		return;
	}
	if (!lich_SkillList[6]->GetCoolTime())
	{
		SetState(CASTING);
		lich_SkillList[6]->UseSkill(target);
	}
}