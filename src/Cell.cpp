#include "Cell.hpp"

Cell::Cell(Cell::Type type, sf::Vector2i pos)
{
	mType = type;
	mPos  = pos;
}

void Cell::setPosition(sf::Vector2i newPos)
{
	mPos = newPos;
}

sf::Vector2i Cell::getPosition()
{
	return mPos;
}

Cell::Type Cell::getType()
{
	return mType;
}

void Cell::step(std::vector<Cell*> neighbors)
{
	if (mType == WIRE)
	{
		int headct = 0;
		//Count the amount of nearby heads.
		for (auto& n : neighbors)
		{
			if (n->getType() == HEAD)
			{
				headct++;
			}
		}
		//Switch to head if there are enough head neighbors.
		if (headct == 1 || headct == 2)
		{
			mType = HEAD;
		}
	}
	else if (mType == HEAD)
	{
		mType = TAIL;
	}
	else if (mType == TAIL)
	{
		mType = WIRE;
	}
}
