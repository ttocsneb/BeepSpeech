
SRC := source
INC := include
BIN := build

ARGS := -Wall -I$(INC)

SOURCES = $(shell find $(SRC) -type f -name '*.c*')
OBJS = $(patsubst $(SRC)/%.cpp,$(BIN)/%.o,$(SOURCES))

INCLUDES = $(shell find $(INC) -type f -name '*.h*')

all: voice.a

docs: ../beepspeech-docs

../beepspeech-docs: $(INCLUDES) $(SOURCES) Doxyfile README.md
	doxygen Doxyfile

# Make a dependency map for each object file
$(BIN)/%.dep: $(SRC)/%.cpp $(BIN)/%.o
	@mkdir -p $(dir $@)
	@echo $(BIN)/$(shell $(CXX) -MM $(ARGS) $<) > $@
include $(patsubst %.o,%.dep,$(OBJS))

# Build object file
$(BIN)/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(ARGS) -c -o $@ $<

voice.a: $(OBJS)
	ar rc $@ $^

clean:
	@rm -rv $(BIN)
