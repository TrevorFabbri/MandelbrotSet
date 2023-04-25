// Mandelbrot Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//
//Have issues with displaying the colours. Double check if the formula in .cpp works properly and what the correct pixelWidth SHOULD be.

#include "ComplexPlane.h"

int main()
{
    float height = 1080;//VideoMode::getDesktopMode().height;
    float width = 1920;//VideoMode::getDesktopMode().width;
    //Get desktop resolution and calculate monitor aspect ratio
    float aspectRatio = height / width;

    cout << "Desktop height : " << height << endl
         << "Desktop width : " << width << endl;

    
    ///Construct window///

       //Create a video mode object
    VideoMode vm(width, height);

        //Create and open project window
    RenderWindow window(vm, "Mandelbrot Set", Style::Fullscreen);

    ///Construct object of type ComplexPlane w/ given aspectRatio.///
    ComplexPlane userPlane(aspectRatio);
    
    ///Construct Font and Text Objects///

    //Font object
    Font font;
    font.loadFromFile("fonts/Arcade.ttf");

    //Text Object
    Text shownText;
    shownText.setFont(font);
    shownText.setString("Default Words :D");
    
    ///Construct a VertexArray for drawing a color for each pixel
    //Set its primitive type to Points
    VertexArray coordArray(Points, 69);
    coordArray.setPrimitiveType(Points);

    ///Resize it to screen width * height
    coordArray.resize(height * width);

    ///Create an enum class state variable with states CALCULATING and DISPLAYING
    enum class State {CALCULATING, DISPLAYING};

    //Initialize to CALCULATING. set state back to DISPLAYING after done calculating a new complex plane view.
    State currentState = State::CALCULATING;

    //Variables to fiddle with
        //bool to deide whether to take or not to take input
        //bool takeInput = true;
    double pixelWidth = 1920; //aspectRatio / 500;
    //Vector2f funnyNumber(-1.54368901269109, 0);
    //userPlane.setCenter(funnyNumber);


    while (window.isOpen())
    {
        ////////////////////////////////////////////////////////////////////
        //                          HANDLE INPUT
        ////////////////////////////////////////////////////////////////////

        //Poll Windows queue events
        Event event;
        while (window.pollEvent(event))
        {
            //Handle (Event::Closed event) to {close the window}. Check if (Keyboard::isKeyPressed(Keyboard::Escape)) to {close the window}
            if ((event.type == Event::Closed) || (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape))) { window.close(); }
            //Handle Event::MouseButtonPressed
            if (event.type == Event::MouseButtonPressed)
            {
                //Get mouse pressed pixel location
                Vector2i pixelPos;
                pixelPos.x = event.mouseButton.x;
                pixelPos.y = event.mouseButton.y;

                Vector2f coordPos = window.mapPixelToCoords(pixelPos, userPlane.getView());  // mapPixelToCoords to find Vector2f planePos in the ComplexPlane View based on the screen mouse click screenPos.

                if (event.mouseButton.button == Mouse::Right)            // (Right click) will {zoomOut and setCenter of the ComplexPlane object}
                {
                    userPlane.zoomOut();
                    userPlane.setCenter(coordPos);
                }
                else if (event.mouseButton.button == Mouse::Left)        // (Left click) will {zoomIn and setCenter of the ComplexPlane object}
                {
                    userPlane.zoomIn();
                    userPlane.setCenter(coordPos);
                }
                currentState = State::CALCULATING;                       // Set the state to CALCULATING to generate the new complex plane view in the update segment
            }

            //Handle Event::MouseMoved
            if (event.type == Event::MouseMoved)
            {
                //Get mouse current pixel location as it moves.
                Vector2i pixelPos;
                pixelPos.x = event.mouseMove.x;
                pixelPos.y = event.mouseMove.y;

                Vector2f mousePos = window.mapPixelToCoords(pixelPos, userPlane.getView());  // mapPixelToCoords to find Vector2f mousePos in the ComplexPlane View based on the screen mouse active screenPos.

                //setMouseLocation on the ComplexPlane object to store this coordinate
                userPlane.setMouseLocation(mousePos);                    //This will be used later to display the mouse coordinates as it moves
            }
        }


        ////////////////////////////////////////////////////////////////////
        //                          UPDATE SCENE
        ////////////////////////////////////////////////////////////////////


        //int userPlane.getView().getSize().x
        
        //If the state is CALCULATING
        if (currentState == State::CALCULATING)
        {
            cout << "CALCULATING. . ." << endl;

            //Double for loop to loop through all pixels in the screen height and width
            for (int j = 0; j < width; j++) //Use j for x ...
            {
                for (int i = 0; i < height; i++) // ... and i for y
                {
                    // Set the position variable in the element of VertexArray (coordArray) that corresponds to the screen coordinate j,i
                    coordArray[j + (i * pixelWidth)].position = { (float)j, (float)i }; //Study vArray[j + i * pixelWidth].position = { (float)j,(float)i };

                    // Use mapPixelToCoords to find the Vector2f coordinate in the ComplexPlane View that corresponds to the screen pixel location at j,i
                    Vector2i pixelLocation(j, i);
                    Vector2f viewCoord = window.mapPixelToCoords(pixelLocation, userPlane.getView());

                    // Call ComplexPlane::countIterations for the Vector2f coordinate in the ComplexPlane and store the number of iterations
                    int coordIterations = userPlane.countIterations(viewCoord);

                    // Declare three local Uint8 variables r, g, b to store the RGB values for the current pixel
                    Uint8 r = 0; Uint8 g = 0; Uint8 b = 0;

                    // Pass the number of iterations and the RGB variables into ComplexPlane::iterationsToRGB. This will assign the RGB values by reference
                    userPlane.iterationsToRGB(coordIterations, r, g, b);

                    // Set the color variable in the element of VertexArray that corresponds to the screen coordinate j,i
                    coordArray[j + (i * pixelWidth)].color = { r, g, b };
                }
            }
            // Set the state to DISPLAYING
            currentState = State::DISPLAYING;

            cout << "DISPLAYING . . ." << endl;
        }

        

        //Call loadText from the ComplexPlane object
        userPlane.loadText(shownText);



        ////////////////////////////////////////////////////////////////////
        //                           DRAW SCENE
        ////////////////////////////////////////////////////////////////////

        window.clear();

      
        window.draw(coordArray);
        window.draw(shownText);
        
        window.display();
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
