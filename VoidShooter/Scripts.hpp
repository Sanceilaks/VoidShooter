#pragma once

#include "Module.hpp"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include <filesystem>
#include <fstream>

#define SCRIPT_NAMESPACE ScriptNamespace

#define BEGIN_SCRIPT_NAMESPACE namespace ScriptNamespace {
#define END_SCRIPT_NAMESPACEW  }

class ScriptSystem;

namespace G {
	inline ScriptSystem* Scripts = nullptr;
}

class ScriptSystem final : public IModule {
	INIT_MODULE(ScriptSystem);

	lua_State* luaState = nullptr;
	std::vector<std::function<void(lua_State*)>> registerCallbacks;

	static sf::String readFile(const std::filesystem::path& path) {
		std::ifstream ifs(path);
		return std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
	}

	void pushGlobals();
public:
	explicit ScriptSystem(Application* app) : IModule(app) {
		G::Scripts = this;
		luaState = luaL_newstate();
	}

	enum class RunFileMethod {
		LuaDoFile,
		LuaDoString
	};

	void runFile(const std::filesystem::path& path, RunFileMethod method = RunFileMethod::LuaDoString, bool pushGlobals = false) {
		if (!is_regular_file(path)) {
			throw std::filesystem::filesystem_error("path is not file", std::make_error_code(std::errc::file_exists));
		}

		if (pushGlobals) {
			this->pushGlobals();
		}

		int result = 0;

		switch (method) {
			case RunFileMethod::LuaDoString: {
				const auto fileContent = readFile(path);
				result = luaL_dostring(luaState, fileContent.toAnsiString().c_str());
				break;
			}
			case RunFileMethod::LuaDoFile: {
				result = luaL_dofile(luaState, path.generic_string().c_str());
				break;
			}
		}

		if (result != 0) {
			spdlog::error("[SCRIPT ERROR] {}", lua_tostring(luaState, -1));
			lua_pop(luaState, 1);
		}
	}

	void runDirectory(const std::filesystem::path& path) {
		if (!is_directory(path)) {
			throw std::filesystem::filesystem_error("path is not directory", std::make_error_code(std::errc::not_a_directory));
		}

		this->pushGlobals();

		for (auto& entry : std::filesystem::recursive_directory_iterator(path)) {
			if (is_directory(entry)) {
				runDirectory(entry);
			} else {
				if (entry.path().extension() == ".lua") {
					runFile(entry, RunFileMethod::LuaDoFile, false);
				}
			}
		}
	}
};