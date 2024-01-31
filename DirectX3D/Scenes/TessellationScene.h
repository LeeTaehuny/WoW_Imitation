#pragma once

class TessellationScene : public Scene
{
public:
    TessellationScene();
    ~TessellationScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Material* material;
    HullShader* hullShader;
    DomainShader* domainShader;

    Mesh<Vertex>* mesh;

    FloatValueBuffer* edgeBuffer;
    FloatValueBuffer* insideBuffer;
};