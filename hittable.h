#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record
{
	public:
		point3 p;
		vec3 normal;
		double t;
		bool front_face;

		void set_face_normal(const ray& r, const vec3& outward_normal) {
			// Sets the hit record normal vector.
			// NOTE: the parameter `outward_normal` is assumed to have unit length.
			
			// Determine if ray is hitting front face or back face
			// Ensure normal vector always points against the ray's direction
			front_face = dot(r.direction(), outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;

		}
};

class hittable {
	public:
		// Destructor - virtual overriden by derived classes - default implementation
		virtual ~hittable() = default;

		// const = 0 - abstract class must have implementations by derived classes
		virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif