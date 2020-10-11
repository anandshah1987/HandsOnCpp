#pragma once
#pragma once
#include <iostream>

class PiLedgerPosterAdaptee
{
public:

    PiLedgerPosterAdaptee() {};

    void GetLedgerEntriesToPost()
    {
        std::cout << "ProInvest - Getting relevant ledger entries to post" << '\n';
    }

    void PostLedgerEntriesToExtSystem()
    {
        std::cout << "ProInvest - Posting ledger entries to external system" << '\n';
    }
};