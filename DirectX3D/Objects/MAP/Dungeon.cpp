#include "Framework.h"
#include "Dungeon.h"

Dungeon::Dungeon()
{
	terrain = new Terrain();


	Gates.resize(6);
	Gates[0] = new Model("Gate");

	Gates[1] = new Model("Gate_Prop");
	Gates[1]->Pos().y -= 75.0f;
	Gates[1]->Pos().x -= 38.0f;

	Gates[2] = new Model("Gate_Prop");
	Gates[2]->Rot().y += 3.15f;
	Gates[2]->Pos().y -= 85.5f;
	Gates[2]->Pos().x += 49.5f;


	Gates[3] = new Model("Gate_Stairs2");
	Gates[3]->Pos().y -= 70.0f;
	Gates[3]->Pos().x -= 127.5f;

	Gates[4] = new Model("Gate_Stairs");
	Gates[4]->Rot().y += 3.15f;
	Gates[4]->Pos().y -= 70.0f;
	Gates[4]->Pos().x += 140.0f;
	
	Gates[5] = new Model("Gate_Door");
	Gates[5]->Scale() *= 9.0f;
	Gates[5]->Pos().y -= 20.5f; // close

	for (int i = 0; i < Gates.size(); ++i) Gates[i]->Pos().y += 75.0f;



	Walls_L.resize(8);
	for (int i = 0; i < Walls_L.size(); ++i) Walls_L[i] = new Model("Wall");
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



	Walls_R.resize(8);
	for (int i = 0; i < Walls_R.size(); ++i) Walls_R[i] = new Model("Wall");
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


	Walls_B.resize(4);
	for (int i = 0; i < Walls_B.size(); ++i) Walls_B[i] = new Model("Wall");
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
}

Dungeon::~Dungeon()
{
	for(int i = 0 ; i < 4; ++i) delete Gates[i];

	for (int i = 0; i < Walls_L.size(); ++i) delete Walls_L[i];
	delete Walls_LF;
	for (int i = 0; i < Walls_R.size(); ++i) delete Walls_R[i];
	delete Walls_RF;
	for (int i = 0; i < Walls_R.size(); ++i) delete Walls_B[i];
}

void Dungeon::Update()
{
	terrain->UpdateWorld();

	for (int i = 0; i < Gates.size(); ++i) Gates[i]->UpdateWorld();
	if (open) DoorMove();

	for (int i = 0; i < Walls_L.size(); ++i) Walls_L[i]->UpdateWorld();
	Walls_LF->UpdateWorld();
	for (int i = 0; i < Walls_R.size(); ++i) Walls_R[i]->UpdateWorld();
	Walls_RF->UpdateWorld();
	for (int i = 0; i < Walls_B.size(); ++i) Walls_B[i]->UpdateWorld();
}

void Dungeon::Render()
{
	terrain->Render();

	for (int i = 0; i < Gates.size(); ++i) Gates[i]->Render();

	for (int i = 0; i < Walls_L.size(); ++i) Walls_L[i]->Render();
	Walls_LF->Render();
	for (int i = 0; i < Walls_R.size(); ++i) Walls_R[i]->Render();
	Walls_RF->Render();
	for (int i = 0; i < Walls_B.size(); ++i) Walls_B[i]->Render();
}

void Dungeon::DoorMove()
{
	if (Gates[5]->Pos().y <= 95.5f) Gates[5]->Pos().y += 5 * DELTA;

	if (Gates[5]->Pos().y > 95.5f)
	{
		Gates[5]->Pos().y = 95.5f;
		open = true;
	}
}
