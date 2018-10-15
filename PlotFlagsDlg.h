#if !defined(AFX_PLOTFLAGSDLG_H__462C60A5_C8A0_11D6_955C_000000000000__INCLUDED_)
#define AFX_PLOTFLAGSDLG_H__462C60A5_C8A0_11D6_955C_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlotFlagsDlg.h : header file
//

class CPlotStructure;

/////////////////////////////////////////////////////////////////////////////
// CPlotFlagsDlg dialog

class CPlotFlagsDlg : public CDialog
{
// Construction
public:
	CPlotFlagsDlg(CPlotStructure* pps, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlotFlagsDlg)
	enum { IDD = IDD_PLOT_FLAGS };
	BOOL	m_blInvert;
	BOOL	m_blReflect;
	int		m_rootSide;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlotFlagsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlotFlagsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CPlotStructure* toEdit;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLOTFLAGSDLG_H__462C60A5_C8A0_11D6_955C_000000000000__INCLUDED_)