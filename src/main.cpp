#include "Engine.hpp"
#include "spdlog/spdlog.h"

#include <cstdlib>
#include <exception>

static const auto WINDOW_WIDTH { 940 };
static const auto WINDOW_HEIGHT { 460 };

static void runEngine() {
	auto engine { game::Engine(WINDOW_WIDTH, WINDOW_HEIGHT) };
	sf::Clock clock {};

	while (engine.isRunning()) {
		auto dt { clock.restart().asSeconds() };

		engine.handleEvents();
		engine.update(dt);
		engine.render();
	}
}

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	try {
		runEngine();
	} catch (const std::exception& e) {
		spdlog::error("{}", e.what());
	}

	return EXIT_SUCCESS;
}
