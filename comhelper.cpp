#include <stdio.h>
#include <iconv.h>
#include <string.h>
#include <string>
#include <algorithm>

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


char* getCmdOption(int argc,char * argv[], const std::string & option)
{
    char ** begin = argv;
    char ** end = argv + argc;
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return NULL;
}
