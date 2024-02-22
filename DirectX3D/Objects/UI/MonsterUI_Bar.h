#pragma once
class MonsterUI_Bar : public Transform
{
public:
	MonsterUI_Bar();
	~MonsterUI_Bar();

	void Update();
	void PostRender();

	void SetHpPercent(float value);

private:
	ProgressBar* hpBar;
	Quad* frame;
};

