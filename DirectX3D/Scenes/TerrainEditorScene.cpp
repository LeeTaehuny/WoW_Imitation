#include "Framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
    terrainEditor = new TerrainEditor();

    //ByteAddress();
}

TerrainEditorScene::~TerrainEditorScene()
{
    delete terrainEditor;
}

void TerrainEditorScene::Update()
{
    terrainEditor->Update();
}

void TerrainEditorScene::PreRender()
{
}

void TerrainEditorScene::Render()
{
    terrainEditor->Render();
}

void TerrainEditorScene::PostRender()
{
}

void TerrainEditorScene::GUIRender()
{
    terrainEditor->GUIRender();
}

void TerrainEditorScene::ByteAddress()
{
    ComputeShader* shader = Shader::AddCS(L"Compute/ByteAddress.hlsl");

    struct Output
    {
        UINT groupID[3];
        UINT groupThreadID[3];
        UINT dispatchThreadID[3];
        UINT groupIndex;
    };

    UINT groupX = 2;
    UINT size = 10 * 8 * 3 * groupX;

    Output* output = new Output[size];
    RawBuffer* buffer = new RawBuffer(sizeof(Output) * size);

    DC->CSSetUnorderedAccessViews(0, 1, &buffer->GetUAV(), nullptr);

    shader->Set();

    DC->Dispatch(groupX, 1, 1);

    buffer->Copy(output, sizeof(Output)* size);

    FILE* file;
    fopen_s(&file, "TextData/RawTest.csv", "w");

    for (UINT i = 0; i < size; i++)
    {
        Output temp = output[i];

        fprintf
        (
            file,
            "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
            i,
            temp.groupID[0], temp.groupID[1], temp.groupID[2],
            temp.groupThreadID[0], temp.groupThreadID[1], temp.groupThreadID[2],
            temp.dispatchThreadID[0], temp.dispatchThreadID[1], temp.dispatchThreadID[2],
            temp.groupIndex
        );
    }
}
