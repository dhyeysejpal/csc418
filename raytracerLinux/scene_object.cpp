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

bool UnitCylinder::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	
	// Cylinder of radius 1 which is intersected with two planes at z = 0.5, -0.5
	Ray3D ro;
	ro.origin = worldToModel*ray.origin;
    ro.dir = worldToModel*ray.dir;
	Point3D sphereOrigin(0,0,0);


	// Define solutions to quadratic equation
	double lambdaP_1;
	double lambdaP_2;
	double lambda_1;
	double lambda_2;

	double A = ro.dir[0]*ro.dir[0] + ro.dir[1]*ro.dir[1];
	double B = (ro.origin[0]*ro.dir[0] + ro.origin[1] * ro.dir[1]);
	double C = ro.origin[0]*ro.origin[0] + ro.origin[1]*ro.origin[1] - 1;

	
	//Find discriminant
	double D = B*B-A*C;
	Point3D intersectionPoint;
	Vector3D normal_1;
	Vector3D normal_2;
	Vector3D normal;

	//If the discriminant is negative there is no intersection
	//Else, get the lambda for the side of the cylinder
	if (D<0)
		return false;

	// calculate solutions, and take the minimum (closest) non-negative 
	// number
	lambda_1 = -B/A + sqrt(D) / A;
	lambda_2 = -B/A - sqrt(D) / A;
	if (lambda_1 < 0 && lambda_2 < 0)
		return false;
	else if (lambda_1 > 0 && lambda_2 < 0)
		lambda_2 = lambda_1;
	else
		lambdaP_2 = lambda_2;
		
	
	//See if ray intersetions either of the caps 
	//and take the minimum position value (may intersect both caps)
	lambda_1 = (-0.5-ro.origin[2])/ro.dir[2];
	lambda_2 = (0.5-ro.origin[2])/ro.dir[2];
	if (lambda_1 < lambda_2){
		lambdaP_1 = lambda_1;
		Point3D normal_temp(0,0,-1);
		normal_1 = normal_temp - sphereOrigin;
		normal_1.normalize();
	}
	else{
		lambdaP_1 = lambda_2;
		Point3D normal_temp(0,0,1);
		normal_1 = normal_temp - sphereOrigin;
		normal_1.normalize();
	}

	
	intersectionPoint = ro.origin + lambdaP_1 * ro.dir;
	if (lambdaP_1* lambdaP_1 < 0.001){
		return false;
	}
	//Use the first lambda to check if it intersects with the cap, top or bottom
	if (intersectionPoint[0]*intersectionPoint[0] + intersectionPoint[1] * intersectionPoint[1] <= 1)
	{
		if (!ray.intersection.none > ray.intersection.t_value){
			return false;
		}
		ray.intersection.point = intersectionPoint;
		ray.intersection.normal = normal_1;
		ray.intersection.t_value = lambdaP_1;
		ray.intersection.none = false;
		return true;
	}


	 //if not intersected with the caps, use the second lamdba to check 
	 //if intersects with the side
	intersectionPoint = ro.origin + lambdaP_2 * ro.dir;
	if (lambdaP_2 * lambdaP_2 < 0.001)
		return false;
	
	normal_2[0] = intersectionPoint[0];
	normal_2[1] = intersectionPoint[1];
	normal_2[2] = 0;
	normal_2.normalize();



	if (intersectionPoint[2] < 0.5 && intersectionPoint[2] > -0.5)
	{
		if (!ray.intersection.none > ray.intersection.t_value)
			return false;
		
		ray.intersection.point = modelToWorld * intersectionPoint;
		Point3D normalll;
		normalll[0] = intersectionPoint[0];
		normalll[1] = intersectionPoint[1];
		normalll[2] = 0;
		ray.intersection.normal = modelToWorld * (normalll - sphereOrigin);
		ray.intersection.t_value = lambdaP_2;
		ray.intersection.none = false;
		return true;
	}
	else
		return false;

}


