##  Makefile
##  Project: XAAS APP XaUserUi
##  Alessandro Mariotti
##  alex@xallegro.com

UNAME_S := $(shell uname -s)
UNAME_P := $(shell uname -p)

BIN_NAME=XaUser.cgi

##WINDOWS CYGWIN
ifeq ($(filter CYGWIN_NT-%.%,$(UNAME_S)),)
    include Makefile_Win.mk
endif

## LINUX
ifeq ($(UNAME_S),Linux)
   include Makefile_Linux.mk
endif

##DARWIN
ifeq ($(UNAME_S),Darwin)
    include Makefile_Mac.mk
endif

#User OBJ
OBJ=$(OBJDIR)Controller.o $(OBJDIR)XaPages.o $(OBJDIR)XaOuTypeUi.o $(OBJDIR)XaOuUi.o 

#MACROS
.PHONY: all all-before all-after clean print-varialbes
all:print-varialbes $(BIN) all-after

clean:
	${RM} $(OBJ) print-varialbes $(BIN)
all-before:
	${RM} $(OBJ)
all-after:
	${RM} $(OBJ)

print-varialbes:
	@echo "I am compiling on : " $(UNAME_P) $(UNAME_S) $(OS) $(PROCESSOR_ARCHITECTURE) $(CASE)

#LINK
    $(BIN): $(OBJ)
	$(CPP) $(OBJ) -v -o $(BIN) $(XALIB) $(LIBS)

#COMPILE
$(OBJDIR)Controller.o: Controller.cpp
	$(CPP) -c Controller.cpp -o $(OBJDIR)Controller.o $(CPPFLAGS)
$(OBJDIR)XaPages.o: XaPages.cpp
	$(CPP) -c XaPages.cpp -o $(OBJDIR)XaPages.o $(CPPFLAGS)
$(OBJDIR)XaOuTypeUi.o: XaOuTypeUi.cpp
	$(CPP) -c XaOuTypeUi.cpp -o $(OBJDIR)XaOuTypeUi.o $(CPPFLAGS)
$(OBJDIR)XaOuUi.o: XaOuUi.cpp
	$(CPP) -c XaOuUi.cpp -o $(OBJDIR)XaOuUi.o $(CPPFLAGS)
