#include <iostream>
#include <string>
#include <locale.h>

using namespace std;


class gameObject //����� "������ ������������ ����"
{
	string name;		//�������� �������

protected:

	virtual void _print() const  // �������� ������������� ������������ (����������� �������)  ������ ���������� �� �����
	{
		cout << "���: " << name;
	}
	gameObject() : name("������") {}  //����������� ��� ���������� 
	gameObject(const gameObject& obj) : name(obj.name) {} //����������� �����������
	gameObject(string _name) : name(_name) {} //������������������� �����������
	virtual ~gameObject() { cout << "������ ������������ ���� ������" << endl; } //����������� ����������

	string getName() const  //������� ��������� �����
	{ 
		return name; 
	};

public:
	
	// �������� ������� ��� ������ ���������� �� �������
	void print() const
	{
		cout << typeid(*this).name() << ": (";
		// ����� ����������� �������
		// �.�. ������� _print �����������, ���������� ��� �����
		// �� ������ �� �������� ������, �� � �� �����������,
		// � ����������� �� ����, ��� ������ ������� �������������� �����
		_print();
		cout << ")" << endl;
	}

	//����� ����������� �������
	virtual void move() = 0; //�������� �������
	virtual void draw() = 0; //���������� ������� 
};


class  character : virtual public gameObject //����� "��������" ����������� �� ������ gameObject
{
protected:
	int healthPoints; //���� ��������
public:
	character() : gameObject(), healthPoints(100) {} ////����������� ��� ���������� 
	character(const character& obj) : gameObject(obj), healthPoints(obj.healthPoints) {} //����������� �����������
	character(string _name, int _healthPoints) //������������������� �����������
		: gameObject(_name), healthPoints(_healthPoints) {}
	~character() { cout << "�������� ������" << endl; } //����������

protected:
	// ����������� ������� _print ���������������� � ����������� ������
	void _print() const
	{
		gameObject::_print(); //�������� ����������� ������� �������� ������
		cout << ", ���� ��������: " << healthPoints;
	}
};


class humanoid : public character  //����� "���������������� ��������" ����������� �� ������ character
{
	float intelligence; //��������� 
public:
	humanoid() : character(), gameObject(), intelligence(1.0) {} //����������� ��� ���������� 
	humanoid(const humanoid& obj) : character(obj), gameObject(obj), intelligence(obj.intelligence) {} //����������� �����������
	humanoid(string _name, int _healthPoints, float _intelligence) //������������������� �����������
		: character(_name, _healthPoints), gameObject(_name), intelligence(_intelligence) {}
	~humanoid() { cout << "���������������� �������� ������" << endl; } //����������

	void move() override //����� ����������� ������� move(), ������� �������������� � ����������� ������ 
	{
		cout << "���������������� �������� " << getName() << " ������" << endl;
	}
	void draw() override //����� ����������� ������� draw(), ������� �������������� � ����������� ������ 
	{
		cout << "���������������� �������� " << getName() << " ���������" << endl;
	}

	// ����������� ������� _print ���������������� � ����������� ������
	void _print() const
	{
		character::_print(); //�������� ����������� ������� �������� ������
		cout << ", ���������: " << intelligence;
	}
};

class  magic : virtual public gameObject //����� "�����" ����������� �� ������ gameObject
{
	string superPower; //���������������� 
public:
	magic() : gameObject(), superPower("����������") {} ////����������� ��� ���������� 
	magic(const magic& obj) : gameObject(obj), superPower(obj.superPower) {} //����������� �����������
	magic(string _name, string _superPower) //������������������� �����������
		: gameObject(_name), superPower(_superPower) {}
	~magic() { cout << "����� ��� ��������� ���������" << endl; } //����������

protected:
	// ����������� ������� _print ���������������� � ����������� ������
	void _print() const
	{
		gameObject::_print(); //�������� ����������� ������� �������� ������
		cout << ", ����������������: " << superPower;
	}
};

class magicCharacter : public character, public magic
{
	int manna;
public:
	magicCharacter() : character(), magic(), gameObject(), manna(100) {} //����������� ��� ���������� 
	magicCharacter(const magicCharacter& obj) : character(obj), magic(obj), gameObject(obj), manna(obj.manna) {} //����������� �����������
	magicCharacter(string _name, int _healthPoints, string _superPower, int _manna) //������������������� �����������
		: character(_name, _healthPoints), magic(_name, _superPower), gameObject(_name), manna(_manna) {}
	~magicCharacter() { cout << "��������� �������� ������" << endl; } //����������

	void move() override //����� ����������� ������� move(), ������� �������������� � ����������� ������ 
	{
		cout << "��������� �������� " << getName() << " ����������" << endl; //��� ����������� ������������ (�� �� ��������� ������� ��������� character:: ��� magic::)
	}
	void draw() override //����� ����������� ������� draw(), ������� �������������� � ����������� ������ 
	{
		cout << "��������� �������� "<< getName() << " ���������" << endl; //��� ����������� ������������ (�� �� ��������� ������� ��������� character:: ��� magic::)
	}

protected:
	// ����������� ������� _print ���������������� � ����������� ������
	void _print() const
	{
		magic::_print(); //�������� ����������� ������� �������� ������
		cout << ", ���� ��������: " << healthPoints;
		cout << ", �����: " << manna;
	}
};

class  magicItem : public magic
{
	int enchantment; //�������������� ��������
public:
	magicItem() : magic(), gameObject(), enchantment(100) {} //����������� ��� ���������� 
	magicItem(const magicItem& obj) :  magic(obj), gameObject(obj), enchantment(obj.enchantment) {} //����������� �����������
	magicItem(string _name, string _superPower, int _enchantment) //������������������� �����������
		:  magic(_name, _superPower), gameObject(_name), enchantment(_enchantment) {}
	~magicItem() { cout << "��������� ������� ������" << endl; } //����������

	void move() override //����� ����������� ������� move(), ������� �������������� � ����������� ������ 
	{
		cout << "��������� ������� " << getName() << " ������ " << endl;
	}
	void draw() override //����� ����������� ������� draw(), ������� �������������� � ����������� ������ 
	{
		cout << "��������� ������� " << getName() << " ���������" << endl;
	}

protected:
	// ����������� ������� _print ���������������� � ����������� ������
	void _print() const
	{
		magic::_print(); //�������� ����������� ������� �������� ������
		cout << ", ��������������: " << enchantment;
	}
};

class  mythicalAnimal : public gameObject
{
	int charges; //������ ���������
public:
	mythicalAnimal() : gameObject(), charges(5) {} //����������� ��� ���������� 
	mythicalAnimal(const mythicalAnimal& obj) : gameObject(obj), charges(obj.charges) {} //����������� �����������
	mythicalAnimal(string _name, int _charges) //������������������� �����������
		: gameObject(_name), charges(_charges) {}
	~mythicalAnimal() { cout << "���������� �������� �������" << endl; } //����������

	void move() override //����� ����������� ������� move(), ������� �������������� � ����������� ������ 
	{
		cout << "���������� �������� " << getName() << " �������� ��������" << endl;
	}
	void draw() override //����� ����������� ������� draw(), ������� �������������� � ����������� ������ 
	{
		cout << "���������� �������� " << getName() << " ����������" << endl;
	}

protected:
	// ����������� ������� _print ���������������� � ����������� ������
	void _print() const
	{
		gameObject::_print(); //�������� ����������� ������� �������� ������
		cout << ", ������ ���������: " << charges;
	}
};


int main()
{
	setlocale(LC_ALL, "Rus"); //���������� ������� ���� 
	humanoid human("����� ����", 100, 1.5);
	human.print();
	human.draw();
	human.move();
	cout << endl;

	magicCharacter magicCh("������� ����������", 1000, "����������� �������� �������", 500);
	magicCh.print();
	magicCh.draw();
	magicCh.move();
	cout << endl;

	magicItem magicItem("������� �������", "����������� � �������", 1000);
	magicItem.print();
	magicItem.draw();
	magicItem.move();
	cout << endl;

	mythicalAnimal animal("����-���", 7);
	animal.print();
	animal.draw();
	animal.move();
	cout << endl;

	system("pause"); //�����
}

