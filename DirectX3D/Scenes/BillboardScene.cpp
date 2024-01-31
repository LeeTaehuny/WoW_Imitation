#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
    // 아래 주석처리된 부분은 방법 A, B, C를 위한 코드

    //trees.reserve(COUNT);
    //FOR(COUNT)
    //{
    //    Vector2 size;
    //    size.x = Random(3.0f, 10.0f);
    //    size.y = Random(3.0f, 10.0f);
    //
    //    Quad* tree = new Quad(size);
    //    tree->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Tree.png");
    //    tree->Pos().x = Random(0.0f, 10.0f);
    //    tree->Pos().z = Random(0.0f, 10.0f);
    //    tree->Pos().y = 0;
    //
    //    trees.push_back(tree);
    //
    //    //캔버싱용 원점 저장 변수 준비
    //    Transform* transform = new Transform(); //트랜스폼
    //    transform->Pos() = tree->Pos(); //위치넣기
    //    origins.push_back(transform); //벡터에 추가
    //}
    //
    ////캔버싱용 변수들 준비
    //FOR(2) blendState[i] = new BlendState();
    //blendState[1]->AlphaToCoverage(true);

    // -----------------------------------------

    // 지오메트리 셰이더를 쓸 때는 시작이 약간 다르다

    material = new Material(L"Geometry/Billboard.hlsl"); // 관측 방향에 관계없이 방향이 똑같아지게 만드는 맞춤 셰이더
    material->SetDiffuseMap(L"Textures/Landscape/Tree.png"); //디퓨즈맵

    geometryShader = Shader::AddGS(L"Geometry/Billboard.hlsl"); //지오메트리 연산 추가
    //기본 세팅 끝 (그릴 재료 + 셰이더 생성, 세팅)
    
    // -> 개별 쿼드 만들지 않음

    //정점과 UV (업데이트 제작도 되지만, 생성 단계에서 만들면 안정적)

    vertices.resize(COUNT); // 정점을 하나의 개체만이 아니라 각 개체의 정점의 기준으로 삼는다
    FOR(COUNT)
    {
        vertices[i].uv.x = Random(1.0f, 10.0f);
        vertices[i].uv.y = Random(1.0f, 10.0f);

        vertices[i].pos.x = Random(0.0f, 30.0f);
        vertices[i].pos.z = Random(0.0f, 30.0f);
        vertices[i].pos.y = 0;
    }
    //정점 버퍼 준비
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), COUNT);

    //블렌드+뎁스 준비
    FOR(2) blendState[i] = new BlendState(); //블렌드
    FOR(2) depthState[i] = new DepthStencilState(); //뎁스

    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); //어떤 것에도 가려지지 않게
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);  //좌표상 조금만 앞에 있으면 다 가려지게
}

BillboardScene::~BillboardScene()
{
}

void BillboardScene::Update()
{
    //빌보드가 카메라를 보는 법
    // (원칙적, 혹은 직접 제어)

    //방법 A : 직접 벡터를 사용하여 방향을 제어
    //for (Quad* tree : trees)
    //{
    //    Vector3 dir = tree->Pos() - CAM->Pos(); // 카메라가 나무를 보는 방향
    //    // **수정됨!!**
    //    tree->Rot().y = atan2(dir.x, dir.z); //나무 방향을 (역)탄젠트로 주기
    //    tree->UpdateWorld(); //업데이트
    //}

    //방법 B : 텍스처와 카메라의 각도를 일치시켜주면 된다
    //for (Quad* tree : trees)
    //{
    //    tree->Rot().x = CAM->Rot().x;
    //    tree->Rot().y = CAM->Rot().y;
    //    tree->UpdateWorld();
    //}

    //방법 C : 캔버싱
    //for (Quad* tree : trees)
    //{
    //    //tree에 대응하는 transform 찾기
    //    int index = find(trees.begin(), trees.end(), tree) - trees.begin();
    //    // find : 벡터에 사용하면 반환값은 반복자. 이 자체로는 숫자 계산을 못 한다
    //    // 반복자가 가지는 계산상의 특징 : 자기들끼리는 단위를 가진 숫자처럼 계산 가능 (반복문의 it++)
    //    // -> find의 결과에 벡터의 begin()을 빼면, 마치 인덱스에서 0을 뺀 것처럼 계산해서 숫자로 만들 수 있다
    //    Transform* origin = origins.at(index); // <-tree에 대응하는 원래 트랜스폼
    //
    //    //캔버싱 진행 (Robot의 업데이트UI 참고)
    //    Vector3 treePos = origin->Pos();
    //    tree->Pos() = CAM->WorldToScreen(treePos);
    //    float scale = 100 / (treePos - CAM->Pos()).Length();
    //    scale = Clamp(0.1f, 100.0f, scale);
    //    tree->Scale() = { scale, scale, scale };
    //    tree->UpdateWorld();
    //}

}

void BillboardScene::PreRender()
{
}

void BillboardScene::Render()
{
    // 쿼드가 일반 렌더로 호출될 때 (방법 A, B)
    //for (Quad* tree : trees)
    //    tree->Render();

    // 쿼드 없이, 정점을 기준으로 해서, 매티리얼 정보를, 셰이더가 직접 그려낼 때
    // ->방법 D

    //블렌드, 뎁스 스테이트 설정 (이미지 배경색 처리, 우선순위 재설정)
    blendState[1]->SetState();
    depthState[1]->SetState();

    vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
    // D3D_PRIMITIVE_TOPOLOGY_POINTLIST : DX 제공 도형 출력 방식 중 하나.
    //                                    삼각형, 선 등의 기준 도형을 쓰지 않고,
    //                                    기준점 위에서 실시간 연산을 통해 직접 그래픽 출력

    // 그려질 이미지 정보 설정
    material->Set();

    // 지오메트리 셰이더 설정
    geometryShader->Set();

    // 출력장치에서 직접 출력 호출
    DC->Draw(COUNT, 0); //미리 설정된 이미지 정보를, COUNT만큼, 0번 정점부터 돌아가면서 출력

    // 출력장치에 셰이더 설정 (출력 과정에서 셰이더가 연산을 통해 매티리얼을 직접 그려낸다)
    DC->GSSetShader(nullptr, nullptr, 0); //매개변수 의미 : 수동 연결할 픽셀 셰이더 없음.
                                          //               추가 설정할 클래스 인스턴스 없음
                                          //               클래스 인스턴스 배정 개수
                                          //               = "사전에 설정해둔 그대로"

    // 출력장치를 통한 직접 출력 (=렌더) 종료 후, 원상복구
    blendState[0]->SetState();
    depthState[0]->SetState();
}

void BillboardScene::PostRender()
{
    // 쿼드가 2D 텍스처로서, 뷰포트로 투사될 때 (방법 C)
    //스크린에서 텍스처를 투사한다면 여기에서 호출
    //blendState[1]->SetState(); // 텍스처용 블렌드 상태 적용
    //for (Quad* tree : trees)
    //    tree->Render();        // 나무 출력
    //blendState[0]->SetState(); // 원상복구
}

void BillboardScene::GUIRender()
{
}
