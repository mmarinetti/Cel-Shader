// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "lab.h"
#include "ChildView.h"
#include <cmath>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
    m_camera.Set(15, 10, 30, 0, 0, 0, 0, 1, 0);

    m_spinangle = 0.;
    m_spintimer = 0;
    m_wireframe = false;

    m_sphere.SetRadius(5);


    SetDoubleBuffer(true);

    m_wood.LoadFile(L"textures/plank01.bmp");
	m_worldmap.LoadFile(L"textures/worldmap.bmp");
	m_marble03.LoadFile(L"textures/marble03.bmp");
	m_marble10.LoadFile(L"textures/marble10.bmp");
	m_bluegill.LoadFile(L"models/BLUEGILL.bmp");
	m_mode = ID_STEP_TORUS;

	m_sphere.SetTexture(&m_worldmap);
	m_torus1.SetTexture(&m_marble03);
	m_torus2.SetTexture(&m_marble10);
	m_fish.SetTexture(&m_bluegill);

	CreateMesh();
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,COpenGLWnd )
    //{{AFX_MSG_MAP(CChildView)
    ON_COMMAND(ID_FILE_SAVEBMPFILE, OnFileSavebmpfile)
    ON_COMMAND(ID_STEP_SPIN, OnStepSpin)
    ON_UPDATE_COMMAND_UI(ID_STEP_SPIN, OnUpdateStepSpin)
    ON_WM_TIMER()
    ON_COMMAND(ID_STEP_BOX, OnStepBox)
    ON_UPDATE_COMMAND_UI(ID_STEP_BOX, OnUpdateStepBox)
    ON_COMMAND(ID_STEP_SPHERE, OnStepSphere)
    ON_UPDATE_COMMAND_UI(ID_STEP_SPHERE, OnUpdateStepSphere)
    ON_COMMAND(ID_STEP_TORUS, OnStepTorus)
    ON_UPDATE_COMMAND_UI(ID_STEP_TORUS, OnUpdateStepTorus)
    //}}AFX_MSG_MAP
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_STEP_MESH, &CChildView::OnStepMesh)
    ON_UPDATE_COMMAND_UI(ID_STEP_MESH, &CChildView::OnUpdateStepMesh)
    ON_COMMAND(ID_VIEW_WIREFRAME, &CChildView::OnViewWireframe)
    ON_UPDATE_COMMAND_UI(ID_VIEW_WIREFRAME, &CChildView::OnUpdateViewWireframe)
    ON_COMMAND(ID_STEP_TORUS2, &CChildView::OnStepTorus2)
    ON_UPDATE_COMMAND_UI(ID_STEP_TORUS2, &CChildView::OnUpdateStepTorus2)
    ON_WM_RBUTTONDOWN()
    ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_STEP_ORGAN, &CChildView::OnStepOrgan)
	ON_UPDATE_COMMAND_UI(ID_STEP_ORGAN, &CChildView::OnUpdateStepOrgan)
	ON_COMMAND(ID_STEP_FUNKY, &CChildView::OnStepFunky)
	ON_COMMAND(ID_STEP_FUNKY, &CChildView::OnStepFunky)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
    if (!COpenGLWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
        ::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

    return TRUE;
}




void CChildView::OnGLDraw(CDC *pDC)
{
    /*GLfloat gray = 0.3f;
    glClearColor(gray, gray, gray, 0.0f) ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat reset[] = {.7f, .7f, .7f, .7f};
	GLfloat msugreen[] = {0.f, .47f, .2f, 1.f};*/

    //
    // Set up the camera
    //

    int wid, hit;
    GetSize(wid, hit);
    m_camera.Apply(wid, hit);

    //
    // Some standard parameters
    //

    // Enable depth test
    /*glEnable(GL_DEPTH_TEST);

    // Cull backfacing polygons
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	GLfloat lightpos[] = {0.5, 2.0, 1., 0.};
	GLfloat color0[] = {.7f, .7f, .7f, .7f};
	GLfloat lightpos1[] = {-1., 5., 1., 1.0};
	GLfloat blue[] = {0.3f, .3f, .7f, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, color0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue);
	glLightfv(GL_LIGHT1, GL_SPECULAR, blue);*/

    // Enable or disable the wireframe mode
	glPolygonMode(GL_FRONT, m_wireframe ? GL_LINE : GL_FILL);


    glPushMatrix();
    glRotated(m_spinangle, 1, .5, .7);

    //
    // shapes
    //

    switch(m_mode)
    {
    case ID_STEP_MESH:
        glPushMatrix();
		glRotated(m_spinangle / 3, 0, 1, 0);

		/*glPushMatrix();
		glTranslated(1, 0, 4);
		glRotated(-30, 1, 0, 0);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, msugreen);
		m_mesh.Draw();
		glPopMatrix();

	    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
		m_surface.Draw();
	    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, reset);*/
		
		glPushMatrix();
		glTranslated(0, -1, 0);
		glRotated(-90, 1., 0, 0);
		m_fish.ReadFile();
		m_fish.Draw();
		glPopMatrix();

		glPopMatrix();
        break;

	case ID_STEP_TORUS:
		m_torus1.ReadFile();
		m_torus1.Draw();
		break;

	default:
		break;
    }

    glPopMatrix();

}

double Normal3dv(double *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void CChildView::OnFileSavebmpfile() 
{
    OnSaveImage();	
}



//
//        Name : CChildView::Box()
// Description : Draw an arbitrary size box. p_x, p_y, and 
//               p_z are the height of the box. We'll use this is a 
//               common primitive.
//      Origin : The back corner is at 0, 0, 0, and the box 
//               is entirely in the positive octant.
//

void CChildView::Box(GLdouble p_x, GLdouble p_y, GLdouble p_z)
{
    GLdouble a[] = {0., 0., p_z};
    GLdouble b[] = {p_x, 0., p_z};
    GLdouble c[] = {p_x, p_y, p_z};
    GLdouble d[] = {0., p_y, p_z};
    GLdouble e[] = {0., 0., 0.};
    GLdouble f[] = {p_x, 0., 0.};
    GLdouble g[] = {p_x, p_y, 0.};
    GLdouble h[] = {0., p_y, 0.};

	GLfloat msugreen[] = {0.f, .47f, .2f, 1.f};
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, msugreen);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, m_wood.TexName());

    // Front
    glBegin(GL_QUADS);
	    glNormal3d(0, 0, 1);
		glTexCoord2f(0, 0);
        glVertex3dv(a);
		glTexCoord2f(1, 0);
        glVertex3dv(b);
		glTexCoord2f(1, 1);
        glVertex3dv(c);
		glTexCoord2f(0, 1);
        glVertex3dv(d);
    glEnd();

	glBindTexture(GL_TEXTURE_2D, m_worldmap.TexName());

    // Right
    glBegin(GL_QUADS);
	    glNormal3d(1, 0, 0);
		glTexCoord2f(0, 1);
        glVertex3dv(c);
		glTexCoord2f(0, 0);
        glVertex3dv(b);
		glTexCoord2f(1, 0);
        glVertex3dv(f);
		glTexCoord2f(1, 1);
        glVertex3dv(g);
    glEnd();

	glDisable(GL_TEXTURE_2D);

    // Back
    glBegin(GL_QUADS);
	    glNormal3d(0, 0, -1);
        glVertex3dv(h);
        glVertex3dv(g);
        glVertex3dv(f);
        glVertex3dv(e);
    glEnd();

    // Left
    glBegin(GL_QUADS);
	    glNormal3d(-1, 0, 0);
        glVertex3dv(d);
        glVertex3dv(h);
        glVertex3dv(e);
        glVertex3dv(a);
    glEnd();

    // Top
    glBegin(GL_QUADS);
	    glNormal3d(0, 1, 0);
        glVertex3dv(d);
        glVertex3dv(c);
        glVertex3dv(g);
        glVertex3dv(h);
    glEnd();

    // Bottom
    glBegin(GL_QUADS);
	    glNormal3d(0, -1, 0);
        glVertex3dv(e);
        glVertex3dv(f);
        glVertex3dv(b);
        glVertex3dv(a);
    glEnd();

}




//
// Name :         CChildView::DrawTori()
// Description :  Draw two tori linked together.
//
void CChildView::DrawTori()
{
    glPushMatrix();

    // This rotation spins the tori
    glRotated(m_spinangle / 3, 0, 1, 0);

    // The flips them down 45 degress so they look nicer.
    glRotated(45., 1, 0, 0);

    // First torus is left 2.5 cm
    glPushMatrix();
    glTranslated(-2.5, 0, 0);

    m_torus1.Draw();

    glPopMatrix();

    // Second torus is right 2.5 cm and rotated
    // around the X axis to right angles with the first
    // torus.
    glPushMatrix();

    glTranslated(2.5, 0, 0);
    glRotated(90., 1, 0, 0);

    m_torus2.Draw();

    glPopMatrix();

    glPopMatrix();
}





void CChildView::OnStepSpin() 
{
    if(m_spintimer)
    {
        KillTimer(m_spintimer);
        m_spintimer = 0;
    }
    else
    {
        m_spintimer = SetTimer(1, 30, NULL);
    }
}

void CChildView::OnUpdateStepSpin(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_spintimer != 0);	
}

void CChildView::OnTimer(UINT nIDEvent) 
{
    m_spinangle += 1;
    Invalidate();

    COpenGLWnd ::OnTimer(nIDEvent);
}

void CChildView::OnStepBox() 
{
    m_mode = ID_STEP_BOX;
    Invalidate();
}

void CChildView::OnUpdateStepBox(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_mode == ID_STEP_BOX);
}

void CChildView::OnStepSphere() 
{
    m_mode = ID_STEP_SPHERE;
    Invalidate();
}

void CChildView::OnUpdateStepSphere(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_mode == ID_STEP_SPHERE);
}


void CChildView::OnStepTorus() 
{
    m_mode = ID_STEP_TORUS;
    Invalidate();
}

void CChildView::OnUpdateStepTorus(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_mode == ID_STEP_TORUS);
}

void CChildView::OnStepTorus2()
{
    m_mode = ID_STEP_TORUS2;
    Invalidate();
}

void CChildView::OnUpdateStepTorus2(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_mode == ID_STEP_TORUS2);
}




void CChildView::OnStepMesh()
{
    m_mode = ID_STEP_MESH;
    Invalidate();
}

void CChildView::OnUpdateStepMesh(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_mode == ID_STEP_MESH);
}

void CChildView::OnViewWireframe()
{
    m_wireframe = !m_wireframe;
    Invalidate();
}

void CChildView::OnUpdateViewWireframe(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_wireframe);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_camera.MouseDown(point.x, point.y);

    COpenGLWnd ::OnLButtonDown(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    if(m_camera.MouseMove(point.x, point.y, nFlags))
        Invalidate();

    COpenGLWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
    m_camera.MouseDown(point.x, point.y, 2);

    COpenGLWnd::OnRButtonDown(nFlags, point);
}


BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    m_camera.MouseWheel(zDelta);
    Invalidate();

    return COpenGLWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void CChildView::OnStepOrgan()
{
	// TODO: Add your command handler code here
	m_mode = ID_STEP_ORGAN;
    Invalidate();
}


void CChildView::OnUpdateStepOrgan(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(m_mode == ID_STEP_ORGAN);
}


//
//        Name : CChildView::DrawFunky()
// Description : Draw a funky object.
//

void CChildView::DrawFunky(void)
{
    GLdouble a[] = {5, 5.5, 2};
    GLdouble b[] = {-3.7, 2, -3.3};
    GLdouble c[] = {3.5, -2.3, 1.1};
    GLdouble d[] = {0, 4, -5};

    // I put this in to get it to draw anything.  
    // You'll delete this when you put in the real 
    // normals.
    //glNormal3d(1, 0, 0);

    // Front
    glBegin(GL_POLYGON);
	    glNormal3d(-0.521, 0.002, 0.854);
        glVertex3dv(a);
        glVertex3dv(b);
        glVertex3dv(c);
    glEnd();

    // Sides
    glBegin(GL_POLYGON);
	    glNormal3d(0.431, -0.895, -0.116);
        glVertex3dv(a);
        glVertex3dv(d);
        glVertex3dv(b);
    glEnd();

    glBegin(GL_POLYGON);
	    glNormal3d(-0.0358, 0.685, 0.728);
        glVertex3dv(b);
        glVertex3dv(d);
        glVertex3dv(c);
    glEnd();

    glBegin(GL_POLYGON);
	    glNormal3d(-0.82, 0.092, 0.566);
        glVertex3dv(c);
        glVertex3dv(d);
        glVertex3dv(a);
    glEnd();

}


void CChildView::OnStepFunky()
{
	// TODO: Add your command handler code here
	m_mode = ID_STEP_FUNKY;
    Invalidate();
}


void CChildView::CreateMesh(void)
{
	/*double v[8][4] = {{0,0,2,1}, {2,0,2,1}, {2,2,2,1}, {0,2,2,1},
	{0,0,0,1}, {2,0,0,1}, {2,2,0,1}, {0,2,0,1}};
	double n[6][4] = {{0,0,1,0}, {1,0,0,0}, {0,0-1,0},
	{-1,0,0,0}, {0,1,0,0}, {0,-1,0,0}};

	for(int i=0; i<8; i++)
		m_mesh.AddVertex(v[i]);

	for(int i=0; i<6; i++)
		m_mesh.AddNormal(n[i]);

	m_mesh.AddFlatQuad(0, 1, 2, 3, 0);
	m_mesh.AddFlatQuad(1, 5, 6, 2, 1);
	m_mesh.AddFlatQuad(5, 4, 7, 6, 2);
	m_mesh.AddFlatQuad(4, 0, 3, 7, 3);
	m_mesh.AddFlatQuad(3, 2, 6, 7, 4);
	m_mesh.AddFlatQuad(0, 4, 5, 1, 5);*/

	//
	// Create a surface
	//

	/*double wid = 20;   // 20 units wide
	double dep = 20;   // 20 units deep
	int nW = 15;       // Number of quads across
	int nD = 15;       // Number of quads deep
	const double PI = 3.141592653;

	// Create the vertices and temporary normals
	// Note that the surface is nW+1 by nD+1 vertices
	for(int j=0; j<=nD; j++)
	{
		for(int i=0; i<=nW; i++)
		{
			double x = double(i)/double(nW) * wid - wid/2;
			double z = double(j)/double(nD) * dep - dep/2;
			double y = sin(double(i)/double(nW) * 4 * PI) +
				sin(double(j)/double(nD) * 3 * PI);

			m_surface.AddVertex(CGrVector(x, y, z, 1));
			m_surface.AddNormal(CGrVector(0, 1, 0, 0));
		}
	}

	// Create the quadrilaterals
	for(int j=0; j<nD; j++)
	{
		for(int i=0; i<nW; i++)
		{
			int a = j * (nW + 1) + i;
			int b = a + nW + 1;
			int c = b + 1;
			int d = a + 1;

			m_surface.AddQuad(a, b, c, d);
		}
	}

	m_surface.ComputeSmoothNormals();
	*/

	//m_fish.SetLightAngle(lightAngle);
	m_fish.LoadOBJ("models\\fish4.obj");
}
