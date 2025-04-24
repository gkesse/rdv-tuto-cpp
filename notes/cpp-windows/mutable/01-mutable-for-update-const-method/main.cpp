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
        m_isRunMethod = true;
    }

private:
    mutable bool m_isRunMethod;
};

int main(int _argc, char **_argv)
{
    cClass oClass;
    oClass.runMethod();
    oClass.runMethod();
    return 0;
}
