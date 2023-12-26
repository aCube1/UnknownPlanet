#ifndef _STATEMACHINE_HPP_
#define _STATEMACHINE_HPP_

#include "NonCopyable.hpp"
#include "state/Base.hpp"
#include "types.hpp"

#include <memory>
#include <unordered_map>

struct StateSet {
	std::shared_ptr<state::Base> state;
	std::vector<usize> paths; /* Possible states that this state can switch to */
};

class StateMachine : NonCopyable {
private:
	std::unordered_map<usize, StateSet> m_states;
	StateSet m_current {};

	usize m_next { 0 }; /* Zero means NO_STATE */

public:
	StateMachine(std::unordered_map<usize, StateSet> states)
		: m_states { std::move(states) } {}

	StateMachine() = default;
	~StateMachine() = default;

	void add_state(usize id, const StateSet& state);

	void switch_to(usize id);

	void update(float delta);
	void render(sf::RenderWindow& window);

private:
	void finish_switch();
};

#endif // _STATEMACHINE_HPP_
