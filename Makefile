# Based on make file at: http://mrbook.org/tutorials/make/

#--------Vars--------------
BASEDIR = .
SRCDIR = $(BASEDIR)/src
BINDIR = $(BASEDIR)/bin
OBJDIR = $(BASEDIR)/obj

INCLUDES = -I$(BASEDIR)/inc

# Compiler and options
CXX = g++
CXXFLAGS = $(INCLUDES)
LDFLAGS =
EXEC = $(BINDIR)/hoverbot

SOURCES = $(SRCDIR)/main.cpp \
	$(SRCDIR)/game.cpp \
	$(SRCDIR)/maze.cpp \
	$(SRCDIR)/bot.cpp \
	$(SRCDIR)/env_config.cpp

# Set the build destination to be different than the source
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

all: checkdirs $(SOURCES) $(EXEC)

$(BINDIR):
	@mkdir -p $@
$(OBJDIR):
	@mkdir -p $@
checkdirs: $(BINDIR) $(OBJDIR)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	rm -rf $(BINDIR) $(OBJDIR)

rebuild: clean all

test: all