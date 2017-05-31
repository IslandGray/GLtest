
// GLtest1View.h : CGLtest1View ��Ľӿ�
//

using namespace std;
#pragma once

#include <vector>
#include <stack>


class CGLtest1View : public CView
{
protected: // �������л�����
	CGLtest1View();
	DECLARE_DYNCREATE(CGLtest1View)

// ����
public:
	CGLtest1Doc* GetDocument() const;
	int m_pointNum;
	int type;
	vector<CPoint> m_point;
	stack<CPoint> sta_point;
	//vector<CPoint*> board_point;
	CRect rect;
	vector<CPoint> line_point;
	int linepoint;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGLtest1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void DrawLineBez(CPoint P1, CPoint P2,CDC* pDC);
	void Fill(CPoint point, CDC *pDC);
	afx_msg void OnFill();
	afx_msg void On32771();
	afx_msg void OnShift();
	afx_msg void OnRotate();
	afx_msg void OnMagnify();
	afx_msg void OnClean();
	afx_msg void OnShrink();
	afx_msg void OnShear();
	afx_msg void OnMirror();
	afx_msg void OnCohenSutherland();
	int Encode(int x, int y);
	void clip(CPoint& P1, CPoint& P2);
};

#ifndef _DEBUG  // GLtest1View.cpp �еĵ��԰汾
inline CGLtest1Doc* CGLtest1View::GetDocument() const
   { return reinterpret_cast<CGLtest1Doc*>(m_pDocument); }
#endif

