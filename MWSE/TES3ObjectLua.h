#pragma once

#include "sol.hpp"

#include "LuaUtil.h"

#include "NINode.h"
#include "TES3GameFile.h"
#include "TES3ReferenceList.h"

#include "BitUtil.h"

namespace mwse {
	namespace lua {
		template <typename T>
		void setUserdataForBaseObject(sol::simple_usertype<T>& usertypeDefinition) {
			// Basic property binding.
			usertypeDefinition.set("objectType", sol::readonly_property(&T::objectType));
			usertypeDefinition.set("objectFlags", sol::readonly_property(&T::objectFlags));

			// Allow object to be converted to strings using their object ID.
			usertypeDefinition.set(sol::meta_function::to_string, &T::getObjectID);

			// Allow objects to be serialized to json using their ID.
			usertypeDefinition.set("__tojson", [](T& self, sol::table state) {
				std::ostringstream ss;
				ss << "\"tes3baseObject:" << self.getObjectID() << "\"";
				return ss.str();
			});

			// Functions exposed as properties.
			usertypeDefinition.set("id", sol::readonly_property(&T::getObjectID));
			usertypeDefinition.set("sourceMod", sol::readonly_property([](T& self) -> const char* {
				if (self.sourceMod) {
					return self.sourceMod->filename;
				}
				return nullptr;
			}));
			usertypeDefinition.set("modified", sol::property(&T::getObjectModified, &T::setObjectModified));
			usertypeDefinition.set("disabled", sol::readonly_property([](T& self) { return BIT_TEST(self.objectFlags, TES3::ObjectFlag::DisabledBit); }));
			usertypeDefinition.set("deleted", sol::readonly_property([](T& self) { return BIT_TEST(self.objectFlags, TES3::ObjectFlag::DeleteBit); }));
		}

		template <typename T>
		void setUserdataForObject(sol::simple_usertype<T>& usertypeDefinition) {
			setUserdataForBaseObject(usertypeDefinition);

			// Basic property binding.
			usertypeDefinition.set("scale", sol::property(&T::getScale, [](T& self, float value) { self.setScale(value); }));

			// Indirect bindings to unions and arrays.
			usertypeDefinition.set("owningCollection", sol::property([](T& self) { return self.owningCollection.asReferenceList; }));

			// Access to other objects that need to be packaged.
			usertypeDefinition.set("nextInCollection", sol::readonly_property([](T& self) { return makeLuaObject(self.nextInCollection); }));
			usertypeDefinition.set("previousInCollection", sol::readonly_property([](T& self) { return makeLuaObject(self.previousInCollection); }));
			usertypeDefinition.set("sceneNode", sol::readonly_property([](T& self) { return makeLuaObject(self.getSceneGraphNode()); }));
			usertypeDefinition.set("sceneCollisionRoot", sol::readonly_property([](T& self) { return makeLuaObject(self.sceneCollisionRoot); }));
		}

		template <typename T>
		void setUserdataForPhysicalObject(sol::simple_usertype<T>& usertypeDefinition) {
			setUserdataForObject(usertypeDefinition);

			// Basic property binding.
			usertypeDefinition.set("boundingBox", sol::readonly_property(&T::boundingBox));

			// Functions exposed as properties.
			usertypeDefinition.set("stolenList", sol::readonly_property(&T::getStolenList));
		}
	}
}