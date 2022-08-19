#include <cstring>
#include <iostream>
 
class String {
private:
    size_t sz_ = 0;
    size_t capacity_ = 1;
    char* string_ = new char[1];

    size_t pow_of_2(size_t x) {
        size_t cnt = 0;
        while (x > 1) {
            x /= 2;
            ++cnt;
        }
        return cnt;
    }

    size_t set_capacity(size_t n) {
        return 1 << (pow_of_2(n) + 1);
    }

    void swap(String& tmp) {
        std::swap(string_, tmp.string_);
        std::swap(sz_, tmp.sz_);
        std::swap(capacity_, tmp.capacity_);
    }

    String(size_t n)
            : sz_(n)
            , capacity_(set_capacity(sz_))
            , string_(new char[capacity_]) 
    {}

    size_t impl_find(const String& substring, bool flag) const {
        size_t ans = (flag ? 0 : length());
        for (size_t i = 0; i + substring.length() <= length(); i++) {
            if (std::memcmp(string_ + i, substring.string_,
                            substring.length()) == 0) {
                ans = i;
                if (!flag) {
                    return ans;
                }
            }
        }
        return ans;
    }

    void resize(size_t newsz) {
        if (newsz <= capacity_) {
            return;
        }
        capacity_ = set_capacity(newsz);
        char* tmp = new char[capacity_];
        std::memcpy(tmp, string_, sz_);
        std::swap(tmp, string_);
        delete[] tmp;
    }

public:
    String() = default;

    String(size_t n, char c)
            : sz_(n)
            , capacity_(set_capacity(sz_))
            , string_(new char[capacity_]) {
        std::memset(string_, c, sz_);
    }

    String(char c)
            : sz_(1)
            , capacity_(set_capacity(sz_))
            , string_(new char[capacity_]) {
        string_[0] = c;
    }

    String(const char* s)
            : sz_(strlen(s))
            , capacity_(set_capacity(sz_))
            , string_(new char[capacity_]) {
        std::memcpy(string_, s, sz_);
    }

    String(const String& s)
            : sz_(s.sz_)
            , capacity_(s.capacity_)
            , string_(new char[capacity_]) {
        std::memcpy(string_, s.string_, sz_);
    }

    friend bool operator==(const String& l, const String& r);

    String& operator=(const String& s) {
        String tmp = s;
        swap(tmp);
        return *this;
    }

    char& operator[](size_t index) {
        return string_[index];
    }

    const char& operator[](size_t index) const {
        return string_[index];
    }

    size_t length() const {
        return sz_;
    }

    void push_back(char s) {
        resize(sz_ + 1);
        string_[sz_++] = s;
    }

    void pop_back() {
        --sz_;
    }

    char& front() {
        return string_[0];
    }

    const char& front() const {
        return string_[0];
    }

    char& back() {
        return string_[sz_ - 1];
    }

    const char& back() const {
        return string_[sz_ - 1];
    }

    String& operator+=(const String& s) {
        resize(sz_ + s.sz_);
        std::memcpy(string_ + sz_, s.string_, s.sz_);
        sz_ += s.sz_;
        return *this;
    }

    size_t find(const String& substring) const {
        return impl_find(substring, 0);
    }

    size_t rfind(const String& substring) const {
        return impl_find(substring, 1);
    }

    String substr(size_t start, size_t count) const {
        size_t end = (start + count <= length()) ? start + count : length();
        String tmp(end - start);
        for (size_t i = start; i < end; ++i) {
            tmp.string_[i - start] = string_[i];
        }
        return tmp;
    }

    bool empty() const {
        return sz_ == 0;
    }

    void clear() {
        sz_ = 0;
    }

    ~String() {
        delete[] string_;
    }
};
 
String operator+(const String& l, const String& r) {
    String copy = l;
    copy += r;
    return copy;
}

bool operator==(const String& l, const String& r) {
    return l.length() == r.length() &&
        std::memcmp(l.string_, r.string_, l.length()) == 0;
}
 
std::ostream& operator<<(std::ostream& ostream, const String& s) {
    for (size_t i = 0; i < s.length(); ++i) {
        ostream << s[i];
    }
    return ostream;
}
 
std::istream& operator>>(std::istream& istream, String& str) {
    char s;
    while (istream.get(s)) {
        if (std::isspace(s)) {
            if (!str.empty()) {
                break;
            }
        } else {
            str.push_back(s);
        }
    }
    return istream;
}

