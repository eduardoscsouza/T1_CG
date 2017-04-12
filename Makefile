all:
	gcc T1.c -lGL -lglut -o Cata-Vento.out

run:
	./Cata-Vento.out

clean:
	rm *.out