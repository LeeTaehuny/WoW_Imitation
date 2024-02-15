#include "Framework.h"
#include "Dungeon.h"

Dungeon::Dungeon() //: Transform()
{
	//terrain = new Terrain();
	//terrain->Rot().x = 0.0f;
	//terrain->Rot().y = 0.0f;
	//terrain->Rot().z = 0.0f;

	//skybox = new SkyBox(L"Textures/Landscape/BlueSky.dds");
	//skybox->UpdateWorld();

	Tiles.resize(98);
	float xgap = 6.0f;
	float zgap = 6.0f;
	float Xcurrent = 29.0f;
	float Zcurrent = 53.0f;
	for (int i = 0; i < Tiles.size(); ++i)
	{
		Tiles[i] = new Quad(L"Textures/Landscape/Tile_Dungeon.png");
		Tiles[i]->Scale() *= 0.0235f;
		Tiles[i]->Rot().x += 1.57f;

		Tiles[i]->Pos().x = Xcurrent;
		Tiles[i]->Pos().z = Zcurrent;

		Xcurrent += xgap;

		if ((i + 1) % 7 == 0)
		{
			Xcurrent = 29.0f;
			Zcurrent += zgap;
		}
	}

	Tiles2.resize(169);
	Xcurrent = 9;
	Zcurrent = 132;
	for (int i = 0; i < Tiles2.size(); ++i)
	{
		Tiles2[i] = new Quad(L"Textures/Landscape/Tile_Dungeon.png");
		Tiles2[i]->Scale() *= 0.0235f;
		Tiles2[i]->Rot().x += 1.57f;

		Tiles2[i]->Pos().x = Xcurrent;
		Tiles2[i]->Pos().z = Zcurrent;

		Xcurrent += xgap;

		if ((i + 1) % 13 == 0)
		{
			Xcurrent = 9.0f;
			Zcurrent += zgap;
		}
	}
	Tiles3.resize(21);
	Xcurrent = 27;
	Zcurrent = 210;
	for (int i = 0; i < Tiles3.size(); ++i)
	{
		Tiles3[i] = new Quad(L"Textures/Landscape/Tile_Dungeon2.png");
		Tiles3[i]->Scale() *= 0.0235f;
		Tiles3[i]->Rot().x += 1.57f;

		Tiles3[i]->Pos().x = Xcurrent;
		Tiles3[i]->Pos().z = Zcurrent;

		Xcurrent += xgap;

		if ((i + 1) % 7 == 0)
		{
			Xcurrent = 27.0f;
			Zcurrent += zgap;
		}
	}

	//Roof = new Model("Roof");
	//Roof->Pos().y += 100;
	//Roof->Pos().z += 100;
	//Roof->Pos().x += 100;


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
	Walls_B[1]->Pos().x += 117.5;
	Walls_B[2]->Pos().x += 117.5;
	
	Walls_BL = new Model("Wall");
	Walls_BL->Rot().y += 1.575f;
	Walls_BL->Pos().y += 10.0f;
	Walls_BL->Pos().x += 993.0f;
	Walls_BL->Pos().z += 137.5f;
	Walls_BR = new Model("Wall");
	Walls_BR->Rot().y -= 1.575f;
	Walls_BR->Pos().y += 10.0f;
	Walls_BR->Pos().x += 993.0f;
	Walls_BR->Pos().z -= 130.5f;

	boxColliders_WBL = new BoxCollider(Vector3(35, 150, 120));
	boxColliders_WBL->SetParent(Walls_BL);
	boxColliders_WBR = new BoxCollider(Vector3(35, 150, 120));
	boxColliders_WBR->SetParent(Walls_BR);
	

	//////////////////////////////////////////////////
	Portal = new Model("Portal");
	Portal->Pos().x += 1005;
	Portal->Pos().y -= 7.0;
	Portal->Scale() *= 6;
	boxColliders_potal.resize(2);
	for (int i = 0; i < boxColliders_potal.size(); ++i) 
	{
		boxColliders_potal[i] = new BoxCollider(Vector3(3.5, 5, 6.5));
		boxColliders_potal[i]->SetParent(Portal);
	}
	boxColliders_potal[0]->Pos().z += 7.0; // L
	boxColliders_potal[0]->Rot().x -= 1.0f;
	boxColliders_potal[0]->Pos().y += 3.0f;
	boxColliders_potal[1]->Pos().z -= 7.0; // R
	boxColliders_potal[1]->Rot().x += 1.0f;
	boxColliders_potal[1]->Pos().y += 3.0f;

	Wall_deco = new Model("Wall_deco");
	Wall_deco->Rot().y += 3.15f;
	Wall_deco->Pos().x += 1042.5;
	Wall_deco->Scale() *= 6;
	boxColliders_WD = new BoxCollider(Vector3(2.5, 10, 2.5));
	boxColliders_WD->Pos().y += 5;
	boxColliders_WD->SetParent(Wall_deco);

	Pillar.resize(6);
	boxColliders_P.resize(6);
	for (int i = 0; i < Pillar.size(); ++i) 
	{
		Pillar[i] = new Model("Pillar");
		boxColliders_P[i] = new BoxCollider(Vector3(3.75, 10, 3.75));
		boxColliders_P[i]->Pos().y += 5;
		boxColliders_P[i]->SetParent(Pillar[i]);
		Pillar[i]->Scale() *= 10.0;
	}
	Pillar[0]->Pos().x += 825;
	Pillar[0]->Pos().z -= 150;
	Pillar[1]->Pos().x += 700;
	Pillar[1]->Pos().z -= 150;
	Pillar[2]->Pos().x += 575;
	Pillar[2]->Pos().z -= 150;

	Pillar[3]->Pos().x += 825;
	Pillar[3]->Pos().z += 150;
	Pillar[4]->Pos().x += 700;
	Pillar[4]->Pos().z += 150;
	Pillar[5]->Pos().x += 575;
	Pillar[5]->Pos().z += 150;

	Grownd_Circle = new Model("Grownd_Circle");
	Grownd_Circle->Pos().x += 762.5;
	Grownd_Circle->Pos().y -= 3.5;
	Grownd_Circle->Scale() *= 10.0;

	IceWall = new Model("IceWall");
	IceWall->Pos().x += 955.0;
	IceWall->Scale() *= 10.0;

	IceWallL = new Model("IceWall2");//L
	IceWallL->Pos().x += 910.0;
	IceWallL->Pos().z += 150;
	IceWallL->Scale() *= 6.0;

	IceWallR = new Model("IceWall2");//R
	IceWallR->Pos().x += 910.0;
	IceWallR->Pos().z -= 150;
	IceWallR->Scale() *= 6.0;

	IceWallC = new Model("IceWall3");
	IceWallC->Rot().y += 1.575f;
	IceWallC->Pos().x += 915.0;
	IceWallC->Scale() *= 3.0;

	boxColliders_B = new BoxCollider(Vector3(17.5, 25, 47.5));
	boxColliders_B->Pos().y += 12.0;
	boxColliders_B->SetParent(IceWall);

	Ice_debris.resize(12);
	Ice_debris[0] = new Model("Ice_debris1");	// 얼음파편 입니다
	Ice_debris[1] = new Model("Ice_debris2");
	Ice_debris[2] = new Model("Ice_debris3");
	Ice_debris[3] = new Model("Ice_debris4");
	Ice_debris[4] = new Model("Ice_debris1");	
	Ice_debris[5] = new Model("Ice_debris2");
	Ice_debris[6] = new Model("Ice_debris3");
	Ice_debris[7] = new Model("Ice_debris4");
	Ice_debris[8] = new Model("Ice_debris1");	
	Ice_debris[9] = new Model("Ice_debris2");
	Ice_debris[10] = new Model("Ice_debris3");
	Ice_debris[11] = new Model("Ice_debris4");
	for (int i = 0; i < 4; ++i) 
	{
		Ice_debris[i]->Pos().y += 580.0f;
		Ice_debris[i]->Pos().x += 955.0;
		Ice_debris[i]->Scale() *= 1.5f;
	}
	for (int i = 4; i < 8; ++i)
	{
		Ice_debris[i]->Pos().y += 530.0f;
		Ice_debris[i]->Pos().x += 955.0;
		Ice_debris[i]->Pos().z -=150;
		Ice_debris[i]->Scale() *= 1.5f;
	}
	for (int i = 8; i < 12; ++i)
	{
		Ice_debris[i]->Pos().y += 530.0f;
		Ice_debris[i]->Pos().x += 955.0;
		Ice_debris[i]->Pos().z += 150;
		Ice_debris[i]->Scale() *= 1.5f;
	}

	Ice_Broken = new Model("IceBroken");
	Ice_Broken->Pos().x += 955.0;
	Ice_Broken->Pos().y -= 5.0;
	Ice_Broken->Scale() *= 1.5f;

	//////////////////////////////////////////////

	InGates.resize(8);
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
	boxCollider_PR = new BoxCollider(Vector3(14.5, 37.5, 15));
	boxCollider_PR->SetParent(InGates[5]);
	boxCollider_PR->Pos().x -= 2.0f;
	boxCollider_PR->Pos().y += 17.5f;
	
	InGates[6] = new Model("Pillar_G"); // L
	InGates[6]->Rot().y += 3.15f;
	InGates[6]->Pos().x += 430.0f;
	InGates[6]->Pos().z += 56.5f;
	InGates[6]->Scale() *= 2.0f;
	boxCollider_PL = new BoxCollider(Vector3(14.5, 37.5, 15));
	boxCollider_PL->SetParent(InGates[6]);
	boxCollider_PL->Pos().x -= 2.0f;
	boxCollider_PL->Pos().y += 17.5f;

	InGates[7] = new Model("Door_deco");
	InGates[7]->Pos().x += 428.5f;
	InGates[7]->Pos().y += 75.0f;
	InGates[7]->Scale() *= 4.0f;



	for (int i = 1; i < Gates.size(); ++i) Gates[i]->SetParent(Gates[0]);
	for (int i = 0; i < Walls_L.size(); ++i) Walls_L[i]->SetParent(Gates[0]);
	Walls_LF->SetParent(Gates[0]);
	for (int i = 0; i < Walls_R.size(); ++i) Walls_R[i]->SetParent(Gates[0]);
	Walls_RF->SetParent(Gates[0]);
	for (int i = 0; i < Walls_B.size(); ++i) Walls_B[i]->SetParent(Gates[0]);
	Walls_BL->SetParent(Gates[0]);
	Walls_BR->SetParent(Gates[0]);
	Portal->SetParent(Gates[0]);
	Wall_deco->SetParent(Gates[0]);
	IceWall->SetParent(Gates[0]);
	IceWallL->SetParent(Gates[0]);
	IceWallR->SetParent(Gates[0]);
	IceWallC->SetParent(Gates[0]);
	for (int i = 0; i < Pillar.size(); ++i) Pillar[i]->SetParent(Gates[0]);
	Grownd_Circle->SetParent(Gates[0]);
	for (int i = 0; i < InGates.size(); ++i) InGates[i]->SetParent(Gates[0]);
	for (int i = 0; i < Ice_debris.size(); ++i) Ice_debris[i]->SetParent(Gates[0]);
	Ice_Broken->SetParent(Gates[0]);

	Gates[0]->Pos().y += 75.0f;
	for (int i = 0; i < Walls_L.size(); ++i) Walls_L[i]->Pos().y -= 75.0f;
	Walls_LF->Pos().y -= 75.0f;
	for (int i = 0; i < Walls_R.size(); ++i) Walls_R[i]->Pos().y -= 75.0f;
	Walls_RF->Pos().y -= 75.0f;
	for (int i = 0; i < Walls_B.size(); ++i) Walls_B[i]->Pos().y -= 75.0f;
	Walls_BL->Pos().y -= 75.0f;
	Walls_BR->Pos().y -= 75.0f;
	Portal->Pos().y -= 75.0f;
	Wall_deco->Pos().y -= 75.0f;
	IceWall->Pos().y -= 75.0f;
	IceWallL->Pos().y -= 75.0f;
	IceWallR->Pos().y -= 75.0f;
	IceWallC->Pos().y -= 75.0f;
	for (int i = 0; i < Pillar.size(); ++i) Pillar[i]->Pos().y -= 75.0f;
	Grownd_Circle->Pos().y -= 75.0f;
	for (int i = 0; i < InGates.size(); ++i) InGates[i]->Pos().y -= 75.0f;
	Ice_Broken->Pos().y -= 75.0f;

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

	for (int i = 0; i < Tiles.size(); ++i) Tiles[i]->UpdateWorld();
	for (int i = 0; i < Tiles2.size(); ++i) Tiles2[i]->UpdateWorld();
	for (int i = 0; i < Tiles3.size(); ++i) Tiles3[i]->UpdateWorld();

	//Roof->UpdateWorld();

	for (int i = 0; i < Gates.size(); ++i) Gates[i]->UpdateWorld();
	if (open) DoorMove();
	if (open_I) DoorMove_I();
	if (isClear) 
	{
		CrashIceWall();
	}
	if (!isClear)
	{
		IceWall->UpdateWorld();
		IceWallL->UpdateWorld();
		IceWallR->UpdateWorld();
		IceWallC->UpdateWorld();
		boxColliders_B->UpdateWorld();
	}

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
	Walls_BL->UpdateWorld();
	Walls_BR->UpdateWorld();
	Portal->UpdateWorld();
	Wall_deco->UpdateWorld();

	for (int i = 0; i < Pillar.size(); ++i) 
	{
		Pillar[i]->UpdateWorld();
		boxColliders_P[i]->UpdateWorld();
	}
	Grownd_Circle->UpdateWorld();
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
	boxCollider_PR->UpdateWorld();
	boxCollider_PL->UpdateWorld();

	boxColliders_WBL->UpdateWorld();
	boxColliders_WBR->UpdateWorld();
	boxCollider_WLF->UpdateWorld();
	boxCollider_WRF->UpdateWorld();
	boxCollider_WGL->UpdateWorld();
	boxCollider_WGR->UpdateWorld();

	boxColliders_WD->UpdateWorld();
	for (int i = 0; i < boxColliders_potal.size(); ++i) boxColliders_potal[i]->UpdateWorld();
}

void Dungeon::Render()
{
	//terrain->Render();

	for (int i = 0; i < Tiles.size(); ++i) Tiles[i]->Render();
	for (int i = 0; i < Tiles2.size(); ++i) Tiles2[i]->Render();
	for (int i = 0; i < Tiles3.size(); ++i) Tiles3[i]->Render();

	//skybox->Render();
	//Roof->Render();

	for (int i = 0; i < Gates.size(); ++i) Gates[i]->Render();

	for (int i = 0; i < Walls_L.size(); ++i) 
	{
		Walls_L[i]->Render();
		//boxColliders_WL[i]->Render();
	}
	Walls_LF->Render();
	for (int i = 0; i < Walls_R.size(); ++i) 
	{
		Walls_R[i]->Render();
		//boxColliders_WR[i]->Render();
	} 
	Walls_RF->Render();
	for (int i = 0; i < Walls_B.size(); ++i) 
	{
		Walls_B[i]->Render();
		//boxColliders_WB[i]->Render();
	}
	Walls_BL->Render();
	Walls_BR->Render();
	Portal->Render();
	Wall_deco->Render();
	if (!isClear)
	{
		IceWall->Render();
		IceWallL->Render();
		IceWallR->Render();
		IceWallC->Render();
	}
	for (int i = 0; i < Pillar.size(); ++i)
	{
		Pillar[i]->Render();
		//boxColliders_P[i]->Render();
	}
	Grownd_Circle->Render();
	for (int i = 0; i < InGates.size(); ++i) InGates[i]->Render();

	//boxCollider_G->Render();
	//boxCollider_GL->Render();
	//boxCollider_GR->Render();
	//boxCollider_GD->Render();
	//boxCollider_GP->Render();
	//boxCollider_GPI->Render();
	//boxCollider_S->Render();
	//boxCollider_SI->Render();
	//boxCollider_SIC->Render();
	//boxCollider_SIL->Render();
	//boxCollider_SIR->Render();
	//
	//boxCollider_DL->Render();
	//boxCollider_DR->Render();
	//boxCollider_PR->Render();
	//boxCollider_PL->Render();
	//boxCollider_WGL->Render();
	//boxCollider_WGR->Render();
	//
	//boxColliders_WBL->Render();
	//boxColliders_WBR->Render();
	//boxCollider_WLF->Render();
	//boxCollider_WRF->Render();
	//
	//boxColliders_WD->Render();
	//for (int i = 0; i < boxColliders_potal.size(); ++i) boxColliders_potal[i]->Render();
	//boxColliders_B->Render();
	if (isClear)
	{
		for (int i = 0; i < Ice_debris.size(); ++i) Ice_debris[i]->Render();
		Ice_Broken->Render();
	}
}

bool Dungeon::IsCollision(Collider* c)
{
	if (boxCollider_G->PushCollision(c)) return true;
	if (boxCollider_GP->PushCollision(c)) return true;
	if (boxCollider_GPI->PushCollision(c)) return true;
	if (boxCollider_GR->PushCollision(c)) return true;
	if (boxCollider_GL->PushCollision(c)) return true;
	if (boxCollider_GD->PushCollision(c)) return true;
	if (boxCollider_S->PushCollision(c)) return true;
	if (boxCollider_SI->PushCollision(c)) return true;
	if (boxCollider_SIC->PushCollision(c)) return true;
	if (boxCollider_SIL->PushCollision(c)) return true;
	if (boxCollider_SIR->PushCollision(c)) return true;
	
	if (boxCollider_WGL->PushCollision(c)) return true;
	if (boxCollider_WGR->PushCollision(c)) return true;
	if (boxCollider_DL->PushCollision(c)) return true;
	if (boxCollider_DR->PushCollision(c)) return true;
	if (boxCollider_PR->PushCollision(c)) return true;
	if (boxCollider_PL->PushCollision(c)) return true;

	for (int i = 0; i < Walls_L.size(); ++i)
	{
		if (boxColliders_WL[i]->PushCollision(c)) return true;
	}
	if (boxCollider_WLF->PushCollision(c)) return true;
	for (int i = 0; i < Walls_R.size(); ++i)
	{
		if (boxColliders_WR[i]->PushCollision(c)) return true;
	}
	if (boxCollider_WRF->PushCollision(c)) return true;
	for (int i = 0; i < Walls_B.size(); ++i)
	{
		if (boxColliders_WB[i]->PushCollision(c)) return true;
	}
	if (boxColliders_WBL->PushCollision(c)) return true;
	if (boxColliders_WBR->PushCollision(c)) return true;
	for (int i = 0; i < Pillar.size(); ++i) 
	{
		if (boxColliders_P[i]->PushCollision(c)) return true;
	}
	if (boxColliders_WD->PushCollision(c)) return true;
	for (int i = 0; i < boxColliders_potal.size(); ++i) 
	{
		if (boxColliders_potal[i]->PushCollision(c)) return true;
	}
	if (boxColliders_B->PushCollision(c)) return true;

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

void Dungeon::CrashIceWall()
{
	IceWall->SetActive(false);
	IceWallL->SetActive(false);
	IceWallR->SetActive(false);
	IceWallC->SetActive(false);
	boxColliders_B->SetActive(false);

	for (int i = 0; i < Ice_debris.size(); ++i) Ice_debris[i]->UpdateWorld();
	Ice_Broken->UpdateWorld();

	for (int i = 0; i < Ice_debris.size(); ++i) 
	{
		if (Ice_debris[i]->Pos().y > 390.0) 
		{
			Ice_debris[i]->Pos().y -= 150 * DELTA;
		}
	}
	
}
