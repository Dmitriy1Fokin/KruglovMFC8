
// PaintORamaDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "PaintORama.h"
#include "PaintORamaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// ���������� ���� CPaintORamaDlg



CPaintORamaDlg::CPaintORamaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAINTORAMA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_PenColor = RGB(0, 0, 0);
}

void CPaintORamaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPaintORamaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLEARBTN, &CPaintORamaDlg::OnClickedClearbtn)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_STN_CLICKED(IDC_PENCOLOR, &CPaintORamaDlg::OnStnClickedPencolor)
END_MESSAGE_MAP()


// ����������� ��������� CPaintORamaDlg

BOOL CPaintORamaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���������� ������ "� ���������..." � ��������� ����.

	// IDM_ABOUTBOX ������ ���� � �������� ��������� �������.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������

	CWnd* p_Canvas = GetDlgItem(IDC_CANVAS);
	p_Canvas->GetWindowRect(&m_Canvas);
	ScreenToClient(&m_Canvas);
	m_Canvas.DeflateRect(2, 2, 1, 1);

	CWnd* pPenColor = GetDlgItem(IDC_PENCOLOR);
	pPenColor->GetWindowRect(&m_PenColorSwatch);
	ScreenToClient(&m_PenColorSwatch);
	m_PenColorSwatch.DeflateRect(2, 2, 1, 1);

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

void CPaintORamaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CPaintORamaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CPaintORamaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPaintORamaDlg::OnClickedClearbtn()
{
	// TODO: �������� ���� ��� ����������� �����������

	CClientDC dc(this);

	dc.SelectStockObject(NULL_PEN);

	dc.Rectangle(m_Canvas);
}


void CPaintORamaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	if (m_Canvas.PtInRect(point))
	{
		m_LineStart = point;
		m_LineEnd = point;
		m_Pen.DeleteObject();
		m_Pen.CreatePen(PS_SOLID, 1, m_PenColor);
		SetCapture();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPaintORamaDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	if ((nFlags & MK_LBUTTON) && m_Canvas.PtInRect(point))
	{
	CClientDC dc(this);
	dc.SelectObject(&m_Pen);
	m_LineEnd = point;
	dc.MoveTo(m_LineStart);
	dc.LineTo(m_LineEnd);
	m_LineStart = m_LineEnd;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CPaintORamaDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CPaintORamaDlg::OnStnClickedPencolor()
{
	// TODO: �������� ���� ��� ����������� �����������
	CColorDialog dlg(m_PenColor);

	if (dlg.DoModal() == IDOK)
	{
		m_PenColor = dlg.GetColor();
		CBrush swatch;
		swatch.CreateSolidBrush(m_PenColor);
		CClientDC dc(this);
		dc.FillRect(&m_PenColorSwatch, &swatch);
	}
}
