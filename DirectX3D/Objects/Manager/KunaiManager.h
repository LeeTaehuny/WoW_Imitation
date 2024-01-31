#pragma once

class KunaiManager : public Singleton<KunaiManager>
{
private:
    friend class Singleton;
    UINT SIZE = 30; // 쿠나이 사전 설정 개수

public:

    KunaiManager();
    ~KunaiManager();

    void Update();
    void Render();

    void Throw(Vector3 pos, Vector3 dir); // 개별 쿠나이에게 던짐 함수를 전달하기 위한 매개함수
                                          // 캐릭터는 이 함수를 쓰고, 이 함수는 진짜 쿠나이를 던진다

    bool IsCollision(Collider* collider);

private:

    //쿠나이의 모델을 통합해서 관리하기 위한...
    ModelInstancing* kunaiInstancing; // 동작은 따로 없어서 모델 인스턴싱만으로 충분
                                      // (투사체도 애니메이션이 있는 경우라면 ModelAnimationInstancing 클래스가 필요할 것)

    vector<Kunai*> kunaies; // 실제 쿠나이의 주 클래스

};

