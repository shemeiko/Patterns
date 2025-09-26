#include <iostream>
#include <string>

class Logger {
private:
    Logger() {}
    ~Logger() {}
public:
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    void operator=(Logger&&) = delete;

    static Logger& getLogger() {
        static Logger instance;
        return instance;
    }

    void log(std::string log_message) {
        std::cout << log_message << '\n';
    }
};

int main() {
    auto& logger = Logger::getLogger(); 
    std::cout << &logger << " " << &Logger::getLogger() << '\n';
    logger.log("Program successfully completed");
}