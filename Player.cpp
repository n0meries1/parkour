#include "Player.h"

Player::Player(glm::vec3 startingPosition) : playerPosition(startingPosition), velocity(0.0f), acceleration(0.0f), onGround(true), gravity(-9.18f), jumpStrength(5.50f), jump(false), speedCap(10.0), playerSize(glm::vec3(1.0f, 1.0f, 1.0f)){}

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

void Player::CheckCollision()
{
	for (const auto& object : objects)
	{
		glm::vec3 objectPos = object.first;
		glm::vec3 objectSize = object.second;
		bool collisionX = (playerPosition.x + playerSize.x / 2 >= objectPos.x - objectSize.x / 2) && (playerPosition.x - playerSize.x / 2 <= objectPos.x + objectSize.x);
		bool collisionY = (playerPosition.y + playerSize.y / 2 >= objectPos.y - objectSize.y / 2) && (playerPosition.y - playerSize.y / 2 <= objectPos.y + objectSize.y);
		bool collisionZ = (playerPosition.z + playerSize.z / 2 >= objectPos.z - objectSize.z / 2) && (playerPosition.z - playerSize.z / 2 <= objectPos.z + objectSize.z);
		if (collisionX && collisionY && collisionZ)
		{
			float Xpenetrationmagnitude = std::min(playerPosition.x + playerSize.x / 2 - objectPos.x - objectSize.x / 2, objectPos.x + objectSize.x / 2 - playerPosition.x - playerSize.x / 2);
			float Ypenetrationmagnitude = std::min(playerPosition.y + playerSize.y / 2 - objectPos.y - objectSize.y / 2, objectPos.y + objectSize.y / 2 - playerPosition.y - playerSize.y / 2);
			float Zpenetrationmagnitude = std::min(playerPosition.z + playerSize.z / 2 - objectPos.z - objectSize.z / 2, objectPos.z + objectSize.z / 2 - playerPosition.z - playerSize.z / 2);
			if (Xpenetrationmagnitude > Ypenetrationmagnitude && Xpenetrationmagnitude > Zpenetrationmagnitude)
			{
				playerPosition.x = playerPosition.x < objectPos.x ? objectPos.x - objectSize.x / 2 - playerSize.x / 2 : objectPos.x + objectSize.x / 2 + playerSize.x / 2;
				velocity.x = 0;
			}

			else if (Ypenetrationmagnitude > Xpenetrationmagnitude && Ypenetrationmagnitude > Zpenetrationmagnitude)
			{
				playerPosition.y = playerPosition.y < objectPos.y ? objectPos.y - objectSize.y / 2 - playerSize.y / 2 : objectPos.y + objectSize.y / 2 + playerSize.y / 2;
				velocity.y = 0;
				onGround = true;
				jump = 0;
			}

			else if (Zpenetrationmagnitude > Xpenetrationmagnitude && Zpenetrationmagnitude > Ypenetrationmagnitude)
			{
				playerPosition.z = playerPosition.z < objectPos.z ? objectPos.z - objectSize.z / 2 - playerSize.z / 2 : objectPos.z + objectSize.z / 2 + playerSize.z / 2;
				velocity.z = 0;
			}
		}
	}
}


