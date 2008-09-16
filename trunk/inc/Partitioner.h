/**
 * Partitioner.h - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
 */

#if !defined(_PARTITIONER_H)
#define _PARTITIONER_H

#include "Pixel.h"
#include "Shape.h"
#include "Clip.h"

class Partitioner
{
private:
	unsigned int optimalThreshold;
	Pixel seeds;
	Shape shapes;
	int floodFillingTime;
	int thresholdingTime;
	unsigned int computeOptimalThreshold(Clip clip);
	void findSeeds(Clip clip);
	void addSeed(Pixel seed);
	Pixel selectRandomSeed();
	void exploreSeedNeighbourhood(Pixel seed);
	bool isSeed(Pixel pixel);
	void removeSeed(Pixel seed);
	void addShape(Shape shape);
	void removeShape(unsigned int shape);
	void splitShape(Shape shape);
	void joinShapes(Shape leftShape, Shape rightShape);
	void sortShapes();
public:
	void Partitioner();
	void applyFloodFill(Clip clip);
	void applyThreshold(Clip clip);
	Shape shapes();
	double floodFillingTime();
	double thresholdingTime();
};

#endif  //_PARTITIONER_H
