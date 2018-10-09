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
        void setData(int index, int value);
        int getData(int index);
        void destory(void);
        ~Array();
};

#endif
