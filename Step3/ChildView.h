// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__50C8628F_112A_40D0_9AB2_53368988C69B__INCLUDED_)
#define AFX_CHILDVIEW_H__50C8628F_112A_40D0_9AB2_53368988C69B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "graphics/OpenGLWnd.h"
#include "graphics/GrTexture.h"	// Added by ClassView
#include "graphics/GrCamera.h"
#include "Torus.h"
#include "Sphere.h"
#include "Organs.h"
#include "mesh.h"
#include "Mesh.h"

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public COpenGLWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnGLDraw(CDC *pDC);
	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnFileSavebmpfile();
	afx_msg void OnStepSpin();
	afx_msg void OnUpdateStepSpin(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStepBox();
	afx_msg void OnUpdateStepBox(CCmdUI* pCmdUI);
	afx_msg void OnStepSphere();
	afx_msg void OnUpdateStepSphere(CCmdUI* pCmdUI);
	afx_msg void OnStepTorus();
	afx_msg void OnUpdateStepTorus(CCmdUI* pCmdUI);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnStepMesh();
    afx_msg void OnUpdateStepMesh(CCmdUI *pCmdUI);
    afx_msg void OnViewWireframe();
    afx_msg void OnUpdateViewWireframe(CCmdUI *pCmdUI);
    afx_msg void OnStepTorus2();
    afx_msg void OnUpdateStepTorus2(CCmdUI *pCmdUI);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawFunky();
    void DrawTori();
    void Box(GLdouble p_x, GLdouble p_y, GLdouble p_z);

    bool m_wireframe;
	CGrTexture m_wood;
	CGrTexture m_worldmap;
	CGrTexture m_marble03;
	CGrTexture m_marble10;
	CGrTexture m_bluegill;

	int m_mode;

	UINT m_spintimer;
	double m_spinangle;

    CGrCamera       m_camera;

	//organs
	COrgans m_organs;

    // The two tori...
    CTorus      m_torus1;
    CTorus      m_torus2;

    // The sphere
    CSphere     m_sphere;
public:
	afx_msg void OnStepOrgan();
	afx_msg void OnUpdateStepOrgan(CCmdUI *pCmdUI);
	afx_msg void OnStepFunky();
private:
	CMesh m_mesh;
	CMesh m_surface;
	CMesh m_fish;
public:
	void CreateMesh(void);
private:
	GLuint shaderTexture[1];
	CGrVector lightAngle;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__50C8628F_112A_40D0_9AB2_53368988C69B__INCLUDED_)
