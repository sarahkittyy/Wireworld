#pragma once

#include <SFML/Graphics.hpp>

#include <imgui/imgui-SFML.h>
#include <imgui/imgui.h>

#include "InfiniteGrid.hpp"

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
};