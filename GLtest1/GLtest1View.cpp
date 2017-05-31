
// GLtest1View.cpp : CGLtest1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GLtest1.h"
#endif

#include "GLtest1Doc.h"
#include "GLtest1View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.1415926535897932384626
#define LEFT 100
#define RIGHT 300
#define TOP 150
#define BOTTOM 310


// CGLtest1View

IMPLEMENT_DYNCREATE(CGLtest1View, CView)

BEGIN_MESSAGE_MAP(CGLtest1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_32772, &CGLtest1View::OnFill)
	ON_COMMAND(ID_32771, &CGLtest1View::On32771)
	ON_COMMAND(ID_32773, &CGLtest1View::OnShift)
	ON_COMMAND(ID_32774, &CGLtest1View::OnRotate)
	ON_COMMAND(ID_32775, &CGLtest1View::OnMagnify)
	ON_COMMAND(ID_32777, &CGLtest1View::OnClean)
	ON_COMMAND(ID_32776, &CGLtest1View::OnShrink)
	ON_COMMAND(ID_32778, &CGLtest1View::OnShear)
	ON_COMMAND(ID_32779, &CGLtest1View::OnMirror)
	ON_COMMAND(ID_32780, &CGLtest1View::OnCohenSutherland)
END_MESSAGE_MAP()

// CGLtest1View 构造/析构

CGLtest1View::CGLtest1View()
{
	// TODO: 在此处添加构造代码
	m_pointNum = 0;
	m_point.clear();
	type = 1;
	rect = CRect(LEFT, TOP, RIGHT, BOTTOM);
	line_point.clear();
	linepoint = 0;
}

CGLtest1View::~CGLtest1View()
{
}

BOOL CGLtest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGLtest1View 绘制

void CGLtest1View::OnDraw(CDC* /*pDC*/)
{
	CGLtest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGLtest1View 打印

BOOL CGLtest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGLtest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGLtest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGLtest1View 诊断

#ifdef _DEBUG
void CGLtest1View::AssertValid() const
{
	CView::AssertValid();
}

void CGLtest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLtest1Doc* CGLtest1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLtest1Doc)));
	return (CGLtest1Doc*)m_pDocument;
}
#endif //_DEBUG


// CGLtest1View 消息处理程序


void CGLtest1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (type == 1) {
		m_point.push_back(point);
		m_pointNum++;
		CView::OnLButtonDown(nFlags, point);
	}
	else if (type == 2) {
		CDC *pDC = GetWindowDC();
		Fill(point, pDC);
		CView::OnLButtonDown(nFlags, point);
	}
	else if (type == 3) {
		CDC *pDC = GetWindowDC();
		line_point.push_back(point);
		linepoint++;
		if (linepoint == 2) {
			pDC->MoveTo(line_point[0]);
			//DrawLineBez(line_point[0], line_point[1], pDC);
			pDC->LineTo(line_point[1]);
		}
		
		CView::OnLButtonDown(nFlags, point);
	}
	//CView::OnLButtonDown(nFlags, point);
}


void CGLtest1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetWindowDC();
	if (type != 3) {
		int i;
		for (i = 0; i < m_pointNum; i++) {
			pDC->MoveTo(m_point[i]);
			if (i < m_pointNum - 1) {
				//pDC->LineTo(m_point[i+1]);
				DrawLineBez(m_point[i], m_point[i + 1], pDC);
			}
			else {
				//pDC->LineTo(m_point[0]);
				DrawLineBez(m_point[i], m_point[0], pDC);
			}
		}
		CView::OnRButtonDown(nFlags, point);
	}
	else {
		clip(line_point[0], line_point[1]);
		DrawLineBez(line_point[0], line_point[1], pDC);
		CView::OnRButtonDown(nFlags, point);
	}
}


void CGLtest1View::DrawLineBez(CPoint P1, CPoint P2,CDC *pDC)
{
	int s1, s2, changeXY;
	int X = P1.x;
	int Y = P1.y;
	int deltax, deltay, e;
	deltax = abs(P2.x - P1.x);
	deltay = abs(P2.y - P1.y);
	if (P2.x - P1.x >= 0) s1 = 1; else s1 = -1;
	if (P2.y - P1.y >= 0) s2 = 1; else s2 = -1;
	e = 2 * deltay - deltax;
	if (deltay>deltax)
	{
		int Temp = deltax;
		deltax = deltay;
		deltay = Temp;
		changeXY = 1;
	}
	else changeXY = 0;
	for (int i = 1; i <= deltax + deltay; i++)
	{
		if (e >= 0)
		{
			if (changeXY == 1) X += s1;
			else Y += s2;
			pDC->SetPixel(X, Y, RGB(255, 0, 255));
			/*
			CPoint* newpoint = new CPoint;
			newpoint->x = X;
			newpoint->y = Y;
			board_point.push_back(newpoint);
			*/
			Sleep(1);
			e = e - 2 * deltax;
		}
		else
		{
			if (changeXY == 1) Y += s2;
			else X += s1;
			pDC->SetPixel(X, Y, RGB(255, 0, 255));
			/*
			CPoint* newpoint = new CPoint;
			newpoint->x = X;
			newpoint->y = Y;
			board_point.push_back(newpoint);
			*/
			Sleep(1);
			e = e + 2 * deltay;
		}
	}
}


void CGLtest1View::Fill(CPoint point,CDC *pDC)
{
	COLORREF fill = RGB(0, 255, 0);
	COLORREF boundary = RGB(255, 0, 255);
	CPoint seed, newseed;
	int xleft, xright, x, y;  //[xLeft, xRight]表示扫描线的区段，x，y表示当前的像素点左边
	bool needfill = false;
	bool stop = true;
	seed.x = point.x;
	seed.y = point.y;
	sta_point.push(seed);
	while (!sta_point.empty()) {
		//* 种子出栈并给点上色
		seed = sta_point.top();
		sta_point.pop();
		pDC->SetPixel(seed.x, seed.y, fill);
		//* 填充当前扫描线位于种子左边的部分
		x = seed.x - 1;
		y = seed.y;
		while (pDC->GetPixel(x, y) != fill &&pDC->GetPixel(x, y) != boundary) {
			pDC->SetPixel(x, y, fill);
			x -= 1;
		}
		xleft = x + 1;  // 记录最左侧的内点

						//* 填充当前扫描线位于种子右边的部分
		x = seed.x + 1;
		y = seed.y;
		while (pDC->GetPixel(x, y) != fill &&pDC->GetPixel(x, y) != boundary) {
			pDC->SetPixel(x, y, fill);
			x += 1;
		}
		xright = x - 1;  // 记录最右侧的内点

						 //*下移一条扫描线
		y = seed.y - 1;
		x = xleft;
		//* 从左向右检测非边界、未填充的象素
		while (x < xright) {
			while (pDC->GetPixel(x, y) != fill &&pDC->GetPixel(x, y) != boundary) {
				//* 存在未填充的像素，则需要填充
				needfill = true;
				x += 1;
			}
			//* 最右侧像素入栈
			if (needfill) {
				newseed.x = x - 1;
				newseed.y = y;
				sta_point.push(newseed);
				needfill = false;
				
				if (stop == true) {
					x += 2;
					while (pDC->GetPixel(x, y) != fill && pDC->GetPixel(x, y) != boundary && x <= 1000) {
						x++;
					}
					if (pDC->GetPixel(x, y) == boundary) {
						newseed.x = x - 5;
						newseed.y = y;
						sta_point.push(newseed);
						stop = false;
					}
				}

				break;
			}
			x++;
		}

		// 上移一条扫描线
		needfill = false;
		y = seed.y + 1;
		x = xleft;
		//* 从左向右检测非边界、未填充的象素
		while (x < xright) {
			while (pDC->GetPixel(x, y) != fill &&pDC->GetPixel(x, y) != boundary) {
				needfill = true;
				x += 1;
			}
			//* 最右侧像素入栈
			if (needfill) {
				newseed.x = x - 1;
				newseed.y = y;
				sta_point.push(newseed);
				needfill = false;

				if (stop == true) {
					x += 2;
					while (pDC->GetPixel(x, y) != fill && pDC->GetPixel(x, y) != boundary && x <= 1000) {
						x++;
					}
					if (pDC->GetPixel(x, y) == boundary) {
						newseed.x = x - 5;
						newseed.y = y;
						sta_point.push(newseed);
						stop = false;
					}
				}

				break;
			}
			x++;
		}
	}
}


void CGLtest1View::OnFill()
{
	// TODO: 在此添加命令处理程序代码
	type = 2;
}


void CGLtest1View::On32771()
{
	// TODO: 在此添加命令处理程序代码
	type = 1;
}


void CGLtest1View::OnShift()
{
	int i = 255 - m_point[0].x;
	int j = 255 - m_point[0].y;
	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++) {
		if (k == 0) {
			pDC->MoveTo(m_point[k].x + i, m_point[k].y + j);
		}
		else if (k <= m_pointNum - 1) {
			pDC->LineTo(m_point[k].x + i, m_point[k].y + j);
		}
		else {
			pDC->LineTo(m_point[0].x + i, m_point[0].y + j);
		}
	}
}


void CGLtest1View::OnRotate()
{
	int i = 0 - m_point[0].x;
	int j = 0 - m_point[0].y;

	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++) {
		int x, y;
		int changed_x, changed_y;
		if (k == 0) {
			x = m_point[k].x + i;
			y = m_point[k].y + j;
			changed_x = x*cos(PI / 2) - y*sin(PI / 2) - i;
			changed_y = x*sin(PI / 2) + y*cos(PI / 2) - j;
			pDC->MoveTo(changed_x, changed_y);
		}
		else if (k <= m_pointNum - 1) {
			x = m_point[k].x + i;
			y = m_point[k].y + j;
			changed_x = x*cos(PI / 2) - y*sin(PI / 2) - i;
			changed_y = x*sin(PI / 2) + y*cos(PI / 2) - j;
			pDC->LineTo(changed_x, changed_y);
		}
		else {
			pDC->LineTo(m_point[0].x, m_point[0].y);
		}
	}
}


void CGLtest1View::OnMagnify()
{
	int i = 0 - m_point[0].x;
	int j = 0 - m_point[0].y;

	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++) {
		int x, y;
		int changed_x, changed_y;
		if (k == 0) {
			pDC->MoveTo(m_point[k].x, m_point[k].y);
		}
		else if (k <= m_pointNum - 1) {
			x = m_point[k].x + i;
			y = m_point[k].y + j;
			changed_x = x * 2 - i;
			changed_y = y * 2 - j;
			pDC->LineTo(changed_x, changed_y);
		}
		else {
			pDC->LineTo(m_point[0].x, m_point[0].y);
		}
	}
}


void CGLtest1View::OnClean()
{
	CDC* pDC;
	pDC = GetWindowDC();

	m_point.clear();
	m_pointNum = 0;

	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));
}


void CGLtest1View::OnShrink()
{
	int i = 0 - m_point[0].x;
	int j = 0 - m_point[0].y;

	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++) {
		int x, y;
		int changed_x, changed_y;
		if (k == 0) {
			pDC->MoveTo(m_point[k].x, m_point[k].y);
		}
		else if (k <= m_pointNum - 1) {
			x = m_point[k].x + i;
			y = m_point[k].y + j;
			changed_x = x * 0.5 - i;
			changed_y = y * 0.5 - j;
			pDC->LineTo(changed_x, changed_y);
		}
		else {
			pDC->LineTo(m_point[0].x, m_point[0].y);
		}
	}
}


void CGLtest1View::OnShear()
{
	int i = 0 - m_point[0].x;
	int j = 0 - m_point[0].y;

	CDC* pDC;
	pDC = GetWindowDC();
	for (int k = 0; k <= m_pointNum; k++) {
		int x, y;
		int changed_x, changed_y;
		if (k == 0) {
			pDC->MoveTo(m_point[k].x, m_point[k].y);
		}
		else if (k <= m_pointNum - 1) {
			x = m_point[k].x + i;
			y = m_point[k].y + j;
			changed_x = x + (y / tan(PI / 4)) - i;
			changed_y = y - j;
			pDC->LineTo(changed_x, m_point[k].y);
		}
		else {
			pDC->LineTo(m_point[0].x, m_point[0].y);
		}
	}
}


void CGLtest1View::OnMirror()
{
	CDC* pDC;
	pDC = GetWindowDC();
	pDC->MoveTo(0, 150);
	pDC->LineTo(500, 150);
	for (int k = 0; k <= m_pointNum; k++) {
		if (k == 0) {
			pDC->MoveTo(m_point[k].x, 300-m_point[k].y);
		}
		else if (k <= m_pointNum - 1) {
			pDC->LineTo(m_point[k].x, 300-m_point[k].y);
		}
		else {
			pDC->LineTo(m_point[0].x, 300-m_point[0].y);
		}
	}
}


void CGLtest1View::OnCohenSutherland()
{
	CDC* pDC;
	pDC = GetWindowDC();
	pDC->Rectangle(&rect);

	type = 3;
}

int CGLtest1View::Encode(int x, int y) {
	int nCode = 0;
	if (x < LEFT) {
		nCode = nCode | 0x01;
	}
	if (x > RIGHT)
		nCode = nCode | 0x02;
	if (y > BOTTOM)
		nCode = nCode | 0x04;
	if (y < TOP)
		nCode = nCode | 0x08;
	return nCode;
}

void CGLtest1View::clip(CPoint& P1, CPoint& P2) {
	int nCode1 = 0;
	int nCode2 = 0;
	nCode1 = Encode(P1.x, P1.y);
	nCode2 = Encode(P2.x, P2.y);
	if (nCode1 == 0 && nCode2 == 0)		//在窗口里
		return;
	else if ((nCode1 & nCode2) != 0) {		//在窗口外
		P1 = CPoint(0, 0);
		P2 = CPoint(0, 0);
		return;
	}
	double wx = P2.x - P1.x;
	double wy = P2.y - P1.y;
	double dx = 0;
	double dy = 0;
	while (nCode1 != 0 || nCode2 != 0) {
		int nCode = nCode1;
		if (nCode1 == 0)
			nCode = nCode2;
		if ((nCode & 0x01) == 0x01) {
			dx = LEFT;
			dy = P1.y + wy*(LEFT - P1.x) / wx;
		}
		else if ((nCode & 0x02) == 0x02) {
			dx = RIGHT;
			dy = P1.y + wy*(RIGHT - P1.x) / wx;
		}
		else if ((nCode & 0x04) == 0x04) {
			dx = (BOTTOM - P1.y)*wx / wy + P1.x;
			dy = BOTTOM;
		}
		else if ((nCode & 0x08) == 0x08) {
			dx = (TOP - P1.y)*wx / wy + P1.x;
			dy = TOP;
		}

		if (nCode == nCode1) {
			P1 = CPoint((int)dx + 0.4, (int)dy + 0.4);
			nCode1 = Encode(P1.x, P1.y);
		}
		else {
			P2 = CPoint((int)dx + 0.4, (int)dy + 0.4);
			nCode2 = Encode(P2.x, P2.y);
		}
	}
}
