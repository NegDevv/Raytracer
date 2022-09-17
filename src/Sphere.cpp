#pragma once
#include "Sphere.h"
#include <iostream>

namespace Raytracer
{

	Sphere::Sphere()
	{
		pos = vec3(0);
		radius = 1.0f;
		color = vec4(MAGENTA);
		light = false;
	}

	Sphere::Sphere(const vec3 position, const float r, const vec4 c)
	{
		pos = position;
		radius = r;
		color = c;
		light = false;
	}

	Sphere::Sphere(const vec3 position, const float r, const vec4 c, const bool l)
	{
		pos = position;
		radius = r;
		color = c;
		light = l;
	}

	Sphere::~Sphere()
	{

	}

	bool Sphere::Intersect(const vec3 ray_orig, const vec3 ray_dir, vec3& hit_point_0, vec3& hit_point_1, vec3& hit_normal_0, vec3& hit_normal_1, float& distance_0, float& distance_1) const
	{
		vec3 oc = ray_orig - pos;
		float a = dot(ray_dir, ray_dir);
		float b = 2.0f * dot(oc, ray_dir);
		float c = dot(oc, oc) - radius * radius;
		float D = b * b - 4.0f * a * c;

		if (D < 0)
		{
			return false;
		}

		// Solve hitpoint
		D = sqrtf(D);

		float t_0 = (-0.5f) * (b + D) / a;
		float t_1 = (-0.5f) * (b - D) / a;

		float a_sqroot = sqrtf(a);

		distance_0 = a_sqroot * t_0;
		hit_point_0 = ray_orig + t_0 * ray_dir;
		hit_normal_0 = (hit_point_0 - pos) / radius;

		distance_1 = a_sqroot * t_1;
		hit_point_1 = ray_orig + t_1 * ray_dir;
		hit_normal_1 = (hit_point_1 - pos) / radius;

		return true;
	}

	bool Sphere::Intersect(const vec3 ray_orig, const vec3 ray_dir, vec3& hit_point, vec3& hit_normal, float& distance) const
	{
		vec3 oc = ray_orig - pos;
		float a = dot(ray_dir, ray_dir);
		float b = 2.0f * dot(oc, ray_dir);
		float c = dot(oc, oc) - radius * radius;
		float D = b * b - 4.0f * a * c;

		if (D < 0.0f)
		{
			return false;
		}

		// Solve hitpoint
		D = sqrtf(D);

		float t = (-0.5f) * (b + D) / a;

		distance = sqrtf(a) * t;
		hit_point = ray_orig + t * ray_dir;
		hit_normal = normalize(hit_point - pos);

		return true;
	}

	bool Sphere::Intersect(const vec3 ray_orig, const vec3 ray_dir) const
	{
		vec3 oc = ray_orig - pos;
		float a = dot(ray_dir, ray_dir);
		float b = 2.0f * dot(oc, ray_dir);
		float c = dot(oc, oc) - radius * radius;
		float D = b * b - 4.0f * a * c;

		if (D < 0.0f)
		{
			return false;
		}

		return true;
	}
}