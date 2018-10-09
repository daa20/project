#ifndef _OPERATOR_H_
#define _OPERATOR_H_

class Operator {
    private:
        char    m_op;
        int     m_p1;
        int     m_p2;
    public:
        void setOperator(char op);
        void setParameter(int p1, int p2);
        bool result(double &d);
};


#endif
