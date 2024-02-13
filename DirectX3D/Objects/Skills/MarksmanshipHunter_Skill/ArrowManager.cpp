#include "Framework.h"
#include "ArrowManager.h"

ArrowManager::ArrowManager()
{
	arrow_models = new ModelInstancing("arrow");

	FOR(30)
	{
		arrow.push_back(arrow_models->Add());
		arrow[i]->SetActive(false);
	}
}

ArrowManager::~ArrowManager()
{
	delete arrow_models;

	for (Transform* tra : arrow)
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

Transform* ArrowManager::GetActiveArrow()
{
	for (int i = 0; i < arrow.size(); ++i)
	{
		if (!arrow[i]->Active())
		{
			return arrow[i];
		}
	}

	return nullptr;
}