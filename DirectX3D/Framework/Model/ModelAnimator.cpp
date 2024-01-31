#include "Framework.h"

ModelAnimator::ModelAnimator(string name)
    : Model(name)
{
    SetShader(L"Model/ModelAnimation.hlsl");

    frameBuffer = new FrameBuffer();

    worldBuffer->SetType(1);
}

ModelAnimator::~ModelAnimator()
{
    for (ModelClip* clip : clips)
        delete clip;

    delete frameBuffer;

    delete[] clipTransforms;
    delete[] nodeTransforms;

    texture->Release();
    srv->Release();
}

void ModelAnimator::Update()
{
    UpdateFrame();
    UpdateWorld();
}

void ModelAnimator::Render()
{
    if (texture == nullptr)
        CreateTexture();

    frameBuffer->SetVS(3);
    DC->VSSetShaderResources(0, 1, &srv);

    Model::Render();
}

void ModelAnimator::GUIRender()
{
    //int clip = frameBuffer->Get().clip;
    //ImGui::SliderInt("Clip", &frameBuffer->Get().clip, 0, clips.size() - 1);
    //ImGui::SliderInt("Frame", (int*) & frameBuffer->Get().curFrame,
    //    0, clips[clip]->frameCount - 1);
    //ImGui::SliderFloat("Scale", &frameBuffer->Get().scale, 0, 10.0f);

    Model::GUIRender();
}

void ModelAnimator::ReadClip(string clipName, UINT clipNum, string lockBone)
{
    string path = "Models/Clips/" + name + "/"
        + clipName + to_string(clipNum) + ".clip";

    BinaryReader* reader = new BinaryReader(path);

    ModelClip* clip = new ModelClip();
    clip->name = reader->String();
    clip->lockBone = lockBone;
    clip->frameCount = reader->UInt();
    clip->tickPerSecond = reader->Float();

    UINT boneCount = reader->UInt();
    FOR(boneCount)
    {
        KeyFrame* keyFrame = new KeyFrame();
        keyFrame->boneName = reader->String();

        UINT size = reader->UInt();
        if (size > 0)
        {
            keyFrame->transforms.resize(size);

            void* ptr = (void*)keyFrame->transforms.data();
            reader->Byte(&ptr, sizeof(KeyTransform) * size);
        }
        clip->keyFrames[keyFrame->boneName] = keyFrame;        
    }

    clips.push_back(clip);

    delete reader;
}

void ModelAnimator::PlayClip(int clip, float scale, float takeTime)
{
    isPlay = true;

    frameBuffer->Get().next.clip = clip;
    frameBuffer->Get().next.scale = scale;
    frameBuffer->Get().takeTime = takeTime;

    clips[clip]->Init();
}

Matrix ModelAnimator::GetTransformByNode(int nodeIndex)
{
    if (texture == nullptr) return XMMatrixIdentity();

    Matrix curAnim;

    {//CurAnim
        Frame& curFrame = frameBuffer->Get().cur;

        Matrix cur = nodeTransforms[curFrame.clip].transform[curFrame.curFrame][nodeIndex];
        Matrix next = nodeTransforms[curFrame.clip].transform[curFrame.curFrame + 1][nodeIndex];

        curAnim = Lerp(cur, next, curFrame.time) * world;
    }

    {//NextAnim
        Frame& nextFrame = frameBuffer->Get().next;

        if (nextFrame.clip == -1)
            return curAnim;

        Matrix cur = nodeTransforms[nextFrame.clip].transform[nextFrame.curFrame][nodeIndex];
        Matrix next = nodeTransforms[nextFrame.clip].transform[nextFrame.curFrame + 1][nodeIndex];

        Matrix nextAnim = Lerp(cur, next, nextFrame.time) * world;

        return Lerp(curAnim, nextAnim, frameBuffer->Get().tweenTime);
    }    
}

void ModelAnimator::CreateTexture()
{
    UINT clipCount = clips.size();

    clipTransforms = new ClipTransform[clipCount];
    nodeTransforms = new ClipTransform[clipCount];

    FOR(clipCount)
        CreateClipTransform(i);

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = MAX_BONE * 4;
    desc.Height = MAX_FRAME;
    desc.MipLevels = 1;
    desc.ArraySize = clipCount;
    desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_IMMUTABLE;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    UINT pitchSize = MAX_BONE * sizeof(Matrix);
    UINT pageSize = pitchSize * MAX_FRAME;

    void* p = VirtualAlloc(nullptr, pageSize * clipCount,
        MEM_RESERVE, PAGE_READWRITE);

    FOR(clipCount)
    {
        UINT start = i * pageSize;

        for (UINT y = 0; y < MAX_FRAME; y++)
        {
            void* temp = (BYTE*)p + pitchSize * y + start;

            VirtualAlloc(temp, pitchSize, MEM_COMMIT, PAGE_READWRITE);
            memcpy(temp, clipTransforms[i].transform[y], pitchSize);
        }
    }

    D3D11_SUBRESOURCE_DATA* subResource = new D3D11_SUBRESOURCE_DATA[clipCount];

    FOR(clipCount)
    {
        void* temp = (BYTE*)p + i * pageSize;

        subResource[i].pSysMem = temp;
        subResource[i].SysMemPitch = pitchSize;
        subResource[i].SysMemSlicePitch = pageSize;
    }

    DEVICE->CreateTexture2D(&desc, subResource, &texture);

    delete[] subResource;
    VirtualFree(p, 0, MEM_RELEASE);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
    srvDesc.Texture2DArray.MipLevels = 1;
    srvDesc.Texture2DArray.ArraySize = clipCount;

    DEVICE->CreateShaderResourceView(texture, &srvDesc, &srv);
}

void ModelAnimator::CreateClipTransform(UINT index)
{
    ModelClip* clip = clips[index];

    FOR(clip->frameCount)
    {
        UINT nodeIndex = 0;

        for (NodeData node : nodes)
        {
            Matrix animation;
            KeyFrame* frame = clip->GetKeyFrame(node.name);
            if (frame != nullptr)
            {
                KeyTransform& transform = frame->transforms[i];

                if (node.name == clip->lockBone)
                {
                    transform.pos = {};
                }

                animation = XMMatrixTransformation(XMVectorZero(),
                    XMQuaternionIdentity(), Vector3(transform.scale),
                    XMVectorZero(), XMLoadFloat4(&transform.rot),
                    Vector3(transform.pos));
            }
            else
            {
                animation = XMMatrixIdentity();
            }

            Matrix parent;
            int parentIndex = node.parent;

            if (parentIndex < 0)
                parent = XMMatrixIdentity();
            else
                parent = nodeTransforms[index].transform[i][parentIndex];

            nodeTransforms[index].transform[i][nodeIndex] = animation * parent;

            int boneIndex = -1;
            if (boneMap.count(node.name))
                boneIndex = boneMap[node.name];
            
            if (boneIndex >= 0)
            {
                Matrix offset = bones[boneIndex].offset;
                offset *= nodeTransforms[index].transform[i][nodeIndex];

                clipTransforms[index].transform[i][boneIndex] = offset;
            }
            nodeIndex++;
        }
    }
}

void ModelAnimator::UpdateFrame()
{
    if (!isPlay) return;

    FrameBuffer::Data& frameData = frameBuffer->Get();

    {
        ModelClip* clip = clips[frameData.cur.clip];

        clip->playTime += frameData.cur.scale * DELTA;
        frameData.cur.time += clip->tickPerSecond * frameData.cur.scale * DELTA;

        if (frameData.cur.time >= 1.0f)
        {
            frameData.cur.curFrame = (frameData.cur.curFrame + 1) % (clip->frameCount - 1);
            frameData.cur.time -= 1.0f;
        }

        clip->Excute();
    }

    {
        if (frameData.next.clip < 0) return;

        ModelClip* clip = clips[frameData.next.clip];

        frameData.tweenTime += DELTA / frameData.takeTime;

        if (frameData.tweenTime >= 1.0f)
        {
            frameData.cur = frameData.next;
            frameData.tweenTime = 0.0f;

            frameData.next.clip = -1;
            frameData.next.curFrame = 0;
            frameData.next.time = 0.0f;
            return;
        }        

        frameData.next.time += clip->tickPerSecond * frameData.next.scale * DELTA;

        if (frameData.next.time >= 1.0f)
        {
            frameData.next.curFrame = (frameData.next.curFrame + 1) % (clip->frameCount - 1);
            frameData.next.time -= 1.0f;
        }
    }
}
