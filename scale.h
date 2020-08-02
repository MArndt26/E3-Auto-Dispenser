/*----------------SCALE VARS----------------*/
String weightString = "";

const int LOADCELL_DOUT_PIN = 10;
const int LOADCELL_SCK_PIN = 11;

HX711 scale;

/*----------------SCALE FUNCTIONS----------------*/
void scaleInit()
{
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
#if HUSH
    Serial.println("Scale Initialized");
#endif
}