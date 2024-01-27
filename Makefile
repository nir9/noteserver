CC = cl

EXEC = noteserver.exe

all: $(EXEC)

$(EXEC): Main.cpp
	$(CC) /EHsc Main.cpp Logger.cpp ManagedSocket.cpp ManagedWinsock.cpp Utils.cpp kernel32.lib /link /out:$(EXEC)

clean:
	del *.obj *.exe *.lib *.exp
