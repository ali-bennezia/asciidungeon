#ifndef _CONF_H_
#define _CONF_H_

#if defined (_WIN32) || defined (_WIN64) || defined (__CYGWIN__)
#define WINMODE
#elif defined (linux) || defined (__linux) || defined(__linux__)
#define LINMODE
#elif
#error "Operating system not supported."
#endif

#endif
