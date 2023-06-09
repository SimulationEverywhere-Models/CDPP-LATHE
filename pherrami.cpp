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
#include "pherrami.h"   // class Pherrami
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Pherrami
* Description: 
********************************************************************/
Pherrami::Pherrami( const string &name ) 
: Atomic( name )
, inInstruc( addInputPort( "inInstruc" ) )
, inHerramienta( addInputPort( "inHerramienta" ) )
, inInfo1( addInputPort( "inInfo1" ) )
, inOnOff( addInputPort( "inOnOff" ) )
, outInfo1( addOutputPort( "outInfo1" ) )
, outInfo2( addOutputPort( "outInfo2" ) )
, outListo( addOutputPort( "outListo" ) )
, preparationTime( 0, 0, 0, 0 )
{
	estado  	   = 0 ; // Detenido
	herramienta    = 0 ; // Sin Herramienta
	onOff          = 0 ; // Sin corriente
	posicion       = 0 ; // Inicial
	nuevaPosicion  = 0 ; // Variable Auxiliar
	cantidadHerramienta =0 ; // Variable Auxiliar
}

/*******************************************************************
* Function Name: initFunction
* Description: iniciliza las variables descriptivas de estado
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Pherrami::initFunction()
{
	return *this ;
}
/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Pherrami::externalFunction( const ExternalMessage &msg )
{

	if(estado==1 && (msg.port()!=inOnOff || msg.value()!=0))
	{
	   timeLeft=msg.time()-lastChange();
	   holdIn( active, timeLeft );
	   return *this;
	}


	if( msg.port() == inHerramienta ){
		if(msg.value()!=0 && herramienta==0){
			herramienta = msg.value() ; // el mensaje indica la herramienta, 0=ninguna
		}else 
		    if(msg.value()==0) herramienta=msg.value();
	}

	if( msg.port() == inInstruc && estado==0 && herramienta!=0 && onOff==1){ 
		nuevaPosicion=msg.value() ;					// Llegada de evento moverse 
		posicion=9999 ;
		estado=1 ; // es equiv. a moviendose 
		preparationTime.seconds(10);
		holdIn( active, preparationTime );
		preparationTime.seconds(0);
	}
	if( msg.port() == inInfo1){ 
            if(msg.value()==1){ // La CPU pregunta si tiene Herramienta
       		  if (herramienta!=0){
			cantidadHerramienta=herramienta ;
			herramienta =99991 ; // 99991 es equiv. a pasando a Herramienta
			holdIn( active, preparationTime );
        	  }else{
			cantidadHerramienta=herramienta ;
			herramienta =99990 ; // 99990 es equiv. a pasando a no Herramienta
			holdIn( active, preparationTime );
		  }
	    }else{
		if(msg.value()==2 && estado==0){ // Preguntan por la posicion. Viene del top
		  estado       =99992 ; 	  // 99992 es equiv. a pasando a detenido
		  holdIn( active, preparationTime );
		}
	    }
	}
	if( msg.port() == inOnOff ) // Corte de Corriente
	{
		if(estado==1 && msg.value()==0){
			estado=0;	
		}
		onOff =msg.value() ;
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Pherrami::internalFunction( const InternalMessage & )
{
	if (estado==1){   
	   estado = 0 ;
           posicion = nuevaPosicion ;
	}
	if (estado==99992) 	estado = 0 ;
	if (herramienta==99991) 	herramienta=cantidadHerramienta ;
	if (herramienta==99990) 	herramienta=cantidadHerramienta ;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Pherrami::outputFunction( const InternalMessage &msg )
{
	if (estado==1) 			sendOutput( msg.time(), outListo, 1) ;//Termino de moverse
	if (estado==99992)    	sendOutput( msg.time(), outInfo2, posicion) ; //posicion
	if (herramienta==99991)	sendOutput( msg.time(), outInfo1, 1) ;//tiene herramienta
	if (herramienta==99990)	sendOutput( msg.time(), outInfo1, 0) ;//no tiene herramienta 
	return *this ;
}
