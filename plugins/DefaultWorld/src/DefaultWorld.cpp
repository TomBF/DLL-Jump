#include <Windows.h>
#include <iostream>

#include "DefaultWorld.h"

static const float JUMP_SPEED = 40.0f;

StaticWorldImpl::StaticWorldImpl()
{
	field_width_ = 0.0f;
	field_height_ = 0.0f;
	max_player_height_ = 0.0f;
}

void StaticWorldImpl::updateEnemies(float time_step, std::vector<Player>& enemies)
{

}

void StaticWorldImpl::updateBases(float time_step, std::vector<Base>& bases)
{

}

bool StaticWorldImpl::hasPlayerEnemyContact(const Player& player)
{
	for (auto e : enemies_)
	{
		if (mag(player.pos_ - e.pos_) < player.radius_ + e.radius_)
			return true;
	}

	return false;
}

bool StaticWorldImpl::hasPlayerGroundContact(const Player& player, float& ground_height)
{
	if (player.pos_.y < player.radius_)
	{
		ground_height = 0.0f;
		return true;
	}

	float closest_ground = FLT_MAX;

	for (auto b : bases_)
	{
		float g_dist = player.pos_.y - b.pos_.y;

		if (g_dist > player.radius_ || g_dist < 0.0f)
			continue;

		if (mag(b.pos_ - player.pos_) > player.radius_ + b.width_ / 2.0f)
			continue;

		if (g_dist < closest_ground)
		{
			ground_height = b.pos_.y;
			closest_ground = g_dist;
		}
	}

	if (closest_ground != FLT_MAX)
	{
		return true;
	}

	return false;
}


void StaticWorldImpl::build(float field_width, float field_height)
{
	field_width_ = field_width;
	field_height_ = field_height;

	//srand((unsigned int)time(0));
	srand(2);

	player_.id_ = 0;
	player_.pos_.x = field_width / 2.0f;
	player_.radius_ = 10.0f;
	player_.pos_.y = player_.radius_ * 2.0f; ///rad above ground
	player_.is_alive_ = true;
	player_speed_ = Point2D(0, 0);

	const float BASE_STAGE_STEP = player_.radius_ * 4.0f;

	for (unsigned int b = 0; b < field_height / BASE_STAGE_STEP; b++)
	{
		Base base;
		base.pos_ = randP2() * Point2D(field_width, 0) + Point2D(0, BASE_STAGE_STEP * (b + 1));
		base.width_ = 20.0f;
		base.id_ = b;
		bases_.push_back(base);
	}

	const float ENEMY_STAGE_STEP = player_.radius_ * 24.0f;
	const float ENEMY_HEIGHT_OFFSET = player_.radius_*8.0f;
	/// no enemies until ENEMY_HEIGHT_OFFSET
	float enemy_y_step = ENEMY_HEIGHT_OFFSET;

	for (unsigned int e = 0; e < field_height / ENEMY_STAGE_STEP; e++)
	{
		enemy_y_step +=  ENEMY_STAGE_STEP*0.5 + ENEMY_STAGE_STEP *0.5 * rand01();

		Player enemy;
		float g;
		do
		{
			enemy.pos_ = Point2D(field_width * rand01(), enemy_y_step);
			enemy.radius_ = 50.0f;
			enemy.id_ = e + 1;

		} while (hasPlayerGroundContact(enemy, g));

		enemy.radius_ = 10.0f;
		enemies_.push_back(enemy);
	}

	std::cout << "Static World Built" << std::endl;

}

void StaticWorldImpl::updatePlayer(float time_step, Player& player, const ControllerInterface& ctrl)
{
	time_step *= 5.0f;
	player.had_ground_contact_ = false;

	if (hasPlayerEnemyContact(player))
	{
		player.is_alive_ = false;
		return;
	}
	if(player.pos_.y < max_player_height_ - 150)
	{
		player.is_alive_ = false;
		return;
	}

	player_speed_.x = clamp(-1.0f, 1.0f, ctrl.inputSide())*10.0f;
	player_speed_.y -= 9.81f * time_step;

	player.pos_ = player.pos_ + player_speed_ * time_step;

	if (player.pos_.x > field_width_)
		player.pos_.x = 0.0;
	if (player.pos_.x < 0.0)
		player.pos_.x = field_width_;
		
	float ground;
	if (hasPlayerGroundContact(player, ground))
	{
		player.had_ground_contact_ = true;
		if (player_speed_.y < 0.0f)
		{
			player.pos_.y = ground + player.radius_;
			player_speed_.y = 0.0f;
		}
		if (ctrl.inputJump())
			player_speed_.y = JUMP_SPEED;
	}

	max_player_height_ = max(player.pos_.y, max_player_height_);
}

void StaticWorldImpl::onTick(float time_step, const ControllerInterface& ctrl)
{
	updatePlayer(time_step, player_, ctrl);
	updateEnemies(time_step, enemies_);
	updateBases(time_step, bases_);
}

void StaticWorldImpl::end()
{

}





extern "C"
{
	__declspec(dllexport) WorldInterface* createWorld(unsigned int width, unsigned int height)
	{
		StaticWorldImpl* world = new StaticWorldImpl();
		world->build((float)width, (float)height);
		return world;
	}
}

