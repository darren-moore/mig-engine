
#include "CollisionEngine.h"
#include "collisionUtils.h"
#include "Component.h"

using namespace std;

void CollisionEngine::processCollisions() {

	// Clear collision lists.
	for(auto it = entityToHitEntities.begin(); it != entityToHitEntities.end(); ++it){
		it->second.clear();
	}

	// Compute collision lists.
	for (auto it1 = entityToHitEntities.begin(); it1 != entityToHitEntities.end(); ++it1) {
		Entity* e1 = it1->first;

		for (auto it2 = it1; it2 != entityToHitEntities.end(); ++it2) {
			Entity* e2 = it2->first;
			if (checkCollision(e1, e2)) {
				entityToHitEntities[e1].push_back(e2);
				entityToHitEntities[e2].push_back(e1);
			}
		}
	}
}


bool CollisionEngine::checkCollision(Entity* e1, Entity* e2) {
	if (e1 == e2) {
		return false;
	}

	if (e2->getComponent<CollisionShape>()->shape->getType() < e1->getComponent<CollisionShape>()->shape->getType()) {
		std::swap(e1, e2);
	}

	Eigen::Vector2f pos1 = e1->getComponent<gTransform>()->position;
	Eigen::Vector2f pos2 = e2->getComponent<gTransform>()->position;

	Shape* s1 = e1->getComponent<CollisionShape>()->shape;
	Shape* s2 = e2->getComponent<CollisionShape>()->shape;

	Shape::type st1 = s1->getType();
	Shape::type st2 = s2->getType();


	if (st1 == Shape::type::line && st2 == Shape::type::line) {
		return false; // TODO
	}

	else if (st1 == Shape::type::line && st2 == Shape::type::box) {
		return false; // TODO
	}

	else if (st1 == Shape::type::line && st2 == Shape::type::circle) {
		return circleLineSegmentCollision(((Line*)s1)->a, ((Line*)s1)->b, pos2 + ((Circle*)s2)->offset, ((Circle*)s2)->r);
	}

	else if (st1 == Shape::type::box && st2 == Shape::type::box) {
		return false; // TODO
	}

	else if (st1 == Shape::type::box && st2 == Shape::type::circle) {
		return circleRectangleCollision(pos1 - ((Box*)s1)->scale / 2, pos1 + ((Box*)s1)->scale / 2, pos2 + ((Circle*)s2)->offset, ((Circle*)s2)->r);
	}

	else if (st1 == Shape::type::circle && st2 == Shape::type::circle) {
		return (pos1 - pos2).norm() < ((Circle*)s1)->r + ((Circle*)s2)->r;
	}
	else {
		return false;
	}


}


void CollisionEngine::addCollisionEntity(Entity* e) {
	entityToHitEntities[e] = vector<Entity*>();
}

vector<Entity*> CollisionEngine::getCollisions(Entity* e) {
	return entityToHitEntities[e];
}
