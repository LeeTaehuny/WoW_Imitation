#include "Framework.h"
#include "BossMap.h"

BossMap::BossMap()
{
	Phase1 = new Model("LastBossMap1");

	Phase2.resize(9);
	Phase2[0] = new Model("LastBossMap2");	

	Phase2[1] = new Model("IceEdge1");
	Phase2[2] = new Model("IceEdge2");
	Phase2[3] = new Model("IceEdge3");
	Phase2[4] = new Model("IceEdge4");
	
	Phase2[5] = new Model("Ice_debris1");
	Phase2[6] = new Model("Ice_debris2");
	Phase2[7] = new Model("Ice_debris3");
	Phase2[8] = new Model("Ice_debris4");

	Phase2[5]->Pos().y = 295.0f;
	Phase2[6]->Pos().y = 295.0f;
	Phase2[7]->Pos().y = 295.0f;
	Phase2[8]->Pos().y = 295.0f;
	


	fixeds.resize(2);
	fixeds[0] = new Model("LastBossMap1_B");
	fixeds[1] = new Model("LastBossMap1_O2");

	fixeds[1]->Pos().y += 22.5f;
	fixeds[1]->Pos().x += 75;



	disappears.resize(4);
	for (Model* disappear : disappears)
	{
		disappear = new Model("LastBossMap1_O");
	}
	disappears[0]->Pos().x += 30;
	disappears[0]->Pos().z -= 30;
	disappears[1]->Pos().x -= 30;
	disappears[1]->Pos().z -= 30;
	disappears[1]->Rot().y += 1.575f;
	disappears[2]->Pos().x -= 30;
	disappears[2]->Pos().z += 30;
	disappears[2]->Rot().y += 3.15f;
	disappears[3]->Pos().x += 30;
	disappears[3]->Pos().z += 30;
	disappears[3]->Rot().y -= 1.575f;
}

BossMap::~BossMap()
{
	delete Phase1;

	for (Model* p2 : Phase2)
	    delete p2;

	for (Model* fixed : fixeds)
		delete fixed;

	for (Model* disappear : disappears)
		delete disappear;
}

void BossMap::Update()
{
	for (Model* fixed : fixeds)
		fixed->UpdateWorld();


	if (PhaseNum == 0 || PhaseNum == 2)
	{
		Phase1->UpdateWorld();
	}

	if (PhaseNum == 1 || PhaseNum == 3)
	{
		for (Model* p2 : Phase2)
		{
			p2->UpdateWorld();
			
			for(int i = 1; i <= 4; ++i)
			{
				if(p2[i].Pos().y > -150.0f)
				{
					p2[i].Pos().y -= 100 * DELTA;
				}
			}
			for (int j = 5; j <= 8; ++j)
			{
				if (p2[j].Pos().y > -150.0f)
				{
					p2[j].Pos().y -= 50 * DELTA;
				}
			}

			for (int k = 1; k <= 8; ++k) // Reset(ZeroSet)
			{
				if(p2[1].Pos().y <= - 150.0f)
				{
					p2[1].Pos().y = 0;
					p2[2].Pos().y = 0;
					p2[3].Pos().y = 0;
					p2[4].Pos().y = 0;

					p2[5].Pos().y = 295.0f;
					p2[6].Pos().y = 295.0f;
					p2[7].Pos().y = 295.0f;
					p2[8].Pos().y = 295.0f;

					p2[k].SetActive(false);
				}
			}
			
		}
		
	}

	if (PhaseNum > 0)
	{
		for (Model* disappear : disappears)
		{
			disappear->SetActive(false);
		}
	}

}

void BossMap::Render()
{
	for (Model* fixed : fixeds)
		fixed->Render();


	if (PhaseNum == 0 || PhaseNum == 2)
	{
		Phase1->Render();
	}

	if (PhaseNum == 1 || PhaseNum == 3)
	{
		for (Model* p2 : Phase2)
		{
			p2->Render();
		}
	}
}
