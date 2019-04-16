#include "InfiniteGrid.hpp"

InfiniteGrid::InfiniteGrid(sf::Vector2u window_size)
{
	//Init settings.
	mWindowSize = window_size;
	mCellSize   = 16;
	mPosition   = {0, 0};

	//Init constants.
	mLineColor = sf::Color::Black;

	//Init vertex arrays.
	mGridLines.setPrimitiveType(sf::Lines);
	mGridCells.setPrimitiveType(sf::Quads);

	init();
}

void InfiniteGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(mGridCells, states);
	states.transform *= mGridLineTransform;
	target.draw(mGridLines, states);
}

void InfiniteGrid::init()
{
	//Initialize the base grid lines.
	initLines();

	//Update the lines & cells.
	update();
}

void InfiniteGrid::initLines()
{
	mGridLines.clear();

	/*
	We draw grid lines to fill up the screen as if the user had set the cell size to virtually 0. We can use mGridLineTransform to scale the grid later in updateLines().
	*/

	//Lines to draw outside the window, to prevent empty spots where lines should be.
	const int buffer = 10;

	//For every vertical line.
	for (int x = -buffer; x < (signed)mWindowSize.x + buffer; x++)
	{
		//Append...
		mGridLines.append(sf::Vertex(
			sf::Vector2f(x, -buffer),
			mLineColor));
		mGridLines.append(sf::Vertex(
			sf::Vector2f(x, mWindowSize.y + buffer),
			mLineColor));
	}
	//For every horizontal line.
	for (int y = -buffer; y < (signed)mWindowSize.y + buffer; y++)
	{
		//Append...
		mGridLines.append(sf::Vertex(
			sf::Vector2f(-buffer, y),
			mLineColor));
		mGridLines.append(sf::Vertex(
			sf::Vector2f(mWindowSize.x + buffer, y),
			mLineColor));
	}
}

void InfiniteGrid::update()
{
	//Update everything.
	updateLines();
	updateCells();
}

void InfiniteGrid::updateLines()
{
	mGridLineTransform = sf::Transform::Identity;

	//Shift over by the position modulo the cell size, divided by the cell size.
	mGridLineTransform.translate(
		(mPosition.x * mCellSize),
		(mPosition.y * mCellSize));

	//Zoom in by the CellSize
	mGridLineTransform.scale(mCellSize, mCellSize);
}

void InfiniteGrid::updateCells()
{
	mGridCells.clear();

	//Iterate over all cells.
	for (auto& cell : mCells)
	{
		//The actual position of the cell is cell.pos - mPosition
		sf::Vector2f pos = sf::Vector2f(cell.pos) - mPosition;

		//Ignore if we're out of bounds.
		sf::FloatRect bounds(-5, -5, mWindowSize.x / mCellSize + 5, mWindowSize.y / mCellSize + 5);
		if (!bounds.contains(pos))
		{
			continue;
		}

		pos.x *= mCellSize;
		pos.y *= mCellSize;

		//Create a quad at the given position
		mGridCells.append(sf::Vertex(
			pos,
			cell.col));
		mGridCells.append(sf::Vertex(
			sf::Vector2f(pos.x + mCellSize, pos.y),
			cell.col));
		mGridCells.append(sf::Vertex(
			sf::Vector2f(pos.x + mCellSize, pos.y + mCellSize),
			cell.col));
		mGridCells.append(sf::Vertex(
			sf::Vector2f(pos.x, pos.y + mCellSize),
			cell.col));
	}
}