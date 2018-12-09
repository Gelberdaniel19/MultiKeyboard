#pragma once

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

void emit(int fd, int type, int code, int val)
{
   struct input_event ie;

   ie.type = type;
   ie.code = code;
   ie.value = val;
   ie.time.tv_sec = 0;
   ie.time.tv_usec = 0;

   write(fd, &ie, sizeof(ie));
}

void press(int fd, int code)
{
    emit(fd, EV_KEY, code, 1);
	emit(fd, EV_SYN, SYN_REPORT, 0);
}

void release(int fd, int code)
{
    emit(fd, EV_KEY, code, 0);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}

void pressRelease(int fd, int code)
{
    press(fd, code);
    release(fd, code);
}

void typeChar(int fd, char letter)
{
    switch(letter) {

		// NUMBER ROW
	case '1':
		pressRelease(fd, 2);
		break;
	case '2':
		pressRelease(fd, 3);
		break;
	case '3':
		pressRelease(fd, 4);
		break;
	case '4':
		pressRelease(fd, 5);
		break;
	case '5':
		pressRelease(fd, 6);
		break;
	case '6':
		pressRelease(fd, 7);
		break;
	case '7':
		pressRelease(fd, 8);
		break;
	case '8':
		pressRelease(fd, 9);
		break;
	case '9':
		pressRelease(fd, 10);
		break;
	case '0':
		pressRelease(fd, 11);
		break;
	case '-':
		pressRelease(fd, 12);
		break;
	case '=':
		pressRelease(fd, 13);
		break;		
		
		// TOP ROW LETTERS
	case 'q':
		pressRelease(fd, 16);
		break;
	case 'w':
		pressRelease(fd, 17);
		break;
	case 'e':
		pressRelease(fd, 18);
		break;
	case 'r':
		pressRelease(fd, 19);
		break;
	case 't':
		pressRelease(fd, 20);
		break;
	case 'y':
		pressRelease(fd, 21);
		break;
	case 'u':
		pressRelease(fd, 22);
		break;
	case 'i':
		pressRelease(fd, 23);
		break;
	case 'o':
		pressRelease(fd, 24);
		break;
	case 'p':
		pressRelease(fd, 25);
		break;
	case '[':
		pressRelease(fd, 26);
		break;
	case ']':
		pressRelease(fd, 27);
		break;

		// MIDDLE ROW LETTERS
	case 'a':
		pressRelease(fd, 30);
		break;
	case 's':
		pressRelease(fd, 31);
		break;
	case 'd':
		pressRelease(fd, 32);
		break;
	case 'f':
		pressRelease(fd, 33);
		break;
	case 'g':
		pressRelease(fd, 34);
		break;
	case 'h':
		pressRelease(fd, 35);
		break;
	case 'j':
		pressRelease(fd, 36);
		break;
	case 'k':
		pressRelease(fd, 37);
		break;
	case 'l':
		pressRelease(fd, 38);
		break;
	case ';':
		pressRelease(fd, 39);
		break;
	case '\'':
		pressRelease(fd, 40);
		break;

		// BOTTOM ROW LETTERS
	case 'z':
		pressRelease(fd, 44);
		break;
	case 'x':
		pressRelease(fd, 45);
		break;
	case 'c':
		pressRelease(fd, 46);
		break;
	case 'v':
		pressRelease(fd, 47);
		break;
	case 'b':
		pressRelease(fd, 48);
		break;
	case 'n':
		pressRelease(fd, 49);
		break;
	case 'm':
		pressRelease(fd, 50);
		break;
	case ',':
		pressRelease(fd, 51);
		break;
	case '.':
		pressRelease(fd, 52);
		break;
	case '/':
		pressRelease(fd, 53);
		break;

		// Space and tilde
	case ' ':
		pressRelease(fd, 57);
		break;
	case '`':
		pressRelease(fd, 41);
		break;
	case '~':
		press(fd, 42);
		pressRelease(fd, 41);
		release(fd, 42);
		break;

		// SHIFT + NUMBER ROW
	case '!':
		press(fd, 42);
		pressRelease(fd, 2);
		release(fd, 42);
		break;
	case '@':
		press(fd, 42);
		pressRelease(fd, 3);
		release(fd, 42);
		break;
	case '#':
		press(fd, 42);
		pressRelease(fd, 4);
		release(fd, 42);
		break;
	case '$':
		press(fd, 42);
		pressRelease(fd, 5);
		release(fd, 42);
		break;
	case '%':
		press(fd, 42);
		pressRelease(fd, 6);
		release(fd, 42);
		break;
	case '^':
		press(fd, 42);
		pressRelease(fd, 7);
		release(fd, 42);
		break;
	case '&':
		press(fd, 42);
		pressRelease(fd, 8);
		release(fd, 42);
		break;
	case '*':
		press(fd, 42);
		pressRelease(fd, 9);
		release(fd, 42);
		break;
	case '(':
		press(fd, 42);
		pressRelease(fd, 10);
		release(fd, 42);
		break;
	case ')':
		press(fd, 42);
		pressRelease(fd, 11);
		release(fd, 42);
		break;
	case '_':
		press(fd, 42);
		pressRelease(fd, 12);
		release(fd, 42);
		break;
	case '+':
		press(fd, 42);
		pressRelease(fd, 13);
		release(fd, 42);
		break;		

		// SHIFT + TOP ROW LETTERS
	case 'Q':
		press(fd, 42);
		pressRelease(fd, 16);
		release(fd, 42);
		break;
	case 'W':
		press(fd, 42);
		pressRelease(fd, 17);
		release(fd, 42);
		break;
	case 'E':
		press(fd, 42);
		pressRelease(fd, 18);
		release(fd, 42);
		break;
	case 'R':
		press(fd, 42);
		pressRelease(fd, 19);
		release(fd, 42);
		break;
	case 'T':
		press(fd, 42);
		pressRelease(fd, 20);
		release(fd, 42);
		break;
	case 'Y':
		press(fd, 42);
		pressRelease(fd, 21);
		release(fd, 42);
		break;
	case 'U':
		press(fd, 42);
		pressRelease(fd, 22);
		release(fd, 42);
		break;
	case 'I':
		press(fd, 42);
		pressRelease(fd, 23);
		release(fd, 42);
		break;
	case 'O':
		press(fd, 42);
		pressRelease(fd, 24);
		release(fd, 42);
		break;
	case 'P':
		press(fd, 42);
		pressRelease(fd, 25);
		release(fd, 42);
		break;		
	case '{':
		press(fd, 42);
		pressRelease(fd, 26);
		release(fd, 42);
		break;
	case '}':
		press(fd, 42);
		pressRelease(fd, 27);
		release(fd, 42);
		break;
		
		// SHIFT + MIDDLE ROW LETTERS
	case 'A':
		press(fd, 42);
		pressRelease(fd, 30);
		release(fd, 42);
		break;
	case 'S':
		press(fd, 42);
		pressRelease(fd, 31);
		release(fd, 42);
		break;
	case 'D':
		press(fd, 42);
		pressRelease(fd, 32);
		release(fd, 42);
		break;
	case 'F':
		press(fd, 42);
		pressRelease(fd, 33);
		release(fd, 42);
		break;
	case 'G':
		press(fd, 42);
		pressRelease(fd, 34);
		release(fd, 42);
		break;
	case 'H':
		press(fd, 42);
		pressRelease(fd, 35);
		release(fd, 42);
		break;
	case 'J':
		press(fd, 42);
		pressRelease(fd, 36);
		release(fd, 42);
		break;
	case 'K':
		press(fd, 42);
		pressRelease(fd, 37);
		release(fd, 42);
		break;
	case 'L':
		press(fd, 42);
		pressRelease(fd, 38);
		release(fd, 42);
		break;
	case ':':
		press(fd, 42);
		pressRelease(fd, 39);
		release(fd, 42);
		break;
	case '\"':
		press(fd, 42);
		pressRelease(fd, 40);
		release(fd, 42);
		break;

		// BOTTOM ROW LETTERS
	case 'Z':
		press(fd, 42);
		pressRelease(fd, 44);
		release(fd, 42);
		break;
	case 'X':
		press(fd, 42);
		pressRelease(fd, 45);
		release(fd, 42);
		break;
	case 'C':
		press(fd, 42);
		pressRelease(fd, 46);
		release(fd, 42);
		break;
	case 'V':
		press(fd, 42);
		pressRelease(fd, 47);
		release(fd, 42);
		break;
	case 'B':
		press(fd, 42);
		pressRelease(fd, 48);
		release(fd, 42);
		break;
	case 'N':
		press(fd, 42);
		pressRelease(fd, 49);
		release(fd, 42);
		break;
	case 'M':
		press(fd, 42);
		pressRelease(fd, 50);
		release(fd, 42);
		break;
	case '<':
		press(fd, 42);
		pressRelease(fd, 51);
		release(fd, 42);
		break;
	case '>':
		press(fd, 42);
		pressRelease(fd, 52);
		release(fd, 42);
		break;
	case '?':
		press(fd, 42);
		pressRelease(fd, 53);
		release(fd, 42);
		break;

    }	
}

void typeWord(int fd, std::string word)
{
	for (int i = 0; i < word.length(); i++)
		typeChar(fd, word[i]);
}
