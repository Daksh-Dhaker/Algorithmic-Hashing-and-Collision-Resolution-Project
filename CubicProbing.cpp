#include "CubicProbing.h"

void CubicProbing::merge1(std::vector<int> &v,int l,int mid,int r){
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

void CubicProbing::merge_sort(std::vector<int> &v,int l,int r){
    if(l==r){
        return;
    }else{
        int mid = (l+r)/2;
        this->merge_sort(v,l,mid);
        this->merge_sort(v,mid+1,r);
        this->merge1(v,l,mid,r);
        return ;
    }
}

int CubicProbing::fastpower(int base,int expo){
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

void CubicProbing::createAccount(std::string id, int count) {
    if(bankStorage1d.size()==0){
        counter =0;
        Account a;
        a.id = "NULL";
        a.balance =-1;
        for(int i=0;i<100003;i++){
            bankStorage1d.push_back(a);
        }
    }
    counter++;
    Account b;
    b.id = id;
    b.balance = count;
    int hash_idx = this->hash(id);
    int i=0;
    long long probe = hash_idx;
    while(bankStorage1d[probe].id !="NULL"){
        i++;
        probe = (hash_idx+(i*i*i))%100003;
    }
    bankStorage1d[probe] = b;
}

std::vector<int> CubicProbing::getTopK(int k) {
    std::vector<int> v;
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id!="NULL"){
            v.push_back(bankStorage1d[i].balance);
        }
    }
    this->merge_sort(v,0,v.size()-1);
    std::vector<int> ans;
    int count1=0;
    int j=v.size()-1;
    while(count1<k && j>=0){
        ans.push_back(v[j]);
        count1++;
        j--;
    }return ans;
}

int CubicProbing::getBalance(std::string id) {
    int hash_idx = this->hash(id);
    long long probe = hash_idx;
    if(bankStorage1d[hash_idx].id == id){
        return bankStorage1d[hash_idx].balance;
    }else{
        probe = (hash_idx+1)%100003;
        long long i=1;
        while(i<100003){
            if(bankStorage1d[probe].id == id){
                break;
            }i++;
            probe = (hash_idx+(i*i*i))%100003;
        }
        if(i==100003){
            return -1;
        }else{
            return bankStorage1d[probe].balance;
        }
    }
}

void CubicProbing::addTransaction(std::string id, int count) {
    int hash_idx = this->hash(id);
    long long probe = hash_idx;
    if(bankStorage1d[hash_idx].id == id){
        bankStorage1d[hash_idx].balance += count;
    }else{
        probe = (hash_idx+1)%100003;
        long long i=1;
        while(i<100003){
            if(bankStorage1d[probe].id == id){
                break;
            }i++;
            probe = (hash_idx+(i*i*i))%100003;
        }
        if(i==100003){
            this->addTransaction(id,count);
        }else{
            bankStorage1d[probe].balance += count;
        }
    }
}

bool CubicProbing::doesExist(std::string id) {
    int hash_idx = this->hash(id);
    long long probe = hash_idx;
    if(bankStorage1d[hash_idx].id == id){
        return true;
    }else{
        probe = (hash_idx+1)%100003;
        long long i=1;
        while(i<100003){
            if(bankStorage1d[probe].id == id){
                break;
            }i++;
            probe = (hash_idx+(i*i*i))%100003;
        }
        if(i==100003){
            return false;
        }else{
            return true;
        }
    }
}

bool CubicProbing::deleteAccount(std::string id) {
    int hash_idx = this->hash(id);
    long long probe = hash_idx;
    if(bankStorage1d[hash_idx].id == id){
        Account a;
        a.id = "NULL";
        a.balance = -1;
        bankStorage1d[hash_idx]=a;
        counter--;
        return true;
    }else{
        probe = (hash_idx+1)%100003;
        long long i=1;
        while(i<100003){
            if(bankStorage1d[probe].id == id){
                break;
            }i++;
            probe = (hash_idx+(i*i*i))%100003;
        }
        if(i==100003){
            return false;
        }else{
            Account a;
            a.id = "NULL";
            a.balance = -1;
            bankStorage1d[probe]=a;
            counter--;
            return true;
        }
    }
}
int CubicProbing::databaseSize() {
    return counter;
}

int CubicProbing::hash(std::string id) {
    long long sum=0;
    int i;
    
    for(i=0;i<4;i++){
        sum = (sum)+(fastpower(31,i+1)*static_cast<int>(id[i]));
        sum = sum%100003;
    }
    
    while(i<11){
        sum = (sum)+(fastpower(16,(i+1-4)%8)*static_cast<int>(id[i]));
        sum = sum%100003;
        i++;
    }i++;
    
    while(i<22){
        sum = (sum)+(fastpower(33,(i+1-12)%7)*static_cast<int>(id[i]));
        sum = sum%100003;
        i++;
    }
   
    int hash_idx = sum%(100003);
    return hash_idx;
}