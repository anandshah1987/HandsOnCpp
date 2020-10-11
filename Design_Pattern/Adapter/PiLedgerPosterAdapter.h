#pragma once

#include <memory>
#include "LedgerPosterAdapterBase.h"
#include "PiLedgerPosterAdaptee.h"


class PiLedgerPosterAdapter : public LedgerPosterAdapterBase
{
public:

    PiLedgerPosterAdapter(std::unique_ptr<PiLedgerPosterAdaptee> piAdaptee) : m_piAdaptee(std::move(piAdaptee))
    {}

    void Obtain() override
    {
        m_piAdaptee->GetLedgerEntriesToPost();
    }

    void Post() override
    {
        m_piAdaptee->PostLedgerEntriesToExtSystem();
    }

private:

    std::unique_ptr<PiLedgerPosterAdaptee> m_piAdaptee;

};

