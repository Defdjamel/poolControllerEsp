#include "EventsManager.h"
#include <misc/lv_log.h>

EventsManager::EventsManager() {
  // Initialization code, if needed
}

void  EventsManager::callEvent(byte event){
   LV_LOG_USER("callEvent %d",event);
    //dispath to all handler
    // for(int i =0 ; i< sizeof( handlers);i++){
    int count = 0;
    for (HandlerObj handlerobj : handlersObj) {
  // code block to be executed

      // Handler handler = handlers[i];

      if(handlerobj.isInit == true){
         handlerobj.handler(event);
        count++;

      }
    
      
    }
 LV_LOG_USER("callEvent count %d",count);

}
 void EventsManager::addHandler(Handler _handler){
   LV_LOG_USER("event addHandler  ");
  for(int i = 0; i < 10; i++) {
  // for (HandlerObj handlerobj : handlersObj) {
   HandlerObj handlerobj = handlersObj[i];
     if(handlerobj.isInit == false){
      
      HandlerObj newhandlerobj = HandlerObj();
      newhandlerobj.handler = _handler;
      newhandlerobj.isInit = true;
       handlersObj[i] = newhandlerobj;
       break;

     }

  }

 }

EventsManager& EventsManager::shared() {
  static EventsManager instance;
  return instance;
}
