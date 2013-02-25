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
			bool noGravity{false};

			sf::Vector2i lastResolution;
			bool crushLeft{false}, crushRight{false}, crushTop{false}, crushBottom{false};

		public:
			ssvs::Delegate<void, sses::Entity&> onDetection;
			ssvs::Delegate<void, sf::Vector2i> onResolution;

			CPhysics(CBGame& mCBGame, ssvsc::World& mWorld, bool mIsStatic, sf::Vector2i mPosition, sf::Vector2i mSize, bool mNoGravity = false);
			~CPhysics();

			void init() override;

			ssvsc::Body& getBody();
			bool isNoGravity();
	};
}

#endif // CPHYSICS_H
