VPATH = ./interface:./interface/edit_dict:./interface/edit_word

objects = dictionary.o error.o word.o main.o \
	main_interface.o edit.o \
	add_word.o remove_word.o \
	add_meaning.o remove_meaning.o change_name.o change_class.o

CXXFLAGS = -iquote /home/map22/PROGRAMMING/C++\ Project/ -std=c++11 -Wall -Wextra -Werror -g
CXX = /usr/bin/g++
g++_compile = ${CXX} ${CXXFLAGS}

my_dictionary: ${objects}
	${g++_compile} $^ -o my_dictionary

main.o: main.cc main_interface.h auxiliary.h
	${g++_compile} -c $< -o $@

dictionary.o: dictionary.cc dictionary.h error.h word.h
	${g++_compile} -c $< -o $@

error.o: error.cc error.h
	${g++_compile} -c $< -o $@

word.o: word.cc word.h error.h
	${g++_compile} -c $< -o $@

main_interface.o: main_interface.cc main_interface.h dictionary.h error.h auxiliary.h edit.h \
		add_word.h remove_word.h add_meaning.h change_name.h change_class.h remove_meaning.h
	${g++_compile} -c $< -o $@

edit.o: edit.cc edit.h dictionary.h error.h word.h auxiliary.h
	${g++_compile} -c $< -o $@

add_word.o: add_word.cc add_word.h auxiliary.h 
	${g++_compile} -c $< -o $@

remove_word.o: remove_word.cc remove_word.h dictionary.h error.h auxiliary.h
	${g++_compile} -c $< -o $@

add_meaning.o: add_meaning.cc add_meaning.h auxiliary.h error.h word.h
	${g++_compile} -c $< -o $@

remove_meaning.o: remove_meaning.cc remove_meaning.h error.h word.h auxiliary.h
	${g++_compile} -c $< -o $@

change_name.o: change_name.cc change_name.h error.h word.h auxiliary.h
	${g++_compile} -c $< -o $@

change_class.o: change_class.cc change_class.h error.h word.h auxiliary.h
	${g++_compile} -c $< -o $@

clean:
	rm -f *.o ./interface/*.o ./interface/edit_dict/*.o ./interface/edit_word/*.o my_dictionary
