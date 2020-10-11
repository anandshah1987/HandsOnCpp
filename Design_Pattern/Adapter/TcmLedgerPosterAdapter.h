#pragma once
#include <memory>
#include "LedgerPosterAdapterBase.h"
#include "TcmLedgerPosterAdaptee.h"

class TcmLedgerPosterAdapter : public LedgerPosterAdapterBase
{
public :

	TcmLedgerPosterAdapter(std::unique_ptr<TcmLedgerPosterAdaptee> tcmAdaptee)
	{
		m_tcmAdaptee = std::move(tcmAdaptee);
	}

	void Obtain() override
	{
		m_tcmAdaptee->FetchLedgerEntries();
	}

	void Post() override
	{
		m_tcmAdaptee->PostEntries();
	}

private:
	std::unique_ptr<TcmLedgerPosterAdaptee> m_tcmAdaptee;
};
