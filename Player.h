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
	unsigned int jump;
	float gravity;
	float jumpStrength;
	float speedCap;
	

	Player(glm::vec3 startingPosition);
	void Update(float deltatime);
	void ApplyForce(glm::vec3 gravityforce);
	void Jump();
	void CheckCollision(std::vector <glm::vec3> objects);

private:
	void HandleCollision(glm::vec3 object);
};

#endif // !PLAYER_H


