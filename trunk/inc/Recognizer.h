/**
 * Recognizer.h - Nessie, reconocedor �ptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Tal�n
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnolog�as Cibern�ticas (IUCTC)
 */

#if !defined(_RECOGNIZER_H)
#define _RECOGNIZER_H

#include "Pixels.h"
#include "Preprocessor.h"
#include "Partitioner.h"
#include "Classifier.h"
#include "Clip.h"
#include "Shape.h"
#include "Text.h"
#include "Statistic.h"

class Recognizer : public Pixels
{
private:
	Preprocessor preprocessor;
	Partitioner partitioner;
	Classifier classifier;
	Clip clip;
	Shape shapes;
	Text text;
	Statistic statistics;
public:
	void Recognizer(string path, unsigned int x, unsigned int y, unsigned int height, unsigned int width);
	void Recognizer(int image);
	Text text();
	Statistic statistics();
	Clip clip();
	void clip(Pixels frame, unsigned int x, unsigned int y, unsigned int height, unsigned int width);
};

#endif  //_RECOGNIZER_H
