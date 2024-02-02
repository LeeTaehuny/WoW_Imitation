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
	int MAX_COUNT = 28;				// �Ǹ� ĭ ��
	class Slot* shopFrame;			// ���� ������
	vector<class Slot*> items;
};

