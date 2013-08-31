#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

#include "Content.h"
#include "Rocket.h"
#include "Planet.h"
#include "FuelCollection.h"
#include "InfoBox.h"

#include <cstdlib>
#include <sstream>
#include <math.h>

std::string Convert (float number){
  std::ostringstream buff;
  buff<<number;
  return buff.str();

 }

void init(Rocket &rocket)
{
	rocket.m_x = 0;
	rocket.m_y = -440;
	rocket.m_r = 0;
	rocket.m_fuelSec = sf::seconds(10.0);
	rocket.stopAll();
}

int main()
{
	// Load Content
	Content content;

	// Music
	content.m_mainTheme.play();
	content.m_mainTheme.setLoop(true);
	content.m_mainTheme.setVolume(75);

	//init time things
	srand(time(NULL));

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rocket Rampage");
    sf::View view;

    //Create player/Rocket/HomePlanet
	Rocket rocket(&content, &window);
	float size = 400;
	Planet homePlanet(&content, &window, 0, 0, size);

	init(rocket);

	// Create fuel
	FuelCollection fuelCollection(content.m_fuelTex, content.m_takeFuelSound);
	fuelCollection.init();

	// For time messuring
	sf::Clock clock;
	float dt = 0;
	bool gameOn = false;

	// For height meter (add to content later)
	sf::Text heightText("", content.m_standardFont, 30);
	heightText.setColor(sf::Color::White);

	sf::RectangleShape fuelBar(sf::Vector2f(200, 40));
	sf::Text fuelText("Fuel ", content.m_standardFont, 30);
	fuelText.setColor(sf::Color::White);

	//Start box thingy
	InfoBox infoBox( &window, &content, sf::Vector2f(-200, -550));

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
        	infoBox.setGameOver(height);
        	init(rocket);
        	fuelCollection.init();
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
        if (fuelCollection.isAnyFuelHit(rocket.m_mainSprite.getPosition()))
        {
        	rocket.fillFuel(sf::seconds(10.0));
        }

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
        height = 	sqrt( pow(rocket.m_x , 2) + pow(rocket.m_y , 2) ) - homePlanet.m_shape.getRadius() - 40;

        heightText.setPosition( window.mapPixelToCoords( sf::Vector2<int>(600, 10)) );
        heightText.setRotation(rocket.m_r);
        heightText.setString(Convert(height) + " Parsec");

        // draw everything here...
        homePlanet.draw();
        rocket.draw();

        window.draw(fuelText);
        window.draw(fuelBar);
        window.draw(heightText);

        if(!gameOn)
        	infoBox.draw();

        window.draw(fuelCollection);

        view.setCenter(sf::Vector2f(rocket.m_x, rocket.m_y));
        view.setRotation(rocket.m_r);
        window.setView(view);

        // end the current frame
        window.display();
    }

    return 0;
}
