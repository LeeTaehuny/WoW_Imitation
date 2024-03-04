#pragma once
class Guild : public Transform
{
public:
	Guild();
	~Guild();

	void Update();
	void Render();
	void UIRender();
	void GUIRender();

private:
	void Control();

// Models
private:
	Model* guild;
	Model* trader;

	RasterizerState* rs[2];

// UI
private:
	class Quad* guildFrame;
	vector<class Quad*> icons;

};

