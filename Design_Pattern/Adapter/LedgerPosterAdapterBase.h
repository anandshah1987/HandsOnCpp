#pragma once

// Adapter target. Client will use this Target 
class LedgerPosterAdapterBase
{
public:
    virtual void Obtain() = 0;
    virtual void Post() = 0;
};



