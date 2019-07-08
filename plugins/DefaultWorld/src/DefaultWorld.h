#pragma once

#include "../../../src/WorldInterface.h"
#include "../../../src/ControllerInterface.h"
#include "../../../src/Point2DPriv.h"

class StaticWorldImpl : public WorldInterface
{
	Player player_;
	
	std::vector<Player> enemies_;
	std::vector<Base> bases_;

	float field_width_;
	float field_height_;
	float max_player_height_;

public:
	StaticWorldImpl();

	void updateEnemies(float time_step, std::vector<Player>& enemies);
	void updateBases(float time_step, std::vector<Base>& bases);
	Player* hasPlayerEnemyContact(const Player& player);
	bool hasPlayerGroundContact(const Player& player, float& ground_height);



public:
	virtual const std::vector<Player>& getEnemies() const override
	{
		return enemies_;
	}
	virtual const std::vector<Base>& getBases() const override
	{
		return bases_;
	}
	virtual const Player& getPlayer() const override
	{
		return player_;
	}

	void build(float field_width, float field_height);
	void updatePlayer(float time_step, Player& player, const ControllerInterface& ctrl);
	virtual void onTick(float time_step, const ControllerInterface& ctrl) override;
	void end();

};
