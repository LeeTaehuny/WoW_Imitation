#pragma once
class MonsterManager : public Singleton<MonsterManager>
{
private:
	friend class Singleton;

public:

	MonsterManager();
	~MonsterManager();

	void Update();
	void Render();

	void SetTarget(Collider* transform);

	void SpawnSkeleton(Vector3 pos);

	void HitCollider(Collider* collider);

private:
	// 스켈레톤의 인스턴싱
	ModelAnimatorInstancing* skeleton_body;
	// 스켈레톤 클래스
	vector<Skeleton*> skeleton;

	// 타겟들의 정보를 저장함
	vector<Collider*> targets;
};