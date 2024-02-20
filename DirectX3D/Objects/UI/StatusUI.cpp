#include "Framework.h"
#include "StatusUI.h"
#include "Objects/Item/Item.h"
#include "Objects/Inventory/Slot.h"
#include "Objects/Character_/CH_Base_ver2.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Item.h"

StatusUI::StatusUI(class CH_Base_ver2* player) : player(player)
{
	// 스탯 창 프레임 설정
	statusFrame = new Slot(L"Textures/UI/status.png", SlotType::Status_Frame);
	statusFrame->Scale() *= 1.5f;
	statusFrame->Pos() = { CENTER_X / 2.0f, CENTER_Y, 1.0f };

	weaponSlot = new Slot(Vector2(33.0f, 33.0f), SlotType::Inventory_Slot);
	weaponSlot->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
	weaponSlot->SetParent(statusFrame);
	weaponSlot->Pos() = Vector3(27, -134, 0);

	Font::Get()->AddColor("White", 1, 1, 1);
	Font::Get()->AddStyle("PGothic", L"맑은 고딕");

	Font::Get()->SetColor("White");

	SetActive(false);

	// 이벤트 등록
	{
		//Observer::Get()->AddEvent("MoveStatusFrame", bind(&StatusUI::MoveStatusFrame, this));
		//Observer::Get()->AddEvent("StopStatusFrame", bind(&StatusUI::StopStatusFrame, this));
	}
}

StatusUI::~StatusUI()
{
	SAFE_DEL(statusFrame);
	SAFE_DEL(weaponSlot);
}

void StatusUI::Update()
{
	if (KEY_DOWN('O'))
	{
		if (Active())
		{
			SetActive(false);
		}
		else
		{
			SetActive(true);
		}
	}

	if (player == nullptr) return;
	if (!Active()) return;

	// 플레이어와 상호작용
	InteractWithPlayer();

	statusFrame->Update();
	weaponSlot->Update();
}

void StatusUI::UIRender()
{
	if (!Active()) return;

	statusFrame->Render();
	weaponSlot->Render();

	// 스텟 렌더링
	RenderStat();
}

void StatusUI::InteractWithPlayer()
{
	// 아이템 장착
	{
		// 좌클릭 시 (인벤토리가 열려있는 상황)
		if (KEY_DOWN(VK_LBUTTON) && player->GetInventory()->Active())
		{
			vector<Slot*> invSlot = player->GetInventory()->GetInvSlots();

			int idx = 0;

			// 모든 칸을 순회하며 선택한 칸을 찾기
			for (Slot* slot : invSlot)
			{
				if (mousePos.x <= slot->GlobalPos().x + slot->GetSize().x && mousePos.x >= slot->GlobalPos().x - slot->GetSize().x &&
					mousePos.y <= slot->GlobalPos().y + slot->GetSize().y && mousePos.y >= slot->GlobalPos().y - slot->GetSize().y)
				{
					// 해당 칸의 아이템 저장
					tempItem = player->GetInventory()->GetInventory()[idx];
					tempIndex = idx;
				}

				idx++;
			}
		}

		// 클릭 해제 시
		if (KEY_UP(VK_LBUTTON) && player->GetInventory()->Active() && tempItem != nullptr && tempIndex != -1)
		{
			// 마우스가 장비창의 아이템 슬롯에 있는지 확인
			if (mousePos.x <= weaponSlot->GlobalPos().x + weaponSlot->GetSize().x && mousePos.x >= weaponSlot->GlobalPos().x - weaponSlot->GetSize().x &&
				mousePos.y <= weaponSlot->GlobalPos().y + weaponSlot->GetSize().y && mousePos.y >= weaponSlot->GlobalPos().y - weaponSlot->GetSize().y)
			{
				// 플레이어 타입별 장착 가능한 무기와 일치하는지 확인
				switch (player->GetProfessionType())
				{
					// 전사(무기)의 경우
				case ProfessionType::ArmsWarrior:
					// 만약 아이템이 무기라면?
					if (Weapon* w = dynamic_cast<Weapon*>(tempItem))
					{
						// 장착 가능한 무기 타입인지 확인하기
						if (w->GetWeaponType() == WeaponType::Sword)
						{
							// 기존 장착했던 무기가 존재하는지 확인하기
							if (weapon != nullptr)
							{
								// 장착했던 무기가 있는 경우 교체
								player->GetInventory()->GetInventory()[tempIndex] = weapon;
								weapon = tempItem;

								player->EquipWeapon(dynamic_cast<Weapon*>(weapon));
							}
							else
							{
								// 장착했던 무기가 없는 경우 새로 끼우기

								// 무기 장착
								weapon = tempItem;
								player->EquipWeapon(dynamic_cast<Weapon*>(weapon));

								// 플레이어 인벤토리 비우기
								player->GetInventory()->GetInventory()[tempIndex] = nullptr;
							}

							// 슬롯 이미지 설정
							weaponSlot->GetMaterial()->SetDiffuseMap(weapon->GetIcon()->GetMaterial()->GetDiffuseMap());
						}
					}

					// 임시 아이템 초기화
					tempItem = nullptr;
					tempIndex = -1;
					break;

					// 마법사(화염)의 경우
				case ProfessionType::FireMage:
					// 만약 아이템이 무기라면?
					if (Weapon* w = dynamic_cast<Weapon*>(tempItem))
					{
						// 장착 가능한 무기 타입인지 확인하기
						if (w->GetWeaponType() == WeaponType::Staff)
						{
							// 기존 장착했던 무기가 존재하는지 확인하기
							if (weapon != nullptr)
							{
								// 장착했던 무기가 있는 경우 교체
								player->GetInventory()->GetInventory()[tempIndex] = weapon;
								weapon = tempItem;

								player->EquipWeapon(dynamic_cast<Weapon*>(weapon));
							}
							else
							{
								// 장착했던 무기가 없는 경우 새로 끼우기

								// 무기 장착
								weapon = tempItem;
								player->EquipWeapon(dynamic_cast<Weapon*>(weapon));

								// 플레이어 인벤토리 비우기
								player->GetInventory()->GetInventory()[tempIndex] = nullptr;
							}

							// 슬롯 이미지 설정
							weaponSlot->GetMaterial()->SetDiffuseMap(weapon->GetIcon()->GetMaterial()->GetDiffuseMap());
						}
					}

					// 임시 아이템 초기화
					tempItem = nullptr;
					tempIndex = -1;
					break;

					// 사제(신성)의 경우
				case ProfessionType::HolyPriest:
					// 만약 아이템이 무기라면?
					if (Weapon* w = dynamic_cast<Weapon*>(tempItem))
					{
						// 장착 가능한 무기 타입인지 확인하기
						if (w->GetWeaponType() == WeaponType::Staff)
						{
							// 기존 장착했던 무기가 존재하는지 확인하기
							if (weapon != nullptr)
							{
								// 장착했던 무기가 있는 경우 교체
								player->GetInventory()->GetInventory()[tempIndex] = weapon;
								weapon = tempItem;

								player->EquipWeapon(dynamic_cast<Weapon*>(weapon));
							}
							else
							{
								// 장착했던 무기가 없는 경우 새로 끼우기

								// 무기 장착
								weapon = tempItem;
								player->EquipWeapon(dynamic_cast<Weapon*>(weapon));

								// 플레이어 인벤토리 비우기
								player->GetInventory()->GetInventory()[tempIndex] = nullptr;
							}

							// 슬롯 이미지 설정
							weaponSlot->GetMaterial()->SetDiffuseMap(weapon->GetIcon()->GetMaterial()->GetDiffuseMap());
						}
					}

					// 임시 아이템 초기화
					tempItem = nullptr;
					tempIndex = -1;
					break;

					// 사냥꾼(속사)의 경우
				case ProfessionType::MarksmanshipHunter:
					// 만약 아이템이 무기라면?
					if (Weapon* w = dynamic_cast<Weapon*>(tempItem))
					{
						// 장착 가능한 무기 타입인지 확인하기
						if (w->GetWeaponType() == WeaponType::Bow)
						{
							// 기존 장착했던 무기가 존재하는지 확인하기
							if (weapon != nullptr)
							{
								// 장착했던 무기가 있는 경우 교체
								player->GetInventory()->GetInventory()[tempIndex] = weapon;
								weapon = tempItem;

								player->EquipWeapon(dynamic_cast<Weapon*>(weapon));
							}
							else
							{
								// 장착했던 무기가 없는 경우 새로 끼우기

								// 무기 장착
								weapon = tempItem;
								player->EquipWeapon(dynamic_cast<Weapon*>(weapon));

								// 플레이어 인벤토리 비우기
								player->GetInventory()->GetInventory()[tempIndex] = nullptr;
							}

							// 슬롯 이미지 설정
							weaponSlot->GetMaterial()->SetDiffuseMap(weapon->GetIcon()->GetMaterial()->GetDiffuseMap());
						}
					}

					// 임시 아이템 초기화
					tempItem = nullptr;
					tempIndex = -1;
					break;

					// 성기사(보호)의 경우
				case ProfessionType::ProtectionWarrior:
					// 만약 아이템이 무기라면?
					if (Weapon* w = dynamic_cast<Weapon*>(tempItem))
					{
						// 장착 가능한 무기 타입인지 확인하기
						if (w->GetWeaponType() == WeaponType::Hammer)
						{
							// 기존 장착했던 무기가 존재하는지 확인하기
							if (weapon != nullptr)
							{
								// 장착했던 무기가 있는 경우 교체
								player->GetInventory()->GetInventory()[tempIndex] = weapon;
								weapon = tempItem;

								player->EquipWeapon(dynamic_cast<Weapon*>(weapon));
							}
							else
							{
								// 장착했던 무기가 없는 경우 새로 끼우기

								// 무기 장착
								weapon = tempItem;
								player->EquipWeapon(dynamic_cast<Weapon*>(weapon));

								// 플레이어 인벤토리 비우기
								player->GetInventory()->GetInventory()[tempIndex] = nullptr;
							}

							// 슬롯 이미지 설정
							weaponSlot->GetMaterial()->SetDiffuseMap(weapon->GetIcon()->GetMaterial()->GetDiffuseMap());
						}
					}

					// 임시 아이템 초기화
					tempItem = nullptr;
					tempIndex = -1;
					break;

				default:
					break;
				}
			}
			// 장비 창에 마우스가 없으므로 임시 아이템 초기화
			else
			{
				tempItem = nullptr;
				tempIndex = -1;
			}
		}
	}

	// 아이템 해제
	{
		// 인벤토리가 열려있고, 우클릭을 한 경우
		if (player->GetInventory()->Active() && KEY_DOWN(VK_RBUTTON))
		{
			// 장비칸에 마우스가 있는지 확인
			if (mousePos.x <= weaponSlot->GlobalPos().x + weaponSlot->GetSize().x && mousePos.x >= weaponSlot->GlobalPos().x - weaponSlot->GetSize().x &&
				mousePos.y <= weaponSlot->GlobalPos().y + weaponSlot->GetSize().y && mousePos.y >= weaponSlot->GlobalPos().y - weaponSlot->GetSize().y)
			{
				// 인벤토리에 아이템 push
				player->GetInventory()->AddItem(weapon);

				// 무기 장착 해제
				player->ClearWeapon();
				weapon = nullptr;
				weaponSlot->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
			}
		}
	}
}

void StatusUI::RenderStat()
{
	string tempString;

	tempString = "maxHP : " + to_string((int)player->GetStat().maxHp);
	Font::Get()->RenderText(tempString, { statusFrame->GlobalPos().x,  statusFrame->GlobalPos().y + 120 });

	tempString = "maxMP : " + to_string((int)player->GetStat().maxMp);
	Font::Get()->RenderText(tempString, { statusFrame->GlobalPos().x,  statusFrame->GlobalPos().y + 90 });

	if (weapon != nullptr)
	{
		tempString = "공격력 : " + to_string((int)player->GetStat().damage + player->GetWeapon()->GetWeaponDamage());
	}
	else
	{
		tempString = "공격력 : " + to_string((int)player->GetStat().damage);
	}

	int padding = 0;
	if (tempString.size() > 12)
	{
		padding = tempString.size() - 12;
	}
	
	Font::Get()->RenderText(tempString, { statusFrame->GlobalPos().x + padding * 10,  statusFrame->GlobalPos().y + 30 });

	tempString = "방어력 : " + to_string((int)player->GetStat().defence);
	Font::Get()->RenderText(tempString, { statusFrame->GlobalPos().x,  statusFrame->GlobalPos().y });
}

void StatusUI::MoveStatusFrame()
{
	// 인벤토리 프레임이 선택되었다면?
	if (statusFrame->GetSelect())
	{
		// 슬롯이 선택된 것이 아닌지 체크하기
		if (mousePos.x <= weaponSlot->GlobalPos().x + weaponSlot->GetSize().x && mousePos.x >= weaponSlot->GlobalPos().x - weaponSlot->GetSize().x &&
			mousePos.y <= weaponSlot->GlobalPos().y + weaponSlot->GetSize().y && mousePos.y >= weaponSlot->GlobalPos().y - weaponSlot->GetSize().y)
		{
			return;
		}

		// 마우스 이동량의 Delta값 만큼 이동시키기
		if (!bIsMove)
		{
			prevPos = mousePos;
			bIsMove = true;
		}
		else
		{
			float deltaX = prevPos.x - mousePos.x;
			float deltaY = prevPos.y - mousePos.y;

			statusFrame->Pos().x += -deltaX;
			statusFrame->Pos().y += -deltaY;

			prevPos = mousePos;
		}
	}
}

void StatusUI::StopStatusFrame()
{
	// 이동중이 아니라고 설정
	bIsMove = false;
}
