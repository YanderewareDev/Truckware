#include "Memory/Memory.h"

#include <Windows.h>
#include <vector>
#include <iostream>
#include <map>
#include <functional>
#include <string>

cMemory Memory;

typedef std::map<std::string, std::function<void(void)>> CommandDictionary;

static DWORD MoneyPointer                       = { 0x011367E4 };
static std::vector<DWORD> MoneyOffsets          = { 0xC, 0x10 };
static int CurrentMoney                         = { 0x0 };

int main() {
    CommandDictionary Command;
    std::string UserInput;

    Memory.FindProcess("eurotrucks2.exe");
    uintptr_t ModuleBase = Memory.GetModuleBaseAddress("eurotrucks2.exe");

    uintptr_t DynamicMoneyPointer = ModuleBase + MoneyPointer;
    uintptr_t MoneyAddress = Memory.FindAddress(DynamicMoneyPointer, MoneyOffsets);

    CurrentMoney = Memory.ReadMemory<int>(MoneyAddress);

    std::cout << "Truckware v1.0 | Nexo#2557\n\n";

    std::cout << "Euro Truck Simulator 2 PID: 0x" << std::hex << Memory.ProcessID << "\n";
    std::cout << "Euro Truck Simulator 2 Handle: 0x" << std::hex << Memory.ProcessHandle << "\n\n";
    
    std::cout << "Money address: 0x" << std::hex << MoneyAddress << "\n";
    std::cout << "Current money value: " << std::dec << CurrentMoney << "\n";
    std::cout << "New money value: "; std::cin >> CurrentMoney;

    Memory.WriteMemory<int>(MoneyAddress, CurrentMoney);
}