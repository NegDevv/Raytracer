#include <math.h>
#include "Camera.h"
#include "Ray.h"
#include <iostream>
#include "Timer.h"

namespace Raytracer
{
	Camera::Camera(uint32_t width, uint32_t height)
	{
		canvas_width = width;
		canvas_height = height;

		half_width = round(canvas_width / 2.0f);
		half_height = round(canvas_height / 2.0f);

		pos = vec3(0.0f, 0.0f, 0.0f);
		rot = vec3(0.0f, 0.0f, 0.0f);
	}

	Camera::Camera(uint32_t width, uint32_t height, vec3 position, vec3 rotation)
	{
		canvas_width = width;
		canvas_height = height;

		half_width = round(canvas_width / 2.0f);
		half_height = round(canvas_height / 2.0f);

		pos = position;
		rot = rotation;
	}


	Camera::~Camera()
	{

	}

	void Camera::Render(sf::Image& scene_image, const std::vector<Geometry*>& geometry) const
	{
		std::cout << "Starting a new render" << std::endl;
		Timer renderTimer;
		float pixel_z = (float)half_width / (tan(fov / 2.0f));
		for (size_t y = 0; y < canvas_height; y++)
		{
			float pixel_y = pos.y + (-half_height) + y;
			uint32_t canvas_y = canvas_height - 1 - y;
			for (size_t x = 0; x < canvas_width; x++)
			{
				float pixel_x = pos.x + (-half_width) + x;

				vec3 pixel_pos(pixel_x, pixel_y, pixel_z);
				vec3 ray_dir = pixel_pos - pos;
				Ray ray(pos, ray_dir);
				sf::Color pixel_color = ray.Trace(geometry);
				scene_image.setPixel(x, canvas_y, pixel_color);
			}
		}

		std::cout << "Render done!" << std::endl << "Time: " << renderTimer.Time_str() << std::endl;
	}
}