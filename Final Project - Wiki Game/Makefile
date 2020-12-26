EXENAME = pathfinder
OBJS = pathfinder.o WikiNames.o graph.o#main.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

.PHONY: all clean

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

pathfinder.o : pathfinder.cpp WikiNames.h
	$(CXX) $(CXXFLAGS) pathfinder.cpp

wiki_names.o : WikiNames.cpp WikiNames.h
	$(CXX) $(CXXFLAGS) WikiNames.cpp

graph.o : graph.cpp graph.h edge.h
	$(CXX) $(CXXFLAGS) graph.cpp

# main.o: main.cpp  
# 	$(CXX) $(CXXFLAGS) main.cpp

clean :
	-rm -f *.o $(EXENAME) WikiNames graph pathfinder
