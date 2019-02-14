/* Cutter
Copyright(C) 2019 R Bruce Porteous

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
#pragma once
#include "afxwin.h"

struct CutterConfig;
class CCutterDlg;

// CConfigDialog dialog

class CConfigDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigDialog)
	CutterConfig* config;
	Cutter* pCutter;

public:
	CConfigDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigDialog();

	void initialize(CCutterDlg* pCutter);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox defaultComPort;
	CButton connectAutomatically;
	CButton listenAutomatically;
	afx_msg void OnBnClickedBtnUpdateCutter();
	afx_msg void OnBnClickedBtnSaveConfig();
	afx_msg void OnBnClickedChkConnectAuto();
	afx_msg void OnBnClickedChkListenAuto();
	afx_msg void OnCbnSelchangeCmbDefaultCom();
};
