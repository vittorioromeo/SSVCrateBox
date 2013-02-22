// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef CBDATA_H
#define CBDATA_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SSVStart.h>

namespace cb
{
	class CBData
	{
		private:
			ssvs::AssetManager* assetManager;

		public:
			CBData();
			~CBData();

			ssvs::AssetManager& getAssetManager();
			sf::Texture& getTexture(std::string mId);
	};
}

#endif // CBDATA_H
