#pragma once
class Dungeon : public Transform
{
public:
	Dungeon();
	~Dungeon();

	void Update();
	void Render();

	bool OpenDoor(bool bol) { return open = bol; }

private:
	Terrain* terrain;

	vector<Model*> Gates;

	vector<Model*> Walls_L;
	Model* Walls_LF;

	vector<Model*> Walls_R;
	Model* Walls_RF;

	vector<Model*> Walls_B;

	void DoorMove();

	bool open = false;
};