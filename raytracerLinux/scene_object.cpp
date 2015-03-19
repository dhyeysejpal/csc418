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

	Point3D origin = worldToModel * ray.origin;
	Vector3D dir = worldToModel * ray.dir;

	float l = -1 * origin[2]/dir[2];   // (a + ld).n = 0; On separating x,y and z components, nx and ny are 0; Hence (a_z + l * d_z) * 1 = 0; l = d_z/a_z;

	if (l<= 0)
		return false;

	Point3D pt = origin + l * dir;

	if((pt[0] - 0.5 < 0) and (pt[0] + 0.5 > 0) and (pt[1] - 0.5 < 0) and (pt[1] + 0.5 > 0))
	{
		if (ray.intersection.none || l < ray.intersection.t_value) 
		{
			
			ray.intersection.point = modelToWorld * Point3D(pt[0], pt[1], 0);;
			ray.intersection.none = false;
			ray.intersection.t_value = l;
			ray.intersection.normal= worldToModel.transpose() * Vector3D(0, 0, 1);
			ray.intersection.normal.normalize();
			return true;
		}
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

	Point3D origin = worldToModel * ray.origin;
	Vector3D dir = worldToModel * ray.dir;

	float A = dir.dot(dir);
	Vector3D f = origin - Point3D(0,0,0);
	float B = f.dot(dir);  
	float C = f.dot(f) - 1;
	float D = B * B - A * C;

	if (D >= 0)
	{
		float l1 = -1 * (B/A) + sqrt(D)/A;
		float l2 = -1 * (B/A) - sqrt(D)/A;
		float l;

		if (l1 < 0 and l2 < 0)
			return false;
		else if ( l1 < 0 )
			l= l2;
		else if ( l2 < 0 )
			l = l1;
		else
			l = fmin(l1, l2);

		Point3D intpt = origin + l * dir;

		if (ray.intersection.none || l < ray.intersection.t_value) 
		{
			ray.intersection.t_value = l;
			ray.intersection.point = modelToWorld * intpt;
			ray.intersection.normal = worldToModel.transpose() * Vector3D(intpt[0],intpt[1],intpt[2]);
			ray.intersection.normal.normalize();
			ray.intersection.none = false;
			return true;
		}
	}
	return false;
}

