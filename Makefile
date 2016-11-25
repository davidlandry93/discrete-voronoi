
CXX=pgc++

CXX_FLAGS=-std=c++11
SOURCES=main.cc discrete_voronoi.cc
OBJECTS=$(subst .cc,.o,${SOURCES})

all: main

main: ${OBJECTS}
	${CXX} ${CXX_FLAGS} -o main ${OBJECTS}

main.o: main.cc
	${CXX} ${CXX_FLAGS} -c main.cc

discrete_voronoi.o: discrete_voronoi.cc discrete_voronoi.h
	${CXX} ${CXX_FLAGS} -c discrete_voronoi.cc

clean:
	rm ${OBJECTS}
