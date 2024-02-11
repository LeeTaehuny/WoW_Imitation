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
	//Vector3 terrainpos() { return terrain->Pos(); }
	Vector3 GetSpawnPoint_P() { return SpawnPoint_P; }
	bool IsCollision(Collider* c);

private:
	//Terrain* terrain;
	Vector3 ThisPos = { 0, 0, 0 };

	vector<Model*> Gates;

	vector<Model*> Walls_L;
	Model* Walls_LF;

	vector<Model*> Walls_R;
	Model* Walls_RF;

	vector<Model*> Walls_B;

	Model* Roof;

	vector<Model*> InGates;
	Model* NextDoor;

	Vector3 SpawnPoint_P = {45.0f,0,10};
	vector<Vector3*> SpawnPoint_A;

	void DoorMove();
	void DoorMove_I();
	bool open = false;
	bool open_I = false;

	BoxCollider* boxCollider_G;
	BoxCollider* boxCollider_GP;
	BoxCollider* boxCollider_GPI;
	BoxCollider* boxCollider_S;
	BoxCollider* boxCollider_SI;
	BoxCollider* boxCollider_SIC;
	BoxCollider* boxCollider_SIL;
	BoxCollider* boxCollider_SIR;

	BoxCollider* boxCollider_WLF;
	BoxCollider* boxCollider_WRF;
	BoxCollider* boxCollider_WGL;
	BoxCollider* boxCollider_WGR;
	vector<BoxCollider*> boxColliders_WL;
	vector<BoxCollider*> boxColliders_WR;
	vector<BoxCollider*> boxColliders_WB;
};