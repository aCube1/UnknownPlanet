#ifndef _GAME_ENGINE_HPP_
#define _GAME_ENGINE_HPP_

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace game {
	class Engine {
		public:
			Engine() = delete;
			Engine(int width, int height);
			~Engine() = default;

			void handleEvents();
			void update(float dt);
			void render();

			[[nodiscard]] bool isRunning() const { return m_running; }

		private:
			sf::RenderWindow m_window;
			sf::View m_camera;
			sf::Event m_event;

			sf::Text m_debug_text; // TEST: Remove later

			bool m_running {};
	};
} // namespace game

#endif // _GAME_ENGINE_HPP_
