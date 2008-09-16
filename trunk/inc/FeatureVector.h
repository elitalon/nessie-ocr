/**
 * FeatureVector.h - Nessie, reconocedor �ptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Tal�n
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnolog�as Cibern�ticas (IUCTC)
 */

#if !defined(_FEATUREVECTOR_H)
#define _FEATUREVECTOR_H

#include "Shape.h"

class FeatureVector
{
private:
	double normalizationFactor;
	double centroidXCoordinate;
	double centroidYCoordinate;
	void computeMoment0();
	void computeMoment1();
	void computeMoment2();
	void computeMoment3();
	void computeMoment4();
	void computeMoment5();
	void computeMoment6();
public:
	double moment0;
	double moment1;
	double moment2;
	double moment3;
	double moment4;
	double moment5;
	double moment6;
	void FeatureVector(Shape shape);
};

#endif  //_FEATUREVECTOR_H
