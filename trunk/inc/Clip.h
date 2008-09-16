/**
 * Clip.h - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
 */

#if !defined(_CLIP_H)
#define _CLIP_H

#include "Pixels.h"

class Clip
{
private:
	unsigned int xOrigin;
	unsigned int yOrigin;
	unsigned int height;
	unsigned int width;
	Pixels frame;
	string path;
public:
	void Clip(Pixels frame, unsigned int x, unsigned int y, unsigned int height, unsigned int width);
	unsigned int height();
	void height(unsigned int height);
	unsigned int width();
	void width(unsigned int width);
	unsigned int xOrigin();
	void xOrigin(unsigned int x);
	unsigned int yOrigin();
	void yOrigin(unsigned int y);
};

#endif  //_CLIP_H
