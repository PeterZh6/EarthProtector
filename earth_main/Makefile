FLAGS = -pedantic-errors -std=c++11

main.o: main.cpp ch0.h ch1.h ch2.h ch3.h ch4.h ch5.h ch6.h ch7.h
	g++ $(FLAGS) -c $<

ch0.o: ch0.cpp ch0.h ch1.h
	g++ $(FLAGS) -c $<

ch1.o: ch1.cpp ch1.h ch2.h music_game.h
	g++ $(FLAGS) -c $<

ch2.o: ch2.cpp ch2.h ch3.h wordle.h
	g++ $(FLAGS) -c $<

ch3.o: ch3.cpp ch3.h ch4.h maze.h
	g++ $(FLAGS) -c $<

ch4.o: ch4.cpp ch4.h ch5.h fight.h
	g++ $(FLAGS) -c $<

ch5.o: ch5.cpp ch5.h ch6.h blackjack.h
	g++ $(FLAGS) -c $<

ch6.o: ch6.cpp ch6.h ch7.h brainstorm.h
	g++ $(FLAGS) -c $<

ch7.o: ch7.cpp ch7.h
	g++ $(FLAGS) -c $<
	
music_game.o: music_game.cpp music_game.h
	g++ $(FLAGS) -c $<
	
wordle.o: wordle.cpp wordle.h
	g++ $(FLAGS) -c $<
	
maze.o: maze.cpp maze.h
	g++ $(FLAGS) -c $<
	
fight.o: fight.cpp fight.h
	g++ $(FLAGS) -c $<
	
blackjack.o: blackjack.cpp blackjack.h
	g++ $(FLAGS) -c $<

brainstorm.o: brainstorm.cpp brainstorm.h
	g++ $(FLAGS) -c $<
	
earthprotector: main.o ch0.o ch1.o ch2.o ch3.o ch4.o ch5.o ch6.o ch7.o music_game.o wordle.o maze.o fight.o blackjack.o brainstorm.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f earthprotector *.o

.PHONY: clean
