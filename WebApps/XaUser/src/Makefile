## Makefile
## info@xallegro.com

UNAME_S := $(shell uname -s)

BIN_NAME=XaUser.cgi

## WINDOWS MINGW32_NT
## TESTED: MINGW32_NT-6.2
ifeq ($(filter MINGW32_NT-%.%,$(UNAME_S)),)

    XALLEGRO_DIR = C:\XAllegro\Xaas
    MINGW_DIR = C:\MinGW\mingw32
    MYSQL_DIR =C:\Program\ Files\ \(x86\)\MySQL\MySQL\ Server\ 5.1

    XALIB_DIR = $(XALLEGRO_DIR)\XaLib
    XALIB=$(XALLEGRO_DIR)\XaLib\bin\XaLib.a

    CPP      = g++
    OBJDIR   = ..\objects\\
    RM       = rm -f -r 
    CUR_DIR  = $(cmd %cd%)

    LIBS     = C:\XAllegro\libs\libxml2\bin\libxml2.dll C:\XAllegro\libs\libxslt\bin\libxslt.dll C:\XAllegro\libs\libxslt\bin\libexslt.dll \
		C:\XAllegro\libs\openssl\bin\libeay32.dll C:\XAllegro\libs\curl\bin\libcurl.dll $(MYSQL_DIR)\lib\libmysql.dll

    CPPINCS  = -I$(XALIB_DIR)\include  -I..\include -I$(MINGW_DIR)\include \
		-I$(MYSQL_DIR)\include -I$(XALLEGRO_DIR)\libs\libxml2\include \
		-I$(XALLEGRO_DIR)\libs\libxslt\include -I$(XALLEGRO_DIR)\libs\openssl\include \
		-I$(XALLEGRO_DIR)\libs\curl\include

    LDFLAGS  =
    CPPFLAGS = $(CPPINCS) -std=c++0x -Wall

    BIN      = $(XALLEGRO_DIR)\web\$(BIN_NAME)

.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Windows

endif

## LINUX
ifeq ($(UNAME_S),Linux)

    CPP      = g++
    OBJDIR   = ../objects/
    RM       = rm -f
    BIN      = ../../../web/$(BIN_NAME)
    LIBS     = -lxml2 -lxslt -lexslt -lssl -lcrypto -L/usr/local/mysql/lib -lmysqlclient -lcurl

    XALLEGRO_DIR = ../../..
    XALIB_DIR = $(XALLEGRO_DIR)/XaLib
    XALIB=/XAllegro/Xaas/XaLib/bin/XaLib.so

    APP_NAME=XaAdv
    APP_DIR=$(XALLEGRO_DIR)\WebApps\$(APP_NAME)    

    CPPINCS  = -I../include -I/usr/include -I/usr/include/libxml2 -I/usr/include/mysql -I$(XALLEGRO_DIR)/XaLib/include
    CPPFLAGS = $(CPPINCS)  -std=c++0x -O3 -Wall

endif

## MAC
## TESTED: 10.10.3
ifeq ($(UNAME_S),Darwin)

    CPP      = g++
    OBJDIR   = ../objects/
    RM       = rm -f
    BIN      = ../../../web/$(BIN_NAME)
    LIBS     = -lxml2 -lxslt -lexslt -lssl -lcrypto -L/usr/local/mysql/lib -lmysqlclient -lcurl

    XALLEGRO_DIR = /XAllegro/Xaas
    XALIB=$(XALLEGRO_DIR)/XaLib/bin/XaLib.so

    CPPINCS  = -I../include -I/usr/include -I/opt/local/include -I/usr/include/libxml2 -I/usr/local/mysql/include -I$(XALLEGRO_DIR)/XaLib/include
    CPPFLAGS = $(CPPINCS)  -std=c++0x -O3 -Wall

endif

#User OBJ
OBJ=$(OBJDIR)Controller.o $(OBJDIR)XaOuType.o $(OBJDIR)XaOu.o $(OBJDIR)XaUserRole.o \
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
	$(CPP) $(OBJ) -v -o $(BIN) $(LIBS) $(LDFLAGS) $(XALIB)


#COMPILE
$(OBJDIR)Controller.o: Controller.cpp
	$(CPP) -c Controller.cpp -o $(OBJDIR)Controller.o $(CPPFLAGS)
$(OBJDIR)XaOuType.o: XaOuType.cpp
	$(CPP) -c XaOuType.cpp -o $(OBJDIR)XaOuType.o $(CPPFLAGS)
$(OBJDIR)XaOu.o: XaOu.cpp
	$(CPP) -c XaOu.cpp -o $(OBJDIR)XaOu.o $(CPPFLAGS)
$(OBJDIR)XaUserRole.o: XaUserRole.cpp
	$(CPP) -c XaUserRole.cpp -o $(OBJDIR)XaUserRole.o $(CPPFLAGS)
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