#pragma once
class PartyUI_Bar : public Transform
{
public:
	PartyUI_Bar();
	~PartyUI_Bar();

	void Update();
	void PostRender();

	void AddPlayer(int index);
	void SetHpPercent(float value, int index);

private:
	vector<ProgressBar*> hpBars;
};

