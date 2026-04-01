#include <iostream>
#include <random>
using namespace std;

mt19937 gen(time(0));   // number generator base this is from what it will gen random numbers

struct emotions{
    int Patrice_meter;
    int Patience_val;
};

struct Mood{

    emotions e;
    
    public:
        int numgen(){
            uniform_int_distribution<> range(1, 50);
            return range(gen);
        }

        int numgen(int low, int high){    // multiple return statemensts for differnt mood levels
            uniform_int_distribution<> range(low, high);
            return range(gen);
        }

};

class Item{
    int Produce_Val;
    int Current_Val;
    int True_val;

    public:
        Item(){}
        Item(int Pval,int Cval, int Tval){
            Produce_Val = Pval;
            Current_Val = Cval;
            True_val = Tval;
        }

    friend class Merchant;
    friend class Buyer;
    friend class Market;

};

class NPC{
    protected:
        Mood M;
        int money;
        int Knowledge; // factor for knowing the True val price
};

class Buyer: public NPC{
    int b_price;
    int b_goal;
    int n_price;                                        // when doing negotiations this will change
    
    public:
        Buyer():b_price(0),n_price(0){}

        void item_price(Item x)
        {
            b_price = x.Current_Val;

            b_goal = b_price - ((M.numgen()*b_price)/100);     // random how much willing to buy for
        };



    friend class Negotitate;
};

class Merchant: public NPC{
    int buy_price;
    int lowest_price;
    int s_price;
    int n_price;

    
    public:
        Merchant(): lowest_price(0),s_price(0),n_price(0){}

        void item_price(Item x)
        {
            s_price = x.True_val;
            buy_price = x.Produce_Val;

            lowest_price = s_price - ((M.numgen()*s_price)/100); // willing to sell if buy price is 20% lower then true val
        }


    friend class Negotitate;
};

class Negotitate{

    Buyer* B;
    Merchant* S;

    int Active_price = 0;   // current price negotiated


    public:                                         // how am i to call this call in  main ?

        // other sutff

        void n_price_update()
        {
            B->n_price = Active_price;
            S->n_price = Active_price;
        }

        void inqure(Buyer &b,Merchant &m,Item x)
        {
            m.item_price(x);
            b.item_price(x);
            
            B = &b;
            S = &m;
            
            cout << "Price " << S->s_price << endl;
            Active_price = S->s_price;
            n_price_update();
        }

        void thoughts(){
            cout << "\n";

            cout << "Buyer" << endl;
            cout << "Buyer Know Price: " << B->b_price << endl
            << "Buyer Goal: " <<  B->b_goal << endl;

            cout <<"Active price: "<<Active_price << endl;

            cout << "Merchant" << endl;
            cout <<"Merchant Buy Price: "<< S->buy_price << endl 
            <<"Merchant Sell Price: " << S->s_price << endl
            << "Merchant Lowest Price: " << S->lowest_price << endl;

            cout << "\n"; 
        }
        
        // Buyer func

        void offer(){
            cout << "\nCostly...\n";
            Active_price = B->b_goal;
            n_price_update();
        }

        void Buy(){
            cout << "\nI'll Take it\n";
        }

        void Sell_p_To_know_p()
        {
            if (B->n_price > B->b_price && B->n_price > B->b_goal)
            {
                if (Active_price > 2*B->b_goal) {cout << "\nI'm Out" << endl; }
                else{ offer(); }
            }
            if (B->n_price < B->b_price && B->n_price < B->b_goal){Buy();}
        }


        // Merchant func

        
};

class Market{
    void search();
    void researc();
};


int main(){
    Item Box(10,100,140);
    Merchant M;
    Buyer B;
    Negotitate N;

    N.inqure(B,M,Box);
    N.thoughts();
    cout << "-------------------------------------------------";
    N.Sell_p_To_know_p();
    cout << "-------------------------------------------------";
    N.thoughts();
    

}

