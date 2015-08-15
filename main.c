#include <stdio.h>
#include <time.h>
#import <ApplicationServices/ApplicationServices.h>
#include "utils.h"

int verboseFlag = 0;
int randomiseFlag = 0;
FILE *file = NULL;

CGEventRef loggingEventTapCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) 
{
  	if(verboseFlag == 1) 
  	{
  		printf("%u,%llx,%ld\n", (uint32_t)type,CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode), sysTimeInMillis());
  	}
    fprintf(file, "%u,%llx,%ld\n", (uint32_t)type,CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode), sysTimeInMillis());
    fflush(file);
 	return event; 
}

void waitAndPostEvent(const useconds_t waitTimeInMicroSeconds, CGEventTapProxy proxy, CGEventRef event) 
{
	usleep(waitTimeInMicroSeconds);
	CGEventTapPostEvent(proxy, event);
}


CGEventRef randomisingFlagEventTapCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) 
{
	if(randomiseFlag ==1)
	{
		waitAndPostEvent(randomValue(10, 100)*1000, proxy, event);
		return NULL; 
	}
	return event;
}


CFMachPortRef registerEventTap(CGEventTapCallBack eventTapCallback)
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
	CFMachPortRef eventTap =  CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, mask, eventTapCallback, NULL);
	CGEventTapEnable(eventTap, true);
	return eventTap;
}


void listenToKeyBoardEvents(CFMachPortRef eventTaps[]) 
{
 	CFRunLoopSourceRef runLoopSource;
 	int i, length = sizeof(*eventTaps)/sizeof(int);
 	for(i = 0; i<sizeof(*eventTaps)/sizeof(int); ++i)
 	{
 		/* To listen for messages you need to create a run loop source */
		runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTaps[i], 0);
		/* Adds a CFRunLoopSource object to a run loop mode. */
		CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
 	}
	CFRunLoopRun();
	
}

int readFlags(int argc, char* const* argv) 
{
	int c;
	while ((c = getopt (argc, argv, "rv")) != -1)
    	switch (c)
    	{
       		case 'r':
       			printf ("Will turn radomise ON\n");
         		randomiseFlag = 1;
         		break;
       		case 'v':
       			printf ("Will turn verbose ON\n");
         		verboseFlag = 1;
         		break;
       		case '?':
         		if (isprint (optopt))
         		{
           			printf ("Unknown option `-%c'. Usage: main.exe <-rv>\n", optopt);
       			}
         		else
         		{
           			printf ("Unknown option character `\\x%x'. Usage: main.exe <-rv>\n", optopt);
       			}
         		return 1;
       		default:
       			printf ("Usage: main.exe <-rv>\n");
         		return 2;
        }

	return 0;
}

FILE* openOutputFile() {

	char dateTimeString[14];
	char fileName[256];

	sysTimeAsString(dateTimeString);
	snprintf(fileName, sizeof fileName, "%s%s%s", "keydam-", dateTimeString, ".csv");
	return fopen(fileName, "a");
}


int main (int argc, char* const* argv) 
{
	int rcode = readFlags(argc, argv);
	if(rcode != 0 ) {
		return 1;
	}
	else 
	{	
		file = openOutputFile();
		CFMachPortRef eventTaps[2];
		eventTaps[0] = registerEventTap(loggingEventTapCallback);
		eventTaps[1] = registerEventTap(randomisingFlagEventTapCallback);
		listenToKeyBoardEvents(eventTaps);
		fclose(file);
		return 0;
	}
}


