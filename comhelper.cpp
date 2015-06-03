#include <comhelper.h>
#include <fstream>
#include <streambuf>


void codeConvert(char * from,char * to,char * src,char * dst,size_t dstSize){
	size_t sl,dl;
	sl = strlen(src);
	dl = dstSize;
	char * pIn = src;
    char * pOut = dst;
	memset(dst,'\0',dstSize);
	iconv_t conv = iconv_open(to,from);
	iconv(conv, &pIn, &sl, &pOut, &dl);
	iconv_close(conv);
}


void gbk2utf8(char * src,char * dst,size_t dstSize){
	char * gbk = (char*)"GBK";
	char * utf8 = (char*)"UTF-8";
	codeConvert(gbk,utf8,src,dst,dstSize);
}


bool fileExists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}


std::string fileReadAll(const std::string& name){
	std::ifstream f(name);
	std::string content((std::istreambuf_iterator<char>(f)),
	                 std::istreambuf_iterator<char>());
	return content;
}


CommandOption::CommandOption(int argc,char * argv[]){
	this->argc = argc;
	this->argv = argv;
}

bool CommandOption::exists(const std::string & option){
	char ** begin = argv;
    char ** end = argv + argc;
	return std::find(begin, end, option) != end;
	return 0;
}

char * CommandOption::get(const std::string & option){
	char ** begin = argv;
	char ** end = argv + argc;
	char ** itr = std::find(begin, end, option);
	if (itr != end && ++itr != end) {
		return *itr;
	}
	return NULL;
}
