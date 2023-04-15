#include <iostream>
#include <graphics.h>
#include <cstring>

const int screenWidth = 1800;
const int screenHeight = 900;

using namespace std;

struct produs
{
  int cod;
  char denumire[101];
};

produs p[300], aux[300];

void background ()
{
  setfillstyle (SOLID_FILL, 19);
  bar (0, 0, screenWidth, screenHeight);
}

void text (int x, int y, char *text, int color)
{
  settextstyle (SANS_SERIF_FONT, HORIZ_DIR, 2);
  setcolor (color);
  outtextxy (x, y, text);
}

void citire (int i, int n)
{
  if (i < n)
    {
      cin >> p[i].cod;
      cin.getline (p[i].denumire, 101);
      citire (i + 1, n);
    }
  else
    {
      cin >> p[i].cod;
      cin.getline (p[i].denumire, 101);
    }
}

void refacere_cod (int n, char *zero)
{
  if (n / 1000 == 0)
    strcat (zero, "0");
  if (n / 100 == 0)
    strcat (zero, "0");
  if (n / 10 == 0)
    strcat (zero, "0");
  char aux[5];
  itoa (n, aux, 10);
  strcat (zero, aux);
}

void afisare_casete (int i, int n, int x, int y, int z, int h, int t, int b,
		int culoare)
{
  if (i <= n)
    {
      setcolor (culoare);
      setfillstyle (SOLID_FILL, culoare);
      rectangle (x, t, y, b);
      floodfill (x + 1, t + 1, culoare);

      char aux[6];
      strcpy (aux, "");
      refacere_cod (p[i].cod, aux);
      text (z, h, aux, WHITE);
      delay (700);
      afisare_casete (i + 1, n, x + 200, y + 200, z + 200, h, t, b, culoare);
    }
}

void afisare_casete_text (int i, int n, int x, int y, int z, int h, int t, int b,
		     int culoare)
{
  if (i <= n)
    {
      setcolor (culoare);
      setfillstyle (SOLID_FILL, culoare);
      rectangle (x, t, y, b);
      floodfill (x + 1, t + 1, culoare);

      char aux[6];
      strcpy (aux, "");
      refacere_cod (p[i].cod, aux);
      text (z, h, aux, WHITE);
      text (z - strlen (p[i].denumire) * 3, h + 50, p[i].denumire, LIGHTGRAY);
      delay (700);
      afisare_casete_text (i + 1, n, x + 200, y + 200, z + 200, h, t, b,
			   culoare);
    }
}

void afisare (int s, int d, int x, int y, int z, int h, int t, int b, int culoare)
{
  int m;
  if (s < d)
    {
      afisare_casete (s, d, x, y, z, h, t, b, culoare);
      m = (s + d) / 2;
      afisare (s, m, x, y, z, h + 90, t + 90, b + 90, culoare);
    }
  else
    {
      afisare_casete (s, d, x, y, z, h, t, b, culoare);
    }
}

void sortare (produs x[], int s, int d)
{
  if (s < d)
    {
      int m = (s + d) / 2;
      sortare (x, s, m);
      sortare (x, m + 1, d);
      //Interclasare
      int i = s, j = m + 1, k = 0;
      while (i <= m && j <= d)
	if (p[i].cod < p[j].cod)
	  aux[++k] = p[i++];
	else
	  aux[++k] = p[j++];
      while (i <= m)
	aux[++k] = p[i++];
      while (j <= d)
	aux[++k] = p[j++];
      for (i = s, j = 1; i <= d; i++, j++)
	p[i] = aux[j];
    }
}

int main ()
{
  int n;
  cout << "Numarul de produse noi: ";
  cin >> n;
  cout << "COD si DENUMIRE:" << endl;
  citire (1, n);

  //Creare fereastra cu grafica
  initwindow (screenWidth, screenHeight,
	      "Lista ordonata cu produse si coduri", 0, 0);

  background ();

  setcolor (WHITE);
  settextstyle (BOLD_FONT, HORIZ_DIR, 3);
  outtextxy (530, 60, "Lista ordonata cu produse si coduri");
  afisare_casete_text (1, n, 140, 200, 150, 180, 160, 220, WHITE);

  int m = (1 + n) / 2;
  afisare (1, m, 140, 200, 150, 310, 290, 350, LIGHTGREEN);
  afisare (m + 1, n, 940, 1000, 950, 310, 290, 350, 8);

  text (750, 550, "Interclasari repetate", WHITE);

  sortare (p, 1, n);
  afisare_casete_text (1, n, 140, 200, 150, 650, 630, 690, 9);

  getch ();
  closegraph ();
  return 0;
}
