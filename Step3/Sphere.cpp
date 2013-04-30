#include "StdAfx.h"
#include "Sphere.h"
#include <cmath>

const double GR_PI = 3.1415926535897932384626433832795;

inline void Normalize3(GLdouble *v)
{
   GLdouble len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
   v[0] /= len;
   v[1] /= len;
   v[2] /= len;
}


CSphere::CSphere(void)
{
    m_radius = 5;
	m_texture = NULL;
}


CSphere::~CSphere(void)
{
}


void CSphere::Draw()
{
	if(m_texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, m_texture->TexName());

	}

	GLdouble a[] = {1, 0, 0};
	GLdouble b[] = {0, 0, -1};
	GLdouble c[] = {-1, 0, 0};
	GLdouble d[] = {0, 0, 1};
	GLdouble e[] = {0, 1, 0};
	GLdouble f[] = {0, -1, 0};

	int recurse = 7;

	// Temporary...
	glNormal3d(0, 0, 1);

	SphereFace(recurse, m_radius, d, a, e);
	SphereFace(recurse, m_radius, a, b, e);
	SphereFace(recurse, m_radius, b, c, e);
	SphereFace(recurse, m_radius, c, d, e);
	SphereFace(recurse, m_radius, a, d, f);
	SphereFace(recurse, m_radius, b, a, f);
	SphereFace(recurse, m_radius, c, b, f);
	SphereFace(recurse, m_radius, d, c, f);

	glDisable(GL_TEXTURE_2D);
}



void CSphere::SphereFace(int p_recurse, double p_radius, double *a,
                            double *b, double *c)
{
	if(p_recurse > 1)
	{
		// Compute vectors halfway between the passed vectors
		GLdouble d[3] = {a[0] + b[0], a[1] + b[1], a[2] + b[2]};
		GLdouble e[3] = {b[0] + c[0], b[1] + c[1], b[2] + c[2]};
		GLdouble f[3] = {c[0] + a[0], c[1] + a[1], c[2] + a[2]};

		Normalize3(d);
		Normalize3(e);
		Normalize3(f);

		SphereFace(p_recurse-1, p_radius, a, d, f);
		SphereFace(p_recurse-1, p_radius, d, b, e);
		SphereFace(p_recurse-1, p_radius, f, e, c);
		SphereFace(p_recurse-1, p_radius, f, d, e);
	}
	else
	{
	    glBegin(GL_TRIANGLES);
		  // What's the texture coordinate for this normal?
		  double tx1 = atan2(a[0], a[2]) / (2. * GR_PI) + 0.5;
		  double ty1 = asin(a[1]) / GR_PI + 0.5;
		  glTexCoord2f(tx1, ty1);
	      glNormal3dv(a);
	      glVertex3d(a[0]*p_radius, a[1]*p_radius, a[2]*p_radius);

		  double tx2 = atan2(b[0], b[2]) / (2. * GR_PI) + 0.5;
		  double ty2 = asin(b[1]) / GR_PI + 0.5;

		  // Test for this coordinate on the other side of the
		  // texture from the first coordinate.
		  if(tx2 < 0.75 && tx1 > 0.75)
			  tx2 += 1.0;
		  else if(tx2 > 0.75 && tx1 < 0.75)
			  tx2 -= 1.0;

		  glTexCoord2f(tx2, ty2);
	      glNormal3dv(b);
	      glVertex3d(b[0]*p_radius, b[1]*p_radius, b[2]*p_radius);

		  double tx3 = atan2(c[0], c[2]) / (2. * GR_PI) + 0.5;
		  double ty3 = asin(c[1]) / GR_PI + 0.5;

		  if(tx3 < 0.75 && tx1 > 0.75)
			  tx3 += 1.0;
		  else if(tx3 > 0.75 && tx1 < 0.75)
			  tx3 -= 1.0;

		  glTexCoord2f(tx3, ty3);
	      glNormal3dv(c);
	      glVertex3d(c[0]*p_radius, c[1]*p_radius, c[2]*p_radius);
	    glEnd();
	}
}