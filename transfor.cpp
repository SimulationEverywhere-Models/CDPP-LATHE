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

/** include files **/
#include "transfor.h"   // class transfor
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Transfor
* Description: 
********************************************************************/
Transfor::Transfor( const string &name ) 
: Atomic( name )
, inVoltaje( addInputPort( "inVoltaje" ) )
, inOnOff( addInputPort( "inOnOff" ) )
, outOnOff( addOutputPort( "outOnOff" ) )
, preparationTime( 0, 0, 0, 0 )
{
	estado  = 0 ; // Apagado
	tipoCorriente = 1 ; // corriente normal
	
}

/*******************************************************************
* Function Name: initFunction
* Description: inicializa las variables descriptivas de estado
* Precondition: El tiempo del proximo evento 
interno es Infinito
********************************************************************/
Model &Transfor::initFunction()
{
	return *this ;
}
/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Transfor::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == inVoltaje ) tipoCorriente=msg.value() ;

	if( msg.port() == inOnOff ){
		if( (msg.value()==1.0)){ /* 1 equiv. a mensaje corriente, 0 no corriente */
			if (estado==0.0)
			{
				estado=99991.0 ;  /* 99991 equiv. a pasando a corriente */
				holdIn( active, preparationTime );
			}
		}
		if(msg.value()==0.0){ /* 1 equiv. a mensaje corriente, 0 no corriente */
			if (estado==1)
			{
				estado=99990.0 ;  // 99990 equiv. a pasando a no corriente
				holdIn( active, preparationTime );
			}
		}
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Transfor::internalFunction( const InternalMessage & )
{
	if (estado==99991.0) estado=1;
	if (estado==99990.0) estado=0;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Transfor::outputFunction( const InternalMessage &msg )
{
	if (estado==99991.0) sendOutput( msg.time(), outOnOff, 1); /* corriente*/
	if (estado==99990.0) sendOutput( msg.time(), outOnOff, 0); /* no corriente*/
	return *this ;
}
