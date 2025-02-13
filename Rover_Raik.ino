const int ForwardPinLeft = 3;   // Контакт для управления двигателем вперед
const int BackwardPinLeft = 5;  // Контакт для управления двигателем в обратном направлении
const int ForwardPinRight = 10;
const int BackwardPinRight = 9;

const int HorizontalPin = A0;  //Контакт для приёма сигналов от джойстика 
const int VerticalPin = A1;

const int JoyStickButton = 2;
bool DebugMod = false;  // Специальный дебаг режим для запоминания движения
int ButtonCount = 0;


void setup() {
  pinMode(ForwardPinLeft, OUTPUT);
  pinMode(BackwardPinRight, OUTPUT);
  pinMode(ForwardPinLeft, OUTPUT);
  pinMode(BackwardPinRight, OUTPUT);
  pinMode(JoyStickButton, INPUT_PULLUP);
  JoyStickButtonStage = digitalRead(JoyStickButton);
}

void loop() {
  {
    if (JoyStickButtonStage == LOW){
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
  {
int HorizontalJoyStick = analogRead(HorizontalPin); 
int VerticalJoyStick = analogRead(VerticalPin);
if (HorizontalJoyStick > 450 and HorizontalJoyStick < 550){ // <- Код с хабра для вычисления позиции джойстика.
  HorizontalJoyStickPos = 0;                               // Производить запись, если дебаг режим.
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
 }
  
  int abs(HorizontalPosToMotor) = ((HorizontalJoyStickToPos - 512) / 2); 
  int abs(VerticalPosToMotor) = ((VerticalJoyStickToPos - 512) / 2);
  int Speed = (((HorizontalPosToMotor / 255) * Rotation) * Dw); //Dw = Диаметр колеса. Rotation = Максимальная скорость вращения двигателя.

  do {
    if (VerticalJoyStickPos > 512){
  analogWrite(ForwardPinLeft, VerticalJoyStickPos);
  analogWrite(ForwardPinRight, VerticalJoyStickPos);
  }
    else{
  analogWrite(BackwardPinLeft, VerticalPosToMotor); 
  analogWrite(BackwardPinRight, VerticalPosToMotor);
  }
    if (HorizontalJoyStickPos > 512){
  analogWrite(ForwardPinLeft,HorizontalPosToMotor);
  delay(Speed / (0.25 * lwheel) * 1000); // lwheel = Расстояния между колесами. Функция поворота на 90 градусов.
  analogWrite(ForwardPinLeft, HorizontalPosToMotor);
  analogWrite(ForwardPinRight, HorizontalPosToMotor);
  }
    else{
  analogWrite(ForwardPinRight,HorizontalPosToMotor);
  delay(Speed / (0.25 * lwheel) * 1000); 
  analogWrite(ForwardPinLeft, HorizontalPosToMotor);
  analogWrite(ForwardPinRight,HorizontalPosToMotor);
  }
  int ForwardPinLeftArray [] = (VerticalPosToMotor);
  int BackwardPinLeftArray [] = (VerticalPosToMotor);
  int ForwardPinRightArray [] = (SomeMotorValue);
  int BackwardPinRightArray [] = (SomeMotorValue);
    } while (DebugMod == True);
}