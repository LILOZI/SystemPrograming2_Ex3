# @author: oz.atar@msmail.ariel.ac.il

CXX = clang++
CXXFLAGS = -std=c++11 -Wsign-conversion -g
CATANOBJ = Catan.o Player.o Land.o LandVertex.o main.o LandEdge.o  $(addprefix cards/, $(CARDSOBJ))
CARDSOBJ = MonopolyCard.o RoadBuildingCard.o YearOfPlentyCard.o KnightCard.o VictoryPointCard.o
TESTOBJ = Test.o TestCounter.o Catan.o Player.o Land.o LandVertex.o LandEdge.o
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

all: Catan

test: $(TESTOBJ) 
	$(CXX) $(CXXFLAGS) $(TESTOBJ) -o test
	./test

Catan: $(CATANOBJ)
	$(CXX) $(CXXFLAGS) $(CATANOBJ) -o Catan

Catan.o : Catan.cpp Catan.hpp
	$(CXX) $(CXXFLAGS) -c Catan.cpp

Player.o : Player.cpp Player.hpp
	$(CXX) $(CXXFLAGS) -c Player.cpp

Land.o : Land.cpp Land.hpp
	$(CXX) $(CXXFLAGS) -c Land.cpp

LandVertex.o : LandVertex.cpp LandVertex.hpp	
	$(CXX) $(CXXFLAGS) -c LandVertex.cpp

LandEdge.o : LandEdge.cpp LandEdge.hpp
	$(CXX) $(CXXFLAGS) -c LandEdge.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

valgrind: Catan
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./Catan 2>&1 | { egrep "lost| at " || true; }
# valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

TestCounter.o: TestCounter.cpp 
	$(CXX) $(CXXFLAGS) -c TestCounter.cpp

Test.o: Test.cpp
	$(CXX) $(CXXFLAGS) -c Test.cpp

# Cards.o : Cards.cpp Cards.hpp
# 	$(CXX) $(CXXFLAGS) -c Cards.cpp

clean:
	rm -f *.o Catan test

.PHONY: all clean	