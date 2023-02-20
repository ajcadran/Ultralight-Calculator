#include "MyLogger.h"

// Define our custom Logger class


MyLogger() {}
virtual ~MyLogger() {}

///
/// Called when the library wants to print a message to the log.
///
virtual void LogMessage(LogLevel log_level, const String16& message) override {
  printf("%s\n", String(message).utf8().data());
}
