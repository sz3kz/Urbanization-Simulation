#pragma once
class Coordinates {
    Coordinates(int x,int y);
    //Coordinates();
    public:
    int getX();
    int getY();
    virtual ~Coordinates() = default;
    private:
    int x;
    int y;
};
