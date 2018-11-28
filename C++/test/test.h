#include<iostream>
#include<string>

class Person
{
private:
    int number;
    std::string name;
public:
    Person();
    ~Person();
};

Person::Person()
{
    std::cout<<"����Person"<<std::endl;
}

Person::~Person()
{
    std::cout<<"����Person"<<std::endl;
}

class A
{
private:
    int number;
    std::string name;
public:
    A();
    ~A();
};

A::A()
{
    std::cout<<"����A"<<std::endl;
}

A::~A()
{
    std::cout<<"����A"<<std::endl;
}

class Student:public Person
{
public:
    Student();
    ~Student();
};

Student::Student()
{
    std::cout<<"����Student"<<std::endl;
}

Student::~Student()
{
    std::cout<<"����Student"<<std::endl;
}

class Teacher:virtual A
{
public:
    Teacher();
    ~Teacher();
};

Teacher::Teacher()
{
    std::cout<<"����Teacher"<<std::endl;
}

Teacher::~Teacher()
{
    std::cout<<"����Teacher"<<std::endl;
}

class Me:public Teacher,virtual public Student
{
public:
    Me();
    ~Me();
};

Me::Me()
{
    std::cout<<"����Me"<<std::endl;
}

Me::~Me()
{
    std::cout<<"����Me"<<std::endl;
}
