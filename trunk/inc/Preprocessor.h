/**
 * Preprocessor.h - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
 */

#if !defined(_PREPROCESSOR_H)
#define _PREPROCESSOR_H

#include "Clip.h"

class Preprocessor
{
private:
	unsigned int noiseThreshold;
	unsigned int allowedNoisyNeighbours;
	double removingNoiseTime;
	double convertingToGrayscaleTime;
public:
	void Preprocessor(unsigned int noiseThreshold, unsigned int noisyNeighbours);
	Clip convertToGrayscale(Clip clip);
	Clip removeIsolatedNoise(Clip clip);
	unsigned int noiseThreshold();
	void noiseThreshold(unsigned int intensity);
	unsigned int allowedNoisyNeighbours();
	void allowedNoisyNeighbours(unsigned int intensity);
	double removingNoiseTime();
	double convertingToGrayscaleTime();
};

#endif  //_PREPROCESSOR_H
