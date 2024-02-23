#pragma once

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

#define MONSTER MonsterManager::Get()

#define FOR(n) for(int i = 0; i < n ; i++)

#define SAFE_DEL(p) \
if (p != nullptr)	\
{					\
	delete p;		\
	p = nullptr;	\
}					\

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <queue>
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

// 캐릭터 인스턴싱 버전
#include "Objects/Character_/CH_Base_ver2.h"
#include "Objects/Character_/ArmsWarrior_in.h"
#include "Objects/Character_/FireMage_in.h"
#include "Objects/Character_/HolyPriest_in.h"
#include "Objects/Character_/MarksmanshipHunter_in.h"
#include "Objects/Character_/ProtectionWarrior_in.h"
#include "Objects/Character_/CH_Manager.h"

#include "Objects/Manager/BlockManager.h"
#include "Objects/Manager/KunaiManager.h"
#include "Objects/Manager/RobotManager.h"

// 몬스터
#include "Objects/Monster/MonsterBase.h"
#include "Objects/Monster/Skeleton.h"
#include "Objects/Monster/Skeleton_Knight.h"
#include "Objects/Monster/Scarecrow.h"
#include "Objects/Monster/VAlkier.h"
#include "Objects/Monster/IceBall.h"
#include "Objects/Monster/MonsterManager.h"
#include "Objects/Monster/Boss/Boss_LichKing.h"

#include "Objects/Monster/Boss/Lich_000_Base.h"
#include "Objects/Monster/Boss/Lich_001_Necrotic_Plague.h"
#include "Objects/Monster/Boss/Lich_002_Infest.h"
#include "Objects/Monster/Boss/Lich_003_Summon_Drudge_Ghouls.h"
#include "Objects/Monster/Boss/Lich_004_Summon_Shambling_Horror.h"
#include "Objects/Monster/Boss/Lich_005_Remorseless_Winter.h"

// 스킬 배이스
#include "Objects/Skills/Base/SkillBase.h"

// 스킬
#include "Objects/Skills/FireBall.h"

// 화염 마법사 스킬
#include "Objects/Skills/FireMage_Skill/F_000_Basic_Atttack.h"
#include "Objects/Skills/FireMage_Skill/F_001_Pyroblast.h"
#include "Objects/Skills/FireMage_Skill/F_002_FireBlast.h"
#include "Objects/Skills/FireMage_Skill/F_004_Scorch.h"
#include "Objects/Skills/FireMage_Skill/F_005_PhoenixFlame.h"
#include "Objects/Skills/FireMage_Skill/F_009_Combustion.h"
#include "Objects/Skills/FireMage_Skill/F_010_Meteor.h"

// 무기 전사 스킬
#include "Objects/Skills/ArmsWarrior_Skill/A_001_MortalStrike.h"
#include "Objects/Skills/ArmsWarrior_Skill/A_002_Overpower.h"
#include "Objects/Skills/ArmsWarrior_Skill/A_004_DiebytheSword.h"
#include "Objects/Skills/ArmsWarrior_Skill/A_007_ColossusSmash.h"
#include "Objects/Skills/ArmsWarrior_Skill/A_010_Bladestorm.h"

// 보호 성기사 스킬
#include "Objects/Skills/ProtectionWarrior_Skill/P_001_Avengers_Shield.h"
#include "Objects/Skills/ProtectionWarrior_Skill/P_002_HOTR.h"
#include "Objects/Skills/ProtectionWarrior_Skill/P_003_Grand_Crusader.h"
#include "Objects/Skills/ProtectionWarrior_Skill/P_004_Ardent_Defender.h"
#include "Objects/Skills/ProtectionWarrior_Skill/P_005_Barricade_Of_Faith.h"
#include "Objects/Skills/ProtectionWarrior_Skill/P_006_Bulwark_Of_Order.h"
#include "Objects/Skills/ProtectionWarrior_Skill/P_007_Blessing_of_Spellwarding.h"
#include "Objects/Skills/ProtectionWarrior_Skill/P_008_Guardian_Of_Ancient_Kings.h"
#include "Objects/Skills/ProtectionWarrior_Skill/P_009_Eye_Of_Tyr.h"
#include "Objects/Skills/ProtectionWarrior_Skill/P_010_Moment_Of_Glory.h"

// 신성 사제 스킬
#include "Objects/Skills/HolyPriest_Skill/H_000_Basic_Atttack.h"
#include "Objects/Skills/HolyPriest_Skill/H_001_Holy_Word_Serenity.h"
#include "Objects/Skills/HolyPriest_Skill/H_002_Holy_Word_Sanctify.h"
#include "Objects/Skills/HolyPriest_Skill/H_003_Guardian_Spirit.h"
#include "Objects/Skills/HolyPriest_Skill/H_004_Holy_Word_Chastise.h"
#include "Objects/Skills/HolyPriest_Skill/H_005_Censure.h"
#include "Objects/Skills/HolyPriest_Skill/H_006_Circle_Of_Healing.h"
#include "Objects/Skills/HolyPriest_Skill/H_007_Cosmic_Ripple.h"
#include "Objects/Skills/HolyPriest_Skill/H_008_Divine_Hymn.h"
#include "Objects/Skills/HolyPriest_Skill/H_009_Enlightenment.h"
#include "Objects/Skills/HolyPriest_Skill/H_010_Everlasting_Light.h"

// 사격 사냥꾼 스킬
#include "Objects/Skills/MarksmanshipHunter_Skill/Arrow.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/ArrowManager.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/M_000_Basic_Atttack.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/M_001_Aimed_Shot.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/M_002_Crack_Shot.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/M_003_Rapid_Fire.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/M_004_Lone_Wolf.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/M_005_Chimaera_Shot.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/M_006_Streamline.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/M_007_Focused_Aim.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/M_008_Multi_Shot.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/M_009_Volley.h"
#include "Objects/Skills/MarksmanshipHunter_Skill/M_010_Wailing_Arrow.h"

#include "Objects/Test/TestLight.h"

#include "Objects/MAP/BossMap.h"
#include "Objects/MAP/Dungeon.h"

//Scene Header
#include "Scenes/Scene.h"

#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"

extern HWND hWnd;
extern Vector3 mousePos;