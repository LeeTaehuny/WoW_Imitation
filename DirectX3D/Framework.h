﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define MAX_LIGHT 10
#define MAX_BONE 512
#define MAX_FRAME 2048
#define MAX_INSTANCE 128

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define DELTA Timer::Get()->GetElapsedTime()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define CAM Environment::Get()->GetMainCamera()

#define DIALOG ImGuiFileDialog::Instance()

#define FOR(n) for(int i = 0; i < n ; i++)

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <assert.h>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <DirectXCollision.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <ImGuiFileDialog.h>
#include <d2d1_2.h>
#include <dwrite.h>
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>
#include <FMOD/fmod.hpp>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "DirectXTex.lib")
#pragma comment(lib, "ImGui.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "assimp-vc143-mtd.lib")
#pragma comment(lib, "fmod_vc.lib")

using namespace std;
using namespace DirectX;
using namespace DirectX::TriangleTests;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMVECTOR Vector4;
typedef XMMATRIX Matrix;
typedef XMFLOAT4X4 Float4x4;

typedef function<void()> Event;
typedef function<void(void*)> ParamEvent;
typedef function<void(int)> IntParamEvent;

//Framework Header
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/BinaryReader.h"
#include "Framework/Utilities/BinaryWriter.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/tinyxml2.h"
#include "Framework/Utilities/Observer.h"
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Font.h"
#include "Framework/Utilities/Audio.h"

using namespace Utility;

#include "Framework/System/Device.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/GlobalBuffer.h"
#include "Framework/Buffer/RawBuffer.h"
#include "Framework/Buffer/StructuredBuffer.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"
#include "Framework/Shader/ComputeShader.h"
#include "Framework/Shader/GeometryShader.h"
#include "Framework/Shader/HullShader.h"
#include "Framework/Shader/DomainShader.h"

#include "Framework/State/RasterizerState.h"
#include "Framework/State/SamplerState.h"
#include "Framework/State/BlendState.h"
#include "Framework/State/DepthStencilState.h"

#include "Framework/Math/Vector2.h"
#include "Framework/Math/Vector3.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/GameMath.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/Material.h"
#include "Framework/Render/Mesh.h"
#include "Framework/Render/DepthStencil.h"
#include "Framework/Render/RenderTarget.h"
#include "Framework/Render/GBuffer.h"

#include "Framework/Collision/Collider.h"
#include "Framework/Collision/BoxCollider.h"
#include "Framework/Collision/SphereCollider.h"
#include "Framework/Collision/CapsuleCollider.h"

#include "Framework/Model/ModelData.h"
#include "Framework/Model/ModelExporter.h"
#include "Framework/Model/ModelMesh.h"
#include "Framework/Model/Model.h"
#include "Framework/Model/ModelClip.h"
#include "Framework/Model/ModelAnimator.h"
#include "Framework/Model/ModelInstancing.h"
#include "Framework/Model/ModelAnimatorInstancing.h"

using namespace GameMath;

#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"
#include "Framework/Environment/Shadow.h"
#include "Framework/Environment/Reflection.h"
#include "Framework/Environment/Refraction.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Quad.h"
#include "Objects/Basic/Cube.h"
#include "Objects/Basic/Sphere.h"
#include "Objects/Basic/Cylinder.h"

#include "Objects/Actor/ActorUI.h"
#include "Objects/UI/ProgressBar.h"

#include "Objects/Landscape/Terrain.h"
#include "Objects/Landscape/TerrainEditor.h"
#include "Objects/Landscape/Skybox.h"
#include "Objects/Landscape/Water.h"
#include "Objects/Landscape/TerrainLOD.h"
#include "Objects/Landscape/TerrainData.h"
#include "Objects/Landscape/QuadTreeTerrain.h"

#include "Objects/Static/Reflector.h"

#include "Objects/Particle/ParticleSystem.h"
#include "Objects/Particle/Particle.h"
#include "Objects/Particle/Rain.h"
#include "Objects/Particle/Snow.h"
#include "Objects/Particle/Sprite.h"
#include "Objects/Particle/Spark.h"
#include "Objects/Particle/Trail.h"

#include "Objects/Algorithm/Node.h"
#include "Objects/Algorithm/Heap.h"
#include "Objects/Algorithm/AStar.h"

#include "Objects/Items/Weapons/Crowbar.h"
#include "Objects/Items/Weapons/Kunai.h"

#include "Objects/Character/Human.h"
#include "Objects/Character/Naruto.h"
#include "Objects/Character/Robot.h"
#include "Objects/Character/Fox.h"

#include "Objects/Manager/BlockManager.h"
#include "Objects/Manager/KunaiManager.h"
#include "Objects/Manager/RobotManager.h"

#include "Objects/Test/TestLight.h"

//Scene Header
#include "Scenes/Scene.h"

#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"

extern HWND hWnd;
extern Vector3 mousePos;