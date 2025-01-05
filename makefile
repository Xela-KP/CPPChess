OBJ_DIR = build/obj
SRC_DIR = src
INCLUDE_DIR = ./include
CXX = clang++
CXXFLAGS = -std=c++23 -I$(INCLUDE_DIR)
$(shell mkdir -p $(OBJ_DIR))
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)
clean:
	rm -rf $(OBJ_DIR) main
.PHONY: clean
