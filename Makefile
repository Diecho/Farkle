CXX = g++

a.out: main.o die.o player.o table.o scoreboard.o
	$(CXX) main.o die.o player.o table.o scoreboard.o

main.o: main.cc die.h player.h table.h scoreboard.h
	$(CXX) -c main.cc

die.o: die.cc die.h
	$(CXX) -c die.cc

player.o: player.cc player.h die.h
	$(CXX) -c player.cc

table.o: table.cc table.h player.h die.h
	$(CXX) -c table.cc

scoreboard.o: scoreboard.cc scoreboard.h player.h table.h
	$(CXX) -c scoreboard.cc

clean:
	rm -f *.o a.out core
