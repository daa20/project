#ifndef _ARRAY_H_
#define _ARRAY_H_


class Array {
    private:
        int m_length;
        int *m_space;
    public:
        Array(int length);
        Array(const Array &obj);
        int length(void);
        ~Array();
        int &operator[](int i);
        Array &operator=(const Array &obj);
        bool operator==(const Array &obj);
        bool operator!=(const Array &obj);
};


#endif
