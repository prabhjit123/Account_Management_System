#include "Chaining.h"
using namespace std;
void Chaining::createAccount(std::string id, int count) 
{
    Account new_account;
    new_account.id = id;
    new_account.balance = count;
    int hash_value = hash(id);
    int sz = bankStorage2d.size();
    if (bankStorage2d.size()==0)
    {
        bankStorage2d.resize(100001);
    }
    bankStorage2d[hash_value-1].push_back(new_account);
    size++;

}

std::vector<int> Chaining::getTopK(int k) 
{
    std::vector <int> balance_list;
    for(int i = 0; i < bankStorage2d.size(); i++)
    {
        for(int j = 0; j < bankStorage2d[i].size(); j++)
        {
            if (balance_list.size()==0)
            {
                balance_list.push_back(bankStorage2d[i][j].balance);
            }
            else
            {
                int h = 0;
                while (h < balance_list.size() && balance_list[h]>bankStorage2d[i][j].balance)
                {
                    h++;
                }
                balance_list.insert(balance_list.begin()+h,bankStorage2d[i][j].balance);
            };
        };
    };
    std::vector <int> final;
    for(int h = 0; h < k; h++)
    {
        final.push_back(balance_list[h]);
    }
    return final;
}

int Chaining::getBalance(std::string id) {
    int hash_value = hash(id);
    int i = 0;
    while (i<bankStorage2d[hash_value-1].size())
    {
        if (bankStorage2d[hash_value-1][i].id==id)
        {
            return bankStorage2d[hash_value-1][i].balance;
        }
        else
        {
            i++;
        };
    };
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    if (doesExist(id)==false)
    {
        createAccount(id,count);
    }
    else
    {
    int hash_value = hash(id);
    int i = 0;
    while (i<bankStorage2d[hash_value-1].size())
    {
        if (bankStorage2d[hash_value-1][i].id==id)
        {
            bankStorage2d[hash_value-1][i].balance += count;
            break;
        }
        else
        {
            i++;
        };
    };

    };
}

bool Chaining::doesExist(std::string id) {
    int hash_value = hash(id);
    int i = 0;
    while (i<bankStorage2d[hash_value-1].size())
    {
        if (bankStorage2d[hash_value-1][i].id==id)
        {
            return true;
        }
        else
        {
            i++;
        };
    };
    return false;
}

bool Chaining::deleteAccount(std::string id) {
    int hash_value = hash(id);
    int i = 0;
    while (i<bankStorage2d[hash_value-1].size())
    {
        if (bankStorage2d[hash_value-1][i].id==id)
        {
            bankStorage2d[hash_value-1].erase(bankStorage2d[hash_value-1].begin()+i,bankStorage2d[hash_value-1].begin()+i+1);
            size--;
            return true;
        }
        else
        {
            i++;
        };
    };
    return false;
}
int Chaining::databaseSize() {
    return size; // Placeholder return value
}

int Chaining::hash(std::string id) {
    int hash = 0;
    int h = 113;
    for(int i =0; i<4; i++)
    {
        hash = hash + static_cast<int>(id[i]);
    }
    for(int i = 12; i<id.size(); i++)
    {
        hash = hash + (id[i] - '0')*h*h*h*3.5;
        h++;
    }
    return abs(hash % 100000); // Placeholder return value
}
