#pragma once

#include <SFML/System.hpp>

#include <vector>

/**
 * @brief A simple cell data structure, including behaviors.
 * 
 */
class Cell
{
public:
	/**
	 * @brief The possible cell types.
	 * 
	 */
	enum Type
	{
		NONE,   //Type NONE rarely used, does nothing.
		WIRE,
		HEAD,
		TAIL
	};

	/**
	 * @brief Construct a new Cell.
	 * 
	 * @param type The initial cell type.
	 */
	Cell(Type type, sf::Vector2i pos = {0, 0});

	/**
	 * @brief Set the cell's position.
	 * 
	 * @param newPos The new pos.
	 */
	void setPosition(sf::Vector2i newPos);

	/**
	 * @brief Get the cell's position.
	 * 
	 * @return sf::Vector2i The cell's current position.
	 */
	sf::Vector2i getPosition();

	/**
	 * @brief Get the Type of the cell.
	 * 
	 * @return Type The cell's current type.
	 */
	Type getType();

	/**
	 * @brief Defines the behavior of the cells. Steps the cell forward based on the types of it's neighbors.
	 * 
	 * @param neighbors The cell's neighbors.
	 */
	void step(std::vector<Cell*> neighbors);

private:
	/**
	 * @brief The cell's internal type.
	 * 
	 */
	Type mType;

	/**
	 * @brief The cell's position.
	 * 
	 */
	sf::Vector2i mPos;
};
