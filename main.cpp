#include "ComplexPlane.h"

int main()
{
	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Calculate the aspect ratio
	float aspectRatio = (float)VideoMode::getDesktopMode().height / (float)VideoMode::getDesktopMode().width;

	// Construct the window
	RenderWindow window(VideoMode(resolution.x, resolution.y), "Mandelbrot Set", Style::Default);
	View mainView(FloatRect(0, 0, resolution.x, resolution.y));

	// Construct an object of type complexPlane
	complexPlane plane(aspectRatio);

	// Construct font and text objects
	Font font;
	font.loadFromFile("Montserrat.otf");

	Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(Color::White);
	text.setPosition(20, 20);

	// Construct a vertex arra
	VertexArray background;
	background.setPrimitiveType(Points);
	background.resize(resolution.x * resolution.y);

	// Create an enum class state variable 
	enum class State { CALCULATING, DISPLAYING };
	State state = State::CALCULATING;

	// The main loop
	while (window.isOpen())
	{

		/*
		************
		Handle input
		************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			// Handle the player quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					state = State::CALCULATING;
					// Left click will zoom in and set new center of the complxePlane object
					plane.setCenter(window.mapPixelToCoords(Mouse::getPosition(), mainView));
					plane.zoomIn();
				}

				if (event.mouseButton.button == Mouse::Right)
				{
					// Right click will zoom out and set new center of the complxePlane object
					plane.setCenter(window.mapPixelToCoords(Mouse::getPosition(), mainView));
					plane.zoomOut();
				}
			}

			if (event.type == Event::MouseMoved)
			{
				state = State::CALCULATING;
				// setMouseLocation on the ComplexPlane object to store this coordinate
				// This will be used later to display the mouse coordinates as it moves
				plane.setMouseLocation(window.mapPixelToCoords(Mouse::getPosition(), mainView));
			}


		}// End event polling

		/*
		****************
		UPDATE THE FRAME
		****************
		*/

		if (state == State::CALCULATING)
		{
			// j = x, i = y
			for (int j = 0; j < resolution.y; j++)
			{
				for (int i = 0; i < resolution.x; i++)
				{
					// FIX THIS LATER, vvv   IDK WHAT VARIABLE REPLACES PIXELWIDTH from instructions
					background[j + i * 1].position = { (float)j,(float)i };
				}
			}
		}


		state = State::DISPLAYING;
		plane.loadText(text);

		/*
		**************
		Draw the scene
		**************
		*/

		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();



	}
	return 0;
}
