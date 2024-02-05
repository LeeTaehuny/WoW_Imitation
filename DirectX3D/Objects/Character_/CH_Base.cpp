#include "Framework.h"
#include "Objects/Inventory/Inventory.h"

CH_Base::CH_Base(string name, CreatureType creatureType, ProfessionType professionType) 
	: ModelAnimator(name), creatureType(creatureType), professionType(professionType)
{
	inventory = new Inventory();
}

CH_Base::~CH_Base()
{
	SAFE_DEL(inventory);
}

void CH_Base::Update()
{
	inventory->Update();
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
	ModelAnimator::Render();
}

void CH_Base::UIRender()
{
	if (!Active()) return;
	inventory->UIRender();
}
