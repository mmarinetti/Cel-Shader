#include "stdafx.h"
#include <fstream>   // For input streams from files
#include <string>    // For the string type
#include <sstream>   // For streams from strings
#include "Mesh.h"
#include <stdio.h>

using namespace std;

//float outlineColor[3] = {0.0f, 0.0f, 0.0f};
//float outlineWidth = 3.0f;

CGrVector lightAngle;

//GLuint shaderTexture[1];

CMesh::CMesh(void)
{
	m_texture = NULL;
	red = 1.0f;
	green = 1.0f;
	blue = 1.0f;
}


CMesh::~CMesh(void)
{
}

void CMesh::RotateVector(MATRIX &M, CGrVector &v, CGrVector &d)
{
	d.X() = (M.Data[0]*v.X())+(M.Data[4]*v.Y())+(M.Data[8]*v.Z());
    d.Y() = (M.Data[1]*v.X())+(M.Data[5]*v.Y())+(M.Data[9]*v.Z());
	d.Z() = (M.Data[2]*v.X())+(M.Data[6]*v.Y())+(M.Data[10]*v.Z());
}

inline float DotProduct(CGrVector &v1, CGrVector &v2)
{
	return v1.X()*v2.X() + v1.Y()*v2.Y() + v1.Z()*v2.Z();
}

inline void Normalize_v(CGrVector &v)
{
	float m = sqrtf(v.X() * v.X()
		           +v.Y() * v.Y()
			       +v.Z() * v.Z());

	if(m != 0.0f)
	{
		v.X() /= m;
		v.Y() /= m;
		v.Z() /= m;
	}
}

void CMesh::Draw(void)
{
	/*if(m_texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, m_texture->TexName());
	}*/

	float TmpShade;
	MATRIX TmpMatrix;
	CGrVector TmpVector, TmpNormal;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	glDisable(GL_LINE_SMOOTH);

	glGetFloatv(GL_MODELVIEW_MATRIX, TmpMatrix.Data);

	glEnable(GL_TEXTURE_1D);
	glBindTexture(GL_TEXTURE_1D, shaderTexture[0]);

	glColor3f(red, green, blue);

	glBegin(GL_TRIANGLES);
	for(PTV v=m_triangles.begin(); v!=m_triangles.end(); v++)
	//for(unsigned v=0; v<m_vertices.size(); v++)
	{
		//if(m_texture != NULL)
		   // glTexCoord2f(m_tvertices[v->t][0], m_tvertices[v->t][1]);
		//glNormal3dv(m_normals[v->n]);

		TmpNormal = m_normals[v->n];
		RotateVector(TmpMatrix, TmpNormal, TmpVector);

		Normalize_v(TmpVector);

		TmpShade = DotProduct(TmpVector, lightAngle);

		if(TmpShade < 0.0f)
			TmpShade = 0.0f;

		glTexCoord1f(TmpShade);
		glVertex3dv(&m_vertices[v->v].X());
	}
	glEnd();

	glDisable(GL_TEXTURE_1D);

	//Outline code
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_BACK, GL_LINE);
	glLineWidth(3.0f);

	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);
	float outlineColor[3] = {0.0f, 0.0f, 1.0f};
	glColor3fv(&outlineColor[0]);

	glBegin(GL_TRIANGLES);
	for(PTV v=m_triangles.begin(); v!=m_triangles.end(); v++)
	{
		glVertex3dv(m_vertices[v->v]);
	}
	glEnd();

	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);
	glPolygonMode(GL_BACK, GL_FILL);
	glDisable(GL_BLEND);
}


void CMesh::AddTriangleVertex(int v, int n, int t)
{
	TV tv;
	tv.v = v;
	tv.n = n;
	tv.t = t;
	m_triangles.push_back(tv);
}


//
// Name:        CMesh::AddFlatQuad()
// Description: Add a quadrangle to the triangle mesh
//
void CMesh::AddFlatQuad(int a, int b, int c, int d, int n)
{
	// First triangle
	AddTriangleVertex(a, n, -1);
	AddTriangleVertex(b, n, -1);
	AddTriangleVertex(c, n, -1);

	// Second Triangle
	AddTriangleVertex(a, n, -1);
	AddTriangleVertex(c, n, -1);
	AddTriangleVertex(d, n, -1);
}


//
// Name:        CMesh::AddQuad()
// Description: Add a quadrangle to the triangle mesh with no
//              assumption of flatness
//
void CMesh::AddQuad(int a, int b, int c, int d)
{
	// First triangle
	AddTriangleVertex(a, a, -1);
	AddTriangleVertex(b, b, -1);
	AddTriangleVertex(c, c, -1);

	// Second triangle
	AddTriangleVertex(a, a, -1);
	AddTriangleVertex(c, c, -1);
	AddTriangleVertex(d, d, -1);
}


//
// Name:        CMesh::ComputeSmoothNormals()
// Description: Compute a normal for each vertex that is the
//              average of the surface normals incident on the
//              vertex.
//
void CMesh::ComputeSmoothNormals(void)
{
    m_normals.resize(m_vertices.size());
    for(unsigned int i=0;  i<m_vertices.size();  i++)
        m_normals[i] = CGrVector(0, 0, 0, 0);

    for(PTV v=m_triangles.begin();  v!=m_triangles.end();  )
    {
        // Collect up the vertices of a triangle...
        int a = v->v;
        v++;
        int b = v->v;
        v++;
        int c = v->v;
        v++;

        // Surface normal
        CGrVector normal = Cross(m_vertices[b] - m_vertices[a], 
                                 m_vertices[c] - m_vertices[a]);
        normal.Normalize3();

        // Add to the incident vertices normals
        m_normals[a] += normal;
        m_normals[b] += normal;
        m_normals[c] += normal;
	}

	// Normalize the normals
    for(unsigned int i=0;  i<m_vertices.size();  i++)
        m_normals[i].Normalize3();
}


void CMesh::LoadOBJ(const char * filename)
{
	ifstream str(filename);
	if(!str)
	{
		AfxMessageBox(L"File not found");
		return;
	}

	string line;
	while(getline(str, line))
	{
		istringstream Istr(line);

		string code;
		Istr >> code;
		if(code == "v")
		{
			double x, y, z;
			Istr >> x >> y >> z;
			AddVertex(CGrVector(x, y, z, 1));
		}
		else if(code == "vn")
		{
			double x, y, z;
			Istr >> x >> y >> z;
			AddNormal(CGrVector(x, y, z, 1));
		}
		else if(code == "vt")
		{
			double s, t;
			Istr >> s >> t;
			AddTexCoord(CGrVector(s, t, 0, 1));
		}
		else if(code == "f")
		{
			for(int i=0; i<3; i++)
			{
				char slash;
				int v, t, n;
				Istr >> v >> slash >> t >> slash >> n;
				AddTriangleVertex(v-1, n-1, t-1);
			}
		}
	}
}

void CMesh::ReadFile()
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0.7f, 0.7f, 0.7f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glShadeModel(GL_SMOOTH);
	glDisable(GL_LINE_SMOOTH);

	glEnable(GL_CULL_FACE);

	glDisable(GL_LIGHTING);

	char Line[255];
	float shaderData[32][3];
	FILE *in = fopen("graphics\\shader.txt", "r");

	if(in)
	{
		for(unsigned i=0; i<32; i++)
		{
			if(feof(in))
				break;

			fgets(Line, 255, in);

			shaderData[i][0] = shaderData[i][1] = shaderData[i][2] = float(atof(Line));
		}

		fclose(in);
	}

	glGenTextures(1, &shaderTexture[0]);

	glBindTexture(GL_TEXTURE_1D, shaderTexture[0]);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 32, 0, GL_RGB, GL_FLOAT, shaderData);

	lightAngle.X() = 0.0f;
	lightAngle.Y() = 0.0f;
	lightAngle.Z() = 1.0f;

	Normalize(lightAngle);
}
