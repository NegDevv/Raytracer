#pragma once
#include "Geometry.h"

namespace Raytracer
{
	class Sphere: public Geometry
	{
	public:
		Sphere();
		Sphere(const vec3 pos, const float r, const vec4 color);
		Sphere(const vec3 pos, const float r, const vec4 color, const bool light);
		~Sphere();

		bool Intersect(const vec3 ray_orig, const vec3 ray_dir, vec3& hit_point_0, vec3& hit_point_1, vec3& hit_normal_0, vec3& hit_normal_1, float& distance_0, float& distance_1) const;
		bool Intersect(const vec3 ray_orig, const vec3 ray_dir, vec3&hit_point, vec3& hit_normal, float &distance) const;
		bool Intersect(const vec3 ray_orig, const vec3 ray_dir) const;
		float radius;
	};
}
