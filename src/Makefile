##  Makefile
##  Project: XAllegro
##  Author XAllegro ltd
##  info@xallegro.com

ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        CCFLAGS += -D AMD64
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
	CCFLAGS += -D IA32
    endif
else

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)

endif
ifeq ($(UNAME_S),Darwin)

    CPP      = g++
    OBJDIR   = ../objects/
    RM       = rm -f
    CUR_DIR  = $(shell pwd)
    BIN      = $(CUR_DIR)/../../XaLib/bin/XaLib.so

    LIBS     = -lxml2 -lxslt -lexslt -lssl -lcrypto -L/usr/local/mysql/lib -lmysqlclient -lcurl 
    CPPINCS  = -I../include -I/usr/include -I/usr/include/libxml2 -I/usr/local/mysql/include -I$(CUR_DIR)/../../XaLib/include
    LDFLAGS  = -dynamiclib -install_name
    CPPFLAGS = $(CPPINCS) -fPIC -std=c++0x -O3

endif

    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)

    endif
    ifneq ($(filter %86,$(UNAME_P)),)

    endif
    ifneq ($(filter arm%,$(UNAME_P)),)

    endif
endif

#XALLEGRO OBJ
OBJ=$(OBJDIR)XaLibBase.o $(OBJDIR)XaLibAction.o $(OBJDIR)XaLibHttp.o $(OBJDIR)XaLibSession.o \
    $(OBJDIR)XaLibDb.o $(OBJDIR)XaLibSql.o $(OBJDIR)XaLibConfig.o $(OBJDIR)XaLibXsl.o $(OBJDIR)XaLibCrypto.o \
    $(OBJDIR)XaLibDom.o $(OBJDIR)XaLibChar.o $(OBJDIR)XaLibCurl.o $(OBJDIR)XaLibSocket.o $(OBJDIR)XaLibLog.o \
    $(OBJDIR)XaLibTime.o $(OBJDIR)XaWs.o $(OBJDIR)XaLibGui.o $(OBJDIR)XaLibController.o \
    $(OBJDIR)XaUser.o $(OBJDIR)XaUserProfile.o $(OBJDIR)XaAddress.o $(OBJDIR)XaLabel.o $(OBJDIR)XaLanguage.o \
    $(OBJDIR)XaUserRole.o $(OBJDIR)XaCurrency.o $(OBJDIR)XaDomain.o  \
    $(OBJDIR)XaLibRbUart.o

#MACROS
.PHONY: all all-before all-after clean print-varialbes
all:print-varialbes $(BIN)

clean:
	${RM} $(OBJ) print-varialbes $(BIN)
all-before:
	${RM} $(OBJ)
all-after:
	${RM} $(OBJ)

print-varialbes:
	@echo "I am compiling on : " $(UNAME_P) $(UNAME_S) $(OS)

#LINK
$(BIN): $(OBJ)
	$(CPP) $(OBJ) -v -o $(BIN) $(LIBS) $(LDFLAGS) $(BIN)

#COMPILE
$(OBJDIR)XaLibController.o: XaLibController.cpp 
	$(CPP) -c XaLibController.cpp -o $(OBJDIR)XaLibController.o $(CPPFLAGS)
$(OBJDIR)XaLibBase.o: XaLibBase.cpp 
	$(CPP) -c XaLibBase.cpp -o $(OBJDIR)XaLibBase.o $(CPPFLAGS)
$(OBJDIR)XaLibAction.o: XaLibAction.cpp 
	$(CPP) -c XaLibAction.cpp -o $(OBJDIR)XaLibAction.o $(CPPFLAGS)
$(OBJDIR)XaLibHttp.o: XaLibHttp.cpp 
	$(CPP) -c XaLibHttp.cpp -o $(OBJDIR)XaLibHttp.o $(CPPFLAGS)
$(OBJDIR)XaLibSession.o: XaLibSession.cpp 
	$(CPP) -c XaLibSession.cpp -o $(OBJDIR)XaLibSession.o $(CPPFLAGS)
$(OBJDIR)XaLibDb.o: XaLibDb.cpp
	$(CPP) -c XaLibDb.cpp -o $(OBJDIR)XaLibDb.o $(CPPFLAGS)
$(OBJDIR)XaLibSql.o: XaLibSql.cpp
	$(CPP) -c XaLibSql.cpp -o $(OBJDIR)XaLibSql.o $(CPPFLAGS)
$(OBJDIR)XaLibConfig.o: XaLibConfig.cpp 
	$(CPP) -c XaLibConfig.cpp -o $(OBJDIR)XaLibConfig.o $(CPPFLAGS)
$(OBJDIR)XaLibXsl.o: XaLibXsl.cpp 
	$(CPP) -c XaLibXsl.cpp -o $(OBJDIR)XaLibXsl.o $(CPPFLAGS)
$(OBJDIR)XaLibCrypto.o: XaLibCrypto.cpp 
	$(CPP) -c XaLibCrypto.cpp -o $(OBJDIR)XaLibCrypto.o $(CPPFLAGS) -w
$(OBJDIR)XaLibDom.o: XaLibDom.cpp 
	$(CPP) -c XaLibDom.cpp -o $(OBJDIR)XaLibDom.o $(CPPFLAGS)
$(OBJDIR)XaLibChar.o: XaLibChar.cpp 
	$(CPP) -c XaLibChar.cpp -o $(OBJDIR)XaLibChar.o $(CPPFLAGS)
$(OBJDIR)XaLibCurl.o: XaLibCurl.cpp 
	$(CPP) -c XaLibCurl.cpp -o $(OBJDIR)XaLibCurl.o $(CPPFLAGS)
$(OBJDIR)XaLibSocket.o: XaLibSocket.cpp 
	$(CPP) -c XaLibSocket.cpp -o $(OBJDIR)XaLibSocket.o $(CPPFLAGS)
$(OBJDIR)XaLibLog.o: XaLibLog.cpp 
	$(CPP) -c XaLibLog.cpp -o $(OBJDIR)XaLibLog.o $(CPPFLAGS)
$(OBJDIR)XaLibTime.o: XaLibTime.cpp 
	$(CPP) -c XaLibTime.cpp -o $(OBJDIR)XaLibTime.o $(CPPFLAGS)
$(OBJDIR)XaWs.o: XaWs.cpp 
	$(CPP) -c XaWs.cpp -o $(OBJDIR)XaWs.o $(CPPFLAGS)
$(OBJDIR)XaLibGui.o: XaLibGui.cpp 
	$(CPP) -c XaLibGui.cpp -o $(OBJDIR)XaLibGui.o $(CPPFLAGS)
$(OBJDIR)XaUser.o: XaUser.cpp 
	$(CPP) -c XaUser.cpp -o $(OBJDIR)XaUser.o $(CPPFLAGS)
$(OBJDIR)XaUserProfile.o: XaUserProfile.cpp 
	$(CPP) -c XaUserProfile.cpp -o $(OBJDIR)XaUserProfile.o $(CPPFLAGS)
$(OBJDIR)XaAddress.o: XaAddress.cpp 
	$(CPP) -c XaAddress.cpp -o $(OBJDIR)XaAddress.o $(CPPFLAGS)
$(OBJDIR)XaLabel.o: XaLabel.cpp 
	$(CPP) -c XaLabel.cpp -o $(OBJDIR)XaLabel.o $(CPPFLAGS)
$(OBJDIR)XaLanguage.o: XaLanguage.cpp 
	$(CPP) -c XaLanguage.cpp -o $(OBJDIR)XaLanguage.o $(CPPFLAGS)
$(OBJDIR)XaUserRole.o: XaUserRole.cpp 
	$(CPP) -c XaUserRole.cpp -o $(OBJDIR)XaUserRole.o $(CPPFLAGS)
$(OBJDIR)XaCurrency.o: XaCurrency.cpp 
	$(CPP) -c XaCurrency.cpp -o $(OBJDIR)XaCurrency.o $(CPPFLAGS)
$(OBJDIR)XaDomain.o: XaDomain.cpp 
	$(CPP) -c XaDomain.cpp -o $(OBJDIR)XaDomain.o $(CPPFLAGS)
$(OBJDIR)XaLibRbUart.o: XaLibRbUart.cpp 
	$(CPP) -c XaLibRbUart.cpp -o $(OBJDIR)XaLibRbUart.o $(CPPFLAGS)