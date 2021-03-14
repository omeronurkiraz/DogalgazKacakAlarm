
/*Bu kod, 09/08/2017 tarihinde maker.robotistan.com için hazırlanmıştır.*/

//Sensör pinlerimizi tanımlıyoruz:
#define sensor_pin A0
#define buzzer_pin 9
//RGB LED'imizin çıkış pinlerini tanımlıyoruz:
#define led_r 5
#define led_g 6
#define led_b 7
//Sensörün çalışması için gerekli ön ısıtma süresini 5sn olarak belirliyoruz
#define preheat_time 10000
//Alarmın çalması için gerekli eşik değerini 300 olarak belirliyoruz.
#define threshold 500 // thresold degerini kendiniz deneyerek bulunuz.
#undef HIGH
#undef LOW
#define HIGH 0
#define LOW 1
void setup()
{
//Alarm için kullanacağımız buzzer ve LED'leri çıkış olarak tanımlıyoruz
pinMode(buzzer_pin, OUTPUT);
pinMode(led_r, OUTPUT);
pinMode(led_g, OUTPUT);
pinMode(led_b, OUTPUT);
//Varsayılan olarak LED'in sönük kalmasını sağlıyoruz
digitalWrite(led_r, HIGH);
digitalWrite(led_g, HIGH);
digitalWrite(led_b, HIGH);
//Sensör değerini seri monitörden görebilmemiz için seri haberleşmeyi başlatıyoruz:
Serial.begin(9600);
//İlk 5sn boyunca sensörün ısınmasını bekliyoruz. Bu esnada LED mavi renkte yanıyor:
Serial.println("Sensor isitiliyor...");
digitalWrite(led_b, LOW);
delay(preheat_time);
//Isıma işlemi için gereken 5sn süre tamamlandığında mavi LED'i söndürüyoruz:
digitalWrite(led_b, HIGH);
delay(100);
}

void loop()
{
//analogRead() fonksiyonu ile sensör değerini ölçüyoruz ve bir değişken içerisinde tutuyoruz:
int sensorValue = analogRead(sensor_pin);
//Sensör değeri belirlediğimiz eşik değerinden yüksek ise alarm() fonksiyonunu çağırıyoruz:
if (sensorValue >= threshold)
alarm(100);
//Alarmın çalmadığı durumda LED'in yeşil yanmasını istiyoruz:
else
digitalWrite(led_g, LOW);
//Sensör değerini bilgisayarımızdan görebilmek için seri monitöre yazıyoruz:
Serial.println(sensorValue);
delay(1);
}

//Alarm fonksiyonumuzu tanımlıyoruz. Bu fonksiyon parametre olarak buzzerın ötüp ve LED'in yanıp söneceği süreyi almakta.

void alarm(unsigned int duration)
{
//Buzzer'ın 440Hz'te (la notası) ses üretmesini istiyoruz:
tone(buzzer_pin, 440);
//Normal durumda yeşil yanmakta olan LED'i söndürüp kırmızı renkte yakıyoruz:
digitalWrite(led_r, LOW);
digitalWrite(led_g, HIGH);
delay(duration);
noTone(buzzer_pin);
digitalWrite(led_r, HIGH);
digitalWrite(led_g, HIGH);
delay(duration);
}
