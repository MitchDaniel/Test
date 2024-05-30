#include <iostream>
#include <string>
#include <vector>

// ��������������� ���������� ������ Mediator
class Mediator;

// ��������� �������
class Colleague {
protected:
    Mediator* mediator;

public:
    explicit Colleague(Mediator* mediator) : mediator(mediator) {}

    virtual void sendMessage1(const std::string& message) const = 0;
    virtual void receiveMessage(const std::string& message) const = 0;
};

// ��������� ����������
class Mediator {
public:
    virtual void sendMessage1(const std::string& message, class Colleague* colleague) const = 0;
};

// ���������� ����� ����������
class ConcreteMediator : public Mediator {
private:
    std::vector<class Colleague*> colleagues;

public:
    void addColleague(Colleague* colleague) {
        colleagues.push_back(colleague);
    }

    void sendMessage1(const std::string& message, Colleague* sender) const override {
        // ��������� ���������� ��������� ���� ��������� ��������, ����� �����������
        for (auto colleague : colleagues) {
            if (colleague != sender) {
                colleague->receiveMessage(message);
            }
        }
    }
};

// ���������� ����� �������
class ConcreteColleague : public Colleague {
public:
    using Colleague::Colleague;

    void sendMessage1(const std::string& message) const override {
        mediator->sendMessage1(message, this);
    }

    void receiveMessage(const std::string& message) const override {
        std::cout << "Received message: " << message << std::endl;
    }
};

int main() {
    ConcreteMediator mediator;

    ConcreteColleague colleague1(&mediator);
    ConcreteColleague colleague2(&mediator);

    mediator.addColleague(&colleague1);
    mediator.addColleague(&colleague2);

    colleague1.sendMessage1("Hello from colleague1!");

    return 0;
}
