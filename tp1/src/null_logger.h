#ifndef NULL_LOGGER_H
#define NULL_LOGGER_H

#include "logger.h"

class NullLogger : public Logger
{
public:
    NullLogger() { };
    virtual ~NullLogger() { };

    virtual void log(const CHAR* message) { };
    virtual void log(CHAR* format, ...) { };
};

#endif