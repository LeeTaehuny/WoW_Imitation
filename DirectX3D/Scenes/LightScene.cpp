#include "Framework.h"
#include "LightScene.h"

LightScene::LightScene()
{
    sphere = new Sphere(10);  
    sphere->GetMaterial()->GetName() = "Fieldstone";

    tl = new TestLight();

    //light = Environment::Get()->GetLight(0); // �⺻������ ���õǾ� �ִ� ������ �޾ƿ´�
    //light = Environment::Get()->AddLight(); //������ �߰��ؼ� ����Ѵ�
    light = tl->GetLight();
    //light->direction = { 0, 0, 1 }; //���� ��ȯ
    //light->color = { 0, 0, 1, 1 }; //���� ���� �Ķ���

    Environment::Get()->GetLight(0)->color = { 0.25f, 0.25f, 0.25f, 1 };
}

LightScene::~LightScene()
{
    delete sphere;
}

void LightScene::Update()
{
    //���� ���� �ٲ� ����
    if (KEY_DOWN('1'))
        light->type = 0; // 0 : ���⼺ ���� (�⺻��)
                         //     ���� ����(����)�� �����ϰ� ���⸸�� ����ϴ� ��
                         //     ���� ��� ��ü�� �Ȱ��� ����� ���� ���߰� ���� �� ����
                         //     ���Ҿ� ���� 3D ���α׷����� �⺻ �� �����̱⵵ �ϴ�
                         //     ���ǿ� �����ϸ� �޺��� ����

    if (KEY_DOWN('2'))
        light->type = 1; // 1 : �� ���� (����Ʈ ����Ʈ) ** �߿�!
                         //     Ư���� �������� ��ü �������� ���������� ���� ���
                         //     ������ ������ ������, ���� ��� �κ��� ����
                         //     �ָ� ������ ���� �� �а� �������� ���� ��ο�����
                         //     ���ǿ� �����ϸ� ���� Ȥ�� �к�, ȶ�� ��

    if (KEY_DOWN('3'))
        light->type = 2; // 2 : ���� ���� (����Ʈ ����Ʈ) ** �߿�!!
                         //     Ư���� �������� �� �������� ���������� ���� ���
                         //     �� ������ Ư¡�� ���Ҿ ���� ���⿡ ��ü�� �ִ��ĵ� �߿�
                         //     ���� ������ ���⿡ �־�� ���� �ް�,
                         //     ������ �����ų� ��ġ�� ��߳��� ���� ���� ���Ѵ�
                         //     ���ǿ� �����ϸ� ����Ʈ����Ʈ, ������, �ڵ��� ������Ʈ

    if (KEY_DOWN('4'))
        light->type = 3; // 3 : ĸ�� ���� (���� ����)
                         //     ĸ��(Dx�� ����, ������ ĸ��)�� ����� �� �� = �߽��� 2���� �� ����
                         //     �� �߽ɿ��� ���� ���� �޾Ƽ� ������ ����� ����
                         //     ���� ���� : ����� ����� ������ �䳻���� ���ؼ� ���� �� (���� ������ �ܼ�ȭ)
                         //     ���ǿ��� �� ĸ�� ������ �״�� ����ϴ� ������ ��� ������,
                         //     ������ �ݿ��ϸ� �߱���, ������ ���� �� ����� ���� ������ �����ϱ� ����
                         //     * ���� : �� ������ ���� ����� �� ���� �ʴ´� (������ DX���� ����)

    // DX������ ���� ���� ���� ������ (����� ��� ����)
    // GPU�� ������ ���� ���� ���� ��� ���Ǵ� �ٸ� ���� ���� ����
    // -> �� ���� (����� ����Ʈ)
    //    : ���� �ƴ� ����� ��ü�� ������ �Ǵ� �� (����Ʈ, Ȥ�� ����Ʈ ����)
    //      ���Ƿ� �������� �� â��, ����� �� ������ ���� ��ü�� ������ �Ǵ� ��Ȳ�� ����� �� ����Ѵ�

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
