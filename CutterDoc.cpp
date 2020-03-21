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

// CutterDoc.cpp : implementation file
//

#include "stdafx.h"
#include <assert.h>
#include <fstream>
#include "Aerofoil.h"
#include "CutterDoc.h"
#include "CutterView.h"
#include "BackgroundGridDlg.hpp"
#include "CNCConnectionDlg.h"
#include "ToolOffsetDialog.h"
#include "FeedRateDialog.h"
#include "Kernel\Wing.h"
#include "Kernel\EllipsePair.h"
#include "Kernel\PointStructure.h"
#include "Kernel\GCodeSnippet.h"
#include "Kernel\DXFObject.h"
#include "Kernel\GCodeOutputFile.h"
#include "Kernel\CNCConnectionOutputDevice.h"
#include "Kernel\ObjectSerializer.h"

// CutterDoc

IMPLEMENT_DYNCREATE(CutterDoc, CDocument)

CutterDoc::CutterDoc()
	: cncHost("localhost")
	, cncPort(8193)
	, cncIsSetup(false)
{
	grid.setHorizontalSize(10);
	grid.setVerticalSize(10);
	grid.enableHorizontal(true);
	grid.enableVertical(true);
}

CWing * CutterDoc::newWing(const char * pszRootName, float rootThickness, const char * pszTipName, float tipThickness)
{
	CWing* pWing = new CWing(pszRootName, 1.0f, pszTipName, 1.0f);
	cut.addStructure(pWing);
	return pWing;
}

CEllipsePair * CutterDoc::newEllipse(CEllipsePair & example)
{
	CEllipsePair* pEllipses = new CEllipsePair(example);
	cut.addStructure(pEllipses);
	return pEllipses;
}

CPointStructure * CutterDoc::newPoint(CPointStructure & example)
{
	CPointStructure* pPoints = new CPointStructure(example);
	cut.addStructure(pPoints);
	return pPoints;
}

GCodeSnippet * CutterDoc::newGcodeSnippet(const char * text)
{
	GCodeSnippet* pSnippet = new GCodeSnippet(text);
	cut.addStructure(pSnippet);
	return pSnippet;
}

DXFObject * CutterDoc::newDxfObject(const char * pszPath)
{
	DXFObject* pdxf = new DXFObject(pszPath);
	cut.addStructure(pdxf);
	return pdxf;
}

void CutterDoc::deleteStructure(CStructure * pStructure)
{
	assert(this);
	assert(pStructure);
	cut.deleteStructure(pStructure);
}

CPathCutter * CutterDoc::newPathCutter(CWing * pStructure)
{
	return cut.addPathCutter(pStructure);
}

EllipseCutter * CutterDoc::newElipseCutter(CEllipsePair * pEllipses)
{
	return cut.addEllipseCutter(pEllipses);
}

PointCutter * CutterDoc::newPointCutter(CPointStructure * pPoints)
{
	return cut.addPointCutter(pPoints);
}

DXFObjectCutter * CutterDoc::newDXFObjectCutter(DXFObject* pdxf)
{
	return cut.addDXFObjectCutter(pdxf);
}

GCodeSnippetCutter * CutterDoc::newGCodeSnippetCutter(GCodeSnippet* pgcode)
{
	return cut.addGCodeSnippetCutter(pgcode);
}

HomeCutter * CutterDoc::newHomePosition()
{
	return cut.addHomePosition();
}

void CutterDoc::deleteCut(CutStructure * pCut)
{
	assert(this);
	assert(pCut);
	cut.deleteCut(pCut);
}

void CutterDoc::runCut(COutputDevice& pdev)
{
	cut.cut(pdev);
}



CutterDoc::~CutterDoc()
{
}


BEGIN_MESSAGE_MAP(CutterDoc, CDocument)
	ON_COMMAND(ID_FILE_SETGRID, &CutterDoc::OnFileSetgrid)
	ON_COMMAND(ID_FILE_CNCOUTPUT, &CutterDoc::OnFileCncoutput)
	ON_COMMAND(ID_FILE_CNCSETUP, &CutterDoc::OnFileCncsetup)
	ON_COMMAND(ID_FILE_GCODE, &CutterDoc::OnFileGcode)
	ON_COMMAND(ID_CUTTER_TOOLOFFSET, &CutterDoc::OnCutterTooloffset)
	ON_COMMAND(ID_CUTTER_FEEDRATE, &CutterDoc::OnCutterFeedrate)
END_MESSAGE_MAP()

BOOL CutterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

BOOL CutterDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	assert(this);
	assert(lpszPathName);

	BOOL success = TRUE;
	try
	{
		std::fstream ifs(lpszPathName, std::ios_base::in);
		CObjectSerializer serializer(&ifs);
		serializer.startReadSection("cutter", this);
		grid.serializeFrom(serializer);
		geometry.serializeFrom(serializer);
		cut.serializeFrom(serializer);
		serializer.endReadSection();
	}
	catch (CSerializeException& se)
	{
		::MessageBox(0, se.what(), "Unable to read cutter file", MB_OK | MB_ICONERROR);
		success = FALSE;
	}
	catch (...)
	{
		::MessageBox(0, "Error opening or parsing input", "Unable to read cutter file", MB_OK | MB_ICONERROR);
		success = FALSE;
	}
	return success;
}


BOOL CutterDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	assert(this);
	assert(lpszPathName);

	BOOL success = TRUE;
	try
	{
		std::fstream ofs(lpszPathName, std::ios_base::out);
		CObjectSerializer serializer(&ofs);
		serializer.startSection("cutter", this);
		grid.serializeTo(serializer);
		geometry.serializeTo(serializer);
		cut.serializeTo(serializer);
		serializer.endSection();
	}
	catch (...)
	{
		success = FALSE;
	}
	return success;
}


// CutterDoc serialization

void CutterDoc::Serialize(CArchive& ar)
{
	assert(false);	// serialization handled in OnOpenDocument, OnSaveDocument
}

// CutterDoc diagnostics

#ifdef _DEBUG
void CutterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CutterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

void CutterDoc::UpdateNow()
{
	assert(this);
	POSITION pos = GetFirstViewPosition();
	while (pos)
	{
		CView* pView = GetNextView(pos);
		ASSERT_VALID(pView);
		pView->UpdateWindow();
	}
	return;
}

void CutterDoc::RedrawNow()
{
	assert(this);
	POSITION pos = GetFirstViewPosition();
	while (pos)
	{
		CView* pView = GetNextView(pos);
		ASSERT_VALID(pView);
		pView->RedrawWindow();
	}
	return;
}

void CutterDoc::geometryUpdated()
{
	assert(this);

	POSITION pos = GetFirstViewPosition();
	while (pos)
	{
		CView* pView = GetNextView(pos);
		ASSERT_VALID(pView);
		if (pView->IsKindOf(RUNTIME_CLASS(CutterView))) {
			static_cast<CutterView*>(pView)->DocSizeChanged();
		}
	}

	RedrawNow();

}



// CutterDoc commands


void CutterDoc::OnFileSetgrid()
{
	CBackgroundGridDlg dlg;
	dlg.m_blPlotHoriz = grid.isHorizontalEnabled();
	dlg.m_blPlotVert = grid.isVerticalEnabled();
	dlg.m_fHorizDistance = grid.getHorizontalSize();
	dlg.m_fVertDistance = grid.getVerticalSize();

	if (dlg.DoModal() == IDOK)
	{
		grid.enableHorizontal(dlg.m_blPlotHoriz != 0);
		grid.enableVertical(dlg.m_blPlotVert != 0);
		grid.setHorizontalSize(dlg.m_fHorizDistance);
		grid.setVerticalSize(dlg.m_fVertDistance);
		RedrawNow();
	}

}


void CutterDoc::OnFileCncoutput()
{
	if (!cncIsSetup)
		OnFileCncsetup();

	if (cncIsSetup)
	{
		try
		{
			CCNCConnectionOutputDevice dev(cncHost.c_str(), cncPort);
			cut.cut(dev);
		}
		catch (std::exception& e)
		{
			::MessageBox(0, e.what(), "Error during plot", MB_OK | MB_ICONEXCLAMATION);
		}
	}
}


void CutterDoc::OnFileCncsetup()
{
	CCNCConnectionDlg dlg;
	dlg.m_host = cncHost.c_str();
	dlg.m_port = cncPort;
	if (dlg.DoModal() == IDOK)
	{
		cncHost = dlg.m_host;
		cncPort = dlg.m_port;
		cncIsSetup = true;
	}
}


void CutterDoc::OnFileGcode()
{
	assert(this);

	CFileDialog dlg(FALSE,
		".GCODE",
		NULL,
		OFN_HIDEREADONLY,
		"G-CODE Files (.GCODE)|*.GCODE||"
	);

	if (dlg.DoModal() == IDOK)
	{
		GCodeOutputFile dev(LPCTSTR(dlg.GetPathName()));
		cut.cut(dev);
	}
}


void CutterDoc::OnCutterTooloffset()
{
	ToolOffsetDialog dlg;
	dlg.toolOffset = cut.getToolOffset();
	if (dlg.DoModal() == IDOK) {
		cut.setToolOffset(dlg.toolOffset);
		RedrawNow();
	}
}


void CutterDoc::OnCutterFeedrate()
{
	FeedRateDialog dlg;
	dlg.feedRate = cut.getFeedRate();
	dlg.useFeedRate = cut.isUseFeedRate() ? TRUE : FALSE;
	if (dlg.DoModal() == IDOK) {
		cut.setFeedRate(dlg.feedRate);
		cut.setUseFeedRate(dlg.useFeedRate == TRUE);
	}
}