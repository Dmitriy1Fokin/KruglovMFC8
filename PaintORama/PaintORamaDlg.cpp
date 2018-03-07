
// PaintORamaDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "PaintORama.h"
#include "PaintORamaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// диалоговое окно CPaintORamaDlg



CPaintORamaDlg::CPaintORamaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAINTORAMA_DIALOG, pParent)
	, m_PenWidth(0)
	, m_PenStyle(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_PenColor = RGB(0, 0, 0);
	m_PenWidth = 1;
}

void CPaintORamaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PENWIDTH, m_PenWidth);
	DDV_MinMaxInt(pDX, m_PenWidth, 1, 32);
	DDX_Radio(pDX, IDC_SOLID_PEN, m_PenStyle);
	DDX_Control(pDX, IDC_SHAPES, m_ShapesCombo);
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


// обработчики сообщений CPaintORamaDlg

BOOL CPaintORamaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

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

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CPaintORamaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CPaintORamaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPaintORamaDlg::OnClickedClearbtn()
{
	// TODO: добавьте свой код обработчика уведомлений

	CClientDC dc(this);

	dc.SelectStockObject(NULL_PEN);

	dc.Rectangle(m_Canvas);
}

void CPaintORamaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
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
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
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
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	
	//Отключить режим рисования
	m_IsDrawing = FALSE;

	/*Если мышка отпущена внутри области рисования, то нарисовать фигуру окончательно*/
	if (m_Canvas.PtInRect(point))
	{
		m_LineEnd = point;
		DrawShape();
	}
	//Если нет, то стереть
	else
	{
		DrawShape(true);
	}

	m_LineStart = point;

	//Отпустить мышь
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CPaintORamaDlg::OnStnClickedPencolor()
{
	// TODO: добавьте свой код обработчика уведомлений
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
	//Получить объект контекста устройства
	CClientDC dc(this);

	//Установить атрибуты DC
	dc.SetAttribDC(dc);
	dc.IntersectClipRect(m_Canvas);

	//Получить номер позиции из спика названий фигур
	int drawmode = m_ShapesCombo.GetCurSel();
	
	//Выбрать перо
	dc.SelectObject(&m_Pen);

	//Метод резиновой нити
	if (stretch && (drawmode != 0))
	{
		//Установить метод резиновой нити
		dc.SetROP2(R2_NOT);
	}

	//Конструкция выбора фигуры
	switch (drawmode)
	{
		//Свободное рисование
	case 0:
		dc.MoveTo(m_LineStart);
		dc.LineTo(m_LineEnd);
		m_LineStart = m_LineEnd;
		break;
		//Рисование линий
	case 1:
		dc.MoveTo(m_LineStart);
		dc.LineTo(m_LineEnd);
		break;
		//Рисование элипсов
	case 2:
		dc.Ellipse(CRect(m_LineStart, m_LineEnd));
		break;
		//Рисование прямоугольника
	case 3:
		dc.Rectangle(CRect(m_LineStart, m_LineEnd));
		break;
	}

}