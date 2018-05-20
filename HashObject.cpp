#include <ostream>

class Hash {
public:
    virtual int hashCode() = 0;

    virtual void print(std::ostream &str) const = 0;

    friend std::ostream &operator<<(std::ostream &os, Hash &hash) {
        hash.print(os);
        return os;
    }
};

class HashObject : public Hash {
    int x;
    int y;
public:
    HashObject(int x, int y) : x(x), y(y) {}

    int hashCode() {
        int result = x;
        result = 31 * result + y;
        return result;
    }

    void print(std::ostream &os) const {
        os << "x: " << x << ", y: " << y;
    }
};
