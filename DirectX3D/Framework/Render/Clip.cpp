#include "Framework.h"

Clip::Clip(vector<Frame*> frames, bool isLoop, float speed)
    : frames(frames), isLoop(isLoop), speed(speed)
{
    delayTime = 1.0f / FPS;
}

Clip::~Clip()
{
    for (Frame* frame : frames)
        delete frame;
}

void Clip::Update()
{
    if (!isPlay) return;

    frameTime += speed * DELTA;

    if (frameTime < delayTime) return;

    frameTime -= delayTime;

    curFrameNum++;

    if (isLoop)
    {
        curFrameNum %= frames.size();
    }
    else
    {
        if (curFrameNum >= frames.size())
        {
            curFrameNum--;
            Stop();
        }
    }

    if (events.count(curFrameNum) > 0)
        events[curFrameNum]();
}

void Clip::Render()
{
    frames[curFrameNum]->Render();
}

void Clip::Play()
{
    isPlay = true;
    frameTime = 0.0f;    
    curFrameNum = 0;
}

void Clip::SetEvent(Event event, int frameNum)
{
    if (frameNum < 0 || frameNum >= frames.size())
        frameNum = frames.size() - 1;    

    events[frameNum] = event;
}
