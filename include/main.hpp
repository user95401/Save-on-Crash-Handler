#pragma once

#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/AccountLoginLayer.hpp>

// Who ever will use that xd
class EditAccountID : public cocos2d::CCNode {
protected:
	CREATE_FUNC(EditAccountID);
public:
	std::vector<std::function<void(int)>> m_onNewID;
	std::vector<std::function<void(geode::TextInput*)>> m_onInputSetup;
	std::vector<std::function<void(cocos2d::CCLabelBMFont*)>> m_onLabelSetup;
	std::vector<std::function<void(const std::string&)>> m_onInputTextChanged;
	std::vector<std::function<void(AccountLoginLayer*)>> m_onAccountLoginLayerShow;
	std::vector<std::function<void(AccountLoginLayer*)>> m_onAccountLoginLayerSetup;
	std::string m_inputLabel = "Account ID:\n \n \n \n ";
	// Get or create shared instance of EditAccountID
	static EditAccountID* get() {
		geode::Ref instance = geode::cast::typeinfo_cast<EditAccountID*>(GameManager::get()->getUserObject("EditAccountID"));
		if (!instance) {
			instance = EditAccountID::create();
			GameManager::get()->setUserObject("EditAccountID", instance);
		}
		return instance;
	}
	// Called when the account ID is changed and was saved
	auto onNewID(std::function<void(int)> callback, auto prepend = false, auto replace = false) {
		if (this->getUserObject("m_onNewID was reserved")) return this;
		if (replace) {
			this->setUserObject("m_onNewID was reserved", GameManager::get()); // clear();
			m_onNewID.clear();
		}
		prepend ? m_onNewID.insert(m_onNewID.begin(), callback) : m_onNewID.push_back(callback);
		return this;
	}
	// Called when the input is created and got basic setup
	auto onInputSetup(std::function<void(geode::TextInput*)> callback, auto prepend = false, auto replace = false) {
		if (this->getUserObject("m_onInputSetup was reserved")) return this;
		if (replace) {
			this->setUserObject("m_onInputSetup was reserved", GameManager::get()); // clear();
			m_onInputSetup.clear();
		}
		prepend ? m_onInputSetup.insert(m_onInputSetup.begin(), callback) : m_onInputSetup.push_back(callback);
		return this;
	}
	// Called when the label is created and got basic setup
	auto onLabelSetup(std::function<void(cocos2d::CCLabelBMFont*)> callback, auto prepend = false, auto replace = false) {
		if (this->getUserObject("m_onLabelSetup was reserved")) return this;
		if (replace) {
			this->setUserObject("m_onLabelSetup was reserved", GameManager::get()); // clear();
			m_onLabelSetup.clear();
		}
		prepend ? m_onLabelSetup.insert(m_onLabelSetup.begin(), callback) : m_onLabelSetup.push_back(callback);
		return this;
	}
	// Called when the input text is changed
	auto onInputTextChanged(std::function<void(const std::string&)> callback, auto prepend = false, auto replace = false) {
		if (this->getUserObject("m_onInputTextChanged was reserved")) return this;
		if (replace) {
			this->setUserObject("m_onInputTextChanged was reserved", GameManager::get()); // clear();
			m_onInputTextChanged.clear();
		}
		prepend ? m_onInputTextChanged.insert(m_onInputTextChanged.begin(), callback) : m_onInputTextChanged.push_back(callback);
		return this;
	}
	// Called when the account login layer is shown and not yet setuped yet
	auto onAccountLoginLayerShow(std::function<void(AccountLoginLayer*)> callback, auto prepend = false, auto replace = false) {
		if (this->getUserObject("m_onAccountLoginLayerShow was reserved")) return this;
		if (replace) {
			this->setUserObject("m_onAccountLoginLayerShow was reserved", GameManager::get()); // clear();
			m_onAccountLoginLayerShow.clear();
		}
		prepend ? m_onAccountLoginLayerShow.insert(m_onAccountLoginLayerShow.begin(), callback) : m_onAccountLoginLayerShow.push_back(callback);
		return this;
	}
	// Called when the account login layer is shown and setuped
	auto onAccountLoginLayerSetup(std::function<void(AccountLoginLayer*)> callback, auto prepend = false, auto replace = false) {
		if (this->getUserObject("m_onAccountLoginLayerSetup was reserved")) return this;
		if (replace) {
			this->setUserObject("m_onAccountLoginLayerSetup was reserved", GameManager::get()); // clear();
			m_onAccountLoginLayerSetup.clear();
		}
		prepend ? m_onAccountLoginLayerSetup.insert(m_onAccountLoginLayerSetup.begin(), callback) : m_onAccountLoginLayerSetup.push_back(callback);
		return this;
	}
};