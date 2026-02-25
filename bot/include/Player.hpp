#pragma once

#include <string>

typedef enum roomId
{
	TAVERN,
	CORRIDOR,
	ROOM1,
	PIT,
} e_roomId;


class Item
{
    
    public :
    
    Item();
    Item(std::string name, int dmg);
    ~Item();
    
    
    private :
    
    std::string _name;
    int         _damage;
};

class Player
{
    
    public:
    
        Player();
        ~Player();

        e_roomId    getRoom() const;
        void        setRoom(e_roomId room);
    
    private:

        e_roomId    _room;
        Item        _item;
};