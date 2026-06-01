#include <Windows.h>
#include <thread>
#include <chrono>
#include "Hooks.h"

#include <string>

void DebugPrint(const char* fmt, ...)
{
    char buf[512];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    OutputDebugStringA(buf);
}

static HANDLE g_MainThread = nullptr;

DWORD WINAPI MainThread(LPVOID module)
{
    AllocConsole();
    FILE* stdoutFile = nullptr;
    FILE* stderrFile = nullptr;
    freopen_s(&stdoutFile, "CONOUT$", "w", stdout);
    freopen_s(&stderrFile, "CONOUT$", "w", stderr);

    SetConsoleTitleA("debug");


    Hooks::Setup();

    while (!(GetAsyncKeyState(VK_END) & 1))
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

    Hooks::Destroy();

    if (stdoutFile) fclose(stdoutFile);
    if (stderrFile) fclose(stderrFile);
    FreeConsole();

    FreeLibraryAndExitThread(static_cast<HMODULE>(module), 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        g_MainThread = CreateThread(
            nullptr,
            0,
            MainThread,
            hModule,
            0,
            nullptr
        );
    }

    return TRUE;
}
