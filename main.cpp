#include <windows.h> //windows.h for windows specific functions and types
#include <winternl.h> // for the ntstatus type and function pointer types

#pragma comment(lib, "ntdll.lib")

int main() {
    typedef NTSTATUS(NTAPI* TfnRtlAdjustPrivilege)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
    typedef NTSTATUS(NTAPI* TfnNtRaiseHardError)(NTSTATUS, ULONG, ULONG, PVOID, ULONG, PULONG);

    // use the #pragma directive to link to the ntdll.lib library which is needed for the RtlAdjustPrivilege and NtRaiseHardError functions
    auto hNtdll = GetModuleHandle("ntdll.dll");
    if (hNtdll == nullptr) return 0;

    // get function pointers to RtlAdjustPrivilege and NtRaiseHardError
    auto pfnRtlAdjustPrivilege = reinterpret_cast<TfnRtlAdjustPrivilege>(GetProcAddress(hNtdll, "RtlAdjustPrivilege"));
    auto pfnNtRaiseHardError = reinterpret_cast<TfnNtRaiseHardError>(GetProcAddress(hNtdll, "NtRaiseHardError"));

    // call RtlAdjustPrivilege to enable the SeShutdownPrivilege privilege
    BOOLEAN b;
    pfnRtlAdjustPrivilege(19, TRUE, FALSE, &b);

    // call NtRaiseHardError to trigger the blue screen with the STATUS_ASSERTION_FAILURE error code and a parameter count of 6
    ULONG r;
    pfnNtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, nullptr, 6, &r);

    return 0;
}
