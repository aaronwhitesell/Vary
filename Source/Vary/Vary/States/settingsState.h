#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "../Player/controller.h"

#include "Trambo/Events/eventHandler.h"
#include "Trambo/GUI/button.h"
#include "Trambo/GUI/container.h"
#include "Trambo/GUI/label.h"
#include "Trambo/States/state.h"

#include <SFML/Graphics/Sprite.hpp>

#include <array>
#include <memory>


namespace sf
{
	class Event;
	class Time;
}

namespace trmb
{
	class Event;
	class StateStack;
}

class SettingsState : public trmb::State, public trmb::EventHandler
{
public:
							SettingsState(trmb::StateStack& stack, trmb::State::Context context);
							SettingsState(const SettingsState &) = delete;
	SettingsState &			operator=(const SettingsState &) = delete;

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);
	virtual void			handleEvent(const trmb::Event &gameEvent);


private:
	typedef unsigned long EventGuid;


private:
	void					updateLabels();
	void					addButtonAndLabel(Controller::Action action, float y, const std::string& text, trmb::State::Context context);
	void					repositionGUI();


private:
	const EventGuid											mFullscreen; // ALW - Matches the GUID in the ToggleFullscreen class.
	const EventGuid											mWindowed;   // ALW - Matches the GUID in the ToggleFullscreen class.

	sf::Sprite												mBackgroundSprite;
	std::shared_ptr<trmb::Button>							mBackButton;
	trmb::Container											mGUIContainer;
	std::array<trmb::Button::Ptr, Controller::ActionCount>	mBindingButtons;
	std::array<trmb::Label::Ptr, Controller::ActionCount>	mBindingLabels;
};

#endif
