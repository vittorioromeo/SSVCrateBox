// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef CBGAME_H
#define CBGAME_H

#include <SSVStart/SSVStart.h>
#include <SSVEntitySystem/SSVEntitySystem.h>
#include <SSVSCollision/SSVSCollision.h>
#include <SFML/Graphics.hpp>
#include "CBData.h"

namespace cb
{
	class CBFactory;

	class CBGame
	{
		private:
			CBData& data;
			ssvsc::World world;
			CBFactory* factory;
			ssvs::GameState gameState;
			ssvs::GameWindow& gameWindow;
			ssvs::Camera camera{gameWindow, {{160, 120}, {320, 240}}};
			ssvu::TimelineManager timelineManager;
			sses::Manager manager;
			int inputX{0}, inputY{0}, inputShoot{0}, inputJump{0};

			void initInput();
			void initUpdate();
			void initDraw();

		public:
			CBGame(CBData& mData, ssvs::GameWindow& mGameWindow);
			~CBGame();
			
			void render(sf::Drawable& mDrawable);

			CBData& getData();
			ssvs::GameState& getGameState();
			ssvs::GameWindow& getGameWindow();
			int getInputX();
			int getInputY();
			int getInputShoot();
			int getInputJump();
	};
}

#endif // CBGAME_H
