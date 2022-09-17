#pragma once
#include "Geometry.h"

namespace Raytracer
{
	class Triangle : public Geometry
	{
	public:
		Triangle();
		Triangle(vec3 vert_0, vec3 vert_1, vec3 vert_2, vec4 col);
		~Triangle();
		bool Intersect(const vec3 ray_orig, const vec3 ray_dir, vec3& hit_point, vec3& hit_normal, float& distance) const;
		bool Intersect(const vec3 ray_orig, const vec3 ray_dir) const;
	private:
		vec3 vertex_0, vertex_1, vertex_2;
	};
}