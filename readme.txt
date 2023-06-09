
Se puede probar el simulador con unos scrips llamados simu1,simu2,simu3,simu4,simu5,simu6


Te dejo esta guia para poder leer las entradas y las salidas


mensajes de llegada

·	inVoltaje            380        	//  Nivel de Voltaje. 380 es solo un ejemplo. Tolera cualquier valor, pero 
actua en consecuencia
·	inOnOff                 1                 // Encender el Torno.
·	inOnOff                 0                 // Apagar el Torno
·	inHerramienta      10                 // Colocar la herramienta Nº 10. Solo se permite ponerle hasta 10 tipos.
·	inHerramienta      0                   // Quitar la herramienta
·	inMaterial          101                 // Longitud en centimetros de la barra de hierro expresados en centimetros. 
Solo puedo poner hasta 500 cm.
·	inMaterial            0                  // Quitar el material
·	inComando          3		// Comando que Indica que voy a empezar a cargar un nuevo programa. 
Borra la memoria y deja al torno en modo de edicion
·	inComando          4		// Comando que da por finalizada la Edicion del progrma

Las siguientes son posibles instrucciones del programa
·	inPrograma       550		// Velocidad de Giro del Porta Material expresada en rpm. Se puede 
indicar desde 500 hasta 600 rpm.
·	inPrograma        20                   // Instrucción de avance de material expresada en cm. Representa el 
tamaño de lo que sera el producto terminado. Se pueden fabricar piezas de hasta 50 cm.
·	inPrograma     10108		// Indica las coordenadas de la nueva posicion del Porta Herramientas. 
(el significado se encuentra explicado en el informe)
·	inPrograma     77773		// Detener giro de Porta Material
·	inPrograma     77774		// Cortar el material para asi obtener la pieza final en la salida.
·	inPrograma    777730		// Instrucción de fin de Programa
·	inComando          1		// Comando de Comienzo de Ejecución
·	inComando          0		// Finalizar ejecucion forzadamente
·	inInfoPortaHerramienta       2   // Pedir Informacion de Posicion al Porta Herramientas
·	inInfoPortaMaterial              2  // Pedir Informacion de velocidad de Giro al Porta Material



mensajes de salida

·	outprodterminado 20 //  Se produjo una pieza o producto terminado de tamaño 20 cm
·	outresiduo 10	// Se produjo un residuo de material de 20 cm. Puede haber dos motivos. O bien se 
saco el material. O se quizo fabricar un pieza demayor tamaño y no habia el material suficiente.
·	outerror 1		// No llega el Ok. luego de la Inst. de movimiento impartida al Porta herramienta. 
Por ello el controlador da un error de timeOut
·	outerror 2		// Idem Ant. Pero con respecto a la instrucción de posicionamiento.
·	outerror 3    		// Se paró  la ejecucion por corte de Energia o baja tensión.
·	outinfoportaherramienta 9999	// Informacion de posicion del portaHerramientas. En este caso es 
indefinido (ver informe parte II)
·	outinfoportamaterial 550 	// Informa velocidad de Giro del Porta Material
·	outinfoproceso 2 	  	// Ejecucion de programa finalizado normalmente
·	outerror 4 			// No hay herramienta para comenzar ejecucion
·	outerror 5 			// No hay material para comenzar ejecucion
·	outinfoproceso 1 	  	// Ejecución terminada desde teclado por usuario




*******************************************************************


Correspondencia entre componentes y Cpp/.ma

El ..top.. (Torno), y el modelo acoplado ..Controlador.. lo vas 
a encontrar en el archivo prueba.ma.


Interruptor 	--- interrup.cpp / .h
transformador	--- transfor.cpp / .h
portaHerramienta--- pherrami.cpp / .h
portaMaterial   --- pmateria.cpp / .h
Unidad Control  --- ucontrol.cpp / .h
memoria		--- memoria.cpp	 / .h






