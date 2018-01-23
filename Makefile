CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Werror=vla -MMD
EXEC = quadris
OBJECTS = main.o bar.o block.o board.o cell.o command.o graphicDisplay.o info.o level0.o level1.o level2.o level3.o nextGenerator.o observer.o record.o rect.o square.o subject.o textdisplay.o unique.o window.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean

