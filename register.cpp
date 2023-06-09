/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"      // class Queue
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico
#include "interrup.h"   // class Interruptor
#include "transfor.h"   // class Transformador
#include "pherrami.h"   // class Porta Herramientas
#include "pmateria.h"   // class Porta Material
#include "ucontrol.h"   // class Unidad de Control
#include "memoria.h"    // class Memoria

void MainSimulator::registerNewAtomics()
{
     SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
     SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
     SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
     SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
     SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
     SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Interrup>() , "Interrup" ) ;
     SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transfor>() , "Transfor" ) ;
     SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Pherrami>() , "Pherrami" ) ;
     SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Pmateria>() , "Pmateria" ) ;
     SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Ucontrol>() , "Ucontrol" ) ;
     SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Memoria>()  , "Memoria" ) ;
}
