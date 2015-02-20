#include <GL/glut.h>
#include <GL/gl.h>
#include <string>
#include <fstream>
#include "Triangle.h"
#include "vector3.h"
#include <vector>
#include <iostream>
#include <cfloat>
#include <cmath>


#define PI 3.14159265
#define T_SIZE 256
//derlerken g++ hw4.cpp -lGLU -lGL -lglut
using namespace std;

vector<Triangle> TriVec;
struct Edge{
	Vector3 vx1, vx2;
	Edge(Vector3 a, Vector3 b){vx1 = a; vx2 = b;};
};
vector<Edge> ContourEdge;


GLuint shirt, text;

bool fst = true, snd = false;
float minX   = FLT_MAX, minY  = FLT_MAX, minZ  = FLT_MAX, maxX = FLT_MIN, maxY = FLT_MIN, maxZ = FLT_MIN;
Vector3 center;
float start;
float posx = 0, posy = 1, posz, ptx = 0, pty = 0, ptz = 0, ux = 0, uy = 1, uz = 0;
float lx = 0, ly = 0, lz = 0;
float secLx = 0, secLy = 0, secLz = 0;
float deg = 0;
float lightDeg = 0;
float lightDeg1 = 0;

float upDeg = 0, downDeg = 0, rightDeg = 0, leftDeg = 0;
Vector3 rght;

bool isH = false;

bool movingUp = false; // Whether or not we are moving up or down 
bool movingRight = false;
float moveY = 0, moveX = 0;

bool growing = false;
float scale = 1;

GLuint ttop, tbottom, tleft, tright, tfront, tback;
float skyboxsize;

//float yLocation = 0.0f; // Keep track of our position on the y axis.
float yRotationAngle = 0.0f; // The angle of rotation for our object


bool* keyStates = new bool[256];// Create an array of boolean values of length 256 (0-255)  
bool* keySpecialStates = new bool[256];


void findCEdges(){
	ContourEdge.clear();
	Vector3 LightPos(lx, ly, lz);
	int triSize = TriVec.size();
	for (int i = 0; i < triSize; i++)
	{
		Vector3 avPt(((TriVec[i].Vertex_a._x + TriVec[i].Vertex_b._x + TriVec[i].Vertex_c._x) / 3), 
					((TriVec[i].Vertex_a._y + TriVec[i].Vertex_b._y + TriVec[i].Vertex_c._y) / 3),
					((TriVec[i].Vertex_a._z + TriVec[i].Vertex_b._z + TriVec[i].Vertex_c._z) / 3) );
		Vector3 incidentLight = avPt - LightPos;
		
		if (incidentLight.dot(TriVec[i].normal) >= 0)
		{
			//every edge of the triangle.
			Edge e1(TriVec[i].Vertex_a, TriVec[i].Vertex_b);
			bool here = false;
			int csize = ContourEdge.size();
			for (int j = 0; j < csize; j++)
				if (ContourEdge[j].vx2 == e1.vx1 && ContourEdge[j].vx1 == e1.vx2)
				{
					ContourEdge.erase(ContourEdge.begin() + j);
					here = true;
					break;
				}
			if (!here) //its not in the list
				ContourEdge.push_back(e1);				
				
			Edge e2(TriVec[i].Vertex_b, TriVec[i].Vertex_c);
			here = false;
			csize = ContourEdge.size();
			for (int j = 0; j < csize; j++)
				if (ContourEdge[j].vx2 == e2.vx1 && ContourEdge[j].vx1 == e2.vx2)
				{
					ContourEdge.erase(ContourEdge.begin() + j);
					here = true;
					break;
				}
			if (!here) //its not in the list
				ContourEdge.push_back(e2);				
			
			Edge e3(TriVec[i].Vertex_c, TriVec[i].Vertex_a);
			here = false;
			csize = ContourEdge.size();
			for (int j = 0; j < csize; j++)
				if (ContourEdge[j].vx2 == e3.vx1 && ContourEdge[j].vx1 == e3.vx2)
				{
					ContourEdge.erase(ContourEdge.begin() + j);
					here = true;
					break;
				}
			if (!here) //its not in the list
				ContourEdge.push_back(e3);			
		}		
	}
	//~ glColor3f(1, 1, 1);	
	//~ for (int i = 0; i < ContourEdge.size(); i++)
	//~ {
		//~ glBegin(GL_LINES);
		//~ glVertex3f(ContourEdge[i].vx1._x, ContourEdge[i].vx1._y, ContourEdge[i].vx1._z);
		//~ glVertex3f(ContourEdge[i].vx2._x, ContourEdge[i].vx2._y, ContourEdge[i].vx2._z);
		//~ glEnd();
	//~ }
	
}
void findCEdges1(){
	ContourEdge.clear();
	Vector3 LightPos(secLx, secLy, secLz);
	int triSize = TriVec.size();
	for (int i = 0; i < triSize; i++)
	{
		Vector3 avPt(((TriVec[i].Vertex_a._x + TriVec[i].Vertex_b._x + TriVec[i].Vertex_c._x) / 3), 
					((TriVec[i].Vertex_a._y + TriVec[i].Vertex_b._y + TriVec[i].Vertex_c._y) / 3),
					((TriVec[i].Vertex_a._z + TriVec[i].Vertex_b._z + TriVec[i].Vertex_c._z) / 3) );
		Vector3 incidentLight = avPt - LightPos;
		
		if (incidentLight.dot(TriVec[i].normal) >= 0)
		{
			//every edge of the triangle.
			Edge e1(TriVec[i].Vertex_a, TriVec[i].Vertex_b);
			bool here = false;
			int csize = ContourEdge.size();
			for (int j = 0; j < csize; j++)
				if (ContourEdge[j].vx2 == e1.vx1 && ContourEdge[j].vx1 == e1.vx2)
				{
					ContourEdge.erase(ContourEdge.begin() + j);
					here = true;
					break;
				}
			if (!here) //its not in the list
				ContourEdge.push_back(e1);				
				
			Edge e2(TriVec[i].Vertex_b, TriVec[i].Vertex_c);
			here = false;
			csize = ContourEdge.size();
			for (int j = 0; j < csize; j++)
				if (ContourEdge[j].vx2 == e2.vx1 && ContourEdge[j].vx1 == e2.vx2)
				{
					ContourEdge.erase(ContourEdge.begin() + j);
					here = true;
					break;
				}
			if (!here) //its not in the list
				ContourEdge.push_back(e2);				
			
			Edge e3(TriVec[i].Vertex_c, TriVec[i].Vertex_a);
			here = false;
			csize = ContourEdge.size();
			for (int j = 0; j < csize; j++)
				if (ContourEdge[j].vx2 == e3.vx1 && ContourEdge[j].vx1 == e3.vx2)
				{
					ContourEdge.erase(ContourEdge.begin() + j);
					here = true;
					break;
				}
			if (!here) //its not in the list
				ContourEdge.push_back(e3);			
		}		
	}
}
 
void renderGreyFloor(){
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-3, minY-0.2, 3);
	glVertex3f(3, minY-0.2, 3);
	glVertex3f(3, minY-0.2, -3);
	glVertex3f(-3, minY-0.2, -3);
	glEnd();
}

void renderShad(){
	glColor3f(1, 1, 1);
	Vector3 lightPos(lx, ly, lz);
	for (int i = 0; i < ContourEdge.size(); i++)
	{
		Vector3 ade = ContourEdge[i].vx1 + ((ContourEdge[i].vx1 - lightPos) * 150);
		Vector3 bde = ContourEdge[i].vx2 + ((ContourEdge[i].vx2 - lightPos) * 150);
		glBegin(GL_QUADS);
		glVertex3f(ContourEdge[i].vx1._x, ContourEdge[i].vx1._y, ContourEdge[i].vx1._z);
		glVertex3f(ContourEdge[i].vx2._x, ContourEdge[i].vx2._y, ContourEdge[i].vx2._z);
		glVertex3f(bde._x, bde._y, bde._z);
		glVertex3f(ade._x, ade._y, ade._z);
		glEnd();		
	}	
} 
void renderShad1(){
	glColor3f(1, 1, 1);
	Vector3 lightPos(secLx, secLy, secLz);
	for (int i = 0; i < ContourEdge.size(); i++)
	{
		Vector3 ade = ContourEdge[i].vx1 + ((ContourEdge[i].vx1 - lightPos) * 150);
		Vector3 bde = ContourEdge[i].vx2 + ((ContourEdge[i].vx2 - lightPos) * 150);
		glBegin(GL_QUADS);
		glVertex3f(ContourEdge[i].vx1._x, ContourEdge[i].vx1._y, ContourEdge[i].vx1._z);
		glVertex3f(ContourEdge[i].vx2._x, ContourEdge[i].vx2._y, ContourEdge[i].vx2._z);
		glVertex3f(bde._x, bde._y, bde._z);
		glVertex3f(ade._x, ade._y, ade._z);
		glEnd();		
	}	
} 
void shadowVolume(){
	//renderBlackFloor();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	renderGreyFloor();
	
	glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 0, 0);
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	
	glCullFace(GL_BACK);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	renderShad();
	
	glCullFace(GL_FRONT);
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	renderShad();
	
	glDepthMask(1);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_ONE);
	
	
	glStencilFunc(GL_EQUAL, 0, 1);
	glColorMask(1, 1, 1, 1);
	glEnable(GL_LIGHT0);
	renderGreyFloor();
	glDisable(GL_STENCIL_TEST);
	
	glDisable(GL_BLEND);
}
void shadowVolume1(){
	
	glClear(GL_STENCIL_BUFFER_BIT);
	
	//glDisable(GL_LIGHT1);
	//glDisable(GL_LIGHT0);
	//renderGreyFloor();
	
	glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 0, 0);
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	
	glCullFace(GL_BACK);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	renderShad1();
	
	glCullFace(GL_FRONT);
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	renderShad1();
	
	glDepthMask(1);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	
	glStencilFunc(GL_EQUAL, 0, 1);
	glColorMask(1, 1, 1, 1);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_ONE);
	
	glEnable(GL_LIGHT1);
	renderGreyFloor();
	glDisable(GL_STENCIL_TEST);
	
	glDisable(GL_BLEND);
}
 
//u nun etrafında tor u deg kadar dondurmek
Vector3 Rot(Vector3 u, Vector3 tor, float deg){
	Vector3 ret;
	float cs = cos(deg * PI / 180);
	float sn = sin(deg * PI / 180);
	u.normalize();
	ret._x = tor._x*(cs + (u._x * u._x)*(1 - cs)) + tor._y*((u._x * u._y)*(1 - cs) - (u._z*sn)) + tor._z*((u._x * u._z*(1-cs)) + u._y * sn);
	ret._y = tor._x*((u._x * u._y)*(1 - cs)+(u._z*sn)) + tor._y*(cs + (u._y * u._y)*(1 - cs)) + tor._z*((u._y * u._z*(1-cs)) - u._x * sn);
	ret._z = tor._x*((u._x * u._z*(1-cs)) - u._y * sn) + tor._y*((u._y * u._z*(1-cs)) + u._x * sn) + tor._z*(cs + (u._z * u._z)*(1 - cs));
	return ret;
}
void camRot(){
	deg += 0.2;
	if(deg > 360)
		deg -= 360;
		
	posx = abs(start) * sin(deg * PI / 180);
	posz = abs(start) * cos(deg * PI / 180);
}
void lightRot(){
	lightDeg += 0.2;
	if(lightDeg > 360)
		lightDeg -= 360;
		
	lx = abs(0.2) * sin(lightDeg * PI / 180);
	lz = abs(0.2) * cos(lightDeg * PI / 180);
	
}
void lightRot1(){
	lightDeg1 -= 0.2;
	if(lightDeg1 < 360)
		lightDeg1 += 360;
		
	secLx = abs(0.2) * sin(lightDeg1 * PI / 180);
	secLz = abs(0.2) * cos(lightDeg1 * PI / 180);
	
}

void camMoveFwd(){	
	Vector3 pos(posx, posy, posz);
	Vector3 pt(ptx, pty, ptz);
	Vector3 viewing = pt - pos;
	
	posx += viewing._x * 0.001;
	posy += viewing._y * 0.001;
	posz += viewing._z * 0.001;
	
	ptx = posx + viewing._x;
	pty = posy + viewing._y;
	ptz = posz + viewing._z;
}
void camMoveBck(){	
	Vector3 pos(posx, posy, posz);
	Vector3 pt(ptx, pty, ptz);
	Vector3 viewing = pt - pos;
	
	posx -= viewing._x * 0.001;
	posy -= viewing._y * 0.001;
	posz -= viewing._z * 0.001;
	
	ptx = posx + viewing._x;
	pty = posy + viewing._y;
	ptz = posz + viewing._z;
}
void camLeft(){
	Vector3 pos(posx, posy, posz);
	Vector3 pt(ptx, pty, ptz);
	Vector3 viewing = pt - pos;
	
	posx -= rght._x * 0.001;
	posy -= rght._y * 0.001;
	posz -= rght._z * 0.001;
	
	ptx = posx + viewing._x;
	pty = posy + viewing._y;
	ptz = posz + viewing._z;
	
}
void camRight(){
	Vector3 pos(posx, posy, posz);
	Vector3 pt(ptx, pty, ptz);
	Vector3 viewing = pt - pos;
	
	posx += rght._x * 0.001;
	posy += rght._y * 0.001;
	posz += rght._z * 0.001;
	
	ptx = posx + viewing._x;
	pty = posy + viewing._y;
	ptz = posz + viewing._z;
}
void camUp(){	
//	if(upDeg < 70)
		upDeg = 0.05;
	Vector3 up(ux, uy, uz);
	Vector3 newUp = Rot(rght, up, upDeg);
	ux = newUp._x;
	uy = newUp._y;
	uz = newUp._z;
	//Vector3 viewing = newUp.cross(rght);
	Vector3 viewing(ptx-posx, pty-posy, ptz-posz);
	Vector3 nV = Rot(rght, viewing, upDeg);
	//ptx = viewing._x + posx;
	//pty = viewing._y + posy;
	//ptz = viewing._z + posz;
	ptx = nV._x + posx;
	pty = nV._y + posy;
	ptz = nV._z + posz;
}
void camDown(){
	downDeg = -0.05;
	Vector3 up(ux, uy, uz);
	Vector3 viewing(ptx-posx, pty-posy, ptz-posz);
	Vector3 newUp = Rot(rght, up, downDeg);	
	ux = newUp._x;
	uy = newUp._y;
	uz = newUp._z;
	Vector3 nV = Rot(rght, viewing, downDeg);
	ptx = nV._x + posx;
	pty = nV._y + posy;
	ptz = nV._z + posz;
}
void camR(){
	rightDeg = 0.05;	
	Vector3 up(ux, uy, uz);
	Vector3 viewing(ptx-posx, pty-posy, ptz-posz);
	Vector3 nR = Rot(up, rght, -rightDeg);
	rght = nR;
	Vector3 nV = Rot(up, viewing, -rightDeg);
	
	ptx = nV._x + posx;
	pty = nV._y + posy;
	ptz = nV._z + posz;	
}
void camL(){
	leftDeg = 0.05;
	Vector3 up(ux, uy, uz);
	Vector3 viewing(ptx-posx, pty-posy, ptz-posz);
	Vector3 nR = Rot(up, rght, leftDeg);
	rght = nR;
	Vector3 nV = Rot(up, viewing, leftDeg);
	
	ptx = nV._x + posx;
	pty = nV._y + posy;
	ptz = nV._z + posz;	
	
}

void eCam(){
	Vector3 up(ux, uy, uz);
	Vector3 viewing(ptx-posx, pty-posy, ptz-posz);
	Vector3 newUp = Rot(viewing, up, -0.1);
	ux = newUp._x;
	uy = newUp._y;
	uz = newUp._z;
	Vector3 nR = Rot(viewing, rght, -0.1);
	rght = nR;
}
void rCam(){
	Vector3 up(ux, uy, uz);
	Vector3 viewing(ptx-posx, pty-posy, ptz-posz);
	Vector3 newUp = Rot(viewing, up, 0.1);
	ux = newUp._x;
	uy = newUp._y;
	uz = newUp._z;
	Vector3 nR = Rot(viewing, rght, 0.1);
	rght = nR;
	
}

void setInit(){
	movingUp = false; // Whether or not we are moving up or down 
	movingRight = false;
	moveY = 0;
	moveX = 0;
	yRotationAngle = 0;
	deg = 0;
	scale = 1;
	posx = 0;
	posy = 0;
	posz = start;
	ptx = 0;
	pty = 0;
	ptz = 0;
	ux = 0;
	uy = 1;
	uz = 0;
	Vector3 pos(posx, posy, posz);
	Vector3 pt(ptx, pty, ptz);
	Vector3 up(ux, uy, uz);
	rght = (pt - pos).cross(up);
	
	lx = 0.2; 
	ly = maxY + 0.3;
	lz = 0;
}
void printNormal(){
	for (int i = 0; i < TriVec.size(); i++)
	{
		cout << TriVec[i].normal._x << " " << TriVec[i].normal._y << " " << TriVec[i].normal._z << endl;
	}
	cout << TriVec.size() << endl;
}
void setCamera () {        
       //~ GLfloat position[] = {0, 0.1, 0.4, 0.0};
       //~ glLightfv(GL_LIGHT0, GL_POSITION , position);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       gluLookAt(posx, posy, posz, ptx, pty, ptz, ux, uy, uz);
}
void Parse(string filepath){
	fstream read;
	read.open(filepath.c_str());
	Vector3 temp1, temp2, temp3;
	while (read >> temp1._x >> temp1._y >> temp1._z)
	{		
		read >> temp2._x >> temp2._y >> temp2._z;
		read >> temp3._x >> temp3._y >> temp3._z;
		Triangle triTemp(temp1, temp2, temp3);
		TriVec.push_back(triTemp);
		if (temp1._x < minX)
			minX = temp1._x;
		if (temp1._y < minY)
			minY = temp1._y;
		if (temp1._z < minZ)
			minZ = temp1._z;
			
		if (temp2._x < minX)
			minX = temp2._x;
		if (temp2._y < minY)
			minY = temp2._y;
		if (temp2._z < minZ)
			minZ = temp2._z;
			
		if (temp3._x < minX)
			minX = temp3._x;
		if (temp3._y < minY)
			minY = temp3._y;
		if (temp3._z < minZ)
			minZ = temp3._z;
			//max
		if(temp1._x > maxX)
			maxX = temp1._x;
		if(temp1._y > maxY)
			maxY = temp1._y;
		if(temp1._z > maxZ)
			maxZ = temp1._z;
			
		if(temp2._x > maxX)
			maxX = temp2._x;
		if(temp2._y > maxY)
			maxY = temp2._y;
		if(temp2._z > maxZ)
			maxZ = temp2._z;
			
		if(temp3._x > maxX)
			maxX = temp3._x;
		if(temp3._y > maxY)
			maxY = temp3._y;
		if(temp3._z > maxZ)
			maxZ = temp3._z;		
	}
	center._x = minX + ((maxX - minX) / 2);
	center._y = minY + ((maxY - minY) / 2);
	center._z = minZ + ((maxZ - minZ) / 2);
	
	float sx, sy, sz;
	sx = maxX - minX;
	sy = maxY - minY;
	sz = maxZ - minZ;
	
	if (sx >= sy) {
		if (sx >= sz) {
			start = maxZ + 2.5 * sx;
			skyboxsize = 7 * sx;
		}
		
		else {
			start = maxZ + 2.5 * sz;
			skyboxsize = 7 * sz;
		}
	}
	
	if (sy >= sx){
		if (sy >= sz) {
			start = maxZ + 2.5 * sy;
			skyboxsize = 7 * sy;
		}
		
		else {
			start = maxZ + 2.5 * sz;
			skyboxsize = 7 * sz;
		}
	}
	posz = 3 * start;
	
	lx = maxX + 0.2;
	ly = maxY + 0.3;
	lz = 0;
	
	secLx = maxX + 0.3;
	secLy = maxY + 0.3;
	secLz = 0;
	
	Vector3 pos(posx, posy, posz);
	Vector3 pt(ptx, pty, ptz);
	Vector3 up(ux, uy, uz);
	rght = (pt - pos).cross(up);
}
void TriDrawer(){
	
	glPushMatrix();
	glColor3f(0.7f, 0.1f, 0.5f);
	glBegin(GL_TRIANGLES);	
	for (int i = 0; i < TriVec.size(); i++)
	{		
		Triangle t = TriVec[i];	
		
		//Vector3 norma(0,0,0), normb(0,0,0), normc(0,0,0);
		Vector3 norma = TriVec[i].normal, normb = TriVec[i].normal, normc = TriVec[i].normal;
		for (int j = 0; j < TriVec.size(); j++)
		{
			if(t.Vertex_a == TriVec[j].Vertex_a)
				norma += TriVec[j].normal;
			else if(t.Vertex_a == TriVec[j].Vertex_b)
				norma += TriVec[j].normal;
			else if(t.Vertex_a == TriVec[j].Vertex_c)
				norma += TriVec[j].normal;
				
			if(t.Vertex_b == TriVec[j].Vertex_a)
				normb += TriVec[j].normal;
			else if(t.Vertex_b == TriVec[j].Vertex_b)
				normb += TriVec[j].normal;
			else if(t.Vertex_b == TriVec[j].Vertex_c)
				normb += TriVec[j].normal;
				
			if(t.Vertex_c == TriVec[j].Vertex_a)
				normc += TriVec[j].normal;
			else if(t.Vertex_c == TriVec[j].Vertex_b)
				normc += TriVec[j].normal;
			else if(t.Vertex_c == TriVec[j].Vertex_c)
				normc += TriVec[j].normal;
		}
					
		
		glNormal3f(norma._x, norma._y, norma._z);
		glVertex3f(t.Vertex_a._x, t.Vertex_a._y, t.Vertex_a._z);	
			
		glNormal3f(normb._x, normb._y, normb._z);
		glVertex3f(t.Vertex_b._x, t.Vertex_b._y, t.Vertex_b._z);	
		
		glNormal3f(normc._x, normc._y, normc._z);
		glVertex3f(t.Vertex_c._x, t.Vertex_c._y, t.Vertex_c._z);
		
	}
		glEnd();
		glPopMatrix();
}
void keyOperations(){
	if(keyStates['q'])
		exit(0);
	if(keyStates[1])
		setInit();
		if(keyStates[32])
			setInit();
		if(isH)
			camRot();	
		if(keyStates[32])
			setInit();
		if(keyStates['w'])
			camMoveFwd();
		if(keyStates['s'])
			camMoveBck();
		if(keyStates['a'])
			camLeft();
		if(keyStates['d'])
			camRight();
		if(keySpecialStates[GLUT_KEY_LEFT])
			camL();
		if(keySpecialStates[GLUT_KEY_RIGHT])
			camR();
		if(keySpecialStates[GLUT_KEY_UP])
			camUp();
		if(keySpecialStates[GLUT_KEY_DOWN])
			camDown();
		if(keyStates['e'])
			eCam();
		if(keyStates['r'])
			rCam();		
}
void setLight(){
	glEnable(GL_LIGHTING);
	
	glEnable(GL_LIGHT0);
	GLfloat position[] = {lx, ly, lz, 1};
	GLfloat whiteColor[] = {1, 1 , 1 , 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION , position);
	glLightfv(GL_LIGHT0 , GL_DIFFUSE , whiteColor);
	glLightfv(GL_LIGHT0 , GL_SPECULAR , whiteColor);
	glTranslatef(lx, ly, lz);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.01, 20, 20);
	glTranslatef(-lx, -ly, -lz);	
	glEnable(GL_LIGHTING);
	
	
	glEnable(GL_LIGHT1);
	GLfloat position2[] = {secLx, secLy, secLz};
	GLfloat blueColor[] = {1, 1, 1, 1};
	glLightfv(GL_LIGHT1, GL_POSITION, position2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blueColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, blueColor);
	glTranslatef(secLx, secLy, secLz);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.01, 20, 20);
	glTranslatef(-secLx, -secLy, -secLz);
	glEnable(GL_LIGHTING);
}

void display(void){
	keyOperations();
	glClearColor(0.f, 0.f, 0.0f, 1.f);//clear the background window to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -2.0f);
	setCamera();
	setLight();
	lightRot();
	lightRot1();
	
	
	//~ glScalef(scale, scale, scale);
	//~ glRotatef(yRotationAngle, 0, 0, 1);
	//~ glTranslatef(moveX, moveY, 0);
	glCallList(shirt);
	

	
	findCEdges();
	shadowVolume();
	findCEdges1();
	shadowVolume1();
	
	glutSwapBuffers();	
}
void reshape(int width, int height){
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);	 // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 1000.0);       // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes 
	glMatrixMode(GL_MODELVIEW);
	
}
void keyPressed(unsigned char key, int x, int y){
	if(key == '1')
	{
		fst = true;
		snd = false;
	}
	else if(key == '2')
	{
		fst = false;
		snd = true;
		Vector3 pos(posx, posy, posz);
		Vector3 pt(ptx, pty, ptz);
		Vector3 up(ux, uy, uz);
		rght = (pt - pos).cross(up);
	}
	else if (key == 'h')
	 {
		isH = !isH;
	 }
	 
	else
		keyStates[key] = true;
}


void keyUp(unsigned char key, int x, int y){
	
	
	keyStates[key] = false;
}
void keySpecial(int key, int x, int y){
	keySpecialStates[key] = true;	
}
void keySpecialUp(int key, int x, int y){
	keySpecialStates[key] = false;
}

int main(int argc, char **argv){
	Parse(argv[1]);
	
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
		keySpecialStates[i] = false;
	}
	
	
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

	
	glutInitWindowSize(900, 700);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("CENG477_HW2");
	
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
		
		
	
	//~ lx = 0.2; 
	//~ ly = maxY + 0.3;
	//~ lz = 0;
	glEnable(GL_LIGHTING);
	
	
	GLfloat global_ambient[] = {0.4, 0.4 , 0.4, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	
	shirt = glGenLists(1);
	glNewList(shirt, GL_COMPILE);
	glTranslatef(- center._x, -center._y, -center._z);
	TriDrawer();
	glEndList();
	
	glutDisplayFunc (display);
	glutIdleFunc (display);
	glutReshapeFunc (reshape);
	
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(keySpecial);
	glutSpecialUpFunc(keySpecialUp);

	glutMainLoop ();
	
	return 0;
}
