/************************************************************************
	
	xStringCapture.cpp - Copyright (c) 2008 The MWSE Project
	http://www.sourceforge.net/projects/mwse

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

**************************************************************************/

#include "VMExecuteInterface.h"
#include "Stack.h"
#include "InstructionInterface.h"
#include "Reference.h"
#include "Log.h"
#include "StringUtil.h"

#include <regex>

using namespace mwse;

namespace mwse
{
	class xStringCapture : mwse::InstructionInterface_t
	{
	public:
		xStringCapture();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static xStringCapture xStringCaptureInstance;

	xStringCapture::xStringCapture() : mwse::InstructionInterface_t(OpCode::xStringCapture) {}

	void xStringCapture::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xStringCapture::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		// Get parameters from stack.
		mwseString_t& string = virtualMachine.getString(Stack::getInstance().popLong());
		mwseString_t& pattern = virtualMachine.getString(Stack::getInstance().popLong());
		mwLong_t desiredMatches = Stack::getInstance().popLong();

		// Go and try to get all of our matches, to a limit of the count given to us as our 3rd parameter.
		mwLong_t matchesReturned = 0;
		try {
			std::regex regex_pattern(pattern, std::regex::extended);
			std::smatch regex_matches;
			if (std::regex_match(string, regex_matches, regex_pattern)) {
				for (size_t i = 0; i < regex_matches.size(); i++) {
					// Bail out if we're past our desired number of matches.
					if (matchesReturned >= desiredMatches) {
						break;
					}

					// Bring the match into string storage and push it back to mwscript.
					mwseString_t& match = mwse::string::store::getOrCreate(regex_matches[i].str());
					mwse::Stack::getInstance().pushString(match);
					matchesReturned++;
				}
			}
		}
		catch (std::regex_error& e) {
			mwse::log::getLog() << "xStringCapture: A regex exception has occurred. " << e.what() << std::endl;
		}

		// If we didn't get enough matches, pad it out with zeros.
		while (matchesReturned < desiredMatches) {
			mwse::Stack::getInstance().pushLong(0);
		}

		return 0.0f;
	}
}