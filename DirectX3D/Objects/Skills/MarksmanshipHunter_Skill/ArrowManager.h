#pragma once

#define ARROW ArrowManager::Get()
class ArrowManager : public Singleton<ArrowManager>
{
	friend class Singleton;

public:
	ArrowManager();
	~ArrowManager();

	void Update();
	void Render();

	// 혹시 모를 벡터 겟터 함수
	vector<Transform*> GetArrow() { return arrow; }

	// 현재 활성화된 화살의 트랜스폼을 받아오기 위한 함수
	Transform* GetActiveArrow();

private:
	ModelInstancing* arrow_models;

	vector<Transform*> arrow;
};