

CPPFLAGS = -std=c++1y
LFLAGS = -ltgui -lthor -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OUTPUT = bin/main

main: main.o Fruit.o Snake.o Menu.o InGame.o Game.o SettingsParser.o
	$(CXX) main.o Fruit.o Snake.o Menu.o InGame.o Game.o SettingsParser.o -o $(OUTPUT) $(CPPFLAGS) $(LFLAGS)
	
main.o: main.cpp
	$(CXX) main.cpp -c $(CPPFLAGS) $(LFLAGS)

Fruit.o: Fruit.cpp
	$(CXX) Fruit.cpp -c $(CPPFLAGS) $(LFLAGS)
	
Snake.o: Snake.cpp
	$(CXX) Snake.cpp -c $(CPPFLAGS) $(LFLAGS)

Menu.o: Menu.cpp
	$(CXX) Menu.cpp -c $(CPPFLAGS) $(LFLAGS)

InGame.o: InGame.cpp
	$(CXX) InGame.cpp -c $(CPPFLAGS) $(LFLAGS)
	
Game.o: Game.cpp
	$(CXX) Game.cpp -c $(CPPFLAGS) $(LFLAGS)
		
SettingsParser.o: SettingsParser.cpp
	$(CXX) SettingsParser.cpp -c $(CPPFLAGS) $(LFLAGS)
	
all: main

clean:
	rm -rf *o main
	
.PHONY:
	all clean
