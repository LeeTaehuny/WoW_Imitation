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

	Scale() *= 0.01f;
	ModelAnimator::Update();

	mainHand = new Transform();

	Frost = new Model("Frostmourne");
	Frost->SetParent(mainHand);
	Frost->Scale() *= 100;

	{
		GetClip((int)ATTACK_1)->SetEvent(bind(&Boss_LichKing::End_ATK, this), 0.9f);
		GetClip((int)HIT)->SetEvent(bind(&Boss_LichKing::End_HIT, this), 0.9f);
		GetClip((int)DIE)->SetEvent(bind(&Boss_LichKing::End_DIE, this), 0.9f);
		GetClip((int)CASTING)->SetEvent(bind(&Boss_LichKing::End_CAST, this), 0.9f);
	}

	SetState(ATTACK_1);
}

Boss_LichKing::~Boss_LichKing()
{
	delete mainHand;
	delete Frost;
}

void Boss_LichKing::Update()
{
	if (!isActive) return;

	if (KEY_DOWN('1'))
	{
		SetState(WALKING);
	}
	if (KEY_DOWN('2'))
	{
		SetState(ATTACK_1);
	}
	if (KEY_DOWN('3'))
	{
		SetState(IDLE);
	}
	if (KEY_DOWN('4'))
	{
		//SetState(HIT);
		Hit();
	}
	if (KEY_DOWN('5'))
	{
		SetState(DIE);
	}
	if (KEY_DOWN('6'))
	{
		SetState(CASTING);
	}

	mainHand->SetWorld(GetTransformByNode(24));
	Frost->UpdateWorld();
	ModelAnimator::Update();
}

void Boss_LichKing::PreRender()
{
	
}

void Boss_LichKing::Render()
{
	//if (!isActive) return;

	Frost->Render();
	ModelAnimator::Render();
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
	if (state == ATTACK_1)
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

void Boss_LichKing::Hit()
{
	if (cur_hp <= 0)
	{
		SetState(DIE);
	}
	else
	{
		SetState(HIT);
	}
}

void Boss_LichKing::End_ATK()
{
	SetState(IDLE);
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
}