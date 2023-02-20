# TODO

## Add

- C++ Code for handling Math

## Change

- Change buffer to a JSString (String) in order to properly return from onButtonClick
- Take in jstr as wchar_t* in MathHandler.cpp. Only convert to wstring when needed.
- Return value from onButtonClick that needs to be displayed to screen in Javascript. Or return void and print to screen directly from C++

## Bugs

- Using printDebugMessage to print buffer is one character behind on each print
- Button click event does not only run on buttons