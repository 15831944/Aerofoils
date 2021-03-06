/* Aerofoil
Aerofoil plotting and CNC cutter driver
Kernel / core algorithms
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

/*
CPlotStructure class to provide a common interface for plotting some type of structure
to paper.  Compare with CutStructure which is the analogue for driving CNC.
*/

#if !defined(AFX_PLOTSTRUCTURE_H__D83773A2_BA49_11D6_AF75_002018BA082E__INCLUDED_)
#define AFX_PLOTSTRUCTURE_H__D83773A2_BA49_11D6_AF75_002018BA082E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "Kernel.h"
#include "PointT.h"
#include "RectT.h"
#include "OutputDevice.h"
#include "Structure.h"
#include "StructureOutput.h"

class CObjectSerializer;
class CUIProxy;

class CPlotStructure : public StructureOutput
{
public:
	CPlotStructure();
	virtual ~CPlotStructure();

	virtual void plot(COutputDevice *pdev) = 0;
	virtual std::string getDescriptiveText() const = 0;
	virtual CStructure* getStructure() = 0;
	virtual const CStructure* getStructure() const = 0;

	inline NumericT getSpan() const {	return getStructure()->getSpan(); }
	RectT getBounds();
	NumericT getSectionPos() const;
	void setSectionPos(NumericT pos);

	void setRootSide(bool isLeft);
	bool isRootLeft() const {return rootIsOnLeft;}

	void setInvert(bool inv);
	bool isInverted() const {return invert;}

	void setReflect(bool ref);
	bool isReflected() const {return reflect;}
	
	void setInterpolate(bool inter);
	void setUIProxy(CUIProxy* pp);
	CUIProxy* getUIProxy();

	void setPosition(NumericT x, NumericT y);
	NumericT getX() const { return xpos; }
	NumericT getY() const { return ypos; }
	

	virtual void serializeTo(CObjectSerializer& os);
	virtual void serializeFrom(CObjectSerializer& os);

	// Structure output
	virtual void move(COutputDevice* pdev, const PointT& root, const PointT& tip);
	virtual void line(COutputDevice* pdev, const PointT& root, const PointT& tip);

protected:
	PointT interpolate(const PointT& root, const PointT& tip) const;
	void interp_move_to(COutputDevice* pdev, const PointT& root, const PointT& tip) const;
	void interp_line_to(COutputDevice* pdev, const PointT& root,const PointT& tip) const;
	void LabelAt(COutputDevice* pdev, const PointT& where, const std::string& text, bool atRoot) const;

private:

	PointT offset(PointT pos) const;

	NumericT xpos,ypos;	// position of section on plot
	NumericT section_pos;		// position for cross section.
	bool shouldInterpolate;

	bool rootIsOnLeft;
	int root_stream;
	int tip_stream;

	bool invert;	// top to bottom
	bool reflect;	// left to right

	CUIProxy* proxy;		// UI implementation

};

#endif // !defined(AFX_PLOTSTRUCTURE_H__D83773A2_BA49_11D6_AF75_002018BA082E__INCLUDED_)
