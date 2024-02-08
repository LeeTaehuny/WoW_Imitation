#include "Framework.h"
#include "Objects/Inventory/Inventory.h"

CH_Base::CH_Base(string name, CreatureType creatureType, ProfessionType professionType)
	: ModelAnimator(name), creatureType(creatureType), professionType(professionType)
{
	switch (creatureType)
	{
	case CreatureType::Player:
		inventory = new Inventory();
		break;
	case CreatureType::NonPlayer:
		break;
	}
}

CH_Base::~CH_Base()
{
	SAFE_DEL(inventory);
	SAFE_DEL(myPlayer);
}

void CH_Base::Update()
{
	if (inventory != nullptr) inventory->Update();
	ModelAnimator::Update();
}

//void CH_Base::SetState(int state)
//{
//	if (state == INTstate) return;
//
//	INTstate = state;
//	PlayClip(state);
//}

void CH_Base::Render()
{
	ModelAnimator::Render();
}

void CH_Base::UIRender()
{
	if (!Active()) return;
	if (inventory != nullptr) inventory->UIRender();
}
