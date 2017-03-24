CPP_FILES := $(wildcard src/*.c)
OBJ_FILES := $(addprefix bin/,$(notdir $(CPP_FILES:.c=.o)))
LD_FLAGS := 
CC_FLAGS := -Wall --pedantic

main: $(OBJ_FILES)
	$(CC) $(LD_FLAGS) -o $@ $^
	
bin/%.o: src/%.c
	$(CC) $(CC_FLAGS) -c -o $@ $<
	
.PHONY: clean
clean:
	rm main
	rm bin/*.o