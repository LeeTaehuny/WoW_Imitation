#include "Framework.h"
#include "LightScene.h"

LightScene::LightScene()
{
    sphere = new Sphere(10);  
    sphere->GetMaterial()->GetName() = "Fieldstone";

    tl = new TestLight();

    //light = Environment::Get()->GetLight(0); // 기본적으로 세팅되어 있는 광원을 받아온다
    //light = Environment::Get()->AddLight(); //광원을 추가해서 사용한다
    light = tl->GetLight();
    //light->direction = { 0, 0, 1 }; //방향 전환
    //light->color = { 0, 0, 1, 1 }; //빛의 색은 파란색

    Environment::Get()->GetLight(0)->color = { 0.25f, 0.25f, 0.25f, 1 };
}

LightScene::~LightScene()
{
    delete sphere;
}

void LightScene::Update()
{
    //광원 유형 바꿔 보기
    if (KEY_DOWN('1'))
        light->type = 0; // 0 : 방향성 광원 (기본값)
                         //     빛의 원점(광원)을 무시하고 방향만을 계산하는 빛
                         //     따라서 모든 물체에 똑같은 밝기의 빛을 비추고 싶을 때 쓴다
                         //     더불어 많은 3D 프로그래밍의 기본 빛 설정이기도 하다
                         //     현실에 비유하면 햇빛과 같다

    if (KEY_DOWN('2'))
        light->type = 1; // 1 : 점 광원 (포인트 라이트) ** 중요!
                         //     특정한 지점에서 전체 방향으로 퍼져나가는 빛을 모사
                         //     가까이 있으면 밝지만, 빛이 닿는 부분이 적고
                         //     멀리 있으면 빛이 더 넓게 퍼지지만 밝기는 어두워진다
                         //     현실에 비유하면 전구 혹은 촛불, 횃불 등

    if (KEY_DOWN('3'))
        light->type = 2; // 2 : 조명 광원 (스포트 라이트) ** 중요!!
                         //     특정한 지점에서 한 방향으로 퍼져나가는 빛을 모사
                         //     점 광원의 특징과 더불어서 빛의 방향에 물체가 있느냐도 중요
                         //     빛이 나가는 방향에 있어야 빛을 받고,
                         //     방향을 등지거나 위치가 어긋나면 빛을 받지 못한다
                         //     현실에 비유하면 스포트라이트, 손전등, 자동차 헤드라이트

    if (KEY_DOWN('4'))
        light->type = 3; // 3 : 캡슐 광원 (이중 광원)
                         //     캡슐(Dx식 말고, 현실의 캡슐)의 모양을 한 빛 = 중심이 2개인 점 광원
                         //     각 중심에서 각각 빛을 받아서 조명의 결과를 연산
                         //     구현 목적 : 막대기 모양의 광원을 흉내내기 위해서 만든 것 (막대 광원의 단순화)
                         //     현실에서 이 캡슐 광원을 그대로 모사하는 원형은 사실 없지만,
                         //     목적을 반영하면 야광봉, 형광등 같은 긴 모양을 가진 광원에 대입하기 좋다
                         //     * 참고 : 이 광원은 엔진 등에서는 잘 쓰지 않는다 (보통은 DX에서 쓴다)

    // DX에서는 현재 별로 쓰지 않지만 (기술적 사양 문제)
    // GPU와 연관이 깊은 전문 엔진 등에서 사용되는 다른 광원 연산 있음
    // -> 면 광원 (에어리어 라이트)
    //    : 점이 아닌 평면이 전체가 광원이 되는 것 (포인트, 혹은 스포트 유형)
    //      현실로 비유했을 때 창문, 모니터 등 면적을 가진 물체가 광원이 되는 상황을 모사할 때 사용한다

    if (!KEY_PRESS(VK_RBUTTON))
    {
        if (KEY_PRESS('W')) light->pos.z += DELTA;
        if (KEY_PRESS('S')) light->pos.z -= DELTA;
        if (KEY_PRESS('A')) light->pos.x -= DELTA;
        if (KEY_PRESS('D')) light->pos.x += DELTA;
        if (KEY_PRESS('R')) light->pos.y += DELTA;
        if (KEY_PRESS('F')) light->pos.y -= DELTA;

        if (KEY_DOWN('Z')) light->pos = { 0, 0, 0 };
        if (KEY_DOWN('X')) light->pos = { 0, 10.5f, 0 };
        if (KEY_DOWN('C')) light->pos = { 0, 10.5f, 10.5f };

        if (KEY_PRESS('Q')) light->range -= 30 * DELTA;
        if (KEY_PRESS('E')) light->range += 30 * DELTA;
    }
    //----------------------------------------------------

    if (KEY_PRESS(VK_F2))
        sphere->GetMaterial()->Load("TextData/Materials/Fieldstone.mat");

    if (KEY_DOWN('P'))
    {
        light->active = (light->active + 1) % 2;
    }

    sphere->UpdateWorld();
}

void LightScene::PreRender()
{
}

void LightScene::Render()
{
    sphere->Render();
}

void LightScene::PostRender()
{    
}

void LightScene::GUIRender()
{
    sphere->GUIRender();
}
