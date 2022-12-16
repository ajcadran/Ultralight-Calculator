#include "MathHandler.h"

MathHandler::MathHandler() {

}

JSValueRef MathHandler::onButtonClick(const JSObject& thisObject, const JSArgs& args, ultralight::View *caller) { //, const RefPtr<Overlay> overlay) {
    // Set private caller to avoid passing into every function
    // Not best practice
    // Derive MathHandler from Calculator in order to have access to caller?
    caller_ = caller;

    // Get character passed from JS
    JSString jstr = args[0].ToString();
    const JSChar* jchar = (wchar_t*)JSStringGetCharactersPtr(jstr);

    if (isdigit(static_cast<int>(jchar[0]))) {
        handleNumber()
    } else {
        handleSymbol(jchar);
    }
    
    /*
    JSValueToObject(ctx, arguments[0], NULL);
    = args[0].ToObject()["key"].ToString()
    
    return JSValue(args[0].ToObject());
    return JSValue(args.data()[0]);
    */

    // Easy way to run JS function
    //overlay->view()->EvaluateScript("debugPrint('Teest')");

    return JSValue(args[0].ToString());
}

void MathHandler::handleSymbol(const JSChar* jchar) {
    //const char* symbol = (char*)&jchar;
    int symbol = static_cast<int>(jchar[0]);

    switch (symbol) {
        case 67: // C
            //printDebugMsg(L"C");
            setRunningTotal(0);
            setBuffer(L"0");
            setPreviousOperator(NULL);
            break;
        case 61: // =
            //printDebugMsg(L"=");
            if (getPreviousOperator() == NULL) return;
            //flushOperation(getBuffer());
            setPreviousOperator(NULL);
            setBuffer(std::to_wstring(getRunningTotal()));
            setRunningTotal(0);
            break;
        case 60: // <
            //printDebugMsg(L"<");
            if (sizeof(getBuffer()) == 1) {
                setBuffer(L"0");
            } else {

            }
            break;
        default:
            printDebugMsg(L"Default");
            break;
    }
}

void MathHandler::handleNumber(const JSChar* number) {
    return;
}

// TODO: Move to Helper class
void MathHandler::printDebugMsg(const JSChar* msg) {
    RefPtr<JSContext> context = caller_->LockJSContext();
    JSContextRef ctx = context->ctx();
    //SetJSContext(context->ctx());

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
            //const char* new_arg = wstringToChar(msg);
            JSRetainPtr<JSStringRef> jsmsg = adopt(JSStringCreateWithCharacters(msg, std::wcslen(msg))); //sizeof(msg)/sizeof(JSChar*))); //adopt(JSStringCreateWithCharacters(msg, wcslen(msg)));
            //delete[] new_arg;

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

bool MathHandler::isNotNumber(const std::wstring wstr) {
    std::wstringstream wss(wstr);
    double d;
    return !(wss >> d);
}

/*
// TODO: Not always working. 
const char* MathHandler::wstringToChar(const std::wstring wstr) {
    const wchar_t* wcstr = wstr.c_str();
    const std::size_t length = std::wcslen(wcstr);
    char* cstr = new char[length];
    std::wcstombs(cstr, wcstr, length);

    return cstr;
}
*/


// Getters and Setters
float MathHandler::getRunningTotal() const { return this->runningTotal; }
void MathHandler::setRunningTotal(float t) { this->runningTotal = t; }

std::wstring MathHandler::getBuffer() const { return this->buffer; }
void MathHandler::setBuffer(std::wstring b) { this->buffer = b; }

char MathHandler::getPreviousOperator() const { return this->previousOperator; }
void MathHandler::setPreviousOperator(char s) { this->previousOperator = s; }
