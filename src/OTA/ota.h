
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
#define FORCE_UPDATE 0

// void getFileFromServer() ;
// void performOTAUpdateFromSPIFFS();
void updateFirmware(const char* firmwareUrl);
void updateOtaView(float progress);
void createOTAView(String lastVersion);
lv_obj_t * arcUpdating;
lv_obj_t * labelPercentageUpdating;

void checkOTAUpdate(){
 
   
// get lastversion
  String response  = sendPostRequest(SERVER_API_LASTVERSION, "", SERVER_PORT, {}, 0 )  ;
  JsonDocument doc;
  deserializeJson(doc, response);
  float last_version =  doc[String("ESP")];
  float current_version =  String(BLYNK_FIRMWARE_VERSION).toFloat();
  Serial.printf("Version ESP : %.2f , current : %.2f \r\n",last_version,current_version);
  if( FORCE_UPDATE == 1 || (last_version > current_version) ){
    //update
    Serial.printf("updating to Firmware %.2f...\r\n",last_version);
    createOTAView(String(last_version));
    updateFirmware(URL);
  }else{
     Serial.println("app already in date");
  }
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
            // Serial.printf("Avancement : %.2f%%\r", progress);
            previousProgress = progress;  // Met à jour le précédent pourcentage affiché
            updateOtaView(progress);
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
              lv_label_set_text(labelPercentageUpdating,"Mise à jour réussie !");
            Serial.println("Redémarrage en cours...");
            ESP.restart();
          } else {
            Serial.println("Mise à jour non terminée.");
          }
        } else {
          Serial.printf("Erreur de mise à jour : %s\n", Update.errorString());
           lv_label_set_text(labelPercentageUpdating, Update.errorString());
           delay(2000);
            ESP.restart();
        }
      } else {
        Serial.println("Pas assez d'espace pour commencer la mise à jour.");
         lv_label_set_text(labelPercentageUpdating, "Pas assez d'espace pour commencer la mise à jour.");
      }
    } else {
      Serial.println("Contenu invalide ou taille du fichier incorrecte.");
    }
  } else {
    Serial.printf("Échec de la requête HTTPS, code de réponse: %d\n", httpCode);
  }

  https.end();  // Terminer la connexion HTTPS
}

  
void createOTAView(String lastVersion){
     lv_obj_t * otaView;
     otaView =lv_win_create(lv_scr_act(),45);
    lv_win_add_title(otaView, "Mise à jour en cours ...");

     lv_obj_t * cont = lv_win_get_content(otaView); 

  

    static lv_style_t style_bg;
    lv_style_init(&style_bg);
    lv_style_set_bg_color(&style_bg, lv_color_black());  // Couleur de fond blanche
    // Appliquer le style à la fenêtre
    lv_obj_add_style(cont, &style_bg, LV_PART_MAIN);

   /*Create an Arc*/
     arcUpdating = lv_arc_create(cont);
    lv_obj_set_size(arcUpdating, 100, 100);
    lv_arc_set_bg_angles(arcUpdating, 0, 360);
      
    lv_arc_set_value(arcUpdating, 0);
    lv_obj_clear_flag(arcUpdating, LV_OBJ_FLAG_CLICKABLE);
     lv_obj_remove_style(arcUpdating, NULL, LV_PART_KNOB);
    lv_obj_align_to(arcUpdating, cont, LV_ALIGN_CENTER, 0  , 0);
     lv_obj_add_style(arcUpdating, &style_bg, LV_PART_MAIN);

       labelPercentageUpdating = lv_label_create(cont);
  lv_obj_align(labelPercentageUpdating, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_font(labelPercentageUpdating,&lv_font_montserrat_16,LV_PART_MAIN);
  lv_label_set_text(labelPercentageUpdating, "0%");

   lv_obj_t *lblVersion = lv_label_create(cont);
  lv_obj_align(lblVersion, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_text_font(lblVersion,&lv_font_montserrat_16,LV_PART_MAIN);
  lv_label_set_text(lblVersion, lastVersion.c_str());
      
  loop();


}
void updateOtaView(float progress){
    lv_arc_set_value(arcUpdating,progress);
    lv_label_set_text_fmt(labelPercentageUpdating, "%.0f%%", progress);
    loop();
    
}