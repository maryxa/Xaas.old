##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com


## WINDOWS MINGW32_NT
## TESTED: MINGW32_NT-6.2
## TESTED WIN7 - WIN10
## ASSUMING XAAS INSTALLED UNDER C:/XAllegro

    CYGWIN_LIB_DIR = C:\XAllegro\cygwin\usr\include

    CPP      = g++
    OBJDIR   = ..\objects\\
    RM       = rm -f -r
    CUR_DIR  = $(cmd %cd%)

    LIBS     = -static
    CPPINCS  = -I..\include -I$(CYGWIN_LIB_DIR) \
		-I$(CYGWIN_LIB_DIR)\libxml2 -I$(CYGWIN_LIB_DIR)\mysql

    CPPFLAGS = $(CPPINCS) -std=c++14 -O3

    BIN      = ..\bin\XaLib.a

.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Windows