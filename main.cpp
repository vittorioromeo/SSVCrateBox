// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <string>
#include <SSVStart.h>
#include "CBData.h"
#include "CBGame.h"

using namespace cb;
using namespace std;
using namespace ssvs;
using namespace ssvs::Utils;
using namespace ssvu;

int main()
{
	srand(unsigned(time(NULL)));

	string title{"Super Crate Box clone " + toStr<float>(0.1f) + " - vee software"};

	GameWindow gameWindow{title, 320, 240, 2, false};
	gameWindow.setFPSLimit(300.f);

	CBData data;
	CBGame cbGame{data, gameWindow};

	gameWindow.setGameState(cbGame.getGameState());
	gameWindow.run();

	return 0;
}
