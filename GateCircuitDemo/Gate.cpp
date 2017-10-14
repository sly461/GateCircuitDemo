// Gate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GateCircuitDemo.h"
#include "Gate.h"
#include "Pin.h"

// CGate
CGate::CGate()
{
	m_Position.x = 0; //λ��
	m_Position.y = 0;
	m_Rect.left = 0; //��Ӿ��ο�
	m_Rect.right = 0;
	m_Rect.top = 0;
	m_Rect.bottom = 0;
	m_IsSelected = 0; //�Ƿ�ѡ�У�
	m_Pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));        //δѡ��ʱ���Ʊ�
	m_SelectedPen.CreatePen(PS_SOLID, 2, RGB(255,0,255));//ѡ��ʱ�����ñ�

}
CGate::CGate(CPoint point)
{
	m_Position= point;         //λ��
	m_Rect.left = point.x; //��Ӿ��ο�
	m_Rect.right = point.x + 40;
	m_Rect.top = point.y;
	m_Rect.bottom = point.y + 40;
	m_IsSelected = 0; //�Ƿ�ѡ�У�
	m_Pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));        //δѡ��ʱ���Ʊ�
	m_SelectedPen.CreatePen(PS_SOLID, 2, RGB(255,0,255));//ѡ��ʱ�����ñ�
}



CGate::~CGate()
{
	POSITION pos = m_InPins.GetHeadPosition();
	while(pos)
	{
		delete m_InPins.GetNext(pos);
	}

	pos = m_OutPins.GetHeadPosition();
	while(pos)
	{
		delete m_OutPins.GetNext(pos);
	}

}


// CGate ��Ա����

//�ƶ�
void CGate::MoveTo(CPoint to)
{
	int offsetx = to.x;
	int offsety = to.y;


	m_Position.x += to.x;
	m_Position.y += to.y;
	//��Ӿ��ο�
	m_Rect.left += to.x;
	m_Rect.right += to.x;
	m_Rect.top += to.y;
	m_Rect.bottom += to.y;

	POSITION pos = m_InPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_InPins.GetNext(pos);
		pin->Move(offsetx, offsety);
	}

	pos = m_OutPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_OutPins.GetNext(pos);
		pin->Move(offsetx, offsety);
	}

}
//���ݵ�ѡ����
CGate * CGate::Selected(CPoint point)
{

	if (m_Rect.PtInRect(point))
	{
		m_IsSelected = true;	
		SelectedPin(point);
	}
	else
	{
		m_IsSelected = false;
	}
	//���û��ѡ�У������������ѡ��
	if (!m_IsSelected)
	{
		POSITION pos = m_InPins.GetHeadPosition();
		while(pos)
		{
			CPin * pin = (CPin*) m_InPins.GetNext(pos);
			pin->NotSelected();
		}

		pos = m_OutPins.GetHeadPosition();
		while(pos)
		{
			CPin * pin = (CPin*) m_OutPins.GetNext(pos);
			pin->NotSelected();
		} 
	}

	if (m_IsSelected)
		return this;
	else
		return NULL;



}
//���ŵ�ѡ��
 CPin * CGate::SelectedPin(CPoint point)
{
	//��¼Ҫ�ҵ�Pin ��ʼΪNULLû���ҵ�
	CPin * selectedPin = NULL;
	if (m_IsSelected)
	{ 
		POSITION pos = m_InPins.GetHeadPosition();
		while(pos)
		{
			CPin * pin = (CPin*) m_InPins.GetNext(pos);
			//���û���ҵ������ң�
			//����ҵ��ˣ���������pin����ѡ��
			if (selectedPin == NULL)
			{
				if (pin->Selected(point))
				{
					selectedPin = pin;
				}
			}
			else
			{
				pin->NotSelected();
			}
		}

		pos = m_OutPins.GetHeadPosition();
		while(pos)
		{
			CPin * pin = (CPin*) m_OutPins.GetNext(pos);
			if (selectedPin == NULL)
			{
				if (pin->Selected(point))
				{
					selectedPin = pin;
				}
			}else
			{
				pin->NotSelected();
			}
		}

	}
	return selectedPin;
}
//��ѡ��
void CGate::NotSelected()
{
	m_IsSelected = false;
}
//�������������
CPin * CGate::FindLatePin(CPoint point)
{
	POSITION pos = m_InPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_InPins.GetNext(pos);
		if (pin->NearMe(point))
		{
			return pin;
		}
	}
	pos = m_OutPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_OutPins.GetNext(pos);
		if (pin->NearMe(point))
		{
			return pin;
		} 
	} 
	return nullptr;

}
void CGate::DrawRect(CDC *pDC)
{
	CPen * oldpen;

	if (m_IsSelected)
	{
		oldpen = pDC->SelectObject(&m_SelectedPen);
	}
	else
	{
		oldpen = pDC->SelectObject(&m_Pen);
	}


	// ������Ӿ��ο�
	CPoint point[5];
	point[0] = CPoint(m_Rect.left, m_Rect.top);
	point[1] = CPoint(m_Rect.left, m_Rect.top + 40);
	point[2] = CPoint(m_Rect.left + 60, m_Rect.top + 40);
	point[3] = CPoint(m_Rect.left + 60, m_Rect.top);
	point[4] = point[0];
	pDC->Polyline(point, 5);
	pDC->SelectObject(oldpen);
	
}
