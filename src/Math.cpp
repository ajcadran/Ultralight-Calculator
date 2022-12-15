#include "Math.h"

Math::Math() {}

JSValueRef Math::onButtonClick(const JSObject& thisObject, const JSArgs& args) {
    //JSValueToObject(ctx, arguments[0], NULL);
    //= args[0].ToObject()["key"].ToString()
    return JSValue(args.data()[0]);
}

/*
JSCallbackWithRetval Math::BindJSFunction(fn) {
    return (JSCallbackWithRetval)std::bind(fn, this, std::placeholders::_1, std::placeholders::_2);
}
*/