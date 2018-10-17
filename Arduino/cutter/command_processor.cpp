#include "command_processor.h"
#include "command_handler.h"
#include "command_queue.h"

CommandProcessor::CommandProcessor(CommandQueue* queue) {
  _commandQueue = queue;
}

bool CommandProcessor::process(char* message, int nBytes){

  
  bool ok = false;
  if(nBytes > 0) {


    // Look for any imediate commands
    switch(*message){

    case '?':
      showCommands();
      ok = true;
      break;
      
    case 'P':   // ping, will let host know queue state, otherwise no op.
      ok = true;
      break;

    default: 
      CommandHandler* handler = CommandHandler::find(*message);
      if(handler == 0) {
        return false;  // no valid handler
      }
      ok = handler->parseInto(message, _commandQueue->addCommand(handler->getMessageSize()));
      break;
    }
  }
  return ok;
  
}

void CommandProcessor::showCommands(){
  Serial.println("? - show this message");
  Serial.println("P - ping, show queue state");
  for(int i=0; i<CommandHandler::getCount(); ++i){
    CommandHandler* handler = CommandHandler::lookup(i);
    Serial.print(handler->getCommandChar());
    Serial.print(" - ");
    Serial.println(handler->getDescription());
  }
}

