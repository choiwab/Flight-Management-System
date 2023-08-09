system.out: main.o flighthashtable.o mylist.o flightticket.o 
	g++ main.o flighthashtable.o mylist.o flightticket.o -o system.out
main.o: main.cpp
	g++ -c main.cpp
flighthashtable.o: flighthashtable.cpp flighthashtable.h 
	g++ -c flighthashtable.cpp
mylist.o: mylist.cpp mylist.h
	g++ -c mylist.cpp
flightticket.o: flightticket.cpp flightticket.h
	g++ -c flightticket.cpp
clean:
	rm *.o *.out