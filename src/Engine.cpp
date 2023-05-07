#include "Engine.hpp"

#include <cstdint>

// Default view size.
static const auto SCREEN_WIDTH { 940 };
static const auto SCREEN_HEIGHT { 460 };

namespace game {
	Engine::Engine(int width, int height) {
		// NOTE: The window is not resizeable.
		uint32_t window_style { sf::Style::Close | sf::Style::Titlebar };

		m_camera = sf::View();
		m_camera.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		m_camera.setCenter(0, 0);

		m_window.create(sf::VideoMode(width, height), "Unknown Planet", window_style);
		m_window.setView(m_camera);
		m_window.setVerticalSyncEnabled(true); // TODO: Make vsync optional.

		m_running = true;

		// TEST: Remove later.
		m_rect.setSize(sf::Vector2f(64.0F, 64.0F));
		m_rect.setOutlineColor(sf::Color::Red);
		m_rect.setOutlineThickness(5);
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
		m_window.draw(m_rect);
		m_window.display();
	}
} // namespace game
