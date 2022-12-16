#include <AppCore/AppCore.h>
#include <AppCore/JSHelpers.h>
#include <JavaScriptCore/JSValueRef.h>
#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSStringRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <cstdio>
#include <string>
#include <type_traits>
#include <sstream>
#include <cwchar>

using namespace ultralight;

class MathHandler
{
private:
    ultralight::View *caller_;
    float runningTotal;
    std::wstring buffer;
    char previousOperator;

public:
    MathHandler();
    JSValueRef onButtonClick(const JSObject& thisObject, const JSArgs& args, ultralight::View *caller);
    void handleSymbol(const JSChar* symbol);
    void handleNumber(const JSChar* number);
    void printDebugMsg(const JSChar* msg);
    bool isNotNumber(const std::wstring wstr);
    //const char* wstringToChar(const std::wstring wstr);

    // Getters and Setters
    float getRunningTotal() const;
    void setRunningTotal(float t);
    std::wstring getBuffer() const;
    void setBuffer(std::wstring b);
    char getPreviousOperator() const;
    void setPreviousOperator(char s);
};