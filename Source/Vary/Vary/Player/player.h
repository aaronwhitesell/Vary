#ifndef PLAYER_H
#define PLAYER_H

#include "controller.h"


namespace sf
{
	class Event;
}

class Player
{
public:
							Player();
							Player(const Player &) = delete;
	Player &				operator=(const Player &) = delete;

	const Controller &		getController() const;
	Controller &			getController();

	void					update();
	void					handleEvent(const sf::Event &inputEvent);


private:
	Controller								mController;
};

#endif
