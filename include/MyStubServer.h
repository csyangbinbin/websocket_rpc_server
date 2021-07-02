#ifndef __MY_STUB_SERVER_INCLUDE__
#define __MY_STUB_SERVER_INCLUDE__
#include <iostream>

#include "include/abstractstubserver.h"
#include <stdio.h>

using namespace jsonrpc;
using namespace std;

class MyStubServer : public AbstractStubServer {
public:
	MyStubServer(AbstractServerConnector& connector, serverVersion_t type);

	virtual void notifyServer();
	virtual std::string sayHello(const std::string& name);
	virtual int addNumbers(int param1, int param2);
	virtual double addNumbers2(double param1, double param2);
	virtual Json::Value calculate(const Json::Value& args);
	virtual bool isEqual(const std::string& str1, const std::string& str2);
	virtual Json::Value buildObject(const std::string& name, int age);
	virtual std::string methodWithoutParameters();
};
#endif
