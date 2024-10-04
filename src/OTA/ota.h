
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <ESP32httpUpdate.h>

// Define server details and file path
// https://github.com/Defdjamel/poolControllerEsp/raw/master/firmware.bin
//https://s3.eu-west-1.amazonaws.com/pickme.today/firmware.bin

//https://raw.githubusercontent.com/adityabangde/ESP32-OTA-Update-via-GitHub/dev/ota_code.bin
//https://raw.githubusercontent.com/Defdjamel/poolControllerEsp/master/firmware.bin

// https://s3.eu-west-1.amazonaws.com/pickme.today/firmware.bin
// #define HOST "s3.eu-west-1.amazonaws.com"
// #define PATH "/pickme.today/firmware.bin"
// #define HOST "raw.githubusercontent.com"
// #define PATH "/Defdjamel/poolControllerEsp/master/firmware.bin"
#define PORT 443
#define URL "https://raw.githubusercontent.com/Defdjamel/poolControllerEsp/master/firmware.bin"

// Define the name for the downloaded firmware file
#define FILE_NAME "firmware.bin"

// void getFileFromServer() ;
// void performOTAUpdateFromSPIFFS();
void updateFirmware(const char* firmwareUrl);

void checkOTAUpdate(){
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  SPIFFS.format();

//get lastversion
  String response  = sendPostRequest(SERVER_API_LASTVERSION, "", SERVER_PORT, {}, 0 )  ;
  JsonDocument doc;
  deserializeJson(doc, response);
  float last_version =  doc[String("ESP")];
  float current_version =  String(BLYNK_FIRMWARE_VERSION).toFloat();
  Serial.printf("Version ESP : %.2f , current : %.2f \r\n",last_version,current_version);
  if(last_version > current_version){
    //update
    Serial.printf("updating to Firmware %.2f...\r\n",last_version);
    // getFileFromServer();
    // performOTAUpdateFromSPIFFS();
    updateFirmware(URL);
  }else{
     Serial.println("app already in date");
  }
  
  return;

}
void updateFirmware(const char* firmwareUrl) {
  WiFiClientSecure client;
  client.setInsecure();  // Pour ignorer la validation SSL, ne pas utiliser en production

  HTTPClient https;

  Serial.println("Téléchargement du firmware depuis l'URL : ");
  Serial.println(firmwareUrl);

  https.begin(client, firmwareUrl);  // Début de la requête HTTPS

  int httpCode = https.GET();  // Exécution de la requête GET

  if (httpCode == HTTP_CODE_OK) {  // Si la réponse du serveur est 200 (succès)
    int contentLength = https.getSize();
    if (contentLength > 0) {
      bool canBegin = Update.begin(contentLength);  // Commence la mise à jour avec la taille connue
      if (canBegin) {
        Serial.println("Mise à jour commencée...");
        
        WiFiClient *stream = https.getStreamPtr();
        uint8_t buff[128] = { 0 };
        int totalWritten = 0;
        int bytesRead;
        float previousProgress = 0.0;

        // Télécharge les données du firmware par paquets
        while ((bytesRead = stream->available()) > 0) {
          int bytesToRead = stream->readBytes(buff, sizeof(buff));  // Lire les données dans le buffer
          totalWritten += Update.write(buff, bytesToRead);  // Écrire dans la mémoire flash

          // Calcul de l'avancement
          float progress = (totalWritten / (float)contentLength) * 100;

          // Affiche seulement si l'avancement dépasse un seuil de 0.5%
          if (progress - previousProgress >= 1) {
            Serial.printf("Avancement : %.2f%%\r", progress);
            previousProgress = progress;  // Met à jour le précédent pourcentage affiché
          }

        // Pause légère pour éviter d'encombrer la sortie série
        }

        if (totalWritten == contentLength) {
          Serial.println("\nTéléchargement complet !");
        } else {
          Serial.printf("\nErreur : seulement %d/%d octets ont été écrits.\n", totalWritten, contentLength);
        }

        // Terminer l'opération de mise à jour
        if (Update.end()) {
          if (Update.isFinished()) {
            Serial.println("Mise à jour réussie !");
            Serial.println("Redémarrage en cours...");
            ESP.restart();
          } else {
            Serial.println("Mise à jour non terminée.");
          }
        } else {
          Serial.printf("Erreur de mise à jour : %s\n", Update.errorString());
        }
      } else {
        Serial.println("Pas assez d'espace pour commencer la mise à jour.");
      }
    } else {
      Serial.println("Contenu invalide ou taille du fichier incorrecte.");
    }
  } else {
    Serial.printf("Échec de la requête HTTPS, code de réponse: %d\n", httpCode);
  }

  https.end();  // Terminer la connexion HTTPS
}
// void getFileFromServer() {
//   WiFiClientSecure client;
//   client.setInsecure(); // Set client to allow insecure connections

//   if (client.connect(HOST, PORT)) { // Connect to the server
//     Serial.println("Connected to server");
//     client.print("GET " + String(PATH) + " HTTP/1.1\r\n"); // Send HTTP GET request
//     client.print("Host: " + String(HOST) + "\r\n"); // Specify the host
//     client.println("Connection: close\r\n"); // Close connection after response
//     client.println(); // Send an empty line to indicate end of request headers

//     // SPIFFS.remove("/" + String(FILE_NAME));
//     File file = SPIFFS.open("/" + String(FILE_NAME), "w",false);// Open file in SPIFFS for writing
//     if (!file) {
//       Serial.println("Failed to open file for writing");
//       return;
//     }

//     bool endOfHeaders = false;
//     String headers = "";
//     String http_response_code = "error";
//     const size_t bufferSize = 1024; // Buffer size for reading data
//     uint8_t buffer[bufferSize];

//     // Loop to read HTTP response headers
//     while (client.connected() && !endOfHeaders) {
//       if (client.available()) {
//         char c = client.read();
//         headers += c;
//         if (headers.startsWith("HTTP/1.1")) {
//           http_response_code = headers.substring(9, 12);
//         }
//         if (headers.endsWith("\r\n\r\n")) { // Check for end of headers
//           endOfHeaders = true;
//         }
//       }
//     }

//     Serial.println("HTTP response code: " + http_response_code); // Print received headers

//     // Loop to read and write raw data to file
//     while (client.connected()) {
//       if (client.available()) {
//         size_t bytesRead = client.readBytes(buffer, bufferSize);
//         file.write(buffer, bytesRead); // Write data to file
//       }
//     }
//     file.close(); // Close the file
//     client.stop(); // Close the client connection
//     Serial.println("File saved successfully");
//   }
//   else {
//     Serial.println("Failed to connect to server");
//   }
// }


// void performOTAUpdateFromSPIFFS() {
//   // Open the firmware file in SPIFFS for reading
//   File file = SPIFFS.open("/" + String(FILE_NAME), FILE_READ);
//   if (!file) {
//     Serial.println("Failed to open file for reading");
//     return;
//   }

//   Serial.println("Starting update..");
//   size_t fileSize = file.size(); // Get the file size
//   Serial.println(fileSize);

//   // Begin OTA update process with specified size and flash destination
//   if (!Update.begin(fileSize, U_FLASH)) {
//     Serial.println("Cannot do the update");
//     return;
//   }

//   // Write firmware data from file to OTA update
//   Update.writeStream(file);

//   // Complete the OTA update process
//   if (Update.end()) {
//     Serial.println("Successful update");
//   }
//   else {
//     Serial.println("Error Occurred:" + String(Update.getError()));
//     return;
//   }

//   file.close(); // Close the file
//   Serial.println("Reset in 4 seconds....");
//   delay(4000);
//   ESP.restart(); // Restart ESP32 to apply the update
// }