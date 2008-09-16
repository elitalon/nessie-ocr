/**
 * Classifier.h - Nessie, reconocedor �ptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Tal�n
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnolog�as Cibern�ticas (IUCTC)
 */

#if !defined(_CLASSIFIER_H)
#define _CLASSIFIER_H

#include "FeatureVector.h"
#include "Shape.h"
#include "Style.h"
#include "Text.h"

class Classifier
{
private:
	FeatureVector featureVectors;
	Shape shapes;
	double buildingFeatureVectorsTime;
	double extractingCharactersTime;
	void buildFeatureVectors();
	char identifyCharacter();
	Style identifyCharacterStyle();
public:
	void Classifier(Shape[] shapes);
	Text extractCharacters();
	double buildingFeatureVectorsTime();
	double extractingCharactersTime();
};

#endif  //_CLASSIFIER_H
