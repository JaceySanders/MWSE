#include "NITextureEffect.h"

namespace NI {
	const auto NI_TextureEffect_ctor = reinterpret_cast<void(__thiscall*)(const DynamicEffect*)>(0x6E3620);

	TextureEffect::TextureEffect() {
		NI_TextureEffect_ctor(this);
	}

	TextureEffect::~TextureEffect() {
		// Call dtor without deletion.
		vTable.asObject->destructor(this, 0);
	}
}