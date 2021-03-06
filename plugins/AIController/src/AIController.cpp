#include <Windows.h>
#include <iostream>

#include "AIController.h"

AIController::AIController()
{
}

bool AIController::inputJump() const 
{
	return true;
}
float AIController::inputSide() const
{
	Point2D dist_vec = clostest_base_.pos_ - last_player_pos_;
	return dist_vec.x;
}

void AIController::onTick(float time_step, const WorldInterface& world)
{
	last_player_pos_ = world.getPlayer().pos_;

	if (world.getPlayer().had_ground_contact_)
	{
		auto& bases = world.getBases();
		float closest_base_dist = FLT_MAX;

		for (auto b : bases)
		{
			if (b.pos_.y < last_player_pos_.y)
				continue;

			float dist = mag((b.pos_ - last_player_pos_)*Point2D(1,10));
			if (dist < closest_base_dist)
			{
				closest_base_dist = dist;
				clostest_base_ = b;
			}
		}
	}

	return;
}

void AIController::onDraw(WorldCanvas& canvas)
{
	canvas.setColor(0, 0, 255, 255);
	canvas.plotCircle(clostest_base_.pos_.x, clostest_base_.pos_.y, 5.0f);
}


extern "C"
{
	__declspec(dllexport) ControllerInterface* createController()
	{
		return new AIController();
	}
}
