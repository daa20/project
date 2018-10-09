#include "operator.h"

void 
Operator::setOperator(char op)
{
    if ((op == '+') || (op == '-') || (op == '*') || (op == '/')) {
        m_op = op;
    } else {
        m_op = '\0';
    }
}

void 
Operator::setParameter(int p1, int p2)
{
    m_p1 = p1;
    m_p2 = p2;
}

bool
Operator::result(double &d)
{
    bool ret = true;

    switch (m_op) {
        case '+' :
            d = m_p1 + m_p2;
            break;

        case '-':
            d = m_p1 - m_p2;
            break;

        case '*':
            d = m_p1 * m_p2;
            break;

        case '/':
            if (m_p2 > -0.0001 && m_p2 < 0.0001) {
                d = 0;
                ret = false;
                return ret;
            }

            d = m_p1 / m_p2;
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}
