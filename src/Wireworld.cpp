#include "Wireworld.hpp"

Wireworld::Wireworld(sf::RenderWindow* window)
	: mWindow(window),
	  mGrid(mWindow->getSize()),
	  mSpeed(sf::seconds(1)),
	  mRunning(false)
{
}

void Wireworld::toggleRunning()
{
	mRunning = !mRunning;
}

bool Wireworld::isRunning()
{
	return mRunning;
}

void Wireworld::setSpeed(sf::Time newSpeed)
{
	mSpeed = newSpeed;
}

sf::Time Wireworld::getSpeed()
{
	return mSpeed;
}

void Wireworld::update()
{
	//If we're not running, break.
	if (!mRunning)
	{
		return;
	}

	//If it's time to step the simulation...
	if (mClock.getElapsedTime() > mSpeed)
	{
		step();
		mClock.restart();
	}
}

void Wireworld::step()
{
	//Copy the vector of cells.
	std::vector<Cell> cells_cpy = mCells;
	//Iterate over all cells.
	for (auto& cell : cells_cpy)
	{
		//Get it's position.
		sf::Vector2i pos = cell.getPosition();
		//Get all neighbors of the cell.
		std::vector<Cell*> neighbors;
		for (int dx = -1; dx <= 1; ++dx)
		{
			for (int dy = -1; dy <= 1; ++dy)
			{
				//As long as it's not the active cell...
				if (!(dx == 0 && dy == 0))
				{
					//Get the cell at the position + {dx, dy}.
					sf::Vector2i cpos = pos + sf::Vector2i(dx, dy);
					//If there is a cell..
					if (isCell(cpos))
					{
						//Append it.
						neighbors.push_back(getCellPtr(cpos));
					}
				}
			}
		}

		//Update the cell in the original cell vector with the new neighbors.
		cell.step(neighbors);
		//Update the grid.
		mGrid.setCell({.pos = cell.getPosition(),
					   .col = CELL_COLORS.at(cell.getType())});
	}

	//Copy cells_cpy back.
	mCells = cells_cpy;
}

void Wireworld::onMousePress(sf::Mouse::Button btn)
{
	if (!isMouseValid())
	{
		return;
	}
	if (btn == sf::Mouse::Left)
	{
		setCell(Cell(Cell::WIRE, getMousePos()));
	}
	else if (btn == sf::Mouse::Right)
	{
		setCell(Cell(Cell::HEAD, getMousePos()));
	}
}

void Wireworld::onMouseRelease(sf::Mouse::Button btn)
{
}

void Wireworld::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Space)
	{
		toggleRunning();
	}
}

void Wireworld::onKeyRelease(sf::Keyboard::Key key)
{
}

void Wireworld::setCell(Cell c)
{
	if (isCell(c.getPosition()))
	{
		*(getCellPtr(c.getPosition())) = c;
	}
	else
	{
		mCells.push_back(c);
	}

	mGrid.setCell({.pos = c.getPosition(), .col = CELL_COLORS.at(c.getType())});
}

bool Wireworld::isCell(sf::Vector2i pos)
{
	//Simple search for pos in mCells.
	for (auto& cell : mCells)
	{
		if (cell.getPosition() == pos)
		{
			return true;
		}
	}
	return false;
}

Cell Wireworld::getCell(sf::Vector2i pos)
{
	if (!isCell(pos))
	{
		return Cell(Cell::NONE, sf::Vector2i(0, 0));
	}
	else
	{
		return *(getCellPtr(pos));
	}
}

Cell* Wireworld::getCellPtr(sf::Vector2i pos)
{
	if (!isCell(pos))
	{
		return nullptr;
	}
	return std::find_if(mCells.begin(), mCells.end(),
						[pos](Cell& c) {
							return c.getPosition() == pos;
						})
		.base();
}

void Wireworld::clearCell(sf::Vector2i pos)
{
	for (auto i = mCells.begin(); i != mCells.end(); ++i)
	{
		if (i->getPosition() == pos)
		{
			mCells.erase(i);
			return;
		}
	}

	mGrid.clearCell(pos);
}

sf::Vector2i Wireworld::getMousePos()
{
	sf::Vector2f pos = (sf::Vector2f)sf::Mouse::getPosition(*mWindow);

	//Move the mouse into cell coords.
	pos.x /= mGrid.getCellSize();
	pos.y /= mGrid.getCellSize();

	//Translate it by the grid's position.
	pos -= mGrid.getPosition();

	//Return it.
	return sf::Vector2i(pos);
}

bool Wireworld::isMouseValid()
{
	//Get the window's bounds.
	sf::IntRect window_bounds(
		0, 0, mWindow->getSize().x, mWindow->getSize().y);

	//Return if the window contains the mouse pos.
	return window_bounds.contains(sf::Mouse::getPosition(*mWindow));
}

void Wireworld::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mGrid, states);
}