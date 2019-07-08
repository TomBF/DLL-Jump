#pragma once

#include <vector>
#include "Point2D.h"

struct Base
{
	int id_;
	Point2D pos_;
	float width_;
};

struct Player
{
	int id_;
	Point2D pos_;
	Point2D speed_;

	float radius_;

	/// true if player is moveable
	bool is_alive_;
	/// true if player had ground contact in last tick
	bool had_ground_contact_;
};

class ControllerInterface;
class WorldCanvas;

class WorldInterface
{
public:
	virtual const std::vector<Player>& getEnemies() const = 0;
	virtual const std::vector<Base>& getBases() const = 0;
	virtual const Player& getPlayer() const = 0;

	virtual void onTick(float time_step, const ControllerInterface& ctrl) = 0;
	virtual void onDraw(WorldCanvas& canvas) { };
};