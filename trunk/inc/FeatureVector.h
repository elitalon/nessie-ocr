/**
 * FeatureVector.h - Nessie, reconocedor óptico de texto en recortes de prensa escrita
 *
 * @author Eliezer Talón
 * @date 16/09/2008
 * @copyright 2008
 * @company Instituto Universitario de Ciencias y Tecnologías Cibernéticas (IUCTC)
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
