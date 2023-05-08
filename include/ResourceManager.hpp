#ifndef _GAME_RESOURCE_MANAGER_HPP_
#define _GAME_RESOURCE_MANAGER_HPP_

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <unordered_map>

namespace game {
	class ResourceManager {
		public:
			static const sf::Texture& loadTexture(
				const std::string& key, const std::filesystem::path& path
			);
			[[nodiscard]] static const sf::Texture& getTexture(const std::string& key);
			static void deleteTexture(const std::string& key);

			static const sf::Font& loadFont(
				const std::string& key, const std::filesystem::path& path
			);
			[[nodiscard]] static const sf::Font& getFont(const std::string& key);
			static void deleteFont(const std::string& key);

		private:
			static std::unordered_map<std::string, sf::Texture> m_textures;
			static std::unordered_map<std::string, sf::Font> m_fonts;
	};
} // namespace game

#endif // _GAME_RESOURCE_MANAGER_HPP_
