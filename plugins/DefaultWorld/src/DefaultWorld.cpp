#include <Windows.h>
#include <iostream>

#include "DefaultWorld.h"

static const float JUMP_SPEED = 40.0f;
static const float GRAVITY = 9.81f;
static const float GAME_SPEED = 5.0f;
static const float DASH_SPEED = 10.0f;

static const float PLAYER_SIZE = 10.0f;
static const float OBSTACLE_WIDTH = 20.0f;
static const float ENEMY_SIZE = 10.0f;

/// maximal horizintal base dist to make it always reachable
static const float OBSTACLE_MAX_HORIZONTAL_DIST = 90.0f;

/// minimal distance of enemies to obstalce to avoid unfair structures
static const float ENEMY_OBSTACLE_DIST = 50.0f;

/// vertical distance between enemies
static const float ENEMY_STAGE_STEP = PLAYER_SIZE * 24.0f;

/// no enemies until ENEMY_HEIGHT_OFFSET
static const float ENEMY_HEIGHT_OFFSET = PLAYER_SIZE *8.0f;

/// if player falls below value it gets killed
static const float KILL_PLAYER_BELOW_MAX_HEIGHT = 150.0f;

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

Player* StaticWorldImpl::hasPlayerEnemyContact(const Player& player)
{
	for (auto &e : enemies_)
	{
		if (e.is_alive_ == false)
			continue;

		if (mag(player.pos_ - e.pos_) < player.radius_ + e.radius_)
			return &e;
	}

	return 0;
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

	srand((unsigned int)time(0));
	//srand(2);

	player_.id_ = 0;
	player_.pos_.x = field_width / 2.0f;
	player_.radius_ = PLAYER_SIZE;
	player_.pos_.y = player_.radius_ * 2.0f; 
	player_.is_alive_ = true;
	player_.speed_ = Point2D(0, 0);

	const float BASE_STAGE_STEP = player_.radius_ * 4.0f;

	Point2D last_base_pos = player_.pos_;
	for (unsigned int b = 0; b < field_height / BASE_STAGE_STEP; b++)
	{
		Base base;
		base.pos_ = last_base_pos + Point2D(std::min<float>(field_width*(rand01()-0.5f)*2.0f, OBSTACLE_MAX_HORIZONTAL_DIST), BASE_STAGE_STEP);
		if (base.pos_.x > field_width)
			base.pos_.x -= field_width;
		if (base.pos_.x < 0)
			base.pos_.x += field_width;

		base.width_ = OBSTACLE_WIDTH;
		base.id_ = b;
		bases_.push_back(base);

		last_base_pos = base.pos_;
	}

	float enemy_y_step = ENEMY_HEIGHT_OFFSET;

	for (unsigned int e = 0; e < field_height / ENEMY_STAGE_STEP; e++)
	{
		enemy_y_step +=  ENEMY_STAGE_STEP*0.5 + ENEMY_STAGE_STEP * 0.5 * rand01();

		Player enemy;
		float g = 0.0f;
		do
		{
			enemy.pos_ = Point2D(field_width * rand01(), enemy_y_step);
			enemy.radius_ = ENEMY_OBSTACLE_DIST;
			enemy.id_ = e + 1;

		} while (hasPlayerGroundContact(enemy, g));

		enemy.radius_ = ENEMY_SIZE;
		enemies_.push_back(enemy);
	}

}

void StaticWorldImpl::updatePlayer(float time_step, Player& player, const ControllerInterface& ctrl)
{
	player.had_ground_contact_ = false;

	if (Player* enemy = hasPlayerEnemyContact(player))
	{
		player.is_alive_ = false;
		return;
	}
	if(player.pos_.y < max_player_height_ - KILL_PLAYER_BELOW_MAX_HEIGHT)
	{
		player.is_alive_ = false;
		return;
	}

	player.speed_.x = clamp(-1.0f, 1.0f, ctrl.inputSide())*DASH_SPEED;
	player.speed_.y -= GRAVITY * time_step * GAME_SPEED;

	player.pos_ = player.pos_ + player.speed_ * time_step * GAME_SPEED;

	if (player.pos_.x > field_width_)
		player.pos_.x = 0.0;
	if (player.pos_.x < 0.0)
		player.pos_.x = field_width_;
		
	float ground;
	if (hasPlayerGroundContact(player, ground))
	{
		player.had_ground_contact_ = true;
		if (player.speed_.y < 0.0f)
		{
			player.pos_.y = ground + player.radius_;
			player.speed_.y = 0.0f;
		}
		if (ctrl.inputJump())
		{
			player.speed_.y = JUMP_SPEED;
		}
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




/// Export createWorld world from DLL
extern "C"
{
	__declspec(dllexport) WorldInterface* createWorld(unsigned int width, unsigned int height)
	{
		StaticWorldImpl* world = new StaticWorldImpl();
		world->build((float)width, (float)height);
		return world;
	}
}

