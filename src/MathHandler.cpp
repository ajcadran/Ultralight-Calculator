#include "MathHandler.h"

#include <typeinfo>
#include <Windows.h>

MathHandler::MathHandler() {
    this->runningTotal = 0;
    this->buffer = "0";
    this->previousOperator = ""[0];
}

JSValueRef MathHandler::onButtonClick(const JSObject& thisObject, const JSArgs& args, ultralight::View *caller) {
    // TODO: Set private caller to avoid passing into every function
    _caller = caller;

    // Get character passed from JS
    JSString jstr = args[0].ToString();
    const JSChar* jchar = (wchar_t*)JSStringGetCharactersPtr(jstr);

    if (isdigit(static_cast<int>(jchar[0]))) {
        handleNumber(std::wcstol(jchar, nullptr, 10));
    } else {
        handleSymbol(jchar);
    }

    AppHelper::sendMsg(getBufferW().c_str(), "printScreen", _caller);
    return JSValue();
}

void MathHandler::handleSymbol(const JSChar* jchar) {
    int symbol = static_cast<int>(jchar[0]);

    switch (symbol) {
        case 67: // C
            setBuffer("0");
            setRunningTotal(0);
            break;
        case 61: // =
            if (getPreviousOperator() == ""[0]) return;
            flushOperation(std::stof(getBuffer()));
            setPreviousOperator(""[0]);
            setBuffer(std::to_string(getRunningTotal()));
            setRunningTotal(0);
            break;
        case 60: // <
            if (getBuffer().length() <= 1) setBuffer("0");
            else this->buffer.pop_back();
            break;
        case 46: // .
            // TODO
            //if (getBuffer().find(symbol) == std::string::npos) setBuffer(getBuffer().push_back('.');
            if (getBuffer().find(symbol) == std::string::npos) this->buffer.push_back('.');
            break;
        default:
            handleMath(jchar);
            break;
    }
}

void MathHandler::handleMath(const JSChar* symbol) {
    if (getBuffer() == "0") return;

    const float intBuffer = std::stof(getBuffer());

    if (getRunningTotal() == 0) setRunningTotal(intBuffer);
    else flushOperation(intBuffer);

    setPreviousOperator(symbol);
    setBuffer("0");
}

void MathHandler::flushOperation(float floatBuffer) {
    if (getPreviousOperator() == "+"[0]) setRunningTotal(getRunningTotal() + floatBuffer);
    else if (getPreviousOperator() == "-"[0]) setRunningTotal(getRunningTotal() - floatBuffer);
    else if (getPreviousOperator() == "x"[0]) setRunningTotal(getRunningTotal() * floatBuffer);
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
JSChar MathHandler::getBufferJS() const { 
    std::wstring wstr(this->buffer.begin(), this->buffer.end());
    return *wstr.c_str();
}
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
