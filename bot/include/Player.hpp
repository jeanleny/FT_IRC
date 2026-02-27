#pragma once

#include <string>

typedef enum roomId
{
	TAVERN,
	CORRIDOR,
	ROOM1,
	PIT,
    ANTECHAMBER,
} e_roomId;


class Item
{
    
    public :
    
    Item();
    Item(std::string name, int dmg);
    ~Item();
	std::string getName();
	int			getDmg();
    
    private :
    
    std::string _name;
    int         _damage;
};

class Player
{
    
    public:
    
    Player();
    ~Player();
    
    e_roomId    	getRoom() const;
    void        	setRoom(e_roomId room);
    void			setItem(Item item);
    Item			getItem();
    std::string		getItemName();
    int             getItemDmg();
    void            setAlive(bool state);
    
    private:

        e_roomId    _room;
        bool        _alive;
        Item        _item;
};
