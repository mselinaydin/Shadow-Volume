#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "vector3.h"
#include <string>
#include <fstream>
#include <vector>

class Triangle{
private:
	float beta, gamma;
	int MaterialIndex;
	float A;
	
	//bunlara elleşme
	Vector3 ab;
	Vector3 ac;
	Vector3 dir;
	Vector3 ao;
public:
	Triangle(Vector3 a, Vector3 b, Vector3 c);

	virtual int GetMaterial(){return MaterialIndex;};
	float t_min;
	
	virtual Vector3 GetNormal(Vector3 intPoint){return normal;};
	
	
	//privatedan taşıma
	
	Vector3 Vertex_a, Vertex_b, Vertex_c;
	Vector3 normal;
};



#endif
