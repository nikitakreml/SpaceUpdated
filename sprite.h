// Подключаем файл строго 1 раз
// (даже если будет несколько #include)
#pragma once

#include "picture.h"




/*******************************************************
 Класс игрового объекта

 Отличается от обычной картинки (Picture) тем, что
 знает свои координаты и умеет определять коллизии (пересечения) 
 с другими спрайтами
*******************************************************/
class Sprite{
  private:
    // Картинку спрайта будем хранить здесь
    Picture pic;

  protected:
    int x = 0, y = 0;

  public:
    // При создании объекта с параметрами будет
    // вызываться конструктор Picture, принимающий путь до картинки
    // (благодаря списку инициализации)
    Sprite(std::string spriteSrc, int x = 0, int y = 0): pic(spriteSrc), x(x), y(y) {
      draw();
    }
    Sprite(){}

    // метод, отрисовывающий картинку спрайта в его координатах
    void draw(){
      pic.draw(x, y);
    }

    // метод перемещает спрайт в новые координаты
    void relocate(int x, int y){
      this->x = x;
      this->y = y;
    }

    // проверка на пересечение с другим спрайтом (коллизия)
    bool hasCollisionWith(Sprite other){
      bool colCollision = false, rowCollision = false;
      if(x + getWidth() > other.x && x < other.x + other.getWidth())
        colCollision = true;
      if(y + getHeight() > other.y && y < other.y + other.getHeight())
        rowCollision = true;

      return colCollision && rowCollision;
    }

    // если не знаешь, зачем здесь ключевое слово virtual,
    // то пока не обращай внимание. Скоро узнаешь :)
    virtual int getWidth() {return pic.getWidth();}
    virtual int getHeight() {return pic.getHeight();}

    int getX() {return x;}
    int getY() {return y;}

    void goLeft() {if(x > 1) x--;}
    void goRight() {x++;}
    void goUp() {if(y > 1) y--;}
    void goDown() {y++;}
};