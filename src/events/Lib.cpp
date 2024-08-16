#include "Lib.h"

void MyLib_::begin() {
  
}

void MyLib_::doStuff() {
 
}

MyLib_ &MyLib_::getInstance() {
  static MyLib_ instance;
  return instance;
}

MyLib_ &MyLib = MyLib.getInstance();