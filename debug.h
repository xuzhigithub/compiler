#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#define DEBUG
//#define DEBUG_W

#ifdef DEBUG

#define debug_printf(format, arg...)              \
           printf(format, ## arg)

#define debug_fprintf(format, arg...)              \
           fprintf(format, ## arg)

#else

#define debug_printf(format, arg...) do {  } while (0)

#define debug_fprintf(format,arg...) do{  }while(0)

#endif

#ifdef DEBUG_W

#define debug_wprintf(format, arg...)              \
           printf(format, ## arg)
#else
#define debug_wprintf(format, arg...) do {  } while (0)

#endif

#endif // DEBUG_H_INCLUDED
