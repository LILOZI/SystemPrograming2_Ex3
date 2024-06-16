
CXX = clang++
CXXFLAGS = -std=c++11 -Wsign-conversion -g

all: MonopolyCard.o RoadBuildingCard.o  YearOfPlentyCard.o KnightCard.o VictoryPointCard.o

MonopolyCard.o: MonopolyCard.cpp MonopolyCard.hpp Card.hpp PromotionCard.hpp
	$(CXX) $(CXXFLAGS) -c $<

RoadBuildingCard.o: RoadBuildingCard.cpp RoadBuildingCard.hpp Card.hpp PromotionCard.hpp
	$(CXX) $(CXXFLAGS) -c $<

YearOfPlentyCard.o: YearOfPlentyCard.cpp YearOfPlentyCard.hpp Card.hpp PromotionCard.hpp
	$(CXX) $(CXXFLAGS) -c $<

KnightCard.o: KnightCard.cpp KnightCard.hpp Card.hpp
	$(CXX) $(CXXFLAGS) -c $<

VictoryPointCard.o: VictoryPointCard.cpp VictoryPointCard.hpp Card.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o

.PHONY: all clean