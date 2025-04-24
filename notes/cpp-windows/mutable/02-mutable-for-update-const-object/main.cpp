#include <iostream>

class cClass
{
public:
    cClass() : m_isRunMethod(false) {}
    ~cClass() = default;
    void runMethod() const
    {
        std::cout << "[Info]:Je suis la methode A."
                  << "|isRunMethod=" << m_isRunMethod
                  << std::endl;
    }

public:
    mutable bool m_isRunMethod;
};

int main(int _argc, char **_argv)
{
    const cClass oClass;
    oClass.runMethod();
    oClass.m_isRunMethod = true;
    oClass.runMethod();
    return 0;
}
