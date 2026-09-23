COMPILER = clang++

EXE = koji
OUT_DIR = out


# SOURCES = $(shell find src -name '*.cpp')
SOURCES = src/main.cpp

OBJECTS = $(SOURCES:%.cpp=$(OUT_DIR)/%.o)
FLAGS = -std=c++20 -g -Wall -Wformat $(shell pkg-config --cflags gtkmm-4.0 mpv taglib) 
LIBS = -ldl $(shell pkg-config --libs gtkmm-4.0 mpv taglib) 

all: $(EXE)

$(EXE): $(OBJECTS) $(FONT_OBJECT)
	$(COMPILER) $^ -o $@ $(LIBS)

$(OUT_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(COMPILER) $(FLAGS) -MMD -MP -c $< -o $@

-include $(OBJECTS:.o=.d)

clean:
	rm -rf $(EXE) $(OUT_DIR)

.PHONY: all clean
