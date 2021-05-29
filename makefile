COMPILER = gcc
COMPILED_FILE_NAME = WarGames
ROOT = sudo

all:
	${COMPILER} WarGames.c -o ${COMPILED_FILE_NAME}

install:
	${ROOT} cp ${COMPILED_FILE_NAME} /bin/

remove:
	${ROOT} rm -rf /bin/${COMPILED_FILE_NAME}
