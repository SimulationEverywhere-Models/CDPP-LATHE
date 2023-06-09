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

/** include files **/
#include "ucontrol.h"   // class Ucontrol
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Ucontrol
* Description: 
********************************************************************/
Ucontrol::Ucontrol( const string &name ) 
: Atomic( name )
, inInstruc( addInputPort( "inInstruc" ) )
, inPrograma( addInputPort( "inPrograma" ) )
, inListo( addInputPort( "inListo" ) )
, inhayMaterial( addInputPort( "inhayMaterial" ) )
, inhayHerramienta( addInputPort( "inhayHerramienta" ) )
, inOnOff( addInputPort( "inOnOff" ) )
, inComando( addInputPort( "inComando" ) )
, outInfo1( addOutputPort( "outInfo1" ) )
, outInstruc ( addOutputPort( "outInstruc"  ) )
, outInstruc1( addOutputPort( "outInstruc1" ) )
, outPrograma( addOutputPort( "outPrograma" ) )
, outError( addOutputPort( "outError" ) )
, outComando( addOutputPort( "outComando" ) )
, outComando1( addOutputPort( "outComando1" ) )
, outComando2( addOutputPort( "outComando2" ) )
, preparationTime( 0, 0, 0, 0 )
{
	estado = 0         ; // pasivo
	corriente =0       ; // sin corriente
	ejecutar=0         ; // auxiliar
	instruccion=0      ; // auxiliar
	estadoAnterior=0   ; // auxiliar
}

/*******************************************************************
* Function Name: initFunction
* Description: iniciliza las variables descriptivas de estado
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Ucontrol::initFunction()
{
	return *this ;
}
/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Ucontrol::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == inPrograma && corriente!=0 && estado==3){ //estado=3 equiv. a En Edicion
		instruccion=msg.value() ;
		estado  =99994 ; // pasando a almacenar instruccion
		holdIn( active, preparationTime );
	}
	if( msg.port() == inInstruc && corriente!=0 && estado==1){ //estado=1 equiv. a ejecutando
	        if(msg.value()>=77770 || (msg.value()>=500 && msg.value()<=600) ){ // Inst.varias 
	        	if (msg.value()==777730){ // Inst. Fin programa
				estado   =999906 ; // Finalizado Normalmente
				holdIn( active, preparationTime );
	        	}else{
   		   		ejecutar=msg.value() ;
    		   		estado  =99991 ; // pasando a ejecutando intruccion
    		   		holdIn( active, preparationTime );
    		   	}
    		}
    		if(msg.value()<=50){ //Instruccion posicionar material 
		   ejecutar=msg.value() ;
		   //preparationTime.seconds(20); // time Out de instruccion
    		   estado  =999950 ; // pasando a  ejecucion intruccion
		   holdIn( active, preparationTime );
    		   //preparationTime.seconds(0) ;
    		}
    		if(msg.value()>=10000 && msg.value()<=11010){ //Instruccion mover porta-Herramienta
		   ejecutar=msg.value() ;
		   //preparationTime.seconds(20); // time Out de instruccion
    		   estado  =999960 ; // pasando a ejecucion intruccion
		   holdIn( active, preparationTime );
		   //preparationTime.seconds(0);
    		}
	}
	if( msg.port() == inComando && corriente!=0 ){ //
		if(estado==0){ // estado=0 es equiv. a pasivo
			if(msg.value()==3){	//nuevo Programa
				estado  =99993 ; // pasando a edicion
				holdIn( active, preparationTime );
			}
		}
		if(estado==3){ // estado=0 es equiv. a en Edicion
			if(msg.value()==4){
				estado  =0 ; // fin edicion
				holdIn( active, preparationTime );
			}
		}
		if(estado==0){ // estado=0 es equiv. a pasivo
			if(msg.value()==1){ // Comenzar Programa
				estado  =99997 ; // verificando Herramienta
				holdIn( active, preparationTime );
			}
		}
		if(estado==1 || estado==99995 || estado==99996){ // estado=0 es equiv. a pasivo
			if(msg.value()==0){
				estado  =999901 ; // pasando a pasivo
				holdIn( active, preparationTime );
			}
		}
	}

	if( msg.port() == inOnOff ) // Corte de Corriente
	{
		if(msg.value()==0 && corriente==1){
			estado  =999902 ; // pasando a pasivo
			corriente=0     ;
			holdIn( active, preparationTime );
		}
		if(msg.value()==1 && corriente==0){
			corriente  =1; // Llegada de Corriente
		}
	}

	if( msg.port() == inhayHerramienta && corriente!=0) // Respuesta de si hay o no herramienta
	{
		if(estado==99998){   // estado=99998 esp.resp.de si hay herramienta
			 if(msg.value()!=0) estado  =99999 ; // Verificando material
			 if(msg.value()==0) estado  =999904 ; //No hay Herramienta. pasando a pasivo
		   	 holdIn( active, preparationTime );
		}
	}
	if( msg.port() == inhayMaterial && corriente!=0) // Respuesta de si hay o no material
	{
		if(estado==999910){   // estado=999910 esp.resp.de si hay material
			if(msg.value()!=0) estado   =99992 ;  // pasando a proxima instruccion
			if(msg.value()==0) estado   =999905 ; //No hay material. pasando a pasivo
			holdIn( active, preparationTime );
		}
	}

	if(msg.port() == inListo && corriente!=0){ 
	    estado   =99992 ;
	    holdIn( active, preparationTime );
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Ucontrol::internalFunction( const InternalMessage & )
{
	if (estado==99992) estado   = 1 ; // pasa a estado ejecutando
	if (estado==99991){
	    estado = 99992 ; // pasa a estado Proxima instruccion
	    holdIn( active, preparationTime );
	    return *this;
	}
	if (estado  ==99993) estado   = 3 ; // pasa a estado en Edicion
	if (estado  ==99994) estado   = 3 ; // pasa a estado en Edicion
	if (estado  ==99995) estado   = 0 ; // pasa a estado pasivo. Time Out finalizado
	if (estado  ==99996) estado   = 0 ; // pasa a estado pasivo. Time Out finalizado
	if (estado  ==999950){  // pasa a espera de que termine inst.
	    estado   =99995 ;
	    preparationTime.seconds(20);
	    holdIn( active, preparationTime );
	    preparationTime.seconds(0);
	    return *this;
	}
	if (estado  ==999960){  // pasa a espera de que termine inst.
	    estado   =99996 ;
	    preparationTime.seconds(20);
	    holdIn( active, preparationTime );
	    preparationTime.seconds(0);
	    return *this;
	}
	if (estado  ==99997)  estado   = 99998  ; // esperando si hay herramienta
	if (estado  ==99999)  estado   = 999910 ; // esperando si hay Material
	if (estado  ==999901) estado   = 0 ; // pasando a Pasivo.Terminado por usuario
	if (estado  ==999902) estado   = 0 ; // pasando a Pasivo.Corte de Corriente
	if (estado  ==999904) estado   = 0 ; // pasando a Pasivo.No hay Herramienta
	if (estado  ==999905) estado   = 0 ; // pasando a Pasivo.No hay Material
	if (estado  ==999906) estado   = 0 ; // pasando a Pasivo.Finalizado Normalmente

	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Ucontrol::outputFunction( const InternalMessage &msg )
{

  if (estado==99991)  sendOutput(msg.time(),outInstruc ,ejecutar); //Ejecutar inst.
  if (estado==999950) sendOutput(msg.time(),outInstruc ,ejecutar); //Ejecutar inst.
  if (estado==999960) sendOutput(msg.time(),outInstruc1,ejecutar); //Ejecutar inst.
  if (estado==99992)  sendOutput(msg.time(),outComando,1) ;       //Proxima Instruccion
  if (estado==99993)  sendOutput(msg.time(),outComando,2) ;       //Borrar memoria
  if (estado==99994)  sendOutput(msg.time(),outPrograma,instruccion);//Almacenar inst.
  if (estado==99995)  sendOutput(msg.time(),outError,1)   ; // Time Out finalizado. Herramienta
  if (estado==99996)  sendOutput(msg.time(),outError,2)   ; // Time Out finalizado. Material
  if (estado==99997)  sendOutput(msg.time(),outComando1,1); // esperando si hay herramienta
  if (estado==99999)  sendOutput(msg.time(),outComando2,1); // esperando si hay Material
  if (estado==999901) sendOutput(msg.time(),outInfo1,1);   // Terminado por usuario
  if (estado==999902) sendOutput(msg.time(),outError,3);   // Corte de Corriente
  if (estado==999904) sendOutput(msg.time(),outError,4);   // No hay Herramienta
  if (estado==999905) sendOutput(msg.time(),outError,5);   // No hay Material
  if (estado==999906) sendOutput(msg.time(),outInfo1,2);   // Finalizado Normalmente
  return *this ;
}
