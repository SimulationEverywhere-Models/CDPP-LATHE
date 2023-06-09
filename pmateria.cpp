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

/** include files **/
#include "pmateria.h"   // class Pmateria
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Pmateria
* Description: 
********************************************************************/
Pmateria::Pmateria( const string &name ) 
: Atomic( name )
, inInstruc( addInputPort( "inInstruc" ) )
, inMaterial( addInputPort( "inMaterial" ) )
, inInfo1( addInputPort( "inInfo1" ) )
, inOnOff( addInputPort( "inOnOff" ) )
, outInfo1( addOutputPort( "outInfo1" ) )
, outInfo2( addOutputPort( "outInfo2" ) )
, outListo( addOutputPort( "outListo" ) )
, outResiduo( addOutputPort( "outResiduo" ) )
, outProdTerminado( addOutputPort( "outProdTerminado" ) )
, preparationTime( 0, 0, 0, 0 )
{
	estado  	   = 0 ; // Detenido
	material       = 0 ; // Sin Material
	onOff          = 0 ; // Sin corriente
	velocidad	   = 0 ; // Velicidad 0 detenido
	avanceParcial  = 0 ; // auxiliar
	auxMaterial = 0 ; // auxiliar
	tiempoTranscurrido= 0 ; // auxiliar
	cantidadMaterial=0; //auxiliar
	tamanoProdTerminado=0;//auxiliar
}

/*******************************************************************
* Function Name: initFunction
* Description: iniciliza las variables descriptivas de estado
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Pmateria::initFunction()
{
	return *this ;
}
/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Pmateria::externalFunction( const ExternalMessage &msg )
{

	if(estado==99993 && (msg.port()!=inOnOff || msg.value()!=0))
	{
	   timeLeft=msg.time()-lastChange();	
	   holdIn( active, timeLeft );
	   return *this;
	}
	
	if( msg.port() == inMaterial ){
		if(msg.value()!=0 && material==0){
			material = msg.value() ; // el mensaje indica la cantidad de material
		}else{
		    if(msg.value()==0){
		    	 material=99994;
				 holdIn( active, preparationTime );
		    }
		}
	}
	if( msg.port() == inInstruc && onOff==1){ 
            if(msg.value()>=500 && msg.value()<=600 && estado==0 && material!=0 && material!=99993)
            {
			velocidad=msg.value();					  // Llegada evento girar a Velocidad
			estado=1 ;		  // es equiv. a girando
	    }
	    if(msg.value()==77773 && estado==1 && material!=0 && material!=99993)
	    { 													// Llegada evento detener=77773
			estado=0 ;		  // es equiv. a detenido
			velocidad=0;
	    }
	    if(msg.value()<=50 && material!=0){ // PosicionandoMaterial =< 50
	    		if((material+avanceParcial)>msg.value()){
				tamanoProdTerminado=msg.value();
				auxMaterial=material;
				cantidadMaterial=msg.value();
				material=99993; // Posicionando Material
				preparationTime.seconds(5);
				holdIn( active, preparationTime );
				preparationTime.seconds(0);
			}else{
              			auxMaterial=material+avanceParcial;
				material=99994; // Sacar Residuo
				holdIn( active, preparationTime );
			}
	    }
	    if(msg.value()==77774 && material!=0 && material!=99993){// evento Cortar Pieza=77774
			cantidadMaterial=material ;
			material=99995;   // Cortando Material
			holdIn( active, preparationTime );
	    }

	}
	if( msg.port() == inInfo1){ 
            if(msg.value()==1){ // La CPU pregunta si tiene Material
       		  if (material!=0){
			cantidadMaterial=material ;
			material =99991 ; // 99991 es equiv. a pasando a Material
			holdIn( active, preparationTime );
        	  }else{
			cantidadMaterial=material ;
			material =99990 ; // 99990 es equiv. a pasando a no Material
			holdIn( active, preparationTime );
		  }
	    }else{
		if(msg.value()==2 && estado==1){ // Preguntan por la Velocidad. Viene del top
		  estado       =99992 ; 	  // 99992 es equiv. a pasando a Girando
		  holdIn( active, preparationTime );
		}
	    }
	}
	if( msg.port() == inOnOff ) // Corte de Corriente
	{
		if(estado==1 && msg.value()==0){
			estado=0;
		}
		if(material==99993 && msg.value()==0){
			timeLeft= msg.time()-lastChange();
			avanceParcial=(5-timeLeft.seconds())*cantidadMaterial/5; 
			material=auxMaterial-avanceParcial ;
		}
		onOff =msg.value() ;
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Pmateria::internalFunction( const InternalMessage & )
{
	if (material==99991) material = cantidadMaterial ;
	if (material==99990) material = cantidadMaterial ;
	if (estado  ==99992) estado   = 1 ;
	if (material==99993){ 
	   material      =auxMaterial-(cantidadMaterial-avanceParcial) ;
	   avanceParcial=0 ;
	}
	if (material==99994) material = 0 ;
	if (material==99995) 
	{
	   material = cantidadMaterial ;
	}
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Pmateria::outputFunction( const InternalMessage &msg )
{
 if (material==99991) sendOutput( msg.time(), outInfo1, cantidadMaterial) ;//tiene material
 if (material==99990) sendOutput( msg.time(), outInfo1, 0) ;//no tiene material
 if (estado  ==99992) sendOutput( msg.time(), outInfo2, velocidad) ; // Velocidad
 if (material==99993) sendOutput( msg.time(), outListo, 1) ;//Termino de posicionarse
 if (material==99994) sendOutput( msg.time(), outResiduo, auxMaterial) ;//Saca Residuo
 if (material==99995) sendOutput( msg.time(), outProdTerminado, tamanoProdTerminado);
 return *this ;
}
