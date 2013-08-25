#include <SFML/Graphics.hpp>

#include "Content.h"
#include "Rocket.h"
#include "Planet.h"

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
	rocket.m_x = 350;
	rocket.m_y = 400;

	// For time messuring
	sf::Clock clock;
	float dt = 0;

	sf::RectangleShape fueelBar(sf::Vector2f(200, 40));

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

        // draw everything here...
        homePlanet.draw();
        rocket.draw();

        // GUI stuff
        sf::Vector2<int> fuelPos(10, 10);
        fueelBar.setPosition( window.mapPixelToCoords(fuelPos) );
        fueelBar.setRotation(rocket.m_r);
        fueelBar.setSize(sf::Vector2f(rocket.m_fuelSec.asSeconds()*20.0, 40));
        fueelBar.setFillColor(sf::Color( 255-rocket.m_fuelSec.asSeconds()*20.0,
        								 rocket.m_fuelSec.asSeconds()*20.0 - 255, 0));
        window.draw(fueelBar);

        view.setCenter(sf::Vector2f(rocket.m_x, rocket.m_y));
        view.setRotation(rocket.m_r);

        window.setView(view);

        // end the current frame
        window.display();
    }

    return 0;
}
