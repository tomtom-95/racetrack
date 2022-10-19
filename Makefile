.RECIPEPREFIX = <
.PHONY = racetrack run clean

CPP = g++
CPPFLAGS = -Wall -std=c++20

INCLUDE = -I/opt/homebrew/Cellar/boost/1.80.0/include

racetrack:
< ${CPP} ${CPPFLAGS} ${INCLUDE} -o build/racetrack src/racetrack.cpp

run:
< ./build/racetrack

clean:
< rm -rf ./build/*


