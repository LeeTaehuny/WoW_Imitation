#pragma once
class Reflector : public GameObject
{
public:
    Reflector(float width = 100.0f, float height = 100.0f);
    ~Reflector();

    void Update();

    void Render();
    void GUIRender();

    void SetReflection();
    Reflection* GetReflection() { return reflection; }

private:
    void MakeMesh();

private:
    Vector2 size;
    Mesh<VertexUV>* mesh;

    Reflection* reflection;

    BlendState* blendState[2];
};

