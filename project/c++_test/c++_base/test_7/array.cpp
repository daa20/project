#include "array.h"

Array::Array(int length)
{
    if (length > 0) {
        m_length = length;
        m_space = new int[m_length];
    } else {
        m_length = 0;
    }
}

Array::Array(const Array &obj)
{
    if (obj.m_length >= 0) {
        this->m_length = obj.m_length;
        this->m_space = new int [this->m_length];
        for (int i = 0; i < this->m_length; i++) {
            this->m_space[i] = obj.m_space[i];
        }
    } else {
        this->m_length = 0;
    }

}

int 
Array::length(void)
{
    return m_length;
}

void
Array::setData(int index, int value)
{
    if (index < m_length) {
        m_space[index] = value;
    }
}

int 
Array::getData(int index)
{
    int ret = 0;
    if (index < m_length) {
        ret = m_space[index];
    }

    return ret;
}

void 
Array::destory(void)
{
    m_length = 0;
    delete [] m_space;
}

Array::~Array()
{
    m_length = 0;
    delete [] m_space;
}
