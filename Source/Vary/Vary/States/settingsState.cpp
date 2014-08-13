#include "settingsState.h"
#include "../Player/devices.h"
#include "../Player/player.h"
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
, mFullscreen(0x5a0d2314)
, mWindowed(0x11e3c735)
, mGUIContainer(context.window)
{
	// ALW - Calculate x, y coordinates relative to the center of the window,
	// ALW - so GUI elements are equidistance from the center in any resolution.
	const sf::Vector2f center = sf::Vector2f(context.window->getSize() / 2u);

	sf::Texture& texture = context.textures->get(Textures::ID::TitleScreen);
	mBackgroundSprite.setTexture(texture);
	trmb::centerOrigin(mBackgroundSprite);
	mBackgroundSprite.setPosition(center);

	const float x = center.x - 375.0f;
	const float y = center.y - 100.0f;
	const float buttonHeight = 50.0f;

	mBackButton = std::make_shared<trmb::Button>(context, Fonts::ID::Main, SoundEffects::ID::Button, Textures::ID::Buttons, 200, 50);
	mBackButton->setPosition(x, y);
	mBackButton->setText("Back");
	mBackButton->setCallback(std::bind(&SettingsState::requestStackPop, this));
	mGUIContainer.pack(mBackButton);

	// Build key binding buttons and labels
	addButtonAndLabel(Controller::MoveUp,	 y + buttonHeight,        "Move Up",    context);
	addButtonAndLabel(Controller::MoveDown,  y + 2.0f * buttonHeight, "Move Down",  context);
	addButtonAndLabel(Controller::MoveLeft,  y + 3.0f * buttonHeight, "Move Left",  context);
	addButtonAndLabel(Controller::MoveRight, y + 4.0f * buttonHeight, "Move Right", context);
	addButtonAndLabel(Controller::Jump,      y + 5.0f * buttonHeight, "Jump", context);
	addButtonAndLabel(Controller::Shoot,     y + 6.0f * buttonHeight, "Shoot", context);

	updateLabels();
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
	for (std::size_t action = 0; action < Controller::ActionCount; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			bool isDeactivateButton = false;
			if (Devices::isKeyboardEnabled() && event.type == sf::Event::KeyReleased)
			{
				Controller &controller = getContext().player->getController();

				switch (action)
				{
				case Controller::MoveUp:
					controller.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), controller.getUp());
					break;
				case Controller::MoveDown:
					controller.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), controller.getDown());
					break;
				case Controller::MoveLeft:
					controller.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), controller.getLeft());
					break;
				case Controller::MoveRight:
					controller.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), controller.getRight());
					break;
				case Controller::Jump:
					controller.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), controller.getJump());
					break;
				case Controller::Shoot:
					controller.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(event.key.code, trmb::KeyboardKeyAsButton::ButtonType::RealTime), controller.getShoot());
					break;
				default:
					assert(("Logic Error: Mismatched enum Action and switch statement!", false));
				}
			
				isUpdateLabel = true;
				isDeactivateButton = true;
			}
			else if (Devices::isMouseEnabled() && event.type == sf::Event::MouseButtonReleased)
			{
				Controller &controller = getContext().player->getController();

				switch (action)
				{
				case Controller::MoveUp:
					controller.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), controller.getUp());
					break;
				case Controller::MoveDown:
					controller.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), controller.getDown());
					break;
				case Controller::MoveLeft:
					controller.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), controller.getLeft());
					break;
				case Controller::MoveRight:
					controller.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), controller.getRight());
					break;
				case Controller::Jump:
					controller.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), controller.getShoot());
					break;
				case Controller::Shoot:
					controller.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(event.mouseButton.button, trmb::MouseButtonAsButton::ButtonType::RealTime), controller.getJump());
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

void SettingsState::handleEvent(const trmb::Event &gameEvent)
{
	// ALW - Currently, fullscreen and windowed mode are the same.
	if (mFullscreen == gameEvent.getType() || mWindowed == gameEvent.getType())
	{
		repositionGUI();
	}
}

void SettingsState::updateLabels()
{
	const Player& player = *getContext().player;

	typedef std::pair<bool, sf::Keyboard::Key> KeyboardKeyBindState;
	std::vector<KeyboardKeyBindState> keyboardBindState(Controller::ActionCount, KeyboardKeyBindState(false, sf::Keyboard::Key::Unknown));

	typedef std::pair<bool, sf::Mouse::Button> MouseButtonBindState;
	std::vector<MouseButtonBindState> mouseBindState(Controller::ActionCount, MouseButtonBindState(false, sf::Mouse::ButtonCount));

	if (Devices::isKeyboardEnabled())
	{
		std::size_t index = 0;
		const auto &actions = getContext().player->getController().getActions();
		const auto &controller = getContext().player->getController();
		for (const auto element : actions)
		{
			sf::Keyboard::Key key = controller.getInputFromKeyboardKeyAsButtonBinding(element->getGameEvent().getType());
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
		const auto &actions = getContext().player->getController().getActions();
		const auto &controller = getContext().player->getController();
		for (const auto element : actions)
		{
			sf::Mouse::Button button = controller.getInputFromMouseButtonAsButtonBinding(element->getGameEvent().getType());
			if (button == sf::Mouse::Button::ButtonCount)
				mouseBindState[index] = MouseButtonBindState(false, sf::Mouse::Button::ButtonCount);
			else
				mouseBindState[index] = MouseButtonBindState(true, button);

			++index;
		}
	}

	// ALW - TODO - Joystick binding

	for (std::size_t i = 0; i < Controller::ActionCount; ++i)
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

void SettingsState::addButtonAndLabel(Controller::Action action, float y, const std::string& text, trmb::State::Context context)
{
	// ALW - Calculate x, y coordinates relative to the center of the window,
	// ALW - so GUI elements are equidistance from the center in any resolution.
	const sf::Vector2f center = sf::Vector2f(context.window->getSize() / 2u);
	const float x = center.x - 375.0f;
	const float buttonWidth = 200.0f;

	mBindingButtons[action] = std::make_shared<trmb::Button>(context, Fonts::ID::Main, SoundEffects::ID::Button, Textures::ID::Buttons, 200, 50);
	mBindingButtons[action]->setPosition(x, y);
	mBindingButtons[action]->setText(text);
	mBindingButtons[action]->setToggle(true);

	const float buffer = 20.0f;

	mBindingLabels[action] = std::make_shared<trmb::Label>("", Fonts::ID::Main, *context.fonts);
	mBindingLabels[action]->setPosition(x + buttonWidth + buffer, y + 15.0f);

	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}

void SettingsState::repositionGUI()
{
	// ALW - Calculate x, y coordinates relative to the center of the window,
	// ALW - so GUI elements are equidistance from the center in any resolution.
	const sf::Vector2f center = sf::Vector2f(getContext().window->getSize() / 2u);

	mBackgroundSprite.setPosition(center);

	const float x = center.x - 375.0f;
	const float y = center.y - 110.0f;

	mBackButton->setPosition(sf::Vector2f(x, y));

	const float buttonWidth = 200.0f;
	const float buttonHeight = 50.0f;

	mBindingButtons[Controller::MoveUp]->setPosition(x,    y + buttonHeight);
	mBindingButtons[Controller::MoveDown]->setPosition(x,  y + 2.0f * buttonHeight);
	mBindingButtons[Controller::MoveLeft]->setPosition(x,  y + 3.0f * buttonHeight);
	mBindingButtons[Controller::MoveRight]->setPosition(x, y + 4.0f * buttonHeight);
	mBindingButtons[Controller::Jump]->setPosition(x,      y + 5.0f * buttonHeight);
	mBindingButtons[Controller::Shoot]->setPosition(x,     y + 6.0f * buttonHeight);

	const float buffer = 20.0f;

	mBindingLabels[Controller::MoveUp]->setPosition(x + buttonWidth + buffer,    y + buttonHeight + 15.0f);
	mBindingLabels[Controller::MoveDown]->setPosition(x + buttonWidth + buffer,  y + 2.0f * buttonHeight + 15.0f);
	mBindingLabels[Controller::MoveLeft]->setPosition(x + buttonWidth + buffer,  y + 3.0f * buttonHeight + 15.0f);
	mBindingLabels[Controller::MoveRight]->setPosition(x + buttonWidth + buffer, y + 4.0f * buttonHeight + 15.0f);
	mBindingLabels[Controller::Jump]->setPosition(x + buttonWidth + buffer,      y + 5.0f * buttonHeight + 15.0f);
	mBindingLabels[Controller::Shoot]->setPosition(x + buttonWidth + buffer,     y + 6.0f * buttonHeight + 15.0f);
}