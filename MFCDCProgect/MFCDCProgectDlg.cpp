
// MFCDCProgectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCDCProgect.h"
#include "MFCDCProgectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCDCProgectDlg 对话框



CMFCDCProgectDlg::CMFCDCProgectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCDCPROGECT_DIALOG, pParent)
	, Maze_Length(0)
	, Maze_Width(0)
	, Message(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDCProgectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Maze_Length);
	DDX_Text(pDX, IDC_EDIT2, Maze_Width);
	DDX_Text(pDX, IDC_EDIT3, Message);
}

BEGIN_MESSAGE_MAP(CMFCDCProgectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCDCProgectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCDCProgectDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCDCProgectDlg 消息处理程序

BOOL CMFCDCProgectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCDCProgectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCDCProgectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDCProgectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDCProgectDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	
	
	UpdateData(TRUE);
	CWnd *pWnd = GetDlgItem(Maze_Show);
	CEdit *write = (CEdit*)GetDlgItem(IDC_EDIT3);
	write->SetWindowTextW(_T("迷宫生成中，请等待"));
	//Message = "迷宫生成中，请等待";
	//UpdateData(FALSE);

	CDC *wall = pWnd->GetDC();
	CBrush brush(RGB(255,255,255));
	wall->SelectObject(brush);
	CRect rect;
	pWnd->GetClientRect(&rect);
	wall->Rectangle(rect);

	delete m;
	m = new MazeProject(Maze_Width, Maze_Length, pWnd);
	m->MazeCreat();
	write->SetWindowTextW(_T("迷宫生成完成!"));
	//Message = "迷宫生成完成!";
	//UpdateData(FALSE);
}


void CMFCDCProgectDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *pWnd = GetDlgItem(Maze_Show);
	m->PathFind(pWnd);
	Message = "寻路完成!";
	UpdateData(FALSE);
}


