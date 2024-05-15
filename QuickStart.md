# OpenRoboticBoard

## Voraussetzung:

- Windows-PC, 64-Bit, möglichst mit Bluetooth
- USB-C-Kabel
- LiPo (7,4V), siehe Zubehör

## Inbetriebnahme

***Bild: ORB mit Beschriftung***

1. SW-Installation
   
   - Software "ORB-Monitor" herunterladen und installieren
   
   - Entwicklungsumgebung "Em::Bitz" herunterladen und installieren
   
   - Mit Batch-Programm **_setEnv.bat** Umgebungsvariable setzen

2. Anschlüsse
   
   - Spannungsversorgung anschließen
   
   - ORB mit USB-C-Kabel an PC anschließen
   
   - ORB-Monitor starten

*<<Folgende Schritte 4.x entfallen, wenn Firmware vorinstalliert ist>>*

3. Firmware-Download
   
   - ORB ausschalten (Schalter unten). Dann Taste auf ORB drücken und festhalten.
     Bei gedrückter Taste ORB wieder einschalten. Es sollte jetzt KEINE LED leuchten.
   
   - ORB-Monitor starten. Im Menü "File"-"Download" in das Verzeichnis ... navigieren und passende DFU-Datei auswählen. Nach Bestätigung startet der Firmware-Update automatisch.
   
   - ORB ausschalten

*<<Ob der Download funktioniert hat, wird im nächsten Schritt geprüft>>*

4. ???
   
   - ORB einschalten (Schalter oben). Die rote LED blinkt
   
   - Im ORB-Monitor Verbindung "USB" wählen. ORB-Monitor verbindet sich mit dem Board, "Not connected" erlischt und die aktuelle Board-Spannung wird angezeigt.
     ***Bild: ORB-Monitor***
     Falls die Verbindung auch nach einigen Sekunden nicht hergestellt werden kann, USB-Kabel herausziehen und wieder einstecken, damit Windows die Treiberinstallation abschließen kann. 
   
   - Im Menu "File"-"Settings" auswählen um Einstellungen am ORB vornehmen zu können. Es öffnet sich ein Dialogfenster, in dem der Name und die Spannungsgrenzen für die Batterieanzeige eingestellt werden können. Der Name wird u.a. für die Bluetooth-Verbindung verwendet.
     Im Dialogfenster werden auch die aktuellen SW-Versionen angezeigt.

5. Bluetooth-Verbindung einrichten (optional)
   
   - In Windows Einstellungen Bluetooth-Gerät hinzufügen. 
   
   - Danach muss ORB-Monitor neu gestartet werden. 
     *<< Ggf. entfällt Neustart in zukünftigen Versionen des ORB-Monitors >>*

6. Motor- und Sensortest
   
   - Zum Testen können die (kompatiblen) Motoren und Sensoren angeschlossen werden:
     
     - M1 bis M4: Bis zu 4 Motoren
     - Servo 1 und Servo2: Bis zu 2 Modellbau-Servos
       *<< Die Pinbelegung der Servos ist nicht einheitlich!!!>>*
     - S1 bis S4: Bis zu 4 Sensoren
     - D1 und D2: Bis zu 2 Schalter
   
   - Verbindung zum ORB herstellen (USB oder Bluetooth)
   
   - Im Menü "Control"-"Motor" auswählen, es öffnet sich das Dialogfenster "Motor Configuration and Setting".
     Hier können die verwendeten Motoren konfiguriert, gestartet und gestoppt werden. Ausserdem lassen sich von hier aus die Servos steuern.
     ***Bild: Dialogbox***
   
   - Im Menü "Control"-"Sensor" auswählen um die Dialogbox "Sensor-Configuration" zu öffnen. In der Dialogbox kann angegeben werden, welche Sensoren an den Ports angeschlossen sind.
     ***Bild: Dialogbox***
   
   - Im Menü "Control"-"View" auswählen. Es erscheint die Dialogbox "View Raw Data", die alle gemessenen Motor- und Sensorwerte sowie die Zustände der beiden Digitaleingänge anzeigt. 
     ***Bild: Dialogbox***

7. Anwendungsprogramm
   
   - Die Entwicklungsumgebung "Em::Bitz" starten und das Projekt ... öffnen
   
   - Projekt mit ... übersetzen. Falls keine Fehler gemeldet werden, Anwendungssoftware mit ORB-Monitor auf den ORB herunterladen
   
   - Die Anwendung starten:
     
     - Im ORB-Monitor mit dem grünen oder gelben Button
     - Auf dem Board mit kurzen oder langem Tastendruck.
   
   - Um die Anwendung zu stoppen:
     
     - Im ORB-Monitor die rote "Stop"-Taste drücken.
     
     - Auf dem Board die Taste erneut betätigen
   
   - Um ein eigenes Projekt anzulegen, ein geeignetes Beispielprojekt in ein eigenes Projektverzeichnis kopieren und dort mit Em::Bitz bearbeiten.

## Zubehör:

- Lipo, z.B. Reely Modellbau-Akkupack 7.4 V, BEC-Stecker
- Ladegerät, z.B. VOLTCRAFT Eco LiPo 1000

## Pinbelegung

## Kabel

*<<Anleitung zur Herstellen eine Kabels für ORB-Variante mit Wannenstecker>>*

## Problembehandlung:

- Firmware-Update funktioniert nicht oder lässt sich nicht starten
  
  - ORB im DFU-Mode?
  - USB-Treiber für DFU-Download installiert?

- USB-Verbindung kann nicht hergestellt werden
  
  - USB-Kabel abziehen und wieder einstecken.
  - Im Windows-Gerätemanager prüfen, ob Geräte "OpenRoboticBoard" erkannt wurden
  - Ggf. Treiber "WinUSB" manuell installieren  
