#pragma once

#include "../../../src/ControllerInterface.h"
#include "../../../src/WorldInterface.h"
#include "../../../src/Point2DPriv.h"
#include "../../../src/WorldCanvas.h"


class AIController : public ControllerInterface
{
	Base clostest_base_;
	Point2D last_player_pos_;

public:
	AIController();

	virtual bool inputJump() const override;
	virtual float inputSide() const override;

	virtual void onTick(float time_step, const WorldInterface& world) override;
	virtual void onDraw(WorldCanvas& canvas);

};




