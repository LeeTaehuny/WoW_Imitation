#pragma once

class TerrainEditorScene : public Scene
{
public:
    TerrainEditorScene();
    ~TerrainEditorScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;    

private:
    void ByteAddress();

private:
    TerrainEditor* terrainEditor;
};