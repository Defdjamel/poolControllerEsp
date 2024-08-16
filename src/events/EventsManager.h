#ifndef USE_EVENTS_MANAGER_H
#define USE_EVENTS_MANAGER_H

#include <Arduino.h>
typedef void (*Handler)(byte);
struct HandlerObj
{
  Handler handler;
  bool isInit = false;
};

enum {EVENT_UPDATEWIFICONFIG, EVENT_CONNECTWIFI_OK,EVENT_CONNECTWIFI_ERROR } eventKey;

class EventsManager{
    private:
  String debugIdentifier = "[SAMPLE MANAGER] | ";
  EventsManager();
  EventsManager(const EventsManager&) = delete;
  EventsManager& operator=(const EventsManager&) = delete;

  public:
  static EventsManager& shared(); // Accessor for singleton instance
  void addHandler(Handler);  
  void callEvent(byte event);  

  private:
  HandlerObj handlersObj[20];
};


#endif
