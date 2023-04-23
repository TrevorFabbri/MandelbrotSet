#pragma once
#include <SFML/Graphics.hpp>
#include <complex>      
#include <sstream>

using namespace sf;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
// change back to float?
const int BASE_ZOOM = 0.5;

class complexPlane
{
private:
	Vector2f m_mouseLocation;
	View m_View;
	int m_zoomCount;
	float m_aspectRatio;
public:
	complexPlane(float aspectRatio);
	void zoomIn();
	void zoomOut();
	void setCenter(Vector2f coord);
	View getView();
	void setMouseLocation(Vector2f coord);
	void loadText(Text& text);
	size_t countIterations(Vector2f coord);
	void iterationsToRGB(size_t count, Uint8& r, Uint8& b);

};
