#include "settingsState.h"
#include "../Player/devices.h"
#include "../Resources/resourceIdentifiers.h"

#include "Trambo/Inputs/keyboardKeyAsButton.h"
#include "Trambo/Inputs/mouseButtonAsButton.h"
#include "Trambo/Utilities/utility.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <cassert>
#include <vector>


SettingsState::SettingsState(trmb::StateStack& stack, trmb::State::Context context)
: State(stack, context)
, mGUIContainer(context.window)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::ID::TitleScreen));

	// Build key binding buttons and labels
	addButtonAndLabel(Player::MoveUp,    200.f, "Move Up",    context);
	addButtonAndLabel(Player::MoveDown,  250.f, "Move Down",  context);
	addButtonAndLabel(Player::MoveLeft,  300.f, "Move Left",  context);
	addButtonAndLabel(Player::MoveRight, 350.f, "Move Right", context);
	addButtonAndLabel(Player::Jump,		 400.f, "Jump",       context);
	addButtonAndLabel(Player::Shoot,     450.f, "Shoot",      context);

	updateLabels();

	auto backButton = std::make_shared<trmb::Button>(context, Fonts::ID::Main, SoundEffects::ID::Button, Textures::ID::Buttons, 200, 50);
	backButton->setPosition(20.f, 520.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	mGUIContainer.pack(backButton);
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time)
{
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	bool isUpdateLabel = false;

	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t action = 0; action < Player::ActionCount; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			bool isDeactivateButton = false;
			if (Devices::isKeyboardEnabled() && event.type == sf::Event::KeyReleased)
			{
				Player& player = *getContext().player;

				switch (action)
				{
				case Player::MoveUp:
					player.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), player.getUp());
					break;
				case Player::MoveDown:
					player.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), player.getDown());
					break;
				case Player::MoveLeft:
					player.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), player.getLeft());
					break;
				case Player::MoveRight:
					player.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), player.getRight());
					break;
				case Player::Jump:
					player.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), player.getJump());
					break;
				case Player::Shoot:
					player.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), player.getShoot());
					break;
				default:
					assert(("Logic Error: Mismatched enum Action and switch statement!", false));
				}
			
				isUpdateLabel = true;
				isDeactivateButton = true;
			}
			else if (Devices::isMouseEnabled() && event.type == sf::Event::MouseButtonReleased)
			{
				Player& player = *getContext().player;

				switch (action)
				{
				case Player::MoveUp:
					player.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), player.getUp());
					break;
				case Player::MoveDown:
					player.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), player.getDown());
					break;
				case Player::MoveLeft:
					player.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), player.getLeft());
					break;
				case Player::MoveRight:
					player.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), player.getRight());
					break;
				case Player::Jump:
					player.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), player.getShoot());
					break;
				case Player::Shoot:
					player.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), player.getJump());
					break;
				default:
					assert(("Logic Error: Mismatched enum Action and switch statement!", false));
				}

				isUpdateLabel = true;
				isDeactivateButton = true;
			}

			// ALW - TODO - Joystick binding

			if (isDeactivateButton)
			{
				mBindingButtons[action]->deactivate();
				// ALW - Hack - Fake a MouseMoved event to force an update. The cursor may be over a button, but hasn't moved.
				sf::Event event;
				event.type = sf::Event::EventType::MouseMoved;
				mGUIContainer.handleEvent(event);
			}

			break;
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isUpdateLabel)
		updateLabels();
	else if (!isKeyBinding)
		mGUIContainer.handleEvent(event);
//	else if (isKeyBinding && !isUpdateLabel)
//		doNothing;

	return false;
}

void SettingsState::updateLabels()
{
	const Player& player = *getContext().player;

	typedef std::pair<bool, sf::Keyboard::Key> KeyboardKeyBindState;
	std::vector<KeyboardKeyBindState> keyboardBindState(Player::ActionCount, KeyboardKeyBindState(false, sf::Keyboard::Key::Unknown));

	typedef std::pair<bool, sf::Mouse::Button> MouseButtonBindState;
	std::vector<MouseButtonBindState> mouseBindState(Player::ActionCount, MouseButtonBindState(false, sf::Mouse::ButtonCount));

	if (Devices::isKeyboardEnabled())
	{
		std::size_t index = 0;
		const auto actions = getContext().player->getActions();
		for (const auto element : actions)
		{
			sf::Keyboard::Key key = player.getInputFromKeyboardKeyAsButtonBinding(element->getGameEvent().getType());
			if (key == sf::Keyboard::Key::Unknown)
				keyboardBindState[index] = KeyboardKeyBindState(false, sf::Keyboard::Key::Unknown);
			else
				keyboardBindState[index] = KeyboardKeyBindState(true, key);

			++index;
		}
	}

	if (Devices::isMouseEnabled())
	{
		std::size_t index = 0;
		const auto actions = getContext().player->getActions();
		for (const auto element : actions)
		{
			sf::Mouse::Button button = player.getInputFromMouseButtonAsButtonBinding(element->getGameEvent().getType());
			if (button == sf::Mouse::Button::ButtonCount)
				mouseBindState[index] = MouseButtonBindState(false, sf::Mouse::Button::ButtonCount);
			else
				mouseBindState[index] = MouseButtonBindState(true, button);

			++index;
		}
	}

	// ALW - TODO - Joystick binding

	for (std::size_t i = 0; i < Player::ActionCount; ++i)
	{
		if (keyboardBindState[i].first && !mouseBindState[i].first)
			mBindingLabels[i]->setText(trmb::toString(keyboardBindState[i].second));
		else if (!keyboardBindState[i].first && mouseBindState[i].first)
			mBindingLabels[i]->setText(trmb::toString(mouseBindState[i].second));
		else if (!keyboardBindState[i].first && !mouseBindState[i].first)
			mBindingLabels[i]->setText("Unbound");
		else
			assert(false);

	}
}

void SettingsState::addButtonAndLabel(Player::Action action, float y, const std::string& text, trmb::State::Context context)
{
	mBindingButtons[action] = std::make_shared<trmb::Button>(context, Fonts::ID::Main, SoundEffects::ID::Button, Textures::ID::Buttons, 200, 50);
	mBindingButtons[action]->setPosition(20.f, y);
	mBindingButtons[action]->setText(text);
	mBindingButtons[action]->setToggle(true);

	mBindingLabels[action] = std::make_shared<trmb::Label>("", Fonts::ID::Main, *context.fonts);
	mBindingLabels[action]->setPosition(240.f, y + 15.f);

	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}
