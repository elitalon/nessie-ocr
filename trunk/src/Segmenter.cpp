/**
 * Partitioner.cpp - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
 */

#include "Segmenter.hpp"
#include "Clip.hpp"
#include "Pixel.hpp"
#include "Shape.hpp"

unsigned int Partitioner::computeOptimalThreshold(Clip clip)
{

}

void Partitioner::findSeeds(Clip clip)
{

}

void Partitioner::addSeed(Pixel seed)
{

}

Pixel Partitioner::selectRandomSeed()
{

}

void Partitioner::exploreSeedNeighbourhood(Pixel seed)
{

}

bool Partitioner::isSeed(Pixel pixel)
{

}

void Partitioner::removeSeed(Pixel seed)
{

}

void Partitioner::addShape(Shape shape)
{

}

void Partitioner::removeShape(unsigned int shape)
{

}

void Partitioner::splitShape(Shape shape)
{

}

void Partitioner::joinShapes(Shape leftShape, Shape rightShape)
{

}

void Partitioner::sortShapes()
{

}

void Partitioner::Partitioner()
{

}

void Partitioner::applyFloodFill(Clip clip)
{

}

void Partitioner::applyThreshold(Clip clip)
{

}

Shape Partitioner::shapes()
{

}

double Partitioner::floodFillingTime()
{

}

double Partitioner::thresholdingTime()
{

}

