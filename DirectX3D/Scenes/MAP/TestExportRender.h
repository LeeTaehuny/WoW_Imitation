#pragma once
class TestExportRender : public Scene
{
public:
    TestExportRender();
    ~TestExportRender();

    virtual void Update() override;
    virtual void Render() override;

    virtual void PreRender() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Model* M1;
    Model* M2;
    Model* M3;
};

