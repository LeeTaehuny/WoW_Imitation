#pragma once

class ModelExportScene : public Scene
{
public:
    ModelExportScene();
    ~ModelExportScene();
        
    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

    // �𵨿��� ���׸���� �޽� ���� �Լ�
    // ���� �̸��� ������ �˾Ƽ� ���ɴϴ�.
    void Model_MER_MESH(string name);

    // �ִϸ��̼� �������� Ŭ�� ����
    // ���� �̸�, �ִϸ��̼� �̸��� �����ø� �˴ϴ�.
    void AnimationClip(string name, string clipName);
};