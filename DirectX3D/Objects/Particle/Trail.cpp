#include "Framework.h"

Trail::Trail(wstring imageFile, Transform* start, Transform* end, UINT width, float speed)
    : start(start), end(end), width(width), speed(speed)
{
    //��Ƽ���� ����
    material->SetShader(L"Basic/Texture.hlsl");
    material->SetDiffuseMap(imageFile);

    //�޽� �����
    CreateMesh();

    //�����Ͷ����� ���� ����
    rasterizerState[0] = new RasterizerState();
    rasterizerState[1] = new RasterizerState();
    rasterizerState[1]->CullMode(D3D11_CULL_NONE); // �ø�(��¼���) : ���� ����
                                                   // ���� ���� ���� ��� �̹��� ���

    //���� ���� ����
    blendState[0] = new BlendState(); // <- ���� ���¸� ���� ���� ������ �� �̷��� ���� ����
    blendState[1] = new BlendState();
    //FOR(2) blendState[i] = new BlendState(); // <- ������ ��ü�� ���ų� Ÿ�� ġ�� ������ ��
    //blendState[1]->Alpha(true);
    blendState[1]->Additive(); //ȥ�տ� ���� ���� (ȭ�Ҵ���)
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

    //�޽� ������ �ޱ�
    vector<VertexUV>& vertices = mesh->GetVertices();

    //���۰� ���� ��ġ�� ��� �������� �ϱ�
    for (UINT i = 0; i <= width; i++)
    {
        //������ ���Ϳ��� �ް�
        Vector3 startPos = vertices[i * 2].pos;
        Vector3 endPos = vertices[(i * 2) + 1].pos;

        //���� ���� �� ��ġ�� �����
        Vector3 startDestPos;
        Vector3 endDestPos;

        //���� ��ġ ���Ϳ� ���� �Ҵ��ϱ� (Ʈ���������� ���� ����+������)
        if (i == 0)
        {
            //������ = Ʈ�������� ��ġ
            startDestPos = start->GlobalPos();
            endDestPos = end->GlobalPos();
        }
        else
        {
            startDestPos = vertices[(i - 1) * 2].pos;
            endDestPos = vertices[(i - 1) * 2 + 1].pos;
        }
        
        //�������� ���������� ������ �̵���Ű��
        startPos = Lerp(startPos, startDestPos, speed * DELTA);
        endPos = Lerp(endPos, endDestPos, speed * DELTA);
        
        //�޽� �����Ϳ� �ݿ�
        vertices[i * 2].pos = startPos;
        vertices[i * 2 + 1].pos = endPos;
    }

    // ������� ���� ������� �׸�(��)�� ���� ���� ���ο� �������� ����ؼ� �Ѿư� ��

    // �ش� ����� ������Ʈ
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

    //������ �׸� �޽� ����� ��

    vertices.reserve((width + 1) * 2); //���͸� ������ "����"��ŭ ����� (���Ʒ� �� ������)
    for (UINT i = 0; i <= width; i++)
    {
        //�ؽ�ó ���� ��ġ : �׸��� ���� �Ʒ� + ���ο� ���� �����ʺ�ŭ��
        VertexUV vertex;
        vertex.uv = { (float)i / width, 0.0f };
        vertices.push_back(vertex);

        vertex.uv = { (float)i / width, 1.0f };
        vertices.push_back(vertex);
    }

    vector<UINT>& indices = mesh->GetIndices();

    //�߷��� ���� �������� �ٽ� ��� �Ｎ ����ó�� �����
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
