// GraphDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RobotExp_4.h"
#include "GraphDlg.h"
#include "afxdialogex.h"


// CGraphDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGraphDlg, CDialogEx)

CGraphDlg::CGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GRAPH_DIALOG, pParent)
{

}

CGraphDlg::~CGraphDlg()
{
}

void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NTGRAPH_POS, m_ntgPos);
	DDX_Control(pDX, IDC_NTGRAPH_VEL, m_ntgVel);
	DDX_Control(pDX, IDC_NTGRAPH_TORQ, m_ntgTorq);
}

BOOL CGraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitNTGraph();

	return TRUE;
}

BEGIN_MESSAGE_MAP(CGraphDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGraphDlg 메시지 처리기입니다.
void CGraphDlg::InitNTGraph()
{
	m_ntgPos.ClearGraph();
	m_ntgVel.ClearGraph();
	m_ntgTorq.ClearGraph();

	m_ntgPos.SetFrameStyle(0);
	m_ntgVel.SetFrameStyle(0);
	m_ntgTorq.SetFrameStyle(0);

	m_ntgPos.SetPlotAreaColor(WHITE);
	m_ntgVel.SetPlotAreaColor(WHITE);
	m_ntgTorq.SetPlotAreaColor(WHITE);

	m_ntgPos.SetShowGrid(TRUE);
	m_ntgVel.SetShowGrid(TRUE);
	m_ntgTorq.SetShowGrid(TRUE);

	m_ntgPos.SetFormatAxisBottom(_T("%.2f"));
	m_ntgVel.SetFormatAxisBottom(_T("%.2f"));
	m_ntgTorq.SetFormatAxisBottom(_T("%.2f"));

	m_ntgPos.SetCaption(_T("위치"));
	m_ntgVel.SetCaption(_T("속도"));
	m_ntgTorq.SetCaption(_T("토크"));

	m_ntgPos.SetXLabel(_T("Time[s]"));
	m_ntgVel.SetXLabel(_T("Time[s]"));
	m_ntgTorq.SetXLabel(_T("Time[s]"));

	m_ntgPos.SetYLabel(_T("Degree[deg]"));
	m_ntgVel.SetYLabel(_T("Velocity[deg/s]"));
	m_ntgTorq.SetYLabel(_T("Torque[Nm]"));

	//Position
	m_ntgPos.AddElement();
	m_ntgPos.SetElementWidth(3);
	m_ntgPos.SetElementLineColor(RED); //Target

	m_ntgPos.AddElement();
	m_ntgPos.SetElementWidth(3);
	m_ntgPos.SetElementLineColor(BLUE); //Current

	m_ntgPos.SetRange(0.0, 10.0, 0.0, 360.0);
	m_ntgPos.SetYGridNumber(4);

	//Velocity
	m_ntgVel.AddElement();
	m_ntgVel.SetElementWidth(4);
	m_ntgVel.SetElementLineColor(RED); //Target

	m_ntgVel.AddElement();
	m_ntgVel.SetElementWidth(3);
	m_ntgVel.SetElementLineColor(BLUE); //Current

	//Torque
	m_ntgTorq.AddElement();
	m_ntgTorq.SetElementWidth(4);
	m_ntgTorq.SetElementLineColor(RED); //Target

	m_ntgTorq.AddElement();
	m_ntgTorq.SetElementWidth(3);
	m_ntgTorq.SetElementLineColor(BLUE); //Current

	SetTimer(1, 100, NULL);
}

void CGraphDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_dCnt += 0.1;
	DataType_t jointData;
	GET_SYSTEM_MEMORY("JointData", jointData);

	if (m_dCnt >= 10.0)
	{
		m_ntgPos.SetRange(m_dCnt - 10.0, m_dCnt, 0.0, 360.0);
	}

	m_ntgPos.PlotXY(m_dCnt, jointData.Q_tar[0] * RAD2DEG, 1);
	m_ntgPos.PlotXY(m_dCnt, jointData.Q_cur[0] * RAD2DEG, 2);

	CDialogEx::OnTimer(nIDEvent);
}
