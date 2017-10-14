// Gate.cpp : 实现文件
//

#include "stdafx.h"
#include "GateCircuitDemo.h"
#include "Gate.h"
#include "Pin.h"

// CGate
CGate::CGate()
{
	m_Position.x = 0; //位置
	m_Position.y = 0;
	m_Rect.left = 0; //外接矩形框
	m_Rect.right = 0;
	m_Rect.top = 0;
	m_Rect.bottom = 0;
	m_IsSelected = 0; //是否选中；
	m_Pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));        //未选中时绘制笔
	m_SelectedPen.CreatePen(PS_SOLID, 2, RGB(255,0,255));//选中时绘制用笔

}
CGate::CGate(CPoint point)
{
	m_Position= point;         //位置
	m_Rect.left = point.x; //外接矩形框
	m_Rect.right = point.x + 40;
	m_Rect.top = point.y;
	m_Rect.bottom = point.y + 40;
	m_IsSelected = 0; //是否选中；
	m_Pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));        //未选中时绘制笔
	m_SelectedPen.CreatePen(PS_SOLID, 2, RGB(255,0,255));//选中时绘制用笔
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


// CGate 成员函数

//移动
void CGate::MoveTo(CPoint to)
{
	int offsetx = to.x;
	int offsety = to.y;


	m_Position.x += to.x;
	m_Position.y += to.y;
	//外接矩形框
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
//根据点选中门
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
	//如果没有选中，清除所有引脚选中
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
//引脚的选中
 CPin * CGate::SelectedPin(CPoint point)
{
	//记录要找的Pin 初始为NULL没有找到
	CPin * selectedPin = NULL;
	if (m_IsSelected)
	{ 
		POSITION pos = m_InPins.GetHeadPosition();
		while(pos)
		{
			CPin * pin = (CPin*) m_InPins.GetNext(pos);
			//如果没有找到，查找，
			//如果找到了，设置所有pin都不选中
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
//不选中
void CGate::NotSelected()
{
	m_IsSelected = false;
}
//查找最近的引脚
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


	// 画出外接矩形框
	CPoint point[5];
	point[0] = CPoint(m_Rect.left, m_Rect.top);
	point[1] = CPoint(m_Rect.left, m_Rect.top + 40);
	point[2] = CPoint(m_Rect.left + 60, m_Rect.top + 40);
	point[3] = CPoint(m_Rect.left + 60, m_Rect.top);
	point[4] = point[0];
	pDC->Polyline(point, 5);
	pDC->SelectObject(oldpen);
	
}
