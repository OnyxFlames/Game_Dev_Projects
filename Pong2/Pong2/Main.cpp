#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

const float width = 640;
const float height = 480;

const float paddle_height = 90;
const float paddle_width = 10;

const float min_bounce = 2.5f;
const float max_bounce = 7.5f;

sf::Vector2f velocity(0.0005f, 0.00025f);
const float paddle_speed = 0.0005f;


bool paused = false;
bool paddle1_up = false;
bool paddle1_down = false;
bool restart = false;
bool paddle2_up = false;
bool paddle2_down = false;

bool collide(sf::FloatRect &lhs, sf::FloatRect &rhs);
float randomfloat(int min, int max);

unsigned score1(0), score2(0);

int main(int argc, char* argv[])
{
	std::string fps_str = "Initalizing..";
	sf::Font fps_font;
	fps_font.loadFromFile("Resources/Fonts/Consola.ttf");
	sf::Text fps_text;
	sf::Text player1_score, player2_score;
	player1_score.setFont(fps_font);
	player2_score.setFont(fps_font);
	player1_score.setPosition(25, 25);
	player2_score.setPosition((width - 50) - player2_score.getGlobalBounds().width, 25);
	fps_text.setFont(fps_font);
	fps_text.setPosition(width / 2.4, height - 25);
	fps_text.setCharacterSize(9);

	sf::RenderWindow window(sf::VideoMode(640, 480), "Pong 2");

	if (argc > 2)
	{
		if (std::strcmp(argv[1], "-limitFPS") == 0)
		{
			window.setFramerateLimit(std::stoi(argv[2]));
			std::cout << "Limiting framerate to (roughly) " << argv[2] << "\n";
		}
	}
	else
		std::cout << "Running program without extra arguments.\n\n";

	sf::RectangleShape	paddle1(sf::Vector2f(paddle_width, paddle_height)),
						paddle2(sf::Vector2f(paddle_width, paddle_height));
	paddle1.setFillColor(sf::Color::Red);
	paddle2.setFillColor(sf::Color::Blue);
	paddle1.setPosition(0, 25);
	paddle2.setPosition(width - (paddle_width), 25);

	sf::CircleShape ball(22.5f);
	ball.setPosition((width - ball.getGlobalBounds().width) / 2, (height - ball.getGlobalBounds().height) / 2);

	sf::RectangleShape test_line(sf::Vector2f(width, 1));
	test_line.setPosition(0, 25);
	test_line.setFillColor(sf::Color::Blue);

	long long framespersecond = 0;
	sf::Clock delta_clock, fps_clock;
	sf::Time curr_time, prev_time, delta;
	while (window.isOpen())
	{
		if (fps_clock.getElapsedTime().asSeconds() < 1.0f)
		{
			framespersecond++;
		}
		else
		{
			//std::cout << "FPS:\t" << framespersecond << "\n";
			//std::cout << "Delta:\t" << delta.asMicroseconds() << "\t(in microseconds)\n";
			fps_text.setString(fps_str);
			framespersecond = 0;
			fps_clock.restart();
		}
		// Start clock before handling events
		curr_time = delta_clock.getElapsedTime();
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

				if (event.key.code == sf::Keyboard::Space)
					paused = !paused;
				if (event.key.code == sf::Keyboard::T)
					restart = true;
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

		delta = (curr_time - prev_time);
		prev_time = curr_time;

		if (paused)
			delta = sf::microseconds(0);
		fps_str = "FPS: " + std::to_string(framespersecond);
		fps_str += "\tDelta: " + (std::to_string(delta.asMicroseconds()));

		if (paddle1_up)
			paddle1.move(sf::Vector2f(0.0f, -(paddle_speed * delta.asMicroseconds())));
		if (paddle1_down)
			paddle1.move(sf::Vector2f(0.0f, (paddle_speed * delta.asMicroseconds())));

		if (paddle2_up)
			paddle2.move(sf::Vector2f(0.0f, -(paddle_speed * delta.asMicroseconds())));
		if (paddle2_down)
			paddle2.move(sf::Vector2f(0.0f, (paddle_speed * delta.asMicroseconds())));

		if (restart)
		{
			score1 = 0;
			score2 = 0;
			paddle1.setPosition(0, 25);
			paddle2.setPosition(width - (paddle_width), 25);
			ball.setPosition((width - ball.getGlobalBounds().width) / 2, (height - ball.getGlobalBounds().height) / 2);
			restart = false;
		}

		if (paddle1.getPosition().y < 0)
			paddle1.setPosition(paddle1.getPosition().x, 0);
		if (paddle1.getPosition().y > (height - paddle1.getGlobalBounds().height))
			paddle1.setPosition(paddle1.getPosition().x, height - paddle1.getGlobalBounds().height);
		if (paddle2.getPosition().y < 0)
			paddle2.setPosition(paddle2.getPosition().x, 0);
		if (paddle2.getPosition().y >(height - paddle2.getGlobalBounds().height))
			paddle2.setPosition(paddle2.getPosition().x, height - paddle2.getGlobalBounds().height);

		ball.move(velocity.x * delta.asMicroseconds(), velocity.y * delta.asMicroseconds());

		if (collide(paddle2.getGlobalBounds(), ball.getGlobalBounds()))
		{
			velocity.x = -velocity.x;
			velocity.y = -randomfloat(min_bounce, max_bounce);
			ball.setFillColor(sf::Color::Blue);
		}
		if (collide(paddle1.getGlobalBounds(), ball.getGlobalBounds()))
		{
			velocity.x = -velocity.x;
			velocity.y = randomfloat(min_bounce, max_bounce);
			ball.setFillColor(sf::Color::Red);
		}

		if (ball.getGlobalBounds().top < 0)
		{
			velocity.y = randomfloat(min_bounce, max_bounce);
			ball.setFillColor(sf::Color::White);
		}
		if ((ball.getGlobalBounds().top + ball.getGlobalBounds().height) > height) 
		{
			velocity.y = -randomfloat(min_bounce, max_bounce);
			ball.setFillColor(sf::Color::White);
		}
		if (ball.getGlobalBounds().left < 0)
		{
			if (ball.getFillColor() == sf::Color::Blue)
				score2++;
			score2++;
			ball.setPosition(width / 1.5, height / 2);
			velocity.y = -randomfloat(min_bounce, max_bounce);
		}
		if ((ball.getGlobalBounds().left + ball.getGlobalBounds().width) > width)
		{
			if (ball.getFillColor() == sf::Color::Red)
				score1++;
			score1++;
			ball.setPosition(width / 5, height / 2);
			velocity.y = randomfloat(min_bounce, max_bounce);
		}

		player1_score.setPosition(25, 25);
		player2_score.setPosition((width - 50) - player2_score.getGlobalBounds().width, 25);
		player1_score.setString(std::to_string(score1));
		player2_score.setString(std::to_string(score2));

		window.clear();
		window.draw(paddle1);
		window.draw(paddle2);
		window.draw(ball);
		window.draw(player1_score);
		window.draw(player2_score);
		//window.draw(test_line);
		window.draw(fps_text);
		window.display();
	}

	return 0;
}


bool collide(sf::FloatRect &lhs, sf::FloatRect &rhs)
{
	return lhs.intersects(rhs);
}

float randomfloat(int min, int max)
{
	float temp = (((rand() + min) % max) / 10000.0f);
	//std::cout << "Generated Number: " << temp << "\n";
	return temp;
}