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
#include <memory>
#include <cstdio>
#include <stdlib.h>

//#define DEBUG 
size_t str_len( const char* str){ 
	// this is size_t because in theroy we could have a string that is longer than maxint 
	// so to be c++ compliant we need to use type_t 
	// because if it is larger than maxType_T then it is malformed c++ by defintion
	/// TODO replace with the cstring header's implementation; 
	/// cant ringht now don't have internet 
	size_t x = 0;  
	while(str[x] != 0){ 
		x++; 
	}
	return ++x; 
}
char* getFileNameFromPath( const char* filePath){ 
	///TODO move this to my skelelib 
	/// takes a folder path as input and returns the file name or the bottom level folder
	char* tempFileName = static_cast<char*>(calloc(str_len(filePath)*sizeof(char),0)); 
	//fills the memory at the adress returned with 0s
	//then staticly cast that to a char pointer
	//you could use new here. 
	size_t size = 0; 
	size_t z = 0; 
#ifdef DEBUG 
	std::cout<<'\n'<< filePath << '\n';
#endif
	if(str_len(filePath)-1 <= 0){ 
		// is the string empty could also check if the first char is 0	
		return nullptr; 
	}
	size_t x = str_len(filePath)-1; 
	while(x--){ 
		if(x > str_len(filePath)-2 || filePath[x] == 0)break;
		/// we subtract one because arrays are 0 based
		// then we subtract one beccause we don't want to set the first char to 0
		//(c strings always end in a null charictar)
		//std::cout<<filePath[x];   	
		if(filePath[x] == '/' || filePath[x] == '\\')break; 	
		tempFileName[z] = filePath[x]; 
#ifdef DEBUG 
		std::cout<<' '<<filePath[x] << ' '; 
#endif
		z++; 
		size += sizeof(char); // should always be 1 but this is more verbose 	
	}	
	 
	char* fileName = static_cast<char*>(calloc(size+1,0));
	//we need to add the one here becuase we removed it when we were 
	//looping though the string the first time
	//create the temp var because it is reversed so I need to 
	//un reverse it. 
	//I create this after writing to the 			
	z = 0; 			
	for(size_t x = size-1; x >= 0; x--){
		if(x > size){ 
			break; 
		}
		fileName[z] = tempFileName[x];
#ifdef DEBUG 
		std::cout<< 'x' << tempFileName[x] << 'z' << fileName[z];
#endif
		z++;
		 	
	}
	free(tempFileName); 
	return fileName; 
}
int main(int argc,char** argv){ 
	if(argc == 2){ 
		auto file = fopen(argv[1],"r");	
		/// TODO Change to fopen_s
		if (file == nullptr){
			printf(" \n->usage %s <file name> [delimiter]\n",
					getFileNameFromPath(argv[0])
			); 
			printf("use to open <file name>");
		        printf("compile its instructions to gameshark codes\n");
			printf("ERROR: un able to open file %s", argv[1]);
			return EXIT_FAILURE;
		}
		char* ln = static_cast<char*>(calloc(1000000*sizeof(char),0));
		while (!feof(file)) {
			ln = fgets(ln, 1000000, file);
			printf("%s", ln);
		}	
	}else{ 
		printf("use : %s [path]\n", getFileNameFromPath(argv[0]));
	       	printf("compiles the file at [path] into gameshark codes");  
		return EXIT_FAILURE; 
	}
	return 1; 
} 
