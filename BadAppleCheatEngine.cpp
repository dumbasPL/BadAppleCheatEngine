#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "resource.h"

#define W 72
#define H 76
#define FRAME_SIZE (W * H)
#define FRAME_RATE 30

int main() {

    HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(IDR_RCDATA1), RT_RCDATA);
    if (!hResource) {
        std::cout << "Error: unable to find resource\n";
        return 1;
    }

    DWORD dwSize = SizeofResource(NULL, hResource);
    if (dwSize == 0) {
        std::cout << "Error: resource is empty\n";
        return 1;
    }

    if (dwSize % FRAME_SIZE != 0) {
        std::cout << "Error: resource is invalid\n";
        return 1;
    }

    HGLOBAL hMemory = LoadResource(NULL, hResource);
    if (!hMemory) {
        std::cout << "Error: unable to load resource\n";
        return 1;
    }

    PBYTE bpData = (PBYTE)LockResource(hMemory);

    PBYTE bpBuffer = (PBYTE)VirtualAlloc(NULL, FRAME_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!bpBuffer) {
        std::cout << "Error: failed to allocate frame buffer\n";
        return 1;
    }

    std::cout << "frame buffer allocated at: 0x" << std::hex << std::setw(sizeof(uintptr_t)) << (uintptr_t)bpBuffer << std::dec << "\n";

    system("pause");

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    LONGLONG frequencyNs = frequency.QuadPart / 1000000;

    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);

    constexpr LONGLONG nsPerFrame = 1000000 / FRAME_RATE;
    LONGLONG nextTick = ticks.QuadPart + (nsPerFrame * frequencyNs);

    DWORD dwFrameCount = dwSize / FRAME_SIZE;
    for (DWORD dwFrameIndex = 0; dwFrameIndex < dwFrameCount; dwFrameIndex++) {
        PBYTE bpFrame = bpData + (FRAME_SIZE * dwFrameIndex);
        for (DWORD i = 0; i < FRAME_SIZE; i++) {
            if (bpFrame[i] > 127) {
                bpBuffer[i] = dwFrameIndex & 0xFF;
            }
        }
        do {
            QueryPerformanceCounter(&ticks);
            Sleep(1);
        } while (ticks.QuadPart < nextTick);
        nextTick += (nsPerFrame * frequencyNs);
    }

}

