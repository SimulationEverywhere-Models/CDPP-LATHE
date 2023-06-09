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

/** include files **/
#include "interrup.h"   // class Interrup
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Interrup
* Description: 
********************************************************************/
Interrup::Interrup( const string &name ) 
: Atomic( name )
, inVoltaje( addInputPort( "inVoltaje" ) )
, inOnOff( addInputPort( "inOnOff" ) )
, outVoltaje( addOutputPort( "outVoltaje" ) )
, outOnOff( addOutputPort( "outOnOff" ) )
, preparationTime( 0, 0, 0, 0 )
{
	estado  = 0 ; // Apagado
	voltaje = 0 ; // Sin corriente
	nuevoVoltaje = 0 ;
}

/*******************************************************************
* Function Name: initFunction
* Description: iniciliza las variables descriptivas de estado
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Interrup::initFunction()
{
	return *this ;
}
/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Interrup::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == inVoltaje ){
		if( (msg.value()>=370 && msg.value()<=390) ){
			if (voltaje<370 || voltaje>390)
			{
				nuevoVoltaje= msg.value() ;		
				voltaje=9999370390.0 ;        /*9999370390 es equiv. a pasandoA+370-390*/
				holdIn( active, preparationTime );
			}
		}
		if( (msg.value()<370) ){
			if (voltaje>=370)
			{
				nuevoVoltaje= msg.value() ;
				voltaje=9999370.0 ;  /*9999370 es equiv. a pasandoA-370*/
				holdIn( active, preparationTime );
			}
		}
		if((msg.value()>390 && msg.value()<5000)){ /* 5000 es arbitrario supongo que no*/
		     if (voltaje<=390){					   /* puede haber un voltaje mayor a 5000*/
				nuevoVoltaje= msg.value() ;
				voltaje=9999390.0 ;  /* 9999390 es equiv. a pasandoA+390 */
				holdIn( active, preparationTime );
			}
		}
	}

	if( msg.port() == inOnOff ){
		if( (msg.value()==1.0)){ /* 1 equiv. a mensaje encender, 0 apagar */
			if (estado==0.0 && voltaje>=370)
			{
				estado=99991.0 ;  /* 99991 equiv. a pasando a encendido */
				holdIn( active, preparationTime );
			}
		}
		if(msg.value()==0.0){ /* 1 equiv. a mensaje encender, 0 apagar */
			if (estado==1)
			{
				estado=99990.0 ;  // 99990 equiv. a pasando a apagado
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
Model &Interrup::internalFunction( const InternalMessage & )
{
	if (voltaje==9999370.0){
	   estado  = 99990.0 ;
	   voltaje = nuevoVoltaje ;
	   holdIn( active, preparationTime );
	}else{
	   if (voltaje==9999370390.0)  voltaje = nuevoVoltaje ; 
           if (voltaje==9999390.0) 	 voltaje = nuevoVoltaje ;
	   if (estado==99991.0) estado=1;
	   if (estado==99990.0) estado=0;		
	   passivate();
	}
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Interrup::outputFunction( const InternalMessage &msg )
{
	if (voltaje==9999370390.0)  sendOutput( msg.time(), outVoltaje, 1); /*1 Corriente Normal*/
        if (voltaje==9999390.0) 	sendOutput( msg.time(), outVoltaje, 2); /*2 Transf.Corriente*/
	if (estado==99991.0) sendOutput( msg.time(), outOnOff, 1); /* encender*/
	if (estado==99990.0) sendOutput( msg.time(), outOnOff, 0); /* apagar*/
	return *this ;
}
