#include "Comp.h"
using namespace std;
void Comp::createAccount(std::string id, int count) {
    Account new_account;
    new_account.id = id;
    new_account.balance = count;
    int hash_value = hash(id);
    int sz = bankStorage1d.size();
    Account dummy;
    dummy.balance = -1;
    if (sz==0)
    {
        bankStorage1d.resize(100001,dummy);
    }
        if (bankStorage1d[hash_value-1].balance<0)
        {
            bankStorage1d[hash_value-1]=new_account;
        }
        else
        {
            int i = hash_value - 1;
            int h = 1;
            while (i<bankStorage1d.size())
            {
                if (bankStorage1d[i].balance<0)
                {
                    bankStorage1d[i] = new_account;
                    break;
                }
                else if (i + h*h*h >= bankStorage1d.size())
                {
                    i = bankStorage1d.size() % h*h*h;
                    while (i < hash_value)
                    {
                        if (bankStorage1d[i].balance<0)
                            {
                                bankStorage1d[i] = new_account;
                                break;
                            }
                        i = i + h*h;
                        h++;
                    };
                    break;
                }
                else 
                {
                    i = i + h*h;
                    h++;
                }
            };
        };
}

std::vector<int> Comp::getTopK(int k) {
    std::vector <int> balance_list;
    for (int i = 0; i < bankStorage1d.size(); i++)
    {
        if (balance_list.size()==0)
        {
            balance_list.push_back(bankStorage1d[i].balance);
        }
        else
        {
            int h = 0;
                while (balance_list[h]>bankStorage1d[i].balance && h < balance_list.size())
                {
                    h++;
                }
                balance_list.insert(balance_list.begin()+h,bankStorage1d[i].balance);
    
        }
    }
    std::vector <int> final;
    for(int h = 0; h < k; h++)
    {
        
        final.push_back(balance_list[h]);
    }
    return final;
}

int Comp::getBalance(std::string id) {
    int hash_value = hash(id);
    int i = hash_value - 1;
    int h = 1;
            while (i<bankStorage1d.size())
            {
                if (bankStorage1d[i].id==id)
                {
                    return bankStorage1d[i].balance;
                }
                else if (i + h*h >= bankStorage1d.size())
                {
                    i = bankStorage1d.size() % h*h;
                    while (i < hash_value)
                    {
                        if (bankStorage1d[i].id==id)
                            {
                                return bankStorage1d[i].balance;
                                break;
                            }
                        i = i + h*h;
                        h++;
                    };
                    break;
                }
                else 
                {
                    i = i + h*h;
                    h++;
                }
            };
    return 0;
}

void Comp::addTransaction(std::string id, int count) {
   int hash_value = hash(id);
    int i = hash_value - 1;
    int h = 1;
    if (doesExist(id)==false)
    {
        createAccount(id,count);
    }
    else{
            while (i<bankStorage1d.size())
            {
                if (bankStorage1d[i].id==id)
                {
                    bankStorage1d[i].balance += count;
                    break;
                }
                else if (i + h*h >= bankStorage1d.size())
                {
                    i = h*h - (bankStorage1d.size()-i) - 1;
                    while (i < hash_value)
                    {
                        if (bankStorage1d[i].id==id)
                        {
                            bankStorage1d[i].balance += count;
                        }
                        i = i + h*h;
                        h++;
                    };
                }
                else 
                {
                    i = i + h*h;
                    h++;
                }
            };
            }
}

bool Comp::doesExist(std::string id) {
   int hash_value = hash(id);
    int i = hash_value - 1;
    int h = 1;
            while (i<bankStorage1d.size())
            {
                if (bankStorage1d[i].id==id && bankStorage1d[i].balance>=0)
                {
                    return true;
                }
                else if (i + h*h >= bankStorage1d.size() && bankStorage1d[i].balance>=0)
                {
                    i = bankStorage1d.size() % h*h;
                    while (i < hash_value)
                    {
                        if (bankStorage1d[i].id==id)
                        {
                            return true;
                        }
                        i = i + h*h;
                        h++;
                    };
                    return false;
                }
                else 
                {
                    i = i + h*h;
                    h++;
                }
            };
    return false; // Placeholder return value
}

bool Comp::deleteAccount(std::string id) {
    int hash_value = hash(id);
    int i = hash_value - 1;
    int h = 1;
            while (i<bankStorage1d.size())
            {
                if (bankStorage1d[i].id==id)
                {
                    bankStorage1d[i].balance=-1;
                    return true;
                }
                else if (i + h*h >= bankStorage1d.size())
                {
                    i = bankStorage1d.size() % h*h*h;
                    while (i < hash_value)
                    {
                        if (bankStorage1d[i].id==id)
                        {
                            bankStorage1d[i].balance=-1;
                            return true;
                        }
                        i = i + h*h;
                        h++;
                    };
                    return false;
                }
                else 
                {
                    i = i + h*h;
                    h++;
                }
            };
    return false; // Placeholder return value
}
int Comp::databaseSize() {
    int sz = 0;
    for (int i = 0; i<bankStorage1d.size(); i++)
    {
        if (bankStorage1d[i].balance>=0)
        {
            sz++;
        };
    };
    return sz;
};
int Comp::hash(std::string id) {
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
    return abs(hash % 100001); // Placeholder return value
}
