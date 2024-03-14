// RenderDoc.h : interface of the CRenderDoc class
//


#include "scene/SceneRender.h"

#pragma once

class CRenderDoc : public CDocument
{
protected: // create from serialization only
	CRenderDoc();
	DECLARE_DYNCREATE(CRenderDoc)
private:
	SceneRender sr;
// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	void		 Draw( CDC* pDC, WORD w, WORD h );
	void		Tick( UINT nPeriod );

// Implementation
public:
	virtual ~CRenderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


