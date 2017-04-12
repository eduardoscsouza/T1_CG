all:
	gcc T1.c -lGL -lglut -lGLU

run:
	./a.out

clean:
	rm *.out