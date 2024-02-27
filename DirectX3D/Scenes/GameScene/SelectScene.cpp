#include "Framework.h"
#include "SelectScene.h"
#include "Framework/Model/ModelAnimator.h"
#include "Objects/Basic/Quad.h"
#include "Objects/UI/Button.h"

SelectScene::SelectScene()
{
	CreateBackGround();
	CreatePreviewModels();
	CreateUI();

	// 멤버 변수 초기화
	saveIndex = -1;
	isReady = false;
}

SelectScene::~SelectScene()
{
	for (ModelAnimator* model : previewModels)
	{
		SAFE_DEL(model);
	}
}

void SelectScene::Start()
{
	// 카메라의 타겟 해제
	CAM->SetTarget(nullptr);
	// 카메라 위치 조정
	CAM->Pos() = Vector3(0.0f, 0.0f, -30.0f);
	// 카메라 회전 조정
	CAM->Rot() = Vector3(0.0f, 0.0f, 0.0f);
}

void SelectScene::Update()
{
	Control();
	Loding();

	for (ModelAnimator* model : previewModels)
	{
		if (model && model->Active())
		{
			model->Update();
		}
	}

	start->Update();
}

void SelectScene::PreRender()
{
	backGround->Render();
}

void SelectScene::Render()
{
	for (ModelAnimator* model : previewModels)
	{
		if (model && model->Active())
		{
			model->Render();
		}
	}
}

void SelectScene::PostRender()
{
	for (Quad* icon : icons)
	{
		icon->Render();
	}

	start->Render();

	loding->Render();
}

void SelectScene::GUIRender()
{
	for (ModelAnimator* model : previewModels)
	{
		if (model && model->Active())
		{
			model->GUIRender();
		}
	}
}

void SelectScene::CreateBackGround()
{
	// 배경 생성
	backGround = new Quad(Vector2(WIN_WIDTH, WIN_HEIGHT));
	backGround->GetMaterial()->SetDiffuseMap(L"Textures/SelectScene/background.jpg");
	backGround->Pos() = Vector3(CENTER_X, CENTER_Y);
	backGround->UpdateWorld();

	// 로딩 화면 생성
	loding = new Quad(Vector2(WIN_WIDTH, WIN_HEIGHT));
	loding->GetMaterial()->SetDiffuseMap(L"Textures/SelectScene/loding.jpg");
	loding->Pos() = Vector3(CENTER_X, CENTER_Y);
	loding->SetActive(false);
	loding->UpdateWorld();
}

void SelectScene::CreatePreviewModels()
{
	previewModels.resize(5);

	ModelAnimator* m = new ModelAnimator("armswarrior");
	m->ReadClip("Idle_1");
	m->Pos() = Vector3(0, -8);
	m->Scale() *= 5.0f;
	m->SetActive(false);

	previewModels[0] = m;

	m = new ModelAnimator("ProtectionWarrior");
	m->ReadClip("Idle_1");
	m->Pos() = Vector3(0, -8);
	m->Scale() *= 5.0f;
	m->SetActive(false);

	previewModels[1] = m;

	m = new ModelAnimator("FireMage");
	m->ReadClip("Idle_1");
	m->Pos() = Vector3(0, -8);
	m->Scale() *= 0.01f * 5.0f;
	m->SetActive(false);

	previewModels[2] = m;

	m = new ModelAnimator("MarksmanshipHunter");
	m->ReadClip("Idle");
	m->Pos() = Vector3(0, -8);
	m->Scale() *= 5.0f;
	m->SetActive(false);

	previewModels[3] = m;

	m = new ModelAnimator("HolyPriest");
	m->ReadClip("Idle_1");
	m->Pos() = Vector3(0, -8);
	m->Scale() *= 5.0f;
	m->SetActive(false);

	previewModels[4] = m;
}

void SelectScene::CreateUI()
{
	icons.resize(5);

	for (int i = 0; i < 5; i++)
	{
		Quad* icon = new Quad(Vector2(150, 150));

		wstring temp = L"Textures/UI/Icons/" + to_wstring(i) + L".png";
		icon->GetMaterial()->SetDiffuseMap(temp);
		icon->Pos() = Vector3(1100, 640 - (i * 110), 0);
		icon->UpdateWorld();
		icons[i] = icon;
	}

	start = new Button(L"Textures/UI/Buttons/start.jpg");
	start->Pos() = { CENTER_X, 50 };

	// 이벤트 매핑
	start->SetDownEvent(bind(&SelectScene::OnClick_Start, this));
}

void SelectScene::Control()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		int idx = 0;

		for (Quad* icon : icons)
		{
			if (mousePos.x <= icon->GlobalPos().x + icon->GetSize().x / 2 && mousePos.x >= icon->GlobalPos().x - icon->GetSize().x / 2 &&
				mousePos.y <= icon->GlobalPos().y + icon->GetSize().y / 2 && mousePos.y >= icon->GlobalPos().y - icon->GetSize().y / 2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (previewModels[i]->Active())
					{
						previewModels[i]->SetActive(false);
					}
				}

				previewModels[idx]->SetActive(true);
				previewModels[idx]->PlayClip(0);

				// 해당 인덱스 저장
				saveIndex = idx + 1;
			}

			idx++;
		}
	}
}

void SelectScene::Loding()
{
	// 로딩 준비가 끝나지 않은 경우 반환
	if (!isReady) return;

	// 캐릭터 매니저 조기 로딩 및 플레이어 스폰
	CH_Manager::Get()->PlayerSpawn(saveIndex);

	// 다음 씬으로 전환
	SceneManager::Get()->ChangeScene("Town");
}

void SelectScene::OnClick_Start()
{
	// 캐릭터를 선택하지 않은 경우 반환
	if (saveIndex == -1) return;

	// 로딩 화면 출력
	loding->SetActive(true);

	// 로딩을 위한 준비가 끝났다고 선언
	isReady = true;
}
