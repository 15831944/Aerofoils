#include "operation.h"
#include "hardware.h"
#include "command_processor.h"
#include "command_queue.h"
#include "fifo.h"
#include "steppers.h"
#include "home.h"
#include "idle.h"

#include "command_handler.h"
#include "step_handler.h"
#include "line_handler.h"
#include "home_handler.h"
#include "enable_handler.h"
#include "disable_handler.h"
#include "wireon_handler.h"
#include "wireoff_handler.h"
#include "abort_handler.h"

char hexDigits[] = "0123456789ABCDEF";

// Comms
char inputBuffer[80];
char outputBuffer[80];

IntervalTimer tickTimer;
Hardware hardware;
CommandQueue commandQueue;
Fifo fifo;

// Main operations
Steppers steppers(&fifo);
Home home(&fifo, &hardware);
Idle idle;
Operation* currentOperation = &idle; 

CommandProcessor commandProcessor(&commandQueue, &fifo, &currentOperation);

// Commands
StepHandler stepHandler(&hardware);
LineHandler lineHandler(&steppers);
HomeHandler homeHandler(&home);
EnableHandler enableHandler(&hardware);
DisableHandler disableHandler(&hardware);
WireOnHandler wireOnHandler(&hardware);
WireOffHandler wireOffHandler(&hardware);
AbortHandler abortHandler(&commandQueue, &fifo, &hardware, &currentOperation);

// Interrupt timer
void timerTick() {
  if(!fifo.isEmpty()) {
    byte val = fifo.get();
    hardware.step(val);
  }
}

void setup() {


  Serial.begin(9600); // USB is always 12 Mbit/sec
  
  CommandHandler::registerHandler(&abortHandler); // always put abort as 0 as called for illegal command.
  CommandHandler::registerHandler(&stepHandler);
  CommandHandler::registerHandler(&lineHandler);
  CommandHandler::registerHandler(&homeHandler);
  CommandHandler::registerHandler(&enableHandler);
  CommandHandler::registerHandler(&disableHandler);
  CommandHandler::registerHandler(&wireOnHandler);
  CommandHandler::registerHandler(&wireOffHandler);

  currentOperation = &idle;

  // Time between hardware pulses.  Not reliable at 5kHz (200uS) especially Nema23 motors
  // Better at 250uS but still misses on reverses
  // Reliable at 2khz (500uS).
  tickTimer.begin(timerTick, 400); 
 }

void loop() {
  int available = Serial.available();
  if (available > 0) {
    int n = Serial.readBytes((char *)inputBuffer, available);
    bool ok = commandProcessor.process((char*)inputBuffer, n);
    outputBuffer[0] = ok ? 'Y' : 'N';
    outputBuffer[1] = commandQueue.isFull() ? 'F' : '-';
    outputBuffer[2] = commandQueue.isEmpty() ? 'E' : '-';
    outputBuffer[3] = hexDigits[hardware.getLimits() & 0x0F];
    outputBuffer[4] = 0;
    Serial.println(outputBuffer);
  }

    hardware.enableStatusLed( commandQueue.isFull());

//  if(currentOperation != &idle){
//    Serial.println(currentOperation->name());
//  }
  
  if(currentOperation->isRunning() ) {
    if(!fifo.isFull()) {
      currentOperation->step();
    }
  } else {
    //Serial.println("Stopped");
    currentOperation = &idle; 
    if(!commandQueue.isEmpty()) {
      Operation* nextOp = commandQueue.processNextCommand();
      if(nextOp != 0) {
        currentOperation = nextOp;
      }
    }
  }
    
 //  hardware.enableStatusLed( !(fifo.isEmpty() && commandQueue.isEmpty()));
}
