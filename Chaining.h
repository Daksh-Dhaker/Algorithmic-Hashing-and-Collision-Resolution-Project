#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    int counter;
    int fastpower(int base,int expo);
    void merge1(std::vector<int> &v,int l,int mid,int r);
    void merge_sort(std::vector<int> &v,int l,int r);
};

#endif // CHAINING_H
