#ifndef PLAYER_H
#define PLAYER_H

//#include "../Engine/Command/command.h"
//#include "../Engine/Input/input.h"

#include <SFML/Window/Event.hpp>

#include <map>


//class CommandQueue;

class Player
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
//		LaunchMissile,
//		ActionCount
	};

//	enum class MissionStatus
//	{
//		MissionRunning,
//		MissionSuccess,
//		MissionFailure
//	};


public:
	Player();

//	void					handleEvent(const sf::Event& event, CommandQueue& commands);
//	void					handleRealtimeInput(CommandQueue& commands);

//	void					assignKeyboardKey(Action action, sf::Keyboard::Key key);
//	void					assignMouseButton(Action action, sf::Mouse::Button button);
//	sf::Keyboard::Key       getAssignedKeyboardKey(Action action) const;
//	sf::Mouse::Button       getAssignedMouseButton(Action action) const;

//	void					setMissionStatus(MissionStatus status);
//	MissionStatus			getMissionStatus() const;


private:
//	void					initializeActions();
//	static bool				isRealtimeAction(Action action);


private:
//	std::map<sf::Keyboard::Key, Action>		  mKeyboardBinding;
//	std::map<sf::Mouse::Button, Action>		  mMouseBinding;
	// ALW - TODO - Joystick binding
//	std::map<Action, Command>				  mActionBinding;
//	MissionStatus							  mCurrentMissionStatus;
};

#endif
