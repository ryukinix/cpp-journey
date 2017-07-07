/* Define the exception here */

class BadLengthException: public exception {
private:
    int length;
public:
    BadLengthException(int n) {
        length = n;
    }
    const char * what () {
        return to_string(length).c_str();
    }
};
