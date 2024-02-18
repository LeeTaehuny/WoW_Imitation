#include "Framework.h"
#include "BossMap.h"

BossMap::BossMap()
{
	skybox = new SkyBox(L"Textures/Landscape/Space.dds");
	skybox->UpdateWorld();

	Phase1 = new Model("LastBossMap1");		// 1페이즈의 땅 입니다
	GroundColider1 = new Cylinder();
	GroundColider1->SetParent(Phase1);
	GroundColider1->Scale() *= 75.0f;
	GroundColider1->Pos().y -= 33.5f;
	//GroundColider1->SetActive(false);

	Phase2.resize(10);
	Phase2[0] = new Model("LastBossMap2");  // 2페이즈의 땅 입니다
	GroundColider2 = new Cylinder();
	GroundColider2->SetParent(Phase2[0]);
	GroundColider2->Scale() *= 50.0f;
	GroundColider2->Pos().y -= 21.5f;
	//GroundColider2->SetActive(false);

	Phase2[1] = new Model("IceEdge1");		// 떨어져나갈 땅의 모서리부분입니다
	Phase2[2] = new Model("IceEdge2");
	Phase2[3] = new Model("IceEdge3");
	Phase2[4] = new Model("IceEdge4");
	
	Phase2[5] = new Model("Ice_debris1");	// 얼음파편 입니다
	Phase2[6] = new Model("Ice_debris2");
	Phase2[7] = new Model("Ice_debris3");
	Phase2[8] = new Model("Ice_debris4");

	Phase2[9] = new Model("IceBreak");		// 얼음이 깨지는 바닥 이펙트? 입니다

	Phase2[5]->Pos().y = 295.0f;			// 얼음 파편의 초기 위치를 설정합니다
	Phase2[6]->Pos().y = 295.0f;
	Phase2[7]->Pos().y = 295.0f;
	Phase2[8]->Pos().y = 295.0f;
	


	fixeds.resize(2);							// 페이즈가 바뀌어도 변화하지 않는 것들
	fixeds[0] = new Model("LastBossMap1_B");    // 땅을 받치고 있는 기둥 입니다
	fixeds[1] = new Model("LastBossMap1_O2");   // 계단쪽에있는 사슬 기둥입니다
	fixeds[1]->Pos().y += 22.5f;                // 사슬 기둥의 초기 위치를 설정합니다
	fixeds[1]->Pos().x += 75;
	StairCollider = new BoxCollider(Vector3(5, 40, 25));
	StairCollider->Pos().y += 7.5;
	StairCollider->Pos().x += 57.5;
	StairCollider->Rot().z -= 0.875;
	Chair_Ground = new BoxCollider(Vector3(15, 10, 20));
	Chair_Ground->Pos().y += 18.5f;
	Chair_Ground->Pos().x += 78.5;
	Chair = new BoxCollider(Vector3(10, 10, 10));
	Chair->Pos().y += 20.0f;
	Chair->Pos().x += 80.0f;

	disappears.resize(4);							// 1페이즈 이후에 사라지는 얼음기둥(갈비뼈모양) 입니다
	disappears_C.resize(4);
	for (int i = 0; i < disappears.size(); i++)
	{
		disappears[i] = new Model("LastBossMap1_O");
		disappears_C[i] = new Cylinder(3.5f, 15.0f, 32);
		disappears_C[i]->SetParent(disappears[i]);
		disappears_C[i]->Pos().y += 10.0f;
		//disappears_C[i]->SetActive(false);
	}
	disappears[0]->Pos().x += 30;					// 초기위치 설정
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

	fixeds[0]->Pos().y -= 2.25f;
	Phase1->SetParent(fixeds[0]);
	for (int i = 0; i < Phase2.size(); i++) Phase2[i]->SetParent(fixeds[0]);
	for (int i = 0; i < fixeds.size(); i++) fixeds[i]->SetParent(fixeds[0]);
	for (int i = 0; i < disappears.size(); i++) disappears[i]->SetParent(fixeds[0]);
	//fixeds[0]->Scale() *= 0.5f;
}

BossMap::~BossMap()
{
	delete Phase1;

	for (int i = 0; i < Phase2.size(); i++) delete Phase2[i];
	for (int i = 0; i < fixeds.size(); i++) delete fixeds[i];
	for (int i = 0; i < disappears.size(); i++) delete disappears[i];
}

void BossMap::Update()
{
	//if(KEY_DOWN(VK_RIGHT))
	//{
	//	PhaseNum += 1;
	//}


	for (int i = 0; i < fixeds.size(); i++) fixeds[i]->UpdateWorld();	// 페이즈가 넘어가도 변화하지 않는것들은 그냥 업데이트 합니다
	StairCollider->UpdateWorld();
	Chair_Ground->UpdateWorld();
	Chair->UpdateWorld();

	switch (PhaseNum) // 페이즈 넘버에따라 엑티브와 업데이트 여부를 판단하여 수행합니다
	{
	case 0:
		Phase1->UpdateWorld();
		Phase1->SetActive(true);
		GroundColider1->SetActive(true);
		GroundColider1->UpdateWorld();
	
		for (int i = 0; i < disappears.size(); i++) 
		{
			disappears[i]->UpdateWorld();
			disappears_C[i]->UpdateWorld();
		}
		break;
	case 1:
		for (int i = 0; i < Phase2.size(); i++) Phase2[i]->SetActive(true);
		Phase1->SetActive(false);
		GroundColider2->SetActive(true);
		GroundColider2->UpdateWorld();
		Fall();
		break;
	case 2:
		Phase1->SetActive(true);
		Phase1->UpdateWorld();
		GroundColider1->SetActive(true);
		for (int i = 0; i < Phase2.size(); i++) Phase2[i]->SetActive(false);
		ZeroSet();
		break;
	case 3:
		for (int i = 0; i < Phase2.size(); i++) Phase2[i]->SetActive(true);
		GroundColider2->SetActive(true);
		Phase1->SetActive(false);
		GroundColider1->SetActive(false);
		Fall();
		break;
	}
}

void BossMap::Render()
{
	skybox->Render();

	for (int i = 0; i < fixeds.size(); i++) fixeds[i]->Render(); // 페이즈가 넘어가도 변화하지 않는것들은 그냥 랜더 합니다
	StairCollider->Render();
	Chair_Ground->Render();
	Chair->Render();

	switch (PhaseNum) // 페이즈 넘버에따라 랜더 여부를 판단하여 수행합니다
	{
	case 0:
		Phase1->Render();
		//GroundColider1->Render();
		for (int i = 0; i < disappears.size(); i++) 
		{
			disappears[i]->Render();
			//disappears_C[i]->Render();
		}
		break;
	case 1:
		Phase2[0]->Render(); // 2페이즈는 일단 땅만 랜더 합니다
		//GroundColider2->Render();
		NoneRender();
		break;
	case 2:
		Phase1->Render();
		GroundColider1->Render();
		break;
	case 3:
		Phase2[0]->Render();
		//GroundColider2->Render();
		NoneRender();
	}
}

bool BossMap::IsCollision(Collider* c)
{
	if (StairCollider->PushCollision(c)) 
	{
		c->GetParent()->Pos().y += 0.1f;
		return true;
	} 
	if (Chair_Ground->PushCollision(c)) return true;
	if (Chair->PushCollision(c)) return true;

	if (PhaseNum == 0)
	{
		for (int i = 0; i < disappears.size(); i++) 
		{
			if (disappears_C[i]->PushCollision((CapsuleCollider*)c)) return true;
		}
	}
	if (PhaseNum == 0 || PhaseNum == 2)
	{
		if (GroundColider1->IsCapsuleCollision((CapsuleCollider*)c)) return true;
	}
	if (PhaseNum == 1 || PhaseNum == 3) 
	{
		if (GroundColider2->IsCapsuleCollision((CapsuleCollider*)c)) return true;
	}
	
	//return false;
}

void BossMap::Fall() // 얼음 바닥이 떨어지는 함수 입니다
{

	for (int i = 0; i < Phase2.size(); i++) Phase2[i]->UpdateWorld();

	for (int i = 1; i <= 4; ++i)
	{
		if (Phase2[i]->Pos().y > -150.0f)
		{
			Phase2[i]->Pos().y -= 100 * DELTA;
		}
	}
	for (int j = 5; j <= 8; ++j)
	{
		if (Phase2[j]->Pos().y > -150.0f)
		{
			Phase2[j]->Pos().y -= 50 * DELTA;
		}
	}
}

void BossMap::ZeroSet() // 떨어진 얼음 바닥 위치를 리셋시킵니다
{
	for (int k = 1; k <= 8; ++k)
	{
		if (Phase2[1]->Pos().y <= -150.0f)
		{
			Phase2[1]->Pos().y = 0;
			Phase2[2]->Pos().y = 0;
			Phase2[3]->Pos().y = 0;
			Phase2[4]->Pos().y = 0;

			Phase2[5]->Pos().y = 295.0f;
			Phase2[6]->Pos().y = 295.0f;
			Phase2[7]->Pos().y = 295.0f;
			Phase2[8]->Pos().y = 295.0f;

			Phase2[k]->SetActive(false);
		}
	}
}

void BossMap::NoneRender() // 얼음바닥이 다 떨어지기 전까지 랜더 합니다 (다떨어지면 랜더하지않습니다)
{
	for (int k = 1; k <= 9; ++k)
	{
		if (Phase2[1]->Pos().y > -150.0f)
		{
			Phase2[k]->Render();
		}
	}
}
