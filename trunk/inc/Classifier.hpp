/**
 * Classifier.h - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
 */

#if !defined(_CLASSIFIER_H)
#define _CLASSIFIER_H

#include "FeatureVector.hpp"
#include "Shape.hpp"
#include "Style.hpp"
#include "Text.hpp"

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
