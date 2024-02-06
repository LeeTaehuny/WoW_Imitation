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

	// 지금 필드에 있는 플레이어 캐릭터들의 모든 콜라이더 정보를 저장함
	void SetTarget(Collider* transform);

	// 스켈레톤 스폰
	void SpawnSkeleton(Vector3 pos);
	// 스켈레톤 나이트 스폰
	void SpawnSkeletonKnight(Vector3 pos);
	// 허수아비 스폰
	void SpawnScarecrow(Vector3 pos);

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

	// 허수아비 인스턴싱 (스켈레톤 나이트로 대체)
	ModelAnimatorInstancing* scarecrow_body;
	// 스켈레톤 나이트 클래스
	vector<Scarecrow*> scarecrow;
};