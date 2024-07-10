#pragma once

#include <vector>

class SpriteComponent;
struct TransformComponent;
class Entity;

class ObstacleManager {
	int mJustCollidedIndex = 0;
	int justFieldedIndex = 0;
	int nextToBeFieldedIndex = 0;
	int mDistanceBetweenObstacles = 0;
	int mMaxObstacleSpriteIndex = 2;

	float mObstacleVelocity = -15;

	std::vector<Entity*> mObstacles;
	std::vector<TransformComponent*> mObstaclesTransformCache;
	std::vector<SpriteComponent*> mObstaclesSpriteCache;

	void loadObstacles();
	void fieldObstacle();
	void updateObstacleSpeed();
	void updateMaxObstacleSpriteIndex();
	void hotSwapObstacleSprite(SpriteComponent* spriteComponent, int sType);
	void setDistanceBetweenObstacles(int seed);

public:
	void init();
	void reset();
	void update();

	void updateGameOverAnimation();
	void initGameOverAnimation();
};