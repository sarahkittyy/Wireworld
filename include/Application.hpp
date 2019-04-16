#pragma once

#include <SFML/Graphics.hpp>

#include "InfiniteGrid.hpp"
#include "Wireworld.hpp"

/**
 * @brief Base app class.
 * 
 */
class Application
{
public:
	/**
	 * @brief Init the app.
	 * 
	 */
	Application();

	/**
	 * @brief Main app loop, equivalent to main().
	 * 
	 * @return int Exit code of the program.
	 */
	int run();

private:
	/**
	 * @brief The app window.
	 * 
	 */
	sf::RenderWindow mWindow;

	/**
	 * @brief The app wireworld simulation.
	 * 
	 */
	Wireworld mSimulation;
};