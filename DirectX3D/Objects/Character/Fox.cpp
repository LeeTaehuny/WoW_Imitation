#include "Framework.h"

Fox::Fox() : ModelAnimator("Fox")
{
    ReadClip("Idle");
    ReadClip("Run", 0, "FoxTransform"); // 모델 파일에 있던 뼈대를 수동으로 설정

    PlayClip(curState); // 현재 상태에 따른 동작 1회 호출
}

Fox::~Fox()
{
}

void Fox::Update()
{
    //캐릭터 조종 3종 호출
    Control();
    Move();
    Rotate();

    ModelAnimator::Update();
}

void Fox::Render()
{
    ModelAnimator::Render();
}

void Fox::Control()
{
    if (KEY_DOWN(VK_LBUTTON))
    {
        destPos = terrain->Pick(); // 최종 목적지를 지형에서 찾아내고

        if (aStar->IsCollisionObstacle(GlobalPos(), destPos)) //직선거리에 장애물이 보이면
        {
            SetPath(); // 장애물의 위치(경로상 어디가 장애물인지) 찾아낸 다음 해당 부분을 돌아가는 경로 계속 내기
        }
        else //장애물이 없으면
        {
            path.clear(); //경로는 무의미하니까 다 없애고
            path.push_back(destPos); //최종 목적지 하나만 남기기 = 그쪽으로 Move() 함수를 수행하면
        }
    }

}

void Fox::Move()
{
    if (path.empty()) //경로가 없으면 = 목적지와 길이 없으면
    {
        SetState(IDLE);
        return; //움직이지 않기
    }

    SetState(RUN); // 이동 시작에 따른 움직이기 시작

    // 벡터로 들어온 경로를 하나씩 찾아가면서 움직이기

    Vector3 dest = path.back(); // 최종 목적지로부부터 시작된 "길"의 마지막
                                // = 목적지로 가기 위한 "최초의" 단기 목적지

    Vector3 direction = dest - GlobalPos(); // 내 위치에서 당장의 목적지로 가기 위한 방향

    direction.y = 0; //좌우이동 위주로 갈 거라서 높이는 고려하지 않음

    if (direction.Length() < 0.5f) // 대충 다 온 것 같으면
    {
        path.pop_back(); // 다 온 목적지는 벡터에서 제거 (체크리스트 체크)
    }

    //목적지로 가기 위한 방향으로 이동
    velocity = direction.GetNormalized();
    Pos() += velocity * moveSpeed * DELTA;
}

void Fox::Rotate()
{
    if (curState == IDLE) return; //이동 중이 아닐 때는 회전 안함

    Vector3 forward = Forward(); //모델의 앞 따오기
    Vector3 cross = Cross(forward, velocity); //내 앞과 가야 할 방뱡에서 나온 법선

    if (cross.y < 0) //위 계산에 의한 법선이 밑이면 = 내가 목적지보다 오른쪽을 보는 중이다
        Rot().y += rotSpeed * DELTA; // 왼쪽 회전
    else if (cross.y > 0) //위와 반대
        Rot().y -= rotSpeed * DELTA; //오른쪽 회전
}

void Fox::SetState(State state) //호출은 이거 하나로만
{
    if (state == curState) return;

    curState = state; //상태를 변경해주고
    PlayClip(state);  //변경된 상태에 따른 애니메이션 재생
}

void Fox::SetPath()
{
    int startIndex = aStar->FindCloseNode(GlobalPos()); // 여우가 있는 노드가 시작 인덱스
    int endIndex = aStar->FindCloseNode(destPos); //최종 목적지에 가장 가까운 노드가 끝

    aStar->GetPath(startIndex, endIndex, path); // 시작, 끝 인덱스를 A* 길찾기에 대입하고,
                                                // 결과를 path에 저장
    aStar->MakeDirectionPath(GlobalPos(), destPos, path); // 중간에 장애물이 있으면 해당 부분도
                                                          // path에 반영

    UINT pathSize = path.size(); //처음 벡터 크기 받기

    while (path.size() > 2) // 이후 길을 찾아가면서 남은 경로 수가 2 이하가 될 때까지 아래 반복
    {
        vector<Vector3> tempPath = path; // 계산용 임시 경로 받아오기
        tempPath.erase(tempPath.begin()); // 최종 목적지는 일단 생각 안 함 (지금은 중간 경로가 있어서)
        tempPath.pop_back(); //이제 경로에서 가는 중이니까 시작 위치도 생각 안 함 (이제는 "지나간 곳"이어서)

        Vector3 start = path.back(); //새로운 시작점
        Vector3 end = path.front(); //새로운 끝

        aStar->MakeDirectionPath(start, end, tempPath); // 장애물 여부를 중간에서 다시 가리기
        
        //조정된 경로 다시 역반영
        path.clear();
        path = tempPath;

        //새로운 시작과 끝을 경로에 넣기
        path.insert(path.begin(), end);
        path.push_back(start);

        if (pathSize == path.size()) //최초의 벡터와 비교해서 경로 크기가 같으면
            break;
        else
            pathSize = path.size(); //경로가 줄어 있으면 줄어든 경로를 반영
    }

    //장애물 여부에 따라 재조정된 경로에 최종 목적지를 넣는다
    path.insert(path.begin(), destPos);
}
