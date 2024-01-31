#pragma once
//ModelData

typedef VertexUVNormalTangentBlend ModelVertex;

struct MeshData
{
    string name;
    UINT materialIndex;

    vector<ModelVertex> vertices;
    vector<UINT> indices;
};

struct NodeData
{
    int index;
    string name;
    int parent;
    Matrix transform;
};

struct BoneData
{
    int index;
    string name;    
    Matrix offset;
};

struct VertexWeights
{
    UINT indices[4] = {};//Bone Index;
    float weights[4] = {};//보간값에 대한 가중치

    void Add(const UINT& index, const float& weight)
    {
        FOR(4)
        {
            if (weights[i] == 0.0f)
            {
                indices[i] = index;
                weights[i] = weight;
                return;
            }
        }
    }

    void Normalize()
    {
        float sum = 0.0f;

        FOR(4)
            sum += weights[i];

        FOR(4)
            weights[i] /= sum;
    }
};

struct KeyVector
{
    float time;
    Float3 value;
};

struct KeyQuat
{
    float time;
    Float4 value;
};

struct KeyData
{
    vector<KeyVector> scales;
    vector<KeyQuat> rotations;
    vector<KeyVector> positions;
};

struct KeyTransform
{
    Float3 scale;
    Float4 rot;
    Float3 pos;
};

struct KeyFrame
{
    string boneName;
    vector<KeyTransform> transforms;
};

struct ClipNode
{
    aiString name;
    vector<KeyTransform> transforms;
};

struct Clip
{
    string name;

    UINT frameCount;
    float tickPerSecond;

    vector<KeyFrame*> keyFrame;
};

struct ClipTransform
{
    Matrix transform[MAX_FRAME][MAX_BONE];
};