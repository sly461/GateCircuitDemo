// NotGate.cpp : 实现文件
//

#include "stdafx.h"
#include "GateCircuitDemo.h"
#include "NotGate.h"
#include "Pin.h"


// CNotGate
 

CNotGate::CNotGate()
{

}

CNotGate::CNotGate(CPoint p):CGate(p)
{
	m_Rect.right = p.x + 60;
	m_Rect.bottom = p.y + 40;

	p.y += 20;
	CPin *inp = new CPin(p);         //进
	m_InPins.AddHead(inp);
	p.x += 60;
	CPin * outp = new CPin(p);        //出
	m_OutPins.AddHead(outp);
}


CNotGate::~CNotGate()
{
}

void CNotGate::Draw(CDC * pDC)
{
	POSITION pos;
	CPin * pinIn, *pinOut;
	pos = m_InPins.GetHeadPosition();   //根据引脚所在的点画门
	while (pos)
	{
		pinIn = (CPin*)m_InPins.GetNext(pos);
	}
	pos = m_OutPins.GetHeadPosition();
	while (pos)
	{
		pinOut = (CPin*)m_OutPins.GetNext(pos);
	}


	CPoint point[5];
	point[0] = pinIn->GetPosition();
	point[1] = point[0];
	point[1].x += 20;
	point[2] = point[1];
	point[2].y += 20;
	point[3] = point[2];
	point[3].x += 20;
	point[3].y -= 20;
	point[4] = pinOut->GetPosition();

	CPoint point2[3]; 
	point2[0] = point[1];
	point2[1] = point2[0];
	point2[1].y -= 20;
	point2[2] = point[3];

	CPen * oldpen;
	if (m_IsSelected)
	{
		oldpen = pDC->SelectObject(&m_SelectedPen);
	}else
	{
		oldpen = pDC->SelectObject(&m_Pen);
	}

	pDC->Polyline(point, 5);
	pDC->Polyline(point2, 3);
	pDC->Ellipse(point[3].x - 3, point[3].y - 3,
		point[3].x + 3, point[3].y + 3);
	
	
	if (m_IsSelected)           //如果选中  画出外接框
	{
		DrawRect(pDC);
	}
	pDC->SelectObject(oldpen);

	pos = m_InPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_InPins.GetNext(pos);
		pin->Draw(pDC);
	}
	pos = m_OutPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_OutPins.GetNext(pos);
		pin->Draw(pDC);
	}
}

 

 


