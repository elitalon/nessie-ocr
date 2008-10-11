/**
 * Shape.h - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
 */

#if !defined(_SHAPE_H)
#define _SHAPE_H

#include "Pixel.hpp"

class Shape
{
private:
	Pixel leftPixel;
	Pixel rightPixel;
	Pixel topPixel;
	Pixel bottomPixel;
	Pixel centroid;
	double inkArea;
	unsigned int orderInText;
	Pixel pixels;
public:
	void Shape();
	unsigned int leftPixel();
	void leftPixel(unsigned int x, unsigned int y, unsigned int intensity);
	unsigned int rightPixel();
	void rightPixel(unsigned int x, unsigned int y, unsigned int intensity);
	unsigned int topPixel();
	void topPixel(unsigned int x, unsigned int y, unsigned int intensity);
	unsigned int bottomPixel();
	void bottomPixel(unsigned int x, unsigned int y, unsigned int intensity);
	unsigned int centroid();
	void centroid(unsigned int x, unsigned int y, unsigned int intensity);
	double inkArea();
	void inkArea(double area);
	unsigned int orderInText();
	void orderInText(unsigned int order);
	void addPixel(Pixel pixel);
	void removePixel(unsigned int xCoordinate, unsigned int yCoordinate);
	Pixel pixels();
};

#endif  //_SHAPE_H
