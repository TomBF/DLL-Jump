#pragma once
#include "../../../src/ControllerInterface.h"

class KeyboardController : public ControllerInterface
{
public:
	virtual bool inputJump() const override;
	virtual float inputSide() const override;
	virtual void onTick(float time_step, const WorldInterface& world) override;
};
