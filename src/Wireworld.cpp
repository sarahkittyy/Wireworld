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
	//Constrain the new speed.
	if (mSpeed < sf::seconds(0))
	{
		mSpeed = sf::seconds(0);
	}
	if (mSpeed > sf::seconds(10))
	{
		mSpeed = sf::seconds(10);
	}
}

sf::Time Wireworld::getSpeed()
{
	return mSpeed;
}

void Wireworld::update()
{
	//Update mouse input handlers.
	updateMouse();

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

void Wireworld::updateMouse()
{
	//First, mouse panning.
	if (mMousePan.mouseHeld)
	{
		//Get the current displacement from the clicked pos.
		sf::Vector2f cpos = getMousePos(false) - mMousePan.initialMouse;
		//Set the grid's position to that.
		mGrid.setPosition(mMousePan.initialGrid + cpos);
	}

	//Next, mouse cell placement.
	if (mCellPlacement.mouseHeld)
	{
		//Current mouse position.
		sf::Vector2i cpos = sf::Vector2i(getMousePos());
		//If it's not already logged...
		if (std::find(mCellPlacement.log.begin(),
					  mCellPlacement.log.end(),
					  cpos) == mCellPlacement.log.end())
		{
			//Log it, and set the cell there.
			mCellPlacement.log.push_back(cpos);
			//The cell type already there.
			Cell::Type t		  = getCell(cpos).getType();
			sf::Mouse::Button btn = mCellPlacement.btn;
			if (t == Cell::NONE)
			{
				if (btn == sf::Mouse::Left)
				{
					t = Cell::WIRE;
				}
				else
				{
					t = Cell::HEAD;
				}
			}
			else if (t == Cell::WIRE)
			{
				if (btn == sf::Mouse::Left)
				{
					t = Cell::NONE;
				}
				else
				{
					t = Cell::TAIL;
				}
			}
			else if (t == Cell::HEAD)
			{
				if (btn == sf::Mouse::Left)
				{
					t = Cell::NONE;
				}
				else
				{
					t = Cell::TAIL;
				}
			}
			else if (t == Cell::TAIL)
			{
				if (btn == sf::Mouse::Left)
				{
					t = Cell::NONE;
				}
			}
			//Set the cell.
			setCell(Cell(t, cpos));
		}
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
	//Only run this event if the mouse is in the winow.
	if (!isMouseValid())
	{
		return;
	}

	//If it's the middle mouse...
	if (btn == sf::Mouse::Middle)
	{
		mMousePan.mouseHeld	= true;
		mMousePan.initialMouse = getMousePos(false);
		mMousePan.initialGrid  = mGrid.getPosition();
	}
	//Otherwise..
	else
	{
		//Reset n toggle cell placement.
		mCellPlacement.mouseHeld = true;
		mCellPlacement.log.clear();
		mCellPlacement.btn = btn;
	}
}

void Wireworld::onMouseRelease(sf::Mouse::Button btn)
{
	//Stop panning if it's the middle mouse button released.
	if (btn == sf::Mouse::Middle)
	{
		mMousePan.mouseHeld = false;
	}
	else
	{
		mCellPlacement.mouseHeld = false;
	}
}

void Wireworld::onMouseScroll(int delta)
{
	//Zoom the grid in/out.
	mGrid.setCellSize(mGrid.getCellSize() + ((delta > 0) ? 1
														 : -1));
}

void Wireworld::onKeyPress(sf::Keyboard::Key key)
{
	//Space pauses the application.
	if (key == sf::Keyboard::Space)
	{
		toggleRunning();
	}
	//+/- change the simulation speed.
	else if (key == sf::Keyboard::Add)
	{
		setSpeed(getSpeed() - sf::seconds(0.5f));
	}
	else if (key == sf::Keyboard::Subtract)
	{
		setSpeed(getSpeed() + sf::seconds(0.5f));
	}
	else if(key == sf::Keyboard::R)
	{
		mCells.clear();
		mGrid.clear();
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

sf::Vector2f Wireworld::getMousePos(bool translate)
{
	sf::Vector2f pos = (sf::Vector2f)sf::Mouse::getPosition(*mWindow);

	//Move the mouse into cell coords.
	pos.x /= mGrid.getCellSize();
	pos.y /= mGrid.getCellSize();

	if (translate)
	{
		//Translate it by the grid's position.
		pos -= mGrid.getPosition();
	}

	//Return it.
	return pos;
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