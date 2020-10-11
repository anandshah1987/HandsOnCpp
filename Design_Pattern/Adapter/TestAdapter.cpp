// ProInvestAdapter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LedgerPosterAdapterBase.h"
#include "PiLedgerPosterAdapter.h"
#include "TcmLedgerPosterAdapter.h"

enum class System { SystemA, SystemB };

std::unique_ptr<LedgerPosterAdapterBase> LedgerPosterFactory(const System system)
{
    switch (system)
    {
    case System::SystemA:
        return std::make_unique<PiLedgerPosterAdapter>(std::make_unique<PiLedgerPosterAdaptee>());

    case System::SystemB:
        return std::make_unique<TcmLedgerPosterAdapter>(std::make_unique<TcmLedgerPosterAdaptee>());

    default :
        return nullptr;
    }
}


void StartPostingLedgerEntriesToExtSystem()
{
    int count = 50;
    auto ledgerPoster = LedgerPosterFactory(System::SystemA);
    while (count > 0)
    {
        ledgerPoster->Obtain();
        ledgerPoster->Post();
        count--;
    }
}

int main()
{
    StartPostingLedgerEntriesToExtSystem();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
