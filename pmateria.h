/*******************************************************************
*
*  DESCRIPTION: Atomic Model Porta Material
*
*  AUTHOR: Fernandez Rojo, Esteban Alejandro
*
*  EMAIL: mailto://estebanrojo@tutopia,com
*
*  DATE: 27/9/2003
*
*******************************************************************/


#ifndef __PMATERIA_H
#define __PMATERIA_H

#include <list>
#include "atomic.h"     /* class Atomic */

class Pmateria : public Atomic
{
public:
	Pmateria(const string &name = "Pmateria");					//Default constructor
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inInstruc;
	const Port &inMaterial;
	const Port &inInfo1;
	const Port &inOnOff;

	Port  &outInfo1;
	Port  &outInfo2;
	Port  &outListo;
	Port  &outResiduo;
	Port  &outProdTerminado;
	
	Time  preparationTime;
	Time  timeLeft;
	
	double material          ;
        double estado            ;
	double onOff             ;
	float  velocidad         ;
	double avanceParcial     ;
	double auxMaterial       ;
	int    tiempoTranscurrido;
	float  cantidadMaterial   ;
	float  tamanoProdTerminado;
	
};	/* Class PMateria*/

#endif   //__PMATERIA_H
