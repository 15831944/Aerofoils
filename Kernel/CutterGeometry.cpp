#include "CutterGeometry.h"
#include "ObjectSerializer.h"


CutterGeometry::CutterGeometry()
	: width(1000)
	, blockLeft(100)
	, blockRight(900)
	, xTravel(500)
	, yTravel(200)
{
	setGeometry();
}


CutterGeometry::~CutterGeometry()
{
}

void CutterGeometry::setWidth(double width) {
	this->width = width; 
	setGeometry();
}

void CutterGeometry::setBlockLeft(double blockLeft) {
	this->blockLeft = blockLeft; 
	setGeometry();
}

void CutterGeometry::setBlockRight(double blockRight) {
	this->blockRight = blockRight; 
	setGeometry();
}

void CutterGeometry::setXTravel(double xTravel) {
	this->xTravel = xTravel; 
}

void CutterGeometry::setYTravel(double yTravel) {
	this->yTravel = yTravel; 
}


void CutterGeometry::blockToAxes(Position<double>& pos) {
	double x = pos.x;
	double y = pos.y;
	double u = pos.u;
	double v = pos.v;

	pos.x = (x * wr - u * wl) / wd;
	pos.u = (u * wl1 - x * wr1) / wd;
	pos.y = (y * wr - v * wl) / wd;
	pos.v = (v * wl1 - y * wr1) / wd;
}

void CutterGeometry::setGeometry() {
	wl = getBlockLeft();
	wr = getBlockRight();

	wl1 = getWidth() - wl;
	wr1 = getWidth() - wr;
	wd = wr - wl;

}

void CutterGeometry::serializeTo(CObjectSerializer & os)
{
	os.startSection("cutterGeometry", this);
	os.write("width", width);
	os.write("blockLeft", blockLeft);
	os.write("blockRight", blockRight);
	os.write("xTravel", xTravel);
	os.write("yTravel", yTravel);
	os.endSection();
}

void CutterGeometry::serializeFrom(CObjectSerializer & os)
{
	os.startReadSection("cutterGeometry", this);
	os.read("width", width);
	os.read("blockLeft", blockLeft);
	os.read("blockRight", blockRight);
	os.read("xTravel", xTravel);
	os.read("yTravel", yTravel);
	os.endReadSection();
	setGeometry();
}
