#include "Framework.h"
#include "TestLight.h"

TestLight::TestLight()
{
    light = Environment::Get()->AddLight();
    light->color = { 1, 0, 0, 1 };
}

TestLight::~TestLight()
{
}

void TestLight::Update()
{
}
