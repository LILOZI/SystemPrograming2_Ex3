# @author: oz.atar@msmail.ariel.ac.il

CXX = clang++
CXXFLAGS = -std=c++11 -Werror -Wsign-conversion
SOURCEOBJ = Catan.o Player.o Land.o LandVertex.o main.o LandEdge.o


all: Catan


Catan: $(SOURCEOBJ)
	$(CXX) $(CXXFLAGS) $(SOURCEOBJ) -o Catan


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



# Cards.o : Cards.cpp Cards.hpp
# 	$(CXX) $(CXXFLAGS) -c Cards.cpp

clean:
	rm -f *.o Catan

.PHONY: all clean	