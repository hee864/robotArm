
// RobotExp_4Dlg.h : 헤더 파일
//

#pragma once
#include "Comm.h"
#include "CommWork.h"
#include "DeviceListReader.h"

#include "GraphDlg.h"
#include "afxwin.h"

#include "ThreadWorker.h"
#include "SharedMemory.h"
#include "SystemMemory.h"
#include "DataType.h"

// CRobotExp_4Dlg 대화 상자
class CRobotExp_4Dlg : public CDialogEx
{
// 생성입니다.
public:
	CRobotExp_4Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROBOTEXP_4_DIALOG };
#endif

private:
	double L_1 = 0.5;
	double L_2 = 0.45;

	CGraphDlg* m_pGraphDlg;

// 구현입니다.
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	HICON m_hIcon;
	CComm m_comm;
	CThreadedWorker _commWorker;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void SolveForwardKinematics(double dAngle, double dAngle2, double* pdPos);
	void SolveInverseKinematics(double dX, double dY, double dZ, double* pdAngle);

	CComboBox m_ComboPort;
	CComboBox m_ComboBaud;
	afx_msg void OnCbnDropdownComboPort();
	CButton m_CheckOpen;
	afx_msg void OnBnClickedCheckOpen();


	CEdit m_EditSend;
	CEdit m_EditRecv;
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	CEdit m_editTarPos1;
	CEdit m_editCurPos1;
	CEdit m_editTarPos2;
	CEdit m_editCurPos2;
	CEdit m_editTarVel;
	CEdit m_editCurVel;
	CEdit m_editTarTorq;
	CEdit m_editCurTorq;
	CEdit m_editTarX;
	CEdit m_editCurX;
	CEdit m_editTarY;
	CEdit m_editCurY;
	CEdit m_editTarZ;
	CEdit m_editCurZ;
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonForward();
	afx_msg void OnBnClickedButtonInverse();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonGraph();
	afx_msg void OnBnClickedButtonSet();
};
