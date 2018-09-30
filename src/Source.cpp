#include <SFML/Graphics.hpp>

#include "Application.h"
#include "Managers/StateManager.h"
#include "States/FrameworkSplashScreen.h"
#include "Managers/CacheSystem.h"

#include <memory>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "skeleton v.0.0.7"/*,sf::Style::Fullscreen*/);
	window.setFramerateLimit(0U);

	Application::init(&window);
	auto backgroundImage = sen::CacheSystem::getTexture("res/Images/bg.jpeg");
	Application::setBackgroundImage(*backgroundImage);
	auto temp = std::make_unique<sen::FrameworkSplashScreen>();
	sen::StateManager::pushState(std::move(temp));
	Application::run();
    
    return 0;
}