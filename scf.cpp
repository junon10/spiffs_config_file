/*
    Project: spiffs_config_file
    Microcontroller: ESP32
    Ide: Arduino
    Author: Junon M.
    Version: 1.0.1
    Date: 2022/07/05
*/

#include "scf.h"

#include "FS.h"
#include <SPIFFS.h>

//---------------------------------------------------------------------------------------------------------
scf::scf() {
  _file_name = "/config.ini";
  _file_content = "";
}
//---------------------------------------------------------------------------------------------------------
scf::~scf() {

}
//---------------------------------------------------------------------------------------------------------
bool scf::file_exists() {
  return SPIFFS.exists(_file_name);
}
//---------------------------------------------------------------------------------------------------------
void scf::set_filename(String FileName) {

  _file_name = FileName;
  
  if (_file_name[0] != '/') _file_name = "/" + _file_name;
  
  _file_content = "";

  SPIFFS.begin();
}
//---------------------------------------------------------------------------------------------------------
uint64_t scf::string_2_uint64(String from) {
  String x = from;
  uint64_t y = 0;

  for (int i = 0; i < x.length(); i++) {
    char c = x.charAt(i);
    if (c < '0' || c > '9') break;
    y *= 10;
    y += (c - '0');
  }
  return y;
}
//---------------------------------------------------------------------------------------------------------
String scf::uint64_2_string(uint64_t from) {
  uint64_t input = from;
  String result = "";
  uint8_t base = 10;

  do {
    char c = input % base;
    input /= base;

    if (c < 10)
      c += '0';
    else
      c += 'A' - 10;
    result = c + result;
  } while (input);
  return result;
} 
//---------------------------------------------------------------------------------------------------------
void scf::write_txt_file(String path, String content)
{
  File f = SPIFFS.open(path, "w");
  f.write((uint8_t *)content.c_str(), content.length());
  f.close();
}
//---------------------------------------------------------------------------------------------------------
String scf::get_str(String Label)
{
  FILE *arq;
  char Buff[100];
  char *result;
  int p1 = 0, p2 = 0, len = 0;
  String s = "", s1 = "", s2 = "";
  String fname = "";

  if (!_file_name.substring(0, sizeof("/spiffs")).equals("/spiffs")) {
    fname = "/spiffs" + _file_name;
  }

  arq = fopen(fname.c_str(), "rt");

  if (arq == NULL)  // Se houve erro na abertura
  {
    Serial.println("\n\nProblemas na abertura do arquivo\n\n");
    return "";
  }

  while (!feof(arq))
  {
    // O 'fgets' lê até 99 caracteres ou até encontrar '\n'
    result = fgets(Buff, 100, arq);

    // Se sim
    if (result)
    {
      // Copie o conteúdo da linha que foi lida para uma string
      s = Buff;

      // Tente localizar o separador
      p1 = s.indexOf("=");

      if (p1 != -1) // Se for localizado, execute
      {
        // Obtenha o tamanho do Rótulo (Label)
        len = p1 - 1;

        // Separe somente o Rótulo, isto é,
        // tudo que estiver antes do sinal de igual
        s1 = s.substring(0, len);

        // Tente localizar o Rótulo (label)
        p2 = s1.indexOf(Label.c_str());

        if (p2 != -1) // Se for localizado, execute
        {
          // Rótulo localizado, primeiro feche o arquivo
          fclose(arq);

          // Obtenha o tamanho total da string
          len = s.length();

          // Copie tudo que estiver depois do sinal de igual até
          // o final da linha
          s2 = s.substring(p1 + 1, len);

          // Remova espaços se tiver
          s2.trim();

          return s2;
        }
      }
    }
  }
  fclose(arq);
  return "";
}
//----------------------------------------------------------------------------------------
double scf::get_double(String Label)
{
  return scf::get_str(Label).toDouble();
}
//----------------------------------------------------------------------------------------
long scf::get_long(String Label)
{
  return atol(scf::get_str(Label).c_str());
}
//----------------------------------------------------------------------------------------
uint64_t scf::get_uint64(String Label)
{
  return string_2_uint64(scf::get_str(Label));
}
//----------------------------------------------------------------------------------------
void scf::set_str(String Label, String Value)
{
  _file_content += Label + " = " + Value + "\n";
}
//----------------------------------------------------------------------------------------
void scf::set_double(String Label, double Value)
{
  _file_content += Label + " = " + String(Value, 12) + "\n";
}
//----------------------------------------------------------------------------------------
void scf::set_long(String Label, long Value)
{
  _file_content += Label + " = " + String(Value) + "\n";
}
//----------------------------------------------------------------------------------------
void scf::set_uint64(String Label, uint64_t Value)
{
  _file_content += Label + " = " + scf::uint64_2_string(Value) + "\n";
}
//----------------------------------------------------------------------------------------
void scf::commit()
{
  scf::write_txt_file(_file_name, _file_content);
  _file_content = "";
}
//----------------------------------------------------------------------------------------
