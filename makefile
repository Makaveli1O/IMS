main:
	g++ -g -O2 -o main main.cpp -lsimlib -lm

run:
	./main

clean:
	rm -f main