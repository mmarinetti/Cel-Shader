#pragma once
class COrgans
{
public:
    COrgans(void);
    virtual ~COrgans(void);

    void Draw();
    void DrawWindpipe();
    void DrawLungs();
    void DrawHeart();
    void DrawStomach();
    void DrawLiver();


private:
    void Draw(int i);
};

