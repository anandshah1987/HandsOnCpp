// Strategy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <memory>

enum class CommissionType
{
	AgeBased,
	OrderBased,
	ProductBased,
	//AgentBased,
};

class CommissionAgent
{
public:
	virtual double CalculateCommission() = 0;
};

class AgeBasedCommission : public CommissionAgent
{
public:
	double CalculateCommission() override
	{
		return 1;
	}
};

class OrderBasedCommission : public CommissionAgent
{
public:
	double CalculateCommission() override
	{
		return 2;
	}
};

class ProductBasedCommission : public CommissionAgent
{
public:
	double CalculateCommission() override
	{
		return 3;
	}
};

class PpRole
{
	std::string m_role;
public :
	PpRole(const std::string& ppRole) :m_role(ppRole)
	{
	}
	// When new commission type is instroduced in the system, I have to modify base class 
	// & add new if-else part. This is against solid design principle - open for extension, 
	// close for modification
	//double CalculateCommission(const CommissionType commissionType)
	//{
	//	double commission = 0;
	//	if (commissionType == CommissionType::AgeBased)
	//	{
	//		commission = 1;
	//	}
	//	else if(commissionType == CommissionType::OrderBased)
	//	{
	//		commission = 2;
	//	}
	//	/*else if (commissionType == CommissionType::ProductBased)
	//	{
	//		commission = 3;
	//	}*/
	//	return commission;
	//}

	double CalculateCommission(CommissionAgent* agent)
	{
		return agent->CalculateCommission();
	}
};

class Investor : public PpRole
{
public :
	Investor():PpRole("Investor")
	{
	}
};

class Agent : public PpRole
{
public:
	Agent() :PpRole("Agent")
	{
	}
};


int main()
{
	Agent agent;
	/*std::cout << "Commission for agent -> " << agent.CalculateCommission(CommissionType::AgeBased) << std::endl;
	std::cout << "Commission for agent -> " << agent.CalculateCommission(CommissionType::OrderBased) << std::endl;*/
	std::cout << "AgeBasedCommission for agent -> " << agent.CalculateCommission(new AgeBasedCommission()) << std::endl;
	std::cout << "OrderBasedCommission for agent -> " << agent.CalculateCommission(new OrderBasedCommission()) << std::endl;
	Investor investor;
	/*std::cout << "Commission for investor -> " << investor.CalculateCommission(CommissionType::AgeBased) << std::endl;
	std::cout << "Commission for investor -> " << investor.CalculateCommission(CommissionType::OrderBased) << std::endl;*/
	std::cout << "AgeBasedCommission for investor -> " << agent.CalculateCommission(new AgeBasedCommission()) << std::endl;
	std::cout << "OrderBasedCommission for investor -> " << agent.CalculateCommission(new OrderBasedCommission()) << std::endl;
	// So when you added new product based commission, you didn't touch base class PpRole at all.
	std::cout << "ProductBasedCommission for investor -> " << agent.CalculateCommission(new ProductBasedCommission()) << std::endl;
}
