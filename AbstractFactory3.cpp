#include <iostream>
#include <memory>
#include <string>
#include <utility>

class AbstractPaymentSystem {
public:
    virtual std::string Invoice() const = 0;
    virtual ~AbstractPaymentSystem() = default;
};

class CardPaymentSystem : public AbstractPaymentSystem {};
class ElectronicPaymentSystem : public AbstractPaymentSystem {};

class VisaProvider : public CardPaymentSystem {
public:
    std::string Invoice() const override { return "The payment had been created by Visa"; };
};

class MastercardProvider : public CardPaymentSystem {
public:
    std::string Invoice() const override { return "The payment had been created by Mastercard"; };
};

class PayPalProvider : public ElectronicPaymentSystem {
public:
    std::string Invoice() const override { return "The payment had been created by PayPal"; };
};

enum class CardPaymentSystems : uint8_t { Visa = 1, Mastercard, };
enum class ElectronicPaymentSystems : uint8_t { PayPal = 1, };

class AbstractPaymentSystemFactory {
public:
    virtual std::unique_ptr<AbstractPaymentSystem> useProvider(int provider) const = 0;
};

class CardPaymentSystemFactory : public AbstractPaymentSystemFactory {
public:
    std::unique_ptr<AbstractPaymentSystem> useProvider(int provider) const override {
        switch((CardPaymentSystems)provider) {
            case CardPaymentSystems::Visa: return std::make_unique<VisaProvider>();
            case CardPaymentSystems::Mastercard: return std::make_unique<MastercardProvider>();
            default: return nullptr;
        }
    };
};

class ElectronicPaymentSystemFactory : public AbstractPaymentSystemFactory {
public:
    std::unique_ptr<AbstractPaymentSystem> useProvider(int provider) const override {
        switch((ElectronicPaymentSystems)provider) {
            case ElectronicPaymentSystems::PayPal: return std::make_unique<PayPalProvider>();
            default: return nullptr;
        }
    };
};

int main() {
    using std::cout;
    auto cardFactory = std::make_unique<CardPaymentSystemFactory>();
    cout << cardFactory->useProvider((int)CardPaymentSystems::Visa)->Invoice() << '\n';
    cout << cardFactory->useProvider((int)CardPaymentSystems::Mastercard)->Invoice() << '\n';

    return 0;
}