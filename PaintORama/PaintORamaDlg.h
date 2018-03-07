
// PaintORamaDlg.h : ���� ���������
//

#pragma once
#include "afxwin.h"


// ���������� ���� CPaintORamaDlg
class CPaintORamaDlg : public CDialogEx
{
// ��������
public:
	CPaintORamaDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAINTORAMA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CRect m_Canvas;
	CPoint m_LineEnd;
	CPoint m_LineStart;
	COLORREF m_PenColor;
	CRect m_PenColorSwatch;
	CPen m_Pen;
	bool m_IsDrawing;
	CBrush m_Brush;
	COLORREF m_BrushColor;
	CRect m_BrushColorSwatch;
	CRect m_BrushPreviewSwatch;
	int m_BrushStyle;

	void DrawShape(bool stretch = false);
	void PaintBrushPreview();

public:
	int m_PenWidth;
	int m_PenStyle;
	CComboBox m_ShapesCombo;
	CListBox m_BrushStyleList;
	
	afx_msg void OnClickedClearbtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnStnClickedPencolor();
	afx_msg void OnSelchangeBrushstyle();
		
	afx_msg void OnClickedBrushcolor();
};
