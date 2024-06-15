// @author: oz.atar@msmail.ariel.ac.il

#include <string>


namespace catan
{
    enum CARDTYPE{
        KNIGHT,
        VICTORY_POINT,
        ROAD_BUILDING,
        MONOPOLY,
        YEAR_OF_PLENTY
    };
    class Card
    {
        private:


        public:
            Card();
            ~Card();


            virtual CARDTYPE getType() = 0;
            virtual std::string getDescription() = 0;
            // virtual std::string icon() = 0;
            // virtual Card* clone() = 0;
    };
}