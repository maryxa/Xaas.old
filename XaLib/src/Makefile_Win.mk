##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com

## ASSUMING XAAS INSTALLED UNDER c:/XAllegro

MYSQL_LIB = C:\XAllegro\libs\mysql-connector-c-6.1.6-winx64
MINGW_LIB_DIR=C:\XAllegro\msys32\mingw64\include

CPP      = g++
OBJDIR   = ..\objects\\
RM       = rm -f -r
CUR_DIR  = $(cmd %cd%)

LIBS     = -static -L$(MYSQL_LIB)\lib 
CPPINCS  = -I..\include -I..\include -I$(MINGW_LIB_DIR) \
	   -I$(MYSQL_LIB)\include -I$(MINGW_LIB_DIR)\libxml2 \

CPPFLAGS = $(CPPINCS) -std=c++14 -O3

BIN      = ..\bin\XaLib.a

.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Windows