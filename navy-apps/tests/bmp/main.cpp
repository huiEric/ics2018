#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ndl.h>

int main() {
  NDL_Bitmap *bmp = (NDL_Bitmap*)malloc(sizeof(NDL_Bitmap));
  NDL_LoadBitmap(bmp, "/share/pictures/projectn.bmp");
  assert(bmp->pixels);
  NDL_OpenDisplay(bmp->w, bmp->h);
  NDL_DrawRect(bmp->pixels, 0, 0, bmp->w, bmp->h);
  printf("w=%d h=%d\n", bmp->w, bmp->h);
  NDL_Render();
  NDL_CloseDisplay();
  printf("done\n");
  while (1);
  return 0;
}
