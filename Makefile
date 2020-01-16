CXX = g++
CXXFLAGS = -std=c++14
EXEC = sorcery
OBJECTS = ascii_graphics.o main.o Board.o Card.o Enchantment.o Minion.o Observer.o Player.o Ritual.o Spell.o TextDisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
