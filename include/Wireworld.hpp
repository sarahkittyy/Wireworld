#pragma once

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <unordered_map>
#include <vector>

#include "Cell.hpp"
#include "InfiniteGrid.hpp"

/**
 * @brief Encapsulates and controls an InfiniteGrid instance to
 * react to input & simulate Wireworld cellular automata.
 * 
 */
class Wireworld : public sf::Drawable
{
public:
	/**
	 * @brief Construct a new Wireworld instance.
	 * 
	 * @param window A pointer to the app window.
	 */
	Wireworld(sf::RenderWindow* window);

	/**
	 * @brief Toggle if the simulation is running or not.
	 * 
	 */
	void toggleRunning();

	/**
	 * @return True If the simulation is running.
	 *  
	 */
	bool isRunning();

	/**
	 * @brief Set the Speed of the simulation.
	 * 
	 * @param newSpeed The new speed of the simulation.
	 */
	void setSpeed(sf::Time newSpeed);

	/**
	 * @brief Get the Speed of the simulation.
	 * 
	 * @return sf::Time The speed of the simul.
	 */
	sf::Time getSpeed();

	/**
	 * @brief Update the simulation.
	 * 
	 * @remarks Call once per frame.
	 * 
	 */
	void update();

	/**
	 * @brief Advance the simulation forward one step.
	 * 
	 */
	void step();

	/////////EVENT HANDLERS///////////

	/**
	 * @brief Called on every mouse press.
	 * 
	 * @param btn The mouse button pressed.
	 */
	void onMousePress(sf::Mouse::Button btn);

	/**
	 * @brief Called on every mouse release.
	 * 
	 * @param btn The button released.
	 */
	void onMouseRelease(sf::Mouse::Button btn);

	/**
	 * @brief Called on every key press.
	 * 
	 * @param key The key pressed.
	 */
	void onKeyPress(sf::Keyboard::Key key);

	/**
	 * @brief Called on every key release.
	 * 
	 * @param key The key released.
	 */
	void onKeyRelease(sf::Keyboard::Key key);

	/**
	 * @brief Either push the new cell, or update the cell that already exists, if it's there.
	 * 
	 * @param c The cell to add/update.
	 */
	void setCell(Cell c);

	/**
	 * @brief Check if there's a cell at the given position.
	 * 
	 * @param pos The position to check.
	 * @return true If there is a cell there.
	 * @return false If the square is empty.
	 */
	bool isCell(sf::Vector2i pos);

	/**
	 * @brief Get the cell located at the given position.
	 * 
	 * @param pos The position.
	 * @return Cell The cell at `pos`
	 * 
	 * @remarks Returns a white cell @ 0,0 if there is none. 
	 * Use isCell(pos) to check if there's a cell there in the first place.
	 */
	Cell getCell(sf::Vector2i pos);

	/**
	 * @brief Remove the cell at the given position, if it exists.
	 * 
	 * @param pos 
	 */
	void clearCell(sf::Vector2i pos);

private:
	/**
	 * @brief SFML's draw() override.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief Pointer to the main app window.
	 * 
	 */
	sf::RenderWindow* mWindow;

	/**
	 * @brief The game grid.
	 * 
	 */
	InfiniteGrid mGrid;

	/**
	 * @brief The vector of actual game cells.
	 * 
	 */
	std::vector<Cell> mCells;

	/**
	 * @brief The constant mapping of cell types to colors.
	 * 
	 */
	const std::unordered_map<Cell::Type, sf::Color> CELL_COLORS = {
		{Cell::NONE, sf::Color::White},
		{Cell::HEAD, sf::Color::Blue},
		{Cell::TAIL, sf::Color::Red},
		{Cell::WIRE, sf::Color::Yellow}};

	/**
	 * @brief Get a pointer to the cell at the given position.
	 * 
	 * @param pos The position.
	 * @return Cell* The cell at that position. Nullptr if it doesn't exist.
	 */
	Cell* getCellPtr(sf::Vector2i pos);

	/**
	 * @brief Get the position of the mouse as a cell position, not a window position.
	 * 
	 * @return sf::Vector2i The cell the mouse is hovering over.
	 */
	sf::Vector2i getMousePos();

	/**
	 * @brief Check if the mouse is inside the viewable window.
	 * 
	 * @return true If the mouse is inside the window.
	 * @return false Otherwise.
	 */
	bool isMouseValid();

	/**
	 * @brief The internal simulation clock.
	 * 
	 */
	sf::Clock mClock;

	/**
	 * @brief The speed of the simulation.
	 * 
	 */
	sf::Time mSpeed;

	/**
	 * @brief Whether or not the simulation is running.
	 * 
	 */
	bool mRunning;
};