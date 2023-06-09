[top]
components : interrup@Interrup transfor@Transfor Controlador pherrami@Pherrami pmateria@Pmateria 

in   : inPrograma inOnOff inVoltaje inComando inHerramienta inMaterial inInfoPortaHerramienta
inInfoPortaMaterial 

out  : outError outInfoPortaHerramienta outInfoPortaMaterial outInfoProceso outProdTerminado outResiduo 


Link : inPrograma 	 				inPrograma@Controlador
Link : inOnOff 	     				inOnOff@interrup
Link : inVoltaje     				inVoltaje@interrup
Link : inComando     				inComando@Controlador
Link : inHerramienta 				inHerramienta@pherrami
Link : inMaterial 	 				inMaterial@pmateria
Link : inInfoPortaHerramienta 		inInfo1@pherrami
Link : inInfoPortaMaterial 			inInfo1@pmateria

Link : outOnOff@interrup							inOnOff@transfor
Link : outVoltaje@interrup							inVoltaje@transfor
Link : outOnOff@transfor							inOnOff@pmateria
Link : outOnOff@transfor							inOnOff@pherrami
Link : outOnOff@transfor							inOnOff@Controlador
Link : outComandoAPortaHerramienta@Controlador     	inInfo1@pherrami
Link : outComandoAPortaMaterial@Controlador        	inInfo1@pmateria
Link : outInstruccionAPortaHerramienta@Controlador 	inInstruc@pherrami
Link : outInstruccionAPortaMaterial@Controlador    	inInstruc@pmateria
Link : outListo@pherrami							inListo@Controlador
Link : outListo@pmateria							inListo@Controlador
Link : outInfo1@pherrami							inHayHerramienta@Controlador
Link : outInfo1@pmateria							inHayMaterial@Controlador

Link : outInformaciondeError@Controlador           outError
Link : outInformaciondeProceso@Controlador     	   outInfoProceso
Link : outInfo2@pherrami     	  				   outInfoPortaHerramienta
Link : outInfo2@pmateria     	  				   outInfoPortaMaterial
Link : outProdTerminado@pmateria 				   outProdTerminado
Link : outResiduo@pmateria 				   		   outResiduo


[Controlador]

components : ucontrol@Ucontrol memoria@Memoria

in   : inPrograma inOnOff inComando inListo inHayHerramienta inHayMaterial
out  : outInformaciondeError outInformaciondeProceso outComandoAPortaHerramienta
outComandoAPortaMaterial outInstruccionAPortaHerramienta outInstruccionAPortaMaterial

Link : inPrograma 	 	inPrograma@ucontrol
Link : inOnOff 	     	inOnOff@ucontrol
Link : inComando     	inComando@ucontrol
Link : inListo 	 	 	inListo@ucontrol
Link : inHayHerramienta inHayHerramienta@ucontrol
Link : inHayMaterial 	inHayMaterial@ucontrol

Link : outProxima@memoria 	 inInstruc@ucontrol
Link : outPrograma@ucontrol  inAlmacenar@memoria
Link : outComando@ucontrol   inProxima@memoria
Link : outComando1@ucontrol  outComandoAPortaHerramienta
Link : outComando2@ucontrol  outComandoAPortaMaterial
Link : outInstruc@ucontrol   outInstruccionAPortaMaterial
Link : outInstruc1@ucontrol  outInstruccionAPortaHerramienta
Link : outError@ucontrol  	 outInformaciondeError
Link : outInfo1@ucontrol  	 outInformaciondeProceso


