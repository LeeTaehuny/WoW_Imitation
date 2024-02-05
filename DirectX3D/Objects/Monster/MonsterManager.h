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
	void SpawnSkeletonKnight(Vector3 pos);

public:
	// 몬스터들의 콜라이더 정보를 저장함
	vector<Collider*> monsterCollider;

	// 플레이어 캐릭터들의 정보를 저장함
	vector<Collider*> targets;
private:
	// 스켈레톤의 인스턴싱
	ModelAnimatorInstancing* skeleton_body;
	// 스켈레톤 클래스
	vector<Skeleton*> skeleton;

	// 스켈레톤 나이트의 인스턴싱
	ModelAnimatorInstancing* skeletonKnight_body;
	// 스켈레톤 나이트 클래스
	vector<Skeleton_Knight*> skeleton_Knight;

};