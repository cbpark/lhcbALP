SRCDIR   := src
BINDIR   := bin
CXXFLAGS := -g -O2 -Wall -Wextra -std=c++14 -pedantic -I$(SRCDIR) $(CXXFLAGS)
LDFLAGS  := -O2 $(LDFLAGS)
LIBS     :=
AR       := ar crs
MKDIR    := mkdir -p
RM       := rm -f

# ROOT (http://root.cern.ch/)
CXXFLAGS += $(shell root-config --noauxcflags --cflags)
LDFLAGS  += $(shell root-config --ldflags) \
        -Wl,-rpath,$(shell root-config --libdir)
LIBS     += $(shell root-config --noauxlibs --libs)

# Targets
EXE    := $(BINDIR)/lhcb_bound_2015 $(BINDIR)/lhcb_bound_2016
EXESRC := $(patsubst $(BINDIR)/%,$(SRCDIR)/%.cc,$(EXE))
EXEOBJ := $(EXESRC:.cc=.o)
OBJSRC := $(filter-out $(EXESRC),$(wildcard $(SRCDIR)/*.cc))
OBJ    := $(OBJSRC:.cc=.o)

.PHONY: all build clean

all: $(EXE)

$(BINDIR)/%: $(SRCDIR)/%.o build $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $< $(OBJ) $(LIBS)

$(LIBOBJ): CXXFLAGS += -fPIC

build:
	$(MKDIR) $(BINDIR)

clean::
	$(RM) $(EXEOBJ) $(OBJ) $(EXE)
	$(RM) -r $(BINDIR)
