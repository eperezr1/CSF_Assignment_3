CXX = g++
CXXFLAGS = -g -Wall -std=c++17

CXX_SRCS = main.cpp Cache.cpp Set.cpp Block.cpp
CXX_OBJS = $(CXX_SRCS:.cpp=.o)


%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

csim : $(CXX_OBJS)
	$(CXX) -o $@ $(CXX_OBJS)

.PHONY: solution.zip
solution.zip :
	rm -f $@
	zip -9r $@ *.cpp *.h README.txt Makefile

clean :
	rm -f csim *.o