#include "ResourceManager.hpp"

namespace game {
	std::unordered_map<std::string, sf::Font> ResourceManager::m_fonts {};

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
			throw std::runtime_error("Unable to load font: " + path.string());
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
