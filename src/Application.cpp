#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(700, 700), "Wireworld"),
	  mSimulation(&mWindow)
{
}

int Application::run()
{
	//The ImGui internal clock.
	sf::Clock imgui_clock;

	//App loop.
	while (mWindow.isOpen())
	{
		//Handle events.
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			//SFML events..
			switch (event.type)
			{
			default:
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
			case sf::Event::Resized:
				mWindow.setSize({event.size.width, event.size.height});
				break;
				//Handle mouse events for Wireworld simul.
			case sf::Event::MouseButtonPressed:
				mSimulation.onMousePress(event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				mSimulation.onMouseRelease(event.mouseButton.button);
				break;
			case sf::Event::MouseWheelScrolled:
				mSimulation.onMouseScroll(event.mouseWheelScroll.delta);
				break;

				//Wireworld keyboard events.
			case sf::Event::KeyPressed:
				mSimulation.onKeyPress(event.key.code);
				break;
			case sf::Event::KeyReleased:
				mSimulation.onKeyRelease(event.key.code);
				break;
			}
		}

		//Update the simulation.
		mSimulation.update();

		//Clear the window.
		mWindow.clear(sf::Color::White);
		//Draw here...

		mWindow.draw(mSimulation);

		//Finish drawing.
		mWindow.display();
	}

	return 0;
}