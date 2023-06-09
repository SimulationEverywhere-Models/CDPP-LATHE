/*******************************************************************
*
*  DESCRIPTION: Atomic Model Transformador
*
*  AUTHOR: Fernandez Rojo, Esteban Alejandro
*
*  EMAIL: mailto://estebanrojo@tutopia,com
*
*  DATE: 27/9/2003
*
*******************************************************************/


#ifndef __TRANSFOR_H
#define __TRANSFOR_H

#include <list>
#include "atomic.h"     /* class Atomic */

class Transfor : public Atomic
{
public:
	Transfor(const string &name = "Transfor");					//Default constructor
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inVoltaje;
	const Port &inOnOff;
	Port  &outOnOff;
	Time  preparationTime;
	Time  timeLeft;
        double estado;
	double tipoCorriente;
};	/* Class Transfor*/

#endif   //__TRANSFOR_H
