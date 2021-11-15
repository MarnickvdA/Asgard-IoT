# Internet Of Asgard

Internet of Things oplossing voor mijn studentenhuis. Huidige setup bestaat uit:

* MQTT Broker (Raspberry Pi 3)
Raspberry Pi op het lokale network fungeert als MQTT message broker voor inkomende en uitgaande berichten van andere IoT devices op het lokale netwerk.

* Deurbel detector (Arduino Uno R3)
Arduino met ENC28J60 LAN module voor connectie met lokale netwerk. Detecteert stroomverandering in deurbel waarna het een 'de deurbel is gegaan' bericht stuurt naar de MQTT broker. Verder detecteert het met behulp van een magneetstripje of de deur open of dicht is. Dit wordt ook verstuurt via MQTT. 

* HJ Lamp (Arduino Uno R3)
Arduino met ENC28J60 LAN module voor connectie met lokale netwerk. Deze Arduino luistert naar MQTT topics over de deurbel en de deur status (open/dicht). Als de deurbel gaat zal deze Arduino een LED Strip aansturen waarna er een lamp in de fusie gaat branden. Zo weet de huisjongste altijd dat hij het deurtje open moet doen :). 
