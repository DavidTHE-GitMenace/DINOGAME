# ─── Project settings ───────────────────────────────────────────────────────────
TARGET      := DinoGame.exe
SRC_FILES   := main.cpp ApiClient.cpp
LDFLAGS     := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lcurl

# ─── Compiler settings ──────────────────────────────────────────────────────────
CXX             := g++
CPPVERSION      := -std=c++17
CXXFLAGS_DEBUG  := -g
CXXFLAGS_WARN   := -Wall -Wextra -Wunreachable-code -Wshadow -Wpedantic

# ─── Auto-generated object files ────────────────────────────────────────────────
OBJECTS := $(SRC_FILES:.cpp=.o)

# ─── Windows cleanup ────────────────────────────────────────────────────────────
DEL := del

# ─── Default target ─────────────────────────────────────────────────────────────
all: $(TARGET)

# ─── Link the executable ───────────────────────────────────────────────────────
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# ─── Compile each .cpp into .o ──────────────────────────────────────────────────
%.o: %.cpp
	$(CXX) $(CPPVERSION) $(CXXFLAGS_DEBUG) $(CXXFLAGS_WARN) -c $< -o $@

# ─── Clean up ────────────────────────────────────────────────────────────────────
clean:
	$(DEL) $(TARGET) $(OBJECTS)

.PHONY: all clean
