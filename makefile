CXX = clang++
CXXFLAGS = -std=c++11

SRCS = main.cpp mask.cpp util.cpp
OBJS = $(SRCS:.cpp=.o)
OUT = main

$(OUT): $(OBJS)
    $(CXX) $(OBJS) -o $(OUT)

clean:
    rm -f $(OBJS) $(OUT)
