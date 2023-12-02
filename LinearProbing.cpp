#include "LinearProbing.h"
using namespace std;
void LinearProbing::createAccount(std::string id, int count)
{
    Account new_account;
    new_account.id = id;
    new_account.balance = count;
    int hash_value = hash(id);
    Account dummy;
    dummy.balance = -1;
    dummy.id = "";
    if (bankStorage1d.size() == 0)
    {
        bankStorage1d.resize(100001, dummy);
    }
    int i = hash_value - 1;
    while (bankStorage1d[i].balance >= 0 && i != hash_value - 2)
    {
        i = (i + 1) % 100001;
    }
    bankStorage1d[i] = new_account;
    size++;
};
std::vector<int> LinearProbing::getTopK(int k)
{
    std::vector<int> balance_list;
    for (int i = 0; i < bankStorage1d.size(); i++)
    {
        if (balance_list.size() == 0)
        {
            balance_list.push_back(bankStorage1d[i].balance);
        }
        else
        {
            int h = 0;
            while (h < balance_list.size() && balance_list[h] > bankStorage1d[i].balance)
            {
                h++;
            }
            balance_list.insert(balance_list.begin() + h, bankStorage1d[i].balance);
        }
    }
    std::vector<int> final;
    for (int h = 0; h < k; h++)
    {
        final.push_back(balance_list[h]);
    }
    return final;
}

int LinearProbing::getBalance(std::string id)
{
    int hash_value = hash(id);
    int i = hash_value;
    while (bankStorage1d[i].id != id && i < bankStorage1d.size())
    {
        i++;
    }
    if (i >= bankStorage1d.size())
    {
        i = 0;
        while (bankStorage1d[i].id != id && i < hash_value)
        {
            i++;
        }
        if (i == hash_value)
        {
            return -1;
        }
    }
    return bankStorage1d[i].balance;
}

void LinearProbing::addTransaction(std::string id, int count)
{
    int hash_value = hash(id);
    int i = hash_value - 1;
    if (doesExist(id) == false)
    {

        createAccount(id, count);
    }
    else
    {
        while (bankStorage1d[i].id != id && i < bankStorage1d.size())
        {
            i++;
        }
        if (i >= bankStorage1d.size())
        {
            i = 0;
            while (bankStorage1d[i].id != id && i < hash_value - 1)
            {
                i++;
            }
        }
        bankStorage1d[i].balance += count;
    };
}

bool LinearProbing::doesExist(std::string id1)
{
    int hash_value = hash(id1);
    int i = hash_value;
    while (i < 200002)
    {
        if (bankStorage1d[i % 100001].id == id1)
        {
            return true;
        }
        i++;
    }
    // if (i>=bankStorage1d.size())
    // {
    //     i = 0;
    //     while (i<hash_value)
    //     {
    //         if (bankStorage1d[i].id==id1)
    //         {
    //             return true;
    //         }
    //         i++;
    //     }
    // }
    return false;
}

bool LinearProbing::deleteAccount(std::string id1)
{
    if (doesExist(id1) == false)
    {
        // std::cout << "YEs\n";
        return false;
    }
    int hash_value = hash(id1);
    int i = hash_value;
    while (i < 200002)
    {
        if (bankStorage1d[i].id == id1)
        {
            bankStorage1d[i].balance = -1;
            bankStorage1d[i].id = "";
            size--;
            return true;
        };

        i = (i + 1) % 100001;
    }
    // i = 0;
    // while (i < hash_value - 1)
    // {
    //     if (bankStorage1d[i].id == id1)
    //     {
    //         bankStorage1d[i].balance = -1;
    //         bankStorage1d[i].id = "";
    //         size--;
    //         return true;
    //     }
    //     i++;
    // }
    return false;
}
int LinearProbing::databaseSize()
{
    return size;
}

int LinearProbing::hash(std::string id)
{
    int hash = 0;
    int h = 113;
    for (int i = 0; i < 4; i++)
    {
        hash = hash + static_cast<int>(id[i]);
    }
    for (int i = 12; i < id.size(); i++)
    {
        hash = hash + (id[i] - '0') * h * h * h * 3.5;
        h++;
    }
    return abs(hash % 100001); // Placeholder return value
}

// int main(){
//     LinearProbing op;
//     op.createAccount("AMAN1234567_1234567890",100);
//     op.createAccount("NMNA1234567_1234567890",10);
//     op.createAccount("NAMA1234567_1234567890",10);
//     op.deleteAccount("NAMA1234567_1234567890");
//     op.addTransaction("ANAM1234567_1234567890",10);
//     std::cout<<op.doesExist("ANAM1234567_1234567890")<<std::endl;
//     op.deleteAccount("NAMA1234567_1234567890");
// std::cout<<op.doesExist("NAMA1234567_1234567890")<<std::endl;

//     std::cout<<op.databaseSize()<<std::endl;

//     return 0;
// }