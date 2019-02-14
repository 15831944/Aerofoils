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
// WindowsUIProxy.cpp: implementation of the CWindowsUIProxy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "aerofoil.h"
#include "WindowsUIProxy.h"
#include "PlotFlagsDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWindowsUIProxy::CWindowsUIProxy()
{

}

CWindowsUIProxy::~CWindowsUIProxy()
{

}

bool CWindowsUIProxy::EditPlotFlags(CPlotStructure* toEdit)
{
	CPlotFlagsDlg dlg(toEdit);
	return dlg.DoModal() == IDOK;
}