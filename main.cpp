#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
using namespace std;
// hash table
template <typename T>
class hash_table
{
private:
    class KeyValuePair
    {

    private:
        T key;
        T value;

    public:
        KeyValuePair(T key, T value)
        {
            this->key = key;
            this->value = value;
        }

        KeyValuePair() {}

        T getKey() { return key; }
        T getValue() { return value; }
        void setValue(T value)
        {
            this->value = value;
        }
    };

    KeyValuePair *entries;
    int length;
    int initSize;
    int entriesCount;

public:
    hash_table()
    {
        this->initSize = 3;
        this->entries = new KeyValuePair[this->initSize];
        this->length = this->initSize;
        this->entriesCount = 0;
    }

    // Other methods...

    void resize()
    {
        if (this->entriesCount < this->length - 1)
        {
            return;
        }
        else
        {
            int newSize = this->length * 2;
            KeyValuePair *entries_copy = new KeyValuePair[length];

            for (int i = 0; i < length; i++)
            {
                entries_copy[i] = this->entries[i];
            }

            delete[] this->entries;
            int entries_copy_len = this->length;
            this->entries = new KeyValuePair[newSize];
            this->length = newSize;

            for (int i = 0; i < entries_copy_len; i++)
            {
                if (entries_copy[i].getKey().empty())
                {
                    continue;
                }
                Add_to_entries(entries_copy[i].getKey(), entries_copy[i].getValue());
            }
            delete[] entries_copy;
        }
    }

    int get_hash(string str)
    {
        // Constants used for FNV-1 hash algorithm
        uint32_t OffsetBasis = 2166136261;
        uint32_t FNVPrime = 16777619;

        // Convert string to byte array
        const char *data = str.c_str();
        size_t len = str.length();
        uint8_t *bytes = new uint8_t[len];
        memcpy(bytes, data, len);

        // Compute hash using FNV-1 algorithm
        uint32_t hash = OffsetBasis;
        for (size_t i = 0; i < len; i++)
        {
            hash = hash ^ bytes[i];
            hash = hash * FNVPrime;
        }

        // Clean up allocated memory
        delete[] bytes;

        // return hash
        return static_cast<int>(hash % this->length);
    }

    int collision_handling(T key, int hash, bool set)
    {
        int new_hash;
        for (int i = 1; i < this->length; i++)
        {
            new_hash = (hash + i) % this->length;
            if (set && (this->entries[new_hash].getKey().empty() || this->entries[new_hash].getKey() == key))
            {

                return new_hash;
            }
            else if (!set && this->entries[new_hash].getKey() == key)
            {

                return new_hash;
            }
            else
            {
                continue;
            }
        }
        return -1;
    }

    // set

    void set(T key, T value)
    {

        resize();
        Add_to_entries(key, value);
    }

    // we create this function Add_to_entries to avoid "circular dependency"
    void Add_to_entries(T key, T value)
    {

        int hash = get_hash(key);
        if (!this->entries[hash].getKey().empty() && this->entries[hash].getKey() != key)
        {
            hash = collision_handling(key, hash, true);
        }

        if (hash == -1)
        {

            throw runtime_error("invalid hashTable");
        }

        if (this->entries[hash].getKey().empty())
        {

            this->entries[hash] = KeyValuePair(key, value);
            this->entriesCount++;
        }
        else if (this->entries[hash].getKey() == key)
        {

            this->entries[hash].setValue(value);
        }
        else
        {
            throw runtime_error("invalid hashTable");
        }
    }
    // get
    T get(T key)
    {

        int hash = get_hash(key);
        if (!this->entries[hash].getKey().empty() && this->entries[hash].getKey() != key)
        {
            hash = collision_handling(key, hash, false);
        }

        if (hash == -1 || this->entries[hash].getKey().empty())
        {
            return "NULL";
        }

        if (this->entries[hash].getKey() == key)
        {

            return this->entries[hash].getValue();
        }
        else
        {
            throw runtime_error("invalid hashTable");
        }
    }

    // remove

    bool Remove(T key)
    {

        int hash = get_hash(key);
        if (!this->entries[hash].getKey().empty() && this->entries[hash].getKey() != key)
        {
            hash = collision_handling(key, hash, false);
        }

        if (hash == -1 || this->entries[hash].getKey().empty())
        {
            return "NULL";
        }

        if (this->entries[hash].getKey() == key)
        {

            this->entries[hash] = KeyValuePair();
            this->entriesCount--;
            return true;
        }
        else
        {
            throw runtime_error("invalid hashTable");
        }
    }

    int size() { return entriesCount; }

    void print()
    {
        for (int i = 0; i < this->length; i++)
        {
            if(!this->entries[i].getKey().empty() ){

                cout << "key: " << this->entries[i].getKey() << " value: " << this->entries[i].getValue() << endl;

            }
            
        }
    }
};
// char freq class
class char_frequencies
{

public:
    char_frequencies(){};

    void ASCII_method(string text)
    {

        cout << " ASCII_method " << endl;
        int array[127] = {0};
        for (char c : text)
        {
            int current_char = int(c);
            array[current_char]++;
        }
        cout << "char frequencies" << endl;
        cout << "-----------------" << endl;
        cout << text << endl;
        for (int i = 0; i < 127; i++)
        {

            if (array[i] > 0)
            {

                cout << char(i) << " , " << array[i] << endl;
            }
            else
            {
                continue;
            }
        }
    }

    // char utf8 frequencies using hash htable function

    void utf8_method(string text)
    {

        cout << "utf8_method" << endl;
        hash_table<string> hash_table;

        for (int i = 0; i < text.length(); i++)
        {
            string cast_char = "";
            cast_char = text[i];
            if (hash_table.get(cast_char) == "NULL")
            {

                hash_table.set(cast_char, "1");
            }
            else
            {

                hash_table.set(cast_char, to_string(stoi(hash_table.get(cast_char)) + 1));
            }
        }

        hash_table.print();
    }
};

//---------------------------------------------------

int main()
{       
    string text = "hello world";
     char_frequencies freq;
     freq.ASCII_method(text);
     freq.utf8_method(text);
    return 0;
}