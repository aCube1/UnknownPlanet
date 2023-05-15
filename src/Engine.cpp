#include "Engine.hpp"

#include "ResourceManager.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <cstdint>

// Default view size.
static const auto SCREEN_WIDTH { 960 };
static const auto SCREEN_HEIGHT { 540 };

namespace game {
	Engine::Engine(int width, int height)
		: m_camera(sf::FloatRect(0.0F, 0.0F, SCREEN_WIDTH, SCREEN_HEIGHT)) {
		createWindow(width, height);

		m_running = true;
	}

	void Engine::handleEvents() {
		while (m_window.pollEvent(m_event)) {
			if (m_event.type == sf::Event::Closed) {
				m_running = false;
				m_window.close();
			}
		}
	}

	void Engine::update(float dt) {
		(void)dt;
	}

	void Engine::render() {
		m_window.clear();
		m_window.display();
	}

	void Engine::createWindow(int width, int height) {
		// NOTE: The window is not resizeable.
		uint32_t window_style { sf::Style::Close | sf::Style::Titlebar };

		m_window.create(sf::VideoMode(width, height), "Unknown Planet", window_style);
		m_window.setPosition(sf::Vector2i(0, 0)); // NOTE: Window position is always 0x0.
		m_window.setView(m_camera);
		m_window.setVerticalSyncEnabled(true); // TODO: Make vsync optional.

		// Load icon texture and send pixels to the window.
		auto icon { ResourceManager::loadTexture("icon", "icon.png").copyToImage() };
		auto icon_size { icon.getSize() };
		m_window.setIcon(icon_size.x, icon_size.y, icon.getPixelsPtr());
	}
} // namespace game
