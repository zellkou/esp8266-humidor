// Start of main function that performs HTTP OTA /// 
void checkForUpdates() {
  uint8_t mac[6];
  char macAddr[14];
  WiFi.macAddress( mac );
  ///sprintf(macAddr,"%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); /// small letters at MAC address
  sprintf(macAddr, "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); /// capital letters at MAC address
  terminal.println(macAddr);
  String fwURL = String( fwUrlBase );
  fwURL.concat( macAddr );
  String fwVersionURL = fwURL;
  fwVersionURL.concat( ".version" );
  Serial.println( "Checking for firmware updates." );
  Serial.print( "MAC address: " );
  Serial.println( macAddr );
  ///terminal.printf("\nChecking for firmware updates.\nMAC address: %s ",mac);
  terminal.printf("\nChecking for firmware updates.\nMAC address: ");
  terminal.print( macAddr );
  Serial.print( "Firmware version URL: " );
  Serial.println( fwVersionURL );
  ///terminal.printf("\nFirmware version URL: %s ",fwVersionURL);
  terminal.printf("\nFirmware version URL: ");
  terminal.print(fwVersionURL);
  terminal.flush();

  HTTPClient httpClient;
  httpClient.begin( fwVersionURL );
  int httpCode = httpClient.GET();
  if( httpCode == 200 ) {
    String newFWVersion = httpClient.getString();

    Serial.print( "Current firmware version: " );
    Serial.println( FW_VERSION );
    Serial.print( "Available firmware version: " );
    Serial.println( newFWVersion );
    ///terminal.printf("\nCurrent firmware version: %s  Available firmware version: %s ",FW_VERSION,newFWVersion);
    terminal.print("\nCurrent firmware version: ");
    terminal.print(FW_VERSION);  
    terminal.print("\nAvailable firmware version: ");
    terminal.println(newFWVersion);
    terminal.flush();
    int newVersion = newFWVersion.toInt();

    if( newVersion > FW_VERSION ) {
      Serial.println( "Preparing to update" );
    terminal.println( "\nPreparing to update" ); 
    terminal.flush();
      String fwImageURL = fwURL;
      fwImageURL.concat( ".bin" );
      t_httpUpdate_return ret = ESPhttpUpdate.update( fwImageURL );

      switch(ret) {
        case HTTP_UPDATE_FAILED:
          Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          terminal.printf("\nHTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          terminal.flush();
          break;

        case HTTP_UPDATE_NO_UPDATES:
          Serial.println("HTTP_UPDATE_NO_UPDATES");
          terminal.println("\nHTTP_UPDATE_NO_UPDATES\n");
          terminal.flush();
          break;
      }
    }
    else {
      Serial.println( "Already on latest version" );
      terminal.println( "\nAlready on latest version\n" );
      terminal.flush();
    }
  }
  else {
    Serial.print( "Firmware version check failed, got HTTP response code " );
    Serial.println( httpCode );
    terminal.printf( "\nFirmware version check failed, got HTTP response code : %d\n",httpCode );
    terminal.flush();
  }
  httpClient.end();
}
// End of main function that performs HTTP OTA /// 

// YOU NEED SOMEWHERE THIS, I PUT IT on LOOP
//if(HTTP_OTA) {
    /// shall I stop timers and Blynk related in order to ensure succesful WEB OTA ??? ///
//    checkForUpdates();
