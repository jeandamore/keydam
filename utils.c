#include <stdlib.h>
#include <sys/time.h>
#include "utils.h"

char* convertCfstringToString(CFStringRef aString) 
{
  if (aString == NULL) {
    return NULL;
  }

  CFIndex length = CFStringGetLength(aString);
  CFIndex maxSize =
  CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8) + 1;
  char *buffer = (char *)malloc(maxSize);
  if (CFStringGetCString(aString, buffer, maxSize,
                         kCFStringEncodingUTF8)) {
    return buffer;
  }
  return NULL;
}


void sysTimeAsString(char* timeString) 
{
  time_t timer;
  struct tm* tm_info;

  time(&timer);
  tm_info = localtime(&timer);

	strftime (timeString, 100, "%Y%m%d%H%M%S", tm_info);
}

long sysTimeInMillis() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return ms;
}

int randomValue(int min, int max) 
{
  return min + (rand() % (max-min));
}