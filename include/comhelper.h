#pragma once
#include <string>
#include <algorithm>
#include <stdio.h>
#include <iconv.h>
#include <string.h>

template <typename X, typename A>
inline void Assert(A assertion)
{
    if( !assertion ) throw X();
}


class CommandOption{
public:
    CommandOption(int argc,char ** argv);
    bool exists(const std::string & option);
    char * get(const std::string & option);

private:
    int argc;
    char ** argv;
};


void codeConvert(char * from,char * to,char * src,char * dst,size_t dstSize);
void gbk2utf8(char * src,char * dst,size_t dstSize);
bool fileExists (const std::string& name);
bool stringStartsWith(std::string str,std::string key);
std::string fileReadAll(const std::string& name);
