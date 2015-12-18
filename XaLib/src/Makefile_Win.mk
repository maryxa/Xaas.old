##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com


## WINDOWS MINGW32_NT
## TESTED: MINGW32_NT-6.2
## TESTED WIN7 - WIN10
## ASSUMING XAAS INSTALLED UNDER c:/XAllegro

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