#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <iostream>

#define X(v) tileType[v] == x
#define O(v) tileType[v] == o

enum players {

	x = 0,
	o = 1,

};

int main()
{
	sf::RenderWindow window(sf::VideoMode(388, 440), "Tic Tac Toe");

	sf::Texture X, O, player, turnTex;

	X.loadFromFile				("resources/X.png");
	O.loadFromFile				("resources/O.png");
	player.loadFromFile			("resources/player.png");

	sf::Sprite playerSprite, turnSprite;

	sf::RectangleShape one		(sf::Vector2f(128, 128));
	sf::RectangleShape two		(sf::Vector2f(128, 128));
	sf::RectangleShape three	(sf::Vector2f(128, 128));
	sf::RectangleShape four		(sf::Vector2f(128, 128));
	sf::RectangleShape five		(sf::Vector2f(128, 128));
	sf::RectangleShape six		(sf::Vector2f(128, 128));
	sf::RectangleShape seven	(sf::Vector2f(128, 128));
	sf::RectangleShape eight	(sf::Vector2f(128, 128));
	sf::RectangleShape nine		(sf::Vector2f(128, 128));
	
	playerSprite.setTexture(player);
	turnSprite.setTexture(X);
	

	one.setPosition				(0, 0);
	two.setPosition				(130, 0);
	three.setPosition			(260, 0);
	four.setPosition			(0, 130);
	five.setPosition			(130, 130);
	six.setPosition				(260, 130);
	seven.setPosition			(0, 260);
	eight.setPosition			(130, 260);
	nine.setPosition			(260, 260);
	playerSprite.setPosition	(0, 388);
	turnSprite.setPosition		(132, 404);

	sf::Vector2i mouseLocation = sf::Vector2i(0, 0);
	bool mouseClicked = false;
	bool turn = x;
	bool isClicked[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int tileType[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	bool allX = false;
	bool allO = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			if (event.type == sf::Event::MouseButtonPressed){
				mouseLocation = sf::Mouse::getPosition(window);
				mouseClicked = true;
			}

			if (mouseClicked == true){

				if (mouseLocation.x >= one.getPosition().x && mouseLocation.x <= (one.getPosition().x + 128)
					&& mouseLocation.y >= one.getPosition().y && mouseLocation.y <= (one.getPosition().y + 128)
					&& isClicked[0] == 0){	//First tile
					mouseClicked = false;
					isClicked[0] = 1;
					
					if (turn == x){
						one.setTexture(&X);
						turn = o;
						tileType[0] = x;
					}
					else if (turn == o){
						one.setTexture(&O);
						turn = x;
						tileType[0] = o;
					}
				}

				if (mouseLocation.x >= two.getPosition().x && mouseLocation.x <= (two.getPosition().x + 128)
					&& mouseLocation.y >= two.getPosition().y && mouseLocation.y <= (two.getPosition().y + 128)
					&& isClicked[1] == 0){	//Second tile
					mouseClicked = false;
					isClicked[1] = 1;

					if (turn == x){
						two.setTexture(&X);
						turn = o;
						tileType[1] = x;
					}
					else if (turn == o){
						two.setTexture(&O);
						turn = x;
						tileType[1] = o;
					}
				}

				if (mouseLocation.x >= three.getPosition().x && mouseLocation.x <= (three.getPosition().x + 128)
					&& mouseLocation.y >= three.getPosition().y && mouseLocation.y <= (three.getPosition().y + 128)
					&& isClicked[2] == 0){	//Third tile
					mouseClicked = false;
					isClicked[2] = 1;

					if (turn == x){
						three.setTexture(&X);
						turn = o;
						tileType[2] = x;
					}
					else if (turn == o){
						three.setTexture(&O);
						turn = x;
						tileType[2] = o;
					}
				}

				if (mouseLocation.x >= four.getPosition().x && mouseLocation.x <= (four.getPosition().x + 128)
					&& mouseLocation.y >= four.getPosition().y && mouseLocation.y <= (four.getPosition().y + 128)
					&& isClicked[3] == 0){	//Fourth tile
					mouseClicked = false;
					isClicked[3] = 1;

					if (turn == x){
						four.setTexture(&X);
						turn = o;
						tileType[3] = x;
					}
					else if (turn == o){
						four.setTexture(&O);
						turn = x;
						tileType[3] = o;
					}
				}

				if (mouseLocation.x >= five.getPosition().x && mouseLocation.x <= (five.getPosition().x + 128)
					&& mouseLocation.y >= five.getPosition().y && mouseLocation.y <= (five.getPosition().y + 128)
					&& isClicked[4] == 0){	//Fifth tile
					mouseClicked = false;
					isClicked[4] = 1;

					if (turn == x){
						five.setTexture(&X);
						turn = o;
						tileType[4] = x;
					}
					else if (turn == o){
						five.setTexture(&O);
						turn = x;
						tileType[4] = o;
					}
				}
				
				if (mouseLocation.x >= six.getPosition().x && mouseLocation.x <= (six.getPosition().x + 128)
					&& mouseLocation.y >= six.getPosition().y && mouseLocation.y <= (six.getPosition().y + 128)
					&& isClicked[5] == 0){	//Sixth tile
					mouseClicked = false;
					isClicked[5] = 1;

					if (turn == x){
						six.setTexture(&X);
						turn = o;
						tileType[5] = x;
					}
					else if (turn == o){
						six.setTexture(&O);
						turn = x;
						tileType[5] = o;
					}
				}

				if (mouseLocation.x >= seven.getPosition().x && mouseLocation.x <= (seven.getPosition().x + 128)
					&& mouseLocation.y >= seven.getPosition().y && mouseLocation.y <= (seven.getPosition().y + 128)
					&& isClicked[6] == 0){	//Seventh tile
					mouseClicked = false;
					isClicked[6] = 1;

					if (turn == x){
						seven.setTexture(&X);
						turn = o;
						tileType[6] = x;
					}
					else if (turn == o){
						seven.setTexture(&O);
						turn = x;
						tileType[6] = o;
					}
				}

				if (mouseLocation.x >= eight.getPosition().x && mouseLocation.x <= (eight.getPosition().x + 128)
					&& mouseLocation.y >= eight.getPosition().y && mouseLocation.y <= (eight.getPosition().y + 128)
					&& isClicked[7] == 0){	//Eighth tile
					mouseClicked = false;
					isClicked[7] = 1;

					if (turn == x){
						eight.setTexture(&X);
						turn = o;
						tileType[7] = x;
					}
					else if (turn == o){
						eight.setTexture(&O);
						turn = x;
						tileType[7] = o;
					}
				}

				if (mouseLocation.x >= nine.getPosition().x && mouseLocation.x <= (nine.getPosition().x + 128)
					&& mouseLocation.y >= nine.getPosition().y && mouseLocation.y <= (nine.getPosition().y + 128)
					&& isClicked[8] == 0){	//Nineth tile
					mouseClicked = false;
					isClicked[8] = 1;

					if (turn == x){
						nine.setTexture(&X);
						turn = o;
						tileType[8] = x;
					}
					else if (turn == o){
						nine.setTexture(&O);
						turn = x;
						tileType[8] = o;
					}
				}

				if (turn == x)
					turnSprite.setTexture(X);
				if (turn == o)
					turnSprite.setTexture(O);

				// Win checking. Macro defined on line 5 and 6
				/*Horizontal X's*/
				if ((	X(0) && X(1) && X(2))
					|| (X(3) && X(4) && X(5))
					|| (X(6) && X(7) && X(8))){
					allX = true;
				}

				/*Vertical X's*/
				if ((	X(0) && X(3) && X(6)
					||	X(1) && X(4) && X(7)
					||	X(2) && X(5) && X(8))){
					allX = true;
				}

				/*Diagonal X's*/
				if ((	X(0) && X(4) && X(8)
					||	X(2) && X(4) && X(6))){
					allX = true;
				}

				/* Horozontal O's*/
				if ((	O(0) && O(1) && O(2))
					|| (O(3) && O(4) && O(5))
					|| (O(6) && O(7) && O(8))){
					allO = true;
				}

				/*Vertical O's*/
				if ((	O(0) && O(3) && O(6)
					||	O(1) && O(4) && O(7)
					||	O(2) && O(5) && O(8))){
					allO = true;
				}

				/*Diagonal O's*/
				if ((	O(0) && O(4) && O(8)
					||	O(2) && O(4) && O(6))){
					allO = true;
				}
				// End of win checking


				if (allX == true){
					one.setTexture(&X);
					two.setTexture(&X);
					three.setTexture(&X);
					four.setTexture(&X);
					five.setTexture(&X);
					six.setTexture(&X);
					seven.setTexture(&X);
					eight.setTexture(&X);
					nine.setTexture(&X);

					for (int i = 0; i <= 8; i++)
						isClicked[i] = true;

				}
				if (allO){
					one.setTexture(&O);
					two.setTexture(&O);
					three.setTexture(&O);
					four.setTexture(&O);
					five.setTexture(&O);
					six.setTexture(&O);
					seven.setTexture(&O);
					eight.setTexture(&O);
					nine.setTexture(&O);

					for (int i = 0; i <= 8; i++)
						isClicked[i] = true;

				}

			}
		}

		window.clear(sf::Color(128, 128, 128));
		window.draw(one);
		window.draw(two);
		window.draw(three);
		window.draw(four);
		window.draw(five);
		window.draw(six);
		window.draw(seven);
		window.draw(eight);
		window.draw(nine);
		window.draw(playerSprite);
		window.draw(turnSprite);
		window.display();
	}

	return 0;
}