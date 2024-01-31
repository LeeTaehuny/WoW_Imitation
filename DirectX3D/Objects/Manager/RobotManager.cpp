#include "Framework.h"

RobotManager::RobotManager()
{
    //인스턴싱 (의 공통 모델) 생성
    robotInstancing = new ModelAnimatorInstancing("Robot");
    robotInstancing->ReadClip("StandUp");
    robotInstancing->ReadClip("Walk");
    robotInstancing->ReadClip("Run");
    robotInstancing->ReadClip("Hit");
    robotInstancing->ReadClip("Dying");

    //로봇 인스턴스 만들어서 인스턴싱과 연결
    FOR(SIZE)
    {
        Transform* transform = robotInstancing->Add(); // 인스턴싱에서 트랜스폼을 추가한 후 매니저에서도 할당
        transform->SetActive(false); // 아직 게임 내에서 생성을 거친 게 아니라 활성화는 안 함
        Robot* robot = new Robot(transform, robotInstancing, i); //내부 인덱스 i번째, 모델은 인스턴싱을 통해 공유하는 로봇 생성
        robots.push_back(robot); //벡터에 윗줄에서 만든 로봇 추가
    }
}

RobotManager::~RobotManager()
{
    delete robotInstancing;

    for (Robot* robot : robots)
        delete robot;
}

void RobotManager::Update()
{
    //충돌 판정부터 진행
    Collision();

    //시간 경과를 체크
    time += DELTA;

    if (time >= SPAWN_TIME) //시간이 생성 간격에 도달하면
    {
        time -= SPAWN_TIME; // time이 오차 발생시 오차를 무시하고 재생성 간격을 우선
                            // -> 장 : 대체로 시간 간격을 유지 가능 / 단 : 오차가 간헐적일 경우 불규칙한 재생성(일찍 생성)
        // time = 0;        // time이 오차 발생시 간격을 무시하고 오차 교정을 우선
                            // -> 장 : 규칙적인 생성 환경을 유지 가능 / 단점 : 시간 간격이 벌어질 위험이 있다
        Spawn(); //재생성
    }

    //모델 자체를 업데이트
    robotInstancing->Update();

    //로봇의 객체들도 업데이트 (객체 : 설계도로서의 클래스 + 결과물로서의 인스턴스의 총칭.)
    for (Robot* robot : robots)
        robot->Update();
}

void RobotManager::Render()
{
    robotInstancing->Render();

    for (Robot* robot : robots)
        robot->Render();
}

void RobotManager::PostRender()
{
    for (Robot* robot : robots)
        robot->PostRender();
}

void RobotManager::SetTarget(Transform* target)
{
    this->target = target; // 매니저에서 표적을 우선 저장

    for (Robot* robot : robots)
        robot->SetTarget(target); // 로봇 하나하나의 표적도 지정

}

bool RobotManager::IsCollision(Ray ray, Vector3& hitPoint)
{
    // 외부에서 데이터가 왔을 때의 충돌
    // 외부 데이터 : 마우스 클릭, 화면을 통한 플레이어의/플레이어로의 공격
    //              + 매니저나 씬에서 지정되지 않은 광선에 의한 충돌

    Contact contact;
    float minDistance = FLT_MAX;

    for (Robot* robot : robots)
    {
        // 로봇 충돌체와 광선 간 충돌 여부를 판별해서
        if (robot->GetCollider()->IsRayCollision(ray, &contact))
        {
            //광선이 충돌했고 접점의 거리도 갱신을 거듭해서
            if (contact.distance < minDistance)
            {
                //해당 접점의 정보를 밖으로 보존하고 (hitPoint에 할당)
                minDistance = contact.distance;
                hitPoint = contact.hitPoint;
            }
        }
    }

    //찾아낸 거리가 초기값보다 의미 있게 적은가를 판별
    return minDistance != FLT_MAX; // FLT_MAX보다 많을 수는 없으므로, 다르다면 분명히 적어진 것
}

void RobotManager::Collision()
{
    // 실시간 범용 충돌판정
    // (게임 내부에서 데이터들이 주어질 때, 해당 데이터끼리 충돌 여부를 반복계산하기 위함)

    for (Robot* robot : robots)
    {
        // 게임에서 주어진 데이터, 매니저가 가진 데이터 등과 로봇을 계속 대조
        // 현재는 쿠나이 충돌체가 주어져 있다
        // + 나중에 필요하면 나루토의 충돌체 등을 추가할 수도 있다

        //쿠나이와 로봇의 충돌 비교
        if (KunaiManager::Get()->IsCollision(robot->GetCollider()))
        {
            robot->Hit();
            return; // 반복문 종료 -> 업데이트로 어차피 계속 돌아간다
        }
    }
}

void RobotManager::Spawn()
{
    Vector3 dir;
    dir.x = Random(-1.0f, 1.0f);
    dir.z = Random(-1.0f, 1.0f);

    // 매니저가 추적 중인 표적의 현재 위치에서 어느 정도 떨어진, 방향은 랜덤이 장소를 선택
    // 거리를 조절하거나, 거리까지 랜덤으로 하고 싶다면 아래 코드의 2000.0f 계수를 수정
    Vector3 randomPos = target->Pos() + (dir.GetNormalized() * 2000.0f);

    //정해진 랜덤 장소에서 로봇 생성
    for (Robot* robot : robots)
    {
        if (!robot->GetTransform()->Active()) // 아직 로봇이 안 나와 있다면
        {
            robot->Spawn(randomPos);
            break; //생성 종료
        }
    }
}
