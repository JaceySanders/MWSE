/************************************************************************

	xPlace.cpp - Copyright (c) 2008 The MWSE Project
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
#include "TES3Util.h"
#include "mwAdapter.h"
#include "VirtualMachine.h"
#include "ScriptUtil.h"

using namespace mwse;

namespace mwse
{
	class xPlace : mwse::InstructionInterface_t
	{
	public:
		xPlace();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xPlaceOpcode = 0X3C2E;
	static xPlace xPlaceInstance;

	xPlace::xPlace() : mwse::InstructionInterface_t(xPlaceOpcode) {}

	void xPlace::loadParameters(mwse::VMExecuteInterface &virtualMachine) {
	}

	float xPlace::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		// Get parameters.
		mwseString_t id = virtualMachine.getString(mwse::Stack::getInstance().popLong());

		// Get other context information for original opcode.
		SCPTRecord_t* script = &virtualMachine.getScript();
		REFRRecord_t* reference = virtualMachine.getReference();
		TES3DefaultTemplate_t* templateToPlace = virtualMachine.getTemplate(id.c_str());

		// Call the original function.
		mwse::mwscript::PlaceAtPC(script, reference, templateToPlace, 1, 256.0f, 1);

		return 0.0f;
	}
}