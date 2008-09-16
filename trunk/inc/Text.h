/**
 * Text.h - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
 */

#if !defined(_TEXT_H)
#define _TEXT_H

#include "Style.h"
#include "WordRate.h"

class Text
{
private:
	string content;
	Style styles;
	WordRate wordRates;
public:
	void Text();
	void addCharacter(char character, Style style);
	void removeCharacter(unsigned int character);
	string content();
	void content(string content);
	Style style();
	void style(unsigned int character, Style style);
	unsigned int length();
	WordRate wordRates();
};

#endif  //_TEXT_H
