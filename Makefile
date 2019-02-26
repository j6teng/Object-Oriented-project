CXX = g++-5
CXXFLAGS = -std=c++14 -Werror=vla
EXEC = sorcery
OBJECTS = main.o player.o card.o minion.o ritual.o enchantment.o spell.o ascii_graphics.o Graphdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean






