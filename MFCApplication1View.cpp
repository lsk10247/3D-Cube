
// MFCApplication1View.cpp: CMFCApplication1View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#include"Tool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFCApplication1View 构造/析构

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: 在此处添加构造代码
}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 绘图
int c = -10;
void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->LineTo(100, 100);
	DrawCircle(600, 300, 99, 50, pDC);
	DrawLine2(200, 200, 300, 150, pDC);
	DrawLine3(250, 200, 300, 201, pDC);
	DrawLine2(200, 200, 300, 250, pDC);
	DrawLine2(200, 200, 300, 50, pDC);
	DrawLine2(200, 200, 300, 350, pDC);
	// TODO: 在此处为本机数据添加绘制代码
	Object object;
	object.Move(0, 0, 0);
	DrawObject(object,camera.WorldToScreenMatrix(0, 0, 1000, 1000, 1, 500),pDC);

	//camera.rotatex = 0.3;
	
	//Eigen::Matrix4f matrix = camera.WorldToScreenMatrix(0, 0, 1000, 1000, 1, 500);
	//Eigen::Vector4f pos1(-10.0 + c, 100.0, 10.0 + c,1);
	//Eigen::Vector4f pos2(-10.0 + c, 100.0, 60.0 + c,1);
	//Eigen::Vector4f pos3(-10.0 + c, 200.0, 10.0 + c,1);
	//Eigen::Vector4f pos4(-10.0 + c, 200.0, 60.0 + c,1);
	//Eigen::Vector4f pos5(10.0 + c, 100.0, 10.0 + c,1);
	//Eigen::Vector4f pos6(10.0 + c, 100.0, 60.0 + c,1);
	//Eigen::Vector4f pos7(10.0  +c , 200.0, 10.0 + c,1);
	//Eigen::Vector4f pos8(10.0 + c, 200.0, 60.0 + c,1);
	//pos1 = matrix * pos1;
	//pos2 = matrix * pos2;
	//pos3 = matrix * pos3;
	//pos4 = matrix * pos4;
	//pos5 = matrix * pos5;
	//pos6 = matrix * pos6;
	//pos7 = matrix * pos7;
	//pos8 = matrix * pos8;
	//pos1 /= pos1(3);
	//pos2 /= pos2(3);
	//pos3 /= pos3(3);
	//pos4 /= pos4(3);
	//pos5 /= pos5(3);
	//pos6 /= pos6(3);
	//pos7 /= pos7(3);
	//pos8 /= pos8(3);
	//DrawLine(round(pos1(0)), round(pos1(2)), round(pos2(0)), round(pos2(2)), pDC);
	//DrawLine(round(pos1(0)), round(pos1(2)), round(pos3(0)), round(pos3(2)), pDC);
	//DrawLine(round(pos3(0)), round(pos3(2)), round(pos4(0)), round(pos4(2)), pDC);
	//DrawLine(round(pos2(0)), round(pos2(2)), round(pos4(0)), round(pos4(2)), pDC);
	//DrawLine(round(pos2(0)), round(pos2(2)), round(pos6(0)), round(pos6(2)), pDC);
	//DrawLine(round(pos1(0)), round(pos1(2)), round(pos5(0)), round(pos5(2)), pDC);
	//DrawLine(round(pos5(0)), round(pos5(2)), round(pos6(0)), round(pos6(2)), pDC);
	//DrawLine(round(pos3(0)), round(pos3(2)), round(pos7(0)), round(pos7(2)), pDC);
	//DrawLine(round(pos5(0)), round(pos5(2)), round(pos7(0)), round(pos7(2)), pDC);
	//DrawLine(round(pos7(0)), round(pos7(2)), round(pos8(0)), round(pos8(2)), pDC);
	//DrawLine(round(pos6(0)), round(pos6(2)), round(pos8(0)), round(pos8(2)), pDC);
	//DrawLine(round(pos4(0)), round(pos4(2)), round(pos8(0)), round(pos8(2)), pDC);

}


// CMFCApplication1View 打印


void CMFCApplication1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCApplication1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication1View 诊断

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 消息处理程序


void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);
}


void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nFlags)
	{
	case 30:
		//A
		camera.x -= 1;
		break;
	case 17:
		//W
		camera.y += 1;
		break;
	case 31:
		//S
		camera.y -= 1;
		break;
	case 32:
		//D
		camera.x += 1;
		break;
	default:
		break;
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int dx = point.x - mousepoint.x;
	camera.rotatez -= (float)dx / 100;
	mousepoint = point;
	Invalidate();
	CView::OnMouseMove(nFlags, point);
}
