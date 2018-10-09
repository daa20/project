#include "array.h"

Array::Array(int length)
{
    if (length >= 0) {

        this->m_length = length;

        this->m_space = new int[this->m_length];
    } else {
        this->m_length = 0;
    }

}

Array::Array(const Array &obj)
{
    if (obj.m_length >= 0) {

        this->m_length = obj.m_length;
        this->m_space = new int[this->m_length];

        for (int i = 0; i < obj.m_length; i++) {
            this->m_space[i] = obj.m_space[i];
        }

    } else {
        this->m_length = 0;
    }
}

int 
Array::length(void)
{
    return this->m_length;
}

Array::~Array()
{
    this->m_length = 0;
    delete [] this->m_space;
}

int &
Array::operator[](int i)
{
    return this->m_space[i];
}

Array &
Array::operator=(const Array &obj)
{
    if (obj.m_length >= 0) {
        
        delete [] this->m_space;
        this->m_length = obj.m_length;
        this->m_space = new int[this->m_length];

        for (int i = 0; i < obj.m_length; i++) {
            this->m_space[i] = obj.m_space[i];
        }

    } else {
        this->m_length = 0;
    }

    return *this;
}


bool 
Array::operator==(const Array &obj)
{
    bool ret = true;

    if (this->m_length == obj.m_length) {
        
        for (int i = 0; i < obj.m_length; i++) {
            if (this->m_space[i] != obj.m_space[i]) {
                ret = false;
                break;
            }
        }

    } else {
        ret = false;
    }

    return ret;
}

bool
Array::operator!=(const Array &obj)
{
    return (!(*this == obj));
}
