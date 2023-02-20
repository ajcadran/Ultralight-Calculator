#include "MathHandler.h"

#include <typeinfo>
#include <Windows.h>

MathHandler::MathHandler() {
    this->runningTotal = 0;
    this->buffer = "";
    this->previousOperator = ""[0];
}

JSValueRef MathHandler::onButtonClick(const JSObject& thisObject, const JSArgs& args, ultralight::View *caller) { //, const RefPtr<Overlay> overlay) {
    // Set private caller to avoid passing into every function
    // Not best practice
    // Derive MathHandler from Calculator in order to have access to caller?
    _caller = caller;

    // Get character passed from JS
    JSString jstr = args[0].ToString();
    const JSChar* jchar = (wchar_t*)JSStringGetCharactersPtr(jstr);

    //OutputDebugStringW(jchar);
    //OutputDebugString("\n");

    //OutputDebugStringW(getBuffer().c_str());
    //OutputDebugString("\n");

    if (isdigit(static_cast<int>(jchar[0]))) {
        handleNumber(std::wcstol(jchar, nullptr, 10));
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

    AppHelper::sendMsg(getBufferW().c_str(), "printScreen", _caller);
    ////return JSValue(getBuffer().c_str());
    //return JSValue(args[0].ToString());
    return JSValue();
}

void MathHandler::handleSymbol(const JSChar *jchar) {
    //const char* symbol = (char*)&jchar;
    int symbol = static_cast<int>(jchar[0]);
    //AppHelper::printDebugMsg(jchar, _caller);

    switch (symbol) {
        case 67: // C
            //AppHelper::printDebugMsg(L"C", _caller);
            setBuffer("0");
            setRunningTotal(0);
            break;
        case 61: // =
            //AppHelper::printDebugMsg(L"=");
            if (getPreviousOperator() == ""[0]) return;
            flushOperation(std::stof(getBuffer()));
            setPreviousOperator(""[0]);
            setBuffer(std::to_string(getRunningTotal()));
            setRunningTotal(0);
            break;
        case 60: // <
            //AppHelper::printDebugMsg(L"<");
            if (getBuffer().length() <= 1) setBuffer("0");
            else this->buffer.pop_back();
            break;
        default:
            //AppHelper::printDebugMsg(jchar);
            handleMath(jchar);
            break;
    }
}

void MathHandler::handleMath(const JSChar *symbol) {
    if (getBuffer() == "0") return;

    const float intBuffer = std::stof(getBuffer()); //static_cast<int>(getBuffer()[0]);

    if (getRunningTotal() == 0) setRunningTotal(intBuffer);
    else flushOperation(intBuffer);

    setPreviousOperator(symbol);
    setBuffer("0");
}

void MathHandler::flushOperation(float floatBuffer) {
    if (getPreviousOperator() == "+"[0]) setRunningTotal(getRunningTotal() + floatBuffer);
    else if (getPreviousOperator() == "-"[0]) setRunningTotal(getRunningTotal() - floatBuffer);
    else if (getPreviousOperator() == "xw"[0]) setRunningTotal(getRunningTotal() * floatBuffer);
    else if (getPreviousOperator() == "/"[0]) setRunningTotal(getRunningTotal() / floatBuffer);
}

void MathHandler::handleNumber(const int number) {
    if (getBuffer() == "0") setBuffer(std::to_string(number));
    else this->buffer += std::to_string(number);

    return;
}

// Getters and Setters
float MathHandler::getRunningTotal() const { return this->runningTotal; }
void MathHandler::setRunningTotal(float t) { this->runningTotal = t; }

std::string MathHandler::getBuffer() const { return this->buffer; }
std::wstring MathHandler::getBufferW() const { 
    std::wstring wstr(this->buffer.begin(), this->buffer.end());
    return wstr;
}
void MathHandler::setBuffer(std::string b) { 
    float value = std::stof(b);
    if (std::floor(value) == value) this->buffer = std::to_string(static_cast<int>(value));
    else this->buffer = std::to_string(value);
}


char MathHandler::getPreviousOperator() const { return this->previousOperator; }
void MathHandler::setPreviousOperator(char s) { this->previousOperator = s; }
void MathHandler::setPreviousOperator(const JSChar *symbol) {
    char ch;
    std::wcstombs(&ch, symbol, 1);
    this->previousOperator = ch;
}
