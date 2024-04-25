#include <iostream>
#pragma execution_character_set("utf-8")
#include <Windows.h>

using namespace std;

class BankAccount {
private:
	int accountNumber;
	double balance;
	double percentageRate;
public:
	BankAccount(int accontNumber, double Balance) {
		this->accountNumber = accontNumber;
		this->balance = Balance;
		this->percentageRate = 0.0;
	}
	// Функция для внесения средств на счет
	void dep(double deposit) {
		if (deposit > 0) {
			balance += deposit;
			cout << "Депозит пополнен. Ваш счет теперь составляет: " << balance << endl;
		}
	}
	// Функция для снятия средств со счета
	void takeMoney(double amount) {
		if (amount > 0 && amount <= balance) {
			balance -= amount;
			cout << "Вы обналичили деньги из счета. Ваш счет теперь составляет: " << balance << endl;
		}
		else
		{
			cout << "Недопустимая сумма или недостаточный баланс." << balance << endl;
		}
	}

	// Функция для получения текущего баланса
	double getBalance() const {
		return balance;
	}

	// Функция для расчета и возврата суммы процентов
	double getInterest() const {
		return balance * percentageRate * (1.0 / 12.0);
	}

	// Функция для обновления процентной ставки
	void setInterestRate(double rate) {
		percentageRate = rate;
	}

	// Функция для получения номера банковского счета
	int getAccountNumber() const {
		return accountNumber;
	}

	// Дружественная функция для перевода средств между счетами
	friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};



bool transfer(BankAccount& from, BankAccount& to, double amount) {
	if (amount > 0 && amount <= from.balance) {
		from.balance -= amount;
		to.balance += amount;
		cout << "Перевод прошел успешно. Ваш счет теперь составляет: " << from.balance
			<< ", новый баланс принимающего: " << to.balance << endl;
		return true;
	}
	else {
		cout << "Перевод не выполнен. Недостаточный баланс или неверная сумма." << endl;
		return false;
	}


}


int main() {


	SetConsoleCP(65001); // устанавливаем кодировку входящего потока данных на UTF-8
	SetConsoleOutputCP(65001); // устанавливаем кодировку исходящего потока данных на UTF-8
	// Создаем два банковских счета
	BankAccount account1(123456, 1000.0);
	BankAccount account2(654321, 2000.0);

	// Устанавливаем процентные ставки
	account1.setInterestRate(0.05);
	account2.setInterestRate(0.03);

	int choice;
	double amount;





	// Меню
	do {
		cout << "\nМеню банковского аккаунта:" << endl;
		cout << "1. Депозит" << endl;
		cout << "2. Обналичивание" << endl;
		cout << "3. Перевод" << endl;
		cout << "4. Просмотр баланса" << endl;
		cout << "5. Выход" << endl;
		cout << "Введите свой выбор: ";
		cin >> choice;


		if (!(cin >> choice)) {
			cout << "Ошибка: Неверный ввод. Пожалуйста, введите число." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}

		switch (choice) {
		case 1:
			cout << "Введите сумму для внесения депозита : ";
			cin >> amount;
			account1.dep(amount);
			break;
		case 2:
			cout << "Введите сумму для обналичивания: ";
			cin >> amount;
			account1.takeMoney(amount);
			break;
		case 3:
			cout << "Введите сумму которую хоитие перевести: ";
			cin >> amount;
			transfer(account1, account2, amount);
			break;
		case 4:
			cout << "Баланс 1 аккаунта: " << account1.getBalance() << endl;
			break;
		case 5:
			cout << "Выход из программы." << endl;
			break;
		default:
			cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
		}
	} while (choice != 5);

	return 0;
}