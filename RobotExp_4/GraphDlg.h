#pragma once
#include "NTGraph.h"
#include "CNTGRAPH_POS.h"
#include "CNTGRAPH_VEL.h"
#include "CNTGRAPH_TORQ.h"

/// 추가 ///
#include "SystemMemory.h"
#include "SharedMemory.h"
#include "DataType.h"

#define RED		RGB(127, 0, 0)
#define GREEN	RGB(0, 127, 0)
#define BLUE	RGB(0, 0, 127)

#define BLACK	RGB(0, 0, 0)
#define WHITE	RGB(255, 255, 255)

// CGraphDlg 대화 상자입니다.

class CGraphDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphDlg)

public:
	CGraphDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGraphDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	/// 수정해야함 ///
	CNTGraph m_ntgPos;
	CNTGraph m_ntgVel;
	CNTGraph m_ntgTorq;

	//CNTGRAPH_POS m_ntgPos;
	//CNTGRAPH_VEL m_ntgVel;
	//CNTGRAPH_TORQ m_ntgTorq;

	afx_msg void OnTimer(UINT_PTR nIDEvent);

/// <summary>
///  추가해야함... 강의 자료에 없음
/// </summary>
/// 
	virtual BOOL OnInitDialog();

private:
	void InitNTGraph();

	double m_dCnt = 0.00;
};
