CXX = g++
CXXFLAGS = -g -Wall -std=c++17

CXX_SRCS = main.cpp
CXX_OBJS = $(CXX_SRCS:.cpp=.o)


%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $*.o

csim : $(CXX_OBJS) $(C_OBJS)
	$(CXX) -o $@ $(CXX_OBJS) $(C_OBJS)

.PHONY: solution.zip
solution.zip :
	rm -f $@
	zip -9r $@ *.cpp *.h README.txt Makefile