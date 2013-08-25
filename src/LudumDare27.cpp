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

	for( ; it != fuel.end(); it++)
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

	for( ; it != fuel.end(); it++)
	{
		it->draw();
	}
}

void fillSkyWithFuel(Content *content, sf::RenderWindow *app, std::list<FuelPowerup> &fuel)
{
	float distLayers = 700;
	float radius = 1000;

	for(int layer = 1; layer < 100; layer++){
		radius += distLayers;

		for(float rad = 0; rad < 2*M_PI; rad += (800.0 / radius) )
		{
			float x = (400.0 + radius * cos(rad)) + (rand() % 400);
			float y = (900.0 + radius * sin(rad)) + (rand() % 400);;

			fuel.push_back(FuelPowerup(content, app, sf::Vector2<int>(x, y)));
		}
	}

}

void init(Rocket &rocket, std::list<FuelPowerup> &fuel, Content *content, sf::RenderWindow *app)
{
	rocket.m_x = 400;
	rocket.m_y = 450;
	rocket.m_fuelSec = sf::seconds(10.0);
	rocket.stopAll();

	fuel.clear();
	fillSkyWithFuel(content, app, fuel);

}

int main()
{
	// Load Content
	Content content;

	//init time things
	srand(time(NULL));

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ludum dare #27");

    sf::View view;

    //Create player/Rocket/HomePlanet
	Rocket rocket(&content, &window);
	float size = 400;
	Planet homePlanet(&content, &window, size, size + 500, size);

	// Powerups
	std::list<FuelPowerup> allFuel;

	init(rocket, allFuel, &content, &window);

	// For time messuring
	sf::Clock clock;
	float dt = 0;
	bool gameOn = false;

	// For height meter (add to content later)
	sf::Font theFont;
	theFont.loadFromFile("../Fonts/SECRCODE.TTF");
	sf::Text heightText("", theFont, 30);
	heightText.setColor(sf::Color::White);

	sf::RectangleShape fuelBar(sf::Vector2f(200, 40));
	sf::Text fuelText("Fuel ", theFont, 30);
	fuelText.setColor(sf::Color::White);

	//Start box thingy
	sf::RectangleShape InfoBox(sf::Vector2f(500, 300));
	InfoBox.setOutlineThickness(10);
	InfoBox.setOutlineColor(sf::Color(250, 150, 100));
	InfoBox.setPosition(150, 200);
	sf::Text InfoText("Rocket Rampage\nWAD - move around\nQE - rotate\n\n(Space to start)", theFont, 40);
	InfoText.setColor(sf::Color::Black);
	InfoText.setPosition(200, 250);

	int height = 0;
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
                if (event.key.code == sf::Keyboard::Space)
                {
                	gameOn = true;
                }
			}
        }

        if(rocket.m_fuelSec == sf::seconds(0.0) && gameOn){
        	InfoText.setString("Game Over!\n\nScore: " + Convert(height) + "\n(Space to restart)");
        	init(rocket, allFuel, &content, &window);
        	gameOn = false;
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        //get time elapsed
        dt = clock.restart().asSeconds();
        if(!gameOn)
        	dt = 0;

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
        height = 	sqrt( pow(homePlanet.m_x - rocket.m_x , 2) + pow(homePlanet.m_y - rocket.m_y , 2) )
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
        if(!gameOn){
        	window.draw(InfoBox);
        	window.draw(InfoText);
        }

        DrawAllFuel(allFuel);

        view.setCenter(sf::Vector2f(rocket.m_x, rocket.m_y));
        view.setRotation(rocket.m_r);
        window.setView(view);

        // end the current frame
        window.display();
    }

    return 0;
}
