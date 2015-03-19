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
// using phong shading. Make sure your vectors are normalized, and
// clamp colour values to 1.0.
//
// It is assumed at this point that the intersection information in ray
// is available. So be sure that traverseScene() is called on the ray
// before this function.
	Colour Ka = ray.intersection.mat->ambient;
	Colour Kd = ray.intersection.mat->diffuse;
	Colour Ks = ray.intersection.mat->specular;
	Colour Ia = _col_ambient;
	Colour Id = _col_diffuse;
	Colour Is = _col_specular;
	Vector3D N = ray.intersection.normal;
	Vector3D L = _pos - ray.intersection.point;
	Vector3D V = -ray.dir;
	Vector3D R = 2.* (L.dot(N) * N) - L;
	N.normalize();
	L.normalize();
	V.normalize();
	R.normalize();
	Colour ambient = (Ka * Ia);
	Colour diffuse = (fmax(0, N.dot(L)) * Kd * Id) ;
	Colour specular = (pow(fmax(0, V.dot(R)), ray.intersection.mat->specular_exp) * Ks * Is);

	//Scene Signature
	//ray.col= Kd;

	//Diffuse
	//ray.col = ambient + diffuse;

	//Phong
	ray.col = ambient + diffuse + specular;

	ray.col.clamp();
}