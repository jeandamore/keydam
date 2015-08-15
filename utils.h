#include <stdio.h>
#import <ApplicationServices/ApplicationServices.h>

char* convertCfstringToString(CFStringRef aString);
void sysTimeAsString(char* timeString);
long sysTimeInMillis();
int randomValue(int min, int max);
