//YOUR CONTROLS:
unsigned long long milliseconds_to_consume = 38; //Increase if problem. Higher = slower blinking but more reliable.



/*Run it: "apt install g++ geany libx11-dev". Open the .cpp in Geany.
Go to Build >> Set Build Commands. Where it says "Compile" and "Build", append " -lX11".
Hit F9 once. F5 to run.

Version 4.0.0
Self-healing and fully automated unidirectional network at 1B/s using
num lock & caps lock LEDs. Keep dropping files into the "send" folder.

Empty files will be deleted, not sent.*/

#include <algorithm>
#include <bitset>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
int main()
{	std::ifstream in_stream;
	std::ofstream out_stream;
	
	std::cout << "\n(1) Send files"
	          << "\n(2) Receive files"
	          << "\n\nOption: ";
	std::string o; std::getline(std::cin, o); if((o != "1") && (o != "2")) {std::cout << "\nBad option.\n"; return 0;}
	
	//Send files.
	//WZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMW
	if(o == "1")
	{	std::filesystem::create_directories("send");
		std::cout << "\n";
		Display* dpy = XOpenDisplay(nullptr); if(!dpy) {return 1;}
		const unsigned int CAPS_MASK = LockMask;
		const unsigned int NUM_MASK = Mod2Mask;
		
		//Turns off Num Lock and Caps Lock.
		XkbLockModifiers(dpy, XkbUseCoreKbd, CAPS_MASK | NUM_MASK, 0); XSync(dpy, False);
		
		//Begins.
		for(unsigned long long files_sent = 0;; files_sent++)
		{	//Waits for files in folder "send".
			std::cout << files_sent << " files sent. Keep dropping files in folder \"send\"...\n";
			std::string path_to_any_first_file;
			for(;;)
			{	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
				
				//Gets list of ALL files from a folder.
				std::vector <std::string> file_list;
				for(const auto& entry : std::filesystem::recursive_directory_iterator("send"))
				{	if(entry.is_regular_file()) {file_list.push_back(entry.path().lexically_relative("send").string());} //Loads list of files to RAM as relative paths.
				}
				std::sort(file_list.begin(), file_list.end()); //Sorts list of files in RAM.
				
				//Deletes file if empty.
				if(!file_list.empty())
				{	path_to_any_first_file = "send/" + file_list[0];
					if(std::filesystem::file_size(path_to_any_first_file) == 0) {std::filesystem::remove_all(path_to_any_first_file);}
					else {break;}
				}
			}
			
			//Sends bit 0. (Signifies which blink is 0).
			XkbLockModifiers(dpy, XkbUseCoreKbd, NUM_MASK, NUM_MASK); XSync(dpy, False); //Num Lock on.
			std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_consume));
			XkbLockModifiers(dpy, XkbUseCoreKbd, NUM_MASK, 0); XSync(dpy, False); //Num Lock off.
			std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_consume));
			
			//Sends file.
			in_stream.open(path_to_any_first_file); if(!in_stream) {std::cout << "\nCan't open file for reading. (Sends file).\n"; return 1;}
			for(char file_byte; in_stream.get(file_byte);)
			{	if(in_stream.peek() == EOF)
				{	//Sends bit 1. (Signifies it's the last byte).
					XkbLockModifiers(dpy, XkbUseCoreKbd, CAPS_MASK, CAPS_MASK); XSync(dpy, False); //Caps Lock on.
					std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_consume));
					XkbLockModifiers(dpy, XkbUseCoreKbd, CAPS_MASK, 0); XSync(dpy, False); //Caps Lock off.
					std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_consume));
				}
				else
				{	//Sends bit 0. (Signifies it's not the last byte).
					XkbLockModifiers(dpy, XkbUseCoreKbd, NUM_MASK, NUM_MASK); XSync(dpy, False); //Num Lock on.
					std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_consume));
					XkbLockModifiers(dpy, XkbUseCoreKbd, NUM_MASK, 0); XSync(dpy, False); //Num Lock off.
					std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_consume));
				}
				
				//Sends byte.
				std::bitset <8> bits(file_byte);
				for(int a = 7; a >= 0; a--)
				{	if(bits[a] == 0)
					{	//Sends bit 0.
						XkbLockModifiers(dpy, XkbUseCoreKbd, NUM_MASK, NUM_MASK); XSync(dpy, False); //Num Lock on.
						std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_consume));
						XkbLockModifiers(dpy, XkbUseCoreKbd, NUM_MASK, 0); XSync(dpy, False); //Num Lock off.
						std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_consume));
					}
					else
					{	//Sends bit 1.
						XkbLockModifiers(dpy, XkbUseCoreKbd, CAPS_MASK, CAPS_MASK); XSync(dpy, False); //Caps Lock on.
						std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_consume));
						XkbLockModifiers(dpy, XkbUseCoreKbd, CAPS_MASK, 0); XSync(dpy, False); //Caps Lock off.
						std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_consume));
					}
				}
			}
			in_stream.close();
			std::filesystem::remove_all(path_to_any_first_file);
		}
	}
	
	//Receive files.
	//WZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMW
	if(o == "2")
	{	std::filesystem::create_directories("saved_as_files");
		struct termios old_settings, new_settings;
		tcgetattr(STDIN_FILENO, &old_settings);
		new_settings = old_settings;
		
		new_settings.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
		
		//Begins.
		for(unsigned long long file_number = 1;; file_number++)
		{	//Waits for key that represents zero.
			std::cout << "\n\nreceiving file " << file_number << ", signifies zero: ";
			char c; if(std::cin.get(c)) {std::cout << c;}
			char key_representing_zero = c;
			
			//Creates file name like "2026_07_31_20:34:55".
			std::string date;
			auto now = std::chrono::system_clock::now();
			std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
			std::tm localTime; localtime_r(&currentTime, &localTime);
			std::ostringstream oss; oss << std::put_time(&localTime, "%Y_%m_%d_%H:%M:%S"); date = oss.str();
			std::string new_file_name = "saved_as_files/" + date;
			
			//Waits for 9 keys.
			out_stream.open(new_file_name); if(!out_stream) {std::cout << "\nCan't open file for writing. (Creates file).\n"; return 1;}
			for(unsigned long long byte_number = 1;; byte_number++)
			{	std::cout << "\nreceiving file " << file_number << ", byte " << byte_number << ": ";
				std::string typed_characters;
				for(int a = 0; a < 9; a++)
				{	char c; if(std::cin.get(c)) {typed_characters += c; std::cout << c;}
				}
				
				//Writes byte.
				std::string eight_bits = typed_characters.substr(1);
				for(int a = 0; a < 8; a++)
				{	if(eight_bits[a] == key_representing_zero) {eight_bits[a] = '0';}
					else                                       {eight_bits[a] = '1';}
				}
				int raw_byte = std::bitset <8> (eight_bits).to_ulong();
				out_stream.put(raw_byte);
				
				//Breaks out if last byte.
				if(typed_characters[0] != key_representing_zero) {break;}
			}
			out_stream.close();
			
			//Copies file to file "saved_as_text" where it's only the 97 standard text bytes (9, 10, and 32-126).
			in_stream.open(new_file_name);                   if( !in_stream) {std::cout << "\nCan't open file for reading. (saved_as_text).\n"; return 1;}
			out_stream.open("saved_as_text", std::ios::app); if(!out_stream) {std::cout << "\nCan't open file for writing. (saved_as_text).\n"; return 1;}
			out_stream << date << "\n";
			for(char file_byte; in_stream.get(file_byte);)
			{	     if((file_byte > 31) && (file_byte < 127)) {out_stream.put(file_byte);}
				else if((file_byte == 9) || (file_byte == 10)) {out_stream.put(file_byte);}
			}
			out_stream << "\n";
			in_stream.close();
			out_stream.close();
			
			//Copies file to file "saved_as_lines" where it's only the 97 standard text bytes (9, 10, and 32-126).
			in_stream.open(new_file_name);                    if( !in_stream) {std::cout << "\nCan't open file for reading. (saved_as_lines).\n"; return 1;}
			out_stream.open("saved_as_lines", std::ios::app); if(!out_stream) {std::cout << "\nCan't open file for writing. (saved_as_lines).\n"; return 1;}
			out_stream << date << " ";
			for(char file_byte; in_stream.get(file_byte);)
			{	     if (file_byte ==   9)  {out_stream << " \\t ";    }
				else if (file_byte ==  10)  {out_stream << " \\n ";    }
				else if((file_byte  >  31)
				     && (file_byte  < 127)) {out_stream.put(file_byte);}
			}
			out_stream << "\n";
			in_stream.close();
			out_stream.close();
		}
	}
}
