#include "Framework.h"

void CH_Base::PlayerUpdate()
{
	// ��Ƽ�� ���°� �ƴ϶�� ������Ʈ���� ����
	if (!Active()) return;

	Moving();
	Jump();
	Attack();
	Casting();

	// �浹ü ������Ʈ
	collider->UpdateWorld();
	
	ModelAnimator::Update();
}

void CH_Base::AIUpdate()
{
	Attack();

	ModelAnimator::Update();
}

void CH_Base::SetState(int state)
{
	if (state == INTstate) return;

	INTstate = state;
	PlayClip(state);
}

void CH_Base::Render()
{
	// ��Ƽ�� ���°� �ƴϸ� �������� ����
	if (!Active()) return;

	collider->Render();
	ModelAnimator::Render();
}