#include <SFML/Graphics.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>

const int width = 1900, height = 600;
const float pong_move_rate = 6.f;
const float ball_speed = 3.0f;
const float ball_angle = 0.33f;
float min_bounce = 25;
float max_bounce = 100;

bool collides(sf::FloatRect &lhs, sf::FloatRect &rhs);

float randomfloat(int min, int max);
int randomint(int min, int max);
void print_help_then_exit();


bool cinematic = false;
bool blind = false;
bool nodlc = false;
bool ballsy = false;
bool wtf = false;
int main(int argc, char * argv[])
{
	if (argc >= 2)
	{
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-help") == 0)
				print_help_then_exit();
			if (strcmp(argv[i], "-cinematic") == 0)
				cinematic = true;
			if (strcmp(argv[i], "-blindmode") == 0)
				blind = true;
			if (strcmp(argv[i], "-nodlc") == 0)
				nodlc = true;
			if (strcmp(argv[i], "-bigballs") == 0)
				ballsy = true;
			if (strcmp(argv[i], "-ohshitwtf") == 0)
				wtf = true;
		}
	}



	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
	
	if(cinematic)
		window.setFramerateLimit(20);
	else
		window.setFramerateLimit(100);

	sf::CircleShape ball(25.f);
	sf::RectangleShape pong[2];
	pong[0].setSize(sf::Vector2f(10.f, 150.f));
	pong[0].setPosition(sf::Vector2f(0, 25));
	pong[0].setFillColor(sf::Color::White);

	if (nodlc) 
	{
		pong[1].setSize(sf::Vector2f(10.f, 150.f));
		pong[1].setPosition(sf::Vector2f(width - 10, 25));
		pong[1].setFillColor(sf::Color::White);
	}
	else
	{
		pong[1].setSize(sf::Vector2f(0.f, 0.f));
		pong[1].setPosition(sf::Vector2f(width - 10, 25));
		pong[1].setFillColor(sf::Color::White);
	}
	if (blind)
	{
		pong[0].setFillColor(sf::Color::Black);
		pong[1].setFillColor(sf::Color::Black);
		ball.setFillColor(sf::Color::Black);
	}
	if (ballsy)
		ball.setScale(sf::Vector2f(2.5f, 2.5f));
	if (wtf)
	{
		min_bounce *= 100;
		max_bounce *= 100;
	}
	sf::Vector2f velocity(ball_speed, ball_angle);
	
	ball.setPosition(width / 2, height / 2);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
				
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				pong[0].move(0.f, -pong_move_rate);
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				pong[0].move(0.f, pong_move_rate);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				pong[1].move(0.f, -pong_move_rate);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				pong[1].move(0.f, pong_move_rate);
			}
		}

		ball.move(velocity);

		if (collides(pong[0].getGlobalBounds(), ball.getGlobalBounds()))
		{
			velocity.x = ball_speed;
			if (velocity.y > 0)
				velocity.y = -randomfloat(min_bounce, max_bounce);
			else
				velocity.y = randomfloat(min_bounce, max_bounce);
		}
		if (collides(pong[1].getGlobalBounds(), ball.getGlobalBounds()))
		{
			velocity.x = -ball_speed;
			if(velocity.y > 0)
				velocity.y = -randomfloat(min_bounce, max_bounce);
			else
				velocity.y = randomfloat(min_bounce, max_bounce);
		}

		if (ball.getGlobalBounds().top < 0)
			velocity.y = randomfloat(min_bounce, max_bounce);
		if ((ball.getGlobalBounds().top + ball.getGlobalBounds().height) > height)
			velocity.y = -randomfloat(min_bounce, max_bounce);

		if (ball.getGlobalBounds().left < 0)
		{
			velocity.x++;
			ball.setPosition(width / 1.5, height / 2);
			velocity.y = -randomfloat(min_bounce, max_bounce);
		}
		if ((ball.getGlobalBounds().left + ball.getGlobalBounds().width) > width)
		{
			velocity.x++;
			ball.setPosition(width / 5, height / 2);
			velocity.y = randomfloat(min_bounce, max_bounce);
		}

		window.clear();
		window.draw(pong[0]);
		window.draw(pong[1]);
		window.draw(ball);
		window.display();
	}
	if (!nodlc)
		std::cout << "For the second paddle, please pay $20 to extrapongplz@pong-thegame.com\n";
	return 0;
}

bool collides(sf::FloatRect &lhs, sf::FloatRect &rhs)
{
	return lhs.intersects(rhs);
}

float randomfloat(int min, int max)
{
	float temp = (((rand() + min) % max) / 100.0f);
	//std::cout << "Number generated: " << temp << "\n";
	return temp;
}

int randomint(int min, int max)
{
	int temp = ((rand() + min) % max);
	//std::cout << "Number generated: " << temp << "\n";
	return temp;
}

void print_help_then_exit()
{
	std::cout << "Options: \n"
		"-cinematic \t-- For cinematic mode.\n"
		"-blindmode \t-- For blind mode.\n"
		"-pridemode \t-- For if you're trapped in a closet-like place.\n"
		"-bigballs \t-- For a good time.\n"
		"-ohshitwtf \t-- For John to test.\n"
		"\n\nPress enter to exit..\n";
	getchar();
	std::exit(-1);
}