#pragma once
#include <math.h>
#include "Sphere.h"
#include <vector>

namespace Raytracer
{
	class Camera {
	public:
		Camera(uint32_t width, uint32_t height);

		Camera(uint32_t width, uint32_t height, vec3 pos, vec3 rot);

		~Camera();

		void Render(sf::Image& scene_image, const std::vector<Geometry*>& geometry) const;

	private:

		uint32_t canvas_width;
		uint32_t canvas_height;
		int32_t half_width;
		int32_t half_height;

		float fov = 90;

		vec3 pos = vec3(0);
		vec3 rot = vec3(0);
	};
}