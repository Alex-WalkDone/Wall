//количество кнопок и диодов
const int BTN_COUNT = 20;

//массив с кнопками
int btn[BTN_COUNT]; // Присвоить номера пинов!!!!
//массив с диодами
int led[BTN_COUNT]; // Присвоить номера пинов!!!!
//массив с масками (какие должы быть состояния кнопок во время игры)
boolean mask[BTN_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//счётчик
unsigned long currentTime = 0;

/*===========================================================================================================*/
void setup() {
  //выбираем режим работы для пинов диодов и кнопок
  for (int i = 0; i < BTN_COUNT; i++) {
    pinMode(btn[i], INPUT_PULLUP);
    pinMode(led[i], OUTPUT);
  }
  //последоательный порт для отладки
  Serial.begin(9600);

}

/*===========================================================================================================*/
void loop() {


}

/*===========================================================================================================*/
/*Выбор случайной кнопки
 * Использует аналоговый пин А5 для снятия наводок
 * Выбирает случайное число от 0 до BTN_COUNT
 * Изменяет выбранную ячейку маски с 0 на 1
 * Включает диод на пине под выбранным номером
 * Выводит выбранное число в Порт
 * 
*/
void chooseTheButton(){
  Serial.println("choosing random button");
   while(true){
    randomSeed(analogRead(A5));
    int a = random(0,BTN_COUNT);
    if(mask[a]==false){
      mask[a]=true;
      digitalWrite(led[a],HIGH);
      Serial.print("I've chosen: ");
      Serial.println(a);
      break;
      }
  }
}
/*===========================================================================================================*/
void waitForPressed(){
Serial.println("Waiting for pressing");
for(currentTime = millis(); millis()-currentTime < 5000;){
  if(isAllPressed()){
    Serial.println("All btns had been pressed");
    for(int i=0; i < BTN_COUNT; i++){
      if(mask[i]==true){
        digitalWrite(ledPins[i], LOW);
        Serial.print("Switched off the led number: ");
        Serial.println(i);
      }
     }
     return;
    }
  }
  Serial.println("Btns hadn't been pressed");
  loser();
}
