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

#pragma once


// WingCoreFlagsDlg dialog
// Dialog to edit the subset of wing flags relevant to core cutting.
class WingCoreFlagsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WingCoreFlagsDlg)

public:
	WingCoreFlagsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~WingCoreFlagsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WING_CUT_FLAGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL cutLeadingEdge;
	BOOL cutTrailingEdge;
	BOOL cutSpars;
	BOOL cutCutouts;
};
