#pragma once

#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GJGameLevel.hpp>

class CrashHandler : public cocos2d::CCNode {
protected:
	CREATE_FUNC(CrashHandler);
public:
	std::string m_implID;
	std::vector<std::function<void(const std::string&)>> m_onCrashCallbacks;
	std::vector<std::function<void(GJGameLevel*)>> m_onLevelSavedAtCrashCallbacks;
	// Get or create shared instance of CrashHandler
	static CrashHandler* get() {
		geode::Ref instance = geode::cast::typeinfo_cast<CrashHandler*>(GameManager::get()->getUserObject("user95401.save-on-crash-handler"));
		if (!instance) {
			instance = CrashHandler::create();
			GameManager::get()->setUserObject("user95401.save-on-crash-handler", instance);
		}
		return instance;
	}
	// Add crash callback
	auto onCrash(std::function<void(const std::string&)> callback, bool prepend = false, bool replace = false) {
		if (this->getUserObject("m_onCrashCallbacks was reserved")) return this;
		if (replace) {
			this->setUserObject("m_onCrashCallbacks was reserved", GameManager::get()); // clear();
			m_onCrashCallbacks.clear();
		}
		prepend ? (void)m_onCrashCallbacks.insert(m_onCrashCallbacks.begin(), callback) : m_onCrashCallbacks.push_back(callback);
		return this;
	}
	// Add level save callback
	auto onLevelSavedAtCrash(std::function<void(GJGameLevel*)> callback, bool prepend = false, bool replace = false) {
		if (this->getUserObject("m_onLevelSavedAtCrashCallbacks was reserved")) return this;
		if (replace) {
			this->setUserObject("m_onLevelSavedAtCrashCallbacks was reserved", GameManager::get()); // clear();
			m_onLevelSavedAtCrashCallbacks.clear();
		}
		prepend ? (void)m_onLevelSavedAtCrashCallbacks.insert(m_onLevelSavedAtCrashCallbacks.begin(), callback) : m_onLevelSavedAtCrashCallbacks.push_back(callback);
		return this;
	}
};