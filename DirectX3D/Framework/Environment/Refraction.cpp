#include "Framework.h"

Refraction::Refraction(wstring normalFile)
{
    waterBuffer = new WaterBuffer();

    normalMap = Texture::Add(normalFile);

    renderTarget = new RenderTarget(2048, 2048);
    depthStencil = new DepthStencil(2048, 2048);

    quad = new Quad(Vector2(200, 200));
    quad->Pos() = { 100, 100, 0 };
    Texture* texture = Texture::Add(L"Refraction", renderTarget->GetSRV());
    quad->GetMaterial()->SetDiffuseMap(texture);
    quad->UpdateWorld();
}

Refraction::~Refraction()
{
    delete renderTarget;
    delete depthStencil;
    delete waterBuffer;
    delete quad;
}

void Refraction::Update()
{
    waterBuffer->Get().waveTime += DELTA;
}

void Refraction::SetRefraction()
{
    renderTarget->Set(depthStencil);
}

void Refraction::SetRender()
{
    waterBuffer->SetPS(10);    
    DC->PSSetShaderResources(11, 1, &renderTarget->GetSRV());
    normalMap->PSSet(12);
}

void Refraction::PostRender()
{
    quad->Render();
}

void Refraction::GUIRender()
{
    ImGui::Text("Water Option");
    ImGui::ColorEdit4("WaveColor", (float*)&waterBuffer->Get().color);

    ImGui::SliderFloat("WaveSpeed", &waterBuffer->Get().waveSpeed, 0.0f, 1.0f);
    ImGui::SliderFloat("WaveScale", &waterBuffer->Get().waveScale, 0.0f, 1.0f);
    ImGui::SliderFloat("WaveShininess", &waterBuffer->Get().waveShininess, 1.0f, 50.0f);
    ImGui::SliderFloat("WaveFresnel", &waterBuffer->Get().fresnel, 0.0f, 1.0f);
}
