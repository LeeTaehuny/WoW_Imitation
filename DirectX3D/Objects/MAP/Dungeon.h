#pragma once
class Dungeon : public Transform
{
public:
	Dungeon();
	~Dungeon();

	void Update();
	void Render();
	void GUIRender();

	bool OpenDoor(bool bol) { return open = bol; }
	bool OpenDoor_I(bool bol) { return open_I = bol; }
	bool IsClear(bool bol) { return isClear = bol; }

	Vector3 GetSpawnPoint_P() { return SpawnPoint_P; }

	bool IsCollision(Collider* c);
	bool PotalCollision(Collider* c);

	vector<Vector3> SpawnMonsters_A()
	{
		vector<Vector3> spawnPoints;

		for (int i = 0; i < SpawnPoint_A.size(); ++i)
		{
			spawnPoints.push_back(SpawnPoint_A[i]);
		}

		return spawnPoints;
	}
	vector<Vector3> SpawnMonsters_B()
	{
		vector<Vector3> spawnPoints;

		for (int i = 0; i < SpawnPoint_B.size(); ++i)
		{
			spawnPoints.push_back(SpawnPoint_B[i]);
		}

		return spawnPoints;
	}

private:
	//Terrain* terrain;
	TerrainLOD* terrain;

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
	vector<Model*> Tree;

	Model* Roof;
	Model* Roofi;
	SkyBox* skybox;
	//Model* TestSky;

	Model* Chandelier;
	LightBuffer::Light* light;
	TestLight* Lamp;
	SphereCollider* TestPos;

	vector<Quad*> Tiles;
	vector<Quad*> Tiles2;
	vector<Quad*> Tiles3;
	Model* Grownd_Circle;

	vector<Model*> InGates;

	Vector3 SpawnPoint_P = {45,0,10};
	vector<Vector3> SpawnPoint_A;
	vector<Vector3> SpawnPoint_B;

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
	SphereCollider* PotalCollider;
	BoxCollider* boxColliders_B;
	vector<BoxCollider*> boxColliders_Tree;

	int n = 0;
	int n1 = 0;
};