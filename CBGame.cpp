// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "CBGame.h"
#include "Components/CPhysics.h"
#include "CBFactory.h"
#include "Utils.h"

using namespace ssvs;
using namespace ssvsc;
using namespace ssvsc::Utils;
using namespace ssvs::Utils;
using namespace ssvs::Input;
using namespace sses;
using namespace sf;

namespace cb
{
	CBGame::CBGame(CBData& mData, ssvs::GameWindow& mGameWindow) : data(mData), world(createResolver<Retro>(), createSpatial<Grid>(600, 600, 2500, 300)),
		factory{new CBFactory{*this, manager, world}}, gameWindow(mGameWindow)

	{
		initInput(); initUpdate(); initDraw();

		int tilesX{320 / 16}, tilesY{240 / 16};

		for(int iY{0}; iY < tilesY; iY++)
			for(int iX{0}; iX < tilesX; iX++)
				if(iX == 0 || iY == 0 || iX == tilesX - 1 || iY == tilesY - 1)
					factory->createWall({1600 * iX + 800, 1600 * iY + 800});						

		factory->createBox({1600 * 4 + 800, 1600 * 4 + 800});
		factory->createBox({1600 * 4 + 800, 1600 * 4 + 800});
		factory->createWall({1600 * 7 + 800, 1600 * 7 + 800});
		factory->createWall({1600 * 8 + 800, 1600 * 7 + 800});
		factory->createWall({1600 * 2 + 800, 1600 * 10 + 800});
		factory->createWall({1600 * 3 + 800, 1600 * 10 + 800});
		factory->createPlayer({1600 * 6 + 800, 1600 * 4 + 800});
	}
	CBGame::~CBGame() { delete factory; }

	void CBGame::initInput()
	{
		using k = Keyboard::Key;

		gameState.addInput({{k::Escape}}, [&](float){ gameWindow.stop(); });

		gameState.addInput({{k::A}}, 	[=](float mFrameTime){ camera.move(Vector2f{-10, 0} * mFrameTime); });
		gameState.addInput({{k::D}}, 	[=](float mFrameTime){ camera.move(Vector2f{10, 0} * mFrameTime); });
		gameState.addInput({{k::W}}, 	[=](float mFrameTime){ camera.move(Vector2f{0, -10} * mFrameTime); });
		gameState.addInput({{k::S}}, 	[=](float mFrameTime){ camera.move(Vector2f{0, 10} * mFrameTime); });
		gameState.addInput({{k::Q}}, 	[=](float mFrameTime){ camera.zoom(pow(1.1f, mFrameTime)); });
		gameState.addInput({{k::E}}, 	[=](float mFrameTime){ camera.zoom(pow(0.9f, mFrameTime)); });

		gameState.addInput({{k::Left}}, 	[&](float){ inputX = -1; });
		gameState.addInput({{k::Right}}, 	[&](float){ inputX = 1; });
		gameState.addInput({{k::Up}}, 		[&](float){ inputY = -1; });
		gameState.addInput({{k::Down}}, 	[&](float){ inputY = 1; });
		gameState.addInput({{k::Z}}, 		[&](float){ inputShoot = 1; });
		gameState.addInput({{k::X}}, 		[&](float){ inputJump = 1; });

		gameState.addInput({{k::Numpad1}}, [&](float)
		{
			auto mousePosition = camera.getMousePosition() * 100.f;
			factory->createWall(Vector2i(mousePosition.x, mousePosition.y));
		}, Trigger::Types::SINGLE);

		gameState.addInput({{k::Numpad2}}, [&](float)
		{
			auto mousePosition = camera.getMousePosition() * 100.f;
			factory->createBox(Vector2i(mousePosition.x, mousePosition.y));
		}, Trigger::Types::SINGLE);

		gameState.addInput({{k::Numpad3}}, [&](float)
		{
			auto mousePosition = camera.getMousePosition() * 100.f;
			factory->createLift(Vector2i(mousePosition.x, mousePosition.y), {0, -20});
		}, Trigger::Types::SINGLE);

		gameState.addInput({{k::Numpad4}}, [&](float)
		{
			auto mousePosition = camera.getMousePosition() * 100.f;
			factory->createLift(Vector2i(mousePosition.x, mousePosition.y), {0, 20});
		}, Trigger::Types::SINGLE);

		gameState.addInput({{k::Numpad5}}, [&](float)
		{
			auto mousePosition = camera.getMousePosition() * 100.f;
			factory->createLift(Vector2i(mousePosition.x, mousePosition.y), {-20, 0});
		}, Trigger::Types::SINGLE);

		gameState.addInput({{k::Numpad6}}, [&](float)
		{
			auto mousePosition = camera.getMousePosition() * 100.f;
			factory->createLift(Vector2i(mousePosition.x, mousePosition.y), {20, 0});
		}, Trigger::Types::SINGLE);

		gameState.addInput({{k::Numpad7}}, [&](float)
		{
			auto mousePosition = camera.getMousePosition() * 100.f;
			factory->createMetalBox(Vector2i(mousePosition.x, mousePosition.y));
		}, Trigger::Types::SINGLE);
	}

	void CBGame::initUpdate()
	{
		gameState.onUpdate += [&](float){ gameWindow.setTitle(toStr(gameWindow.getFPS())); };
		gameState.onUpdate += [&](float){ for(auto cPhysics : manager.getComponents<CPhysics>("physics")) if(!cPhysics->isNoGravity()) cPhysics->getBody().applyForce({0, 25}); };
		gameState.onUpdate += [&](float mFrameTime){ world.update(mFrameTime); };
		gameState.onUpdate += [&](float mFrameTime){ manager.update(mFrameTime); };
		gameState.onUpdate += [&](float mFrameTime){ timelineManager.update(mFrameTime); };
		gameState.onUpdate += [&](float){ inputX = inputY = inputShoot = inputJump = 0; };
	}

	void CBGame::initDraw()
	{
		gameState.onDraw += [&]{ camera.apply(); };
		gameState.onDraw += [&]{ manager.draw(); };
		gameState.onDraw += [&]{ camera.unapply(); };
	}

	void CBGame::render(Drawable &mDrawable) { gameWindow.draw(mDrawable); }

	CBData& CBGame::getData() 			{ return data; }
	GameState& CBGame::getGameState() 	{ return gameState; }
	GameWindow& CBGame::getGameWindow()	{ return gameWindow; }
	int CBGame::getInputX() 			{ return inputX; }
	int CBGame::getInputY() 			{ return inputY; }
	int CBGame::getInputShoot() 		{ return inputShoot; }
	int CBGame::getInputJump() 			{ return inputJump; }
}
