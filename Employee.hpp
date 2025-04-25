#include <iostream>
#include <string>

class Employee
{
public:
    // בנאי למזהה מסוג string
    Employee(const std::string& id, int salary, int seniority)
        : string_id(id), salary(salary), seniority(seniority) {}

    // בנאי נוסף שתומך גם ב-int אם אתה עדיין רוצה לשמור תאימות
    Employee(int id, int salary, int seniority)
        : string_id(std::to_string(id)), salary(salary), seniority(seniority) {}

    ~Employee() = default;

    // פלט נוח
    friend std::ostream& operator<<(std::ostream& os, const Employee& e)
    {
        os << "ID: " << e.string_id
           << ", Salary: " << e.salary
           << ", Seniority: " << e.seniority;
        return os;
    }

    std::string getId() const { return string_id; }
    int getSalary() const { return salary; }
    int getSeniority() const { return seniority; }

private:
    std::string string_id;
    int salary;
    int seniority;
};


