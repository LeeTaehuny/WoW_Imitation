#include "Framework.h"

ModelMesh::ModelMesh(string name) : name(name)
{
}

ModelMesh::~ModelMesh()
{
    delete mesh;
}

void ModelMesh::Render()
{
    material->Set();
    mesh->Draw();
}

void ModelMesh::RenderInstanced(UINT instanceCount)
{
    material->Set();
    mesh->DrawInstanced(instanceCount);
}

void ModelMesh::CreateMesh(void* vertexData, UINT vertexCount, void* indexData, UINT indexCount)
{
    mesh = new Mesh<ModelVertex>();

    mesh->GetVertices().resize(vertexCount);
    memcpy(mesh->GetVertices().data(), vertexData, sizeof(ModelVertex) * vertexCount);

    mesh->GetIndices().resize(indexCount);
    memcpy(mesh->GetIndices().data(), indexData, sizeof(UINT) * indexCount);

    mesh->CreateMesh();
}
