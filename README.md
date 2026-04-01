# 2PlayerUno
# Person1(Card Classes)
## You have to create 4 classes
1. Card , the base class
2. Numbercard , derived from Card
3. ActionCard , derived from Card
4. WildCard , derived from Card

Now the details of each class ,
---
### **Card**
#### Attributes:
+ color : std::string(protected)
+ symbol : std::string(protected)
#### Methods(all public):
+ virtual void display() const , here display according to color and symbol, **it should not print newline**.
+ Parametrized constructor of card
+ std::string get_color() const
+ std::string get_symbol() const
+ void set_color(std::string s)
+ virtual ~ Card(){}
---
### **NumberCard**
#### Attributes:
+ None
#### Methods(all public):
+ Parametrised constructor using chaining to initialize the color and symbol of base class
+ virtual ~NumberCard(){}
---
### **ActionCard**
#### Attributes:
+ None
#### Methods(all public):
+ Parametrised constructor using chaining to initialize the color and symbol of base class
+ virtual ~ActionCard(){}
---
### WildCard
#### Attributes:
+ None
#### Methods(all public):
+ **a constructor that only takes symbol as input and initialises color as "Multicolor" and symbol as input for the base class** , prototype would be something like WildCard(std::string s1)
+ **virtual void display() const override** for this just virtually overide the function display from base class and use display to display for different cases like when say the card symbol is wil or when card symbol is wild +4 or say when the color of card has went from multicolor to actual color
    - basically these 3 cases :
        1. Multicolor (default)
        2. Wild with chosen color
        3. Wild +4 with chosen color
+ virtual ~WildCard(){}

### Thats all for Person 1
---
# Person 2(Deck class)
## You have to create 1 class which is : **Deck** , the one which will be used to play
### I recommend you to check the classic uno cards on wikipedia before you start making the deck class
### Now the details of class 

### Deck
#### Attributes:
+ std::vector<Card *> d; {strictly go with vectors as arrays would make it very complex}
#### Methods:
+ Constructor **Deck()**
## Deck constructor
+ This constructor above is very important as this will make the whole deck so you work is almost all about this.
+ So just see the offcial uno cards and for first 80 cards make the number cards double time as you can see in official wiki of uno cards and for that:
#### Use these only 
``` cpp
std::vector<std::string> colors{"Red","Yellow","Green","Blue"};
std::vector<std::string> symbols{"0","1","2","3","4","5","6","7","8","9"};
```
+ To make all possible cards and each should be double (see official uno cards in wiki)
+ And use dynamic memory alloaction to do so
+ Now for remaining action cards use :
#### These only
``` cpp
std::vector<std::string> actionsymbols{"Skip","Reverse","+2"};
```
+ to make all posible action cards
+ and finally make all wild cards using symbols **"Wild"** and **"Wild+4"** and symbol would of course be multicolor by default (read WildCard class default constructor above for the same)
#### Use dynamic memory allocation for creating all cards and you have to assign each card to vetor d using .push_back();
#### Now Deck constructor is complete
### Back to methods
#### Methods:
+ **void shuffle()** :this should shuffle the deck using random seed (leave the body for this empty if you want , i will handle this one).
+ Card *remove_top_card() : should remove top card from deck by using **.pop_back()** in vector d and return the card that was popped.
+ Card *top_card() : return top card i.e the pointer to backmost card of vector d as we are considering back of vector to be top , cuz return type is Card * and not just Card.
+ void add_card(Card *c) : add a card to back of d vector i.e the deck using .push_back() method
+ int count(): return size of deck .i.e the size od d vector(d vector is the one in attributes)
### Thats all for Person2
---
# Person 3(Person class)
## This is named person to show the cards in the hand of a person so this class also basically stores Card * objects just like deck but is different
### So again the details :
### Atributes:
+ std::vector<Card *> d;
### Methods(all public):
+ bool valid_card(const Card *c1,const Card *c2) : checks if c1 card can be played on c2 card (just chec if symbol or color is same and exceptions are wild cards , like wild cards are always playable)
+ bool any_playable_card(Card *c) : check if any card in our hand .i.e the d vector can be played or no and the card in parameter is the one to be compared with for playing(that is the discard pile card)
+ void show_cards() : print all cards of person(i.e all cards in vector d) in a structured manner , also showing indices with each card
+ void add_card(Card *c) : add a card * to back of person hand cards using .push_back()
+ int number_of_cards() : return number of cards in hand i.e size of vector d.
+ Card *play_card(int i) : this should remove the card on inputted index and return the same deleted card , nasically on playing card the card goes from person's hand but you have to return it too
+ Card *card_index(int i) : return card at i index , do check for invalid entry tough and return nullptr for invalid entry.
---
# Person 4 
## This person is gonna take the main() containing game logic (I will handle this)
---
# Finally
# Integration Notes(some logics used in main to give you an idea of how your classes would be used and some notes)

- Deck, Person, and Card classes must work with raw pointers (Card*)
- Deck will provide cards using remove_top_card()
- Person will store cards using add_card()
- Game logic will use:
    - valid_card()
    - play_card()
    - any_playable_card()

- No class should print extra newlines unless specified
- Do NOT delete cards (game logic will manage lifecycle), Memory cleanup will be handled later / ignored for now
- Do not change prototypes unless absolutely necessary (inform before changing)