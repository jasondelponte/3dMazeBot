# Based on make file at: http://mrbook.org/tutorials/make/

#--------Vars--------------
BASEDIR = .
SRCDIR = $(BASEDIR)/src
TSTSRCDIR = $(BASEDIR)/test
BINDIR = $(BASEDIR)/bin
OBJDIR = $(BASEDIR)/obj

INCLUDES = -I$(BASEDIR)/inc -I$(BASEDIR)/test

# Compiler and options
CXX = g++
CXXFLAGS = $(INCLUDES)
LDFLAGS =
EXEC = $(BINDIR)/hoverbot
TSTEXEC = $(BINDIR)/hoverbot_test

#----Source files---------
SOURCES = \
	$(SRCDIR)/game.cpp \
	$(SRCDIR)/maze.cpp \
	$(SRCDIR)/bot.cpp \
	$(SRCDIR)/env_config.cpp \
	$(SRCDIR)/pathfind.cpp \
	$(SRCDIR)/pathtree.cpp

TSTSOURCES = \
	$(TSTSRCDIR)/test_unit.cpp \
	$(TSTSRCDIR)/maze_test.cpp \
	$(TSTSRCDIR)/env_config_test.cpp \
	$(TSTSRCDIR)/pathtree_test.cpp \
	$(TSTSRCDIR)/pathfind_test.cpp

# Set the build destination to be different than the source
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
TSTOBJS = $(patsubst $(TSTSRCDIR)/%.cpp,$(OBJDIR)/%.o,$(TSTSOURCES))


#-----Commands------------
all: checkdirs $(SOURCES) $(EXEC)

test: checkdirs $(SOURCES) $(TSTSOURCES) $(TSTEXEC)
	$(TSTEXEC)

clean:
	rm -rf $(BINDIR) $(OBJDIR)

rebuild: clean all


#-----Stages--------------
$(BINDIR):
	@mkdir -p $@
$(OBJDIR):
	@mkdir -p $@
checkdirs: $(BINDIR) $(OBJDIR)

$(EXEC): $(OBJDIR)/main.o $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJDIR)/main.o $(OBJECTS) -o $@

# Build the exec with the test source included
$(TSTEXEC): $(OBJDIR)/main_test.o $(OBJECTS) $(TSTOBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJDIR)/main_test.o $(OBJECTS) $(TSTOBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TSTSRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@
