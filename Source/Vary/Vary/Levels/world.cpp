#include "world.h"
#include "../Resources/resourceIdentifiers.h"

#include "Trambo/SceneNodes/spriteNode.h"
#include "Trambo/Sounds/soundPlayer.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <algorithm>


World::World(sf::RenderTarget& outputTarget, trmb::FontHolder& fonts, trmb::SoundPlayer& sounds)
: mTarget(outputTarget)
, mCamera(outputTarget.getDefaultView())
, mTextures()
, mFonts(fonts)
, mSounds(sounds)
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, 1600.0, 1200.0)
, mSpawnPosition(mWorldBounds.width / 2.f, mWorldBounds.height / 2.f)
, mHero(nullptr)
{
	loadTextures();
	buildScene();

	// ALW - Center the camera on the hero
	mCamera.getView().setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	mSceneGraph.update(dt);			// ALW - Update the hero along with the rest of the scene graph
	correctHeroPosition();			// ALW - Keep hero in world boundaries
	mCamera.update(mWorldBounds);   // ALW - Update the camera position
}

void World::draw()
{
	mTarget.setView(mCamera.getView());
	mTarget.draw(mSceneGraph);
}

void World::loadTextures()
{
	mTextures.load(Textures::ID::Grass,      "Data/Textures/Grass.png");
	mTextures.load(Textures::ID::Heroes,	 "Data/Textures/Heroes.png");
}

void World::correctHeroPosition()
{
	// ALW - If the camera moves outside the boundaries of the world then
	// ALW - move it back to the world boundary.
	sf::Vector2f position = mHero->getPosition();

	sf::Vector2f heroHalfDimensions; // ALW - Accounts for origin being set to the center of the sprite
	heroHalfDimensions.x = mHero->getBoundingRect().width / 2.0f;
	heroHalfDimensions.y = mHero->getBoundingRect().height / 2.0f;

	position.x = std::max(position.x, mWorldBounds.left + heroHalfDimensions.x);
	position.x = std::min(position.x, mWorldBounds.left + mWorldBounds.width - heroHalfDimensions.x);
	position.y = std::max(position.y, mWorldBounds.top + heroHalfDimensions.y);
	position.y = std::min(position.y, mWorldBounds.top + mWorldBounds.height - heroHalfDimensions.y);

	mHero->setPosition(position);
}

void World::buildScene()
{
	// Initialize the different layers

	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		trmb::SceneNode::Ptr layer(new trmb::SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture &GrassTexture = mTextures.get(Textures::ID::Grass);
	GrassTexture.setRepeated(true);

	sf::IntRect textureRect(mWorldBounds);

	// Add the background sprite to the scene
	std::unique_ptr<trmb::SpriteNode> GrassSprite(new trmb::SpriteNode(GrassTexture, textureRect));
	GrassSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(GrassSprite));

	// Add player's character
	std::unique_ptr<Hero> player(new Hero(Hero::Type::Wizard, mTextures, mFonts));
	mHero = player.get();
	mHero->setPosition(mSpawnPosition);
	mSceneLayers[Middleground]->attachChild(std::move(player));
	mCamera.setHero(mHero);
}
