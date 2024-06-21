# [DirectX11 3D Team Project] WoW_Imitation
## 개요
- 원작 : World of Warcraft
- 장르 : RPG
- 개발 기간 : 5주 (24.01.22 ~ 24.02.29 [기획 & 리소스 수집 및 개발])
- 개발 인원 : 3인 (김진우, 이태현, 최성빈)
- 개발 목적 : 전통 RPG요소를 직접 구현해보며 그래픽스에 대한 공부내용 적용
- 개발 환경    
    * 사용 언어 : C++    
    * Tool : Visual Studio 2022    
    * WinAPI 환경에서의 DirectX11 API 사용
    * 설명 영상 링크 : https://youtu.be/nIsQ_ebXqDI

## 구현 목표
![image](https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/9d53bea6-5575-4040-8d58-cd8c2e21a0d6)

![image](https://github.com/LeeTaehuny/BTD5_Imitation/assets/105622632/ad4e6dfb-2635-4497-85af-3930b353d207)    
     
## 프로젝트 역할 분담
![image](https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/88ccb044-78e9-4969-84e8-8846cecdeea7)

### 구현 - 모델 스키닝 작업
<img src="https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/fddb54d2-9fc1-4f62-9306-0b66342e5d72" width="300" height="300"/>
<img src="https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/0dfc5fd1-aafd-4fa4-a77a-05146fbefa71" width="300" height="300"/> 
     
- 믹사모 자동 리깅 후 애니메이션이 이상하게 출력되어 캐릭터 애니메이션을 자연스럽게 스킨 메쉬(Skin Mesh)에 대한 가중치를 조정하는 작업을 진행했습니다.
- 블렌더를 사용한 웨이트 페인팅 작업을 통해 모델의 움직임을 자연스럽게 수정했습니다.        

### 구현 - 캐릭터 & 스킬 시스템
- 캐릭터는 5가지(전사, 성기사, 사제, 사냥꾼, 마법사)가 존재합니다.
- 플레이어는 직접 조작이 가능합니다.
  - 'W', 'S' 키를 이용해 앞, 뒤로 이동이 가능하며 , 이동 중 'A','D' 키로 방향을 변경할 수 있습니다.
  - 'Q', 'E' 키를 이용해 좌, 우로 이동이 가능합니다.
- 캐릭터별 10가지 스킬을 가지고 있으며 스킬 트리를 구현해 [선행 스킬]을 배운 경우에만 새로운 스킬을 배울 수 있도록 설정했습니다.          
- 캐릭터별 스킬 정리     
  [무기 전사](https://github.com/LeeTaehuny/WoW_Imitation/blob/main/Description/ArmsWarrior.md)      
  [보호 성기사](https://github.com/LeeTaehuny/WoW_Imitation/blob/main/Description/ProtectionWarrior.md)       
  [신성 사제](https://github.com/LeeTaehuny/WoW_Imitation/blob/main/Description/HolyPriest.md)       
  [사격 사냥꾼](https://github.com/LeeTaehuny/WoW_Imitation/blob/main/Description/MarksmanshipHunter.md)       
  [화염 마법사](https://github.com/LeeTaehuny/WoW_Imitation/blob/main/Description/FireMage.md)     
- 모든 모델 및 애니메이션은 Assimp 라이브러리를 사용해 추출하였습니다.
       
### 구현 - 캐릭터 선택 (Select Scene)    
<img src="https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/6a615724-e9fb-4218-b88f-54056e2bb43e" width="800" height="500"/>

- 게임을 시작하면 처음 마주하는 씬에서 캐릭터를 선택할 수 있습니다.
- 캐릭터는 총 5종이며 선택한 아이콘에 맞는 캐릭터의 프리뷰를 화면에 출력하였습니다.
- 캐릭터를 선택하면 해당 캐릭터의 음성 및 기본 Idle 동작을 재생하였습니다.
- 선택된 캐릭터가 존재하는 경우 "접속"버튼을 통해 마을로 이동이 가능합니다.


### 구현 - 길드 시스템 (동료 NPC)
<img src="https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/705f4c20-c70c-4b97-a9d0-bf19271fa082" width="800" height="400"/>     

- 플레이어는 마을에서 길드를 통해 동료(NPC)를 최대 5명까지 모집할 수 있습니다.
- 파티원을 추가하면 우측 중앙에 파티원의 현재 체력 상태를 볼 수 있는 UI를 추가하였습니다.     
<img src="https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/82e1095e-4235-4250-a488-6477a0bab9d6" width="200" height="200"/>    


- 각 NPC의 공격 타입(근접, 원거리, 힐러)에 따라 행동 패턴을 구분지어 구현하였습니다.
  <img src="https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/86290ee4-e82f-4ae8-b825-74603f0624c0" width="1000" height="500"/>    
   


### 구현 - 인벤토리 & 상점 시스템
![image](https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/6ed6786e-3702-4714-9ae1-2167578e6ac2)     

- 플레이어는 마을에서 상점을 통해 아이템(무기, 포션)을 구매할 수 있습니다.
- 상점의 아이템 우클릭 시 해당 아이템의 타입을 확인하고, 인벤토리에 새로운 아이템을 생성해 추가해줬습니다.
- 구매한 아이템은 자동으로 인벤토리의 빈 칸(가장 앞)에 들어가게 되며, 무기는 한 칸에 하나씩, 포션은 여러 개가 들어가도록 구현하였습니다.
- 반대로 상점이 열린 상태에서 인벤토리 내 아이템을 우클릭하면 해당 아이템이 삭제되도록 판매 기능을 구현했습니다. (포션의 경우 개수가 0개가 되면 삭제)
- 인벤토리는 아이템들의 정보를 저장하며, 아이템을 드래그 하여 순서를 변경할 수 있도록 구현하였습니다.
- 인벤토리 창은 상하좌우 드래그를 통해 이동 가능하도록 구현하였습니다. (클릭 후 마우스 위치 변화량 기반)

### 구현 - Map(마을 맵)
<img src="https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/b3d19a90-bbe8-49f4-bc2c-d48e2b43de19" width="800" height="500"/>    

- 마을 씬의 지형은 HeightMap을 활용해 입체적인 높낮이를 표현했고, AlphaMap을 이용해 다양한 텍스처를 겹쳐 적용시켰습니다.
- 스카이 박스를 만들어 하늘을 표현하였고, 나무들은 빌보드 기법을 적용시켜 자연스럽게 표현하였습니다.
- 포탈은 Model과 Quad로 제작하였으며, Quad의 경우 BlendState를 조정하여 반투명하게 설정하였습니다.

### 구현 - Map(던전 맵)
![image](https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/af32740f-278a-4027-bb81-f345d8efb508)


- 각 모델에 콜라이더를 배치한 후 좌표값과 스케일을 조절하여 던전에 배치하였습니다.
- 라이트를 추가하고 값(밝기, 색상)을 바꿔 시각적인 효과를 추가하였습니다.
- PushCollider() 함수를 활용해 플레이어가 벽에 충돌할 시 통과하지 않도록 구현했습니다.
- 플레이어와 몬스터의 스폰 위치를 저장해 던전 씬이 시작되거나 특정 조건을 만족한 경우 해당 위치에 플레이어/몬스터를 스폰하도록 설정하였습니다.
- 던전 내부에서 조건을 판별하여 맵 이벤트(문 열림)를 활성화 시켜줍니다.

### 구현 - Map(보스 맵)
![image](https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/39c9c092-b3b7-47a0-8056-381d37d4e63e)


- 원기둥 콜라이더의 충돌 판별 함수를 만들어 캐릭터가 땅에 닿은 상태인지를 판별합니다.
- 보스의 특정 페이즈에서 가장자리의 얼음이 깨져 추락하는 것을 표현했습니다.
- 캐릭터가 맵(모델)을 벗어나면 떨어지도록 구현하였습니다.
- 보스의 페이즈와 여러 모델들을 연동시켜 페이즈별로 맵이 변경되도록 구현하였습니다.

### 구현 - 몬스터 AI (스켈레톤, 스켈레톤 나이트, 리치왕, 얼음구슬, 발키리)
![image](https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/c1f44e5a-118b-4eda-bdec-514ff1361a07)

### 구현 - 보스 페이즈
> 1페이즈 (체력 70% 이상)    

- 사용 스킬 : 스켈레톤 및 스켈레톤 나이트 소환, 괴저의 역병
- 스켈레톤 및 스켈레톤 나이트는 소환되면 자신과 가장 가까이 있는 적을 공격합니다.
- 괴저의 역병 발동시 현재 리치왕이 타겟으로 삼고있는 캐릭터에게 이펙트가 지속적으로 작용하며 5초마다 최대 체력의 30%에 해당하는 데미지를 주게 됩니다.
- 괴저의 역병 스킬은 최대 체력의 30% 이상을 회복하면 해제됩니다.
- 괴저의 역병 스킬을 맞은 캐릭터가 사망하거나 15초가 지나면 가까운 캐릭터에게 전염됩니다.
  
<img src="https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/3d6dd988-00d6-458a-913e-e9f37df651ed" width="600" height="200"/>     


> 2페이즈 (체력 40% ~ 70%)     
     
- 사용 스킬 : 발키리 소환, 파멸, 외각 지형 붕괴
- 페이즈 시작과 동시에 외각 지형을 붕괴시켜 맵 사이즈를 줄입니다.
- 발키리는 가장 가까운 캐릭터를 추격하여 캐릭터와 충돌 시 캐릭터를 맵 밖으로 끌고 날아갑니다.
- 발키리는 외각 지형에 도착하면 소멸하며, 캐릭터는 그대로 떨어져 사망합니다.
- 파멸은 설치 스킬입니다.
- 처음에는 범위와 위력이 작지만, 캐릭터에게 피해를 입힐 수록 범위와 위력이 상승하게 됩니다.
  
<img src="https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/cf1675a2-3480-4eed-9c11-a404427479b3" width="600" height="300"/> 


> 3페이즈 (체력 40% 미만)

- 사용 스킬 : 외각 지형 붕괴
- 페이즈 시작과 동시에 외각 지형을 붕괴시켜 맵 사이즈를 줄입니다.
- 3페이즈는 1페이즈와 동일한 스킬 패턴을 가지고 있습니다.


> 페이즈 변환     
     
- 사용 스킬 : 얼음 구슬 소환, 냉혹한 겨울
- 페이즈가 전환되는 사이 패턴입니다.
- 리치왕이 무너트린 외각 지형을 복구합니다.
- 리치왕은 맵의 중앙으로 돌아가 행동을 중지하고, 스킬을 사용합니다.
- 냉혹한 겨울 스킬은 보스로부터 일정 범위 내의 모든 적에게 데미지를 입힙니다.
- 얼음 구슬은 가장 가까운 캐릭터를 추적하며, 해당 캐릭터와 주변에 지속적인 범위 데미지를 입힙니다.
- 냉혹한 겨울 스킬이 종료되면 자연스럽게 다음 페이즈로 변경됩니다.
  
<img src="https://github.com/LeeTaehuny/WoW_Imitation/assets/105622632/c9205a72-0da9-416e-af6c-fcebd6c02e4f" width="600" height="300"/> 



