#pragma once

class WorldInterface;
class WorldCanvas;

class ControllerInterface
{
public:
	virtual void onDraw(WorldCanvas& canvas) { };
	virtual void onTick(float time_step, const WorldInterface& world) { }

	virtual bool	inputJump() const = 0;
	virtual float	inputSide() const = 0;
};