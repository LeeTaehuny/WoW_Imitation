#pragma once

class BuffParticle : public Particle
{
public:
    BuffParticle(int spawnCount);
    ~BuffParticle();

    virtual void Update() override;
    virtual void Render() override;
    virtual void GUIRender() override;

private:
    void Create();

private:
    BuffBuffer* buffer;
    vector<VertexUV> vertices;

    int spawnCount;
};
