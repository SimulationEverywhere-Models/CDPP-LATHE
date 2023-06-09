/*******************************************************************
*
*  DESCRIPTION: Atomic Model Unidad de Control
*
*  AUTHOR: Fernandez Rojo, Esteban Alejandro
*
*  EMAIL: mailto://estebanrojo@tutopia,com
*
*  DATE: 27/9/2003
*
*******************************************************************/


#ifndef __UCONTROL_H
#define __UCONTROL_H

#include <list>
#include "atomic.h"     /* class Atomic */

class Ucontrol : public Atomic
{
public:
	Ucontrol(const string &name = "Ucontrol");					//Default constructor
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inInstruc;
	const Port &inPrograma;
	const Port &inListo;
	const Port &inhayMaterial;
	const Port &inhayHerramienta;
	const Port &inOnOff;
	const Port &inComando;

	Port  &outInfo1;
	Port  &outInstruc;
	Port  &outInstruc1;
	Port  &outPrograma;
	Port  &outError;
	Port  &outComando;
	Port  &outComando1;
	Port  &outComando2;
	
	Time  preparationTime;
	Time  timeLeft;
	
	double estado             ;
	double instruccion        ;
	float  ejecutar           ;
	float  corriente          ;
	float  estadoAnterior     ;
	
};	/* Class Ucontrol*/

#endif   //__UCONTROL_H
