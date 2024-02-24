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
    void PostRender();
    void GUIRender();

    // 스켈레톤 스폰
    void SpawnSkeleton(Vector3 pos);
    // 스켈레톤 나이트 스폰
    void SpawnSkeletonKnight(Vector3 pos);
    // 허수아비 스폰
    void SpawnScarecrow(Vector3 pos);
    // 발키리 스폰
    void SpawnVAlkier(Vector3 pos);
    // 얼음구슬 스폰
    void SpawnIceBall(Vector3 pos);
    // 리치왕 스폰
    void SpawnBoss(Vector3 pos);

    MonsterBase* hitCollision(IN Collider* collider);

// Getter & Setter
public:
    // 지금 필드에 있는 플레이어 캐릭터들의 모든 콜라이더 정보를 저장함
    void SetTarget(CH_Base_ver2* transform);
    vector<MonsterBase*> GetSkeleton() { return skeleton; }
    vector<MonsterBase*> GetSkeleton_Knight() { return skeleton_Knight; }
    vector<MonsterBase*> GetScarecrow() { return scarecrow; }
    vector<MonsterBase*> GetVAlkier() { return valkier; }
    vector<MonsterBase*> GetIceBall() { return valkier; }

    MonsterBase* GetBoss() { return lichKimg; }

public:
    // 몬스터들의 콜라이더 정보를 저장함
    //vector<Collider*> monsterCollider;

    // 플레이어 캐릭터들의 정보를 저장함
    vector<CH_Base_ver2*> targets;
private:
    // 스켈레톤의 인스턴싱
    ModelAnimatorInstancing* skeleton_body;
    // 스켈레톤 클래스
    vector<MonsterBase*> skeleton;

    // 스켈레톤 나이트의 인스턴싱
    ModelAnimatorInstancing* skeletonKnight_body;
    // 스켈레톤 나이트 클래스
    vector<MonsterBase*> skeleton_Knight;

    // 허수아비 인스턴싱 (스켈레톤 나이트로 대체)
    ModelAnimatorInstancing* scarecrow_body;
    // 스켈레톤 나이트 클래스
    vector<MonsterBase*> scarecrow;

    // 발키리 인스턴싱
    ModelAnimatorInstancing* valkier_body;
    // 발키리 클래스
    vector<MonsterBase*> valkier;

    // 아이스볼 클래스
    vector<MonsterBase*> iceBall;

    class MonsterBase* lichKimg;
};