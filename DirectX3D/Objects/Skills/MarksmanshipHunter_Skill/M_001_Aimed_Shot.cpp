﻿#include "Framework.h"
#include "M_001_Aimed_Shot.h"

M_001_Aimed_Shot::M_001_Aimed_Shot() : ActiveSkill(SkillType::Target)
{
	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 30.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본 쿨타임은 : (6초)
		// 충천하여 스킬을 사용하는 방식 (2회 충전)
		// 그렇기 때문에 쿨타입을 반으로 줄임
		MAX_delay = 6.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// 마나 소모 : 35.0%
		usingType = monster_Data;
	}
	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/001.jpg");

	arrow = new Model("arrow");
	effectTexture = new Quad(L"Textures/Effect/Alpha_Red_snow.png");
	effectTexture->SetParent(arrow);
	effectTexture->Scale() *= 0.05f;
	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
}

M_001_Aimed_Shot::~M_001_Aimed_Shot()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete arrow;
	delete targetMonster;
	delete effectTexture;

	FOR(2) delete blendState[i];
	FOR(2) delete depthState[i];
}

void M_001_Aimed_Shot::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		direction = (targetMonster->GetCollider()->GlobalPos() - myCollider->GlobalPos()).GetNormalized();
		myCollider->Pos() += direction * speed * DELTA;
		myCollider->UpdateWorld();

		arrow->Pos() = myCollider->GlobalPos();
		arrow->Rot().y = atan2(direction.x, direction.z) + -(XM_PI * 0.5f);
		effectTexture->Rot() = CAM->Rot();
		effectTexture->UpdateWorld();
		arrow->UpdateWorld();

		if (myCollider->IsCollision(targetMonster->GetCollider()))
		{
			targetMonster->Hit(skillDamage);
			myCollider->SetActive(false);
			isRun = false;
		}
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void M_001_Aimed_Shot::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		blendState[1]->SetState();
		depthState[1]->SetState();
		effectTexture->Render();
		blendState[0]->SetState();
		depthState[0]->SetState();

		arrow->Render();
	}	
}

void M_001_Aimed_Shot::UseSkill(MonsterBase* monsterbase)
{
	if (isCooldown || monsterbase == nullptr || 
		owner->GetStat().mp < 350) return;

	if (MarksmanshipHunter_in* c = dynamic_cast<MarksmanshipHunter_in*>(owner))
	{
		c->SetState(MarksmanshipHunter_in::State::ATTACK1);
	}

	skillDamage = owner->GetStat().damage * 2.8f;
	owner->GetStat().mp -= 350;

	myCollider->Pos() = owner->GlobalPos();
	myCollider->Pos().y += owner->GlobalScale().y;
	myCollider->SetActive(true);
	myCollider->UpdateWorld();

	targetMonster = monsterbase;
	animStart = 0;
	isRun = true;
	isCooldown = true;
}