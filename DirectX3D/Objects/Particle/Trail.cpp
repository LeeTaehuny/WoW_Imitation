#include "Framework.h"

Trail::Trail(wstring imageFile, Transform* start, Transform* end, UINT width, float speed)
    : start(start), end(end), width(width), speed(speed)
{
    //매티리얼 세팅
    material->SetShader(L"Basic/Texture.hlsl");
    material->SetDiffuseMap(imageFile);

    //메시 만들기
    CreateMesh();

    //래스터라이저 상태 설정
    rasterizerState[0] = new RasterizerState();
    rasterizerState[1] = new RasterizerState();
    rasterizerState[1]->CullMode(D3D11_CULL_NONE); // 컬링(출력선별) : 하지 않음
                                                   // 방향 관계 없이 모든 이미지 출력

    //블렌드 상태 설정
    blendState[0] = new BlendState(); // <- 개별 상태를 각각 따로 설정할 때 이렇게 각자 생성
    blendState[1] = new BlendState();
    //FOR(2) blendState[i] = new BlendState(); // <- 생성할 객체가 많거나 타자 치기 귀찮을 때
    //blendState[1]->Alpha(true);
    blendState[1]->Additive(); //혼합에 의한 투명 (화소누적)
}

Trail::~Trail()
{
    delete mesh;

    delete rasterizerState[0];
    delete rasterizerState[1];

    delete blendState[0];
    delete blendState[1];
}

void Trail::Update()
{
    if (!Active()) return;

    //메쉬 데이터 받기
    vector<VertexUV>& vertices = mesh->GetVertices();

    //시작과 끝의 위치를 계속 재조정을 하기
    for (UINT i = 0; i <= width; i++)
    {
        //정점을 벡터에서 받고
        Vector3 startPos = vertices[i * 2].pos;
        Vector3 endPos = vertices[(i * 2) + 1].pos;

        //새로 찍어야 할 위치를 만들고
        Vector3 startDestPos;
        Vector3 endDestPos;

        //만든 위치 벡터에 값을 할당하기 (트랜스폼으로 받은 시작+끝에서)
        if (i == 0)
        {
            //목적지 = 트랜스폼의 위치
            startDestPos = start->GlobalPos();
            endDestPos = end->GlobalPos();
        }
        else
        {
            startDestPos = vertices[(i - 1) * 2].pos;
            endDestPos = vertices[(i - 1) * 2 + 1].pos;
        }
        
        //보간으로 목적지까지 정점을 이동시키기
        startPos = Lerp(startPos, startDestPos, speed * DELTA);
        endPos = Lerp(endPos, endDestPos, speed * DELTA);
        
        //메쉬 데이터에 반영
        vertices[i * 2].pos = startPos;
        vertices[i * 2 + 1].pos = endPos;
    }

    // 여기까지 오면 만들어진 그림(들)의 양쪽 끝이 새로운 목적지를 계속해서 쫓아갈 것

    // 해당 결과를 업데이트
    mesh->UpdateVertex();
}

void Trail::Render()
{
    if (!Active()) return;

    worldBuffer->SetVS(0);

    material->Set();

    rasterizerState[1]->SetState();
    blendState[1]->SetState();

    mesh->Draw();

    rasterizerState[0]->SetState();
    blendState[0]->SetState();
}

void Trail::CreateMesh()
{
    mesh = new Mesh<VertexUV>();

    vector<VertexUV>& vertices = mesh->GetVertices();

    //궤적의 그림 메시 만드는 법

    vertices.reserve((width + 1) * 2); //벡터를 가로의 "개수"만큼 만들기 (위아래 한 쌍으로)
    for (UINT i = 0; i <= width; i++)
    {
        //텍스처 참조 위치 : 그림의 위와 아래 + 가로에 대한 단위너비만큼만
        VertexUV vertex;
        vertex.uv = { (float)i / width, 0.0f };
        vertices.push_back(vertex);

        vertex.uv = { (float)i / width, 1.0f };
        vertices.push_back(vertex);
    }

    vector<UINT>& indices = mesh->GetIndices();

    //잘려서 만든 정점들을 다시 모아 즉석 쿼드처럼 만들기
    indices.reserve(width * 6);
    FOR(width)
    {
        indices.push_back(i * 2);
        indices.push_back(i * 2 + 2);
        indices.push_back(i * 2 + 1);

        indices.push_back(i * 2 + 1);
        indices.push_back(i * 2 + 2);
        indices.push_back(i * 2 + 3);
    }

    mesh->CreateMesh();
}
