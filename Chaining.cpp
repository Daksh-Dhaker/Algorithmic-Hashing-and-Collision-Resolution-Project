#include "Chaining.h"

void Chaining::merge1(std::vector<int> &v,int l,int mid,int r){
    std::vector<int> v1;
    std::vector<int> v2;
    for(int i=l;i<=mid;i++){
        v1.push_back(v[i]);
    }
    for(int i=mid+1;i<=r;i++){
        v2.push_back(v[i]);
    }
    int i=0;int j=0;
    int k=l;
    while(i<v1.size() && j<v2.size()){
        if(v1[i]==v2[j]){
            v[k]=v1[i];
            k++;
            v[k]=v1[i];
            k++;
            i++;j++;
        }else if(v1[i]<v2[j]){
            v[k]=v1[i];
            k++;
            i++;
        }else{
            v[k]=v2[j];
            k++;
            j++;
        }
    }
    if(i!=v1.size()){
        while(i<v1.size()){
            v[k]=v1[i];
            k++;
            i++;
        }
    }
    if(j!=v2.size()){
        while(j<v2.size()){
            v[k]=v2[j];
            k++;
            j++;
        }
    }
}

void Chaining::merge_sort(std::vector<int> &v,int l,int r){
    if(l==r){
        return;
    }else{
        int mid = (l+r)/2;
        merge_sort(v,l,mid);
        merge_sort(v,mid+1,r);
        merge1(v,l,mid,r);
        return ;
    }
}

int Chaining::fastpower(int base,int expo){
    if(expo ==0){
        return 1;
    }else if(expo == 1){
        return base;
    }else{
        if(expo%2 ==0){
            return fastpower(base*base,expo/2);
        }else{
            return base*(fastpower(base*base,(expo-1)/2));
        }
    }
}

void Chaining::createAccount(std::string id, int count) {
    if(bankStorage2d.size()==0){
        std::vector<Account> v;
        for(int i=0;i<100000;i++){
            bankStorage2d.push_back(v);
        }
        counter=0;
    }
    counter = counter+1;
    Account a;
    a.id = id;
    a.balance = count;
    int hash_idx = hash(id);
    bankStorage2d[hash_idx].push_back(a); 
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> v;
    for(int i=0;i<bankStorage2d.size();i++){
        for(int j=0;j<bankStorage2d[i].size();i++){
            v.push_back(bankStorage2d[i][j].balance);
        }
    }
    merge_sort(v,0,v.size()-1);
    std::vector<int> ans;
    int count1=0;
    int j=v.size()-1;
    while(count1<k && j>=0){
        ans.push_back(v[j]);
        count1++;
        j--;
    }return ans;
}

int Chaining::getBalance(std::string id) {
    int hash_idx = hash(id);
    int size = bankStorage2d[hash_idx].size();
    int i;
    int balance =0;
    for(i=0;i<size;i++){
        if(bankStorage2d[hash_idx][i].id==id){
            balance = bankStorage2d[hash_idx][i].balance;
            break;
        }
    }
    if(i==size){
        return -1;
    }else{
        return balance;
    }
}

void Chaining::addTransaction(std::string id, int count) {
    int hash_idx = hash(id);
    int size = bankStorage2d[hash_idx].size();
    int i;
    for(i=0;i<size;i++){
        if(bankStorage2d[hash_idx][i].id==id){
            bankStorage2d[hash_idx][i].balance += count;
            break;
        }
    }
    if(i==size){
        Account a;
        a.id = id;
        a.balance = count;
        bankStorage2d[hash_idx].push_back(a);
        counter++;
    }
}

bool Chaining::doesExist(std::string id) {
    int hash_idx = hash(id);
    int size = bankStorage2d[hash_idx].size();
    int i;
    for(i=0;i<size;i++){
        if(bankStorage2d[hash_idx][i].id==id){
            return true;
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id) {
    int hash_idx = hash(id);
    int size = bankStorage2d[hash_idx].size();
    int i;
    for(i=0;i<size;i++){
        if(bankStorage2d[hash_idx][i].id==id){
            break;
        }
    }
    if(i==size){
        return false;
    }else{
        bankStorage2d[hash_idx].erase(bankStorage2d[hash_idx].begin() +i);
        counter--;
        return true;
    }
}
int Chaining::databaseSize() {
    return counter; 
}

int Chaining::hash(std::string id) {
    long long sum=0;
    int i;
    
    for(i=0;i<4;i++){
        sum = (sum)+(fastpower(31,i+1)*static_cast<int>(id[i]));
        sum = sum%100000;
    }
    
    while(i<11){
        sum = (sum)+(fastpower(16,(i+1-4)%8)*static_cast<int>(id[i]));
        sum = sum%100000;
        i++;
    }i++;
    
    while(i<22){
        sum = (sum)+(fastpower(33,(i+1-12)%7)*static_cast<int>(id[i]));
        sum = sum%100000;
        i++;
    }
   
    int hash_idx = sum%(100000);
    return hash_idx; 
}
