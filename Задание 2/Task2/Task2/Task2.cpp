#include <iostream>
#include <string>
#include <locale.h>

using namespace std;


class gameObject //класс "объект компьютерной игры"
{
	string name;		//название объекта

protected:

	virtual void _print() const  // механизм динамического полиморфизма (виртуальная функция)  вывода информации на экран
	{
		cout << "Имя: " << name;
	}
	gameObject() : name("Объект") {}  //конструктор без параметров 
	gameObject(const gameObject& obj) : name(obj.name) {} //конструктор копирования
	gameObject(string _name) : name(_name) {} //параметризированный конструктор
	virtual ~gameObject() { cout << "Объект компьютерной игры удален" << endl; } //виртуальный деструктор

	string getName() const  //функция получения имени
	{ 
		return name; 
	};

public:
	
	// открытая функция для вывода информации об объекте
	void print() const
	{
		cout << typeid(*this).name() << ": (";
		// вызов виртуальной функции
		// т.к. функция _print виртуальная, вызываться она будет
		// не только из текущего класса, но и из производных,
		// в зависимости от того, для какого объекта осуществляется вызов
		_print();
		cout << ")" << endl;
	}

	//чисто виртуальные функции
	virtual void move() = 0; //движение объекта
	virtual void draw() = 0; //прорисовка объекта 
};


class  character : virtual public gameObject //класс "Персонаж" унаследован от класса gameObject
{
protected:
	int healthPoints; //очки здоровья
public:
	character() : gameObject(), healthPoints(100) {} ////конструктор без параметров 
	character(const character& obj) : gameObject(obj), healthPoints(obj.healthPoints) {} //конструктор копирования
	character(string _name, int _healthPoints) //параметризированный конструктор
		: gameObject(_name), healthPoints(_healthPoints) {}
	~character() { cout << "Персонаж удален" << endl; } //деструктор

protected:
	// виртуальная функция _print переопределяется в производном классе
	void _print() const
	{
		gameObject::_print(); //вызываем виртуальную функцию базового класса
		cout << ", очки здоровья: " << healthPoints;
	}
};


class humanoid : public character  //класс "человекоподобный персонаж" унаследован от класса character
{
	float intelligence; //интеллект 
public:
	humanoid() : character(), gameObject(), intelligence(1.0) {} //конструктор без параметров 
	humanoid(const humanoid& obj) : character(obj), gameObject(obj), intelligence(obj.intelligence) {} //конструктор копирования
	humanoid(string _name, int _healthPoints, float _intelligence) //параметризированный конструктор
		: character(_name, _healthPoints), gameObject(_name), intelligence(_intelligence) {}
	~humanoid() { cout << "Человекоподобный персонаж удален" << endl; } //деструктор

	void move() override //чисто виртуальная функция move(), которая переопределена в производном классе 
	{
		cout << "Человекоподобный персонаж " << getName() << " бегает" << endl;
	}
	void draw() override //чисто виртуальная функция draw(), которая переопределена в производном классе 
	{
		cout << "Человекоподобный персонаж " << getName() << " отрисован" << endl;
	}

	// виртуальная функция _print переопределяется в производном классе
	void _print() const
	{
		character::_print(); //вызываем виртуальную функцию базового класса
		cout << ", интеллект: " << intelligence;
	}
};

class  magic : virtual public gameObject //класс "Магия" унаследован от класса gameObject
{
	string superPower; //Сверхспособность 
public:
	magic() : gameObject(), superPower("Бессмертие") {} ////конструктор без параметров 
	magic(const magic& obj) : gameObject(obj), superPower(obj.superPower) {} //конструктор копирования
	magic(string _name, string _superPower) //параметризированный конструктор
		: gameObject(_name), superPower(_superPower) {}
	~magic() { cout << "Магия вне Хогвартса запрещена" << endl; } //деструктор

protected:
	// виртуальная функция _print переопределяется в производном классе
	void _print() const
	{
		gameObject::_print(); //вызываем виртуальную функцию базового класса
		cout << ", сверхспособность: " << superPower;
	}
};

class magicCharacter : public character, public magic
{
	int manna;
public:
	magicCharacter() : character(), magic(), gameObject(), manna(100) {} //конструктор без параметров 
	magicCharacter(const magicCharacter& obj) : character(obj), magic(obj), gameObject(obj), manna(obj.manna) {} //конструктор копирования
	magicCharacter(string _name, int _healthPoints, string _superPower, int _manna) //параметризированный конструктор
		: character(_name, _healthPoints), magic(_name, _superPower), gameObject(_name), manna(_manna) {}
	~magicCharacter() { cout << "Волшебный персонаж удален" << endl; } //деструктор

	void move() override //чисто виртуальная функция move(), которая переопределена в производном классе 
	{
		cout << "Волшебный персонаж " << getName() << " левитирует" << endl; //ТУТ ВИРТУАЛЬНОЕ НАСЛЕДОВАНИЕ (мы не указываем область видимости character:: или magic::)
	}
	void draw() override //чисто виртуальная функция draw(), которая переопределена в производном классе 
	{
		cout << "Волшебный персонаж "<< getName() << " отрисован" << endl; //ТУТ ВИРТУАЛЬНОЕ НАСЛЕДОВАНИЕ (мы не указываем область видимости character:: или magic::)
	}

protected:
	// виртуальная функция _print переопределяется в производном классе
	void _print() const
	{
		magic::_print(); //вызываем виртуальную функцию базового класса
		cout << ", очки здоровья: " << healthPoints;
		cout << ", манна: " << manna;
	}
};

class  magicItem : public magic
{
	int enchantment; //зачарованность предмета
public:
	magicItem() : magic(), gameObject(), enchantment(100) {} //конструктор без параметров 
	magicItem(const magicItem& obj) :  magic(obj), gameObject(obj), enchantment(obj.enchantment) {} //конструктор копирования
	magicItem(string _name, string _superPower, int _enchantment) //параметризированный конструктор
		:  magic(_name, _superPower), gameObject(_name), enchantment(_enchantment) {}
	~magicItem() { cout << "Волшебный предмет удален" << endl; } //деструктор

	void move() override //чисто виртуальная функция move(), которая переопределена в производном классе 
	{
		cout << "Волшебный предмет " << getName() << " летает " << endl;
	}
	void draw() override //чисто виртуальная функция draw(), которая переопределена в производном классе 
	{
		cout << "Волшебный предмет " << getName() << " отрисован" << endl;
	}

protected:
	// виртуальная функция _print переопределяется в производном классе
	void _print() const
	{
		magic::_print(); //вызываем виртуальную функцию базового класса
		cout << ", зачарованность: " << enchantment;
	}
};

class  mythicalAnimal : public gameObject
{
	int charges; //заряды суперсилы
public:
	mythicalAnimal() : gameObject(), charges(5) {} //конструктор без параметров 
	mythicalAnimal(const mythicalAnimal& obj) : gameObject(obj), charges(obj.charges) {} //конструктор копирования
	mythicalAnimal(string _name, int _charges) //параметризированный конструктор
		: gameObject(_name), charges(_charges) {}
	~mythicalAnimal() { cout << "Мифическое животное удалено" << endl; } //деструктор

	void move() override //чисто виртуальная функция move(), которая переопределена в производном классе 
	{
		cout << "Мифическое животное " << getName() << " бороздит просторы" << endl;
	}
	void draw() override //чисто виртуальная функция draw(), которая переопределена в производном классе 
	{
		cout << "Мифическое животное " << getName() << " отрисовано" << endl;
	}

protected:
	// виртуальная функция _print переопределяется в производном классе
	void _print() const
	{
		gameObject::_print(); //вызываем виртуальную функцию базового класса
		cout << ", заряды суперсилы: " << charges;
	}
};


int main()
{
	setlocale(LC_ALL, "Rus"); //подключаем русский язык 
	humanoid human("Вещий Олег", 100, 1.5);
	human.print();
	human.draw();
	human.move();
	cout << endl;

	magicCharacter magicCh("Саволла Всемогучий", 1000, "Перемещение объектов взягдом", 500);
	magicCh.print();
	magicCh.draw();
	magicCh.move();
	cout << endl;

	magicItem magicItem("Зеркало Беккера", "Возвращение в прошлое", 1000);
	magicItem.print();
	magicItem.draw();
	magicItem.move();
	cout << endl;

	mythicalAnimal animal("Чудо-юдо", 7);
	animal.print();
	animal.draw();
	animal.move();
	cout << endl;

	system("pause"); //пауза
}

