/**
 * Partitioner.cpp - Nessie, reconocedor �ptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Tal�n
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnolog�as Cibern�ticas (IUCTC)
 */

#include "Partitioner.h"
#include "Clip.h"
#include "Pixel.h"
#include "Shape.h"

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

