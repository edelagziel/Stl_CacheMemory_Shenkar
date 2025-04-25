#include <iostream>
#include <map>
#include <memory>
#include <exception>
#include <vector>

template<typename K,typename V>
class CasheMmorey
{

public:
    CasheMmorey()
    {
       
    }
    ~CasheMmorey()
    {

    }

    void add (const K& key, const V& value)
    {
        auto Temp = std::make_shared<K>(key);

        if (Maim_memory.find(Temp) != Maim_memory.end()) {
            throw std::runtime_error("DuplicateKeyException");
        }
       
        Maim_memory.insert(std::pair<std::shared_ptr<K>,V>(Temp,value));
    } 

    void erase(const K& key)
    {
        for (auto it = Maim_memory.begin(); it != Maim_memory.end(); ++it) {
            if (*(it->first) == key) {
                Maim_memory.erase(it);
                return;
            }
        }
        throw std::runtime_error("ObjectNotExistException");
    }


    void Print()
    {
        std::cout << "📋 Printing all employees:\n";
        for (const auto& pair : Maim_memory)
            std::cout << *(pair.first) << " -> " << pair.second << std::endl;
    }


    std::shared_ptr<V> get(const K& key)
    {
        // חיפוש בקאש
        for (auto it = cache_memory.begin(); it != cache_memory.end(); )
        {
            auto sp = it->first.lock(); // ננסה להפוך ל-shared_ptr זמני
            if (sp)
            {
                if (*sp == key)
                {
                    std::cout << "In_Cache" << std::endl;
                    return std::make_shared<V>(it->second); // מחזיר עותק כמצביע חכם
                }
                ++it;
            }
            else
            {
                it = cache_memory.erase(it); // מנקה קאש שפג תוקפו
            }
        }
    
        // אם לא נמצא בקאש – נבדוק בזיכרון הראשי
        for (auto it = Maim_memory.begin(); it != Maim_memory.end(); ++it)
        {
            if (*(it->first) == key)
            {
                std::cout << "In_Main" << std::endl;
    
                cache_memory[it->first] = it->second; // מוסיף לקאש
                return std::make_shared<V>(it->second); // מחזיר עותק כמצביע
            }
        }
    
        return nullptr; // לא נמצא בכלל
    }

    std::vector<V> getCacheValues()const
    { 
        std::vector<V> cache_Values; 
        
        for (const auto& pair : cache_memory) {
            // נבדוק אם ה־weak_ptr עדיין בתוקף
            if (auto sp = pair.first.lock()) {
                // אם כן, נוסיף את הערך מסוג V
                cache_Values.push_back(pair.second);
            }
        }
    
        return cache_Values; // יחזיר את כל הערכים התקפים מהקאש
    }
    
    
  

    



    
    

    


private:
    std::map<std::shared_ptr<K>,V> Maim_memory;//The Big Map Include All The Element 
    std::map<std::weak_ptr<K>, V, std::owner_less<std::weak_ptr<K>>> cache_memory;
   
   


};


