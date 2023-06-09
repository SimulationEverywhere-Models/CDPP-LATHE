/*******************************************************************
*
*  DESCRIPTION: Atomic Model Memoria
*
*  AUTHOR: Esteban Alejandro Fernandez Rojo
*
*  EMAIL: mailto://estebanrojo@tutopia.com
*
*  DATE: 28/9/2003
*
*******************************************************************/

#ifndef __MEMORIA_H
#define __MEMORIA_H

#include <list>
#include "atomic.h"     // class Atomic

class Memoria : public Atomic
{
public:
	Memoria( const string &name = "Memoria" );					//Default constructor

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &inAlmacenar;
	const Port &inProxima;
	Port &outProxima;
	
	Time preparationTime;
	typedef list<Value> ElementList ;
	ElementList elements ;
	Time timeLeft;
	

};	// class Memoria

#endif   //__MEMORIA_H
