// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include <string>


namespace catan
{
    enum CARDTYPE{
        MONOPOLY,
        ROAD_BUILDING,
        YEAR_OF_PLENTY,
        KNIGHT,
        VICTORY_POINT
    };
    class Card
    {
        private:


        public:
            Card() = default;
            virtual ~Card();


            virtual CARDTYPE getType() const = 0;
            virtual string getDescription() const = 0;
            // virtual std::string icon() = 0;
            virtual Card* clone() = 0;
    };
}