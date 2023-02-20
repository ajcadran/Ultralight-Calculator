#pragma once
#include <AppCore/AppCore.h>
#include <AppCore/JSHelpers.h>
#include <JavaScriptCore/JSValueRef.h>
#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSStringRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <iostream>
#include <sstream>

using namespace ultralight;

class AppHelper
{
public:
    AppHelper();
    static void sendMsg(const JSChar* msg, const char* function, ultralight::View* _caller);
};
