/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements scene_object.h

***********************************************************/

#include <cmath>
#include <iostream>
#include "scene_object.h"

bool UnitSquare::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0), 
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.

	ray.origin = worldToModel * ray.origin;
	ray.dir = worldToModel * ray.dir;

	float l = ray.dir[2]/ray.origin[2];   // (a + ld).n = 0; On separating x,y and z components, nx and ny are 0; Hence (a_z + l * d_z) * 1 = 0; l = d_z/a_z;


	/*the four bounding lines of the square are:
	l1 -> x - 0.5 = 0
	l2 -> x + 0.5 = 0
	l3 -> y - 0.5 = 0
	l4 -> y + 0.5 = 0
	In order for the point to be inside the square, f(l1) < 0, f(l2) > 0, f(l3) < 0 and f(l4) > 0
	*/

	Point3D pt = ray.origin + l * ray.dir;
	if((pt[0] - 0.5 < 0) and (pt[0] + 0.5 > 0) and (pt[1] - 0.5 < 0) and (pt[1] + 0.5 > 0))
	{
		ray.intersection.point = pt;
		ray.intersection.none = false;
		ray.intersection.t_value = l;
		ray.intersection.normal= Vector3D(0,0,1);
		return true;
	}

	return false;
}

bool UnitSphere::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSphere, which is centred 
	// on the origin.  
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.

	ray.origin = worldToModel * ray.origin;
	ray.dir = worldToModel * ray.dir;

	float A = ray.dir.dot(ray.dir);
	Point3D c = Point3D(0,0,0);
	Vector3D f = Vector3D(ray.origin[0] - c[0], ray.origin[1]- c[1], ray.origin[2]- c[2]);
	float B = f.dot(ray.dir);  
	float C = f.dot(f) - 1;
	float D = B * B - A * C;

	if (D >= 0)
	{
		float l1 = -1 * (B/A) + sqrt(D)/A;
		float l2 = -1 * (B/A) - sqrt(D)/A;

		if (l1 < 0 and l2 < 0)
			return false;

		else if (l1 > 0 and l2 < 0)
		{
			ray.intersection.point = ray.origin + l1 * ray.dir;
			ray.intersection.none = false;
			ray.intersection.t_value = l1;
			ray.intersection.normal = Vector3D(ray.intersection.point[0],ray.intersection.point[1],ray.intersection.point[2]);   //normal at point on circle is x/R,y/R,z/R. R = 1 here.
			return true; 
		}

		else if (l1 > l2 and l2 > 0)
		{
			ray.intersection.point = ray.origin + l2 * ray.dir;
			ray.intersection.none = false;
			ray.intersection.t_value = l2;
			ray.intersection.normal = Vector3D(ray.intersection.point[0],ray.intersection.point[1],ray.intersection.point[2]);
			return true; 
		}
	}
	return false;
}

