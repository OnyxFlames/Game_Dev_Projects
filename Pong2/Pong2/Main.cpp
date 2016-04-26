#include <SFML/Graphics.hpp>

const float width = 640;
const float height = 480;

const float paddle_height = 100;
const float paddle_width = 25;

const sf::Vector2f velocity(1.0f, 1.0f);
const float paddle_speed = 3.0f;

bool paddle1_up = false;
bool paddle1_down = false;

bool paddle2_up = false;
bool paddle2_down = false;

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Pong 2");
	window.setFramerateLimit(60);
	sf::RectangleShape	paddle1(sf::Vector2f(paddle_width, paddle_height)),
						paddle2(sf::Vector2f(paddle_width, paddle_height));
	paddle1.setPosition(25, 25);
	paddle2.setPosition(width - (paddle_width * 2), 25);

	sf::RectangleShape test_line(sf::Vector2f(width, 1));
	test_line.setPosition(0, 25);
	test_line.setFillColor(sf::Color::Blue);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::W)
					paddle1_up = true;
				if (event.key.code == sf::Keyboard::S)
					paddle1_down = true;

				if (event.key.code == sf::Keyboard::Up)
					paddle2_up = true;
				if (event.key.code == sf::Keyboard::Down)
					paddle2_down = true;

				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::W)
					paddle1_up = false;
				if (event.key.code == sf::Keyboard::S)
					paddle1_down = false;

				if (event.key.code == sf::Keyboard::Up)
					paddle2_up = false;
				if (event.key.code == sf::Keyboard::Down)
					paddle2_down = false;
				break;
			}
		}

		if (paddle1_up)
			paddle1.move(sf::Vector2f(0.0f, -paddle_speed));
		if (paddle1_down)
			paddle1.move(sf::Vector2f(0.0f, paddle_speed));

		if (paddle2_up)
			paddle2.move(sf::Vector2f(0.0f, -paddle_speed));
		if (paddle2_down)
			paddle2.move(sf::Vector2f(0.0f, paddle_speed));

		window.clear();
		window.draw(paddle1);
		window.draw(paddle2);
		window.draw(test_line);
		window.display();
	}

	return 0;
}