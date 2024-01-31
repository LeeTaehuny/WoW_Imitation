#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
    //modelAnimator = new ModelAnimator("Human"); // 모델명으로 애니메이터 생성
    //modelAnimator->ReadClip("Idle", 1);         // 사전에 설정됐던 클립명으로 동작을 불러오기
    //modelAnimator->ReadClip("Run", 1);          // 동작의 이름은 .fbx에 내장되었던 동작이름(클립명)에서 따온 것
    //modelAnimator->ReadClip("Jump", 1);         // fbx 뷰어 프로그램 등을 사용하면 클립명, 기타 정보 확인 가능
    //                                            // 전용 뷰어 프로그램이 좋고, 편집 프로그램도 좋습니다 (예 : 3Ds MAX)

    // 가져온 동작에 따라서 ReadClip 함수 실행
    // : 동작 구성에 따라서 클립의 소분류가 지정된 경우, 호출할 때 클립의 수(혹은 순번)를 매개변수로 하나 더 주면 OK
    //   -> 위에 있는 호출 (클립명 + 클립수) , 아래쪽은 그런 정보가 없어서 클립명만으로도 호출가능

    // 현재 애니메이터 구현의 약점 : 텍스처는 그렇다쳐도, 정점 정보와, 뼈대 정보, 움직임 정보까지
    // 모든 출력에 관계한 기초 데이터를 일일이 파일에서 읽은 후 별도로 생성해서 재생한다는 것
    
    // -> 객체가 많아지면 거의 그 객체의 구현 수만큼 컴퓨터가 부담을 떠안게 된다

    // -> 해결 방안 : 한 씬에 한 종류의 캐릭터가 여럿 나올 때, 해당 캐릭터를 구성하는 기초적인 요소
    //    (정점, 어떤 동작이 있는지, 어떤 뼈대를 가졌는지...) 들을 한 군데에 저장하고,
    //    만들어진 실제 객체는 해당 실체만이 가지는 고유 정보와 (트랜스폼 정보나, 내부 데이터 몇 개)
    //    다른 객체와 공유 가능한 공통 정보를(생김새, 텍스처, 동작, 뼈대) 하나로 합쳐서 구현하는 것
    //    그러면 구현에 필요한 컴퓨터의 연산을 상당히 줄일 수 있게 된다

    // = 모델, 혹은 애니메이션의 생성 후 관리법 (Animation Instancing, 애니메이션 인스턴싱)

    // * 같이 이해하면 좋은 용어 

    // 1. 드로우 유닛 : 객체 하나를 그리기 위해 필요한 연산의 단위. 정점, 뼈대, 가중치, 매티리얼 등을 통칭
    // 2. 드로우 콜 : 컴퓨터가 단위시간당 드로우 유닛을 받은 수. 이게 너무 높으면 컴퓨터의 사양이 높아진다 (앱이 느려진다)

    // -> 애니메이션 인스턴싱을 다르게 표현하면, 드로우 유닛을 공유시켜, 드로우 콜을 줄이는 기법

    // : 자세한 코드는 모델 인스턴싱->애니메이션 인스턴싱에서

    //modelAnimator = new ModelAnimator("Fox");
    //modelAnimator->ReadClip("Fox_Run");

    modelAnimator = new ModelAnimator("Robot");
    modelAnimator->ReadClip("Run");
    modelAnimator->ReadClip("Walk");
    modelAnimator->ReadClip("Dying");
    modelAnimator->ReadClip("StandUp");
    modelAnimator->ReadClip("Hit");
}

ModelAnimationScene::~ModelAnimationScene()
{
    delete modelAnimator;
}

void ModelAnimationScene::Update()
{
    if (KEY_DOWN('1'))
        modelAnimator->PlayClip(0);
    if (KEY_DOWN('2'))
        modelAnimator->PlayClip(1);
    if (KEY_DOWN('3'))
        modelAnimator->PlayClip(2);
    if (KEY_DOWN('4'))
        modelAnimator->PlayClip(3);
    if (KEY_DOWN('5'))
        modelAnimator->PlayClip(4);

    modelAnimator->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
    modelAnimator->Render();
}

void ModelAnimationScene::PostRender()
{
}

void ModelAnimationScene::GUIRender()
{
    modelAnimator->GUIRender();
}

void ModelAnimationScene::SetIdle()
{
    modelAnimator->PlayClip(0, 1.0f, 0.1f);
}
