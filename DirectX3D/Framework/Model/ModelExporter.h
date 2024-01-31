#pragma once

class ModelExporter
{
public:
    ModelExporter(string name, string file);
    ~ModelExporter();

    void ExportMaterial();
    void ExportMesh();
    void ExportClip(string clipName);

private:
    //Material
    void ReadMaterial();
    void WriteMaterial();
    string CreateTexture(string file);

    //Mesh
    void ReadMesh(aiNode* node);
    void ReadNode(aiNode* node, int index, int parent);
    void ReadBone(aiMesh* mesh, vector<VertexWeights>& vertexWeights);
    void WriteMesh();

    //Clip
    Clip* ReadClip(aiAnimation* animation);
    void ReadKeyFrame(Clip* clip, aiNode* node, vector<ClipNode>& clipNodes);
    void WriterClip(Clip* clip, string clipName, UINT index);
    void SetClipNode(const KeyData& keyData, const UINT& frameCount, ClipNode& clipNode);
    Float3 CalcInterpolationVector(const vector<KeyVector>& keyData, UINT& count, int curFrame);
    Float4 CalcInterpolationQuat(const vector<KeyQuat>& keyData, UINT& count, int curFrame);

private:
    Assimp::Importer* importer;
    const aiScene* scene;

    string name;

    vector<Material*> materials;
    vector<MeshData*> meshes;
    vector<NodeData*> nodes;
    vector<BoneData*> bones;

    map<string, UINT> boneMap;
    UINT boneCount = 0;
};