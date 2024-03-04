#include "Framework.h"
#include "Arrow.h"

Arrow::Arrow(Transform* transform)
{
	transform->SetParent(this);
	isRun = false;
}

Arrow::~Arrow(){}

void Arrow::Update(){}