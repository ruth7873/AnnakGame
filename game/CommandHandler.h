#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Command.h"
#include "WorldMap.h"
using namespace std;

struct Handler
{
	void (*handler)(shared_ptr<Command> command);
};

class CommandHandler
{
public:
	static unordered_map<string, Handler> commandHandlerTable;

	CommandHandler();
	static void select(shared_ptr<Command> c);
	static void work(shared_ptr<Command> c);
	static void wait(shared_ptr<Command>c);
	static void rain(shared_ptr<Command> c);
	static void resource(shared_ptr<Command> c);
	static void people(shared_ptr<Command> c);
	static void build(shared_ptr<Command> c);
	static void move(shared_ptr<Command> c);
	static void makeEmpty(shared_ptr<Command> c);
	static void manufacture(shared_ptr<Command> c);
	static void deposit(shared_ptr<Command>c);
	static void takeResources(shared_ptr<Command>c);
	static void resources(shared_ptr<Command> c);
};