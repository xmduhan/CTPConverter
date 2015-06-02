#include <comhelper.h>
#include <string>
#include <iostream>

int main(int argc, char * argv []){
    CommandOption commandOption(argc,argv);
    if( commandOption.exists("-v") ) {
        std::cout << "-v is in Command Option" << std::endl;
    }
    return 0;
}
