#include "StateMachine.hpp"

void StateMachine::add_state(usize id, const StateSet& state) {
	if (id != 0 && state.state != nullptr) {
		m_states.insert_or_assign(id, state);
	}
}

void StateMachine::switch_to(usize id) {
	if (id != 0) {
		m_next = id;
	}
}

void StateMachine::update(float delta) {
	finish_switch();

	if (m_current.state != nullptr) {
		m_current.state->on_update(delta);
	}
}

void StateMachine::render(sf::RenderWindow& window) {
	if (m_current.state != nullptr) {
		m_current.state->on_render(window);
	}
}

void StateMachine::finish_switch() {
	// Can we can go to the Next State?
	if (m_next == 0 || !m_states.contains(m_next)) {
		return;
	}

	const auto& paths { m_current.paths };

	// Check if Current State can switch to Next State
	const auto it { std::find(paths.cbegin(), paths.cend(), m_next) };
	if (it == paths.end()) {
		return;
	}

	// Get Id to the Next State
	const auto next_id { std::distance(paths.cbegin(), it) };

	// Exit Current, get and enter Next State
	m_current.state->on_exit();
	m_current = m_states.at(next_id);
	m_current.state->on_enter();
}
