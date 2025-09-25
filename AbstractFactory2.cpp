#include <iostream>
#include <memory>

class AbstractPaymentSystem {
public:
    virtual std::string Invoice() const = 0;
};

class CardPaymentSystem : public AbstractPaymentSystem {};
class ElectronicPaymentSystem : public AbstractPaymentSystem {};
class CryptoCurrencyPaymentSystem : public AbstractPaymentSystem {};

class VisaProvider : public CardPaymentSystem {
public:
    std::string Invoice() const override {
        return "payment created by Visa";
    }
};

class MastercardProvider : public CardPaymentSystem {
public:
    std::string Invoice() const override {
        return "payment created by Mastercard";
    }
};

class PayPalProvider : public ElectronicPaymentSystem {
public:
    std::string Invoice() const override {
        return "payment created by PayPal";
    }
};

class GooglePayProvider : public ElectronicPaymentSystem {
public:
    std::string Invoice() const override {
        return "payment created by GooglePay";
    }
};

class StripeProvider : public CryptoCurrencyPaymentSystem{
public:
    std::string Invoice() const override {
        return "payment created by Stripe";
    }
};

enum class CardPaymentSystems { Visa = 1, Mastercard };
enum class ElectronicPaymentSystems { PayPal = 1, GooglePay };
enum class CryptoCurrencyPaymentSystems { Stripe = 1 };

class CardPaymentSystemFactory {
public:
    std::unique_ptr<AbstractPaymentSystem> useProvider(CardPaymentSystems provider) const {
        switch(provider) {
            case CardPaymentSystems::Visa: return std::make_unique<VisaProvider>();
            case CardPaymentSystems::Mastercard: return std::make_unique<VisaProvider>();
            default: return nullptr;
        }
    }
};

class ElectronicPaymentSystemFactory {
public:
    std::unique_ptr<AbstractPaymentSystem> useProvider(ElectronicPaymentSystems provider) const {
        switch(provider) {
            case ElectronicPaymentSystems::PayPal: return std::make_unique<PayPalProvider>();
            case ElectronicPaymentSystems::GooglePay: return std::make_unique<GooglePayProvider>();
            default: return nullptr;
        }
    }
};

class CryptocurrencyPaymentSystemFactory {
public:
    std::unique_ptr<AbstractPaymentSystem> useProvider(CryptoCurrencyPaymentSystems provider) const {
        switch(provider) {
            case CryptoCurrencyPaymentSystems::Stripe: return std::make_unique<StripeProvider>();
            default: return nullptr;
        }
    }
};

int main() {
    using std::cout;
    auto cardFactory = std::make_unique<CardPaymentSystemFactory>();
    cout << cardFactory->useProvider(CardPaymentSystems::Visa)->Invoice() << '\n';

    return 0;
}