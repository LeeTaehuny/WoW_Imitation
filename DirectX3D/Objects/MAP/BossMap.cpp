#include "Framework.h"
#include "BossMap.h"

BossMap::BossMap()
{
	Phase1 = new Model("LastBossMap1");		// 1�������� �� �Դϴ�

	Phase2.resize(10);
	Phase2[0] = new Model("LastBossMap2");  // 2�������� �� �Դϴ�

	Phase2[1] = new Model("IceEdge1");		// ���������� ���� �𼭸��κ��Դϴ�
	Phase2[2] = new Model("IceEdge2");
	Phase2[3] = new Model("IceEdge3");
	Phase2[4] = new Model("IceEdge4");
	
	Phase2[5] = new Model("Ice_debris1");	// �������� �Դϴ�
	Phase2[6] = new Model("Ice_debris2");
	Phase2[7] = new Model("Ice_debris3");
	Phase2[8] = new Model("Ice_debris4");

	Phase2[9] = new Model("IceBreak");		// ������ ������ �ٴ� ����Ʈ? �Դϴ�

	Phase2[5]->Pos().y = 295.0f;			// ���� ������ �ʱ� ��ġ�� �����մϴ�
	Phase2[6]->Pos().y = 295.0f;
	Phase2[7]->Pos().y = 295.0f;
	Phase2[8]->Pos().y = 295.0f;
	


	fixeds.resize(2);							// ����� �ٲ� ��ȭ���� �ʴ� �͵�
	fixeds[0] = new Model("LastBossMap1_B");    // ���� ��ġ�� �ִ� ��� �Դϴ�
	fixeds[1] = new Model("LastBossMap1_O2");   // ����ʿ��ִ� �罽 ����Դϴ�

	fixeds[1]->Pos().y += 22.5f;                // �罽 ����� �ʱ� ��ġ�� �����մϴ�
	fixeds[1]->Pos().x += 75;



	disappears.resize(4);							// 1������ ���Ŀ� ������� �������(��������) �Դϴ�
	for (int i = 0; i < disappears.size(); i++)
	{
		disappears[i] = new Model("LastBossMap1_O");
	}
	disappears[0]->Pos().x += 30;					// �ʱ���ġ ����
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


	for (int i = 0; i < fixeds.size(); i++) fixeds[i]->UpdateWorld();	// ����� �Ѿ�� ��ȭ���� �ʴ°͵��� �׳� ������Ʈ �մϴ�

	switch (PhaseNum) // ������ �ѹ������� ��Ƽ��� ������Ʈ ���θ� �Ǵ��Ͽ� �����մϴ�
	{
	case 0:
		Phase1->SetActive(true);
		for (int i = 0; i < disappears.size(); i++) disappears[i]->UpdateWorld();
		break;
	case 1:
		for (int i = 0; i < Phase2.size(); i++) Phase2[i]->SetActive(true);
		Phase1->SetActive(false);
		Fall();
		break;
	case 2:
		Phase1->SetActive(true);
		for (int i = 0; i < Phase2.size(); i++) Phase2[i]->SetActive(false);
		ZeroSet();
		break;
	case 3:
		for (int i = 0; i < Phase2.size(); i++) Phase2[i]->SetActive(true);
		Phase1->SetActive(false);
		Fall();
		break;
	}
}

void BossMap::Render()
{
	for (int i = 0; i < fixeds.size(); i++) fixeds[i]->Render(); // ����� �Ѿ�� ��ȭ���� �ʴ°͵��� �׳� ���� �մϴ�

	switch (PhaseNum) // ������ �ѹ������� ���� ���θ� �Ǵ��Ͽ� �����մϴ�
	{
	case 0:
		Phase1->Render();
		for (int i = 0; i < disappears.size(); i++) disappears[i]->Render();
		break;
	case 1:
		Phase2[0]->Render(); // 2������� �ϴ� ���� ���� �մϴ�
		NoneRender();
		break;
	case 2:
		Phase1->Render();
		break;
	case 3:
		Phase2[0]->Render();
		NoneRender();
	}
}

void BossMap::Fall() // ���� �ٴ��� �������� �Լ� �Դϴ�
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

void BossMap::ZeroSet() // ������ ���� �ٴ� ��ġ�� ���½�ŵ�ϴ�
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

void BossMap::NoneRender() // �����ٴ��� �� �������� ������ ���� �մϴ� (�ٶ������� ���������ʽ��ϴ�)
{
	for (int k = 1; k <= 9; ++k)
	{
		if (Phase2[1]->Pos().y > -150.0f)
		{
			Phase2[k]->Render();
		}
	}
}
