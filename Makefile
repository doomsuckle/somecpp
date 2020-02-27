main:
	g++ -std=c++1y proggy.cpp -o prog -Iinclude

#test:
#	g++ -std=c++1y testy.cpp -o test -Iinclude
#	g++ -std=c++1y proggy.cpp -o prog

clean:
	rm prog
	rm test
	rm main.d

