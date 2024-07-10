#include "Game.h"
#include "Collision.h"
#include "TransformComponent.h"
#include "EntityComponentSystem.h"
#include "Sprites.h"
#include "SpriteComponent.h"

char* Collision::mTag;
bool Collision::mCollided;

bool Collision::checkForCollision(Collider otherCollider) {
	Collider& dinoCollider = Game::mDino.getComponent<SpriteComponent>().getSprite()->getCollider();
		
	for (auto& A : dinoCollider.getColliderRects()) {
		for (auto& B : otherCollider.getColliderRects()) {
			if (A.x + A.w >= B.x
				&&
				B.x + B.w >= A.x
				&&
				A.y + A.h >= B.y
				&&
				B.y + B.h >= A.y)
			{
				mCollided = true;
				mTag = const_cast<char*>(otherCollider.getCollisionTag());

				return true;
			}
		}
	}

	return false;
}

bool Collision::checkForCollisions() {
	std::vector<std::unique_ptr<Entity>>& entities = Game::mEntityManager.getEntities();

	for (auto& e : entities) {
		if (e->isActive() && (Game::mDino.mEntityIndex != e->mEntityIndex)) {
			if (checkForCollision(e->getComponent<SpriteComponent>().getSprite()->getCollider())) {
				break;
			}
		}
	}

	return mCollided;
}

char* Collision::getTag() {
	return mTag;
}
