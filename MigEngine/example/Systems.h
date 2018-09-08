#pragma once
#include "System.h"
#include "Components.h"
#include "Locator.h"
#include "collisionUtils.h"

class MovementSystem : public System {
public:
	void init() {
		addRequiredComponent<Player>();
		addRequiredComponent<gTransform>();
		addRequiredComponent<CollisionShape>();
		ioEngine_ = Locator::getIOEngine();
	}

private:
	IOEngine* ioEngine_;

	void execute(std::vector<Entity*>& entities, const float dt) {
		for (auto& e : entities) {
			Player* player = e->getComponent<Player>();
			gTransform* transform = e->getComponent<gTransform>();
			CollisionShape* collisionShape = e->getComponent<CollisionShape>();
			if (collisionShape->shape->getType() != Shape::box) { continue; }
			Box* box = (Box*)collisionShape->shape;
			if (ioEngine_->isDown(player->upKey) &&
				transform->position.y() + box->offset.y() - box->scale.y() / 2 > 0) {
				transform->position[1] = transform->position[1] - player->speed;
			}
			if (ioEngine_->isDown(player->downKey) &&
				transform->position.y() + box->offset.y() + box->scale.y() / 2 < ioEngine_->getWindowHeight()) {
				transform->position[1] = transform->position[1] + player->speed;
			}
		}
	}
};

class SpriteRenderSystem : public System {
public:
	void init() {
		addRequiredComponent<Sprite>();
		addRequiredComponent<gTransform>();
		renderEngine_ = Locator::getRenderEngine();
		ioEngine_ = Locator::getIOEngine();
	}
private:
	RenderEngine* renderEngine_;
	IOEngine* ioEngine_;

	void execute(std::vector<Entity*>& entities, const float dt) {
		for (auto& e : entities) {
			renderEngine_->drawTexture(e->getComponent<Sprite>()->texture, e->getComponent<gTransform>()->position, Eigen::Vector2f(100, 100), ioEngine_->getCurrentWindowTime() * 2);
		}
	}
};

class QuadRenderSystem : public System {
public:
	void init() {
		addRequiredComponent<Quad>();
		addRequiredComponent<gTransform>();
		renderEngine_ = Locator::getRenderEngine();
		ioEngine_ = Locator::getIOEngine();
	}
private:
	RenderEngine* renderEngine_;
	IOEngine* ioEngine_;

	void execute(std::vector<Entity*>& entities, const float dt) {
		for (auto& e : entities) {
			Eigen::Vector2f offset = e->getComponent<Quad>()->offset;
			Eigen::Vector2f scale = e->getComponent<Quad>()->scale;
			Eigen::Vector2f position = e->getComponent<gTransform>()->position;
			renderEngine_->drawRectangle(offset.x() + position.x() - scale.x() / 2, offset.y() + position.y() - scale.y() / 2,
				offset.x() + position.x() + scale.x() / 2, offset.y() + position.y() + scale.y() / 2);
		}
	}
};

class CircleRenderSystem : public System {
public:
	void init() {
		addRequiredComponent<Circ>();
		addRequiredComponent<gTransform>();
		renderEngine_ = Locator::getRenderEngine();
		ioEngine_ = Locator::getIOEngine();
	}
private:
	RenderEngine* renderEngine_;
	IOEngine* ioEngine_;

	void execute(std::vector<Entity*>& entities, const float dt) {
		for (auto& e : entities) {
			Eigen::Vector2f offset = e->getComponent<Circ>()->offset;
			float radius = e->getComponent<Circ>()->radius;
			Eigen::Vector2f position = e->getComponent<gTransform>()->position;
			renderEngine_->drawCircle(offset.x() + position.x(), offset.y() + position.y(), radius);
		}
	}
};

class TimeIntegrationSystem : public System {
public:
	void init() {
		addRequiredComponent<Velocity>();
		addRequiredComponent<gTransform>();
	}
private:
	void execute(std::vector<Entity*>& entities, const float dt) {
		for (auto& e : entities) {
			e->getComponent<gTransform>()->position += dt * e->getComponent<Velocity>()->velocity;
		}
	}
};


// No continuous collision detection yet.
class BallCollisionResolutionSystem : public System {
public:
	void init() {
		addRequiredComponent<gTransform>();
		addRequiredComponent<Velocity>();
		addRequiredComponent<CollisionShape>();

		ioEngine_ = Locator::getIOEngine();
		collisionEngine_ = Locator::getCollisionEngine();
	}
private:
	IOEngine* ioEngine_;
	CollisionEngine* collisionEngine_;

	void execute(std::vector<Entity*>& entities, const float dt) {
		for (auto& ball : entities) {
			Shape* s1 = ball->getComponent<CollisionShape>()->shape;
			if (s1->getType() != Shape::type::circle) {
				continue;
			}

			// Handle collision resolution
			for (auto& hit : collisionEngine_->getCollisions(ball)) {
				Shape* s2 = hit->getComponent<CollisionShape>()->shape;
				Eigen::Vector2f v = ball->getComponent<Velocity>()->velocity;

				if (s2->getType() == Shape::type::line) {
					resolvePlanarCollision(((Line*)s2)->a , ((Line*)s2)->b, ball->getComponent<gTransform>()->position+((Circle*)s1)->offset, ((Circle*)s1)->r, ball->getComponent<gTransform>(), ball->getComponent<Velocity>());
				}
				if (s2->getType() == Shape::type::box) {
					resolveBoxCollision(hit->getComponent<gTransform>()->position + ((Box*)s2)->offset, ((Box*)s2)->scale, ball->getComponent<gTransform>()->position + ((Circle*)s1)->offset, ((Circle*)s1)->r, ball->getComponent<gTransform>(), ball->getComponent<Velocity>());
				}
			}

		}
	}

	void resolvePlanarCollision(const Eigen::Vector2f& p1, const Eigen::Vector2f& p2, Eigen::Vector2f c, float r, gTransform* pos, Velocity* vel) {

		Eigen::Vector2f line = p2 - p1;
		Eigen::Vector2f normal = Eigen::Vector2f(-line[1], line[0]).normalized();

		// Normals are oriented. Choose the correct one.
		if (vel->velocity.dot(normal) > 0) {
			normal.array() *= -1;
		}

		vel->velocity += 2*vel->velocity.dot(-normal)*normal;

		// Push out of plane.
		float dist = distToLine(p1, p2, c);
		pos->position += (r - dist)*normal;
		
	}

	void resolveBoxCollision(const Eigen::Vector2f& position, const Eigen::Vector2f& scale, Eigen::Vector2f c, float r, gTransform* pos, Velocity* vel) {
		Eigen::Vector2f p1 = position - scale / 2;
		Eigen::Vector2f p2 = position - scale/2 + Eigen::Vector2f(scale(0), 0);
		Eigen::Vector2f p3 = position - scale / 2 + Eigen::Vector2f(0, scale(1));
		Eigen::Vector2f p4 = position + scale/2;

		if (circleLineSegmentCollision(p1, p2, c, r)) {
			resolvePlanarCollision(p1, p2, c, r, pos, vel);
		}
		else if (circleLineSegmentCollision(p1, p3, c, r)) {
			resolvePlanarCollision(p1, p3, c, r, pos, vel);
		}
		else if (circleLineSegmentCollision(p3, p4, c, r)) {
			resolvePlanarCollision(p3, p4, c, r, pos, vel);
		}
		else if (circleLineSegmentCollision(p2, p4, c, r)) {
			resolvePlanarCollision(p2, p4, c, r, pos, vel);
		}
		
	}

	float distToLine(const Eigen::Vector2f& a, const Eigen::Vector2f& b, const Eigen::Vector2f& p) {
		Eigen::Vector2f e = (b - a).normalized();
		float projection_t = (p - a).dot(e)/(b-a).norm();
		if (projection_t > 0 && projection_t < 1) {
			return ((p - a) - (b - a).norm()*projection_t * e).norm();
		}
		else {
			return min((p - a).norm(), (p - b).norm());
		}
	}
};
