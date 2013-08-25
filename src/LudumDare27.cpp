#include <SFML/Graphics.hpp>

#include "Content.h"
#include "Rocket.h"
#include "Planet.h"
#include <sstream>

std::string Convert (float number){
  std::ostringstream buff;
  buff<<number;
  return buff.str();

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


        view.setCenter(sf::Vector2f(rocket.m_x, rocket.m_y));
        view.setRotation(rocket.m_r);
        window.setView(view);

        // end the current frame
        window.display();
    }

    return 0;
}
