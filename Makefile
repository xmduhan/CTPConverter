IDIR =include
LIBS =lib/*.so
CC=g++
LD=g++
CFLAGS=-I$(IDIR) -g -std=gnu++11
LFLAGS= $(LIBS) -lzmq


all : generate bin/trader bin/md bin/test


generate: CTraderWrapper.cpp include/CTraderWrapper.h trader.cpp include/trader.h \
	CTraderHandler.cpp include/CTraderHandler.h test/channel.py test/CTPStruct.py \
	test/examples.py test/query_api_tests.py CMdHandler.cpp include/CMdHandler.h


CTraderWrapper.cpp : template/CTraderWrapper.cpp.tpl
	python generate.py CTraderWrapper.cpp.tpl


include/CTraderWrapper.h : template/CTraderWrapper.h.tpl
	python generate.py CTraderWrapper.h.tpl include


trader.cpp : template/trader.cpp.tpl
	python generate.py trader.cpp.tpl


include/trader.h : template/trader.h.tpl
	python generate.py trader.h.tpl include


CTraderHandler.cpp : template/CTraderHandler.cpp.tpl
	python generate.py CTraderHandler.cpp.tpl


include/CTraderHandler.h : template/CTraderHandler.h.tpl
	python generate.py CTraderHandler.h.tpl include


CMdHandler.cpp : template/CMdHandler.cpp.tpl
	python generate.py CMdHandler.cpp.tpl


include/CMdHandler.h : template/CMdHandler.h.tpl
	python generate.py CMdHandler.h.tpl include


test/channel.py : template/channel.py.tpl
	python generate.py channel.py.tpl test


test/CTPStruct.py : template/CTPStruct.py.tpl
	python generate.py CTPStruct.py.tpl test


test/examples.py : template/examples.py.tpl
	python generate.py examples.py.tpl test


test/query_api_tests.py : template/query_api_tests.py.tpl
	python generate.py query_api_tests.py.tpl test


bin/trader : trader.o CTraderWrapper.o comhelper.o Configure.o CTraderHandler.o jsoncpp.o Message.o
	$(LD) trader.o CTraderWrapper.o comhelper.o Configure.o  CTraderHandler.o \
	jsoncpp.o Message.o $(LFLAGS) -o bin/trader


bin/md : md.o comhelper.o Configure.o jsoncpp.o Message.o CMdHandler.o
	$(LD) md.o comhelper.o Configure.o jsoncpp.o Message.o CMdHandler.o $(LFLAGS) -o bin/md


bin/test : test.o CTraderWrapper.o comhelper.o Configure.o CTraderHandler.o jsoncpp.o Message.o
	$(LD) test.o CTraderWrapper.o comhelper.o Configure.o CTraderHandler.o \
	jsoncpp.o Message.o $(LFLAGS) -o bin/test


CTraderWrapper.o : CTraderWrapper.cpp include/*.h
	$(CC) -c CTraderWrapper.cpp $(CFLAGS)


comhelper.o : comhelper.cpp include/*.h
	$(CC) -c comhelper.cpp $(CFLAGS)


Configure.o : Configure.cpp include/*.h
	$(CC) -c Configure.cpp $(CFLAGS)


trader.o : trader.cpp include/*.h
	$(CC) -c trader.cpp $(CFLAGS)


CTraderHandler.o : CTraderHandler.cpp include/*.h
	$(CC) -c CTraderHandler.cpp $(CFLAGS)


jsoncpp.o : jsoncpp.cpp include/*.h
	$(CC) -c jsoncpp.cpp $(CFLAGS)


Message.o : Message.cpp include/*.h
	$(CC) -c Message.cpp $(CFLAGS)


CMdHandler.o : CMdHandler.cpp include/*.h
	$(CC) -c CMdHandler.cpp $(CFLAGS)


test.o : test.cpp include/*.h
	$(CC) -c test.cpp $(CFLAGS)


md.o : md.cpp include/*.h
	$(CC) -c md.cpp $(CFLAGS)


clean :
	touch template/*
	rm -f *.o *.orig include/*.orig *.pyc *.con *.pk bin/trader bin/md bin/test
