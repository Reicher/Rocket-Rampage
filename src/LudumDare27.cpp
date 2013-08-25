#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

#include "Content.h"
#include "Rocket.h"
#include "Planet.h"
#include "FuelPowerup.h"

#include <cstdlib>
#include <sstream>
#include <math.h>

std::string Convert (float number){
  std::ostringstream buff;
  buff<<number;
  return buff.str();

 }

void TakeFuel(Rocket &rocket, std::list<FuelPowerup> &fuel)
{
	float threshold = 50;
	std::list<FuelPowerup>::iterator it = fuel.begin();

	for( it ; it != fuel.end(); it++)
	{
		double dist = sqrt( pow(rocket.m_x - it->getPos().x , 2) + pow( rocket.m_y - it->getPos().y, 2) );
		if(dist <= threshold)
		{
			it->take();
			rocket.fillFuel(sf::seconds(10.0));
			fuel.erase(it);
			break;
		}
	}
}

void DrawAllFuel(std::list<FuelPowerup> fuel)
{
	std::list<FuelPowerup>::iterator it = fuel.begin();

	for( it ; it != fuel.end(); it++)
	{
		it->draw();
	}
}

void fillSkyWithFuel(Content *content, sf::RenderWindow *app, std::list<FuelPowerup> &fuel)
{
	float distLayers = 500;

	//for(int layer = 0; layer < 10; layer++){
	//float circ = M_PI * pow(800, 2);

	for(float rad = 0; rad < 2*M_PI; rad += 0.5)
	{
		float x = 400.0 + 800.0 * cos(rad);
		float y = 900.0 + 800.0 * sin(rad);

		fuel.push_back(FuelPowerup(content, app, sf::Vector2<int>(x, y)));
	}


//		sf::Vector2<int> pos(400+rand() % ) , 0);

	//}

}

int main()
{
	// Load Content
	Content content;

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ludum dare #27");

    sf::View view;

    //Create player/Rocket/HomePlanet
	Rocket rocket(&content, &window);
	float size = 400;
	Planet homePlanet(&content, &window, size, size + 500, size);
	rocket.m_x = 400;
	rocket.m_y = 450;

	// Powerups
	std::list<FuelPowerup> allFuel;
	fillSkyWithFuel(&content, &window, allFuel);

	// For time messuring
	sf::Clock clock;
	float dt = 0;

	// For height meter (add to content later)
	sf::Font theFont;
	theFont.loadFromFile("../Fonts/SECRCODE.TTF");
	sf::Text heightText("", theFont, 30);
	heightText.setColor(sf::Color::White);

	sf::RectangleShape fuelBar(sf::Vector2f(200, 40));
	sf::Text fuelText("Fuel ", theFont, 30);
	fuelText.setColor(sf::Color::White);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                	window.close();
                }
			}
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        //get time elapsed
        dt = clock.restart().asSeconds();

        // Update all
        rocket.update(dt, &homePlanet);
        TakeFuel(rocket, allFuel);

        // Fuel bar ( encapsule later)
        fuelText.setPosition( window.mapPixelToCoords(sf::Vector2<int>(10, 10)) );
        fuelText.setRotation(rocket.m_r);

        fuelBar.setPosition( window.mapPixelToCoords(sf::Vector2<int>(70, 10)) );
        fuelBar.setRotation(rocket.m_r);
        fuelBar.setSize(sf::Vector2f(rocket.m_fuelSec.asSeconds()*20.0, 40));
        fuelBar.setFillColor(sf::Color( 255-rocket.m_fuelSec.asSeconds()*20.0,
        								 rocket.m_fuelSec.asSeconds()*20.0 - 255,
        								 0));
        // Height meter
        int height = 	sqrt( pow(homePlanet.m_x - rocket.m_x , 2) + pow(homePlanet.m_y - rocket.m_y , 2) )
        				- homePlanet.m_shape.getRadius() - 50;
        heightText.setPosition( window.mapPixelToCoords( sf::Vector2<int>(600, 10)) );
        heightText.setRotation(rocket.m_r);
        heightText.setString(Convert(height) + " Parsec");

        // draw everything here...
        homePlanet.draw();
        rocket.draw();

        window.draw(fuelText);
        window.draw(fuelBar);
        window.draw(heightText);

        DrawAllFuel(allFuel);

        view.setCenter(sf::Vector2f(rocket.m_x, rocket.m_y));
        view.setRotation(rocket.m_r);
        window.setView(view);

        // end the current frame
        window.display();
    }

    return 0;
}
