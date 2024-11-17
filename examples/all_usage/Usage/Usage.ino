#include <Ebase.h>

EBase eeprom(512); // Initialize EEPROM with 512 bytes

// Variables to store the data read from EEPROM
String email, password, ssid, wifiPassword, updatedPassword;

void setup() {
    Serial.begin(9600);
    Serial.println("EBase Library Usage Example");

    // Step 1: Flash (Clear) the EEPROM
    Serial.println("\n--- Flashing EEPROM ---");
    eeprom.flash();

    // Step 2: Write data to EEPROM
    Serial.println("\n--- Writing Data to EEPROM ---");
    eeprom.write("email", "user@example.com");
    eeprom.write("password", "securePassword123");
    eeprom.write("ssid", "MyWiFiNetwork");
    eeprom.write("wifi_password", "WiFiPass123");

    // Step 3: Read data back from EEPROM
    Serial.println("\n--- Reading Data from EEPROM ---");
    email = eeprom.read("email");
    password = eeprom.read("password");
    ssid = eeprom.read("ssid");
    wifiPassword = eeprom.read("wifi_password");

    // Step 4: Update existing data
    Serial.println("\n--- Updating Data in EEPROM ---");
    eeprom.write("password", "newPassword456");
    updatedPassword = eeprom.read("password");
}

void loop() {
    // Print the data to Serial Monitor with a 3000 ms delay
    Serial.println("Stored Data:");
    Serial.println("Email: " + email);
    delay(3000); // 3 seconds delay

    Serial.println("Password: " + password);
    delay(3000); // 3 seconds delay

    Serial.println("SSID: " + ssid);
    delay(3000); // 3 seconds delay

    Serial.println("WiFi Password: " + wifiPassword);
    delay(3000); // 3 seconds delay

    Serial.println("\n--- Updated Data ---");
    Serial.println("Updated Password: " + updatedPassword);
    delay(3000); // 3 seconds delay
}
