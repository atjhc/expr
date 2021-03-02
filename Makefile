CC = clang
LIBNAME = libexpr.a

BUILD = build
OBJECTS =  parser.o lexer.o ast.o sym.o expr.o

OFILES = $(OBJECTS:%.o=$(BUILD)/%.o)
CFLAGS = -I$(BUILD) -I./

all: $(BUILD)/$(LIBNAME) $(BUILD)/tests

format:
	clang-format -i --style=file *.c *.h

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/tests: tests.c $(BUILD)/$(LIBNAME)
	$(CC) $(CFLAGS) -o $(BUILD)/tests tests.c $(BUILD)/$(LIBNAME)

$(BUILD)/$(LIBNAME): $(BUILD) $(OFILES)
	ar rc $(BUILD)/$(LIBNAME) $(BUILD)/*.o
	ranlib $(BUILD)/$(LIBNAME)

$(BUILD)/lexer.c: $(BUILD) grammar.l
	flex --outfile=$(BUILD)/lexer.c --header-file=$(BUILD)/lexer.h grammar.l

$(BUILD)/parser.c: $(BUILD) grammar.y
	bison --output-file=$(BUILD)/parser.c --defines=$(BUILD)/parser.h grammar.y

$(BUILD)/%.o: %.c %.h $(BUILD)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -rf $(BUILD)

.PHONY: all format clean