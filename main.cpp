#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
std::string color_code(std::string color){
    if(color == "Red") return "\033[31m";
    if(color == "Green") return "\033[32m";
    if(color == "Yellow") return "\033[33m";
    if(color == "Blue") return "\033[34m";
    return "\033[0m";
}
class Card{
protected:
    std::string color;
    std::string symbol;
public:
    virtual void display() const{
        std::cout << color_code(color) << symbol << " of " << color << "\033[0m ";
    }
    Card(std::string s1,std::string s2)
        :color{s1},symbol{s2}{}
    std::string get_color() const{
        return color;
    }
    std::string get_symbol() const{
        return symbol;
    }
    void set_color(std::string s){
        color=s;
    }
    virtual ~Card(){}
};
class NumberCard:public Card{
public:
    NumberCard(std::string s1,std::string s2)
        :Card{s1,s2}{}
    virtual ~NumberCard(){}
};
class ActionCard:public Card{
public:
    ActionCard(std::string s1,std::string s2)
        :Card{s1,s2}{}
    virtual ~ActionCard(){}
};
class WildCard:public Card{
public:
    WildCard(std::string s1)
        :Card{"Multicolor",s1}{}
    virtual void display() const override{
        if(symbol=="Wild"&&color!="Multicolor"){
            std::cout << color_code(color) << "Wild card of " << color << "\033[0m ";
        }
        else if(symbol=="Wild +4"&&color!="Multicolor"){
            std::cout << color_code(color) << "Wild +4 of " << color << "\033[0m ";
        }
        else if(symbol=="Wild"&&color=="Multicolor"){
            std::cout << "\033[31mW\033[0m" << "\033[32mI\033[0m"<< "\033[33mL\033[0m"<< "\033[34mD\033[0m " << "card";
        }
        else{
            std::cout << "\033[31mW\033[0m" << "\033[32mI\033[0m"<< "\033[33mL\033[0m"<< "\033[34mD\033[0m " << "+4";
            //std::cout << "Wild +4";
        }
    }
    virtual ~WildCard(){}
};
class Deck{
protected:
    std::vector<Card *> d;
public:
    Deck(){
        std::vector<std::string> colors{"Red","Yellow","Green","Blue"};
        std::vector<std::string> symbols{"0","1","2","3","4","5","6","7","8","9"};
        for(std::string i: colors){
            for(std::string j: symbols){
                if(j=="0"){
                    Card *c=new NumberCard{i,j};
                    d.push_back(c);
                }else{
                    Card *c=new NumberCard{i,j};
                    Card *c1=new NumberCard{i,j};
                    d.push_back(c);
                    d.push_back(c1);
                }
            }
        }
        std::vector<std::string> actionsymbols{"Skip","Reverse","+2"};
        for(std::string i: colors){
            for(std::string j: actionsymbols){
                Card *c=new ActionCard{i,j};
                Card *c1=new ActionCard{i,j};
                d.push_back(c);
                d.push_back(c1);
            }
        }
        for(int i=0;i<4;i+=1){
            Card *c=new WildCard{"Wild"};
            Card *c1=new WildCard{"Wild +4"};
            d.push_back(c);
            d.push_back(c1);
        }
    }
    void shuffle(){
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(d.begin(),d.end(),g);
    }
    Card *remove_top_card(){
        Card *c=d.back();
        d.pop_back();
        return c;
    }
    Card *top_card(){
        return d.back();
    }
    void add_card(Card *c){
        d.push_back(c);
    }
    int count(){
        return d.size();
    }
};
class Person{
protected:
    std::vector<Card *> d;
public:
    bool valid_card(const Card *c1,const Card *c2){
        if(c1->get_symbol()=="Wild"||c1->get_symbol()=="Wild +4"){
            return true;
        }
        else if(c1->get_symbol()==c2->get_symbol()||c1->get_color()==c2->get_color()){
            return true;
        }
        else{
            return false;
        }
    }
    bool any_playable_card(Card *c){
        bool found=false;
        for(const Card *i:d){
            if(i->get_symbol()=="Wild"||i->get_symbol()=="Wild +4"){
                found=true;
            }
        }
        if(found==true){
            return true;
        }
        for(Card *i:d){
            if(i->get_symbol()==c->get_symbol()||i->get_color()==c->get_color()){
                return true;
            }
        }
        return false;
    }
    void show_cards(){
        std::cout << "[";
        for(int i=0;i<d.size();i+=1){
            std::cout << i << " -> ";
            d[i]->display();
            if(i!=d.size()-1){
                std::cout << " , ";
            }
        }
        std::cout << "]";
    }
    void add_card(Card *c){
        d.push_back(c);
    }
    int number_of_cards(){
        return d.size();
    }
    Card *play_card(int i){
        int a=0;
        auto it=d.begin();
        while(true){
            if(a==i){
                Card *c=d[i];
                d.erase(it);
                return c;
                break;
            }
            a+=1;
            it++;
        }
    }
    Card *card_index(int i){
        if(i>=d.size()){
            return nullptr;
        }
        else{
            return d[i];
        }
    }
};
void reassigndeck(Deck &d,std::vector<Card *> &discard){
    while(!(discard.empty())){
        d.add_card(discard.back());
        discard.pop_back();
    }
    d.shuffle();
    discard.push_back(d.remove_top_card());
    std::cout << "Deck reassigned due to less cards" << std::endl;
    std::cout << "Now the top most card on discard pile :";
    discard.back()->display();
    std::cout << std::endl;
}
void uno(){
    std::cout << "===========" << std::endl;
    std::cout << "    UNO   " << std::endl;
    std::cout << "===========" << std::endl;
}
int main(){
    Deck deck;
    deck.shuffle();
    Person p1;
    Person p2;
    for(int i=0;i<7;i+=1){
        p1.add_card(deck.remove_top_card());
    }
    for(int i=0;i<7;i+=1){
        p2.add_card(deck.remove_top_card());
    }
    std::vector<Card *> discard_pile;
    discard_pile.push_back(deck.remove_top_card());
    bool can_play=true;
    while(true){
        if(p2.number_of_cards()==1){
            uno();
            std::cout << "The bot has won the game" << std::endl;
            break;
        }
        if(p1.number_of_cards()==1){
            uno();
            std::cout << "You have won the game" << std::endl;
            break;
        }
        if(deck.count()==0){
            reassigndeck(deck,discard_pile);
        }
        std::cout << "Your cards :" << std::endl;
        p1.show_cards();
        std::cout << std::endl;
        std::cout << "Bot cards :Unknown , It has " << p2.number_of_cards() << " cards " <<  std::endl;
        std::cout << "Card on discard pile :";
        discard_pile.back()->display();
        std::cout << std::endl;
        if(can_play){
            std::cout << "=============" << std::endl;
            std::cout << "Your Turn" << std::endl;
            std::cout << "=============" << std::endl;
            bool will_play=false;
            if(p1.any_playable_card(discard_pile.back())){
                std::cout << "You have playable card(s)" << std::endl;
                std::cout << "Pick one card to play using the index number provided :";
                int picked=0;
                while(true){
                    std::cin >> picked;
                    if((picked<p1.number_of_cards())&&(p1.valid_card(p1.card_index(picked),discard_pile.back()))){
                        break;
                    }
                    else{
                        std::cout << "Enter valid index of card and card sould be playable :";
                        continue;
                    }
                }
                discard_pile.push_back(p1.play_card(picked));
                will_play=true;
            }
            else{
                if(deck.count()<1){
                    reassigndeck(deck,discard_pile);
                }
                std::cout << "You dont have any playable cards , so you have to pick from deck" << std::endl;
                std::cout << "Picked up card :";
                deck.top_card()->display();
                std::cout << std::endl;
                p1.add_card(deck.remove_top_card());
                if(p1.valid_card(p1.card_index(p1.number_of_cards()-1),discard_pile.back())){
                    std::cout << "The picked up card is vaild , would you play it(1->yes , 0-> no) : ";
                    int checker=0;
                    while(true){
                        std::cin >> checker;
                        if(checker==0||checker==1){
                            break;
                        }
                        else{
                            std::cout << "Enter valid input :";
                            continue;
                        }
                    }
                    if(checker==1){
                        will_play=true;
                        discard_pile.push_back(p1.play_card(p1.number_of_cards()-1));
                    }
                }
            }
            if(will_play==true){
                if(discard_pile.back()->get_symbol()=="Skip"||discard_pile.back()->get_symbol()=="Reverse"){
                    std::cout << "The bot's Turn is skipped " << std::endl << std::endl;
                    continue;
                }
                else if(discard_pile.back()->get_symbol()=="+2"){
                    if(deck.count()<2){
                        reassigndeck(deck,discard_pile);
                    }
                    for(int i=0;i<2;i+=1){
                        p2.add_card(deck.remove_top_card());
                    }
                    std::cout << "The bot has drawn 2 cards and its turn has been missed" << std::endl << std::endl;
                    continue;
                }
                else if(discard_pile.back()->get_symbol()=="Wild"){
                    std::cout << "Enter the color to be set for the wild card (0-> red,1-> yellow ,2->green ,3 ->blue) :";
                    int selection=0;
                    while(true){
                        std::cin >> selection;
                        if(selection<4){
                            break;
                        }
                        else{
                            std::cout << "Enter one of given valid numbers :";
                            continue;
                        }
                    }
                    if(selection==0){
                        discard_pile.back()->set_color("Red");
                        std::cout << "The color of the top card on discard pile has ben changed to Red" << std::endl;
                    }
                    else if(selection==1){
                        discard_pile.back()->set_color("Yellow");
                        std::cout << "The color of the top card on discard pile has ben changed to Yellow" << std::endl;
                    }
                    else if(selection==2){
                        discard_pile.back()->set_color("Green");
                        std::cout << "The color of the top card on discard pile has ben changed to Green" << std::endl;
                    }
                    else{
                        discard_pile.back()->set_color("Blue");
                        std::cout << "The color of the top card on discard pile has ben changed to Blue" << std::endl;
                    }
                }
                else if(discard_pile.back()->get_symbol()=="Wild +4"){
                    if(deck.count()<4){
                        reassigndeck(deck,discard_pile);
                    }
                    for(int i=0;i<4;i+=1){
                        p2.add_card(deck.remove_top_card());
                    }
                    std::cout << "Enter the color to be set for the wild card (0-> red,1-> yellow ,2->green ,3 ->blue) :";
                    int selection=0;
                    while(true){
                        std::cin >> selection;
                        if(selection<4){
                            break;
                        }
                        else{
                            std::cout << "Enter one of given valid numbers :";
                            continue;
                        }
                    }
                    if(selection==0){
                        discard_pile.back()->set_color("Red");
                        std::cout << "The color of the top card on discard pile has ben changed to Red" << std::endl;
                    }
                    else if(selection==1){
                        discard_pile.back()->set_color("Yellow");
                        std::cout << "The color of the top card on discard pile has ben changed to Yellow" << std::endl;
                    }
                    else if(selection==2){
                        discard_pile.back()->set_color("Green");
                        std::cout << "The color of the top card on discard pile has ben changed to Green" << std::endl;
                    }
                    else{
                        discard_pile.back()->set_color("Blue");
                        std::cout << "The color of the top card on discard pile has ben changed to Blue" << std::endl;
                    }
                    std::cout << "The bot has missed its turn and has drawn four cards" << std::endl << std::endl;
                    continue;
                }
                else{
                }
            }
        }
        if(p1.number_of_cards()==1){
            uno();
            std::cout << "You have won the game" << std::endl;
            break;
        }
        std::cout << "=============" << std::endl;
        std::cout << "Bot's turn" << std::endl;
        std::cout << "=============" << std::endl;
        bool bot_play=false;
        if(p2.any_playable_card(discard_pile.back())){
            bool number=false;
            bool action=false;
            bool wild=false;
            for(int i=0;i<p2.number_of_cards();i+=1){
                if(p2.valid_card(p2.card_index(i),discard_pile.back())){
                    if(p2.card_index(i)->get_symbol()=="Wild"||p2.card_index(i)->get_symbol()=="Wild +4"){
                        wild=true;
                    }
                    else if(p2.card_index(i)->get_symbol()=="Skip"||p2.card_index(i)->get_symbol()=="Reverse"||p2.card_index(i)->get_symbol()=="+2"){
                        action=true;
                    }
                    else{
                        number=true;
                    }
                }
            }
            if(number==true){
                for(int i=0;i<p2.number_of_cards();i+=1){
                    if((p2.valid_card(p2.card_index(i),discard_pile.back()))&&(p2.card_index(i)->get_symbol()!="Wild"&&p2.card_index(i)->get_symbol()!="Wild +4"&&p2.card_index(i)->get_symbol()!="Skip"&&p2.card_index(i)->get_symbol()!="Reverse"&&p2.card_index(i)->get_symbol()!="+2")){
                        discard_pile.push_back(p2.play_card(i));
                        bot_play=true;
                        break;
                    }
                }
            }
            else if(number==false && action==true){
                for(int i=0;i<p2.number_of_cards();i+=1){
                    if((p2.valid_card(p2.card_index(i),discard_pile.back()))&&(p2.card_index(i)->get_symbol()=="Skip"||p2.card_index(i)->get_symbol()=="Reverse"||p2.card_index(i)->get_symbol()=="+2")){
                        discard_pile.push_back(p2.play_card(i));
                        bot_play=true;
                        break;
                    }
                }
            }
            else{
                for(int i=0;i<p2.number_of_cards();i+=1){
                    if((p2.valid_card(p2.card_index(i),discard_pile.back()))&&(p2.card_index(i)->get_symbol()=="Wild"||p2.card_index(i)->get_symbol()=="Wild +4")){
                        discard_pile.push_back(p2.play_card(i));
                        bot_play=true;
                        break;
                    }
                }
            }
        }
        else{
            std::cout << "Bot has no playable card , it is picking up from deck" << std::endl;
            if(deck.count()<1){
                reassigndeck(deck,discard_pile);
            }
            p2.add_card(deck.remove_top_card());
            if(p2.valid_card(p2.card_index(p2.number_of_cards()-1),discard_pile.back())){
                std::cout << "The picked up card by the bot is playable" << std::endl;
                if(p2.card_index(p2.number_of_cards()-1)->get_symbol()=="Wild"||p2.card_index(p2.number_of_cards()-1)->get_symbol()=="Wild +4"){
                    std::cout << "The Bot chooses not to play the card" << std::endl;
                }
                else{
                    std::cout << "The bot chooses to play the obtained card" << std::endl;
                    discard_pile.push_back(p2.play_card(p2.number_of_cards()-1));
                    bot_play=true;
                }
            }
        }
        if(bot_play){
            std::cout << "Thw Bot has played :";
            discard_pile.back()->display();
            std::cout << std::endl;
            if(discard_pile.back()->get_symbol()=="Skip"||discard_pile.back()->get_symbol()=="Reverse"){
                    std::cout << "Your Turn is skipped " << std::endl << std::endl;
                    can_play=false;
                    continue;
            }
            else if(discard_pile.back()->get_symbol()=="+2"){
                if(deck.count()<2){
                    reassigndeck(deck,discard_pile);
                }
                for(int i=0;i<2;i+=1){
                    p1.add_card(deck.remove_top_card());
                }
                std::cout << "You have drawn 2 cards and your turn has been missed" << std::endl << std::endl;
                can_play=false;
                continue;
            }
            else if(discard_pile.back()->get_symbol()=="Wild"){
                int red=0,yellow=0,green=0,blue=0;
                for(int i=0;i<p2.number_of_cards();i+=1){
                    if(p2.card_index(i)->get_color()=="Red"){
                        red+=1;
                    }
                    else if(p2.card_index(i)->get_color()=="Yellow"){
                        yellow+=1;
                    }
                    else if(p2.card_index(i)->get_color()=="Green"){
                        green+=1;
                    }
                    else if(p2.card_index(i)->get_color()=="Blue"){
                        blue+=1;
                    }
                }
                std::vector<int> c{red,yellow,green,blue};
                int max=*max_element(c.begin(),c.end());
                if(red==max){
                    discard_pile.back()->set_color("Red");
                    std::cout << "Now the discard pile wild card color has changed to Red" << std::endl;
                }
                else if(yellow==max){
                    discard_pile.back()->set_color("Yellow");
                    std::cout << "Now the discard pile wild card color has changed to Yellow" << std::endl;
                }
                else if(green==max){
                    discard_pile.back()->set_color("Green");
                    std::cout << "Now the discard pile wild card color has changed to Green" << std::endl;
                }
                else{
                    discard_pile.back()->set_color("Blue");
                    std::cout << "Now the discard pile wild card color has changed to Blue" << std::endl;
                }
                can_play=true;
                continue;
            }
            else if(discard_pile.back()->get_symbol()=="Wild +4"){
                if(deck.count()<4){
                    reassigndeck(deck,discard_pile);
                }
                for(int i=0;i<4;i+=1){
                    p1.add_card(deck.remove_top_card());
                }
                std::cout << "You had to pick up 4 cards from deck and have missed a turn" << std::endl;
                int red=0,yellow=0,green=0,blue=0;
                for(int i=0;i<p2.number_of_cards();i+=1){
                    if(p2.card_index(i)->get_color()=="Red"){
                        red+=1;
                    }
                    else if(p2.card_index(i)->get_color()=="Yellow"){
                        yellow+=1;
                    }
                    else if(p2.card_index(i)->get_color()=="Green"){
                        green+=1;
                    }
                    else if(p2.card_index(i)->get_color()=="Blue"){
                        blue+=1;
                    }
                }
                std::vector<int> c{red,yellow,green,blue};
                int max=*max_element(c.begin(),c.end());
                if(red==max){
                    discard_pile.back()->set_color("Red");
                    std::cout << "Now the discard pile wild card color has changed to Red" << std::endl;
                }
                else if(yellow==max){
                    discard_pile.back()->set_color("Yellow");
                    std::cout << "Now the discard pile wild card color has changed to Yellow" << std::endl;
                }
                else if(green==max){
                    discard_pile.back()->set_color("Green");
                    std::cout << "Now the discard pile wild card color has changed to Green" << std::endl;
                }
                else{
                    discard_pile.back()->set_color("Blue");
                    std::cout << "Now the discard pile wild card color has changed to Blue" << std::endl;
                }
                can_play=false;
                continue;
            }
            else{
                can_play=true;
                continue;
            }
        }
    }
    return 0;
}