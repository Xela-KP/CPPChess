CXX = clang++
CXXFLAGS = -std=c++11

SRCS = main.cpp util.cpp mask.cpp fen.cpp movement.cpp
OBJS = $(SRCS:.cpp=.o)
OUT = main

$(OUT): $(OBJS)
    $(CXX) $(OBJS) -o $(OUT)

clean:
    rm -f $(OBJS) $(OUT)
