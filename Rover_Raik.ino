const int ForwardPinLeft = 3;   // Контакт для управления двигателем вперед.
const int BackwardPinLeft = 5;  // Контакт для управления двигателем назад.
const int ForwardPinRight = 10;
const int BackwardPinRight = 9;

const int HorizontalPin = A1;  //Контакты для приёма сигналов от джойстика.
const int VerticalPin = A2;
const int JoyStickButton = A3;

bool DebugMod = false;  // Специальный дебаг режим для запоминания движения.

const int Rotation = 4;  //Rotation = Максимальная скорость вращения двигателя.
const int Lwheel = 150;  //Lwheel = Расстояния между колесами.
const int Dwheel = 50;   //Dwheel = Диаметр колеса.

void setup() {
  pinMode(ForwardPinLeft, OUTPUT);
  pinMode(BackwardPinLeft, OUTPUT);
  pinMode(ForwardPinRight, OUTPUT);
  pinMode(BackwardPinRight, OUTPUT);
  pinMode(JoyStickButton, INPUT_PULLUP);
}

void loop() {
  int ButtonCount = 0;
  if (digitalRead(JoyStickButton) == LOW) {
    ButtonCount++;
    delay(300);
  }
  if (ButtonCount == 3) {  //Если кнопка нажата 3 раза включает режим дебага (Запоминания маршрута)
    DebugMod = true;
  } else if (ButtonCount == 6) {
    ButtonCount = 0;
    DebugMod = false;
  }
  if (DebugMod == true) {
    int HorizontalJoyStick = analogRead(HorizontalPin);
    int VerticalJoyStick = analogRead(VerticalPin);
    int HorizontalJoyStickPos;
    int VerticalJoyStickPos;
    //Код для перевода позиции джойстика в мощность работы мотора.
    if (HorizontalJoyStick > 450 and HorizontalJoyStick < 550) {
      HorizontalJoyStickPos = 0;
    }
    if (HorizontalJoyStick >= 550) {
      HorizontalJoyStickPos = map(HorizontalJoyStick, 550, 1023, 0, 255);
    }
    if (HorizontalJoyStick <= 450) {
      HorizontalJoyStickPos = map(HorizontalJoyStick, 450, 0, 0, 255);
    }
    if (VerticalJoyStick > 450 and VerticalJoyStick < 550) {
      VerticalJoyStickPos = 0;
    }
    if (VerticalJoyStick >= 550) {
      VerticalJoyStickPos = map(VerticalJoyStick, 550, 1023, 0, 255);
    }
    if (VerticalJoyStick <= 450) {
      VerticalJoyStickPos = map(VerticalJoyStick, 450, 0, 0, 255);
    }
    int Speed = (((HorizontalJoyStickPos / 255) * Rotation) * Dwheel);
    if (VerticalJoyStick > 512) {
      analogWrite(ForwardPinLeft, VerticalJoyStickPos);
      analogWrite(ForwardPinRight, VerticalJoyStickPos);
    } else {
      analogWrite(BackwardPinLeft, VerticalJoyStickPos);
      analogWrite(BackwardPinRight, VerticalJoyStickPos);
    }
    if (HorizontalJoyStick > 512) {
      analogWrite(ForwardPinLeft, HorizontalJoyStickPos);
      delay(Speed / (0.25 * Lwheel) * 1000);
      analogWrite(ForwardPinRight, HorizontalJoyStickPos);
    } else {
      analogWrite(ForwardPinRight, HorizontalJoyStickPos);
      delay(Speed / (0.25 * Lwheel) * 1000);
      analogWrite(ForwardPinLeft, HorizontalJoyStickPos);
    }
    /*
    int * ForwardPinLeftArray;
    ForwardPinLeftArray = ();
    int * BackwardPinLeftArray;
    BackwardPinLeftArray = ();
    int * ForwardPinRightArray;
    ForwardPinRightArray = ();
    int * BackwardPinRightArray;
    BackwardPinLeftArray = (); 
    */
  }
  //else{}
}
