#pragma once

class ModelAnimator : public Model
{
protected:
    struct Frame
    {
        int clip = 0;
        UINT curFrame = 0;
        float time = 0.0f;
        float scale = 1.0f;
    };

    class FrameBuffer : public ConstBuffer
    {
    public:
        struct Data
        {
            float takeTime = 0.2f;
            float tweenTime = 0.0f;
            float runningTime = 0.0f;
            float padding;

            Frame cur, next;
        };

    public:
        FrameBuffer() : ConstBuffer(&data, sizeof(Data))
        {
            data.next.clip = -1;
        }

        Data& Get() { return data; }

    private:
        Data data;
    };

public:
    ModelAnimator(string name);
    ~ModelAnimator();

    void Update();
    void Render();
    void GUIRender();

    void ReadClip(string clipName, UINT clipNum = 0, string lockBone = "");
    void PlayClip(int clip, float scale = 1.0f, float takeTime = 0.2f);

    Matrix GetTransformByNode(int nodeIndex);

    ModelClip* GetClip(UINT index) { return clips[index]; }

protected:
    void CreateTexture();
    void CreateClipTransform(UINT index);

    void UpdateFrame();

protected:
    bool isPlay = true;

    vector<ModelClip*> clips;

    FrameBuffer* frameBuffer;

    ClipTransform* clipTransforms;
    ClipTransform* nodeTransforms;

    ID3D11Texture2D* texture = nullptr;
    ID3D11ShaderResourceView* srv;
};