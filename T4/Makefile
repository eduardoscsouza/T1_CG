all:
	g++ T4.cpp -lGL -lglut -std=c++11 -lm -o Ellipsoid.out

run:
	./Ellipsoid.out

test:
	g++ T4.cpp -lGL -lglut -std=c++11 -lm -o Ellipsoid.out -Wall -Wextra -g
	valgrind --leak-check=full --track-origins=yes ./Ellipsoid.out

clean:
	rm *.out