// ANDGate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GateCircuitDemo.h"
#include "ANDGate.h"
#include "Pin.h"

// CANDGate

CANDGate::CANDGate()
{
}

CANDGate::CANDGate(CPoint p):CGate(p)
{ 
	m_Position = p;

	m_Rect.right = p.x + 60;       //���ο�
	m_Rect.bottom = p.y + 40;

	p.y += 10;                    //��������
	CPin *inp = new CPin(p);
	m_InPins.AddHead(inp);

	p.y += 20;
	inp = new CPin(p);
	m_InPins.AddHead(inp);

	
	p.x += 60;                       //һ������
	p.y -= 10;
	CPin * outp = new CPin(p);
	m_OutPins.AddHead(outp);


}
CANDGate::~CANDGate()
{

}
void CANDGate::Draw(CDC * pDC)
{
	POSITION pos = m_InPins.GetHeadPosition();         //�������Ż���
	CPin * pinIn1, *pinIn2, *pinOut;

	int flag = 0;
	while (pos)
	{
		if (!flag)
		{
			pinIn1 = (CPin*)m_InPins.GetNext(pos);
			flag = 1;
		}
		else pinIn2= (CPin*)m_InPins.GetNext(pos);
	}
	pos = m_OutPins.GetHeadPosition();
	while (pos)
	{
		pinOut = (CPin*)m_OutPins.GetNext(pos);
	}


	CPen * oldpen;                     //����
	if (m_IsSelected)
	{
		oldpen = pDC->SelectObject(&m_SelectedPen);
	}
	else
	{
		oldpen = pDC->SelectObject(&m_Pen);
	}

	CPoint point[2];                         //��������
	point[0] = pinIn1->GetPosition();
	point[1] = point[0];
	point[1].x += 20;
	pDC->Polyline(point, 2);


	point[0] = pinIn2->GetPosition();
	point[1] = point[0];
	point[1].x += 20;
	pDC->Polyline(point, 2);

	point[0] = pinOut->GetPosition();
	point[1] = point[0];
	point[1].x -= 20;
	pDC->Polyline(point, 2);

	point[1].x -= 20;                    
	point[0] = point[1];
	point[0].y -= 20;
	pDC->Polyline(point, 2);
	
	float angleStart = 270.f;           //����Բ
	float angleSize = 180.f;
	pDC->MoveTo(point[1]);
	pDC->AngleArc(point[1].x, point[1].y, 20, angleStart, angleSize);
	

	if (m_IsSelected)
	{
		DrawRect(pDC);
	}

	pDC->SelectObject(oldpen);

	pos = m_InPins.GetHeadPosition();
	while (pos)
	{
		CPin * pin = (CPin*)m_InPins.GetNext(pos);
		pin->Draw(pDC);
	}
	pos = m_OutPins.GetHeadPosition();
	while (pos)
	{
		CPin * pin = (CPin*)m_OutPins.GetNext(pos);
		pin->Draw(pDC);
	}

}


