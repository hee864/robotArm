#pragma once
#include "NTGraph.h"
#include "CNTGRAPH_POS.h"
#include "CNTGRAPH_VEL.h"
#include "CNTGRAPH_TORQ.h"

/// �߰� ///
#include "SystemMemory.h"
#include "SharedMemory.h"
#include "DataType.h"

#define RED		RGB(127, 0, 0)
#define GREEN	RGB(0, 127, 0)
#define BLUE	RGB(0, 0, 127)

#define BLACK	RGB(0, 0, 0)
#define WHITE	RGB(255, 255, 255)

// CGraphDlg ��ȭ �����Դϴ�.

class CGraphDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphDlg)

public:
	CGraphDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGraphDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
//	/// �����ؾ��� ///
	CNTGraph m_ntgPos;
	CNTGraph m_ntgVel;
	CNTGraph m_ntgTorq;

	//CNTGRAPH_POS m_ntgPos;
	//CNTGRAPH_VEL m_ntgVel;
	//CNTGRAPH_TORQ m_ntgTorq;

	afx_msg void OnTimer(UINT_PTR nIDEvent);

/// <summary>
///  �߰��ؾ���... ���� �ڷῡ ����
/// </summary>
/// 
	virtual BOOL OnInitDialog();

private:
	void InitNTGraph();

	double m_dCnt = 0.00;
};
