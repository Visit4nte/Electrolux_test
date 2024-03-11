// Q2) Imagine a situation where you have an electronic board with a microcontroller and a button. You
// are required to check if the button is pressed (state ON) or not (state OFF) and for how long the
// button is kept pressed. If the button gets pressed, you also need to have a clear state definition
// ranging from ON, PROTECTED and OFF; as per the state diagram below. The protected state is
// defined as an intermediate stage between the transition from the ON state to the OFF state, so
// that each time the button is released, the button state changes to PROTECTED for 10 seconds
// before going to the OFF state.

#define Button 7 

int PinState = 0;
int BeforeState = 0;
float TimePressed = 0.0;

void setup() {
  // put your setup code here, to run once:
    pinMode(Button, INPUT);

    Serial.begin(19200); //Serial to print informations
}

void loop() {
  // Define ON State
    PinState = digitalRead(Button);
    if (PinState == 1 && PinState != BeforeState){
        BeforeState = 1;
        Serial.println("State: ON");
        TimePressed = millis(); // Resgister the time when the button was pressed
        delay(100); // Delay to avoid debounce problems
    }

    // Define OFF State
    if (PinState == 0 && PinState != BeforeState){
        BeforeState = 0;
        Serial.println ("State: PROTECTED");
        TimePressed = (millis() - TimePressed)/1000; // Calculate how much time the button was kept pressed
        Serial.print ("Pressed time:");
        Serial.println (TimePressed);
        delay(10000); // Dalay to lock in Protected state.
        Serial.println ("State: OFF");  
    }
}