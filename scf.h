/*
    Project: spiffs_config_file
    Microcontroller: ESP32
    Compiler: Arduino GCC
    Author: Junon M.
    Version: 1.0.0
    Date: 2022/07/04
*/

#ifndef scf_h
#define scf_h
#include "Arduino.h"

class scf
{
  private:
    String _file_name;
    String _file_content;

    void write_txt_file(String path, String content);

  public:

    //----------------------------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------------------------
    scf();
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    // Destructor
    //----------------------------------------------------------------------------------------
    virtual ~scf();
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    // Informs if the file exists
    //----------------------------------------------------------------------------------------
    bool fileExists();
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    // Conversions
    //----------------------------------------------------------------------------------------
    String float2String(float from);
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    // Set Filename
    //----------------------------------------------------------------------------------------
    void setFileName(String FileName);
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    // Reads a previously written key from the file
    //----------------------------------------------------------------------------------------
    String getStr(String Label);
    float getFloat(String Label);
    int getInt(String Label);
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    // Create a new key in the file
    //----------------------------------------------------------------------------------------
    void putStr(String Label, String Value);
    void putFloat(String Label, float Value);
    void putInt(String Label, int Value);
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    // Save keys and values to file
    //----------------------------------------------------------------------------------------
    void commit();
    //----------------------------------------------------------------------------------------

};

#endif /* scf_h */
