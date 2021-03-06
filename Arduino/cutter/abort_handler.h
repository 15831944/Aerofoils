#ifndef ABORT_HANDLER_H
#define ABORT_HANDLER_H

#include "command_handler.h"

class CommandQueue;
class Fifo;
class Hardware;
class Operation;

// * Z - abort
struct abortT : public commandT{
};

/*
 * CommandHandler to run the Abort command - stop everything.
 */
class AbortHandler : public CommandHandler {
private:
  CommandQueue* _commands;
  Fifo* _fifo;
  Hardware* _hardware;
  Operation** _currentOperation;

public:
  AbortHandler(CommandQueue* commands, Fifo* fifo, Hardware* hardware, Operation** currentOperation);
  virtual size_t getMessageSize() { return sizeof(abortT); }
  virtual bool parseInto(char* msg, byte* buffer);
  virtual Operation* process(byte* msg);
  virtual char* getDescription();

};


#endif
