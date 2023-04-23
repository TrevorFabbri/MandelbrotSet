#include "ComplexPlane.h"

complexPlane::complexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_View.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_View.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}

void complexPlane::zoomIn()
{
	m_zoomCount++;
	float x = BASE_WIDTH * (BASE_ZOOM ^ m_zoomCount);
	float y = BASE_HEIGHT * m_aspectRatio * (BASE_ZOOM ^ m_zoomCount);
	m_View.setSize(x, y);
}

void complexPlane::zoomOut()
{
	m_zoomCount--;
	float x = BASE_WIDTH * (BASE_ZOOM ^ m_zoomCount);
	float y = BASE_HEIGHT * m_aspectRatio * (BASE_ZOOM ^ m_zoomCount);
	m_View.setSize(x, y);
}

void complexPlane::setCenter(Vector2f coord)
{
	m_View.setCenter(coord);
}

View complexPlane::getView()
{
	return m_View;
}

void complexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

void complexPlane::loadText(Text& text)
{
	Vector2f temp = m_View.getCenter();
	std::stringstream textStream;
	textStream <<
		"Mandelbrot Set" <<
		"\nCenter: (" << temp.x << "," << temp.y << ")"
		"\nCursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" <<
		"\nLeft-click to Zoom in" <<
		"\nRight-click to Zoom out";
	text.setString(textStream.str());
}

size_t complexPlane::countIterations(Vector2f coord)
{
	// Fix this later
	size_t temp = 5;



	return temp;
}

void complexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& b)
{
	// Finish this later

}
