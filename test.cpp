#include <comhelper.h>
#include <string>
#include <iostream>



int main(int argc, char * argv []){

    char * filename = (char *)"/tmp/config.json";
    if (fileExists(filename)){
        std::cout << "file exists" << std::endl;
        std::cout << "file content=" << fileReadAll(filename) << std::endl;
    }else{
        std::cout << "file not found" << std::endl;
    }

}
