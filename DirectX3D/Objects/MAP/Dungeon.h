#pragma once
class Dungeon : public Transform
{
public:
	Dungeon();
	~Dungeon();

	void Update();
	void Render();

	bool OpenDoor(bool bol) { return open = bol; }
	bool OpenDoor_I(bool bol) { return open_I = bol; }
	bool IsClear(bool bol) { return isClear = bol; }
	//Vector3 terrainpos() { return terrain->Pos(); }
	Vector3 GetSpawnPoint_P() { return SpawnPoint_P; }
	bool IsCollision(Collider* c);

private:
	//Terrain* terrain;
	//Vector3 ThisPos = { 0, 0, 0 };

	vector<Model*> Gates;

	vector<Model*> Walls_L;
	Model* Walls_LF;

	vector<Model*> Walls_R;
	Model* Walls_RF;

	vector<Model*> Walls_B;

	Model* Walls_BL;
	Model* Walls_BR;
	Model* Portal;
	Model* Wall_deco;
	Model* IceWall;
	Model* IceWallL;
	Model* IceWallR;
	Model* IceWallC;
	vector<Model*> Ice_debris;
	Model* Ice_Broken;

	vector<Model*> Pillar;

	Model* Roof;
	Model* Roofi;
	SkyBox* skybox;
	//Model* TestSky;
	vector<Quad*> Tiles;
	vector<Quad*> Tiles2;
	vector<Quad*> Tiles3;
	Model* Grownd_Circle;

	vector<Model*> InGates;

	Vector3 SpawnPoint_P = {45.0f,0,10};
	vector<Vector3*> SpawnPoint_A;

	void DoorMove();
	void DoorMove_I();
	void CrashIceWall();
	bool open = false;
	bool open_I = false;
	bool isClear = false;

	BoxCollider* boxCollider_G;
	BoxCollider* boxCollider_GL;
	BoxCollider* boxCollider_GR;
	BoxCollider* boxCollider_GD;
	BoxCollider* boxCollider_GP;
	BoxCollider* boxCollider_GPI;
	BoxCollider* boxCollider_S;
	BoxCollider* boxCollider_SI;
	BoxCollider* boxCollider_SIC;
	BoxCollider* boxCollider_SIL;
	BoxCollider* boxCollider_SIR;

	BoxCollider* boxCollider_DL;
	BoxCollider* boxCollider_DR;
	BoxCollider* boxCollider_PR;
	BoxCollider* boxCollider_PL;

	BoxCollider* boxCollider_WLF;
	BoxCollider* boxCollider_WRF;
	BoxCollider* boxCollider_WGL;
	BoxCollider* boxCollider_WGR;
	vector<BoxCollider*> boxColliders_WL;
	vector<BoxCollider*> boxColliders_WR;
	vector<BoxCollider*> boxColliders_WB;
	BoxCollider* boxColliders_WD;
	vector<BoxCollider*> boxColliders_potal;
	BoxCollider* boxColliders_WBL;
	BoxCollider* boxColliders_WBR;
	vector<BoxCollider*> boxColliders_P;
	BoxCollider* boxColliders_B;
};