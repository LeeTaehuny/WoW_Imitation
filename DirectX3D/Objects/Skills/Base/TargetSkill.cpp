﻿#include "Framework.h"

TargetSkill::TargetSkill(Type type) : 
	SkillBase(TARGET), // 타겟팅 스킬임을 설정
	type(type)         // 즉발성인지 아닌지 구분하기 위함
{
	particle = new Snow();
}

TargetSkill::~TargetSkill()
{
	delete enemy;
}

void TargetSkill::NonTarget(){}

void TargetSkill::Target()
{
	if (!enemy) return;
	if (!myCollider->Active()) return;

	switch (type)
	{
	case TargetSkill::AA: // 즉발성
		vong();
		break;

	case TargetSkill::BB: // 투사체
		wing();
		break;
	}

	particle->Play(myCollider->Pos());
	if (particle != nullptr) particle->Update();
	myCollider->UpdateWorld();
}

void TargetSkill::vong()
{
	// 대상의 위치로 콜라이더 이동
	myCollider->Pos() = enemy->GlobalPos();
}

void TargetSkill::wing()
{
	// 자신과 적의 위치를 받아와 방향을 정합니다.
	velocity = (enemy->GlobalPos() - myCollider->GlobalPos()).GetNormalized();

	// 정해진 방향과 델타값, 날아가는 속도를 곱하여 콜라이더에 누적합니다.
	myCollider->Pos() += velocity * DELTA * FlyingSpeed;
	// 자신과 적의 방향을 통해 항상 적을 바라보도록 각도를 수정합니다.
	myCollider->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;

	// 적의 콜라이더와 충돌하면 내 콜라이더 비활성화
	if (enemy->IsCollision(myCollider))
	{
		myCollider->SetActive(false);
	}
}