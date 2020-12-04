// Recordvalue_VectorOfChar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#define IN_PP_ID 1
#define IN_ACCOUNT_ID 2
#define MAX_FIELD_SIZE 1024

class RecordValue
{
public :
    void Add(const short item, const char* data);
    void Get(const short item, char* data);

    struct FieldValueStruct
    {
        //int fieldSize{};
        short itemNo{};
        short dataSize{};
        int headerSize = (sizeof(decltype(itemNo)) + sizeof(decltype(dataSize)) 
                                + sizeof(decltype(headerSize)));
        char data[MAX_FIELD_SIZE]{};
        
    };

private :

    unsigned int m_fieldCount;
    std::vector<char> m_recordData;
    //unsigned int m_newIndexInsert{};
};

void RecordValue::Add(const short item, const char* data)
{
    FieldValueStruct field{};
    field.itemNo = item;
    field.dataSize = static_cast<short>(strlen(data));
    memcpy(field.data, data, field.dataSize);
    auto fieldSize = field.headerSize + field.dataSize;

    m_recordData.resize(m_recordData.size()+ fieldSize);
    
    FieldValueStruct* fieldPtr = reinterpret_cast<FieldValueStruct*>(&m_recordData[m_recordData.size() - fieldSize]);
    fieldPtr->itemNo = item;
    fieldPtr->dataSize = field.dataSize;
    memcpy(fieldPtr->data, data, field.dataSize);
    fieldPtr->headerSize = field.headerSize;

    m_fieldCount++;
}

void RecordValue::Get(const short item, char* data)
{
    int offSet = 0;
    for (unsigned int i=0; i < m_fieldCount; i++)
    {
        FieldValueStruct* fieldPtr = reinterpret_cast<FieldValueStruct*>(&m_recordData[offSet]);
        if (item == fieldPtr->itemNo)
        {
            memcpy(data, fieldPtr->data, fieldPtr->dataSize);
            data[fieldPtr->dataSize] = '\0';
            break;
        }
        offSet += (fieldPtr->headerSize+ fieldPtr->dataSize);
    }
}


int main()
{
    RecordValue rvIn;
    rvIn.Add(IN_PP_ID, "1001");
    rvIn.Add(IN_ACCOUNT_ID, "1");
    char ppId[10];
    rvIn.Get(IN_PP_ID, ppId);
    char accountId[2];
    rvIn.Get(IN_ACCOUNT_ID, accountId);
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
