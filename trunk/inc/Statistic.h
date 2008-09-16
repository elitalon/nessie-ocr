/**
 * Statistic.h - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
 */

#if !defined(_STATISTIC_H)
#define _STATISTIC_H

#include "WordRate.h"

class Statistic
{
private:
	unsigned int nWords;
	double classifyingTime;
	WordRate wordRates;
	double removingNoiseTime;
	double convertingToGrayscaleTime;
	double floodFillingTime;
	double thresholdingTime;
	double buildingFeatureVectorsTime;
	double extractingCharactersTime;
	friend class recognizer;
	void nWords(unsigned int nWords);
	void wordRates(WordRate wordRate);
	void preprocessingTime(double removingNoiseTime, double convertingToGrayscaleTime);
	void partitioningTime(double thresholdingTime, double floodFillingTime);
	void classifyingTime(double buildingFeatureVectorsTime, double extractingCharactersTime);
public:
	double extractingCharactersTime();
	double buildingFeatureVectorsTime();
	double classifyingTime();
	double thresholdingTime();
	double floodFillingTime();
	double partitioningTime();
	double convertingToGrayscaleTime();
	double removingNoiseTime();
	double preprocessingTime();
	WordRate wordRates();
	unsigned int nWords();
};

#endif  //_STATISTIC_H
