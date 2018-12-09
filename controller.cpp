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

#include "keystrokes.hpp"

// Allows the user to pick which device to read from
std::string GetPath()
{
	// Set up directory for reading
	const char* parent = "/dev/input/by-id";
	std::vector<std::string> devices;
	DIR* dir;
	struct dirent* ent;

	// Open and read directory
	if ((dir = opendir(parent)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			std::string str(ent->d_name);
			if (str != "." && str != "..")
				devices.emplace_back(str);
		}
		closedir(dir);
	} else {
		std::cout << "Couldn't read directory" << std::endl;
		exit(-1);
	}

	// List choices
	for (int i = 0; i < devices.size(); i++)
		std::cout << i << "\t" << devices[i] << std::endl;

	// Get choice
	int choice = -1;
	while (choice < 0 || choice >= devices.size())
		std::cin >> choice;

	return devices[choice];
}

int main()
{	
	// Set up new event keyboard
	struct uinput_setup usetup;
	int fd_out = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	ioctl(fd_out, UI_SET_EVBIT, EV_KEY);
	for (int i = 1; i < 127; i++)	 
		ioctl(fd_out, UI_SET_KEYBIT, i);
	memset(&usetup, 0, sizeof(usetup));
	usetup.id.bustype = BUS_USB;
	usetup.id.vendor = 0x1234;
	usetup.id.product = 0x5678;
	strcpy(usetup.name, "Macro virtual");
	ioctl(fd_out, UI_DEV_SETUP, &usetup);
	ioctl(fd_out, UI_DEV_CREATE);

	// Get path to the device as a char array
	std::string choice = "/dev/input/by-id/" + GetPath();   
	std::cout << "\nChoice:\t" << choice << std::endl;
	char path[choice.size()+1];
	strcpy(path, choice.c_str());

	// Set up for reading
	int fd = open(path, O_RDONLY);
	char* buf[256];
	struct input_event ev;
	int num;
	
	// Steal key events
	ioctl(fd, EVIOCGRAB, 1);
	while (true) {
		num = read(fd, &ev, sizeof(ev));
		if (num == (ssize_t)-1) continue;
		if (num != sizeof(ev)) break;	   
		if (ev.type == EV_KEY && ev.value == 0) {
			switch (ev.code) {
			case KEY_1:
				typeWord(fd_out, "Example text 1!");
				std::cout << std::endl;
				break;
			case KEY_2:
				typeWord(fd_out, "More examples ~\"");
				std::cout << std::endl;
				break;
			case KEY_3:
				typeWord(fd_out, "last one7*()");
				std::cout << std::endl;
				break;
			}
		}
	}

	// This is never actually reached. The user has to give an interrupt signal. Fix?
	ioctl(fd, UI_DEV_DESTROY);
	close(fd);	
	return 0;
}
