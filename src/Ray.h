#include "Sphere.h"
#include <vector>
#include <immintrin.h>

namespace Raytracer
{
	class Ray
	{
	public:

		Ray(vec3 origin, vec3 direction);

		~Ray();

		sf::Color Trace(const std::vector<Geometry*>& geometry) const;
		bool Intersect_AVX(const __m256& sphere_pos_x, const __m256& sphere_pos_y, const __m256& sphere_pos_z, const __m256& sphere_radius,
			__m256& hit_point_x, __m256& hit_point_y, __m256& hit_point_z,
			__m256& hit_normal_x, __m256& hit_normal_y, __m256& hit_normal_z,
			__m256& distances) const;

	private:
		vec3 org;
		vec3 dir;
	};
}