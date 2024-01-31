#pragma once
class AStarScene : public Scene
{
public:

    AStarScene();
    ~AStarScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Terrain* terrain;
    AStar* aStar;
    Fox* fox;

};

