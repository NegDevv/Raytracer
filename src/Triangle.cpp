#include "Triangle.h"

namespace Raytracer
{

	Triangle::Triangle()
	{
		vertex_0 = vec3(0);
		vertex_1 = vec3(0);
		vertex_2 = vec3(0);
		pos = vec3(0);
		color = vec4(MAGENTA);
	}

	Triangle::Triangle(const vec3 vert_0, const vec3 vert_1, const vec3 vert_2, const vec4 col)
	{
		vertex_0 = vert_0;
		vertex_1 = vert_1;
		vertex_2 = vert_2;

		float x = (vert_0.x + vert_1.x + vert_2.x) / 3;
		float y = (vert_0.y + vert_1.y + vert_2.y) / 3;
		float z = (vert_0.z + vert_1.z + vert_2.z) / 3;

		pos = vec3(x, y, z);

		color = col;
	}

	Triangle::~Triangle()
	{

	};

	bool Triangle::Intersect(const vec3 ray_orig, const vec3 ray_dir, vec3& hit_point, vec3& hit_normal, float& distance) const
	{
		// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

		const float EPSILON = 0.0000001;
		vec3 edge_1, edge_2, h, s, q;
		float a, f, u, v;
		edge_1 = vertex_1 - vertex_0;
		edge_2 = vertex_2 - vertex_0;
		h = cross(ray_dir, edge_2);
		a = dot(edge_1, h);

		if (a > -EPSILON && a < EPSILON)
		{
			return false;    // This ray is parallel to this triangle.
		}

		f = 1.0 / a;
		s = ray_orig - vertex_0;
		u = f * dot(s, h);

		if (u < 0.0 || u > 1.0)
		{
			return false;

		}

		q = cross(s, edge_1);
		v = f * dot(ray_dir, q);

		if (v < 0.0 || u + v > 1.0)
		{
			return false;
		}

		// At this stage we can compute t to find out where the intersection point is on the line.
		float t = f * dot(edge_2, q);

		if (t > EPSILON) // ray intersection
		{
			hit_point = ray_orig + ray_dir * t;
			distance = sqrtf(dot(ray_dir, ray_dir)) * t;
			vec3 edge_1 = vertex_1 - vertex_0;
			vec3 edge_2 = vertex_2 - vertex_0;
			hit_normal = cross(edge_1, edge_2);
			return true;
		}
		else
		{
			// This means that there is a line intersection but not a ray intersection.
			return false;
		}


	}

	bool Triangle::Intersect(const vec3 ray_orig, const vec3 ray_dir) const
	{
		// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

		const float EPSILON = 0.0000001;
		vec3 edge_1, edge_2, h, s, q;
		float a, f, u, v;
		edge_1 = vertex_1 - vertex_0;
		edge_2 = vertex_2 - vertex_0;
		h = cross(ray_dir, edge_2);
		a = dot(edge_1, h);

		if (a > -EPSILON && a < EPSILON)
		{
			return false;    // This ray is parallel to this triangle.
		}

		f = 1.0 / a;
		s = ray_orig - vertex_0;
		u = f * dot(s, h);

		if (u < 0.0 || u > 1.0)
		{
			return false;

		}

		q = cross(s, edge_1);
		v = f * dot(ray_dir, q);

		if (v < 0.0 || u + v > 1.0)
		{
			return false;
		}

		// At this stage we can compute t to find out where the intersection point is on the line.
		float t = f * dot(edge_2, q);

		if (t > EPSILON) // ray intersection
		{
			/*hit_point = ray_orig + ray_dir * t;
			distance = sqrtf(ray_dir.dot(ray_dir)) * t;
			Vector3f edge_1 = vertex_1 - vertex_0;
			Vector3f edge_2 = vertex_2 - vertex_0;
			hit_normal = edge_1.cross(edge_2);*/
			return true;
		}
		else
		{
			// This means that there is a line intersection but not a ray intersection.
			return false;
		}
	}
}