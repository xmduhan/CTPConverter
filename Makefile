IDIR =include
LIBS =lib/*.so
CC=g++
CFLAGS=-I$(IDIR) -g -std=gnu++11
LFLAGS= $(LIBS) -lzmq

all : generate compile


generate: CApiWrapper.cpp CApiWrapper.h converter.cpp converter.h CTraderHandler.cpp CTraderHandler.h


CApiWrapper.cpp : template/CApiWrapper.cpp.tpl
	python generate.py CApiWrapper.cpp.tpl


CApiWrapper.h : template/CApiWrapper.h.tpl
	python generate.py CApiWrapper.h.tpl


converter.cpp : template/converter.cpp.tpl
	python generate.py converter.cpp.tpl


converter.h : template/converter.h.tpl
	python generate.py converter.h.tpl


CTraderHandler.cpp : template/CTraderHandler.cpp.tpl
	python generate.py CTraderHandler.cpp.tpl


CTraderHandler.h : template/CTraderHandler.h.tpl
	python generate.py CTraderHandler.h.tpl


compile : CApiWrapper.o comhelper.o Configure.o converter.o CTraderHandler.o jsoncpp.o Message.o
	$(CC) *.o $(LFLAGS) -o converter


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


clean:
	touch template/*
	rm -f *.o *.orig include/*.orig *.pyc *.con *.pk converter
