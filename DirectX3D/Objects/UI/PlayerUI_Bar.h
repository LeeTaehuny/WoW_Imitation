#pragma once
class PlayerUI_Bar : public Transform
{
public:
	PlayerUI_Bar(wstring IconImageFile);
	~PlayerUI_Bar();

	void Update();
	void PostRender();

	void SetHpPercent(float value);
	void SetMpPercent(float value);

private:
	ProgressBar* hpBar;
	ProgressBar* mpBar;
	Quad* frame;
	Quad* icon;
};

