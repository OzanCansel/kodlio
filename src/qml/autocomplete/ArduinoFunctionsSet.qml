import QtQuick 2.0
import "../singleton"

AutoCompleteSet {

    Component.onCompleted   :   {

        //Fonksiyonlar başlangıç ------------------

        appendItem({
                       "name"            :   "pinMode(<b>byte pin</b> , <b>byte görev</b>)",
                       "usageTemplate"   :   "pinMode(<pin> , <görev>)" ,
                       "description"     :   "Belirtilen pinin sinyal okumak için mi yoksa sinyal göndermek için mi kullanılacağını belirler." ,
                       "example"         :   "pinMode(8 , OUTPUT);<br>pinMode(9 , INPUT)" ,
                       "type"            :  Enum.method
                   })
        appendItem({
                       "name"            :  "digitalWrite(<b>byte pin</b> , <b>sinyalSeviyesi</b>)",
                       "usageTemplate"   :  "digitalWrite(<pin> , <sinyalSeviyesi>)" ,
                       "description"     :  "Belirtilen pinin sinyal seviyesi dijital olarak değiştirir.\n  [sinyalSeviyesi] parametresi <font color=\"red\"><b>HIGH</b></font> ve <b>LOW</b> sabitlerini alabilir. HIGH belirtilen pinden sinyal gönderir, LOW sinyali durdurur." ,
                       "example"         :  "digitalWrite(8 , HIGH);<br> digitalWrite(9 , LOW)" ,
                       "type"            :  Enum.method
                   })

        appendItem({

                       "name"          :   "digitalRead(<b>byte pin</b>)" ,
                       "usageTemplate" :   "digitalRead(<pin>)" ,
                       "description"   :   "Belirtilen pinin sinyal seviyesini <strong>dijital</strong> olarak okur. <span style=\"color: #ff0000;\">HIGH</span> veya <span style=\"color: #000000;\">LOW</span> d&ouml;nd&uuml;r&uuml;r." ,
                       "example"       :   "int val = digitalRead(8)" ,
                       "type"          :   Enum.method
                   })

        appendItem({
                       "name"          :   "analogWrite(<b>byte pin</b> , <b>byte val</b>)" ,
                       "usageTemplate" :   "analogWrite(<pin> , <pwm>)" ,
                       "description"   :   "<p>Belirtilen pine analog sinyal g&ouml;nderir. dijitalWrite fonksiyonunda <strong><span style=\"color: #ff0000;\">HIGH</span></strong> veya <strong>LOW</strong> g&ouml;nderirken, burada 0 ile 255 arasında sinyal yollayabiliriz.</p>
<p><strong>Dikkat :</strong> Bu metod sadece pwm destekleyen pinler i&ccedil;in kullanılabilir. (Mikrokontrolc&uuml; &uuml;zerinde <strong>'~'</strong> işareti ile başlayan pinler)</p>" ,
                       "example"       :   "analogWrite(9 , 126);" ,
                       "type"          :   Enum.method
                   })

        appendItem({
                       "name"          :   "analogRead(<b>byte pin</b>)" ,
                       "usageTemplate" :   "analogRead(<pin>)" ,
                       "description"   :   "<p>Belirtilen pinden sinyal okur. Bu metod <strong>'A'</strong> <span style=\"color: #ff6600;\">(örn.</span> <span style=\"color: #0000ff;\">A0 , A1 , A2<span style=\"color: #ff6600;\">)</span></span> ile başlayan pinler i&ccedil;in kullanılabilir. Pine gelen sinyal değerini voltajın değerine g&ouml;re&nbsp;yorumlar ve geriye 0-1023 arasında bir değer d&ouml;nd&uuml;r&uuml;r. 1023 pinden <span style=\"color: #ff0000;\">5V</span> olduğuna, 0 ise <strong>0V</strong> olduğu anlamına gelir. Sens&ouml;rlerden gelen değerleri okumak i&ccedil;in sık sık kullanılır.</p>" ,
                       "example"       :   "analogRead(A0)" ,
                       "type"          :   Enum.method

                   })

        appendItem({
                       "name"          :   "delay(<b>unsigned long uykuSüresi</b>)" ,
                       "usageTemplate" :   "delay(<uykuSüresi>)" ,
                       "description"   :   "<p>Mikrokontrolcüyü belirtilen süre kadar uyutur ve ardından kaldığı yerde devam eder. Süre milisaniye(1000 ms = 1 saniye) cinsinden belirtilmelidir. Uyku süresince herhangi bir kod çalıştırılamaz. Bu süre içerisinde işlemci mevcut pinlerindeki durumunu korur.</p>" ,
                       "example"       :   "delay(1000); //İşlemciyi bir saniyeliğine uyutur" ,
                       "type"          :   Enum.method
                   })

        appendItem({
                       "name"          :   "delayMicroseconds(<b>unsigned long uykuSüresi</b>)" ,
                       "usageTemplate" :   "delayMicroseconds(<uykuSüresi>)" ,
                       "description"   :   "Mikrokontrolcüyü belirtilen süre kadar uyutur ve ardından kaldığı yerde devam eder. Süre mikrosaniye(1,000,000 = 1000 ms = 1 saniye) cinsinden belirtilmelidir. Uyku süresince herhangi bir kod çalıştırılamaz. Bu süre içerisinde işlemci mevcut pinlerindeki durumunu korur." ,
                       "example"       :   "delayMicroseconds(2000); //İşlemciyi 2 saniyeliğine uyutur" ,
                       "type"          :   Enum.method
                   })

        appendItem({
                        "name"          :   "min(<b>T a , T b</b>)",
                        "usageTemplate" :   "min(<deger1> , <deger2>)",
                        "description"   :   "Gönderilen parametrelerden küçük olanı geri döndürür.",
                        "example"       :   "int kucukDeger = min(5 , 7); //Bu örnekte 5'i geri döndürür ve kucukDeger değişkenine atar.",
                        "type"          :   Enum.method
                   })

        appendItem({
                        "name"          :   "max(<b>T a, T b</b>",
                        "usageTemplate" :   "max(<deger1> , <deger2>)" ,
                        "description"   :   "Gönderilen parametrelerden büyük olanı geri döndürür.",
                        "example"       :   "int buyukDeger = max(5 , 7); //7'yi geri döndürür ve buyukDeger degiskenine atar.",
                        "type"          :   Enum.method
                   })

        appendItem({
                       "name"           :   "abs(<b>T a , T b</b>)",
                        "usageTemplate" :   "abs(<deger>)",
                        "description"   :   "Gönderilen değerin mutlak değerini döndürür.",
                        "example"       :   "int mutlakDeger = abs(-5); //-5'in mutlak değeri olan 5'i geri döndürür.",
                        "type"          :   Enum.method
                   })

        appendItem({
                        "name"          :   "constrain(<b>T deger , T altSınır, T üstSınır</b>)",
                        "usageTemplate" :   "constrain(<deger> , <altSınır> , <üstSınır>)",
                        "description"   :   "Metoda gönderilen <deger> alt sınırdan küçükse geri alt sınır, <deger> üst sınırdan büyükse geriye üst sınır, eğer ki alt ve üst sınırın arasındaysa <deger>'i geri döndürür.",
                        "example"       :   "int sonuc = constrain(5 , 9 , 15); //Geriye 9 döndürür.<br>int sonuc = constrain(10 , 9 , 15); //geriye 10 döndürür.<br>int sonuc = constrain(16 , 9 , 15); //Geriye 15 döndürür.",
                        "type"          :   Enum.method
                   })

        appendItem({
                       "name"           :   "map(<b>T deger , T değerinKendiAralığı1 , T değerinKendiAralığı2 , T degiştirilenAralık1 , T degiştirilenAralık2</b>)",
                       "usageTemplate"  :   "map(<deger> , <kAralık1> , <kAralık2> , <dAralık1> , <dAralık2>)" ,
                        "description"   :   "Metoda gönderilen değeri belirtilen aralıklara göre ayarlar ve geri döndürür." ,
                        "example"       :   "int ayarlanmisDeger = map(50 , 0 , 100 , 0 , 1000); //0 ile 100 arasında değişen değeri 0 ile 1000 arasında değişen değere çevirir. Metod geriye 500 döndürür.",
                        "type"          :   Enum.method
                   })

        appendItem({
                        "name"          :   "pow(<b>T sayı , T üst</b>)",
                        "usageTemplate" :   "pow(<değer> , <üst>)" ,
                        "description"   :   "Sayıların üstünü almak için kullanılır. İlk parametre sayıyı, ikinci parametre ise üst kısmını ifade eder.",
                        "example"       :   "int sonuç = pow(10 , 2); // 10 üzeri 2'yi yani 10'un karesini döndürür.",
                        "type"          :   Enum.method
                   })

        appendItem({
                        "name"          :   "sqrt(<b>T sayı</b>)",
                        "usageTemplate" :   "sqrt(<sayı>)" ,
                        "description"   :   "Gönderilen sayının karekökünü alır.",
                        "example"       :   "int sonuç = sqrt(4); //Geriye 2 döndürür.",
                        "type"          :   Enum.method
                   })

        appendItem({
                       "name"           :   "sin(<b>T radyan</b>)",
                        "usageTemplate" :   "sin(<radyan>)" ,
                        "description"   :   "Gönderilen açının sinüsünü alır. Açı radyan cinsinden olmalıdır. 180° 1π radyandır.",
                        "example"       :   "int sinüs = sin(PI * 1); //Geri sinüs180 yani 0 döndürür.",
                        "type"          :   Enum.method
                   })

        appendItem({
                       "name"           :   "tone(<b>int pin , int frekans</b>)",
                        "usageTemplate" :   "tone( <pin> , <frekans> )" ,
                        "description"   :   "Belirtilen pine belirtilen frekansda sinyaller yollar. Buzzer ile birlikte kullanılarak notalar elde edilebilir.",
                        "example"       :   "tone(8 , 220); //Buzzerdan LA notası verir.",
                        "type"          :   Enum.method
                   })

        appendItem({
                       "name"           :   "tone(<b>int pin , int frekans , int süre</b>)",
                        "usageTemplate" :   "tone( <pin> , <frekans> , <süre> )" ,
                        "description"   :   "Belirtilen pine belirtilen frekansda girinlen süre boyunca sinyal yollar. Buzzer ile birlikte kullanılarak notalar elde edilebilir.",
                        "example"       :   "tone(8 , 220 , 1000 ); //Buzzerdan LA notasını 1000ms = 1sn boyunca verir.",
                        "type"          :   Enum.method
                   })

        appendItem({
                       "name"           :   "noTone(<b>int pin</b>)",
                        "usageTemplate" :   "tone( <pin> )" ,
                        "description"   :   "Belirtilen pindeki sinyalleri durdurur.",
                        "example"       :   "tone( 8 ); //Buzzeri susturur.",
                        "type"          :   Enum.method
                   })

        appendItem({
                       "name"           :   "pulseIn(<b>int pin , int sinyalSeviyesi</b>)",
                        "usageTemplate" :   "pulseIn( <pin> , <sinyalSeviyesi>)" ,
                        "description"   :   "Pinin belirtilen sinyal seviyesine gelene kadar bekler ve geçen süreyi geri döndürür.",
                        "example"       :   "pulseIn( 8 , HIGH ); //8 numaralı pinden HIGH sinyali gelene kadar bekler ve geçen süreyi geri döndürür.",
                        "type"          :   Enum.method
                   })
        appendItem({
                       "name"           :   "pulseIn(<b>int pin , int sinyalSeviyesi , int zamanAsimi</b>)",
                        "usageTemplate" :   "pulseIn( <pin> , <sinyalSeviyesi> , <zamanAsimi>)" ,
                        "description"   :   "Pinin belirtilen sinyal seviyesine gelene kadar bekler ve eger zamanAsimina ugrarsa geriye 0 döndürür.",
                        "example"       :   "pulseIn( 8 , HIGH , 2000 ); //8 numaralı pinden HIGH sinyali gelene kadar bekler ve 2000 mikrosaniye içerisinde herhangi bir sinyal gelmezse geriye 0 döndürür.",
                        "type"          :   Enum.method
                   })


        //Fonksiyonlar bitiş ------------------


        //Primitive tipler başlangıç    -----------------------
        appendItem({
                       "name"          :   "void",
                       "usageTemplate" :   "void",
                       "description"   :   "void boşluk anlamına gelen, genellikle metod imzasına veya nesnenin tipi bilinmediğine kullanılan veri tipidir." ,
                       "example"       :   "void lediYakSöndür();"  ,
                       "type"          :   Enum.primitiveType
                   })

        appendItem({
                       "name"          :   "boolean",
                       "usageTemplate" :   "boolean",
                       "description"   :   "boolean true(doğru) veya false(yanlış) olarak 2 değer tutan veri tipidir. Hafızada 1 bytelık yer tutar." ,
                       "example"       :   "boolean ledAcik(); //Ledin açık olup olmadığını belirten metod olarak kullanılabilir"  ,
                       "type"          :   Enum.primitiveType
                   })


        appendItem({
                       "name"          :   "char",
                       "usageTemplate" :   "char",
                       "description"   :   "char bir tane ASCII karakterini ifade eden veri tipidir. -127 ile 127 arasında değer alır. Hafızada 1 bytelık yer tutar. Karakter sayıya çevirilerek hafızada tutulur." ,
                       "example"       :   "char basHarf = 'R';"  ,
                       "type"          :   Enum.primitiveType
                   })

        appendItem({
                       "name"          :   "unsigned char",
                       "usageTemplate" :   "unsigned char",
                       "description"   :   "char bir tane ASCII karakterini ifade eden veri tipidir. 0-255 arasında değer alır. Hafızada 1 bytelık yer tutar. Karakter sayıya çevirilerek hafızada tutulur." ,
                       "example"       :   "unsigned char basHarf = 'R';"  ,
                       "type"          :   Enum.primitiveType
                   })

        appendItem({
                       "name"          :   "byte",
                       "usageTemplate" :   "byte",
                       "description"   :   "8 bitlik işaretsiz sayıdır. 0 ile 255 arasında bir değer alır. İkilik , onluk veya onaltılık sistemlerde değerler alabilir." ,
                       "example"       :   "byte ikilikSistem = B10010;<br>byte onlukSistem = 127;<br>byte onAltilikSistem = 0xFF;"  ,
                       "type"          :   Enum.primitiveType
                   })

        appendItem({
                        "name"          :   "int",
                        "usageTemplate" :   "int",
                        "description"   :   "Tamsayı tanımlamak için kullanılan veri tipidir. Pozitif ve negatif tamsayılar tanımlanabilir. -32,768 ile 32,767 arasında değerler alır.",
                        "example"       :   "int dogumYili = 2015; //Pozitif değer<br>int sicaklik = -5; //Negatif değer",
                        "type"          :   Enum.primitiveType
                   })

        appendItem({
                        "name"          :   "unsigned int",
                        "usageTemplate" :   "unsigned int" ,
                        "description"   :   "Tamsayıları tanımlamak için kullanılan veri tipidir. int veri tipinden farkı sadece pozitif sayıları ifade etmek için kullanılmasıdır, sadece pozitif sayıları tuttuğu için 65,535'e kadar olan tamsayı değerlerini alabilir.",
                        "example"       :   "int ay = 8;",
                        "type"          :   Enum.primitiveType
                   })

        appendItem({
                        "name"          :   "long",
                        "usageTemplate" :   "long",
                        "description"   :   "Tamsayı tanımlamak için kullanılan veri tipidir. Pozitif ve negatif değerler alabilir. -2,147,483,648 ile 2,147,483,647 arasında değerler alır. int ile ifade edilemeyecek kadar büyük değerler için kullanılabilir.",
                        "example"       :   "long isikHizi = 300000;",
                        "type"          :   Enum.primitiveType
                   })

        appendItem({
                        "name"          :   "unsigned long",
                        "usageTemplate" :   "unsigned long",
                        "description"   :   "Tamsayı tanımlamak için kullanılan veri tipidir. long tipinden farkı sadece pozitif sayıları ifade etmek için kullanılmasıdır. Sadece pozitif sayıları tuttuğu için 4,294,967,295'a kadar tamsayı değerlerini alabilir.",
                        "example"       :   "unsigned long cinNufusu = 1301000000;" ,
                        "type"          :   Enum.primitiveType
                   })

        appendItem({
                        "name"          :   "float",
                        "usageTemplate" :   "float",
                        "description"   :   "Virgüllü ve tamsayıları ifade etmek için kullanılan veri tipidir. int, long vb. veri tiplerinden farkı virgüllü sayıları da ifade edebilmesidir. Hafızada 4 bytelık yer tutar.",
                        "example"       :   "float pi = 3.141592;   //Pi sayısını tutan değişken",
                        "type"          :   Enum.primitiveType
                   })

        appendItem({
                        "name"          :   "double",
                        "usageTemplate" :   "double",
                        "description"   :   "Virgüllü ve tamsayıları ifade etmek için kullanılan veri tipidir. float veri tipine kıyasla virgülden sonra daha detaylı değerler tutabilir.",
                        "example"       :   "double pi = 3.141592653589793;",
                        "type"          :   Enum.primitiveType
                    })

        appendItem({
                        "name"          :   "String"    ,
                        "usageTemplate" :   "String",
                        "description"   :   "Yazıları programatik olarak saklamak için kullanılan veri tipidir. Karakter dizisi olarak hafızada saklanır.",
                        "example"       :   "String editorAdı = \"Roboskop\"",
                        "type"          :   Enum.classType
                   })

        //Class tipler bitiş    -----------------------

        //Constant ------------------

        appendItem({
                        "name"          :   "HIGH",
                        "usageTemplate" :   "HIGH",
                        "description"   :   "Belirtilen pinin sinyal seviyesini okurken veya sinyal seviyesini ayarlarken kullanılır. Elektronik olarak 3.0 Volt üstü HIGH'dır." ,
                        "example"       :   "digitalWrite(13 , HIGH); //Arduino üzerinde bulunan ledi yakar.<br>if(digitalRead(13) == HIGH) // Eğer 13 numaralı pinin voltajı HIGH ise",
                        "type"          :   Enum.constant
                   })

        appendItem({
                        "name"          :   "LOW",
                        "usageTemplate" :   "LOW",
                        "description"   :   "Belirtilen pinin sinyal seviyesini okurken veya sinyal seviyesini ayarlarken kullanılır. Elektronik olarak 3.0 Volt altı LOW'dur." ,
                        "example"       :   "digitalWrite(13 , LOW); //Arduino üzerinde bulunan ledi söndürür.",
                        "type"          :   Enum.constant
                   })


        appendItem({
                        "name"          :   "INPUT",
                        "usageTemplate" :   "INPUT",
                        "description"   :   "Pini ayarlarken kullanılır. Pinden değer okunacağını ifade eden sabittir." ,
                        "example"       :   "pinMode(13 , INPUT); //13 numaralı pinden sinyal okunması için işlemciyi ayarlar",
                        "type"          :   Enum.constant
                   })


        appendItem({
                        "name"          :   "OUTPUT",
                        "usageTemplate" :   "OUTPUT",
                        "description"   :   "Pini ayarlarken kullanılır. Pinden sinyal gönderileceğini ifade eden sabittir." ,
                        "example"       :   "pinMode(13 , OUTPUT); //13 numaralı pinden sinyal gönderilmesi için işlemciyi ayarlar",
                        "type"          :   Enum.constant
                   })

        appendItem({
                        "name"          :   "true",
                        "usageTemplate" :   "true",
                        "description"   :   "Programatik olarak doğruyu ifade eder. 0'dan büyük her sayı 'true'dur." ,
                        "example"       :   "while(true) { } //Bu koşul her zaman doğru olduğu için sonsuz dönüyü ifade eder",
                        "type"          :   Enum.constant
                   })

        appendItem({
                        "name"          :   "false",
                        "usageTemplate" :   "false",
                        "description"   :   "Programatik olarak yanlışı ifade eder. 0 ve 0'dan küçük her sayı 'false'dur." ,
                        "example"       :   "while(false) { } //Bu koşul hiç bir zaman sağlanmayacağı için bloğa girmeyecektir.",
                        "type"          :   Enum.constant
                   })

        //Constant bitiş ------------------

        //Control statement başlangıç ----------------------------------

        appendItem({
                        "name"          :   "if ( koşul )",
                        "usageTemplate" :   "if(<koşul>){ \n\n }",
                        "description"   :   "Program akışını belirli koşullara göre değiştirmek için kullanılır. if 'eğer' anlamına gelmektedir. Yani eğer belirtilen koşul sağlanıyorsa bloğa gir anlamına gelir." ,
                        "example"       :   "if( 2 < 5 ) {  } //Eğer ki 2 sayısı 5'ten küçük ise bloğa giricektir.",
                        "type"          :   Enum.constant
                   })

        appendItem({
                        "name"          :   "if(koşul) <b>else</b> { }",
                        "usageTemplate" :   "if(<koşul>){ \n\n } else {\n\n}",
                        "description"   :   "Program akışını belirli koşullara göre değiştirmek için kullanılır. if 'eğer' anlamına gelmektedir. Yani eğer belirtilen koşul sağlanıyorsa bloğa gir anlamına gelir." ,
                        "example"       :   "if( 2 < 5 ) {  <br> } >else { <br> }//Eğer ki 2 sayısı 5'ten küçük ise bloğa giricektir.",
                        "type"          :   Enum.constant
                   })


        //Control statement bitiş ----------------------------------


        reindex(0)
    }
}
