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

/** include files **/
#include "memoria.h"    // class Memoria
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Memoria
* Description: 
********************************************************************/
Memoria::Memoria( const string &name )
: Atomic( name )
, inAlmacenar( addInputPort( "inAlmacenar" ) )
, inProxima( addInputPort( "inProxima" ) )
, outProxima( addOutputPort( "outProxima" ) )
, preparationTime( 0, 0, 3, 0 )
{
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Memoria::initFunction()
{
	elements.erase( elements.begin(), elements.end() ) ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Memoria::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == inAlmacenar )	elements.push_back( msg.value() ) ;

	if( msg.port() == inProxima )
	{
		if(msg.value()==1){
			if( !elements.empty() )
				holdIn( active, preparationTime );
		}else (*this).initFunction() ;
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Memoria::internalFunction( const InternalMessage & )
{
	elements.pop_front() ;
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Memoria::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), outProxima, elements.front() ) ;
	return *this ;
}
