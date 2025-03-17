const byte HorizontalJoyStickPin = A1;// Убрать после подключения к esp
const byte VerticalJoyStickPin = A2;
const byte JoyStickButton = A3;

const byte ForwardPinLeft = 6;
const byte BackwardPinLeft = 7;
const byte ForwardPinRight = 12;
const byte BackwardPinRight = 13;
//const byte Esp8266Data; Для приёма данных с esp

byte HorizontalSpeed;
byte VerticalSpeed;
long time_since_turn;
byte MovementCase;
float CompareTurn;//Для сравнения прошлого и текущего угла
bool SideOfTurn; // Сторона поворота, если true Вперед
bool DebugMod = false;
float DegreeOfTurn;

const byte Radius_between_wheels = 100;
const byte Radius_of_wheel = 25;

void setup() {
  pinMode(ForwardPinLeft, OUTPUT);
  pinMode(BackwardPinLeft, OUTPUT);
  pinMode(ForwardPinRight, OUTPUT);
  pinMode(BackwardPinRight, OUTPUT);
  pinMode(JoyStickButton, INPUT);
}

void loop() {
  if (DebugMod == false) {
    static int ButtonCount = 0;
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

    int HorizontalJoyStick = analogRead(HorizontalJoyStickPin);
    int VerticalJoyStick = analogRead(VerticalJoyStickPin);
    if (HorizontalJoyStick > 450 and HorizontalJoyStick < 550) {
      HorizontalSpeed = 0;
    }
    if (HorizontalJoyStick >= 550) {
      HorizontalSpeed = map(HorizontalJoyStick, 550, 1023, 0, 255);
    }
    if (HorizontalJoyStick <= 450) {
      HorizontalSpeed = map(HorizontalJoyStick, 450, 0, 0, 255);
    }
    if (VerticalJoyStick > 450 and VerticalJoyStick < 550) {
      VerticalSpeed = 0;
    }
    if (VerticalJoyStick >= 550) {
      VerticalSpeed = map(VerticalJoyStick, 550, 1023, 0, 255);
    }
    if (VerticalJoyStick <= 450) {
      VerticalSpeed = map(VerticalJoyStick, 450, 0, 0, 255);
    }

    if (VerticalJoyStick > 512 and HorizontalJoyStick > 512) {
      DegreeOfTurn = degrees(atan2(HorizontalJoyStick - 512, VerticalJoyStick - 512));
      DegreeOfTurn = abs(DegreeOfTurn);
      MovementCase = 0;
    } else if (VerticalJoyStick < 512 and HorizontalJoyStick > 512) {
      DegreeOfTurn = degrees(atan2(HorizontalJoyStick - 512, VerticalJoyStick - 512));
      DegreeOfTurn = abs(DegreeOfTurn);
      DegreeOfTurn -= 90;
      MovementCase = 1;
    } else if (VerticalJoyStick > 512 and HorizontalJoyStick < 512) {
      DegreeOfTurn = degrees(atan2(HorizontalJoyStick - 512, VerticalJoyStick - 512));
      DegreeOfTurn = abs(DegreeOfTurn);
      MovementCase = 2;
    } else {
      DegreeOfTurn = degrees(atan2(HorizontalJoyStick - 512, VerticalJoyStick - 512));
      DegreeOfTurn = abs(DegreeOfTurn);
      DegreeOfTurn -= 90;
      MovementCase = 3;
    }

    if (DegreeOfTurn < CompareTurn and CompareTurn != DegreeOfTurn) {
      SideOfTurn = false;
    } else {
      SideOfTurn = true;
    }

    CompareTurn = DegreeOfTurn - CompareTurn;
    CompareTurn = abs(CompareTurn);
    float TimeFor1DegreeTurn = (Radius_between_wheels / (Radius_of_wheel * (VerticalSpeed / 255) * 3)) * DEG_TO_RAD;
    float time_for_turn = TimeFor1DegreeTurn * CompareTurn;
    switch (MovementCase) {
      case 0:
        time_since_turn = millis();
        if (time_since_turn < time_for_turn and SideOfTurn == true) {
          analogWrite(ForwardPinLeft, VerticalSpeed);
          analogWrite(ForwardPinRight, VerticalSpeed);
        } else if (time_since_turn < time_for_turn and SideOfTurn == false) {
          analogWrite(BackwardPinLeft, VerticalSpeed);
          analogWrite(ForwardPinRight, VerticalSpeed);
        }
        break;
      case 1:
        time_since_turn = millis();
        if (time_since_turn < time_for_turn and SideOfTurn == true) {
          analogWrite(ForwardPinLeft, VerticalSpeed);
          analogWrite(BackwardPinRight, VerticalSpeed);
        } else if (time_since_turn < time_for_turn and SideOfTurn == false) {
          analogWrite(BackwardPinLeft, VerticalSpeed);
          analogWrite(BackwardPinRight, VerticalSpeed);          
        }
        break;
      case 2:
        time_since_turn = millis();
        if (time_since_turn < time_for_turn and SideOfTurn == true) {
          analogWrite(ForwardPinLeft, VerticalSpeed);
          analogWrite(ForwardPinRight, VerticalSpeed);
        } else if (time_since_turn < time_for_turn and SideOfTurn == false) {
          analogWrite(BackwardPinLeft, VerticalSpeed);
          analogWrite(ForwardPinRight, VerticalSpeed);
        }
        break;
      case 3:
        time_since_turn = millis();
        if (time_since_turn < time_for_turn and SideOfTurn == true) {
          analogWrite(BackwardPinLeft, VerticalSpeed);
          analogWrite(ForwardPinRight, VerticalSpeed);
        } else if (time_since_turn < time_for_turn and SideOfTurn == false) {
          analogWrite(BackwardPinLeft, VerticalSpeed);
          analogWrite(BackwardPinRight, VerticalSpeed);
        }
        break;
    }
    /*
      byte* ForwardPinLeftArray;
      ForwardPinLeftArray = &(VerticalSpeed);
      byte* BackwardPinLeftArray;
      BackwardPinLeftArray = &(VerticalSpeed);
      byte* ForwardPinRightArray;
      ForwardPinRightArray = &(VerticalSpeed);
      byte* BackwardPinRightArray;
      BackwardPinRightArray = &(VerticalSpeed);
    */
  } /*else{
    analogWrite(ForwardPinLeft, ForwardPinLeftArray)
    analogWrite(BackwardPinLeft, BackwardPinLeftArray)
    analogWrite(ForwardPinRight, ForwardPinRightArray)
    analogWrite(BackwardPinRight, BackwardPinRightArray)
  }*/
}
