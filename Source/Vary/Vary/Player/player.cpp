#include "player.h"
//#include "SceneNode/aircraft.h"

//#include "../Engine/Command/commandQueue.h"

#include <algorithm>
#include <map>
#include <string>

//using namespace std::placeholders;


//struct AircraftMover
//{
//	AircraftMover(float vx, float vy)
//		: velocity(vx, vy)
//	{
//	}
//
//	void operator() (Aircraft& aircraft, sf::Time) const
//	{
//		aircraft.accelerate(velocity * aircraft.getMaxSpeed());
//	}
//
//	sf::Vector2f velocity;
//};

Player::Player()
//	: mCurrentMissionStatus(MissionStatus::MissionRunning)
{
	// Set initial key bindings
//	mKeyboardBinding[sf::Keyboard::A] = MoveLeft;
//	mKeyboardBinding[sf::Keyboard::D] = MoveRight;
//	mKeyboardBinding[sf::Keyboard::W] = MoveUp;
//	mKeyboardBinding[sf::Keyboard::S] = MoveDown;
//	mMouseBinding[sf::Mouse::Left] = Fire;
//	mMouseBinding[sf::Mouse::Right] = LaunchMissile;

	// Set initial action bindings
//	initializeActions();

	// Assign all categories to player's aircraft
//	for (auto& pair : mActionBinding)
//		pair.second.category = Category::PlayerAircraft;
}

/*
void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (Input::isKeyboardEnabled() && event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyboardBinding.find(event.key.code);
		if (found != mKeyboardBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
	else if (Input::isMouseEnabled() && event.type == sf::Event::MouseButtonPressed)
	{
		// Check if pressed button appears in button binding, trigger command if so
		auto found = mMouseBinding.find(event.mouseButton.button);
		if (found != mMouseBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}

	// ALW - TODO - Joystick binding

}
*/

/*
void Player::handleRealtimeInput(CommandQueue& commands)
{
	if (Input::isKeyboardEnabled())
	{
		// Traverse all bound keyboard keys and check if they are pressed
		for (auto pair : mKeyboardBinding)
		{
			// If key is pressed, lookup action and trigger corresponding command
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
				commands.push(mActionBinding[pair.second]);
		}
	}

	if (Input::isMouseEnabled())
	{
		// Traverse all bound mouse buttons and check if they are pressed
		for (auto pair : mMouseBinding)
		{
			// If key is pressed, lookup action and trigger corresponding command
			if (sf::Mouse::isButtonPressed(pair.first) && isRealtimeAction(pair.second))
				commands.push(mActionBinding[pair.second]);
		}
	}

	// ALW - TODO - Joystick binding

}
*/

/*
void Player::assignKeyboardKey(Action action, sf::Keyboard::Key key)
{
	// ALW - Remove all keyboard keys that already map to action
	for (auto itr = mKeyboardBinding.begin(); itr != mKeyboardBinding.end();)
	{
		if (itr->second == action)
			mKeyboardBinding.erase(itr++);
		else
			++itr;
	}

	// ALW Remove all mouse buttons that already map to action
	for (auto itr = mMouseBinding.begin(); itr != mMouseBinding.end();)
	{
		if (itr->second == action)
			mMouseBinding.erase(itr++);
		else
			++itr;
	}

	// ALW - TODO - Joystick binding

	// Insert new binding
	mKeyboardBinding[key] = action;
}
*/

/*
void Player::assignMouseButton(Action action, sf::Mouse::Button button)
{
	// ALW - Remove all keyboard keys that already map to action
	for (auto itr = mKeyboardBinding.begin(); itr != mKeyboardBinding.end();)
	{
		if (itr->second == action)
			mKeyboardBinding.erase(itr++);
		else
			++itr;
	}

	// ALW Remove all mouse buttons that already map to action
	for (auto itr = mMouseBinding.begin(); itr != mMouseBinding.end();)
	{
		if (itr->second == action)
			mMouseBinding.erase(itr++);
		else
			++itr;
	}

	// ALW - TODO - Joystick binding

	// Insert new binding
	mMouseBinding[button] = action;
}
*/

/*
sf::Keyboard::Key Player::getAssignedKeyboardKey(Action action) const
{
	for (auto pair : mKeyboardBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	// ALW - Hack - Allows check to be made, if action does not correspond to a key.
	return sf::Keyboard::Unknown;
}
*/

/*
sf::Mouse::Button Player::getAssignedMouseButton(Action action) const
{
	for (auto pair : mMouseBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	// ALW - Hack - Allows check to be made, if action does not correspond to a button.
	return sf::Mouse::Button::ButtonCount;
}
*/

/*
void Player::setMissionStatus(MissionStatus status)
{
	mCurrentMissionStatus = status;
}
*/

/*
Player::MissionStatus Player::getMissionStatus() const
{
	return mCurrentMissionStatus;
}
*/

/*
void Player::initializeActions()
{
	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-1, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+1, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -1));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +1));
	mActionBinding[Fire].action = derivedAction<Aircraft>([](Aircraft& a, sf::Time){ a.fire(); });
	mActionBinding[LaunchMissile].action = derivedAction<Aircraft>([](Aircraft& a, sf::Time){ a.launchMissile(); });
}
*/

/*
bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
	case Fire:
		return true;

	default:
		return false;
	}
}
*/