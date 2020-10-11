// Polymorphism_Trial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <array>
#include <functional>

class CFundInterface
{
public :
    virtual std::string GetFundIdentification() const = 0;
    //virtual void SetFundIdentification(std::string fundId) = 0;
};

struct FundsData : public CFundInterface
{
    std::string instrumentId;
    std::string GetFundIdentification() const override
    {
        return instrumentId;
    }
};

//template<typename T>
class CFundMgmtFee
{
public :
    CFundMgmtFee(std::array<std::unique_ptr<CFundInterface>, 3>& fundData)
    {
        for (const auto& fund : fundData)
        {
            std::cout << "Fund identification is " << fund->GetFundIdentification() << '\n';
        }
    }
};

int main()
{
    /*FundsData obj;
    obj.instrumentId = "Test";
    CFundInterface& base = obj;
    std::cout << "output is " << base.GetFundIdentification() << '\n';*/

    std::array<FundsData, 3> fundsData;
    fundsData[0].instrumentId = "Tata";
    fundsData[1].instrumentId = "Relience";
    fundsData[2].instrumentId = "IRCTC";

    std::array<std::unique_ptr<CFundInterface>, 3> fundDataPtr{};
    for (int i=0; i<3; i++)
    {
        fundDataPtr[i] = std::make_unique<FundsData>(fundsData[i]);
    }
    CFundMgmtFee mgmtFee(fundDataPtr);

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
