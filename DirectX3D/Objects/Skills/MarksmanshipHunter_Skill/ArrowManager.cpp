#include "Framework.h"
#include "ArrowManager.h"

ArrowManager::ArrowManager()
{
	arrow_models = new ModelInstancing("arrow");

	FOR(30)
	{
		Arrow* aro = new Arrow(arrow_models->Add());

		arrows.push_back(aro);
		arrows[i]->SetActive(false);
	}
}

ArrowManager::~ArrowManager()
{
	delete arrow_models;

	for (Arrow* tra : arrows)
		delete tra;
}

void ArrowManager::Update()
{
	arrow_models->Update();
}

void ArrowManager::Render()
{
	arrow_models->Render();
}

Arrow* ArrowManager::GetActiveArrow()
{
	for (int i = 0; i < arrows.size(); ++i)
	{
		if (!arrows[i]->GetIsRun())
		{
			arrows[i]->SetIsRun(true);
			return arrows[i];
		}
	}

	// 사용 가능한 화살이 없다면 새롭게 만듬
	Arrow* aro = new Arrow(arrow_models->Add());
	aro->SetActive(false);
	aro->SetIsRun(false);
	arrows.push_back(aro);
	return arrows[arrows.size() - 1];
}