#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(700, 700), "Wireworld"),
	  mSimulation(&mWindow)
{
	//Initialize ImGui..
	ImGui::SFML::Init(mWindow);
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
			//Process ImGui events.
			ImGui::SFML::ProcessEvent(event);

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

		//Update ImGui...
		ImGui::SFML::Update(mWindow, imgui_clock.restart());
		//Draw to imgui...

		//Stop drawing to imgui..
		ImGui::EndFrame();

		//Clear the window.
		mWindow.clear(sf::Color::White);
		//Draw here...

		mWindow.draw(mSimulation);


		//Render ImGui
		ImGui::SFML::Render(mWindow);
		//Finish drawing.
		mWindow.display();
	}

	return 0;
}