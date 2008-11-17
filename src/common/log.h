#ifndef LOG_H
#define LOG_H

typedef enum { LOG_LEVEL_DEBUG, LOG_LEVEL_ERROR, LOG_LEVEL_NONE } log_level;

void LOG_ERROR( const char * module_name, const char * message );
void LOG_DEBUG( const char * module_name, const char * message );
void LOG_SET_LEVEL( log_level level );

#endif
