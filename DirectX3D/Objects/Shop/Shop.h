#pragma once

class Shop : public Transform
{
public:
	Shop();
	~Shop();

	void Update();
	void Render();
	void UIRender();
	void GUIRender();

public:


// Models
private:
	Model* shop;
	Model* trader;

	RasterizerState* rs[2];

// UI
private:
	int MAX_COUNT = 28;				// 판매 칸 수
	class Slot* shopFrame;			// 상점 프레임
	vector<class Slot*> items;
};

