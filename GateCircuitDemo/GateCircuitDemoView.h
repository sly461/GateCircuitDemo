
// GateCircuitDemoView.h : CGateCircuitDemoView ��Ľӿ�
//

#pragma once
#include "NotGate.h"
#include "ANDGate.h"
#include "Pin.h"

class CGateCircuitDemoView : public CView
{
protected: // �������л�����
	CGateCircuitDemoView();
	DECLARE_DYNCREATE(CGateCircuitDemoView)

// ����
public:
	CGateCircuitDemoDoc* GetDocument() const;

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
	virtual ~CGateCircuitDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	bool m_isSelectedGate;        //�Ƿ�ѡ����
	CPoint m_mousePoint;      //����λ��
	int m_type;                  //ѡ������
	CPin * m_selectedPin;         //ѡ�е�����
	CObList m_gates;             //װ�ŵ�����
	CGate * m_selectedGate;     //ѡ�е���
	
	
	void LineToPin(CPoint point);                //����������֮�������
	void SelectGateAndPin(CPoint point);          //ѡ����


protected:
	bool m_flag;                     //�л�����
	



// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSelected();
	afx_msg void OnNotgate();
	afx_msg void OnUpdateNotgate(CCmdUI *pCmdUI);

	afx_msg void OnUpdateSelected(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnAndgate();
	afx_msg void OnUpdateAndgate(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // GateCircuitDemoView.cpp �еĵ��԰汾
inline CGateCircuitDemoDoc* CGateCircuitDemoView::GetDocument() const
   { return reinterpret_cast<CGateCircuitDemoDoc*>(m_pDocument); }
#endif

