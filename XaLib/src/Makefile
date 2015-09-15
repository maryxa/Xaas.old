##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com

UNAME_S := $(shell uname -s)

## WINDOWS MINGW32_NT
## TESTED: MINGW32_NT-6.2
## TESTED WIN7 - WIN10
## ASSUMING XAAS INSTALLED UNDER c:/XAllegro
ifeq ($(filter MINGW32_NT-%.%,$(UNAME_S)),)

    MYSQL_LIB = C:\XAllegro\libs\mysql
    MINGW_LIB_DIR=C:\XAllegro\msys\1.0\opt\windows_32\include

    CPP      = g++
    OBJDIR   = ..\objects\\
    RM       = rm -f -r
    CUR_DIR  = $(cmd %cd%)

    LIBS     = -static -L$(MYSQL_LIB)\lib 
    CPPINCS  = -I..\include -I..\include -I$(MINGW_LIB_DIR) \
		-I$(MYSQL_LIB)\include -I$(MINGW_LIB_DIR)\libxml2 \

    CPPFLAGS = $(CPPINCS) -std=c++0x -O3 -D__NO_INLINE__ -Wall

    BIN      = ..\bin\XaLib.a

.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Windows

endif

## LINUX
ifeq ($(UNAME_S),Linux)

    CPP      = g++
    OBJDIR   = ../objects/
    RM       = rm -f
    CUR_DIR  = $(shell pwd)
    BIN      = ../bin/XaLib.so

    LIBS     = -lxml2 -lxslt -lexslt -lssl -lcrypto -lmysqlclient -lcurl 
    CPPINCS  = -I../include -I/usr/include -I/usr/include/libxml2 -I/usr/include/mysql -I$(CUR_DIR)/../../XaLib/include
    LDFLAGS  = -shared
    CPPFLAGS = $(CPPINCS) -fPIC -std=c++0x -O3 -Wall

endif

## MAC
## TESTED: 10.10.3
## TESTED: 10.10.4
ifeq ($(UNAME_S),Darwin)


    CPP      = g++
    OBJDIR   = ../objects/
    RM       = rm -f
    CUR_DIR  = $(shell pwd)
    BIN      = $(CUR_DIR)/../bin/XaLib.so

    LIBS     = -lxml2 -lxslt -lexslt -lssl -lcrypto -L/usr/local/mysql/lib -lmysqlclient -lcurl 
    CPPINCS  = -I../include -I/usr/include -I/usr/include/libxml2 -I/usr/local/mysql/include
    LDFLAGS  = -dynamiclib -install_name
    CPPFLAGS = $(CPPINCS) -fPIC -std=c++0x -O3 -Wall

endif

    UNAME_P := $(shell uname -p)

#XAAS OBJ
OBJ=$(OBJDIR)XaLibBase.o $(OBJDIR)XaLibAction.o $(OBJDIR)XaLibModel.o $(OBJDIR)XaLibHttp.o $(OBJDIR)XaLibSession.o $(OBJDIR)XaLibToken.o \
    $(OBJDIR)XaLibDb.o $(OBJDIR)XaLibSql.o $(OBJDIR)XaLibConfig.o $(OBJDIR)XaLibXsl.o $(OBJDIR)XaLibCrypto.o \
    $(OBJDIR)XaLibDom.o $(OBJDIR)XaLibChar.o $(OBJDIR)XaLibCurl.o $(OBJDIR)XaLibError.o \
    $(OBJDIR)XaLibSocket.o $(OBJDIR)XaLibWebSocket.o $(OBJDIR)XaLibLog.o \
    $(OBJDIR)XaLibTime.o $(OBJDIR)XaLibWs.o $(OBJDIR)XaLibGui.o $(OBJDIR)XaLibController.o $(OBJDIR)XaLibControllerBackEnd.o $(OBJDIR)XaLibControllerFrontEnd.o\
    $(OBJDIR)XaOuType.o $(OBJDIR)XaOuObj.o $(OBJDIR)XaOu.o \
    $(OBJDIR)XaUser.o $(OBJDIR)XaUserUi.o $(OBJDIR)XaUserProfile.o $(OBJDIR)XaAddress.o $(OBJDIR)XaLabel.o $(OBJDIR)XaLanguage.o \
    $(OBJDIR)XaUserRole.o $(OBJDIR)XaCurrency.o $(OBJDIR)XaDomain.o  \
    $(OBJDIR)XaLibMail.o $(OBJDIR)XaLibRbUart.o $(OBJDIR)XaLibRbGpIo.o

#MACROS
.PHONY: all all-before all-after clean print-varialbes
all:print-varialbes $(BIN) #all-after

clean:
	${RM} $(OBJ) print-varialbes $(BIN)
all-before:
	${RM} $(OBJ)
all-after:
	$(OBJ)

print-varialbes:
	@echo "I am compiling on : " $(UNAME_P) $(UNAME_S) $(OS)

#LINK
ifeq ($(findstring MINGW32_NT,$(UNAME_S)),MINGW32_NT)
    $(BIN): $(OBJ)
	ar r $(BIN) $(OBJ)
	ranlib $(BIN) $(LDFLAGS)
endif

ifeq ($(UNAME_S),Linux)
    $(BIN): $(OBJ)
	$(CPP) $(OBJ) -v -o $(BIN) $(LIBS) $(LDFLAGS)
endif

ifeq ($(UNAME_S),Darwin)
    $(BIN): $(OBJ)
	$(CPP) $(OBJ) -v -o $(BIN) $(LIBS) $(LDFLAGS) $(BIN)
endif

#COMPILE
$(OBJDIR)XaLibController.o: XaLibController.cpp 
	$(CPP) -c XaLibController.cpp -o $(OBJDIR)XaLibController.o $(CPPFLAGS)
$(OBJDIR)XaLibControllerBackEnd.o: XaLibControllerBackEnd.cpp 
	$(CPP) -c XaLibControllerBackEnd.cpp -o $(OBJDIR)XaLibControllerBackEnd.o $(CPPFLAGS)
$(OBJDIR)XaLibControllerFrontEnd.o: XaLibControllerFrontEnd.cpp 
	$(CPP) -c XaLibControllerFrontEnd.cpp -o $(OBJDIR)XaLibControllerFrontEnd.o $(CPPFLAGS)
$(OBJDIR)XaLibBase.o: XaLibBase.cpp 
	$(CPP) -c XaLibBase.cpp -o $(OBJDIR)XaLibBase.o $(CPPFLAGS)
$(OBJDIR)XaLibAction.o: XaLibAction.cpp 
	$(CPP) -c XaLibAction.cpp -o $(OBJDIR)XaLibAction.o $(CPPFLAGS)
$(OBJDIR)XaLibModel.o: XaLibModel.cpp 
	$(CPP) -c XaLibModel.cpp -o $(OBJDIR)XaLibModel.o $(CPPFLAGS)
$(OBJDIR)XaLibHttp.o: XaLibHttp.cpp 
	$(CPP) -c XaLibHttp.cpp -o $(OBJDIR)XaLibHttp.o $(CPPFLAGS)
$(OBJDIR)XaLibSession.o: XaLibSession.cpp 
	$(CPP) -c XaLibSession.cpp -o $(OBJDIR)XaLibSession.o $(CPPFLAGS)
$(OBJDIR)XaLibToken.o: XaLibToken.cpp 
	$(CPP) -c XaLibToken.cpp -o $(OBJDIR)XaLibToken.o $(CPPFLAGS)
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
$(OBJDIR)XaLibError.o: XaLibError.cpp 
	$(CPP) -c XaLibError.cpp -o $(OBJDIR)XaLibError.o $(CPPFLAGS)
$(OBJDIR)XaLibSocket.o: XaLibSocket.cpp 
	$(CPP) -c XaLibSocket.cpp -o $(OBJDIR)XaLibSocket.o $(CPPFLAGS)
$(OBJDIR)XaLibWebSocket.o: XaLibWebSocket.cpp 
	$(CPP) -c XaLibWebSocket.cpp -o $(OBJDIR)XaLibWebSocket.o $(CPPFLAGS)
$(OBJDIR)XaLibLog.o: XaLibLog.cpp 
	$(CPP) -c XaLibLog.cpp -o $(OBJDIR)XaLibLog.o $(CPPFLAGS)
$(OBJDIR)XaLibTime.o: XaLibTime.cpp 
	$(CPP) -c XaLibTime.cpp -o $(OBJDIR)XaLibTime.o $(CPPFLAGS)
$(OBJDIR)XaLibWs.o: XaLibWs.cpp 
	$(CPP) -c XaLibWs.cpp -o $(OBJDIR)XaLibWs.o $(CPPFLAGS)
$(OBJDIR)XaLibGui.o: XaLibGui.cpp 
	$(CPP) -c XaLibGui.cpp -o $(OBJDIR)XaLibGui.o $(CPPFLAGS)
$(OBJDIR)XaUser.o: XaUser.cpp 
	$(CPP) -c XaUser.cpp -o $(OBJDIR)XaUser.o $(CPPFLAGS)
$(OBJDIR)XaUserUi.o: XaUserUi.cpp 
	$(CPP) -c XaUserUi.cpp -o $(OBJDIR)XaUserUi.o $(CPPFLAGS)

$(OBJDIR)XaOuType.o: XaOuType.cpp 
	$(CPP) -c XaOuType.cpp -o $(OBJDIR)XaOuType.o $(CPPFLAGS)

$(OBJDIR)XaOuObj.o: XaOuObj.cpp 
	$(CPP) -c XaOuObj.cpp -o $(OBJDIR)XaOuObj.o $(CPPFLAGS)
$(OBJDIR)XaOu.o: XaOu.cpp 
	$(CPP) -c XaOu.cpp -o $(OBJDIR)XaOu.o $(CPPFLAGS)

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
$(OBJDIR)XaLibMail.o: XaLibMail.cpp 
	$(CPP) -c XaLibMail.cpp -o $(OBJDIR)XaLibMail.o $(CPPFLAGS)
$(OBJDIR)XaLibRbUart.o: XaLibRbUart.cpp 
	$(CPP) -c XaLibRbUart.cpp -o $(OBJDIR)XaLibRbUart.o $(CPPFLAGS)
$(OBJDIR)XaLibRbGpIo.o: XaLibRbGpIo.cpp 
	$(CPP) -c XaLibRbGpIo.cpp -o $(OBJDIR)XaLibRbGpIo.o $(CPPFLAGS)