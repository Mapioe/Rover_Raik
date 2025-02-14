const int ForwardPinLeft = 3;   // Контакт для управления двигателем вперед
const int BackwardPinLeft = 5;  // Контакт для управления двигателем в обратном направлении
const int ForwardPinRight = 10;
const int BackwardPinRight = 9;

const int HorizontalPin = A1;  //Контакт для приёма сигналов от джойстика 
const int VerticalPin = A2;

const int JoyStickButton = A3;
bool DebugMod = false;  // Специальный дебаг режим для запоминания движения

float Rotation = 4.6666; //Rotation = Максимальная скорость вращения двигателя.
int Lwheel = 150; // Lwheel = Расстояния между колесами. Функция поворота на 90 градусов. В мм?
int Dwheel = 50; //Dwheel = Диаметр колеса.

void setup() {
  pinMode(ForwardPinLeft, OUTPUT);
  pinMode(BackwardPinRight, OUTPUT);
  pinMode(ForwardPinLeft, OUTPUT);
  pinMode(BackwardPinRight, OUTPUT);
  pinMode(JoyStickButton, INPUT_PULLUP);
}

void loop() {
  {
    int ButtonCount = 0;
     if (digitalRead(JoyStickButton) == LOW ){
      ButtonCount++;
      delay(500);
    } 
    if (ButtonCount == 3){ //Если кнопка нажата 3 раза включает режим дебага (Запоминания маршрута)
      DebugMod = true;
    }
    else if (ButtonCount == 6){
      ButtonCount = 0;
      DebugMod = false;
    }
  }
do{
int HorizontalJoyStick = analogRead(HorizontalPin); 
int VerticalJoyStick = analogRead(VerticalPin);
int HorizontalJoyStickPos = 0;
int VerticalJoyStickPos = 0;
if (HorizontalJoyStick > 450 and HorizontalJoyStick < 550){ // <- Код с хабра для вычисления позиции джойстика.
  HorizontalJoyStickPos = 0;
} 
if (HorizontalJoyStick >= 550){
  HorizontalJoyStickPos = map(HorizontalJoyStick, 550, 1023, 0, 5); // Последнее число 255?
}
if (HorizontalJoyStick <= 450){
  HorizontalJoyStickPos = map(HorizontalJoyStick, 450, 0, 0, -5);
}
if (VerticalJoyStick > 450 and VerticalJoyStick < 550){ 
  VerticalJoyStickPos = 0;
}
if (VerticalJoyStick >= 550){
  VerticalJoyStickPos = map(VerticalJoyStick, 550, 1023, 0, 5);
}
if (VerticalJoyStick <= 450){
  VerticalJoyStickPos = map(VerticalJoyStick, 450, 0, 0, -5);
  
}
int A = ((HorizontalJoyStickPos - 512) / 2) - 1; //Используем костыль вместо велосипеда.
int HorizontalPosToMotor = abs(A);
int B = ((VerticalJoyStickPos - 512) / 2) - 1;
int VerticalPosToMotor = abs(B);
int Speed = (((HorizontalPosToMotor / 255) * Rotation) * Dwheel);
  if (VerticalJoyStickPos > 512){
analogWrite(ForwardPinLeft, VerticalPosToMotor);
analogWrite(ForwardPinRight, VerticalPosToMotor);
}
  else{
analogWrite(BackwardPinLeft, VerticalPosToMotor); 
analogWrite(BackwardPinRight, VerticalPosToMotor);
}
  if (HorizontalJoyStickPos > 512){
analogWrite(ForwardPinLeft,HorizontalPosToMotor);
delay(Speed / (0.25 * Lwheel) * 1000); 
analogWrite(ForwardPinLeft, HorizontalPosToMotor);
analogWrite(ForwardPinRight, HorizontalPosToMotor);
}
  else{
analogWrite(ForwardPinRight,HorizontalPosToMotor);
delay(Speed / (0.25 * Lwheel) * 1000); 
analogWrite(ForwardPinLeft, HorizontalPosToMotor);
analogWrite(ForwardPinRight,HorizontalPosToMotor);
}
int * ForwardPinLeftArray;
ForwardPinLeftArray = (VerticalPosToMotor);
int * BackwardPinLeftArray;
BackwardPinLeftArray = (VerticalPosToMotor);
int * ForwardPinRightArray;
ForwardPinRightArray = (VerticalPosToMotor);
int * BackwardPinRightArray;
BackwardPinLeftArray = (VerticalPosToMotor);
  } while (DebugMod == true);
}