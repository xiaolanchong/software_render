// RenderDoc.cpp : implementation of the CRenderDoc class
//

#include "stdafx.h"
#include "Render.h"

#include "RenderDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CRenderDoc

IMPLEMENT_DYNCREATE(CRenderDoc, CDocument)

BEGIN_MESSAGE_MAP(CRenderDoc, CDocument)
END_MESSAGE_MAP()


// CRenderDoc construction/destruction

CRenderDoc::CRenderDoc()
{
	// TODO: add one-time construction code here

}

CRenderDoc::~CRenderDoc()
{
}

BOOL CRenderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CRenderDoc serialization

void CRenderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CRenderDoc diagnostics

#ifdef _DEBUG
void CRenderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRenderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRenderDoc commands

static float s_fTime = 0.0f;

void	CRenderDoc::Draw( CDC* pDC, WORD w, WORD h )
{
	sr.Render( pDC, w, h/*, s_fAngle*/ );
}

void	CRenderDoc::Tick( UINT /*nPeriod*/ )
{
	sr.Tick( s_fTime );
	s_fTime += 0.1f;
	UpdateAllViews(0);
}
