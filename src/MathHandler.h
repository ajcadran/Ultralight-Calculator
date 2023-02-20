#pragma once
#include <AppCore/AppCore.h>
#include <AppCore/JSHelpers.h>
#include <JavaScriptCore/JSValueRef.h>
#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSStringRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <string>
#include <iostream>
#include <sstream>
#include <locale>

#include "AppHelper.h"

using namespace ultralight;

class MathHandler
{
private:
    ultralight::View *_caller;
    float runningTotal;
    std::string buffer;
    char previousOperator;

public:
    MathHandler();
    JSValueRef onButtonClick(const JSObject& thisObject, const JSArgs& args, ultralight::View* caller);
    void handleSymbol(const JSChar* symbol);
    void handleMath(const JSChar* symbol);
    void flushOperation(float floatBuffer);
    void handleNumber(const int number);

    // Getters and Setters
    float getRunningTotal() const;
    void setRunningTotal(float total);
    std::string getBuffer() const;
    JSChar getBufferJS() const;
    std::wstring getBufferW() const;
    void setBuffer(std::string buffer);
    char getPreviousOperator() const;
    void setPreviousOperator(char symbol);
    void setPreviousOperator(const JSChar *symbol);
};
