CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD 
EXEC = chess
# OBJECTS = bishop.o board.o chess.o human.o king.o knight.o main.o observer.o pawn.o piece.o player.o queen.o robot1.o robot2.o robot3.o robot4.o rook.o subject.o textrender.o
OBJECTS = bishop.o board.o chess.o graphicsrender.o human.o king.o knight.o main.o observer.o pawn.o piece.o player.o queen.o robot1.o robot2.o robot3.o robot4.o rook.o subject.o textrender.o xwindow.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	# ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS}
