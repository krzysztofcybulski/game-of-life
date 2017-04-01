TARGET	 = main
CC		 = gcc

CFLAGS	 = -Wall 
LINKER	 = gcc -o
LFLAGS	 = -Wall -lpng

SRCDIR	 = src
OBJDIR	 = obj
BINDIR	 = bin

SOURCES	 := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS	 := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm		 = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"