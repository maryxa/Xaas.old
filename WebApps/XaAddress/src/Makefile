##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com

UNAME_S := $(shell uname -s)
UNAME_P := $(shell uname -p)

BIN_NAME=XaAddress.cgi

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
OBJ=$(OBJDIR)Controller.o \
    $(OBJDIR)XaAddressGeo.o $(OBJDIR)XaAddressGeoType.o \
    $(OBJDIR)XaAddressMail.o $(OBJDIR)XaAddressMailType.o \
    $(OBJDIR)XaAddressPhone.o $(OBJDIR)XaAddressPhoneCode.o $(OBJDIR)XaAddressPhoneType.o

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
$(OBJDIR)XaAddressGeo.o: XaAddressGeo.cpp
	$(CPP) -c XaAddressGeo.cpp -o $(OBJDIR)XaAddressGeo.o $(CPPFLAGS)
$(OBJDIR)XaAddressGeoType.o: XaAddressGeoType.cpp
	$(CPP) -c XaAddressGeoType.cpp -o $(OBJDIR)XaAddressGeoType.o $(CPPFLAGS)
$(OBJDIR)XaAddressMail.o: XaAddressMail.cpp
	$(CPP) -c XaAddressMail.cpp -o $(OBJDIR)XaAddressMail.o $(CPPFLAGS)
$(OBJDIR)XaAddressMailType.o: XaAddressMailType.cpp
	$(CPP) -c XaAddressMailType.cpp -o $(OBJDIR)XaAddressMailType.o $(CPPFLAGS)
$(OBJDIR)XaAddressPhone.o: XaAddressPhone.cpp
	$(CPP) -c XaAddressPhone.cpp -o $(OBJDIR)XaAddressPhone.o $(CPPFLAGS)
$(OBJDIR)XaAddressPhoneCode.o: XaAddressPhoneCode.cpp
	$(CPP) -c XaAddressPhoneCode.cpp -o $(OBJDIR)XaAddressPhoneCode.o $(CPPFLAGS)
$(OBJDIR)XaAddressPhoneType.o: XaAddressPhoneType.cpp
	$(CPP) -c XaAddressPhoneType.cpp -o $(OBJDIR)XaAddressPhoneType.o $(CPPFLAGS)