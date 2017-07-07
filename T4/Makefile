#Eduardo Santos Carlos de Souza
#9293481

all:
	g++ T4.cpp -lGL -lGLU -lglut -std=c++11 -lm -O3 -o Ellipsoid.out

run:
	./Ellipsoid.out

test:
	g++ T4.cpp -lGL -lGLU -lglut -std=c++11 -lm -O3 -o Ellipsoid.out -Wall -Wextra -g
	valgrind --leak-check=full --track-origins=yes ./Ellipsoid.out

clean:
	rm *.out