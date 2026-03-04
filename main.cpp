#include <TFT_eSPI.h>
#include <math.h>

TFT_eSPI tft = TFT_eSPI();

uint16_t SKY;
uint16_t MTN;
float t = 0.0;
float phase;

String msg = "Starstuff Playlist: Ship in a Bottle - Fin // Icarus - Bastille // East of Eden - Zella Day // Astronomical - SVRCINA // When Will My Life Begin (Reprise 2) - Mandy Moore // w.o.t.h - Tamino // Forgotten Love - Aurora // Te Guardo - Silvana Estrada // The Moon Will Sing - The Crane Wives // The Beach - Wolf Alice // You Keep Me Crawling - Aurora";
int tx = 0;

int mtns(int x, int W, int H) {
  float u = (float)x / (float)(W - 1);
  float base = H * 0.58;
  float m1 = 20.0 * sinf(u * 2.0 * M_PI * phase);
  float m2 = 12.0 * cosf(u * 2.0 * M_PI * 3.8 + phase);
  float m3 =  6.0 * sinf(u * 2.0 * M_PI * 8.0 + phase);
  int y = (int)(base + m1 + m2 + m3);
  if (y < 0) y = 0;
  if (y >= H) y = H - 1;
  return y;
}

void setup() {
  tft.init();
  tft.setTextWrap(false);
  tft.setRotation(1);
  SKY = tft.color565(18, 4, 38);
  MTN = tft.color565(3, 8, 28);
  phase = (float)random(100) / 100.0;
  tft.fillScreen(SKY);

  int W = tft.width();
  int H = tft.height();

  for (int x = 0; x < W; x++) {
    int ry = mtns(x, W, H);
    tft.drawFastVLine(x, ry, H - ry, MTN);
  }

  tx = W;
}

void loop() {
  int W = tft.width();
  int H = tft.height();

  for (int x = 0; x < W; x++) {
    int ms = mtns(x, W, H);
    float u = (float)x / (float)W;

    int rayH = (int)(ms * (0.5 + 0.3 * sinf(u * 6.0 + t * 0.5)));
    if (rayH < 10) rayH = 10;

    tft.drawFastVLine(x, 0, ms, SKY);

    int sc = (int)(t * 60.0);
    int gap = 4;
    for (int i = 0; i < rayH / gap; i++) {
      int yL = (sc + i * gap) % rayH;
      int y  = ms - 1 - yL;
      if (y < 0) continue;

      float f = (float)yL / (float)rayH;
      float r = f * 180;
      float g = 220 - f * 160;
      float b = 100 + f * 100;

      float br = 1.0 - f * 0.75;
      r = r * br;
      g = g * br;
      b = b * br;

      tft.drawPixel(x, y, tft.color565((int)r, (int)g, (int)b));
    }
  }

  t += 0.03;

  int tw = msg.length() * 6;
  int sy = H - 12;

  tft.fillRect(0, sy - 2, W, 14, MTN);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, MTN);
  tft.setCursor(tx, sy);
  tft.print(msg);

  tx -= 2;
  if (tx < -tw) tx = W;
}