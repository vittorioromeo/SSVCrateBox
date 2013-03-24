#ifndef CLIFT_H
#define CLIFT_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SSVEntitySystem/SSVEntitySystem.h>
#include <SSVSCollision/SSVSCollision.h>
#include "CBGame.h"

namespace cb
{
	class CLift : public sses::Component
	{
		private:
			CBGame& cbGame;
			ssvsc::Body& body;
			sf::Vector2f velocity;

		public:
			CLift(sses::Entity& mEntity, CBGame& mCBGame, ssvsc::Body& mBody, sf::Vector2f mVelocity);
			void update(float) override;
	};
}

#endif
