#include "Framework.h"

Rain::Rain()
{
    //그림 세팅
    //material->SetShader(L"Basic/Texture.hlsl"); // <- 텍스처로서 비 출력
    material->SetShader(L"Geometry/Rain.hlsl"); //지오메트리 셰이더용 커스텀 셰이더
    material->SetDiffuseMap(L"Textures/Effect/Rain.png");

    geometryShader = Shader::AddGS(L"Geometry/Rain.hlsl");

    buffer = new WeatherBuffer(); // 클래스 안에 기본값 있음

    Create(); // 정점 만들기 함수 끌어서 호출
}

Rain::~Rain()
{
    delete buffer;
}

void Rain::Update()
{
    buffer->Get().time += DELTA; //시간에 경과시간 누적
}

void Rain::Render()
{
    buffer->SetVS(10); //정점 셰이더 + 그림 출력 조건문 사용 (10 : 다른 색 반환 없음)
    Particle::Render(); //부모 렌더 함수 이어 호출
}

void Rain::GUIRender()
{
    // 버퍼가 갖고 있는 날씨로서의 파티클 옵션 설정

    ImGui::Text("Rain Particle Options");
    ImGui::Text("Time : %f", &buffer->Get().time);
    ImGui::DragFloat3("Velocity", (float*)&buffer->Get().velocity, 0.1f);
    ImGui::SliderFloat("Distance", &buffer->Get().distance, 0, 500);
    ImGui::DragFloat3("Origin", (float*)&buffer->Get().origin, 0.1f);
    ImGui::DragFloat3("Size", (float*)&buffer->Get().size, 0.1f);
    ImGui::ColorEdit4("Color", (float*)&buffer->Get().color);
}

void Rain::Create()
{
    int count = 10000; //빗방울 개수. 원하는 값 설정
    buffer->Get().velocity = { 0, -5, 0 }; //속력 필요할 경우 수정

    // 위 설정값이 헤더의 최대값을 넘지 않도록
    particleCount = (count < MAX_COUNT) ? count : MAX_COUNT;

    vertices.resize(particleCount);
    FOR(particleCount)
    {
        Float2 size;
        size.x = Random(0.1f, 0.4f);
        size.y = Random(2.0f, 8.0f);

        Float3 pos;
        pos.x = Random(-buffer->Get().size.x, buffer->Get().size.x);
        pos.y = Random(-buffer->Get().size.y, buffer->Get().size.y);
        pos.z = Random(-buffer->Get().size.z, buffer->Get().size.z);
                // size = 날씨 버퍼의 크기 = 날씨가 영향을 미치는 지역의 규모 = 파티클 전체 크기
                // 따라서 빗방울이 있는 장소는 size 속 어딘가

        //텍스처 연산용 정점 벡터에 추가
        vertices[i].pos = pos;
        vertices[i].uv = size;
    }
    //출력용 정점 버퍼에도 반영
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), particleCount);
}