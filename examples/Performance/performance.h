#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#define MAX_OFFSET 20*8-64

class Printer: public Print
{
public:
  Printer();
  Printer(Arduboy *boy);
  virtual size_t write(uint8_t);

  char buffer[320]; // 16x20 textual

  int offset = 0;
  int cursor_x = 0;
  int cursor_y = 0;
  Arduboy *arduboy;
};

Printer::Printer(){}
Printer::Printer(Arduboy *boy)
{
	*arduboy = *boy;
}

size_t Printer::write(uint8_t c)
{
	if (c == '\n') {
		cursor_y+=1;
	} else {
		buffer[cursor_y*16+cursor_x]=c;
		cursor_x+=1;
	}
}

#endif