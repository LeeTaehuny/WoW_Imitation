#pragma once
class Dungeon : public Transform
{
public:
	Dungeon();
	~Dungeon();

	void Update();
	void Render();

private:
	Model* m1;
	vector<Model*> ms;
};