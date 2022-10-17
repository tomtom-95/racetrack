.RECIPEPREFIX = <
.PHONY = racetrack run clean

CPP = g++
CPPFLAGS = -Wall -std=c++20

racetrack:
< ${CPP} ${CPPFLAGS} -o build/racetrack src/racetrack.cpp

run:
< ./build/racetrack

clean:
< rm -rf ./build/*


