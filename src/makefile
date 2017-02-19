#===============================================================
# Makefile
#===============================================================
# マクロ定義部
#---------------------------------------------------------------
OUTPUTDIR	= ../bin
CC		= /usr/bin/gcc
LD		= /usr/bin/g++
CPP		= /usr/bin/g++
#---------------------------------------------------------------
#
TARGET = $(OUTPUTDIR)/tt

#---------------------------------------------------------------
#
#CFLAGS		= -g
CFLAGS 		= -g -D_DEBUG
#CPPFLAGS	= -g -Std=C++11
CPPFLAGS	= -g -D_DEBUG -std=c++11 -Wwrite-strings

#---------------------------------------------------------------
#
LDFLAGS		= -lstdc++
LIBS		=

#---------------------------------------------------------------
# 中間ファイル
OBJS	= SourceAnalizer.o Element.o ElementRepository.o IdentifierInspector.o \
	ImportInspector.o InspectorBase.o ReservedInspector.o WhitespaceInspector.o \
	CommentInspector.o ElementProperties.o BBPInspector.o ColonInspector.o \
	SeparatorInspector.o NodeElement.o NodeInspectorBase.o EOFInspector.o \
	CompilationUnitInspector.o ClassDeclarationInspector.o QuortInspector.o \
	EndOfLineInspector.o OperatorDef.o OperatorInspector.o

#---------------------------------------------------------------
# 生成規則部
#.SUFF[XES:　.idI　.PC　.pc　.C　.c　.cpp
all:	$(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFFLAGS) ${LIBS} $(CFLAGS) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<
#---------------------------------------------------------------
clean:
	rm $(TARGET)
	rm $(OBJS)

remake:	clean all
