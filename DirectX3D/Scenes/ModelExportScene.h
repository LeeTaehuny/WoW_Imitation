#pragma once

class ModelExportScene : public Scene
{
public:
    ModelExportScene();
    ~ModelExportScene();
        
    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

    // 모델에서 메테리얼과 메쉬 추출 함수
    // 모델의 이름만 넣으면 알아서 나옵니다.
    void Model_MER_MESH(string name);

    // 애니메이션 폴더에서 클립 추출
    // 모델의 이름, 애니메이션 이름을 넣으시면 됩니다.
    void AnimationClip(string name, string clipName);
};