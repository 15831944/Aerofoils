/* Aerofoil
Aerofoil plotting and CNC cutter driver
Copyright(C) 1995-2019 R Bruce Porteous

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
#if !defined(AFX_WINGDLG_H__1103E541_BB64_11D6_AF75_002018BA082E__INCLUDED_)
#define AFX_WINGDLG_H__1103E541_BB64_11D6_AF75_002018BA082E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WingDlg.h : header file
//

#include "AerofoilPreviewControl.h"
#include "kernel/Wing.h"

/////////////////////////////////////////////////////////////////////////////
// CWingDlg dialog

class CWingDlg : public CDialog
{
// Construction
public:
	CWingDlg(CWing* w, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWingDlg)
	enum { IDD = IDD_EDIT_WING };
	CListBox	m_lstSpars;
	float	m_LE;
	float	m_span;
	float	m_TE;
	float	m_fSkin;
	//}}AFX_DATA
	CListBox m_lstCutouts;
	AerofoilPreviewControl rootSection;
	AerofoilPreviewControl tipSection;
	double rootChord;
	double rootSweep;
	double rootWashout;
	double rootThickness;
	double tipChord;
	double tipSweep;
	double tipHeight;
	double tipWashout;
	double tipThickness;
	double rootHeight;
	CStatic lblRootInfo;
	CStatic lblTipInfo;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void addSparToList(CSpar* ps);
	void addCutoutToList(Cutout* pc);

	// Generated message map functions
	//{{AFX_MSG(CWingDlg)
	afx_msg void OnCmdAddSpar();
	afx_msg void OnCmdSparDelete();
	afx_msg void OnCmdSparEdit();
	afx_msg void OnSelchangeLstSpars();
	afx_msg void OnDblclkLstSpars();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CWing* wing;
	CWing wingCopy;	// local copy to edit, update wing if ok.
public:
	afx_msg void OnBnClickedBtnAddCutout();
	afx_msg void OnBnClickedBtnEditCutout();
	afx_msg void OnBnClickedBtnDeleteCutout();
	afx_msg void OnLbnDblclkLstCutouts();
	afx_msg void OnBnClickedCmdRootSectionName();
	afx_msg void OnBnClickedCmdTipSectionName();
	afx_msg void OnKillfocusEdtRootChord();
	afx_msg void OnKillfocusEdtRootThicknessMod();
	afx_msg void OnKillfocusEdtRootWashout();
	afx_msg void OnKillfocusEdtSkin();
	afx_msg void OnKillfocusEdtSpan();
	afx_msg void OnKillfocusEdtTipChord();
	afx_msg void OnKillfocusEdtTipThicknessMod();
	afx_msg void OnKillfocusEdtTipWashout();
	afx_msg void OnKillfocusEdtLe();
	afx_msg void OnKillfocusEdtTe();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINGDLG_H__1103E541_BB64_11D6_AF75_002018BA082E__INCLUDED_)
