#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(700, 700), "Wireworld")
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
			}
		}
		//Update ImGui...
		ImGui::SFML::Update(mWindow, imgui_clock.restart());
		//Draw to imgui...

		//Stop drawing to imgui..
		ImGui::EndFrame();

		//Clear the window.
		mWindow.clear(sf::Color::White);
		//Draw here...


		//Render ImGui
		ImGui::SFML::Render(mWindow);
		//Finish drawing.
		mWindow.display();
	}

	return 0;
}