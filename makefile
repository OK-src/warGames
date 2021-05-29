COMPILER = gcc
COMPILED_FILE_NAME = WarGames
ROOT = sudo

all:
	${COMPILER} WarGames.c -o ${COMPILED_FILE_NAME}
	#            88         
	#            88         
	#            88         
	# ,adPPYba,  88   ,d8   
	#a8"     "8a 88 ,a8"    
	#8b       d8 8888[      
	#"8a,   ,a8" 88`"Yba,   
	# `"YbbdP"'  88   `Y8a  

install:
	${ROOT} cp ${COMPILED_FILE_NAME} /bin/
	#            88         
	#            88         
	#            88         
	# ,adPPYba,  88   ,d8   
	#a8"     "8a 88 ,a8"    
	#8b       d8 8888[      
	#"8a,   ,a8" 88`"Yba,   
	# `"YbbdP"'  88   `Y8a 

remove:
	${ROOT} rm -rf /bin/${COMPILED_FILE_NAME}
	#            88         
	#            88         
	#            88         
	# ,adPPYba,  88   ,d8   
	#a8"     "8a 88 ,a8"    
	#8b       d8 8888[      
	#"8a,   ,a8" 88`"Yba,   
	# `"YbbdP"'  88   `Y8a 
