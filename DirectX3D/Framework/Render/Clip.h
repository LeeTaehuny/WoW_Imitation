#pragma once

class Clip
{
private:
    const float FPS = 10.0f;

public:
    Clip(vector<Frame*> frames, bool isLoop = true, float speed = 1.0f);
    ~Clip();

    void Update();
    void Render();

    void Play();
    void Stop() { isPlay = false; }

    void SetEvent(Event event, int frameNum = -1);

    Frame* GetCurFrame() { return frames[curFrameNum]; }

private:
    vector<Frame*> frames;

    UINT curFrameNum = 0;

    float frameTime = 0.0f;    
    float speed = 0.0f;
    float delayTime = 0.0f;

    bool isLoop = false;
    bool isPlay = false;

    map<int, Event> events;
};