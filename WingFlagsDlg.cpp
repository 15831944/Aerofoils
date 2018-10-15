// WingFlagsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Aerofoil.h"
#include "WingFlagsDlg.h"

#include "kernel/PlotFlags.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWingFlagsDlg dialog


CWingFlagsDlg::CWingFlagsDlg(CPlotFlags* pf, CWnd* pParent /*=NULL*/)
	: CDialog(CWingFlagsDlg::IDD, pParent)
	, flags(pf)
{
	//{{AFX_DATA_INIT(CWingFlagsDlg)
	m_blPlotChord = FALSE;
	m_blPlotLabels = FALSE;
	m_blPlotMarkers = FALSE;
	m_blPlotSection = FALSE;
	m_blPlotSkin = FALSE;
	m_blPlotSpars = FALSE;
	m_blPlotTE = FALSE;
	m_blPlotLE = FALSE;
	//}}AFX_DATA_INIT
}


void CWingFlagsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWingFlagsDlg)
	DDX_Check(pDX, IDC_CHK_PLOT_CHORD, m_blPlotChord);
	DDX_Check(pDX, IDC_CHK_PLOT_LABELS, m_blPlotLabels);
	DDX_Check(pDX, IDC_CHK_PLOT_MARKERS, m_blPlotMarkers);
	DDX_Check(pDX, IDC_CHK_PLOT_SECTION, m_blPlotSection);
	DDX_Check(pDX, IDC_CHK_PLOT_SKIN, m_blPlotSkin);
	DDX_Check(pDX, IDC_CHK_PLOT_SPARS, m_blPlotSpars);
	DDX_Check(pDX, IDC_CHK_PLOT_TE, m_blPlotTE);
	DDX_Check(pDX, IDC_CHK_PLOT_LE, m_blPlotLE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWingFlagsDlg, CDialog)
	//{{AFX_MSG_MAP(CWingFlagsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWingFlagsDlg message handlers

void CWingFlagsDlg::OnOK() 
{
	if(UpdateData())
	{
		flags->plot_section =	m_blPlotSection != FALSE;  /* True if intermediate sect wanted */
		flags->plot_skin =		m_blPlotSkin != FALSE;     /* True if skin thickness plot */
		flags->plot_chord =		m_blPlotChord != FALSE;    /* True if chord plot wanted */
		flags->plot_markers =	m_blPlotMarkers != FALSE;  /* True if 10% markers wanted */
		flags->plot_spars =		m_blPlotSpars != FALSE;    /* True if plot of spars wanted */
		flags->plot_le =		m_blPlotLE != FALSE;       /* True if LE wanted */
		flags->plot_te =		m_blPlotTE != FALSE;       /* True if TE wanted */
		flags->plot_labels =	m_blPlotLabels != FALSE;   /* True if annotated drawing wanted */

		CDialog::OnOK();
	}
}

BOOL CWingFlagsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_blPlotSection = (flags->plot_section 	) ? TRUE : FALSE;  /* True if intermediate sect wanted */
	m_blPlotSkin	= (flags->plot_skin 	) ? TRUE : FALSE;     /* True if skin thickness plot */
	m_blPlotChord	= (flags->plot_chord 	) ? TRUE : FALSE;    /* True if chord plot wanted */
	m_blPlotMarkers = (flags->plot_markers 	) ? TRUE : FALSE;  /* True if 10% markers wanted */
	m_blPlotSpars	= (flags->plot_spars 	) ? TRUE : FALSE;    /* True if plot of spars wanted */
	m_blPlotLE		= (flags->plot_le 		) ? TRUE : FALSE;       /* True if LE wanted */
	m_blPlotTE		= (flags->plot_te 		) ? TRUE : FALSE;       /* True if TE wanted */
	m_blPlotLabels	= (flags->plot_labels 	) ? TRUE : FALSE;   /* True if annotated drawing wanted */
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}