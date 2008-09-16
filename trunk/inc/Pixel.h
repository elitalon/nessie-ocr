/**
 * Pixel.h - Nessie, reconocedor �ptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Tal�n
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnolog�as Cibern�ticas (IUCTC)
 */

#if !defined(_PIXEL_H)
#define _PIXEL_H


class Pixel
{
private:
	unsigned int x;
	unsigned int y;
	unsigned int intensity;
public:
	void Pixel(unsigned int x, unsigned int y, unsigned int intensity);
	unsigned int x();
	void x(unsigned int position);
	unsigned int y();
	void y(unsigned int position);
	unsigned int intensity();
	void intensity(unsigned int intensity);
};

#endif  //_PIXEL_H
