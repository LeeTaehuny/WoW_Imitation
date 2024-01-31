#pragma once

class GridScene : public Scene
{
private:
    const int MAX_VALUE = 100;

public:
    GridScene();
    ~GridScene();
        
    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    void MakeMesh();

private:
    Material* material;
    Mesh<VertexColor>* mesh;

    UINT curWidth, curHeight;
    UINT fixWidth, fixHeight;

    MatrixBuffer* worldBuffer;

    Vector3 curGridColor = { 0.5f, 0.5f, 0.5f };
    Vector3 fixGridColor = { 0.5f, 0.5f, 0.5f };
};