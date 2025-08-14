#include <Geode/ui/TextInput.hpp>
#include <Geode/ui/Notification.hpp>
#include <Geode/utils/general.hpp>

using namespace geode::prelude;

#include <Geode/modify/FLAlertLayer.hpp>
class $modify(EditAccountID_FLAlertLayer, FLAlertLayer) {
	void trySaveValue(float) {
		if (Ref ew = GameManager::get()) ew->save();
		if (Ref aw = Notification::create("Saved!")) aw->show();
		if (Ref manager = GJAccountManager::get()) for (auto& a : EditAccountID::get()->m_onNewID) if (a) a(manager->m_accountID);
	}
	$override void show() {
		FLAlertLayer::show();
		if (Ref casted = typeinfo_cast<AccountLoginLayer*>(this)) {
			// callback
			for (auto& a : EditAccountID::get()->m_onAccountLoginLayerShow) if (a) a(casted);
			// input
			if (Ref accm = GJAccountManager::get()) if (Ref inp = TextInput::create(62.f, fmt::format("{}", accm->m_accountID).c_str())) {
				// preset value
				inp->setString(fmt::format("{}", accm->m_accountID).c_str());
				// callback
				inp->setCallback(
					[inp = Ref(inp)](const std::string& p0) {
						if (Ref manager = GJAccountManager::get()) manager->m_accountID = utils::numFromString<int>(
							p0
						).unwrapOr(manager->m_accountID);
						if (inp) inp->unschedule(schedule_selector(EditAccountID_FLAlertLayer::trySaveValue));
						if (inp) inp->scheduleOnce(schedule_selector(EditAccountID_FLAlertLayer::trySaveValue), 0.5f);
						// callback
						for (auto& a : EditAccountID::get()->m_onInputTextChanged) if (a) a(p0);
					}
				);
				// position
				inp->setPosition({ 145.000f, -86.000f });
				// label
				if (Ref inpInner = inp->getInputNode()) {
					Ref lbl = CCLabelBMFont::create(EditAccountID::get()->m_inputLabel.c_str(), "bigFont.fnt");
					if (lbl) lbl->setScale(0.400f);
					if (lbl) inpInner->addChild(lbl, 1, "inp-label"_h);
					// callback
					for (auto& a : EditAccountID::get()->m_onLabelSetup) if (a) a(lbl);
				}
				// add to menu
				if (Ref menu = this->m_buttonMenu) menu->addChild(inp);
				// callback
				for (auto& a : EditAccountID::get()->m_onInputSetup) if (a) a(inp);
			};
			// callback
			for (auto& a : EditAccountID::get()->m_onAccountLoginLayerSetup) if (a) a(casted);
		}
	};
};