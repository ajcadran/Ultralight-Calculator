#include <AppCore/JSHelpers.h>
#include <JavaScriptCore/JSValueRef.h>

using namespace ultralight;

class Math
{
public:
    Math();
    JSValueRef onButtonClick(const JSObject& thisObject, const JSArgs& args);

    // Bind functions
    //JSCallbackWithRetval BindJSFunction(fn); // (Math *math)
};