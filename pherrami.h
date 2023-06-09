/*******************************************************************
*
*  DESCRIPTION: Atomic Model Porta Herramienta
*
*  AUTHOR: Fernandez Rojo, Esteban Alejandro
*
*  EMAIL: mailto://estebanrojo@tutopia,com
*
*  DATE: 27/9/2003
*
*******************************************************************/


#ifndef __PHERRAMI_H
#define __PHERRAMI_H

#include <list>
#include "atomic.h"     /* class Atomic */

class Pherrami : public Atomic
{
public:
	Pherrami(const string &name = "Pherrami");					//Default constructor
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inInstruc;
	const Port &inHerramienta;
	const Port &inInfo1;
	const Port &inOnOff;

	Port  &outInfo1;
	Port  &outInfo2;
	Port  &outListo;
	
	Time  preparationTime;
	Time  timeLeft;
	
	double herramienta;
        double estado;
	double onOff;
	float posicion;
	double nuevaPosicion;
	double cantidadHerramienta;
	
};	/* Class Pherrami*/

#endif   //__PHERRAMI_H
