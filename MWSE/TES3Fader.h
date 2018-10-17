#pragma once

#include "TES3Defines.h"

#include "NIObject.h"
#include "NIPointer.h"

namespace TES3 {
	typedef void(__stdcall* FaderCallback)();

	struct Fader {
		struct Node {
			float duration; // 0x0
			float target; // 0x4
			FaderCallback callback; // 0x8
			Fader::Node * next; // 0xC
		};
		bool isActive; // 0x0
		int unknown_0x04;
		NI::Pointer<NI::Node> node; // 0x8
		NI::Pointer<NI::AVObject> geometry; // 0xC // Actual type is NiTriShape.
		int unknown_0x10;
		int unknown_0x14;
		int unknown_0x18;
		int unknown_0x1C;
		int unknown_0x20;
		int unknown_0x24;
		int unknown_0x28;
		int unknown_0x2C;
		Fader::Node * queueTail;
		Fader::Node * queueHead;
		bool unknown_0x38;
		void * unknown_0x3C; // Maybe a callback?

		//
		// Other related this-call functions.
		//

		void fadeTo(float value, float duration, FaderCallback callback = nullptr);

	};
	static_assert(sizeof(Fader) == 0x40, "TES3::Fader failed size validation");
}