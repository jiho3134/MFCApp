
// MFCApp2View.cpp: CMFCApp2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApp2.h"
#endif

#include "MFCApp2Doc.h"
#include "MFCApp2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApp2View

IMPLEMENT_DYNCREATE(CMFCApp2View, CEditView)

BEGIN_MESSAGE_MAP(CMFCApp2View, CEditView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApp2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ZOOMIN, &CMFCApp2View::OnZoomin)
	ON_COMMAND(ID_ZOOMOUT, &CMFCApp2View::OnZoomout)
END_MESSAGE_MAP()

// CMFCApp2View 생성/소멸

CMFCApp2View::CMFCApp2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCApp2View::~CMFCApp2View()
{
}

BOOL CMFCApp2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL | WS_HSCROLL);	// 자동 래핑을 사용합니다.

	return bPreCreated;
}


// CMFCApp2View 인쇄


void CMFCApp2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApp2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 CEditView 준비
	return CEditView::OnPreparePrinting(pInfo);
}

void CMFCApp2View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 시작 인쇄
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMFCApp2View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 기본 CEditView 종료 인쇄
	CEditView::OnEndPrinting(pDC, pInfo);
}

void CMFCApp2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApp2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApp2View 진단

#ifdef _DEBUG
void CMFCApp2View::AssertValid() const
{
	CEditView::AssertValid();
}

void CMFCApp2View::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMFCApp2Doc* CMFCApp2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApp2Doc)));
	return (CMFCApp2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApp2View 메시지 처리기
static int fSize = 14;
CFont tf;
void CMFCApp2View::OnZoomin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// Client 영역의 문자 크기를 확대
	LOGFONT lf;
	//ZeroMemory(&lf, sizeof(lf));
	//lf.lfHeight = fSize++;
	if (GetFont() == NULL)
	{
		CFont* pFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
		pFont->GetLogFont(&lf);
	}
	else GetFont()->GetLogFont(&lf);
	if (lf.lfHeight < 0) lf.lfHeight = abs(lf.lfHeight);
	lf.lfHeight++;

	//CFont* cf = new CFont;
	//cf->DeleteObject();
	//cf->CreateFontIndirect(&lf);
	tf.DeleteObject();
	tf.CreateFontIndirect(&lf);
	SetFont(&tf);
}

void CMFCApp2View::OnZoomout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// Client 영역의 문자 크기를 축소
	LOGFONT lf;
	GetFont()->GetLogFont(&lf);
	lf.lfHeight--;

	tf.DeleteObject();
	tf.CreateFontIndirect(&lf);
	SetFont(&tf);
}