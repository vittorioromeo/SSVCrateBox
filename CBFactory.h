// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef CBFACTORY_H
#define CBFACTORY_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <SSVStart.h>
#include <SSVEntitySystem.h>
#include <SSVSCollision.h>
#include "CBGame.h"

namespace cb
{
	class CBFactory
	{
		private:
			CBGame& cbGame;
			sses::Manager& manager;
			ssvsc::World& world;

		public:
			CBFactory(CBGame& mCBGame, sses::Manager& mManager, ssvsc::World& mWorld);

			sses::Entity& createWall(sf::Vector2i mPosition);
			sses::Entity& createBox(sf::Vector2i mPosition);
			sses::Entity& createPlayer(sf::Vector2i mPosition);
			sses::Entity& createLift(sf::Vector2i mPosition, sf::Vector2f mVelocity);
			sses::Entity& createMetalBox(sf::Vector2i mPosition);
	};
}

#endif // CBFACTORY_H
