#include "hero.h"
#include "../Resources/resourceIdentifiers.h"

#include "../../../3rdParty/TinyXML2/tinyxml2.h"

#include "Trambo/Events/event.h"
#include "Trambo/Inputs/actionBinding.h"
#include "Trambo/Utilities/utility.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>


Hero::Hero(Type type, const trmb::TextureHolder &textures, const trmb::FontHolder &fonts)
: Entity()
, mType(type)
, mSprite()
{
	readXML(mType);
	setHitpoints(mData.hitpoints);
	mSprite.setTexture(textures.get(mData.texture));
	mSprite.setTextureRect(mData.textureRect);

	trmb::centerOrigin(mSprite);
}

void Hero::handleEvent(const trmb::Event &gameEvent)
{
	// ALW - These GUIDs match the GUIDs in the Controller class.
	const trmb::ActionBinding::EventGuid mUp = 0x84b05719;
	const trmb::ActionBinding::EventGuid mDown = 0xa95ea771;
	const trmb::ActionBinding::EventGuid mLeft = 0x84e6c13c;
	const trmb::ActionBinding::EventGuid mRight = 0x19e343e8;
	const trmb::ActionBinding::EventGuid mJump = 0x6955d309;
	const trmb::ActionBinding::EventGuid mShoot = 0x3e6524cd;

	switch (gameEvent.getType())
	{
	case mUp:
		accelerate(0.0f, -1.0f);
		break;
	case mDown:
		accelerate(0.0f, 1.0f);
		break;
	case mLeft:
		accelerate(-1.0f, 0.0f);
		break;
	case mRight:
		accelerate(1.0f, 0.0f);
		break;
	}
}

void Hero::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
		target.draw(mSprite, states);
}

void Hero::updateCurrent(sf::Time dt)
{
	accelerate(trmb::Entity::getVelocity() * getMaxSpeed());

	trmb::Entity::updateCurrent(dt);
}

sf::FloatRect Hero::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Hero::isAllied() const
{
	return mType == Type::Priest
		|| mType == Type::Warrior
		|| mType == Type::Wizard;
}

float Hero::getMaxSpeed() const
{
	return mData.speed;
}

std::string Hero::toString(Type type) const
{
	std::string ret;
	switch (type)
	{
		case Type::Priest:
			ret = "priest";
			break;

		case Type::Warrior:
			ret = "warrior";
			break;

		case Type::Wizard:
			ret = "wizard";
			break;
	}

	// ALW - Will assert if type does not correspond to a string
	assert(ret.compare("") != 0);
	return ret;
}

Textures::ID Hero::toTexture(const std::string& str) const
{
	Textures::ID ret;
	bool success = false;
	if (str == "Textures::ID::Heroes")
	{
		// ALW - Should match str (fragile)
		ret = Textures::ID::Heroes;
		success = true;
	}

	// ALW - Will assert if str does not correspond to a Textures::ID
	assert(success);
	return ret;
}

void Hero::readXML(Type type)
{
	const std::string filename("Data/Configs/Heroes.xml");
	tinyxml2::XMLDocument config;
	if (config.LoadFile(filename.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		throw std::runtime_error("TinyXML2 - Failed to load " + filename);
	}

	tinyxml2::XMLElement *element = config.FirstChildElement()->FirstChildElement(toString(type).c_str());
	if (!element)
	{
		// ALW - Will assert if the type's element does not exist
		assert(element);
	}

	mData.hitpoints        = element->FirstChildElement("hitpoints")->IntAttribute("attribute");
	mData.speed            = element->FirstChildElement("speed")->FloatAttribute("attribute");
	mData.fireInterval     = sf::seconds(element->FirstChildElement("fireInterval")->FloatAttribute("attribute"));
	mData.texture          = toTexture(element->FirstChildElement("texture")->Attribute("attribute"));

	const int left         = element->FirstChildElement("textureRect")->IntAttribute("attribute0");
	const int top          = element->FirstChildElement("textureRect")->IntAttribute("attribute1");
	const int width        = element->FirstChildElement("textureRect")->IntAttribute("attribute2");
	const int height       = element->FirstChildElement("textureRect")->IntAttribute("attribute3");
	mData.textureRect      = sf::IntRect(left, top, width, height);
}
