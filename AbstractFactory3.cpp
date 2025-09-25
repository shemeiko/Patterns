#include <iostream>
#include <memory>
#include <string>

class AbstractPayment {
public:
    virtual std::string GetInvoice() const = 0; 
    virtual ~AbstractPayment() = default;
};

class AbstractTransaction {
public:
    virtual std::string Status() const = 0;
    virtual ~AbstractTransaction() = default;
};

class VisaPayment : public AbstractPayment {
public:
    std::string GetInvoice() const override {
        return "[Visa]: Payment has been created by Visa";
    }
};

class MastercardPayment : public AbstractPayment {
public:
    std::string GetInvoice() const override {
        return "[Mastercard]: Payment has been created by Mastercard";
    }
};

class VisaTransaction : public AbstractTransaction {
public:
    std::string Status() const override {
        return "[Visa]: Transactions had been logged!";
    }
};

class MastercardTransaction : public AbstractTransaction {
public:
    std::string Status() const override {
        return "[Mastercard]: Transactions had been logged!";
    }
};

class AbstractPaymentProviderFactory {
public:
    virtual std::unique_ptr<AbstractPayment> CreatePayment() const = 0;
    virtual std::unique_ptr<AbstractTransaction> CreateTransaction() const = 0;
    virtual ~AbstractPaymentProviderFactory() = default;
};

class VisaPaymentProviderFactory : public AbstractPaymentProviderFactory {
public:
    std::unique_ptr<AbstractPayment> CreatePayment() const override {
        return std::make_unique<VisaPayment>();
    }
    std::unique_ptr<AbstractTransaction> CreateTransaction() const override {
        return std::make_unique<VisaTransaction>();
    }
};

class MastercardPaymentProviderFactory : public AbstractPaymentProviderFactory {
public:
    std::unique_ptr<AbstractPayment> CreatePayment() const override {
        return std::make_unique<MastercardPayment>();
    }
    std::unique_ptr<AbstractTransaction> CreateTransaction() const override {
        return std::make_unique<MastercardTransaction>();
    }
};

void ClientCode(const AbstractPaymentProviderFactory& factory) {
    using std::cout;
    std::cout << "------Testing code------" << '\n';
    auto payment = factory.CreatePayment();
    auto transaction = factory.CreateTransaction();
    std::cout << payment->GetInvoice() << '\n';
    std::cout << transaction->Status() << "\n\n";
}

int main() {
    std::unique_ptr<AbstractPaymentProviderFactory> factory = std::make_unique<VisaPaymentProviderFactory>();
    ClientCode(*factory);
    factory = std::make_unique<MastercardPaymentProviderFactory>();
    ClientCode(*factory);

    return 0;
}