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
};