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

#include "stdafx.h"
#include<assert.h>
#include "GCodeInterpreter.h"
#include "GCodeProgram.h"


GCodeProgram::GCodeProgram(GCodeInterpreter* pi) :
	pInterpreter(pi),
	bPaused(false),
	bComplete(false),
	bRunning(false),
	upstreamContext(0)
{
}


GCodeProgram::~GCodeProgram()
{
}

void GCodeProgram::setInterpreter(GCodeInterpreter* pInterpreter)
{
	assert(this);
	assert(pInterpreter);
	this->pInterpreter = pInterpreter;
}

void GCodeProgram::setUpstreamContext(ParserContext * upstreamContext)
{
	this->upstreamContext = upstreamContext;
}

void GCodeProgram::showError(const std::string & line, size_t where, const std::string & msg)
{
	assert(this);
	std::string error(msg);
	error.append(" : ");
	error.append(line.substr(0, where));
	error.append(">>>");
	error.append(line.substr(where));
	errors.push_back(error);
	if (upstreamContext) {
		upstreamContext->showError(line, where, msg);
	}
}

boolean GCodeProgram::canPause() {
	if (upstreamContext) {
		upstreamContext->canPause();
	}
	return bPausable;
}

void GCodeProgram::pause()
{
	bPaused = true;
	if (upstreamContext) {
		upstreamContext->pause();
	}

}

void GCodeProgram::complete()
{
	assert(this);
	bComplete = true;
	if (upstreamContext) {
		upstreamContext->complete();
	}

}

void GCodeProgram::restart()
{
	assert(this);
	bRunning = true;
	bComplete = false;
	bPaused = true;
	errors.clear();
	currentLine = lines.begin();
	if (upstreamContext) {
		upstreamContext->restart();
	}

}

void GCodeProgram::clear()
{
	assert(this);
	lines.clear();
	errors.clear();
	bRunning = false;
	bComplete = false;
	bPaused = false;
	currentLine = lines.end(); // will abort any runnign program.
}

void GCodeProgram::add(const std::string & line)
{
	lines.push_back(line);
}

std::string GCodeProgram::nextLine()
{
	if (currentLine == lines.end()) {
		return std::string("");
	}
	return *currentLine;
}

void GCodeProgram::start()
{
	assert(this);
	assert(pInterpreter);
	
	pInterpreter->setContext(this);
	errors.clear();
	currentLine = lines.begin();
	bRunning = true;
	bComplete = false;
	bPaused = true;
}

boolean GCodeProgram::step()
{
	if (currentLine != lines.end()) {
		pInterpreter->process(*currentLine);
		++currentLine;
		if (currentLine == lines.end()) {
			bComplete = true;
			bPaused = false;
			bRunning = false;
		}
	}
	return !bComplete;
}

void GCodeProgram::reset()
{
	bComplete = false;
	bPaused = false;
	bRunning = false;
	currentLine = lines.end();
}

void GCodeProgram::load(std::istream & is)
{
	std::string line;
	while (std::getline(is, line)) {
		lines.push_back(line);
	}
	bRunning = false;
	bComplete = false;
	bPaused = false;
}

void GCodeProgram::save(std::ostream & os)
{
	for (auto const& line : lines) {
		os << line << std::endl;
	}
}

void GCodeProgram::asString(std::string & str)
{
	str = "";
	for (auto const&l : lines) {
		str.append(l);
		str.append("\r\n");
	}
}
