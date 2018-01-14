/************************************************************************
	
	ScriptUtil.h - Copyright (c) 2008 The MWSE Project
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

#pragma once

#include "mwOffsets.h"
#include "mwseTypes.h"
#include "mwseString.h"

namespace mwse
{
	namespace mwscript
	{
		int getInstructionPointer();
		void setInstructionPointer(int IP);

		REFRRecord_t* getScriptTargetReference();
		void setScriptTargetReference(REFRRecord_t* reference);

		TES3DefaultTemplate_t* getScriptTargetTemplate();
		void setScriptTargetTemplate(TES3DefaultTemplate_t* record);

		TES3DefaultTemplate_t* getScriptSecondObject();
		void setScriptSecondObject(TES3DefaultTemplate_t* record);

		mwLong_t getScriptVariableIndex();
		void setScriptVariableIndex(mwLong_t index);

		mwFloat_t getScriptDestinationX();
		void setScriptDestinationX(mwFloat_t value);

		mwFloat_t getScriptDestinationY();
		void setScriptDestinationY(mwFloat_t value);

		mwFloat_t getScriptDestinationZ();
		void setScriptDestinationZ(mwFloat_t value);

		void setScriptDestination(mwFloat_t x, mwFloat_t y, mwFloat_t z);

		mwFloat_t getScriptTargetRotationX();
		void setScriptTargetRotationX(mwFloat_t value);

		mwFloat_t getScriptTargetRotationY();
		void setScriptTargetRotationY(mwFloat_t value);

		mwFloat_t getScriptTargetRotationZ();
		void setScriptTargetRotationZ(mwFloat_t value);

		void setScriptTargetRotation(mwFloat_t x, mwFloat_t y, mwFloat_t z);

		float RunOriginalOpCode(SCPTRecord_t* script, REFRRecord_t* reference, int opCode, TES3DefaultTemplate_t* objectParam, char charParam, float unk1, float unk2);

		void AddItem(SCPTRecord_t* script, REFRRecord_t* reference, TES3DefaultTemplate_t* itemTemplate, mwLong_t count);

		void AddSpell(SCPTRecord_t* script, REFRRecord_t* reference, TES3DefaultTemplate_t* spellTemplate);

		void AITravel(SCPTRecord_t* script, REFRRecord_t* reference, mwFloat_t x, mwFloat_t y, mwFloat_t z);

		void Drop(SCPTRecord_t* script, REFRRecord_t* reference, TES3DefaultTemplate_t* itemTemplate, mwLong_t count);

		void Equip(SCPTRecord_t* script, REFRRecord_t* reference, TES3DefaultTemplate_t* itemTemplate);

		void ExplodeSpell(SCPTRecord_t* script, REFRRecord_t* reference, TES3DefaultTemplate_t* spellTemplate);

		bool HasItemEquipped(SCPTRecord_t* script, REFRRecord_t* reference, TES3DefaultTemplate_t* itemTemplate);

		bool GetSpellEffects(SCPTRecord_t* script, REFRRecord_t* reference, TES3DefaultTemplate_t* spellTemplate);

		void PlaceAtPC(SCPTRecord_t* script, REFRRecord_t* reference, TES3DefaultTemplate_t* placedTemplate, mwLong_t count, mwFloat_t distance, mwFloat_t direction);
	}
}