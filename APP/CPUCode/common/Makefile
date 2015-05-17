TARGET=libcommon.a

MAKEFLAGS += --warn-undefined-variables

MAXLIBDIR = ../maxlib

SRCDIR = src
OBJDIR = obj
LIBDIR = lib


INCLUDE_DIRS+= -Iinclude
CPPFLAGS+= $(INCLUDE_DIRS)
CFLAGS += $(INCLUDE_DIRS) -fPIC -std=c99
LDFLAGS += 
LDLIBS +=  -ldl -lrt


# List of object files
OBJ= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.c))

TARGETABS= $(addprefix $(LIBDIR)/, $(TARGET))

.PHONY: all
all: $(TARGETABS)


# Don't include .d files if we're cleaning
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
-include $(OBJ:.o=.d)
endif
endif


# The target
$(TARGETABS): $(OBJ)
	@echo "---- $@ ----"
	$(AR) rcs $@ $^


# Compilation (and dependency generation)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "---- $@ ----"
	$(CC) $(CPPFLAGS) $(CFLAGS) -o "$@" -c "$<"
	$(CC) $(CPPFLAGS) $(CFLAGS) -MM  -MP -MT "$(OBJDIR)/$(notdir $@)" "$<" > "$(@:.o=.d)"


# Object directory		
$(OBJ) $(OBJ:.o=.d): | $(OBJDIR)
$(OBJDIR):
	mkdir $(OBJDIR)
	
# Library directory		
$(TARGETABS): | $(LIBDIR)
$(LIBDIR):
	mkdir $(LIBDIR)
	

# Clean
.PHONY: clean distclean
distclean:clean

clean:
	rm -rf $(OBJDIR)
	rm -rf $(TARGETABS) $(LIBDIR)

