#pragma once

class ModelClip
{
private:
    friend class ModelAnimator;
    friend class ModelAnimatorInstancing;

    ModelClip() = default;
    ~ModelClip();

    void Init();
    void Excute();

    KeyFrame* GetKeyFrame(string boneName);

public:
    void SetEvent(Event event, float timeRatio);

private:
    string name;
    string lockBone;

    UINT frameCount;
    float tickPerSecond;
    float duration;

    float playTime = 0.0f;

    unordered_map<string, KeyFrame*> keyFrames;

    map<float, Event> events;
    map<float, Event>::iterator eventIter;
};