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
	homePlanet.getClosestSurfacePoint(rocket.m_x, rocket.m_y);
	rocket.m_x -= 50;
	rocket.m_y -= 100;

	sf::CircleShape temp(10);
	temp.setFillColor(sf::Color(255, 0, 0));

	// For time messuring
	sf::Clock clock;
	float dt = 0;

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

        window.draw(temp);

        view.setCenter(sf::Vector2f(rocket.m_x, rocket.m_y));
        window.setView(view);

        // end the current frame
        window.display();
    }

    return 0;
}
