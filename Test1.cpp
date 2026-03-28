#include <iostream>
#include <random>
using namespace std;




class Mood{

    int risk;    // will use to decide if the guy is satiffied with his price or will risk more

    public:
        int numgen(){
            mt19937 gen(time(0));
            uniform_int_distribution<> range(1, 50);
            return range(gen);
        }

        int numgen(int low, int high){    // multiple return statemensts for differnt mood levels
            mt19937 gen(time(0));
            uniform_int_distribution<> range(low, high);
            return range(gen);
        }

};

class Item{
    int Current_Val;
    int True_val;

    public:
        Item(){}
        Item(int Cval, int Tval){
            Current_Val = Cval;
            True_val = Tval;
        }

    friend class Merchant;
    friend class Buyer;
    friend class Market;
    friend class Negotitate;
};

class NPC{
    protected:
        int money;
        int Knowledge; // factor for knowing the True val price
        Mood M;
};

class Buyer: public NPC{
    int b_price;
    int b_goal;
    int n_price;                                        // when doing negotiations this will change
    
    public:
        Buyer():b_price(0),n_price(0){}

        void item_price(Item x){
            b_price = x.Current_Val;

            n_price = x.Current_Val;
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

        void item_price(Item x){
            s_price = x.True_val;

            n_price = s_price;
            lowest_price = s_price - ((M.numgen()*s_price)/100); // willing to sell if buy price is 20% lower then true val
        }


    friend class Negotitate;
};

class Negotitate{
    
    public:                                         // how am i to call this call in  main ?
        void which_item(Buyer &b,Merchant &m,Item x)
        {
            m.item_price(x);
            b.item_price(x);
        }


        void Haggle(Buyer &b,Merchant &m)
        {
            cout << "Buyer Buy price: " << b.b_price << endl;
            cout << "Merchant Sell Price: " << m.s_price << endl;

            // buyer
            cout << "Buyer goal: " << b.b_goal << endl;

            //Merchant
            cout << "Merchant Lowest: " << m.lowest_price << endl;
        };


};

class Market{
    void search();
    void researc();
};


int main(){
    Item Box(50,100);
    Merchant M;
    Buyer B;
    Negotitate N;

    N.which_item(B,M,Box);
    N.Haggle(B,M);



}

