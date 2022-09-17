#include "Ray.h"
#include <iostream>
#include <math.h>

namespace Utils
{
	sf::Color ConvertRGBAToSfColor(glm::vec4 color)
	{
		uint8_t r = (uint8_t)std::min(color.r * 255.0f, 255.0f);
		uint8_t g = (uint8_t)std::min(color.g * 255.0f, 255.0f);
		uint8_t b = (uint8_t)std::min(color.b * 255.0f, 255.0f);
		uint8_t a = (uint8_t)std::min(color.a * 255.0f, 255.0f);


		return sf::Color(r, g, b, a);
	}
}

namespace Raytracer
{

	Ray::Ray(vec3 origin, vec3 direction)
	{
		org = origin;
		dir = direction;
	}

	Ray::~Ray()
	{

	}


	sf::Color Ray::Trace(const std::vector<Geometry*>& geometry) const
	{
		vec4 pixel_color(BLACK);
		vec4 surface_color(BLACK);

		vec3 hit_point, hit_normal;
		float closest = INFINITY;
		float distance = INFINITY;
		Geometry* closest_object = nullptr;

		for (size_t i = 0; i < geometry.size(); i++)
		{
			if (geometry[i]->Intersect(org, dir, hit_point, hit_normal, distance))
			{
				if (distance < closest)
				{
					closest_object = geometry[i];
					closest = distance;
					surface_color = closest_object->color;
				}
			}
		}

		if (!closest_object)
		{
			return Utils::ConvertRGBAToSfColor(BLACK);
		}

#define USE_SHADING
#ifdef USE_SHADING

		for (size_t i = 0; i < geometry.size(); i++)
		{
			if (geometry[i]->light)
			{
				Geometry* light = geometry[i];
				vec3 light_ray_dir = normalize(light->pos - hit_point);
				vec3 light_ray_orig = hit_point;
				bool illuminated = true;
				float bias = 1e-4;
				for (size_t j = 0; j < geometry.size(); j++)
				{
					if (i != j)
					{
						if (geometry[j]->Intersect(-light_ray_orig + hit_normal * bias, light_ray_dir))
						{
							//std::cout << "light_ray_orig: " << light_ray_orig << std::endl;
							//std::cout << "hit_point: " << hit_point << std::endl;
							illuminated = false;
							break;
						}
						/*std::cout << "light_ray_orig: " << light_ray_orig << std::endl;
						std::cout << "hit_point: " << hit_point << std::endl;*/
					}
				}

				float light_amount = std::max(dot(hit_normal, light_ray_dir), 0.0f) * (float)illuminated;
				//std::cout << "light_amount "  << light_amount << std::endl;


				pixel_color.r += surface_color.r * light_amount;
				pixel_color.g += surface_color.g * light_amount;
				pixel_color.b += surface_color.b * light_amount;
			}
		}
#elif
			pixel_color = surface_color;
#endif
		return Utils::ConvertRGBAToSfColor(pixel_color);
	}




	// Should use data oriented layout for this vectorization setup
	bool Ray::Intersect_AVX(const __m256& sphere_pos_x, const __m256& sphere_pos_y, const __m256& sphere_pos_z, const __m256& sphere_radius,
		__m256& hit_point_x, __m256& hit_point_y, __m256& hit_point_z,
		__m256& hit_normal_x, __m256& hit_normal_y, __m256& hit_normal_z,
		__m256& distances) const
	{
		const __m256 ray_org_vec_x = _mm256_set1_ps(org.x);
		const __m256 ray_org_vec_y = _mm256_set1_ps(org.y);
		const __m256 ray_org_vec_z = _mm256_set1_ps(org.z);

		const __m256 ray_dir_vec_x = _mm256_set1_ps(dir.x);
		const __m256 ray_dir_vec_y = _mm256_set1_ps(dir.y);
		const __m256 ray_dir_vec_z = _mm256_set1_ps(dir.z);


		//Vector3f oc = org - pos;
		const __m256 oc_x = _mm256_sub_ps(ray_org_vec_x, sphere_pos_x);
		const __m256 oc_y = _mm256_sub_ps(ray_org_vec_y, sphere_pos_y);
		const __m256 oc_z = _mm256_sub_ps(ray_org_vec_z, sphere_pos_z);


		//float a = ray_dir.dot(ray_dir);
		const __m256 a = _mm256_fmadd_ps(ray_dir_vec_x, ray_dir_vec_x, (_mm256_fmadd_ps(ray_dir_vec_y, ray_dir_vec_y, (_mm256_mul_ps(ray_dir_vec_z, ray_dir_vec_z)))));


		const __m256 mul_vec_2 = _mm256_set1_ps(2.0f);

		//float b = 2.0 * oc.dot(ray_dir);
		const __m256 b = _mm256_mul_ps(mul_vec_2, _mm256_fmadd_ps(oc_x, ray_dir_vec_x, (_mm256_fmadd_ps(oc_y, ray_dir_vec_y, (_mm256_mul_ps(oc_z, ray_dir_vec_z))))));


		//float c = oc.dot(oc) - radius * radius;

		__m256 radius_sqr = _mm256_mul_ps(sphere_radius, sphere_radius);

		const __m256 c = _mm256_sub_ps(_mm256_fmadd_ps(oc_x, oc_x, (_mm256_fmadd_ps(oc_y, oc_y, (_mm256_mul_ps(oc_z, oc_z))))), radius_sqr);

		//float D = b * b - 4 * a * c;

		const __m256 mul_vec_4 = _mm256_set1_ps(4.0f);

		const __m256 D = _mm256_sub_ps(_mm256_mul_ps(b, b), _mm256_mul_ps(_mm256_mul_ps(mul_vec_4, a), c));

		return false;
	}
}
