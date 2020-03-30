#include "EventSource.h"
#include "Event.h"
#include "../../Utilities/util/include/Dispatcher.h"


EventSource::EventSource() {
}


EventSource::~EventSource() {
}

void EventSource::run() {
  const Event* ev;
  while ( ( ev = get() ) != 0 ) {
    Dispatcher<Event>::notify( *ev );
    delete ev;
  }
  return;
}
