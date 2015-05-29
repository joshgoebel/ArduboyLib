#ifndef PERFORMANCE_H
#define PERFORMANCE_H

class Printer: public Print
{
public:
  // ArduboyCustom();
  virtual size_t write(uint8_t);

  char buffer[320]; // 16x20 textual

};

size_t Printer::write(uint8_t c)
{

}


#endif
