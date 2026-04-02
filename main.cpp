class Deck {
    vector <Card *> d; 
public:
    Deck() {
        vector <string> colors = {"Red", "Yellow", "Green", "Blue"};
        vector <string> symbols = {"0","1","2","3","4","5","6","7","8","9"};
        for (string s : symbols) {
            if (s == "0") {
                for (string c : colors) {
                    d.push_back(new NumberCard(c, s));
                }
            }
            else {
                for (string c : colors) {
                    for (int i = 1; i <= 2; i++) {
                        d.push_back(new NumberCard(c, s));
                    }
                } 
            }
        }
        vector <string> actionSymbols = {"Skip", "Reverse", "+2"};
        for (string c : colors) {
            for (string as : actionSymbols) {
                for (int i = 1; i <= 2; i++) {
                    d.push_back(new ActionCard(c, as));
                }
            }
        }
        vector <string> wildSymbols = {"Wild", "Wild +4"};
        for (string ws : wildSymbols) {
            for (int i = 1; i <= 4; i++) {
                d.push_back(new WildCard(ws));
            }
        }
    }
    void shuffle(){
        random_device rd;
        mt19937 gen(rd());
        std::shuffle(d.begin(), d.end(), gen);
    }
    Card* remove_top_Card(){
        Card* c = d.back();
        d.pop_back();
        return c;
    }
    Card *top_card(){
        return d.back();
    }
    void add_card(Card *c){
        d.push_back(c);
    }
    int count() {
        return d.size();
    }
};//     Deck class code if want any change in code first let me know