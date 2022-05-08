#include "Scripts.hpp"

#include "FontManager.hpp"

static void luaLogInfo(const char* message) {
	spdlog::info(message);
}

static void luaLogWarning(const char* message) {
	spdlog::warn(message);
}

static void luaLogError(const char* message) {
	spdlog::error(message);
}

void ScriptSystem::pushGlobals() {
	luaL_openlibs(luaState);
	luabridge::getGlobalNamespace(luaState).
		addFunction("log_info", luaLogInfo).
		addFunction("log_error", luaLogError).
		addFunction("log_warn", luaLogWarning);

	std::ranges::for_each(registerCallbacks, [&](std::function<void(lua_State*)> f) { f(luaState); });
}
