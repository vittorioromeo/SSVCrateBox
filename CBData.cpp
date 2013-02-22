// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "CBData.h"

using namespace sf;
using namespace ssvs;
using namespace std;

namespace cb
{
	CBData::CBData() : assetManager{new AssetManager} { assetManager->loadFolder("Data/"); }
	CBData::~CBData() { delete assetManager; }
	AssetManager& CBData::getAssetManager() { return *assetManager; }
	Texture& CBData::getTexture(string mId) { return getAssetManager().getTexture(mId); }
}
