CXXFLAGS         = -std=c++17 -Wall -pedantic -Wextra -g

PROG             = pathfinding

OBJS             = 


all: $(PROG)

$(PROG) : main.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROG) main.cpp $(OBJS)

depend:
	$(CXX) *.cpp -MM > .depend

include .depend

clean:
	rm -f $(OBJS) $(PROG)
