#pragma once

#include "FrameMdlProjector.h"

class Decorator : public FrameModel
{
protected:
	FrameModel * component;

public:
	void SetComponent(FrameModel* component)
	{
		this->component = component;
	}

	void operation() override
	{
		if (component != nullptr)
			component->operation();
	}
};