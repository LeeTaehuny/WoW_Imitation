#include "Framework.h"

Rain::Rain()
{
    //�׸� ����
    //material->SetShader(L"Basic/Texture.hlsl"); // <- �ؽ�ó�μ� �� ���
    material->SetShader(L"Geometry/Rain.hlsl"); //������Ʈ�� ���̴��� Ŀ���� ���̴�
    material->SetDiffuseMap(L"Textures/Effect/Rain.png");

    geometryShader = Shader::AddGS(L"Geometry/Rain.hlsl");

    buffer = new WeatherBuffer(); // Ŭ���� �ȿ� �⺻�� ����

    Create(); // ���� ����� �Լ� ��� ȣ��
}

Rain::~Rain()
{
    delete buffer;
}

void Rain::Update()
{
    buffer->Get().time += DELTA; //�ð��� ����ð� ����
}

void Rain::Render()
{
    buffer->SetVS(10); //���� ���̴� + �׸� ��� ���ǹ� ��� (10 : �ٸ� �� ��ȯ ����)
    Particle::Render(); //�θ� ���� �Լ� �̾� ȣ��
}

void Rain::GUIRender()
{
    // ���۰� ���� �ִ� �����μ��� ��ƼŬ �ɼ� ����

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
    int count = 10000; //����� ����. ���ϴ� �� ����
    buffer->Get().velocity = { 0, -5, 0 }; //�ӷ� �ʿ��� ��� ����

    // �� �������� ����� �ִ밪�� ���� �ʵ���
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
                // size = ���� ������ ũ�� = ������ ������ ��ġ�� ������ �Ը� = ��ƼŬ ��ü ũ��
                // ���� ������� �ִ� ��Ҵ� size �� ���

        //�ؽ�ó ����� ���� ���Ϳ� �߰�
        vertices[i].pos = pos;
        vertices[i].uv = size;
    }
    //��¿� ���� ���ۿ��� �ݿ�
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), particleCount);
}