// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef CRENDER_H
#define CRENDER_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SSVEntitySystem/SSVEntitySystem.h>
#include <SSVSCollision.h>
#include "CBGame.h"

namespace cb
{
	class CRender : public sses::Component
	{
		private:
			CBGame& cbGame;
			ssvsc::Body& body;
			sf::Sprite sprite;
			bool flippedX{false}, flippedY{false};

		public:
			CRender(sses::Entity& mEntity, CBGame& mCBGame, ssvsc::Body& mBody, std::string mTextureId);

			void update(float) override;
			void draw() override;

			void setRotation(float mDegrees);
			void setFlippedX(bool mFlippedX);
			void setFlippedY(bool mFlippedY);
			bool isFlippedX() const;
			bool isFlippedY() const;
			sf::Sprite& getSprite();
	};
}

#endif
