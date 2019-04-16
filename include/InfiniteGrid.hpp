#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief Renders an infinite grid of colored cells to the window.
 * Contains method for resizing the grid, and setting the top-left position of the grid to any point in space.
 * 
 */
class InfiniteGrid : public sf::Drawable
{
public:
	struct Cell
	{
		sf::Vector2i pos;
		sf::Color col;
	};

	InfiniteGrid(sf::Vector2u window_size);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief Initialize all vertex arrays that need to be.
	 * 
	 */
	void init();

	/**
	 * @brief Init the grid lines. Only needs to be run once.
	 * 
	 */
	void initLines();

	/**
	 * @brief Update the grid lines & cells.
	 * 
	 */
	void update();

	/**
	 * @brief Instead of updating all the vertices of the grid lines
	 * each update, we simply update mGridLineTransform, since the lines
	 * only deviate by a portion of the cell size max at any time.
	 * 
	 */
	void updateLines();

	/**
	 * @brief Update the grid cell vertex array.
	 * 
	 */
	void updateCells();

	/**
	 * @brief The grid line vertex array.
	 * 
	 */
	sf::VertexArray mGridLines;

	/**
	 * @brief The transform applied to the grid lines,
	 * so we don't have to re-init the vertex array
	 * on every grid transform.
	 * 
	 */
	sf::Transform mGridLineTransform;

	/**
	 * @brief The vertex array for grid cells.
	 * 
	 */
	sf::VertexArray mGridCells;

	/**
	 * @brief All cells to draw.
	 * 
	 */
	std::vector<Cell> mCells;

	/**
	 * @brief The size of each cell to render.
	 * 
	 */
	unsigned mCellSize;

	/**
	 * @brief Grid position, by cells.
	 * A.K.A
	 * mCellSize = 16, mPosition = {1, 1}
	 * actual position = {16, 16}
	 * 
	 */
	sf::Vector2f mPosition;

	/**
	 * @brief The size of the window to render to.
	 * 
	 */
	sf::Vector2u mWindowSize;



	/////////CONSTANTS/////////

	/**
	 * @brief The color of the lines.
	 * 
	 */
	sf::Color mLineColor;
};