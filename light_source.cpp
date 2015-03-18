/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements light_source.h

***********************************************************/

#include <cmath>
#include "light_source.h"

void PointLight::shade( Ray3D& ray ) {
	// TODO: implement this function to fill in values for ray.col 
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray 
	// is available.  So be sure that traverseScene() is called on the ray 
	// before this function.

	Vector3D s = ray.origin - this.get_position();
	s.normalize();
	ray.dir.normalize();
	ray.intersection.normal.normalize();
	vector3D r = -1 * s + 2(s.dot(ray.intersection.normal)) * ray.intersection.normal;
	r.normalize();
	ray.col = ray.intersection.mat.ambient * this._col_ambient + ray.intersection.mat.diffuse * this._col_diffuse * max(0,s.dot(ray.intersection.normal))\
	+	ray.intersection.mat.specular * this._col_specular * [max(0,r.dot(ray.dir))] ^ ray.intersection.mat.specular_exp;
	ray.col.clamp();
}

