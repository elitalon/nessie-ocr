/**
 * Classifier.cpp - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
 */

#include "Classifier.hpp"
#include "Text.hpp"

void Classifier::buildFeatureVectors()
{

}

char Classifier::identifyCharacter()
{
	return 'a';
}

Classifier::Classifier(Shape shapes)
: featureVectors_(FeatureVector()), shapes_(Shape()), buildingFeatureVectorsTime_(0.0), extractingCharactersTime_(0.0)
{

}

Text Classifier::extractCharacters()
{
	return Text();
}

double Classifier::buildingFeatureVectorsTime()
{
	return buildingFeatureVectorsTime_;
}

double Classifier::extractingCharactersTime()
{
	return extractingCharactersTime_;
}

