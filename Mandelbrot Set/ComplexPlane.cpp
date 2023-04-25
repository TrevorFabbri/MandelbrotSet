#include "ComplexPlane.h"


ComplexPlane::ComplexPlane(float Ratio)
{
	m_aspectRatio = Ratio; //Store the Ratio into m_aspectRatio

	m_view.setSize(BASE_WIDTH, (-BASE_HEIGHT) * m_aspectRatio); //(-) size invert vertical axis.
	m_view.setCenter(0.0, 0.0);
	m_view.getViewport();
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float l_x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float l_y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

	m_view.setSize(l_x, l_y);
	//m_view.zoom();

	//Console Check
	cout << "Zoomed In!" << endl
		 << "Zoom Count : " << m_zoomCount << endl;
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float l_x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float l_y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

	m_view.setSize(l_x, l_y);
	//m_view.zoom();

	//Console Check
	cout << "Zoomed Out!" << endl
		 << "Zoom Count : " << m_zoomCount << endl;
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);

	//Console Check
	cout << "New Center" << endl;
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord; //Store the given value in the m_mouseLocation variable
}

void ComplexPlane::loadText(Text& text)
{
	stringstream ss;
	ss << "Text works!!" << endl;
	ss << "Mandelbrot Set" << endl
		<< "Center: (" << m_view.getCenter().x << "," << m_view.getCenter().y << ")" << endl
		<< "Cursor: (" <<  m_mouseLocation.x   << "," <<  m_mouseLocation.y   << ")" << endl
		<< "Left-click to Zoom in"													 << endl
		<< "Right-click to Zoom out"												 << endl; 

		text.setString(ss.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	size_t count = 0;

	complex<float> c(coord.x, coord.y); //Center
	complex<float> z(0,0);	//	z_(i + 1) = (z_i)^2 + c, where z_0 = 0;

	while ((abs(z) <= 2.0) && count < MAX_ITER)	//Loop through the formula until z exceeds 2.0 or remains stable after 64 (MAX_ITER) iterations
	{

		z = z * z + c;

		count++;
	}

	return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	//Using Professor's format:
	if (count >= MAX_ITER) //MAX ITERATIONS ARE BLACK
	{r = 0; g = 0; b = 0;}
	else if (count > (0.98 * MAX_ITER))	//UBER LEGENDARY
	{
		r = 0; g = 255; b = 0;
	}
	else if (count > (0.95 * MAX_ITER))	//VERY LEGENDARY
	{
		r = 0; g = 255; b = 64;
	}
	else if (count > (0.85 * MAX_ITER))	//LEGENDARY
	{
		r = 0; g = 255; b = 128;
	}
	else if (count > (0.8 * MAX_ITER))	//ULTRA
	{
		r = 0; g = 255; b = 187;
	}
	else if (count > (0.7 * MAX_ITER))	//SSR RANK
	{
		r = 0; g = 110; b = 255;
	}
	else if (count > (0.5 * MAX_ITER))	//SR RANK
	{
		r = 0; g = 0; b = 255;
	}
	else if (count > (0.4 * MAX_ITER))	//RARE
	{
		r = 115; g = 0; b = 255;
	}
	else if (count > (0.3 * MAX_ITER))	//GREAT
	{
		r = 175; g = 0; b = 222;
	}
	else if (count > (0.2 * MAX_ITER))	//UNCOMMON 
	{
		r = 255; g = 0; b = 175;
	}
	else if (count > (0.1 * MAX_ITER))	//COMMON RANK
	{
		r = 255; g = 0; b = 100;
	}
	else if (count > (0.05 * MAX_ITER))	//NORMY RANK
	{
		r = 255; g = 128; b = 180;
	}
	else if (count > (0.025 * MAX_ITER))	//MEH RANK
	{
		r = 255; g = 180; b = 205;
	}
	else								//BAD RANK
	{
		r = 0; g = 215; b = 255;
	}

}

View ComplexPlane::getView()
{
	return m_view;
}

