IDIR =include
LIBS =lib/*.so
CC=g++
LD=g++
CFLAGS=-I$(IDIR) -g -std=gnu++11
LFLAGS= $(LIBS) -lzmq


all : generate compile


generate: CApiWrapper.cpp include/CApiWrapper.h converter.cpp include/converter.h \
	CTraderHandler.cpp include/CTraderHandler.h test/channel.py test/CTPStruct.py


CApiWrapper.cpp : template/CApiWrapper.cpp.tpl
	python generate.py CApiWrapper.cpp.tpl


include/CApiWrapper.h : template/CApiWrapper.h.tpl
	python generate.py CApiWrapper.h.tpl include


converter.cpp : template/converter.cpp.tpl
	python generate.py converter.cpp.tpl


include/converter.h : template/converter.h.tpl
	python generate.py converter.h.tpl include


CTraderHandler.cpp : template/CTraderHandler.cpp.tpl
	python generate.py CTraderHandler.cpp.tpl


include/CTraderHandler.h : template/CTraderHandler.h.tpl
	python generate.py CTraderHandler.h.tpl include


test/channel.py : template/channel.py.tpl
	python generate.py channel.py.tpl test


test/CTPStruct.py : template/CTPStruct.py.tpl
	python generate.py CTPStruct.py.tpl test


compile : CApiWrapper.o comhelper.o Configure.o converter.o CTraderHandler.o jsoncpp.o Message.o
	$(LD) *.o $(LFLAGS) -o converter


CApiWrapper.o : CApiWrapper.cpp include/*.h
	$(CC) -c CApiWrapper.cpp $(CFLAGS)


comhelper.o : comhelper.cpp include/*.h
	$(CC) -c comhelper.cpp $(CFLAGS)


Configure.o : Configure.cpp include/*.h
	$(CC) -c Configure.cpp $(CFLAGS)


converter.o : converter.cpp include/*.h
	$(CC) -c converter.cpp $(CFLAGS)


CTraderHandler.o : CTraderHandler.cpp include/*.h
	$(CC) -c CTraderHandler.cpp $(CFLAGS)


jsoncpp.o : jsoncpp.cpp include/*.h
	$(CC) -c jsoncpp.cpp $(CFLAGS)


Message.o : Message.cpp include/*.h
	$(CC) -c Message.cpp $(CFLAGS)


clean :
	touch template/*
	rm -f *.o *.orig include/*.orig *.pyc *.con *.pk converter
