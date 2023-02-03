#include "AppHelper.h"

AppHelper::AppHelper() {}

void AppHelper::sendMsg(const JSChar *msg, const char *function, ultralight::View* _caller) {
    // Get Scene Context
    RefPtr<JSContext> context = _caller->LockJSContext();
    JSContextRef ctx = context->ctx();
    //SetJSContext(context->ctx()); // Depricated method

    // Function name
    JSRetainPtr<JSStringRef> str = adopt(JSStringCreateWithUTF8CString(function));

    // Evaluate function name
    JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

    // Check if 'func' exists
    if (JSValueIsObject(ctx, func)) {
        // Cast 'func' to an Object. Returns null if typecast fails
        JSObjectRef funcObj = JSValueToObject(ctx, func, 0);

        // Check if 'funcObj' is a Function and not null
        if (funcObj && JSObjectIsFunction(ctx, funcObj)) {

            // Create JS string from null-terminated UTF8 C-string
            // Store in garbage-collected pointer
            JSRetainPtr<JSStringRef> jsmsg = adopt(JSStringCreateWithCharacters(msg, std::wcslen(msg))); //sizeof(msg)/sizeof(JSChar*))); //adopt(JSStringCreateWithCharacters(msg, wcslen(msg)));

            // Create list of arguments
            const JSValueRef args[] = { JSValueMakeString(ctx, jsmsg.get()) };

            // Get number of arguments
            size_t num_args = sizeof(args) / sizeof(JSValueRef*);

            // Create exception check
            JSValueRef exception = 0;

            // Call function with list of arguments
            JSValueRef result = JSObjectCallAsFunction(ctx, funcObj, 0, num_args, args, &exception);


            if (exception) {
                // Handle exceptions
            }

            if (result) {
                // Handle results
            }
        }
    }
}

void AppHelper::printDebugMsg(const JSChar *msg, ultralight::View *_caller) {
    // Get Scene Context
    RefPtr<JSContext> context = _caller->LockJSContext();
    JSContextRef ctx = context->ctx();
    //SetJSContext(context->ctx()); // Depricated method

    // Function name
    JSRetainPtr<JSStringRef> str = adopt(JSStringCreateWithUTF8CString("debugPrint"));

    // Evaluate function name
    JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

    // Check if 'func' exists
    if (JSValueIsObject(ctx, func)) {
        // Cast 'func' to an Object. Returns null if typecast fails
        JSObjectRef funcObj = JSValueToObject(ctx, func, 0);

        // Check if 'funcObj' is a Function and not null
        if (funcObj && JSObjectIsFunction(ctx, funcObj)) {

            // Create JS string from null-terminated UTF8 C-string
            // Store in garbage-collected pointer
            JSRetainPtr<JSStringRef> jsmsg = adopt(JSStringCreateWithCharacters(msg, std::wcslen(msg))); //sizeof(msg)/sizeof(JSChar*))); //adopt(JSStringCreateWithCharacters(msg, wcslen(msg)));

            // Create list of arguments
            const JSValueRef args[] = { JSValueMakeString(ctx, jsmsg.get()) };

            // Get number of arguments
            size_t num_args = sizeof(args) / sizeof(JSValueRef*);

            // Create exception check
            JSValueRef exception = 0;

            // Call function with list of arguments
            JSValueRef result = JSObjectCallAsFunction(ctx, funcObj, 0, num_args, args, &exception);


            if (exception) {
                // Handle exceptions
            }

            if (result) {
                // Handle results
            }
        }
    }
}

void AppHelper::printDebugMsg(const std::wstring msg, ultralight::View *_caller) {
    // Get Scene Context
    RefPtr<JSContext> context = _caller->LockJSContext();
    JSContextRef ctx = context->ctx();
    //SetJSContext(context->ctx()); // Depricated method

    // Function name
    JSRetainPtr<JSStringRef> str = adopt(JSStringCreateWithUTF8CString("debugPrint"));

    // Evaluate function name
    JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

    // Check if 'func' exists
    if (JSValueIsObject(ctx, func)) {
        // Cast 'func' to an Object. Returns null if typecast fails
        JSObjectRef funcObj = JSValueToObject(ctx, func, 0);

        // Check if 'funcObj' is a Function and not null
        if (funcObj && JSObjectIsFunction(ctx, funcObj)) {

            // Create JS string from null-terminated UTF8 C-string
            // Store in garbage-collected pointer
            JSRetainPtr<JSStringRef> jsmsg = adopt(JSStringCreateWithCharacters(msg.c_str(), msg.length())); //sizeof(msg)/sizeof(JSChar*))); //adopt(JSStringCreateWithCharacters(msg, wcslen(msg)));

            // Create list of arguments
            const JSValueRef args[] = { JSValueMakeString(ctx, jsmsg.get()) };

            // Get number of arguments
            size_t num_args = sizeof(args) / sizeof(JSValueRef*);

            // Create exception check
            JSValueRef exception = 0;

            // Call function with list of arguments
            JSValueRef result = JSObjectCallAsFunction(ctx, funcObj, 0, num_args, args, &exception);


            if (exception) {
                // Handle exceptions
            }

            if (result) {
                // Handle results
            }
        }
    }
}

void AppHelper::printDebugMsg(const float num, ultralight::View *_caller) {
    // Get Scene Context
    RefPtr<JSContext> context = _caller->LockJSContext();
    JSContextRef ctx = context->ctx();
    //SetJSContext(context->ctx()); // Depricated method

    // Function name
    JSRetainPtr<JSStringRef> str = adopt(JSStringCreateWithUTF8CString("debugPrint"));

    // Evaluate function name
    JSValueRef func = JSEvaluateScript(ctx, str.get(), 0, 0, 0, 0);

    // Check if 'func' exists
    if (JSValueIsObject(ctx, func)) {
        // Cast 'func' to an Object. Returns null if typecast fails
        JSObjectRef funcObj = JSValueToObject(ctx, func, 0);

        // Check if 'funcObj' is a Function and not null
        if (funcObj && JSObjectIsFunction(ctx, funcObj)) {

            // Create JS string from null-terminated UTF8 C-string
            // Store in garbage-collected pointer
            std::wostringstream woss;
            woss << num;
            const JSChar* msg = woss.str().c_str();
            JSRetainPtr<JSStringRef> jsmsg = adopt(JSStringCreateWithCharacters(msg, std::wcslen(msg))); //sizeof(msg)/sizeof(JSChar*))); //adopt(JSStringCreateWithCharacters(msg, wcslen(msg)));

            // Create list of arguments
            const JSValueRef args[] = { JSValueMakeString(ctx, jsmsg.get()) };

            // Get number of arguments
            size_t num_args = sizeof(args) / sizeof(JSValueRef*);

            // Create exception check
            JSValueRef exception = 0;

            // Call function with list of arguments
            JSValueRef result = JSObjectCallAsFunction(ctx, funcObj, 0, num_args, args, &exception);


            if (exception) {
                // Handle exceptions
            }

            if (result) {
                // Handle results
            }
        }
    }
}