#include "Calculator.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 700

//Math *math = new Math();

Calculator::Calculator()
{
    ///
    /// Create our main App instance.
    ///
    app_ = App::Create();

    ///
    /// Create a resizable window by passing by OR'ing our window flags with
    /// kWindowFlags_Resizable.
    ///
    window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
                             false, kWindowFlags_Titled | kWindowFlags_Resizable);
    window_->SetTitle("Ultralight Calculator");

    ///
    /// Create our HTML overlay-- we don't care about its initial size and
    /// position because it'll be calculated when we call OnResize() below.
    ///
    overlay_ = Overlay::Create(window_, 1, 1, 0, 0);

    ///
    /// Force a call to OnResize to perform size/layout of our overlay.
    ///
    OnResize(window_.get(), window_->width(), window_->height());

    ///
    /// Load a page into our overlay's View
    ///
    overlay_->view()->LoadURL("file:///app.html");

    ///
    /// Register our MyApp instance as an AppListener so we can handle the
    /// App's OnUpdate event below.
    ///
    app_->set_listener(this);

    ///
    /// Register our MyApp instance as a WindowListener so we can handle the
    /// Window's OnResize event below.
    ///
    window_->set_listener(this);

    ///
    /// Register our MyApp instance as a LoadListener so we can handle the
    /// View's OnFinishLoading and OnDOMReady events below.
    ///
    overlay_->view()->set_load_listener(this);

    ///
    /// Register our MyApp instance as a ViewListener so we can handle the
    /// View's OnChangeCursor and OnChangeTitle events below.
    ///
    overlay_->view()->set_view_listener(this);

    //Platform::instance().set_logger(new MyLogger());
}

Calculator::~Calculator() {}

void Calculator::Run() {
    app_->Run();
}

void Calculator::OnUpdate() {
    ///
    /// This is called repeatedly from the application's update loop.
    ///
    /// You should update any app logic here.
    ///
}

void Calculator::OnClose(ultralight::Window *window) {
    app_->Quit();
}

void Calculator::OnResize(ultralight::Window *window, uint32_t width, uint32_t height) {
    ///
    /// This is called whenever the window changes size (values in pixels).
    ///
    /// We resize our overlay here to take up the entire window.
    ///
    overlay_->Resize(width, height);
}

void Calculator::OnFinishLoading(ultralight::View *caller,
                                 uint64_t frame_id,
                                 bool is_main_frame,
                                 const String &url) {
    ///
    /// This is called when a frame finishes loading on the page.
    ///
}

void Calculator::OnDOMReady(ultralight::View *caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const String &url) {      
    RefPtr<JSContext> context = caller->LockJSContext();
    SetJSContext(context->ctx());
    JSObject global = JSGlobalObject();

    global["onButtonClick"] = (JSCallbackWithRetval)std::bind(&MathHandler::onButtonClick, mathHandler, std::placeholders::_1, std::placeholders::_2, caller); //, overlay_);
    //global["onButtonClick"] = BindJSCallbackWithRetval(&Calculator::onButtonClick);
}

void Calculator::OnChangeCursor(ultralight::View *caller,
                                Cursor cursor) {
    ///
    /// This is called whenever the page requests to change the cursor.
    ///
    /// We update the main window's cursor here.
    ///
    window_->SetCursor(cursor);
}

void Calculator::OnChangeTitle(ultralight::View *caller,
                               const String &title) {
    ///
    /// This is called whenever the page requests to change the title.
    ///
    /// We update the main window's title here.
    ///
    window_->SetTitle(title.utf8().data());
}

