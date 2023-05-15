#include "ResourceManager.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace game {
	std::unordered_map<std::string, sf::Font> ResourceManager::m_fonts {};
	std::unordered_map<std::string, sf::Texture> ResourceManager::m_textures {};

	const sf::Texture& ResourceManager::loadTexture(
		const std::string& key, const std::filesystem::path& path
	) {
		// Verify if the path is empty or is an invalid extension.
		// TODO: Allow more file extensions.
		if (path.empty() || path.extension() != ".png") {
			throw std::runtime_error("Invalid texture file: " + path.string());
		}

		// Try to emplace a new texture instance.
		auto texture { m_textures.try_emplace(key, sf::Texture()) };

		// If insertion happened, load texture from file.
		if (texture.second && !texture.first->second.loadFromFile(path)) {
			throw std::runtime_error(
				"Failed to load texture from file: " + path.string()
			);
		}

		return texture.first->second;
	}

	const sf::Texture& ResourceManager::getTexture(const std::string& key) {
		return m_textures.at(key);
	}

	void ResourceManager::deleteTexture(const std::string& key) {
		auto it { m_textures.find(key) };
		if (it != m_textures.end()) {
			m_textures.erase(it);
		}
	}

	const sf::Font& ResourceManager::loadFont(
		const std::string& key, const std::filesystem::path& path
	) {
		// Verify if the path is empty or is an invalid extension.
		if (path.empty() || path.extension() != ".ttf") {
			throw std::runtime_error("Invalid font file: " + path.string());
		}

		// Try to emplace a new font instance.
		auto font { m_fonts.try_emplace(key, sf::Font()) };

		// If insertion happened, load font from file.
		if (font.second && !font.first->second.loadFromFile(path)) {
			throw std::runtime_error("Failed to load font from file: " + path.string());
		}

		return font.first->second;
	}

	const sf::Font& ResourceManager::getFont(const std::string& key) {
		return m_fonts.at(key);
	}

	void ResourceManager::deleteFont(const std::string& key) {
		auto it { m_fonts.find(key) };
		if (it != m_fonts.end()) {
			m_fonts.erase(it);
		}
	}
} // namespace game
