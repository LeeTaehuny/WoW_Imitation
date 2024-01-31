#pragma once
class BillboardScene : public Scene
{
private:
    UINT COUNT = 100;

public:
    BillboardScene();
    ~BillboardScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    // 빌보드 : 원문은 "간판"
    //         프로그래밍에서는 언제나 카메라를 향하는 2D 텍스처를 지칭
    vector<Quad*> trees; //나무 (그림 텍스처)

    // 빌보드 구현 방법
    // A : 벡터로 방향 제어 : 구현이 가장 쉽지만 텍스처가 움직이는 게 눈에 잘 띈다
    // B : 카메라와 방향 일치 : 보이기는 가장 안정적이지만 카메라에 너무 의존이 심하다
    // C : 2D용 뷰포트에 직접 투사 (그래픽 연산 후 -> 2D 공간에 렌더) : 존재하는 공간이 달라져서
    //                                                      상호작용, 출력 우선순위 혼란 가능

    // D : 텍스처 정보를 한번 더 셰이더로 연산해서 재구성
    //     -> DX의 기능 사용 (지오메트리 셰이더) : 텍스처의 정보를 화면에 직접
    //        (그래픽 연산부터 하고 -> 2D의 정보를 가진 데이터로 렌더)
    //        하드웨어 부담이 있지만, 연산과 셰이더가 지원되는 환경에서는 속도가 더 빠르다
    //        랜덤 생성의 경우 어떻게 데이터를 보존할(혹은 필요에 따라 다시 셔플할) 것인가가 관건
    //        렌더 호출 위치가 코드 안에서 비슷하기 때문에 상호작용, 출력 우선순위가 비교적 안정

    // 빌보드 사용 사례(용도) : 먼 곳의 배경, 플레이어가 놓치면 안 되는 2D 정보
    //                        (2D 텍스처로 나온 줍는 아이템, 홀로그램 정보창, 온라인 게임의 플레이어 이름 등)
    //                        .....그리고 게임 중에 나오는 그래픽 특수 효과들 (GFX, 혹은 파티클)

    // 방법 C를 위한 변수들 : 투사 위치를 행렬 공간(프로젝션)에서 캔버스(뷰포트)로 바꿔주기
    Terrain* terrain; //배경!!
    BlendState* blendState[2]; //블렌드 스테이트
    vector<Transform*> origins; //나무 위치 원점 저장 (캔버싱용)

    // +D를 위한 변수들 : 지오메트리 셰이더 호출을 위한 것들
    Material* material;
    VertexBuffer* vertexBuffer; // 여기서 텍스처 + 정점을 또 연산할 필요 있음

    GeometryShader* geometryShader; // 지오메트리 셰이더 (핵심)

    DepthStencilState* depthState[2]; //뎁스 스테이트
    vector<VertexUV> vertices; //텍스처의 버텍스 타입(과 개체용 벡터)
};

