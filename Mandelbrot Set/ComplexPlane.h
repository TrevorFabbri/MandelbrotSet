#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <complex>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

class ComplexPlane
{
private:
	Vector2f m_mouseLocation;
	View m_view;
	int m_zoomCount;
	float m_aspectRatio;

	const unsigned int MAX_ITER = 64;
	const float BASE_WIDTH = 4.0;
	const float BASE_HEIGHT = 4.0;
	const float BASE_ZOOM = 0.5;

public:
	ComplexPlane(float Ratio);					//class construct w/ float parameter
	void zoomIn();								//Call to zoom in
	void zoomOut();								//Call to zoom out
	void setCenter(Vector2f coord);				//Call to set center to a taken coordinate
	View getView();								//Call to return a View object
	void setMouseLocation(Vector2f coord);		//Call to set mouse location to a taken coordinate
	void loadText(Text& text);					//Call to load a taken and referenced text
	size_t countIterations(Vector2f coord);		//Call to take a coordinate and return an iteration count
	void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);	//

};