#pragma once

// CPin ����Ŀ��
//����
class CPin : public CObject
{
public:
	CPin();
	CPin(CPoint point);
	virtual ~CPin();


protected:
	CPoint m_Position; //λ��
	CObList m_LinkPins; //���ӵ�����
	bool m_IsSelected;//�Ƿ�ѡ��
	CPen m_SelectedPen; //ѡ��ʱ���Ƶı�
	CPoint m_mousePoint;        //����λ��

public:
	void Draw(CDC * pDC); //����
	void Move(int offsetx, int offsety);//�ƶ�
	CPin * Selected(CPoint point);//ѡ��
	CPin * NearMe(CPoint point);//�Ƿ����Լ��ܽ�

	void NotSelected();//����ѡ��

	void SetPoint(CPoint point);//����λ��
	CPoint GetPosition();
	void setMousePoint(CPoint c);        //��������λ��
	void AddLinkPin(CPin * ppin);//�����������
	
};


