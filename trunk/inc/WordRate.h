/**
 * WordRate.h - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
 */

#if !defined(_WORDRATE_H)
#define _WORDRATE_H


struct WordRate
{
public:
	string word;
	unsigned int rate = 0;
};

#endif  //_WORDRATE_H
