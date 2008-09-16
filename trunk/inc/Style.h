/**
 * Style.h - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
 */

#if !defined(_STYLE_H)
#define _STYLE_H

#include "FontWeight.h"
#include "FontProportionality.h"

class Style
{
private:
	unsigned int size;
	unsigned int color;
	FontWeight weight;
	FontProportionality proportionality;
public:
	bool isBold();
	bool isItalic();
	bool isUnderlined();
	bool isNormal();
	bool isMonospaced();
	bool isProportional();
	unsigned int size();
	void size(unsigned int size);
	unsigned int color();
	void color(unsigned int color);
	FontWeight weight();
	void weight(FontWeight weight);
	FontProportionality proportionality();
	void proportionality(FontProportionality proportionality);
};

#endif  //_STYLE_H
