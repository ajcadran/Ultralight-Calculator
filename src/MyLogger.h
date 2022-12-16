#include <cstdio>

using namespace ultralight;

class MyLogger : public Logger {
public:
    MyLogger();
    virtual ~MyLogger();
    virtual void LogMessage(LogLevel log_level, const String16& message) override;
};