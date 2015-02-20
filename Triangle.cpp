#include <cfloat>
#include "Triangle.h"
#include <iostream>

using namespace std;

Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c){
	Vertex_a = a;
	Vertex_b = b;
	Vertex_c = c;
	normal = (Vertex_b - Vertex_a).cross(Vertex_c - Vertex_a);
	//normal.normalize();
}

