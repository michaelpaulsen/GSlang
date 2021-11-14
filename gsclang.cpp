/**
DeadHamster  https://discord.gg/Ad8W2a5a9k
RAM in the N64 is 8MB, which at most will go up to 6 bytes. a typical Integer value is 8 bytes
This leaves a single byte which we can use somewhat freely in keeping with a nice, 32bit data value
80 XXXXXX YYYY is the code structure
or 81 XXXXXX YYYY
80 codes will replace 1 single byte at the address XXXXXX with the value 00YY
81 codes will replace 2 bytes at XXXXXX with the value YYYY
there are some other codes which will check the current value, and if it equals YYYY will continue to execute code. These can be used as "IF" statements to check when to run a code

*/
#include <iostream> 

int main(int argc,char** argv){ 
	for(int x = 1; x < argc; x++){  
		std::cout << argv[x]<<'\n'; 
	}	
} 
