#pragma once
class BossMap : public Transform
{
public:
	BossMap();
	~BossMap();

	void Update();
	void Render();
	
	UINT SetPhase(UINT Num) { return PhaseNum = Num; }


private:
	UINT PhaseNum = 0;

	LastBossMap_Phase1* Phase1;
	LastBossMap_Phase2* Phase2;

};

