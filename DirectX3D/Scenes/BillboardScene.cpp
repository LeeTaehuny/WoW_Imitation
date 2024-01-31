#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
    // �Ʒ� �ּ�ó���� �κ��� ��� A, B, C�� ���� �ڵ�

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
    //    //ĵ���̿� ���� ���� ���� �غ�
    //    Transform* transform = new Transform(); //Ʈ������
    //    transform->Pos() = tree->Pos(); //��ġ�ֱ�
    //    origins.push_back(transform); //���Ϳ� �߰�
    //}
    //
    ////ĵ���̿� ������ �غ�
    //FOR(2) blendState[i] = new BlendState();
    //blendState[1]->AlphaToCoverage(true);

    // -----------------------------------------

    // ������Ʈ�� ���̴��� �� ���� ������ �ణ �ٸ���

    material = new Material(L"Geometry/Billboard.hlsl"); // ���� ���⿡ ������� ������ �Ȱ������� ����� ���� ���̴�
    material->SetDiffuseMap(L"Textures/Landscape/Tree.png"); //��ǻ���

    geometryShader = Shader::AddGS(L"Geometry/Billboard.hlsl"); //������Ʈ�� ���� �߰�
    //�⺻ ���� �� (�׸� ��� + ���̴� ����, ����)
    
    // -> ���� ���� ������ ����

    //������ UV (������Ʈ ���۵� ������, ���� �ܰ迡�� ����� ������)

    vertices.resize(COUNT); // ������ �ϳ��� ��ü���� �ƴ϶� �� ��ü�� ������ �������� ��´�
    FOR(COUNT)
    {
        vertices[i].uv.x = Random(1.0f, 10.0f);
        vertices[i].uv.y = Random(1.0f, 10.0f);

        vertices[i].pos.x = Random(0.0f, 30.0f);
        vertices[i].pos.z = Random(0.0f, 30.0f);
        vertices[i].pos.y = 0;
    }
    //���� ���� �غ�
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), COUNT);

    //����+���� �غ�
    FOR(2) blendState[i] = new BlendState(); //����
    FOR(2) depthState[i] = new DepthStencilState(); //����

    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); //� �Ϳ��� �������� �ʰ�
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);  //��ǥ�� ���ݸ� �տ� ������ �� ��������
}

BillboardScene::~BillboardScene()
{
}

void BillboardScene::Update()
{
    //�����尡 ī�޶� ���� ��
    // (��Ģ��, Ȥ�� ���� ����)

    //��� A : ���� ���͸� ����Ͽ� ������ ����
    //for (Quad* tree : trees)
    //{
    //    Vector3 dir = tree->Pos() - CAM->Pos(); // ī�޶� ������ ���� ����
    //    // **������!!**
    //    tree->Rot().y = atan2(dir.x, dir.z); //���� ������ (��)ź��Ʈ�� �ֱ�
    //    tree->UpdateWorld(); //������Ʈ
    //}

    //��� B : �ؽ�ó�� ī�޶��� ������ ��ġ�����ָ� �ȴ�
    //for (Quad* tree : trees)
    //{
    //    tree->Rot().x = CAM->Rot().x;
    //    tree->Rot().y = CAM->Rot().y;
    //    tree->UpdateWorld();
    //}

    //��� C : ĵ����
    //for (Quad* tree : trees)
    //{
    //    //tree�� �����ϴ� transform ã��
    //    int index = find(trees.begin(), trees.end(), tree) - trees.begin();
    //    // find : ���Ϳ� ����ϸ� ��ȯ���� �ݺ���. �� ��ü�δ� ���� ����� �� �Ѵ�
    //    // �ݺ��ڰ� ������ ������ Ư¡ : �ڱ�鳢���� ������ ���� ����ó�� ��� ���� (�ݺ����� it++)
    //    // -> find�� ����� ������ begin()�� ����, ��ġ �ε������� 0�� �� ��ó�� ����ؼ� ���ڷ� ���� �� �ִ�
    //    Transform* origin = origins.at(index); // <-tree�� �����ϴ� ���� Ʈ������
    //
    //    //ĵ���� ���� (Robot�� ������ƮUI ����)
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
    // ���尡 �Ϲ� ������ ȣ��� �� (��� A, B)
    //for (Quad* tree : trees)
    //    tree->Render();

    // ���� ����, ������ �������� �ؼ�, ��Ƽ���� ������, ���̴��� ���� �׷��� ��
    // ->��� D

    //����, ���� ������Ʈ ���� (�̹��� ���� ó��, �켱���� �缳��)
    blendState[1]->SetState();
    depthState[1]->SetState();

    vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
    // D3D_PRIMITIVE_TOPOLOGY_POINTLIST : DX ���� ���� ��� ��� �� �ϳ�.
    //                                    �ﰢ��, �� ���� ���� ������ ���� �ʰ�,
    //                                    ������ ������ �ǽð� ������ ���� ���� �׷��� ���

    // �׷��� �̹��� ���� ����
    material->Set();

    // ������Ʈ�� ���̴� ����
    geometryShader->Set();

    // �����ġ���� ���� ��� ȣ��
    DC->Draw(COUNT, 0); //�̸� ������ �̹��� ������, COUNT��ŭ, 0�� �������� ���ư��鼭 ���

    // �����ġ�� ���̴� ���� (��� �������� ���̴��� ������ ���� ��Ƽ������ ���� �׷�����)
    DC->GSSetShader(nullptr, nullptr, 0); //�Ű����� �ǹ� : ���� ������ �ȼ� ���̴� ����.
                                          //               �߰� ������ Ŭ���� �ν��Ͻ� ����
                                          //               Ŭ���� �ν��Ͻ� ���� ����
                                          //               = "������ �����ص� �״��"

    // �����ġ�� ���� ���� ��� (=����) ���� ��, ���󺹱�
    blendState[0]->SetState();
    depthState[0]->SetState();
}

void BillboardScene::PostRender()
{
    // ���尡 2D �ؽ�ó�μ�, ����Ʈ�� ����� �� (��� C)
    //��ũ������ �ؽ�ó�� �����Ѵٸ� ���⿡�� ȣ��
    //blendState[1]->SetState(); // �ؽ�ó�� ���� ���� ����
    //for (Quad* tree : trees)
    //    tree->Render();        // ���� ���
    //blendState[0]->SetState(); // ���󺹱�
}

void BillboardScene::GUIRender()
{
}
