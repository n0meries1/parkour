#include "Player.h"

Player::Player(glm::vec3 startingPosition) : playerPosition(startingPosition), velocity(0.0f), acceleration(0.0f), onGround(true), gravity(-9.18f), jumpStrength(5.50f), jump(false), speedCap(10.0) {}

void Player::Update(float deltatime)
{

	if (!onGround)
		velocity.y += gravity * deltatime * 5;

	if (jump != 0)
	{
		if (jump >= 50)
		{
			velocity.y = 0.0f;
			jump = 0;
		}
		else
		{
			jump += 1;
			velocity.y += jumpStrength * deltatime * 50;
		}
	}

	float speed = glm::length(glm::vec2(velocity.x, velocity.z));
	if (speed > speedCap)
	{
		glm::vec2 horizontalVelocity = glm::normalize(glm::vec2(velocity.x, velocity.z)) * speedCap;
		velocity.x = horizontalVelocity.x;
		velocity.z = horizontalVelocity.y;
	}

	playerPosition += velocity * deltatime;


	onGround = false;

	//

}

void Player::ApplyForce(glm::vec3 gravityforce)
{
	velocity.x  = gravityforce.x;
	velocity.z = gravityforce.z;
	
}

void Player::Jump()
{
	if (onGround)
	{
		jump = 1;
	}
}

void Player::CheckCollision(std::vector <glm::vec3> objects)
{
	for (const auto& object : objects)
		HandleCollision(object);

}

void Player::HandleCollision(glm::vec3 object)
{
	if (playerPosition.y <= object.y + 1.0f && playerPosition.y >= object.y - 1.0f)
	{
		playerPosition.y = object.y + 1.0f;
		velocity.y = 0.0f;
		onGround = true;
	}

}
