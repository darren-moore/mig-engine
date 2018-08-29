
#include "collisionUtils.h"
#include <math.h>
using namespace Eigen;

bool circleLineSegmentCollision(const Eigen::Vector2f& p1, const Eigen::Vector2f& p2, const Eigen::Vector2f& c, float r) {

	Vector2f e = p1;
	Vector2f d = p2 - p1;

	float aye = d.squaredNorm();
	float bee = 2 * d.dot(e - c);
	float cee = (e - c).squaredNorm() - r*r;
	float t;

	float discrim = bee*bee - 4 * aye*cee;
	if (discrim > 0) {
		float s1 = (-bee + sqrt(discrim)) / (2 * aye);
		float s2 = (-bee - sqrt(discrim)) / (2 * aye);
		t = fmin(s1, s2);

		auto signum = [](float h)->bool {return ((0 < h) - (h < 0));};

		// now check if fully inside circle
		if (signum(s1) + signum(s2) == 0)
			return true;
	}
	else {
		return false;
	}

	return (t < 1 && t > 0);
}

bool circleRectangleCollision(const Eigen::Vector2f& b1, const Eigen::Vector2f& b2, const Eigen::Vector2f& c, float r) {
	Vector2f p1 = b1;
	Vector2f p2 = b2; p2.x() = b1.x();
	Vector2f p3 = b2; p3.y() = b1.y();
	Vector2f p4 = b2;
	bool hitEdges = circleLineSegmentCollision(p1, p2, c, r) ||
					circleLineSegmentCollision(p1, p3, c, r) ||
					circleLineSegmentCollision(p4, p2, c, r) ||
					circleLineSegmentCollision(p4, p3, c, r);
	bool insideRect = (c.x() > b1.x() && c.x() < b2.x()) && (c.y() > b1.y() && c.y() < b2.y());

	return(hitEdges || insideRect);
}