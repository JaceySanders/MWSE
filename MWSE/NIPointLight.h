#pragma once

#include "NILight.h"

#include "NIPointer.h"

namespace NI {
	struct PointLight : Light {
		float constantAttenuation; // 0xD0
		float linearAttenuation; // 0xD4
		float quadraticAttenuation; // 0xD8

		//
		// Custom functions.
		//

		static Pointer<PointLight> create();

		void setAttenuationForRadius(unsigned int radius);

	};
	static_assert(sizeof(PointLight) == 0xDC, "NI::PointLight failed size validation");
}
