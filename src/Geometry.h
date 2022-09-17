#pragma once
#include <glm.hpp>
#include <SFML/Graphics.hpp>

namespace Raytracer
{
	using namespace glm;

	inline constexpr vec4 BLACK = vec4(0, 0, 0, 1.0f);
	inline constexpr vec4 RED = vec4(1.0f, 0, 0, 1.0f);
	inline constexpr vec4 GREEN = vec4(0, 1.0f, 0, 1.0f);
	inline constexpr vec4 BLUE = vec4(0, 0, 1.0f, 1.0f);
	inline constexpr vec4 YELLOW = vec4(1.0f, 1.0f, 0, 1.0f);
	inline constexpr vec4 MAGENTA = vec4(1.0f, 0, 1.0f, 1.0f);
	inline constexpr vec4 WHITE = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	class Geometry
	{
	public:
		virtual bool Intersect(const vec3 ray_orig, const vec3 ray_dir, vec3& hit_point, vec3& hit_normal, float& distance) const = 0;
		virtual bool Intersect(const vec3 ray_orig, const vec3 ray_dir) const = 0;
		vec4 color;
		bool light;
		float luminance;
		vec3 pos;
	};
}

