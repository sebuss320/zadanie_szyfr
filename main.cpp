#include <string>
#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

int randomPosition(int max) {
    return rand() % max;
}

char *generateKey(const char *base, int size) {
    char *result = new char[size];
    for (int i = 0; i < size; i++) {
        result[i] = '.';
    }

    int freeSpaces = size;
    for (int i = 0; i < size; i++) {
        char current = base[i];
        int position = randomPosition(freeSpaces--);
        while (result[position] != '.') {
            position++;
            if (position >= size) {
                position = 0;
            }
        }
        result[position] = current;
    }
    return result;
}

string encrypt(const string &message, const char *base, char *key, int size) {
    string result;
    for (char current : message) {
        int position = 0;
        while (current != base[position] && position < size) {
            position++;
        }
        if (position < size) {
            result.push_back(key[position]);
        } else {
            result.push_back(current);
        }
    }
    return result;
}

string decrypt(const string &message, char *base, const char *key, int size) {
    string result;
    for (char current : message) {
        int position = 0;
        while (current != key[position] && position < size) {
            position++;
        }
        if (position < size) {
            result.push_back(base[position]);
        } else {
            result.push_back(current);
        }
    }
    return result;
}

int main() {
    // given alphabet
    srand(time(nullptr));
    int size = 48;
    char base[48] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                     'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'w', 'x', 'y', 'z',
                     'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                     'M', 'N', 'O', 'P', 'R', 'S', 'T', 'U', 'W', 'X', 'Y', 'Z',};

    string message = "Hello, Coders School!";
    auto key = generateKey(base, size);
    auto cypher = encrypt(message, base, key, size);
    auto result = decrypt(cypher, base, key, size);

    cout << "Message: " << message << '\n';
    cout << "Cypher: " << cypher << '\n';
    cout << "Result: " << result << '\n';

    assert(message == result);
    return 0;
}