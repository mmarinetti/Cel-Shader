#include "StdAfx.h"
#include "Organs.h"

#include "gl/gl.h"

COrgans::COrgans(void)
{
}


COrgans::~COrgans(void)
{
}


void COrgans::Draw()
{
	GLfloat black[] = {0, 0, 0, 1};
	GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat liverred[] = {0.788f, .223f, .223f, 1.f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, liverred);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	DrawLiver();

	glMaterialfv(GL_FRONT, GL_SPECULAR, black);

	GLfloat lungsdif[] = {0.54f, 0.54f, 0.54f, 1.f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lungsdif);

    DrawLungs();

	GLfloat windpipedif[] = {.12f, .43f, .64f, 1.f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, windpipedif);

    DrawWindpipe();

	GLfloat heartdif[] = {.64f, .43f, .12f, 1.f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, heartdif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

    DrawHeart();

	glMaterialfv(GL_FRONT, GL_SPECULAR, black);

	GLfloat stomachdif[] = {.43f, .64f, .12f, 1.f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, stomachdif);

    DrawStomach();

	GLfloat reset[] = {.7f, .7f, .7f, .7f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, reset);

}

