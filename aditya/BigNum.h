#define GRANULARITY 8

class BigNum
{
    private:
    
    char *arr;    //character array representing number
    int size;        //number of digits in the number
    // pthread_mutexes maybe
    
    public:
    BigNum(const char*);
    BigNum(const BigNum&);
    BigNum operator+(const BigNum &);
    BigNum operator-(const BigNum &);
    BigNum operator*(const BigNum &);
    BigNum operator/(const BigNum &);
    BigNum operator<<(const BigNum &);
    BigNum operator>>(const BigNum &);
    BigNum operator&(const BigNum &);
    BigNum operator|(const BigNum &);
    BigNum operator^(const BigNum &);
    BigNum operator~();
    BigNum operator==(const BigNum &);   

    void print();
};

