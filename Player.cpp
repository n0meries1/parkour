#include "Player.h"

Player::Player(glm::vec3 startingPosition) 
    : playerPosition(startingPosition), velocity(0.0f), acceleration(0.0f), 
      onGround(true), gravity(-9.18f), jumpStrength(5.50f), jumpheight(30.0f), speedCap(10.0f), playerSize(glm::vec3(1.0f, 1.0f, 1.0f)) {}

void Player::Update(float deltatime)
{
    if (!onGround)
    {
        velocity.y += gravity * deltatime * 5;
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
    CheckCollision();

    if (playerPosition.y < -20.0f)
        playerPosition = glm::vec3(0.0f, 5.0f, 0.0f);
}

void Player::ApplyForce(glm::vec3 gravityforce)
{
    velocity.x = gravityforce.x;
    velocity.z = gravityforce.z;
}

void Player::Jump()
{
    if (onGround)
    {
        velocity.y = sqrt(2 * std::abs(gravity) * jumpheight);
        onGround = false;
    }
}

void Player::CheckCollision()
{
    for (const auto& object : objects)
    {
        glm::vec3 objectPos = object.first;
        glm::vec3 objectSize = object.second;

        bool collisionX = (playerPosition.x + playerSize.x / 2 >= objectPos.x - objectSize.x / 2) && 
                          (playerPosition.x - playerSize.x / 2 <= objectPos.x + objectSize.x / 2);
        bool collisionY = (playerPosition.y + playerSize.y / 2 >= objectPos.y - objectSize.y / 2) && 
                          (playerPosition.y - playerSize.y / 2 <= objectPos.y + objectSize.y / 2);
        bool collisionZ = (playerPosition.z + playerSize.z / 2 >= objectPos.z - objectSize.z / 2) && 
                          (playerPosition.z - playerSize.z / 2 <= objectPos.z + objectSize.z / 2);

        if (collisionX && collisionY && collisionZ)
        {
            float penetrationX = std::min((playerPosition.x + playerSize.x / 2) - (objectPos.x - objectSize.x / 2), 
                                          (objectPos.x + objectSize.x / 2) - (playerPosition.x - playerSize.x / 2));
            float penetrationY = std::min((playerPosition.y + playerSize.y / 2) - (objectPos.y - objectSize.y / 2), 
                                          (objectPos.y + objectSize.y / 2) - (playerPosition.y - playerSize.y / 2));
            float penetrationZ = std::min((playerPosition.z + playerSize.z / 2) - (objectPos.z - objectSize.z / 2), 
                                          (objectPos.z + objectSize.z / 2) - (playerPosition.z - playerSize.z / 2));

            if (penetrationY < penetrationX && penetrationY < penetrationZ)
            {
                if (playerPosition.y < objectPos.y)
                {
                    playerPosition.y = objectPos.y - objectSize.y / 2 - playerSize.y / 2;
                    velocity.y = 0;
               
                }
                else 
                {
                    playerPosition.y = objectPos.y + objectSize.y / 2 + playerSize.y / 2;
                    velocity.y = 0;
                    onGround = true;
                  
                }
            }
            else if (penetrationX < penetrationY && penetrationX < penetrationZ)
            {
                if (playerPosition.x < objectPos.x)
                {
                    playerPosition.x = objectPos.x - objectSize.x / 2 - playerSize.x / 2;
                }
                else
                {
                    playerPosition.x = objectPos.x + objectSize.x / 2 + playerSize.x / 2;
                }
                velocity.x = 0;
            }
            else 
            {
                if (playerPosition.z < objectPos.z)
                {
                    playerPosition.z = objectPos.z - objectSize.z / 2 - playerSize.z / 2;
                }
                else
                {
                    playerPosition.z = objectPos.z + objectSize.z / 2 + playerSize.z / 2;
                }
                velocity.z = 0;
            }
        }
    }
}
