#include "Framework.h"
#include "BossMap.h"

BossMap::BossMap()
{
	Phase1 = new LastBossMap_Phase1();
	Phase2 = new LastBossMap_Phase2();
}

BossMap::~BossMap()
{
	delete Phase1;
	delete Phase2;
}

void BossMap::Update()
{
	if (PhaseNum == 0 || PhaseNum == 2)
	{
		Phase1->Update();
	}

	if (PhaseNum == 1 || PhaseNum == 3)
	{
		Phase2->Update();
	}
}

void BossMap::Render()
{
	if (PhaseNum == 0 || PhaseNum == 2)
	{
		Phase1->Render();
	}

	if (PhaseNum == 1 || PhaseNum == 3)
	{
		Phase2->Render();
	}
}
