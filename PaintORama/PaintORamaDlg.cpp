
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
	, m_PenWidth(0)
	, m_PenStyle(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_PenColor = RGB(0, 0, 0);
	m_PenWidth = 1;
	m_BrushStyle = 0;
}

void CPaintORamaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PENWIDTH, m_PenWidth);
	DDV_MinMaxInt(pDX, m_PenWidth, 1, 32);
	DDX_Radio(pDX, IDC_SOLID_PEN, m_PenStyle);
	DDX_Control(pDX, IDC_SHAPES, m_ShapesCombo);
	DDX_Control(pDX, IDC_BRUSHSTYLE, m_BrushStyleList);
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
	ON_LBN_SELCHANGE(IDC_BRUSHSTYLE, &CPaintORamaDlg::OnSelchangeBrushstyle)
	ON_STN_CLICKED(IDC_BRUSHCOLOR, &CPaintORamaDlg::OnClickedBrushcolor)
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

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1);
	pSpin->SetRange(1, 32);
	pSpin->SetPos(1);

	m_ShapesCombo.SetCurSel(0);

	//�������� ��������� �� ������� ����������
	CWnd* pBrushColor = GetDlgItem(IDC_BRUSHCOLOR);

	//�������� ���������� �������� ����������
	pBrushColor->GetWindowRect(&m_BrushColorSwatch);

	//�������� ���������� ������������ ���������� �������
	ScreenToClient(&m_BrushColorSwatch);

	//C����� �����
	m_BrushColorSwatch.DeflateRect(2, 2, 1, 1);



	//�������� ��������� �� ������� ����������
	CWnd* pPreviewColor = GetDlgItem(IDC_BRUSHPREVIEW);

	//�������� ���������� �������� ����������
	pPreviewColor->GetWindowRect(&m_BrushPreviewSwatch);

	//�������� ���������� ������������ ���������� �������
	ScreenToClient(&m_BrushPreviewSwatch);

	//C����� �����
	m_BrushPreviewSwatch.DeflateRect(2, 2, 1, 1);

	//���������� ��������� ���� �����
	m_BrushColor = RGB(0, 0, 0);

	//������� ����� �����
	m_Brush.CreateStockObject(WHITE_BRUSH);

	//�������� �������� ������ � ������� ListBox
	m_BrushStyleList.AddString((LPCTSTR)"(none)");
	m_BrushStyleList.AddString((LPCTSTR)"Solid");
	m_BrushStyleList.AddString((LPCTSTR)"LL-UR Diagonal");
	m_BrushStyleList.AddString((LPCTSTR)"UL-LR Diagonal");
	m_BrushStyleList.AddString((LPCTSTR)"Grid");
	m_BrushStyleList.AddString((LPCTSTR)"Grid Diagonal");
	m_BrushStyleList.AddString((LPCTSTR)"Horizontal");
	m_BrushStyleList.AddString((LPCTSTR)"Vertical");
	m_BrushStyleList.AddString((LPCTSTR)"White");
	m_BrushStyleList.AddString((LPCTSTR)"Light Gray");
	m_BrushStyleList.AddString((LPCTSTR)"Medium Gray");
	m_BrushStyleList.AddString((LPCTSTR)"Dark Gray");
	m_BrushStyleList.AddString((LPCTSTR)"Black");

	//���������� ��������� ������� ������� �� 8 ��������
	m_BrushStyleList.SetCurSel(8);


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

		m_IsDrawing = true;
		
		m_Pen.DeleteObject();
		UpdateData(TRUE);
		m_Pen.CreatePen(m_PenStyle, m_PenWidth, m_PenColor);

		SetCapture();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CPaintORamaDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	if (m_IsDrawing && (nFlags & MK_LBUTTON) && m_Canvas.PtInRect(point))
	{
		DrawShape(true);
		m_LineStart = m_LineEnd;
		DrawShape(true);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CPaintORamaDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	
	//��������� ����� ���������
	m_IsDrawing = FALSE;

	/*���� ����� �������� ������ ������� ���������, �� ���������� ������ ������������*/
	if (m_Canvas.PtInRect(point))
	{
		m_LineEnd = point;
		DrawShape();
	}
	//���� ���, �� �������
	else
	{
		DrawShape(true);
	}

	m_LineStart = point;

	//��������� ����
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

void CPaintORamaDlg::DrawShape(bool stretch)
{
	//�������� ������ ��������� ����������
	CClientDC dc(this);

	//���������� �������� DC
	dc.SetAttribDC(dc);
	dc.IntersectClipRect(m_Canvas);

	//�������� ����� ������� �� ����� �������� �����
	int drawmode = m_ShapesCombo.GetCurSel();
	
	//������� ����
	dc.SelectObject(&m_Brush);

	//dc.SelectObject(&m_Pen);

	//����� ��������� ����
	if (stretch && (drawmode != 0))
	{
		//���������� ����� ��������� ����
		dc.SetROP2(R2_NOT);
	}

	//����������� ������ ������
	switch (drawmode)
	{
		//��������� ���������
	case 0:
		dc.MoveTo(m_LineStart);
		dc.LineTo(m_LineEnd);
		m_LineStart = m_LineEnd;
		break;
		//��������� �����
	case 1:
		dc.MoveTo(m_LineStart);
		dc.LineTo(m_LineEnd);
		break;
		//��������� �������
	case 2:
		dc.Ellipse(CRect(m_LineStart, m_LineEnd));
		break;
		//��������� ��������������
	case 3:
		dc.Rectangle(CRect(m_LineStart, m_LineEnd));
		break;
	}

}

void CPaintORamaDlg::OnSelchangeBrushstyle()
{
	// TODO: �������� ���� ��� ����������� �����������
	//������� ���������� ������
	m_Brush.DeleteObject();

	//�������� ����� ��������� �������
	int style = m_BrushStyleList.GetCurSel();

	//�� ������ ������� �����, � ��������� ������
	switch (style)
	{
	case 0:
		m_Brush.CreateStockObject(NULL_BRUSH);
		break;
	case 1:
		m_Brush.CreateSolidBrush(m_BrushColor);
		break;
	case 2:
		m_Brush.CreateHatchBrush(HS_BDIAGONAL, m_BrushColor);
		break;
	case 3:
		m_Brush.CreateHatchBrush(HS_FDIAGONAL, m_BrushColor);
		break;
	case 4:
		m_Brush.CreateHatchBrush(HS_CROSS, m_BrushColor);
		break;
	case 5:
		m_Brush.CreateHatchBrush(HS_DIAGCROSS, m_BrushColor);
		break;
	case 6:
		m_Brush.CreateHatchBrush(HS_HORIZONTAL, m_BrushColor);
		break;
	case 7:
		m_Brush.CreateHatchBrush(HS_VERTICAL, m_BrushColor);
		break;
	case 9:
		m_Brush.CreateStockObject(LTGRAY_BRUSH);
		break;
	case 10:
		m_Brush.CreateStockObject(GRAY_BRUSH);
		break;
	case 11:
		m_Brush.CreateStockObject(DKGRAY_BRUSH);
		break;
	case 12:
		m_Brush.CreateStockObject(BLACK_BRUSH);
		break;
		//������� ����� �� ���������
	default:
		m_Brush.CreateStockObject(WHITE_BRUSH);
		break;
	}

	//������� ������� ��������� ���� Preview
	PaintBrushPreview();
}

void CPaintORamaDlg::PaintBrushPreview()
{
	CClientDC dc(this);
	dc.FillRect(&m_BrushPreviewSwatch, &m_Brush);
}


void CPaintORamaDlg::OnClickedBrushcolor()
{
	// TODO: �������� ���� ��� ����������� �����������
	//������� ������ ����������� ���� ����� �����
	CColorDialog dlg(m_BrushColor);

	/*���� ���� ������ ������ ��, �� ��������� ��������� �����*/
	if (dlg.DoModal() == IDOK)
	{
		m_BrushColor = dlg.GetColor();
		CClientDC dc(this);
		CBrush b(m_BrushColor);

		//������������ ���������� ����� �����
		dc.FillRect(&m_BrushColorSwatch, &b);
	}

	/*��������� ������� �������� �����, ��������� ������*/
	OnSelchangeBrushstyle();
}
