#ifndef PASSWORD_CORE_H
#define PASSWORD_CORE_H

#include <string>

class PasswordCore {
public:
    std::string generate_password(int length) const;
};

#endif // PASSWORD_CORE_H
