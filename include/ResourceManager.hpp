#ifndef _GAME_RESOURCE_MANAGER_HPP_
#define _GAME_RESOURCE_MANAGER_HPP_

#include <filesystem>
#include <unordered_map>

namespace sf {
	class Texture;
	class Font;
} // namespace sf

namespace game {
	class ResourceManager final {
		public:
			// Verify if there's a texture with the key name.
			// If not, load texture from file, emplace it in m_textures and
			// return a reference.
			// Throw an exception if is unable to load texture.
			static const sf::Texture& loadTexture(
				const std::string& key, const std::filesystem::path& path
			);

			// Return a reference of a already loaded texture.
			// Throw an exception if texture doesn't exist.
			[[nodiscard]] static const sf::Texture& getTexture(const std::string& key);

			// Unload texture.
			static void deleteTexture(const std::string& key);

			// Verify if there's a font with the key name.
			// If not, load font from file, emplace it in m_fonts and
			// return a reference.
			// Throw an exception if is unable to load fonts.
			static const sf::Font& loadFont(
				const std::string& key, const std::filesystem::path& path
			);

			// Return a reference of a already loaded font.
			// Throw an exception if font doesn't exist.
			[[nodiscard]] static const sf::Font& getFont(const std::string& key);

			// Unload font.
			static void deleteFont(const std::string& key);

		private:
			static std::unordered_map<std::string, sf::Texture> m_textures;
			static std::unordered_map<std::string, sf::Font> m_fonts;
	};
} // namespace game

#endif // _GAME_RESOURCE_MANAGER_HPP_
