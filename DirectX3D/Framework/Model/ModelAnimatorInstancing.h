#pragma once

class ModelAnimatorInstancing : public ModelAnimator
{
public:
    struct Motion
    {
        float takeTime = 0.2f;
        float tweenTime = 0.0f;
        float runningTime = 0.0f;
        float duration = 0.0f;

        Frame cur, next;

        Motion()
        {
            next.clip = -1;
        }
    };

private:
    class FrameInstancingBuffer : public ConstBuffer
    {
    public:
        struct Data
        {
            Motion motions[MAX_INSTANCE];
        };

    public:
        FrameInstancingBuffer() : ConstBuffer(&data, sizeof(Data))
        {
        }

        Data& Get() { return data; }

    private:
        Data data;
    };

public:
    ModelAnimatorInstancing(string name);
    ~ModelAnimatorInstancing();

    void Update();
    void Render();
    void GUIRender();

    Transform* Add();

    void PlayClip(UINT instanceID, int clip, float scale = 1.0f, float takeTime = 0.1f);

    Matrix GetTransformByNode(UINT instanceID, int nodeIndex);

    Motion* GetMotion(UINT instanceID)
    { 
        return &frameInstancingBuffer->Get().motions[instanceID];
    }

    UINT GetClipSize() { return clips.size(); }

private:    
    void UpdateFrame(UINT instanceID, Motion& motion);
    void UpdateTransforms();

private:
    vector<Transform*> transforms;
    InstanceData instanceDatas[MAX_INSTANCE];

    VertexBuffer* instanceBuffer;
    FrameInstancingBuffer* frameInstancingBuffer;

    UINT drawCount = 0;
};