  
CC = g++
CFLAGS = -Wall
EXEC_NAME = yats-main
INCLUDES =-I/usr/include/SDL -I/usr/include/boost
LIBS = -L/usr/lib/x86_64-linux-gnu/ -lSDL -lSDLmain -lboost_filesystem -lboost_system -lSDL_gfx
OBJ_FILES = yats-main.o Body.o NodeSim.o RoadLink.o Vehicle.o EnvironmentSim.o  PointSim.o  SourceSim.o  VueEnvSim.o InitialScreen.o Road.o TimerSDL.o

INSTALL_DIR = ./

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES)  -o $@ -c $<  $(LIBS)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<  $(LIBS)

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES)  -o $@ -c $<  $(LIBS)

install :
	cp $(EXEC_NAME) $(INSTALL_DIR)
