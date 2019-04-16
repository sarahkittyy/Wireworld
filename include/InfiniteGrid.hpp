#pragma once

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cmath>

/**
 * @brief Renders an infinite grid of colored cells to the window.
 * Contains method for resizing the grid, and setting the top-left position of the grid to any point in space.
 * 
 */
class InfiniteGrid : public sf::Drawable
{
public:
	/**
	 * @brief The cell's data structure.
	 * 
	 */
	struct Cell
	{
		sf::Vector2i pos;
		sf::Color col;
	};

	/**
	 * @brief Initializes the grid.
	 * 
	 * @param window_size The size of the window to render to.
	 */
	InfiniteGrid(sf::Vector2u window_size);

	/**
	 * @brief Set the size of the rendered cell.
	 * 
	 * @param newSize The new cell size.
	 */
	void setCellSize(int newSize);

	/**
	 * @brief Get the size of each cell.
	 * 
	 * @return unsigned The length of a side of a cell.
	 */
	unsigned getCellSize();

	/**
	 * @brief Set the top-left position of the grid.
	 * 
	 * @param newPos The position the grid should render from.
	 * 
	 * @remarks This is in cell coords, i.e. if the cell size is 16, 16 you do not need to enter {16, 16} to get to cell {1, 1}.
	 */
	void setPosition(sf::Vector2f newPos);

	/**
	 * @brief Get the position of the grid.
	 * 
	 * @return sf::Vector2i The top-left coordinate of the (rendered) part of the grid.
	 * 
	 * @remarks This is in cell coords, i.e. *cell* (5, 5), and not screen coords.
	 */
	sf::Vector2f getPosition();

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