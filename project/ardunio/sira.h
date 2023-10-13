void hazirlaSira();
void ekleRezistans(float x);
void ekleMerkez(float x);
void gosterMerkez();
void gosterRezistans();

typedef enum {SDOWN = -3,MDOWN = -2,BDOWN = -1,MIXED = 0,SUP = 1,MUP = 2,BUP = 3} degisim_t;
degisim_t degisimMerkez();
degisim_t degisimRezistans();
degisim_t gelismisDegisimRezistans();
degisim_t gelismisDegisimMerkez();
