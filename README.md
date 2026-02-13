*This project has been created as part of the 42 curriculum by [tobourge](https://profile.intra.42.fr/users/tobourge) and [lperis](https://profile.intra.42.fr/users/lperis)*

# Description:
In this project called FT_IRC, our goal is to create a server where several clients can communicate.
The whole program works under the IRC norm(see [IRC-NORM](https://www.rfc-editor.org/rfc/rfc2812)), this norm homogenize all IRC, allows every clients-software to talks with each other and their own difference, (nc, HexChat...).
The server allows clients to create channels, manage them by setting specific modes, add topics, restrict members...

# Instructions:
The program takes two argument on launching
- The server port (6697 is a irc reserved one)
- The server password. This will be typed by the client upon joining.

In order to use our IRC server :
1. **Client Registration**
		First, lets connect to the server by using basic registration command on our client.
	- PASS with the server previously set on the server launching
	- USER to set the username
	- NICK to set the nickname (which will be used to authenticate you most of the time )
2. **Channel creation**
		Now that we are connected, we can use JOIN to create a channel.
		JOIN take an argument with a '#'.
		If the channel doesn't exist it will be created, otherwise the channel is joined.
3. **Communication**
		To talk with each other, clients uses the PRIVMSG command.
		PRIVMSG take two parameters, the addressee, and the message content.
		If the the first parameter is a channel, this message will be sent to everybody in channel. Otherwise, the client has a private discussion with the addressee.
4. **Operators Command and Mode**
		In channels, certain rules can be added to organize it.
		These are set with the MODE command :
		**MODE**
			Mode changes the channel's mode.
			It can take several argument.
			The signs '+' and '-' to add or remove the mode
			The flags we want
			The parameters argument if the flag needs it.
			**Flags** :
				-i : This will only allow invited clients
				-t : This will restrict the topic changement to the operators
				-k : Takes one keyword parameter, set a password to the channel
				-o : Take one client as parameter, makes him operator
				-l : take one number as parameter, set a client limit to the channel.
		**KICK** 
			Takes the nickname target as the parameter. This will eject the targeted client.
		**INVITE**
			Takes the nickname's target as the parameter. This will allow the client to join a channel with the invite mode set.
		**TOPIC**
			Takes the new topic as parameter, change the actual topic.
5. **OTHER COMMAND**
		**PART**
			This makes you quit the channel
		**NICK**
			Takes the new nickname as parameter and change it.
	

# Resources
This projects puts us in an uncomfortable position with the network/socket/protocol system.
The Beejs guide is absolutely wonderful to demystify it see [Beej's guide](https://beej.us/guide/bgnet/html/split-wide/) 

For the IRC Norm, numeric replies, command code
[IRC-2812](https://www.rfc-editor.org/rfc/rfc2812)
[IRC-PROTOCOL](https://mathieu-lemoine.developpez.com/tutoriels/irc/protocole/?page=page-5)
[IRC-MODERN](https://ircdocs.horse/)


# Project Norm

##CLASS FORMAT

Private members must be written with '_' :
```c++
private :
  int  _value;
```

Public elements must be ordered as follows :

```c++
public :

  // CANONICAL ELEMENTS
  Constructor();
  OverloadConstructor();
  ~Destructor();
  [...]

  // GETTERS - SETTERS
  int    getVar1(); const
  int    getVar2(); const
  void   setVar1(int);
  void   setVar2(int);
  [...]

  // SPECIFIC METHODS
  void method1();
  void method2();
  [...]
```

Functions and variables must written with the Lower Camel Case format.

Functions names must start with a verb
```c++
int addCLient(int fd);
char *serverClient;
```
