
// GateCircuitDemoView.h : CGateCircuitDemoView 类的接口
//

#pragma once
#include "NotGate.h"
#include "ANDGate.h"
#include "Pin.h"

class CGateCircuitDemoView : public CView
{
protected: // 仅从序列化创建
	CGateCircuitDemoView();
	DECLARE_DYNCREATE(CGateCircuitDemoView)

// 特性
public:
	CGateCircuitDemoDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGateCircuitDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	bool m_isSelectedGate;        //是否选中门
	CPoint m_mousePoint;      //鼠标的位置
	int m_type;                  //选中类型
	CPin * m_selectedPin;         //选中的引脚
	CObList m_gates;             //装门的容器
	CGate * m_selectedGate;     //选中的门
	
	
	void LineToPin(CPoint point);                //引脚与引脚之间的连线
	void SelectGateAndPin(CPoint point);          //选中门


protected:
	bool m_flag;                     //切换函数
	



// 生成的消息映射函数
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

#ifndef _DEBUG  // GateCircuitDemoView.cpp 中的调试版本
inline CGateCircuitDemoDoc* CGateCircuitDemoView::GetDocument() const
   { return reinterpret_cast<CGateCircuitDemoDoc*>(m_pDocument); }
#endif

