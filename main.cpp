#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DESEN_YUKSEKLIK 15
#define MAX_DESEN_GENISLIK 20
#define RESIM_YUKSEKLIK 25
#define RESIM_GENISLIK 80
#define DESEN_KODU_BOYUT 5
#define MAX_PATTERNS 10

struct Desen
{
  char kod[DESEN_KODU_BOYUT];
  int satir_sayisi;
  int sutun_sayisi;
  char karakterler[MAX_DESEN_YUKSEKLIK][MAX_DESEN_GENISLIK + 1];
};

void isPatternFound(char resim[RESIM_YUKSEKLIK][RESIM_GENISLIK+1], struct Desen *desen)
{
  int i, j, k, l;
  int satir = RESIM_YUKSEKLIK;
  int sutun = RESIM_GENISLIK;
  int desenSatir = desen->satir_sayisi;
  int desenSutun = desen->sutun_sayisi;
  bool xx = false;

  for (i = 0; i <= satir - desenSatir; i++)
  {
    for (j = 0; j <= sutun - desenSutun; j++)
    {
      bool match = true;
      for (k = 0; k < desenSatir; k++)
      {
        for (l = 0; l < desenSutun; l++)
        {
          if (desen->karakterler[k][l] != ' ' && resim[i + k][j + l] != desen->karakterler[k][l])
          {
            match = false;
            break;
          }
        }
        if (!match)
        {
          break;
        }
      }
      if (match)
      {
        printf("Bulundu! Kod: %s Konum : (%d, %d)\n", desen->kod, (i+1), (j + 1));
        xx=true;
      }
    }
  }
  if(!xx)
  	printf("Bulunamadi! Kod: %s\n",desen->kod);
}

int main()
{
  FILE *desenDosya = fopen("desenler.txt", "r");
  if (desenDosya == NULL)
  {
    printf("Desenler dosyasi okuma hatasi!\n");
    return -1;
  }

  int desenSayisi;
  fscanf(desenDosya, "%d", &desenSayisi);
  struct Desen desenler[desenSayisi];

  for (int i = 0; i < desenSayisi; i++)
  {
    fscanf(desenDosya, "%s %d %d", desenler[i].kod, &desenler[i].satir_sayisi, &desenler[i].sutun_sayisi);
    fgetc(desenDosya);

    char temp[MAX_DESEN_YUKSEKLIK * (MAX_DESEN_GENISLIK + 1)];

    temp[0] = '\0';
    for (int j = 0; j < desenler[i].satir_sayisi; j++)
    {
      char line[MAX_DESEN_GENISLIK + 1];
      fgets(line, sizeof(line), desenDosya);
      line[strcspn(line, "\n")] = '\0';
      strcat(temp, line);
    }

    int k = 0;
    for (int row = 0; row < desenler[i].satir_sayisi; row++)
    {
      for (int col = 0; col < desenler[i].sutun_sayisi; col++)
      {
        desenler[i].karakterler[row][col] = temp[k++];
      }
    }
  }
  fclose(desenDosya);

  FILE *resimDosya = fopen("resim.txt", "r");
  if (resimDosya == NULL)
  {
    printf("Resim dosyasi okuma hatasi!\n");
    return -1;
  }

  //char resim [25][81];
  //for (int j = 0; j < RESIM_YUKSEKLIK; j++)
  //{
  //   fgets(resim[j], sizeof(resim[j]), resimDosya);
  //    printf("%s", resim[j]);
  // }
  char resim [25][81] = 
  { "aaaa l     aaaa l     AAAA  a           aa                           ***********",
      "a  a l     a  a l     AbbA  b           bb                           **++++++++*",
      "aaaa l     aaaa l     AAAA  c           cc                           **%++++++%*",
      "a  a l     a  a l     AbbA  d           dd                           **%%++++%%*",
      "a  a lllll a  a lllll AbbA  e           ee           000             **%%%++%%%*",
      "                                        aa           000             **%%%++%%%*",
      "                                        bb           000             **%%++++%%*",
      "                                        cc                           **%++++++%*",
      "                                        dd                           **++++++++*",
      "                                        ee                           ***********",
      "********************************************************************************",
      "********************************************************************************",
      "********************************************************************************",
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaad",
      "b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.eeb.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.b.be",
      "                                        aa                                     a",
      "5555555555555555555555555555555555555555bb5555555555555555555555555555555555555b",
      "***************               ***       cc           *           **************c",
      "*             *              ** **      dd          * *          *             d",
      "*            **             **   **     ee   *     *   *         *        *    e",
      "*             *   *        **     **    aa   *    *     *        *             a",
      "*      *      *           **       **   bb   *   *********       *             b",
      "*             *   *      **         **  cc   *                   *             c",
      "*            **         *************** dd   *                   *             d",
      "*             *         *************** ee                       *      *      e" };


 
  fclose(resimDosya);


  for(int i = 0; i < desenSayisi; i++)
  {
    isPatternFound(resim, &desenler[i]);
  }

  return 0;
}
