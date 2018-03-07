
// PaintORamaDlg.h : файл заголовка
//

#pragma once


// диалоговое окно CPaintORamaDlg
class CPaintORamaDlg : public CDialogEx
{
// Создание
public:
	CPaintORamaDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAINTORAMA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CRect m_Canvas;
public:
	afx_msg void OnClickedClearbtn();
private:
	CPoint m_LineEnd;
	CPoint m_LineStart;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	COLORREF m_PenColor;
	CRect m_PenColorSwatch;
public:
	afx_msg void OnStnClickedPencolor();
private:
	CPen m_Pen;
public:
	int m_PenWidth;
	int m_PenStyle;
};
