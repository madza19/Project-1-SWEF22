#ifndef BAH_HASH_H_INCLUDED
#define BAH_HASH_H_INCLUDED
const int TABLE_SIZE = 17;
const int MAX_DIST = 4;

int insertValue(int);
int deleteValue(int);
int searchValue(int);
int hashValue(int);
void clearKey(int);

struct Buckets
{
    bool inUse = false;
    int value = 0;
    int hop[MAX_DIST] = {0};
};
Buckets bucket[TABLE_SIZE];


// Attempts to insert a value or recursively move values if insertion fails
int insertValue(int value) {
    int key = hashValue(value);

    // Inserts a value
    // Returns insertion key if successful
    // Exits loop if insertion is unsuccessful
    for(int i = 0; i < MAX_DIST; ++i) {
        if(bucket[key].hop[i] == 0 && !bucket[key + i].inUse) {
            key = key + i;
            if(key >= TABLE_SIZE) {
                // Out of bounds
                return -2;
            }

            bucket[key - i].hop[i] = 1;

            bucket[key].inUse = true;
            bucket[key].value = value;
            return key;
        }
    }

    // Moves a value using recursion
    // Returns insertion key if successful
    // Exits loop if move is unsuccessful
    for(int i = 0; i < MAX_DIST; ++i) {
        if(bucket[key].hop[i] == 0) {
            int parentKey = hashValue(bucket[key + i].value);
            int distance = (key + i) - parentKey;

            for(int j = 0; j < MAX_DIST; ++j) {
                if(!bucket[parentKey + j].inUse) {
                    bucket[parentKey + j].inUse = true;

                    bucket[parentKey + j].value = bucket[key + i].value;

                    bucket[parentKey].hop[j] = 1;
                    bucket[parentKey].hop[distance] = 0;

                    clearKey(key + i);
                    insertValue(value);
                    return key + i;
                }
            }
        }
    }

    // Insert and move failed
    return -1;
}

// Deletes a value and returns it's corresponding key
int deleteValue(int value) {
    int key = hashValue(value);

    if(bucket[key].hop[0] == 1 && bucket[key].value == value) {
        bucket[key].inUse = false;
        bucket[key].value = 0;
        bucket[key].hop[0] = 0;
        return key;
    }
    else if(bucket[key].hop[1] == 1 && bucket[key + 1].value == value) {
        bucket[key + 1].inUse = false;
        bucket[key + 1].value = 0;
        bucket[key].hop[1] = 0;
        return key + 1;
    }
    else if(bucket[key].hop[2] == 1 && bucket[key + 2].value == value) {
        bucket[key + 2].inUse = false;
        bucket[key + 2].value = 0;
        bucket[key].hop[2] = 0;
        return key + 2;
    }
    else if(bucket[key].hop[3] == 1 && bucket[key + 3].value == value) {
        bucket[key + 3].inUse = false;
        bucket[key + 3].value = 0;
        bucket[key].hop[3] = 0;
        return key + 3;
    }
    else {
        // Value not found
        return -1;
    }
}

// Searches for a value and returns it's corresponding key
int searchValue(int value) {
    int key = hashValue(value);

    if(bucket[key].hop[0] == 1 && bucket[key].value == value) {
        return key;
    }
    else if(bucket[key].hop[1] == 1 && bucket[key + 1].value == value) {
        return key + 1;
    }
    else if(bucket[key].hop[2] == 1 && bucket[key + 2].value == value) {
        return key + 2;
    }
    else if(bucket[key].hop[3] == 1 && bucket[key + 3].value == value) {
        return key + 3;
    }
    else {
        // Value not found
        return -1;
    }
}


// Generates and returns hashValue for a given value
int hashValue(int value) {
    return value % TABLE_SIZE;
}

// Clears key field for a corresponding value
void clearKey(int key) {
    bucket[key].inUse = false;
    bucket[key].value = 0;
    bucket[key].hop[0] = 0; //TODO set corresponding parent key to 0 if value doesnt belong
}

#endif // BAH_HASH_H_INCLUDED

