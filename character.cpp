#include <iostream>
#include <string>
#include <vector>

using namespace std;
/* 
Write a Character class holding a raw pointer member (e.g. an Equipment*).
Implement all 5: constructor, destructor, copy ctor, copy assignment, move ctor, move assignment.
Print from inside each to see which gets called when you put Characters in a std::vector.
Deliberately remove the copy constructor first, reproduce the double-free/shallow-copy bug, then fix it.
*/
class Equipment
{
private:
    string _name;

public:
    explicit Equipment(string name) : _name(std::move(name))
    {
        cout << "equipment contr is called for " << _name << endl;
    }

    const string &name()
    {
        return _name;
    }
};

class Character
{
private:
    string _name;
    Equipment *_weapon;

public:
    /* Constructor */
    Character(string name, string weapon_name) : _name(name), _weapon(new Equipment(weapon_name))
    {
        cout << "Constr is called " << endl;
    };

    /* Copy Constructor */
    Character(const Character &other)
    {
        cout << "Copy Constr is called" << endl;
        _weapon = new Equipment(other._weapon->name());
        _name = other._name;
    }
    /* Copy Assignment Operator */
    Character &operator=(const Character &other)
    {
        if (this == &other)
            return *this;
        cout << "Copy Assignment is called" << endl;
        _weapon = new Equipment(other._weapon->name());
        _name = other._name;
        return *this;
    }

    /* Move Constructor -- . If your move constructor could throw, the vector falls back to copying during reallocation instead — because if a move threw partway through relocating elements, the vector could end up in a corrupted, half-moved state with no way to safely roll back. A noexcept move gives the "strong exception guarantee" the vector needs to use it safely for this internal reshuffling.*/
    Character(Character &&other) noexcept
    {
        cout << " move constructor is called " << endl;
        _weapon = other._weapon;
        _name = other._name;
        other._weapon = nullptr;
        _name = "";
    }

    /* Move Assignment Operator */
    Character &operator=(Character &&other) noexcept
    {
        if (this == &other)
            return *this;
        delete _weapon;
        _weapon = other._weapon;
        _name = other._name;
        other._weapon = nullptr;
        cout << " move assignment operator is called " << endl;
        return *this;
    }

    /* Destructor */
    ~Character()
    {
        cout << "destructor is called " << endl;
        delete _weapon;
    }
};

int main()
{
    vector<Character> characters;
   /*    
   Character character("yash", "knife");
    
    // both value are lvalue -- copies
    characters.push_back(character);
    characters.emplace_back(character);
    
    // equipment contr is called for knife
    // Constr is called 
    // Copy Constr is called
    // equipment contr is called for knife
    // Copy Constr is called
    // equipment contr is called for knife
    //  move constructor is called -- vector is reallocating size 
    // destructor is called +4 
    cout << "----------------------" <<endl;
    */

    // both values are rvalue -- temporary 
    // push back demands a build objected whereas emplace build the object inplace in the vector slot
    characters.push_back(Character("vinay", "sword"));
    // equipment contr is called for sword
    // Constr is called 
    // move constructor is called -- extra move is called
    // destructor is called 
    // destructor is called 
    characters.emplace_back("emmy" ,"hammer");
    // equipment contr is called for hammer
    // Constr is called  -- no move constructor is called as the object creation happens directly in vector slot
    // destructor is called 
    return 0;
}