#include <iostream>
#include <fstream>
#include <string>
#include "CasheMmorey.hpp"
#include "Employee.hpp"

// הצהרות
void Save(const CasheMmorey<std::string, Employee>& db, const std::string& filename);
void Load(CasheMmorey<std::string, Employee>& db, const std::string& filename);

int main()
{
    CasheMmorey<std::string, Employee> db;

    std::cout << "📥 Loading initial data from emps (1).bin...\n";
    Load(db, "emps (1).bin");

    std::cout << "💾 Saving it as emps.bin for further use...\n";
    Save(db, "emps.bin");

    // מחיקות או עדכונים לדוגמה
    db.erase("C89012");
    db.add("NEW1", Employee("NEW1", 9999, 9));

    std::cout << "\n📋 After modifications:\n";
    db.Print();

    std::cout << "\n💾 Saving updated data to emps.bin...\n";
    Save(db, "emps.bin");

    return 0;



}

void Save(const CasheMmorey<std::string, Employee>& db, const std::string& filename)
{
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "❌ Failed to open file for writing\n";
        return;
    }

    for (const auto& pair : db.getCacheValues())
    {
        std::string id = pair.getId();
        uint8_t length = id.size();
        int salary = pair.getSalary();
        int seniority = pair.getSeniority();

        out.write(reinterpret_cast<char*>(&length), 1);
        out.write(id.c_str(), length);
        out.write(reinterpret_cast<char*>(&salary), sizeof(salary));
        out.write(reinterpret_cast<char*>(&seniority), sizeof(seniority));
    }

    out.close();
    std::cout << "📁 Saved to file successfully.\n";
}

void Load(CasheMmorey<std::string, Employee>& db, const std::string& filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "❌ Failed to open file for reading\n";
        return;
    }

    while (true)
    {
        uint8_t idLength;
        if (!in.read(reinterpret_cast<char*>(&idLength), 1)) break;

        std::string id(idLength, '\0');
        if (!in.read(&id[0], idLength)) break;

        int salary = 0, seniority = 0;
        if (!in.read(reinterpret_cast<char*>(&salary), sizeof(salary))) break;
        if (!in.read(reinterpret_cast<char*>(&seniority), sizeof(seniority))) break;

        db.add(id, Employee(id, salary, seniority));
        std::cout << "📥 Loaded: ID=" << id << ", Salary=" << salary << ", Seniority=" << seniority << std::endl;
    }

    in.close();
    std::cout << "📁 Finished loading file.\n";
}
