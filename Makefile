SRC_DIR = ./src
OBJ_DIR = ./obj
BUILD_DIR = ./build

PROJECT = ${BUILD_DIR}/ballgame.exe

################################

CPPFLAGS = -MMD $(SRC_DIR:%=-I%)
CFLAGS = -Wall -Werror -g -c
LDFLAGS = -o ${PROJECT} -lm

################################

rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRC_FILES = $(call rwildcard, ${SRC_DIR}, *.c)
OBJ_FILES = $(patsubst ./%.c, ${OBJ_DIR}/%.o, ${SRC_FILES})
DEP_FILES = $(patsubst %.o, %.d, ${OBJ_FILES})

################################

.PHONY: all
all: ${PROJECT}

.PHONY: clean
clean:
	rm -rf ${BIN_DIR} ${OBJ_DIR}

.PHONY: from-scratch
from-scratch:
	${MAKE} clean
	${MAKE} all

################################

${PROJECT}: ${OBJ_FILES}
	@mkdir -p "${@D}"
	${CC} $^ ${LDFLAGS}

${OBJ_DIR}/%.o: %.c ./Makefile
	@mkdir -p "${@D}"
	${CC} ${CFLAGS} ${CPPFLAGS} $< -o $@

-include ${DEP_FILES}
