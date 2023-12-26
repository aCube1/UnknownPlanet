#ifndef _STATE_BASE_HPP_
#define _STATE_BASE_HPP_

#include <SFML/Graphics/RenderWindow.hpp>

class Engine;

namespace state {
	class Base {
	protected:
		Engine& m_engine;

	public:
		Base(Engine& engine)
			: m_engine { engine } {}

		virtual ~Base() = default;

		virtual void on_enter() {}

		virtual void on_exit() {}

		virtual void on_update(float delta) = 0;
		virtual void on_render(sf::RenderWindow& window) = 0;
	};
} // namespace state

#endif // _STATES_BASE_HPP_
