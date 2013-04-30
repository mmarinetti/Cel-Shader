#include "stdafx.h"
#include "Torus.h"

#include <cmath>
#include <stdio.h>
#include <iostream>
#include "gl/gl.h"

const double GR_PI = 3.1415926535897932384626433832795;

typedef struct tagMATRIX
{
	float Data[16];
}
MATRIX;

typedef struct tagVECTOR
{
	float X, Y, Z;
}
VECTOR;

typedef struct tagVERTEX
{
	VECTOR Nor;
	VECTOR Pos;
}
VERTEX;

typedef struct tagPOLYGON
{
	VERTEX Verts[3];
}
POLYGON;

float outlineColor[3] = {0.0f, 0.0f, 1.0f};
float outlineWidth = 3.0f;
VECTOR lightAngle;
GLuint shaderTexture[1];

inline float DotProduct(VECTOR &v1, VECTOR &v2)
{
	return v1.X*v2.X + v1.Y*v2.Y + v1.Z*v2.Z;
}

inline void Normalize(VECTOR &v)
{
	float m = sqrtf(v.X*v.X + v.Y*v.Y + v.Z*v.Z);

	if(m != 0.0f)
	{
		v.X /= m;
		v.Y /= m;
		v.Z /= m;
	}
}

void RotateVector(MATRIX &m, VECTOR &v, VECTOR &d)
{
	d.X = (m.Data[0]*v.X)+(m.Data[4]*v.Y)+(m.Data[8]*v.Z);
	d.Y = (m.Data[1]*v.X)+(m.Data[5]*v.Y)+(m.Data[9]*v.Z);
	d.Z = (m.Data[2]*v.X)+(m.Data[6]*v.Y)+(m.Data[10]*v.Z);
}


CTorus::CTorus(void)
{
    //
    // Default values
    //

    // Large radius of the torus
    // This is the radius of the entire torus
    m_r1 = 5;

    // Small radius of the torus
    // This is the radius of a cross section of the torus
    m_r2 = 1;

    // Number of steps in the large radius
    m_steps1 = 50;

    // Number of steps in the small radius
    m_steps2 = 20;

    m_texture = NULL;
}


CTorus::~CTorus(void)
{
}


//
// Name :         CChildView::Draw()
// Description :  Render a Torus of large radius m_r1 and small radius m_r2
//                m_steps1 is the number of steps we do for the large
//                radius and m_steps2 is the number of steps for the
//                small radius.  There will be m_steps1 * m_steps2 
//                quadrilaterals in the torus.
//
void CTorus::Draw()
{
	/*if(m_texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, m_texture->TexName());
	}*/

	float TmpShade;
	MATRIX TmpMatrix;
	VECTOR TmpVector, TmpNormal;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);

	glGetFloatv(GL_MODELVIEW_MATRIX, TmpMatrix.Data);

	glEnable(GL_TEXTURE_1D);
	glBindTexture(GL_TEXTURE_1D, shaderTexture[0]);

	glColor3f(1.0f, 1.0f, 1.0f);

    // How large are the angular steps in radians
    const double step1r = 2. * GR_PI / m_steps1;
    const double step2r = 2. * GR_PI / m_steps2;

    // We build the torus in slices that go from a1a to a1b
    double a1a = 0;
    double a1b = step1r;

    for(int s=0;  s<m_steps1;  s++, a1a = a1b, a1b += step1r)
    {
        // We build a slice out of quadrilaterals that range from 
        // angles a2a to a2b.

        double a2a = 0;
        double a2b = step2r;

        for(int s2=0;  s2<m_steps2;  s2++, a2a = a2b,  a2b += step2r)
        {
            // We need to know the corners
            double n[3], v[3];

            glBegin(GL_QUADS);
            TorusVertex(a1a, m_r1, a2a, m_r2, v, n);
			//glTexCoord2f(2*a1a, .395*a2a);
            //glNormal3dv(n);
			TmpNormal.X = n[0];
			TmpNormal.Y = n[1];
			TmpNormal.Z = n[2];

			RotateVector(TmpMatrix, TmpNormal, TmpVector);
			Normalize(TmpVector);
			TmpShade = DotProduct(TmpVector, lightAngle);

			if(TmpShade < 0.0f)
				TmpShade = 0.0f;

			glTexCoord1f(TmpShade);
            glVertex3dv(&v[0]);

            TorusVertex(a1b, m_r1, a2a, m_r2, v, n);
			//glTexCoord2f(2*a1b, .395*a2a);
            //glNormal3dv(n);
			TmpNormal.X = n[0];
			TmpNormal.Y = n[1];
			TmpNormal.Z = n[2];

			RotateVector(TmpMatrix, TmpNormal, TmpVector);
			Normalize(TmpVector);
			TmpShade = DotProduct(TmpVector, lightAngle);

			if(TmpShade < 0.0f)
				TmpShade = 0.0f;

			glTexCoord1f(TmpShade);

            glVertex3dv(&v[0]);

            TorusVertex(a1b, m_r1, a2b, m_r2, v, n);
			//glTexCoord2f(2*a1b, .395*a2b);
            //glNormal3dv(n);
			TmpNormal.X = n[0];
			TmpNormal.Y = n[1];
			TmpNormal.Z = n[2];

			RotateVector(TmpMatrix, TmpNormal, TmpVector);
			Normalize(TmpVector);
			TmpShade = DotProduct(TmpVector, lightAngle);

			if(TmpShade < 0.0f)
				TmpShade = 0.0f;

			glTexCoord1f(TmpShade);

            glVertex3dv(&v[0]);

            TorusVertex(a1a, m_r1, a2b, m_r2, v, n);
			//glTexCoord2f(2*a1a, .395*a2b);
            //glNormal3dv(n);
			TmpNormal.X = n[0];
			TmpNormal.Y = n[1];
			TmpNormal.Z = n[2];

			RotateVector(TmpMatrix, TmpNormal, TmpVector);
			Normalize(TmpVector);
			TmpShade = DotProduct(TmpVector, lightAngle);

			if(TmpShade < 0.0f)
				TmpShade = 0.0f;

			glTexCoord1f(TmpShade);

            glVertex3dv(&v[0]);

            glEnd();
        }
    }

	//glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_1D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_BACK, GL_LINE);
	glLineWidth(outlineWidth);

	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);
	glColor3fv(&outlineColor[0]);

	for(int s=0;  s<m_steps1;  s++, a1a = a1b, a1b += step1r)
    {
        // We build a slice out of quadrilaterals that range from 
        // angles a2a to a2b.

        double a2a = 0;
        double a2b = step2r;

        for(int s2=0;  s2<m_steps2;  s2++, a2a = a2b,  a2b += step2r)
        {
            // We need to know the corners
            double n[3], v[3];

            glBegin(GL_QUADS);
            TorusVertex(a1a, m_r1, a2a, m_r2, v, n);
            glVertex3dv(v);

            TorusVertex(a1b, m_r1, a2a, m_r2, v, n);
            glVertex3dv(v);

            TorusVertex(a1b, m_r1, a2b, m_r2, v, n);
            glVertex3dv(v);

            TorusVertex(a1a, m_r1, a2b, m_r2, v, n);
            glVertex3dv(v);

            glEnd();
        }
    }
	
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);
	glPolygonMode(GL_BACK, GL_FILL);
	glDisable(GL_BLEND);
}



//
// Name :         CTorus::TorusVertex()
// Description :  Compute the x,y,z coordinates and surface normal for a 
//                torus vertex.  
// Parameters :   a1 - The angle relative to the center of the torus
//                r1 - Radius of the entire torus
//                a2 - The angle relative to the center of the torus slice
//                r2 - Radius of the torus ring cross-section
//                v - Returns vertex
//                n - Returns surface normal
//

void CTorus::TorusVertex(double a1, double r1, double a2, double r2, 
                         double *v, double *n)
{
    // Some sines and cosines we'll need.
    double ca1 = cos(a1);
    double sa1 = sin(a1);
    double ca2 = cos(a2);
    double sa2 = sin(a2);

    // What is the center of the slice we are on.
    double centerx = r1 * ca1;
    double centerz = -r1 * sa1;    // Note, y is zero

    // Compute the surface normal
    n[0] = ca2 * ca1;          // x
    n[1] = sa2;                // y
    n[2] = -ca2 * sa1;         // z

    // And the vertex
    v[0] = centerx + r2 * n[0];
    v[1] = r2 * n[1];
    v[2] = centerz + r2 * n[2];
}

void CTorus::ReadFile()
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

	lightAngle.X = 0.0f;
	lightAngle.Y = 0.0f;
	lightAngle.Z = 1.0f;

	Normalize(lightAngle);
}
