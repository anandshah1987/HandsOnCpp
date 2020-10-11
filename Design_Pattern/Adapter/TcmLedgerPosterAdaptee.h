#pragma once
#include <iostream>


class TcmLedgerPosterAdaptee
{
public :
	TcmLedgerPosterAdaptee() {};

	void FetchLedgerEntries()
	{
		std::cout << "TCM - Getting relevant ledger entries to post" << '\n';
	}

	void PostEntries()
	{
		std::cout << "TCM - Posting ledger entries to external system" << '\n';
	}
};