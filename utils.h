#include <stdio.h>
#import <ApplicationServices/ApplicationServices.h>

char* convertCfstringToString(CFStringRef aString);
void sysTimeString(char* timeString);
long sysTimeInMillis();