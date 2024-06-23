#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm/glm.hpp>
#include <vector>
#include <iostream>

class Player
{
public:
	glm::vec3 playerPosition;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	bool onGround;
	float jumpheight;
	float gravity;
	float jumpStrength;
	float speedCap;
	std::vector <std::pair<glm::vec3, glm::vec3>> objects;
	glm::vec3 playerSize;

	Player(glm::vec3 startingPosition);
	void Update(float deltatime);
	void ApplyForce(glm::vec3 gravityforce);
	void Jump();
	void CheckCollision();
};

#endif // !PLAYER_H


