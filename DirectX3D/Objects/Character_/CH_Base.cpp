#include "Framework.h"
#include "Objects/Inventory/Inventory.h"

CH_Base::CH_Base(string name) : ModelAnimator(name)
{
	inventory = new Inventory();
}

void CH_Base::PlayerUpdate()
{
	// 액티브 상태가 아니라면 업데이트하지 않음
	if (!Active()) return;

	Moving();
	Jump();
	Attack();
	Casting();

	inventory->Update();

	// 충돌체 업데이트
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
	// 액티브 상태가 아니면 렌더하지 않음
	if (!Active()) return;

	collider->Render();
	ModelAnimator::Render();
}

void CH_Base::UIRender()
{
	if (!Active()) return;

	inventory->UIRender();
}
