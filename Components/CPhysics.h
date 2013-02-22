// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef CPHYSICS_H
#define CPHYSICS_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <SSVEntitySystem.h>
#include <SSVSCollision.h>
#include <SSVStart.h>
#include "CBGame.h"

namespace cb
{
	class CPhysics : public sses::Component
	{
		private:
			CBGame& cbGame;
			ssvsc::World& world;
			ssvsc::Body& body;

		public:
			ssvs::Delegate<void, sses::Entity&> onDetection;
			ssvs::Delegate<void, sf::Vector2i> onResolution;

			CPhysics(CBGame& mCBGame, ssvsc::World& mWorld, bool mIsStatic, sf::Vector2i mPosition, sf::Vector2i mSize);
			~CPhysics();

			void init() override;

			ssvsc::Body& getBody();
	};
}

#endif // CPHYSICS_H
