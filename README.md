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
