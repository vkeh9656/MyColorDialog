
// MyColorDialogDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MyColorDialog.h"
#include "MyColorDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyColorDialogDlg 대화 상자



CMyColorDialogDlg::CMyColorDialogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYCOLORDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyColorDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyColorDialogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SELECT_COLOR_BTN, &CMyColorDialogDlg::OnBnClickedSelectColorBtn)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CMyColorDialogDlg 메시지 처리기

BOOL CMyColorDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMyColorDialogDlg::OnPaint()
{
	if (IsIconic())
	{	
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		 CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMyColorDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyColorDialogDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CRect r(10, 10, 60, 40);
	//if (r.PtInRect(point)) // 마우스로 클릭한 좌표가 영역 안에 들어있으면 if문 안에 들어옴
	//{
	//	CColorDialog ins_dlg;
	//	ins_dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	//	ins_dlg.m_cc.rgbResult = m_user_color; // CC_RGBINIT 플래그가 세팅되있어야만 사용 가능
	//	
	//	if (IDOK == ins_dlg.DoModal())
	//	{
	//		m_user_color = ins_dlg.GetColor();
	//		InvalidateRect(r);
	//	}
	//}

	//CDialogEx::OnLButtonDown(nFlags, point);
}


void CMyColorDialogDlg::OnBnClickedSelectColorBtn()
{
	CColorDialog ins_dlg;
	ins_dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	ins_dlg.m_cc.rgbResult = m_user_color; // CC_RGBINIT 플래그가 세팅되있어야만 사용 가능

	if (IDOK == ins_dlg.DoModal())
	{
		m_user_color = ins_dlg.GetColor();
		GetDlgItem(IDC_SELECT_COLOR_BTN)->Invalidate();
	}
}


void CMyColorDialogDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpds) // OwnerDraw 체크
{
	if (nIDCtl == IDC_SELECT_COLOR_BTN)
	{
		CDC* p_dc = CDC::FromHandle(lpds->hDC);
		p_dc->FillSolidRect(&lpds->rcItem, RGB(228, 228, 228));
		CString str;
		GetDlgItemText(IDC_SELECT_COLOR_BTN, str);

		CRect r(lpds->rcItem);
		CRect color_rect(lpds->rcItem.left + 3, lpds->rcItem.top + 3, lpds->rcItem.right - 3, lpds->rcItem.bottom - 3);
		if (lpds->itemState & ODS_SELECTED) // 현재 이 아이템이 선택되어져 있는가?
		{
			r -= CPoint(1, 1);
			color_rect -= CPoint(1, 1);
			p_dc->Draw3dRect(&lpds->rcItem, RGB(210, 210, 210), RGB(238, 238, 238));
		}
		else
		{
			p_dc->Draw3dRect(&lpds->rcItem, RGB(248, 248, 248), RGB(128, 128, 128));
		}

		p_dc->SetBkMode(TRANSPARENT);
		p_dc->SetTextColor(m_user_color);
		p_dc->DrawText(str, r, DT_CENTER | DT_VCENTER | DT_SINGLELINE); // 한줄짜리 옵션에만 V-center 옵션이 먹음, 그래서 singleline 들어감

		
		p_dc->Draw3dRect(color_rect, m_user_color, m_user_color);
	}

	CDialogEx::OnDrawItem(nIDCtl, lpds);
}
