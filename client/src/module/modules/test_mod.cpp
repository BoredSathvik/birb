#include "test_mod.h"

TestMod::TestMod() : Module("Test Counter", "test_mod", true) {}

TestMod::~TestMod() {}

void TestMod::OnInit() {
    Logger::LogF("sus");
    // MessageWebSocket websocket;

    // UIThread::RunOnUIThreadAsync([&] {
    //     websocket.ConnectAsync(Windows::Foundation::Uri{L"ws://localhost:8080"}).get();

    //     DataWriter dataWriter{websocket.OutputStream()};
    //     dataWriter.WriteString(L"Hello World");

    //     dataWriter.StoreAsync().get();
    //     dataWriter.DetachStream();
    // }).get();
}
