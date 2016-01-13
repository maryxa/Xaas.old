## Makefile
## info@xallegro.com

UNAME_S := $(shell uname -s)

BIN_NAME=XaUserUi.cgi

## WINDOWS MINGW32_NT
## TESTED: MINGW32_NT-6.2
ifeq ($(filter CYGWIN_NT-%.%,$(UNAME_S)),)

    XALLEGRO_DIR = C:\XAllegro\Xaas

    MYSQL_LIB = C:\XAllegro\libs\mysql64
    MINGW_LIB_DIR=C:\XAllegro\cygwin\usr\include

    XALIB_DIR = $(XALLEGRO_DIR)\XaLib
    XALIB=$(XALLEGRO_DIR)\XaLib\bin\XaLib.a

    CPP      = g++
    OBJDIR   = ..\objects\\
    RM       = rm -f -r 
    CUR_DIR  = $(cmd %cd%)

    LIBS     = -L$(MINGW_LIB_DIR)\lib -L$(MINGW_LIB_DIR)\bin \
		-lcurl.dll -lcrypto -lxml2.dll -lxslt.dll -lexslt.dll -lmysqlclient\

    CPPINCS  = -I$(XALIB_DIR)\include -I..\include \
		-I$(MINGW_LIB_DIR) -I$(MINGW_LIB_DIR)\libxml2 -I$(MINGW_LIB_DIR)\mysql  

    LDFLAGS  =
    CPPFLAGS = $(CPPINCS) -std=c++14 -Wall

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
## TESTED: 10.10.4
## TESTED: 10.10.5
ifeq ($(UNAME_S),Darwin)

    CPP      = g++
    OBJDIR   = ../objects/
    RM       = rm -f
    BIN      = ../../../web/$(BIN_NAME)
    LIBS     = -lxml2 -lxslt -lexslt -lssl -lcrypto -L/usr/local/mysql/lib -lmysqlclient -lcurl

    XALLEGRO_DIR = /XAllegro/Xaas
    XALIB=$(XALLEGRO_DIR)/XaLib/bin/XaLib.so

    CPPINCS  = -I../include -I/usr/include -I/opt/local/include -I/usr/include/libxml2 -I/usr/local/mysql/include -I$(XALLEGRO_DIR)/XaLib/include
    CPPFLAGS = $(CPPINCS)  -std=c++14 -O3 -Wall

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
