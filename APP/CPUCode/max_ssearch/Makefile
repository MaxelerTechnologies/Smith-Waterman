# default is to build for hardware, but can be overriden

# Useful includes and stuff
MAKEFLAGS += --warn-undefined-variables

TARGET = max_ssearch

MAXLIBDIR = ..
COMMONLIBDIR = ../common
COMMONLIB = $(COMMONLIBDIR)/lib/libcommon.a

BINDIR = bin
SRCDIR = src
OBJDIR = obj
INCDIR = include
CMDLINE = cmdline


INCLUDE_DIRS += -I$(SRCDIR) -Iinclude -I$(MAXLIBDIR) $(shell slic-config --cflags) -I$(COMMONLIBDIR)/include
CPPFLAGS += $(INCLUDE_DIRS) #-DUSE_TIMING -DAPP_NAME=\"$(TARGET)\"
CFLAGS += $(INCLUDE_DIRS) -std=c99
LDFLAGS += 
LDLIBS +=  -ldl -lrt -L$(COMMONLIBDIR)/lib -lcommon

# List of object files
OBJ=$(OBJDIR)/$(CMDLINE).o \
	$(filter-out $(OBJDIR)/$(CMDLINE).o, \
		$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.c)))

TARGETABS= $(addprefix $(BINDIR)/, $(TARGET))


.PHONY: all
all: $(MAXLIB) $(TARGETABS)

# Don't include .d files if we're cleaning
ifneq ($(MAKECMDGOALS),clean)
-include $(OBJ:.o=.d)
endif


$(COMMONLIB):
	make -C $(COMMONLIBDIR)

# The target
$(TARGETABS): $(OBJ) $(BINDIR) $(COMMONLIB)
	@echo "---- $@ ----"
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)
	rm -f $(SRCDIR)/$(CMDLINE).c $(SRCDIR)/$(CMDLINE).h
	rm -f $(OBJDIR)/$(CMDLINE).o



# Compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	@echo "---- $@ ----"
	$(CC) $(CPPFLAGS) $(CFLAGS) -o "$@" -c "$<"
	$(CC) $(CPPFLAGS) $(CFLAGS) -MM  -MP -MT "$(OBJDIR)/$(notdir $@)" "$<" > "$(@:.o=.d)"


# Cmdline
$(SRCDIR)/%.c :
	gengetopt -i $(SRCDIR)/$(CMDLINE).ggo --output-dir=$(SRCDIR)


# Object directory
$(OBJ) $(OBJ:.o=.d): | $(OBJDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)
	
# Bin directory
$(BINDIR):
	mkdir -p $(BINDIR)


# Clean
.PHONY: clean clean_cmdline distclean
distclean: clean

clean: clean_cmdline
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
	
clean_cmdline:
	rm -f $(SRCDIR)/$(CMDLINE).c $(SRCDIR)/$(CMDLINE).h
	rm -f $(OBJDIR)/$(CMDLINE).o
