#include <iostream>
#include <string>
#include <sstream>  
#include <stdexcept>

#pragma once
#define HASHMAP_H

using namespace std;


template <typename T>
string to_string_custom(const T& val) {
    stringstream ss;
    ss << val;
    return ss.str();
}


template <typename k, typename t>
struct hashnode
{
    k key;
    t value;
    hashnode* next;

    hashnode(k Key, t val) : key(Key), value(val), next(nullptr) {}
};

template <typename t, typename k>
class Hashmap
{
private:
    static const int table_size = 100;
    hashnode<k, t>** table;

    // Hash function to calculate hash value based on key
    int hashFunc(k key)
    {
        int hashVal = 0;
        for (char ele : key) 
        {
            hashVal += ele;  
        }
        return hashVal % table_size;  
    }

public:
    Hashmap()
    {
        table = new hashnode<k, t>* [table_size];
        for (int i = 0; i < table_size; i++)
        {
            table[i] = nullptr;
        }
    }

    ~Hashmap()
    {
        for (int i = 0; i < table_size; i++)
        {
            hashnode<k, t>* temp = table[i];
            while (temp != nullptr)
            {
                hashnode<k, t>* todel = temp;
                temp = temp->next;
                delete todel;
            }
        }
        delete[] table;
    }

    void insert(k key, t value) {
        int i = hashFunc(key);

        // Check if the value already exists for the key and update if necessary
        hashnode<k, t>* curr = table[i];
        while (curr != nullptr) {
            if (curr->key == key) {
                curr->value = value; 
                return;
            }
            curr = curr->next;
        }

      
        hashnode<k, t>* newnode = new hashnode<k, t>(key, value);
        newnode->next = table[i];
        table[i] = newnode;
    }

    t get(k key) {
        int idx = hashFunc(key);
        hashnode<k, t>* curr = table[idx];
        while (curr != nullptr) {
            if (curr->key == key) {
                return curr->value; 
            }
            curr = curr->next;
        }
        throw runtime_error("Key not found");
    }


    bool find(k key)
    {
        int idx = hashFunc(key);

        hashnode<k, t>* curr = table[idx];
        while (curr != nullptr)
        {
            if (curr->key == key)
            {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
};