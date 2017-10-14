
// GateCircuitDemoView.cpp : CGateCircuitDemoView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "GateCircuitDemo.h"
#endif

#include "GateCircuitDemoDoc.h"
#include "GateCircuitDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGateCircuitDemoView

IMPLEMENT_DYNCREATE(CGateCircuitDemoView, CView)

BEGIN_MESSAGE_MAP(CGateCircuitDemoView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGateCircuitDemoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_SELECTED, &CGateCircuitDemoView::OnSelected)
	ON_COMMAND(ID_NOTGATE, &CGateCircuitDemoView::OnNotgate)
	ON_UPDATE_COMMAND_UI(ID_NOTGATE, &CGateCircuitDemoView::OnUpdateNotgate)
	ON_UPDATE_COMMAND_UI(ID_SELECTED, &CGateCircuitDemoView::OnUpdateSelected)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_ANDGATE, &CGateCircuitDemoView::OnAndgate)
	ON_UPDATE_COMMAND_UI(ID_ANDGATE, &CGateCircuitDemoView::OnUpdateAndgate)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CGateCircuitDemoView ����/����

CGateCircuitDemoView::CGateCircuitDemoView()
{
	// TODO: �ڴ˴���ӹ������
	m_flag = false;
	m_type = 0;
	m_mousePoint = CPoint(0, 0);
	m_selectedGate = nullptr;
	m_isSelectedGate = false;    
	m_selectedPin = nullptr;
}

CGateCircuitDemoView::~CGateCircuitDemoView()
{
}

BOOL CGateCircuitDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGateCircuitDemoView ����

void CGateCircuitDemoView::OnDraw(CDC* pDC)
{
	CGateCircuitDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	POSITION pos = m_gates.GetHeadPosition();
	while(pos)
	{
		((CGate *)(m_gates.GetNext(pos)))->Draw(pDC);
	}
	
}


// CGateCircuitDemoView ��ӡ

//����������֮�������
void CGateCircuitDemoView::LineToPin(CPoint point)
{
	m_isSelectedGate = false;
	m_mousePoint = point;
	if (m_selectedPin != nullptr)
	{
		POSITION pos = m_gates.GetHeadPosition();
		CGate* linkGate = nullptr;
		while (pos)
		{
			linkGate = ((CGate *)(m_gates.GetNext(pos)))->Selected(point);
			if (m_selectedGate == linkGate)
			{
				linkGate = nullptr;
			}
			if (linkGate != nullptr)
				break;
		}
		if (linkGate != nullptr)
		{
			CPin *pin = linkGate->FindLatePin(point);
			if (pin != nullptr)
			{
				pin->AddLinkPin(m_selectedPin);
				m_selectedPin->AddLinkPin(pin);
			}

		}
		this->Invalidate();
		m_selectedPin = nullptr;
		m_flag = true;
	}
}

//ѡ��Ԫ����������
void CGateCircuitDemoView::SelectGateAndPin(CPoint point)
{
	//ѡ��Ԫ����
	POSITION pos = m_gates.GetHeadPosition();
	while (pos)
	{
		CGate * t = ((CGate *)(m_gates.GetNext(pos)));
		if (!m_isSelectedGate)t = t->Selected(point);
		if (m_isSelectedGate == false && t != nullptr)
		{
			m_isSelectedGate = true;
			t->m_IsSelected = true;
			m_selectedGate = t;
		}
		else
		{
			if (nullptr != t)t->m_IsSelected = false;
		}
	}
	if (false == m_isSelectedGate)
	{
		m_selectedGate = nullptr;
		m_selectedPin = nullptr;
	}
	if (nullptr != m_selectedGate)
	{
		m_selectedPin = m_selectedGate->SelectedPin(point);
		if (m_selectedPin != nullptr)m_selectedPin->setMousePoint(point);
	}
	this->Invalidate();
}

void CGateCircuitDemoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGateCircuitDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGateCircuitDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGateCircuitDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CGateCircuitDemoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGateCircuitDemoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGateCircuitDemoView ���

#ifdef _DEBUG
void CGateCircuitDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CGateCircuitDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGateCircuitDemoDoc* CGateCircuitDemoView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGateCircuitDemoDoc)));
	return (CGateCircuitDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CGateCircuitDemoView ��Ϣ�������


void CGateCircuitDemoView::OnSelected()
{
	m_type = 0;
}


void CGateCircuitDemoView::OnNotgate()
{
	m_type = 1;
}


void CGateCircuitDemoView::OnUpdateNotgate(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_type == 1);
}


void CGateCircuitDemoView::OnUpdateSelected(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_type == 0);
}


void CGateCircuitDemoView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_mousePoint = point;
	switch(m_type)
	{
	case 1: 
		{
		CNotGate * pGate = new CNotGate(point);
		m_gates.AddHead(pGate);
		break; 
		}
	case 2: 
		{
		CANDGate * pGate = new CANDGate(point);
		m_gates.AddHead(pGate);
		break; 
		}
	default:
		break;
	}
	this->Invalidate();
	CView::OnLButtonDblClk(nFlags, point);
}


void CGateCircuitDemoView::OnAndgate()
{
	m_type = 2;
}


void CGateCircuitDemoView::OnUpdateAndgate(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_type == 2);
}





void CGateCircuitDemoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	//��ǰ��ѡ�����ţ�������ֵ����һ��Ԫ���������ţ�������������
	LineToPin(point);
	if (m_flag)
	{
		m_flag = false;
		return;
	}
	//�����������λ���ж��Ƿ�ѡ��Ԫ������Ԫ�����ϵ�����
	SelectGateAndPin(point);
	CView::OnLButtonDown(nFlags, point);
}


void CGateCircuitDemoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isSelectedGate = false;
	m_mousePoint = point;
	CView::OnLButtonUp(nFlags, point);
}


void CGateCircuitDemoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_selectedGate == nullptr)
		return;
	if (m_isSelectedGate)
	{
		CPoint c = CPoint(point.x - m_mousePoint.x, point.y - m_mousePoint.y);
		m_selectedGate->MoveTo(c);
		m_mousePoint = point;
	}


	//���ѡ��������  
	if (nullptr != m_selectedPin)
		m_selectedPin->setMousePoint(point);

	this->Invalidate();
	CView::OnMouseMove(nFlags, point);
}
