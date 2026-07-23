//Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.

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
#include <unistd.h>
int main()
{	std::ifstream in_stream;
	std::ofstream out_stream;
	
	//Receive files.
	//WZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMWZMW
	if(2 == 2)
	{	std::filesystem::create_directories("saved_as_files");
		
		//Automatic enter stuff.
		struct termios old_settings, new_settings;
		tcgetattr(STDIN_FILENO, &old_settings);
		new_settings = old_settings;
		
		//Makes keyboard input be accepted automatically, as if pressing enter.
		new_settings.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
		
		//Begins.
		for(unsigned long long file_number = 1;; file_number++)
		{	//Waits for key that represents zero.
			std::cout << "\n\nReceiving file " << file_number << ", signifies zero: ";
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
			{	std::cout << "\nReceiving file " << file_number << ", byte " << byte_number << ": ";
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
