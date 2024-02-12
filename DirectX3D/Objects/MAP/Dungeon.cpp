#include "Framework.h"
#include "Dungeon.h"

Dungeon::Dungeon() //: Transform()
{
	//terrain = new Terrain();
	//terrain->Rot().x = 0.0f;
	//terrain->Rot().y = 0.0f;
	//terrain->Rot().z = 0.0f;

	Gates.resize(6);
	Gates[0] = new Model("Gate");
	boxCollider_G = new BoxCollider(Vector3(35, 120, 230));
	boxCollider_G->SetParent(Gates[0]);
	boxCollider_G->Pos().y -= 80;
	boxCollider_GL = new BoxCollider(Vector3(35, 30, 95));
	boxCollider_GL->SetParent(Gates[0]);
	boxCollider_GL->Pos().z -= 65;
	boxCollider_GR = new BoxCollider(Vector3(35, 30, 95));
	boxCollider_GR->SetParent(Gates[0]);
	boxCollider_GR->Pos().z += 65;

	Gates[1] = new Model("Gate_Prop");
	Gates[1]->Pos().y -= 75.0f;
	Gates[1]->Pos().x -= 38.0f;
	boxCollider_GP = new BoxCollider(Vector3(55, 125, 80));
	boxCollider_GP->SetParent(Gates[1]);
	boxCollider_GP->Pos().y -= 7.0;

	Gates[2] = new Model("Gate_Prop");
	Gates[2]->Rot().y += 3.15f;
	Gates[2]->Pos().y -= 85.5f;
	Gates[2]->Pos().x += 49.5f;
	boxCollider_GPI = new BoxCollider(Vector3(55, 125, 80));
	boxCollider_GPI->SetParent(Gates[2]);
	boxCollider_GPI->Pos().y -= 7.0;


	Gates[3] = new Model("Gate_Stairs2");
	Gates[3]->Pos().y -= 70.0f;
	Gates[3]->Pos().x -= 127.5f;
	boxCollider_S = new BoxCollider(Vector3(125, 150, 60));
	boxCollider_S->SetParent(Gates[3]);
	boxCollider_S->Rot().z -= 1.125f;
	boxCollider_S->Pos().y -= 37.5f;
	boxCollider_S->Pos().x += 30.0f;

	Gates[4] = new Model("Gate_Stairs");
	Gates[4]->Rot().y += 3.15f;
	Gates[4]->Pos().y -= 70.0f;
	Gates[4]->Pos().x += 140.0f;
	boxCollider_SI = new BoxCollider(Vector3(80, 70, 45));
	boxCollider_SI->SetParent(Gates[4]);
	boxCollider_SI->Rot().z -= 1.125f;
	boxCollider_SI->Pos().y -= 9.5f;
	boxCollider_SI->Pos().x += 50.0f;
	boxCollider_SIC = new BoxCollider(Vector3(57.5, 50, 42.5));
	boxCollider_SIC->SetParent(Gates[4]);
	boxCollider_SIC->Pos().x -= 25.0f;
	boxCollider_SIC->Pos().y -= 13.5f;

	boxCollider_SIL = new BoxCollider(Vector3(50.0, 62.5, 45.5));
	boxCollider_SIL->SetParent(Gates[4]);
	boxCollider_SIL->Pos().x -= 20.0f;
	boxCollider_SIL->Pos().y -= 25.0f;
	boxCollider_SIL->Pos().z -= 32.5f;
	boxCollider_SIL->Rot().x += 0.95f;

	boxCollider_SIR = new BoxCollider(Vector3(50.0, 62.5, 45.5));
	boxCollider_SIR->SetParent(Gates[4]);
	boxCollider_SIR->Pos().x -= 20.0f;
	boxCollider_SIR->Pos().y -= 25.0f;
	boxCollider_SIR->Pos().z += 32.5f;
	boxCollider_SIR->Rot().x -= 0.95f;
	

	Gates[5] = new Model("Gate_Door");
	Gates[5]->Scale() *= 9.0f;
	Gates[5]->Pos().y -= 20.5f; // close
	boxCollider_GD = new BoxCollider(Vector3(2, 5, 4));
	boxCollider_GD->SetParent(Gates[5]);
	boxCollider_GD->Pos().y += 2.5f;

	//////////////////////////////////////////////

	Walls_L.resize(8);
	boxColliders_WL.resize(8);
	for (int i = 0; i < Walls_L.size(); ++i) 
	{
		Walls_L[i] = new Model("Wall");
		boxColliders_WL[i] = new BoxCollider(Vector3(35, 150, 120));
		boxColliders_WL[i]->SetParent(Walls_L[i]);
	}

	for (int i = 0; i < Walls_L.size(); ++i)
	{
		Walls_L[i]->Rot().y += 1.575f;
		Walls_L[i]->Pos().y += 10.0f;
		Walls_L[i]->Pos().z += 130.0f;
	}
	float gap = 117.5f;
	float currentX = 0.0f;
	for (int i = 0; i < Walls_L.size(); ++i)
	{
		Walls_L[i]->Pos().x = currentX;
		currentX += gap;
	}
	for (int i = 0; i < Walls_L.size(); ++i) Walls_L[i]->Pos().x += 57.5f;
	for (int i = 4; i < Walls_L.size(); ++i) Walls_L[i]->Pos().z += 120.0;
	Walls_LF = new Model("Wall");
	Walls_LF->Pos().x += 460.0f;
	Walls_LF->Pos().z += 180.0f;
	Walls_LF->Pos().y += 10.0f;
	boxCollider_WLF = new BoxCollider(Vector3(35, 150, 120));
	boxCollider_WLF->SetParent(Walls_LF);

	//////////////////////////////////////////////

	Walls_R.resize(8);
	boxColliders_WR.resize(8);
	for (int i = 0; i < Walls_R.size(); ++i) 
	{
		Walls_R[i] = new Model("Wall");
		boxColliders_WR[i] = new BoxCollider(Vector3(35, 150, 120));
		boxColliders_WR[i]->SetParent(Walls_R[i]);
	}
		

	for (int i = 0; i < Walls_R.size(); ++i)
	{
		Walls_R[i]->Rot().y -= 1.575f;
		Walls_R[i]->Pos().y += 10.0f;
		Walls_R[i]->Pos().z -= 130.0f;
	}
	gap = 117.5f;
	currentX = 0.0f;
	for (int i = 0; i < Walls_R.size(); ++i)
	{
		Walls_R[i]->Pos().x = currentX;
		currentX += gap;
	}
	for (int i = 0; i < Walls_R.size(); ++i) Walls_R[i]->Pos().x += 57.5f;
	for (int i = 4; i < Walls_R.size(); ++i) Walls_R[i]->Pos().z -= 120.0;
	Walls_RF = new Model("Wall");
	Walls_RF->Pos().x += 460.0f;
	Walls_RF->Pos().z -= 180.0f;
	Walls_RF->Pos().y += 10.0f;
	boxCollider_WRF = new BoxCollider(Vector3(35, 150, 120));
	boxCollider_WRF->SetParent(Walls_RF);

	//////////////////////////////////////////////

	Walls_B.resize(4);
	boxColliders_WB.resize(4);
	for (int i = 0; i < Walls_B.size(); ++i) 
	{
		Walls_B[i] = new Model("Wall");
		boxColliders_WB[i] = new BoxCollider(Vector3(35, 150, 120));
		boxColliders_WB[i]->SetParent(Walls_B[i]);
	} 
	for (int i = 0; i < Walls_B.size(); ++i)
	{
		Walls_B[i]->Rot().y -= 3.15f;
		Walls_B[i]->Pos().y += 10.0f;
		Walls_B[i]->Pos().x += 950.0f;
	}
	gap = 117.5f;
	currentX = 0.0f;
	for (int i = 0; i < Walls_B.size(); ++i)
	{
		Walls_B[i]->Pos().z = currentX;
		currentX -= gap;
		Walls_B[i]->Pos().z += 180.0f;
	}

	//////////////////////////////////////////////

	InGates.resize(7);
	InGates[0] = new Model("InGate");
	InGates[0]->Pos().x += 460.0f;
	InGates[0]->Pos().y += 10.0f;
	
	InGates[1] = new Model("Wall"); // L
	InGates[1]->Pos().x += 460.0f;
	InGates[1]->Pos().y += 10.0f;
	InGates[1]->Pos().z += 90.0f;
	boxCollider_WGL = new BoxCollider(Vector3(35, 150, 120));
	boxCollider_WGL->SetParent(InGates[1]);

	InGates[2] = new Model("Wall"); // R
	InGates[2]->Pos().x += 460.0f;
	InGates[2]->Pos().y += 10.0f;
	InGates[2]->Pos().z -= 95.0f;
	boxCollider_WGR = new BoxCollider(Vector3(35, 150, 120));
	boxCollider_WGR->SetParent(InGates[2]);
	
	InGates[3] = new Model("InGateDoor_R");
	InGates[3]->Pos().x += 450.0f;
	InGates[3]->Pos().z -= 36.5f;
	InGates[3]->Pos().y -= 12.5f;
	InGates[3]->Scale() *= 2.0f;
	boxCollider_DR = new BoxCollider(Vector3(9, 50, 17.5f));
	boxCollider_DR->SetParent(InGates[3]);
	boxCollider_DR->Pos().x += 0.0f;
	boxCollider_DR->Pos().z += 10.0f;
	boxCollider_DR->Pos().y += 22.5f;
	
	InGates[4] = new Model("InGateDoor_L");
	InGates[4]->Pos().x += 450.0f;
	InGates[4]->Pos().z += 36.5f;
	InGates[4]->Pos().y -= 12.5f;
	InGates[4]->Scale() *= 2.0f;
	boxCollider_DL = new BoxCollider(Vector3(9, 50, 17.5f));
	boxCollider_DL->SetParent(InGates[4]);
	boxCollider_DL->Pos().x += 0.0f;
	boxCollider_DL->Pos().z -= 10.0f;
	boxCollider_DL->Pos().y += 22.5f;

	
	InGates[5] = new Model("Pillar_G"); // R
	InGates[5]->Rot().y += 3.15f;
	InGates[5]->Pos().x += 430.0f;
	InGates[5]->Pos().z -= 56.5f;
	InGates[5]->Scale() *= 2.0f;
	
	InGates[6] = new Model("Pillar_G"); // L
	InGates[6]->Rot().y += 3.15f;
	InGates[6]->Pos().x += 430.0f;
	InGates[6]->Pos().z += 56.5f;
	InGates[6]->Scale() *= 2.0f;



	for (int i = 1; i < Gates.size(); ++i) Gates[i]->SetParent(Gates[0]);
	for (int i = 0; i < Walls_L.size(); ++i) Walls_L[i]->SetParent(Gates[0]);
	Walls_LF->SetParent(Gates[0]);
	for (int i = 0; i < Walls_R.size(); ++i) Walls_R[i]->SetParent(Gates[0]);
	Walls_RF->SetParent(Gates[0]);
	for (int i = 0; i < Walls_B.size(); ++i) Walls_B[i]->SetParent(Gates[0]);
	for (int i = 0; i < InGates.size(); ++i) InGates[i]->SetParent(Gates[0]);

	Gates[0]->Pos().y += 75.0f;
	for (int i = 0; i < Walls_L.size(); ++i) Walls_L[i]->Pos().y -= 75.0f;
	Walls_LF->Pos().y -= 75.0f;
	for (int i = 0; i < Walls_R.size(); ++i) Walls_R[i]->Pos().y -= 75.0f;
	Walls_RF->Pos().y -= 75.0f;
	for (int i = 0; i < Walls_B.size(); ++i) Walls_B[i]->Pos().y -= 75.0f;
	for (int i = 0; i < InGates.size(); ++i) InGates[i]->Pos().y -= 75.0f;

	Gates[0]->Scale() *= 0.166f;
	Gates[0]->Pos().y -= 62.5f;
	Gates[0]->Pos().x += 45.0f;
	Gates[0]->Pos().z += 50.0f;
	Gates[0]->Rot().y -= 1.575f;
}

Dungeon::~Dungeon()
{
	//delete terrain;

	for (int i = 0; i < 4; ++i) delete Gates[i];

	for (int i = 0; i < Walls_L.size(); ++i) delete Walls_L[i];
	delete Walls_LF;
	for (int i = 0; i < Walls_R.size(); ++i) delete Walls_R[i];
	delete Walls_RF;
	for (int i = 0; i < Walls_R.size(); ++i) delete Walls_B[i];

	for (int i = 0; i < InGates.size(); ++i) delete InGates[i];
}

void Dungeon::Update()
{
	//terrain->UpdateWorld();

	for (int i = 0; i < Gates.size(); ++i) Gates[i]->UpdateWorld();
	if (open) DoorMove();
	if (open_I) DoorMove_I();

	for (int i = 0; i < Walls_L.size(); ++i) 
	{
		Walls_L[i]->UpdateWorld();
		boxColliders_WL[i]->UpdateWorld();
	}
	Walls_LF->UpdateWorld();
	for (int i = 0; i < Walls_R.size(); ++i) 
	{
		Walls_R[i]->UpdateWorld();
		boxColliders_WR[i]->UpdateWorld();
	} 
	Walls_RF->UpdateWorld();
	for (int i = 0; i < Walls_B.size(); ++i) 
	{
		Walls_B[i]->UpdateWorld();
		boxColliders_WB[i]->UpdateWorld();
	}

	for (int i = 0; i < InGates.size(); ++i) InGates[i]->UpdateWorld();

	if (!KEY_PRESS(VK_RBUTTON))
	{
		//if (KEY_PRESS(VK_LEFT)) terrain->Pos().z += 50 * DELTA;
		//if (KEY_PRESS(VK_RIGHT)) terrain->Pos().z -= 50 * DELTA;
		//if (KEY_PRESS(VK_UP)) terrain->Pos().x += 50 * DELTA;
		//if (KEY_PRESS(VK_DOWN)) terrain->Pos().x -= 50 * DELTA;
	}

	boxCollider_G->UpdateWorld();
	boxCollider_GL->UpdateWorld();
	boxCollider_GR->UpdateWorld();
	boxCollider_GD->UpdateWorld();
	boxCollider_GP->UpdateWorld();
	boxCollider_GPI->UpdateWorld();
	boxCollider_S->UpdateWorld();
	boxCollider_SI->UpdateWorld();
	boxCollider_SIC->UpdateWorld();
	boxCollider_SIL->UpdateWorld();
	boxCollider_SIR->UpdateWorld();

	boxCollider_DL->UpdateWorld();
	boxCollider_DR->UpdateWorld();

	boxCollider_WLF->UpdateWorld();
	boxCollider_WRF->UpdateWorld();
	boxCollider_WGL->UpdateWorld();
	boxCollider_WGR->UpdateWorld();
	
}

void Dungeon::Render()
{
	//terrain->Render();

	for (int i = 0; i < Gates.size(); ++i) Gates[i]->Render();

	for (int i = 0; i < Walls_L.size(); ++i) 
	{
		Walls_L[i]->Render();
		boxColliders_WL[i]->Render();
	}
	Walls_LF->Render();
	for (int i = 0; i < Walls_R.size(); ++i) 
	{
		Walls_R[i]->Render();
		boxColliders_WR[i]->Render();
	} 
	Walls_RF->Render();
	for (int i = 0; i < Walls_B.size(); ++i) 
	{
		Walls_B[i]->Render();
		boxColliders_WB[i]->Render();
	} 

	for (int i = 0; i < InGates.size(); ++i) InGates[i]->Render();

	boxCollider_G->Render();
	boxCollider_GL->Render();
	boxCollider_GR->Render();
	boxCollider_GD->Render();
	boxCollider_GP->Render();
	boxCollider_GPI->Render();
	boxCollider_S->Render();
	boxCollider_SI->Render();
	boxCollider_SIC->Render();
	boxCollider_SIL->Render();
	boxCollider_SIR->Render();
	
	boxCollider_DL->Render();
	boxCollider_DR->Render();

	boxCollider_WLF->Render();
	boxCollider_WRF->Render();
	boxCollider_WGL->Render();
	boxCollider_WGR->Render();
}

bool Dungeon::IsCollision(Collider* c)
{
	if (boxCollider_GP->PushCollision(c)) return true;
	if (boxCollider_S->PushCollision(c)) return true;
	if (boxCollider_SI->PushCollision(c)) return true;
	if (boxCollider_SIC->PushCollision(c)) return true;
	if (boxCollider_SIL->PushCollision(c)) return true;
	if (boxCollider_SIR->PushCollision(c)) return true;

	return false;
}

void Dungeon::DoorMove()
{
	if (Gates[5]->Pos().y <= 15.5f) 
	{
		Gates[5]->Pos().y += 5 * DELTA;
		boxCollider_GD->Pos().y += 0.01 * DELTA;
	} 

	if (Gates[5]->Pos().y > 15.5f)
	{
		Gates[5]->Pos().y = 15.5f;
		boxCollider_GD->Pos().y = 2.5f;
		open = true;
	}
	return;
}

void Dungeon::DoorMove_I()
{
	for (int i = 3; i < Gates.size(); ++i)
	{
		if (InGates[3]->Pos().z >= -40.0f)
		{
			InGates[3]->Pos().z -= 5.0f * DELTA;
		}
		if (InGates[3]->Rot().y < 1.575f)
		{
			InGates[3]->Rot().y += 0.5f * DELTA;
		}
		
		if (InGates[4]->Pos().z <= 40.0f)
		{
			InGates[4]->Pos().z += 5.0f * DELTA;
		}
		if (InGates[4]->Rot().y > -1.575f)
		{
			InGates[4]->Rot().y -= 0.5f * DELTA;
		}
	}
	return;
}
