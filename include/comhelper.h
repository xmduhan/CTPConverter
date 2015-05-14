#pragma once

template <typename X, typename A>
inline void Assert(A assertion)
{
    if( !assertion ) throw X();
}


void codeConvert(char * from,char * to,char * src,char * dst,size_t dstSize);
void gbk2utf8(char * src,char * dst,size_t dstSize);
