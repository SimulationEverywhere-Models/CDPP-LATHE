/*******************************************************************
*
*  DESCRIPTION: Atomic Model Interruptor
*
*  AUTHOR: Fernandez Rojo, Esteban Alejandro
*
*  EMAIL: mailto://estebanrojo@tutopia,com
*
*  DATE: 27/9/2003
*
*******************************************************************/


#ifndef __INTERRUP_H
#define __INTERRUP_H

#include <list>
#include "atomic.h"     /* class Atomic */

class Interrup : public Atomic
{
public:
	Interrup(const string &name = "Interrup");					//Default constructor
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inVoltaje;
	const Port &inOnOff;
	Port  &outVoltaje;
	Port  &outOnOff;
	Time  preparationTime;
	Time  timeLeft;
        double estado;
	double voltaje;
	double nuevoVoltaje;
};	/* Class Interrup*/

#endif   //__INTERRUP_H
