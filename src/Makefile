app: *.h app.cpp
	g++ app.cpp -o app -O3 -fopenmp -mcmodel=large
test: app
	./app < toydata.txt