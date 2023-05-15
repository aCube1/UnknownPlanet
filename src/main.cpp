#include "Engine.hpp"
#include "ResourceManager.hpp"
#include "spdlog/spdlog.h"

#include <cstdlib>
#include <exception>

static const auto WINDOW_WIDTH { 960 };
static const auto WINDOW_HEIGHT { 540 };

static void loadResources() {
	using game::ResourceManager;

	ResourceManager::loadFont("andybold", "assets/fonts/andybold.ttf");
}

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
		loadResources();
		runEngine();
	} catch (const std::exception& e) {
		spdlog::error("{}", e.what());
	}

	return EXIT_SUCCESS;
}
