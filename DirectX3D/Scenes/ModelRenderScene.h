#pragma once

class ModelRenderScene : public Scene
{
public:
    ModelRenderScene();
    ~ModelRenderScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Model* model;
    Model* model2;
    Model* model3;
    Model* model4[4];
    Model* model5;
    Model* model6;
};