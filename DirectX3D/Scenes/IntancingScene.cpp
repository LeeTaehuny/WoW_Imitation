#include "Framework.h"
#include "IntancingScene.h"

IntancingScene::IntancingScene()
{
    
    // 모델 (최초 구현) 생성

    models = new ModelAnimatorInstancing("Naruto"); // 애니메이터 하나인 것처럼 일단 만들기

    //나루토의 경우
    models->ReadClip("Idle");       // 닌자 자세
    models->ReadClip("Punching");   // 주먹질

    //인간(테스트)인 경우
    //models->ReadClip("Idle", 1); // 휴먼 FBX는 동작에 수가 지정돼 있어서 1 매개변수 필요 (다른 모델은 없어도 될 수 있음)
    //models->ReadClip("Run", 1);

    // (인스턴싱 핵심) 헤더에서 지정한 정렬 크기만큼 인스턴스를 추가 생성
    for (float z = 0; z < SIZE; ++z)
    {
        for (float x = 0; x < SIZE; ++x)
        {
            Transform* transform = models->Add();
                // 인스턴싱의 "추가" 함수를 통해서 동일한 정점, 동일한 동작, 동일한 텍스처에
                // 위치, 개성, ID 정도만 다른 새 개체를 만들기
            transform->Pos() = { x, 0, z }; //새 개체 위치 정하기
            transform->Scale() *= 0.01f; //추가된 개체는 0.01배 크기
        }
    }

}

IntancingScene::~IntancingScene()
{
    delete models; // 원형 지우기 (나머지도 다 이 데이터를 쓰니까)
}

void IntancingScene::Update()
{
    models->Update(); // 안에 있는 정점만 계산
}

void IntancingScene::PreRender()
{
}

void IntancingScene::Render()
{
    models->Render(); // 공통되는 정점을 하나인 것처럼 계산 후, 각 세부 개체의 위치에서 출력만
}

void IntancingScene::PostRender()
{
}

void IntancingScene::GUIRender()
{
    ImGui::SliderInt("ID", &instanceID, 0, 100); // 확인할 인스턴스의 ID
    ImGui::SliderInt("Clip", &clip, 0, 1);       // 수행시킬 동작

    if (ImGui::Button("Play")) //플레이 버튼 생성 후 해당 버튼이 눌리면
    {
        models->PlayClip(instanceID, clip); // 지정된 id 인스턴스에 지정된 동작 수행시키기
    }
    models->GUIRender();// 각 모델 UI 렌더 따로

}
