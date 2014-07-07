#include "player.h"


Player::Player()
{
	// ALW - Create a map of event guids and corresponding actions
	mActionBindings.createAction(mUp);
	mActionBindings.createAction(mDown);
	mActionBindings.createAction(mLeft);
	mActionBindings.createAction(mRight);
	mActionBindings.createAction(mJump);
	mActionBindings.createAction(mShoot);

	// ALW - Create a map of keyboard buttons and corresponding actions (default bindings)
	mActionBindings.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(sf::Keyboard::Up,    trmb::KeyboardKeyAsButton::ButtonType::RealTime), mUp);
	mActionBindings.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(sf::Keyboard::Down,  trmb::KeyboardKeyAsButton::ButtonType::RealTime), mDown);
	mActionBindings.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(sf::Keyboard::Left,  trmb::KeyboardKeyAsButton::ButtonType::RealTime), mLeft);
	mActionBindings.assignKeyboardKeyAsButtonBinding(trmb::KeyboardKeyAsButton(sf::Keyboard::Right, trmb::KeyboardKeyAsButton::ButtonType::RealTime), mRight);
	mActionBindings.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(sf::Mouse::Right,    trmb::MouseButtonAsButton::ButtonType::RealTime), mJump);
	mActionBindings.assignMouseButtonAsButtonBinding(trmb::MouseButtonAsButton(sf::Mouse::Left,		trmb::MouseButtonAsButton::ButtonType::RealTime), mShoot);
}

const trmb::ActionBinding::EventGuid Player::getUp() const
{
	return mUp;
}

const trmb::ActionBinding::EventGuid Player::getDown() const
{
	return mDown;
}

const trmb::ActionBinding::EventGuid Player::getLeft() const
{
	return mLeft;
}

const trmb::ActionBinding::EventGuid Player::getRight() const
{
	return mRight;
}

const trmb::ActionBinding::EventGuid Player::getJump() const
{
	return mJump;
}

const trmb::ActionBinding::EventGuid Player::getShoot() const
{
	return mShoot;
}

const std::vector<trmb::ActionBinding::ActionSharedPtr> & Player::getActions() const
{
	return mActionBindings.getActions();
}

sf::Keyboard::Key Player::getInputFromKeyboardKeyAsButtonBinding(trmb::ActionBinding::EventGuid eventGuid) const
{
	return mActionBindings.getInputFromKeyboardKeyAsButtonBinding(eventGuid);
}

sf::Mouse::Button Player::getInputFromMouseButtonAsButtonBinding(trmb::ActionBinding::EventGuid eventGuid) const
{
	return mActionBindings.getInputFromMouseButtonAsButtonBinding(eventGuid);
}

void Player::update()
{
	mActionBindings.update();
}

void Player::handleEvent(const sf::Event &inputEvent)
{
	mActionBindings.handleEvent(inputEvent);
}

void Player::assignKeyboardKeyAsButtonBinding(const trmb::KeyboardKeyAsButton &keyboardKeyAsButton, trmb::ActionBinding::EventGuid eventGuid)
{
	mActionBindings.assignKeyboardKeyAsButtonBinding(keyboardKeyAsButton, eventGuid);
}

void Player::assignMouseButtonAsButtonBinding(const trmb::MouseButtonAsButton &mouseButtonAsButton, trmb::ActionBinding::EventGuid eventGuid)
{
	mActionBindings.assignMouseButtonAsButtonBinding(mouseButtonAsButton, eventGuid);
}
