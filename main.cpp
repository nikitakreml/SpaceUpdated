#include <iostream>
#include <ctime> // для функции time(), исп. для рандома
#include <vector>
#include <chrono>
#include <thread>

#include "directed_sprite.h"

using namespace std;

int getRandomInt(int min, int max){
  return min + random() % max;
}


int main() {
  TerminalDecorator::clrscr();  
  vector<Sprite> base;
  srand(time(0)); // это для рандома
  int health = 3;
  int ammo = 15;
  int score = 0; // здесь будем хранить счет
  int difficulty = 0;
  // в эту переменную будем считывать символы
  // и реагировать на ввод W, A, S, D
  char key; 
  // Очищаем терминал
  TerminalDecorator::clrscr();

  DirectedSprite player("sprites/player", 2, 30, 30);
  Sprite meteor("sprites/meteor", getRandomInt(0, 50), 1);
  Sprite bullet("sprites/bullet", 1000,1000);
  // Позволяем читать символы без нажатия Enter 
  TerminalDecorator::setNeedEnter(false);
  // Отключить вывод вводимых символов
  // (вы не видите, что печатаете в консоли)
  TerminalDecorator::setEcho(false);

  int counter = getRandomInt(2, 5);
  for(int i = 0; i < counter; i++) {
       Sprite storage("sprites/storage", getRandomInt(1, 50),  40);

       base.push_back(storage);
  } 



 
  while (true) {
    if(score % 2) {
      difficulty += 2;
    }
    cin >> key;
    // очищаем терминал
    TerminalDecorator::clrscr();     
    // рисуем следующий кадр елки
    for(int i = 0; i < counter; i++)
    {
    base[i].draw();
         if(meteor.hasCollisionWith(base[i]))
         {
          meteor.relocate(getRandomInt(0, 50), 1);
          base[i].relocate(100,100);
          health--;
         }
         if(meteor.hasCollisionWith(base[i]))
         {
          meteor.relocate(getRandomInt(0, 50), 1);
          base[i].relocate(100,100);
          health--;
         }

      }

    // рисуем подарок
    
    meteor.draw();
    // обрабатываем введенный символ,
    // чтобы понять, куда двигаться
    // странные числа - это то, что получается при вводе 
    // кириллицы (ц, Ц, ы, Ы, ф, Ф, а, А)

   

    if(tolower(key) == 'w' || key == -122 || key == -90) {
      player.goUp();
      player.goUp();
    }
    if(tolower(key) == 's' || key == -85 || key == -117) {
      player.goDown();
      player.goDown();
    }
    if(tolower(key) == 'a' || key == -92 || key == -124) {
      player.goLeft();
      player.goLeft();
      player.setDirection("left");
    }
    if(tolower(key) == 'd' || key == -78 || key == -110) {
      player.goRight();
      player.goRight();
      player.setDirection("right");
    }
    if(tolower(key) == '1' && bullet.getX() == 1000 && ammo > 0) {
      bullet.relocate(player.getX(),player.getY());
      ammo--;
    }
    bullet.goUp();
    bullet.goUp();
    bullet.goUp();
    bullet.draw();
    player.drawNext();
    //Коллизии
    
    if(bullet.hasCollisionWith(meteor))
    {
      meteor.relocate(getRandomInt(0, 50), 1);
      bullet.relocate(1000, 1000);
      score++;
      ammo++;
    }
    if(bullet.getY()<5) {
       bullet.relocate(1000, 1000);
    }
    if(player.hasCollisionWith(meteor))
    {
      meteor.relocate(getRandomInt(0, 50), 1);
      health--;
    }

    if(meteor.getY() > 50)
    {
        meteor.relocate(getRandomInt(0, 50), 1);
    } 
    meteor.goDown();


    TerminalDecorator::gotoxy(50, 1);
    // Выставляем красный фон и белый шрифт
    TerminalDecorator::setColors(TerminalDecorator::white, TerminalDecorator::red);
    // печатаем на экран счет (как результат он всегда 
    // будет печататься в позиции 50 по горизонтали и 1 по вертикали)
    cout << "Score: " << score << endl;

    TerminalDecorator::gotoxy(60, 1);
    cout << "Health: " << health << endl;

    TerminalDecorator::gotoxy(20, 1);
    cout << "Ammo: " << ammo << endl;

    if(health == 0) {
      TerminalDecorator::clrscr();  
      TerminalDecorator::gotoxy(40, 40);
      TerminalDecorator::setColors(TerminalDecorator::white, TerminalDecorator::red);
      cout << "You Lost";
      break;
    }
        if(score == 20) {
          TerminalDecorator::clrscr();  
          TerminalDecorator::gotoxy(40, 40);
          TerminalDecorator::setColors(TerminalDecorator::white, TerminalDecorator::red);
          cout << "You Won";
          break;
    }

  }

  // Возвращаем терминал в обычный режим работы.
  // (видим вводимые символы и после ввода ожидаем нажатия Enter)
  TerminalDecorator::setNeedEnter(true);
  TerminalDecorator::setEcho(true);

 


  return 0;
}