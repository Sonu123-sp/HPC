#include <stdio.h>
#include <math.h>

/******************************************************************************
 * This program takes an initial estimate of m and c and finds the associated 
 * rms error. It is then as a base to generate and evaluate 8 new estimates, 
 * which are steps in different directions in m-c space. The best estimate is 
 * then used as the base for another iteration of "generate and evaluate". This 
 * continues until none of the new estimates are better than the base. This is
 * a gradient search for a minimum in mc-space.
 * 
 * To compile:
 *   cc -o lr_coursework 108_a.c -lm
 * 
 * To run:
 *   ./lr_coursework
 * 
 * Dr Kevan Buckley, University of Wolverhampton, 2018
 *****************************************************************************/


typedef struct point_t {
  double x;
  double y;
} point_t;

int n_data = 1000;

point_t data[];

void print_data() {
  int i;
  printf("x,y\n");
  for(i=0; i<n_data; i++) {
    printf("%0.2lf,%0.2lf\n", data[i].x, data[i].y);
  }
}

int main() {
  print_data();
  return 0;
}

point_t data[] = {
  {83.74,106.34},{73.39,113.86},{77.96,116.13},{79.05,99.53},
  {78.42,123.49},{66.05,92.78},{65.28,89.23},{82.08,112.68},
  {76.00,89.05},{69.45,97.14},{82.39,118.99},{60.34,80.15},
  {57.04,89.13},{80.20,127.97},{84.48,105.81},{78.12,133.41},
  {70.52,93.88},{93.03,125.69},{70.05,95.63},{68.58,89.01},
  { 6.70,32.41},{ 6.10,15.84},{16.40,49.00},{32.23,43.99},
  {56.73,70.58},{64.22,101.28},{56.10,77.67},{55.15,76.24},
  {18.14,27.20},{35.20,69.89},{56.60,74.69},{21.74,44.62},
  {18.17,37.32},{73.48,96.31},{85.17,126.58},{84.95,124.48},
  {79.38,121.14},{95.12,130.68},{21.14,49.79},{ 2.36,32.37},
  {40.79,64.39},{44.71,59.59},{63.84,91.03},{40.63,55.66},
  { 4.75,32.97},{34.81,54.46},{27.77,55.46},{87.10,120.46},
  {31.41,49.15},{34.79,50.51},{21.17,49.44},{ 8.87,25.18},
  {96.25,125.31},{32.01,51.61},{81.53,119.04},{ 9.78,35.30},
  {70.64,105.43},{76.65,115.25},{48.74,71.25},{87.70,123.83},
  { 6.78,50.34},{83.93,124.53},{ 7.81,33.51},{32.90,58.00},
  {38.81,76.13},{84.21,110.96},{26.93,56.53},{35.68,66.30},
  {89.43,128.18},{40.25,59.29},{ 0.29,20.10},{27.46,49.81},
  {59.70,87.64},{44.81,81.52},{ 4.25,49.98},{57.40,87.62},
  { 6.23,25.46},{37.29,57.19},{31.14,43.38},{82.59,101.25},
  {23.18,49.57},{84.95,128.84},{29.80,41.03},{12.78,46.02},
  {15.66,45.37},{99.80,130.02},{94.17,132.91},{22.60,60.75},
  {61.72,81.84},{99.84,123.21},{ 0.26,23.42},{56.43,83.42},
  {95.09,136.25},{93.48,136.33},{69.29,104.04},{97.09,127.39},
  {56.57,81.25},{10.12,45.78},{78.95,115.47},{59.81,76.07},
  {22.57,30.01},{88.86,123.23},{25.04,48.17},{ 2.15,16.57},
  { 0.60,22.46},{23.62,57.28},{71.99,109.50},{99.72,132.03},
  {50.01,81.97},{ 9.47,27.03},{ 4.77,17.19},{18.97,55.61},
  { 7.00,35.20},{22.59,63.88},{44.67,69.17},{80.60,96.96},
  {58.54,100.03},{83.99,119.83},{49.74,82.94},{80.87,116.76},
  { 1.43,28.16},{97.12,109.29},{ 8.72,45.48},{ 0.16,17.61},
  {42.41,66.50},{60.60,106.80},{70.66,110.42},{45.21,58.05},
  {22.51,35.63},{97.11,126.70},{88.39,134.12},{92.45,102.06},
  {24.94,48.84},{10.11,43.11},{85.41,124.57},{ 1.06,18.21},
  {12.83,42.16},{97.76,136.25},{65.19,106.28},{41.08,67.65},
  {73.42,108.37},{ 1.90,19.83},{87.83,109.92},{31.08,75.47},
  {26.01,51.85},{16.81,30.60},{73.31,110.27},{ 3.17,17.35},
  {73.47,110.59},{59.71,83.99},{91.47,109.86},{55.68,69.73},
  {39.19,75.61},{33.03,72.17},{65.06,88.92},{12.71,44.96},
  {60.87,90.97},{98.35,140.22},{12.03,24.38},{17.66,24.44},
  {10.55,31.26},{70.28,99.49},{29.17,65.26},{29.72,59.44},
  {93.11,130.73},{10.31,38.89},{ 7.84,28.59},{95.04,114.02},
  {17.64,37.28},{15.99,49.27},{99.33,118.30},{75.31,109.18},
  {37.72,50.12},{24.63,34.10},{25.68,46.44},{62.28,71.69},
  {73.85,104.53},{ 8.77,33.27},{41.19,77.99},{97.40,116.13},
  {12.02,37.19},{ 9.29,34.87},{31.27,52.74},{17.94,43.58},
  {16.40,25.59},{55.52,96.88},{94.83,127.70},{68.98,110.26},
  {31.23,54.59},{49.17,63.18},{19.53,38.67},{83.68,101.98},
  {68.82,96.06},{86.77,124.87},{63.85,106.88},{52.77,98.17},
  {59.42,89.11},{27.27,52.85},{61.01,90.34},{80.10,116.89},
  {73.81,112.05},{32.67,55.78},{ 5.19,14.02},{49.60,67.97},
  {85.97,103.76},{12.63,25.81},{63.11,97.75},{ 8.28,32.23},
  {39.62,61.00},{44.63,70.61},{80.02,109.81},{67.41,91.42},
  {56.76,81.23},{65.41,97.47},{35.93,64.01},{61.15,93.82},
  {15.85,38.57},{34.33,58.62},{86.53,111.39},{57.52,70.74},
  {80.21,117.90},{92.02,129.92},{71.09,110.89},{56.23,70.38},
  {49.93,73.71},{93.20,125.76},{11.74,37.94},{22.60,55.90},
  {86.19,114.25},{22.65,66.55},{20.98,44.70},{18.38,42.85},
  {66.80,71.14},{84.56,105.13},{83.69,106.03},{86.16,136.85},
  {73.01,115.11},{21.03,42.77},{ 5.68,35.39},{26.00,47.86},
  {49.04,70.02},{42.01,67.58},{63.84,85.45},{33.99,69.31},
  {82.27,131.39},{23.91,50.83},{71.22,99.28},{50.90,74.42},
  {63.43,127.34},{64.52,101.94},{26.16,46.94},{93.75,135.33},
  {24.45,60.31},{27.07,59.56},{ 6.63,30.60},{96.60,103.76},
  {84.70,100.29},{40.94,60.39},{20.97,72.10},{52.04,88.50},
  {29.82,67.23},{49.00,81.70},{ 6.81,26.55},{74.02,127.44},
  {11.94,22.42},{76.65,85.37},{20.12,51.68},{30.81,57.82},
  {84.34,110.19},{24.62,50.82},{ 2.39,29.61},{71.27,119.05},
  { 7.65,27.22},{52.06,76.39},{18.30,40.25},{ 7.64,39.02},
  {81.37,106.20},{11.52,27.99},{40.32,45.07},{78.58,96.79},
  {95.95,121.82},{27.46,63.07},{55.87,94.45},{ 0.70,24.57},
  {97.99,132.86},{33.66,48.20},{90.80,151.81},{26.50,52.14},
  {43.63,58.92},{89.43,133.69},{86.56,118.66},{62.23,64.55},
  {24.14,57.02},{57.77,94.64},{42.50,74.10},{51.19,77.93},
  {12.87,44.92},{60.37,77.71},{33.65,73.18},{23.54,49.79},
  { 4.28,23.60},{60.19,102.95},{34.91,64.20},{88.52,103.35},
  {58.87,90.38},{93.30,118.97},{56.23,97.15},{91.77,116.53},
  {69.16,91.38},{42.31,66.76},{47.95,72.87},{25.19,49.40},
  {86.48,119.90},{40.74,69.72},{43.28,74.73},{98.01,106.18},
  { 7.77,36.49},{94.93,125.37},{56.76,70.90},{ 2.03,26.08},
  { 8.43,32.71},{53.25,108.51},{42.03,79.29},{70.05,99.48},
  {28.46,47.84},{52.90,65.89},{13.78,27.18},{34.73,79.88},
  {58.46,88.84},{90.98,131.32},{ 6.97,23.44},{42.35,84.44},
  {97.08,125.68},{48.45,70.66},{60.29,86.37},{49.84,57.71},
  {19.48,52.06},{92.02,129.81},{58.61,96.17},{18.01,52.96},
  {30.69,50.44},{75.70,98.74},{86.50,110.18},{94.28,139.99},
  {27.65,44.94},{20.51,49.15},{95.70,113.23},{14.88,32.87},
  {13.01,42.81},{61.35,84.81},{42.95,70.86},{33.19,37.43},
  {54.06,69.36},{47.79,68.21},{37.46,66.41},{24.05,53.35},
  {91.70,128.14},{43.79,49.26},{22.27,28.06},{81.85,107.34},
  { 2.84,26.03},{54.53,94.13},{83.91,101.50},{78.32,96.69},
  { 7.44,36.02},{94.55,131.05},{46.17,68.56},{47.07,65.63},
  {62.94,88.22},{37.56,69.79},{99.54,127.49},{23.76,20.87},
  {82.13,121.06},{39.69,52.19},{12.26,31.42},{84.10,129.77},
  {53.53,78.33},{73.41,110.28},{36.68,63.60},{16.80,45.02},
  { 7.14,36.68},{42.08,71.80},{59.56,107.04},{41.23,73.06},
  {86.11,115.39},{71.75,98.85},{94.78,127.67},{20.46,36.27},
  {32.55,75.12},{73.01,108.35},{50.16,88.92},{76.51,104.09},
  {55.23,78.03},{64.48,97.81},{75.78,109.67},{48.27,101.74},
  {13.65,37.06},{96.59,123.13},{ 9.52,23.72},{58.56,77.86},
  {14.02,58.67},{54.21,67.92},{25.33,63.98},{98.19,134.54},
  {23.06,39.93},{46.83,59.60},{72.45,100.56},{ 8.78,12.39},
  {67.85,110.33},{74.42,96.69},{70.35,89.57},{79.86,87.27},
  {51.62,92.07},{23.21,43.83},{ 1.10,45.80},{11.62,50.67},
  {67.71,101.40},{32.18,60.45},{65.00,79.10},{37.65,80.13},
  {78.68,116.54},{ 2.97,35.03},{20.43,34.06},{98.46,126.72},
  {28.90,63.72},{57.71,64.73},{28.10,48.16},{55.50,75.17},
  {23.52,51.43},{11.55,34.28},{93.45,125.26},{ 7.74,35.97},
  {99.28,125.32},{93.31,129.15},{67.44,92.65},{47.81,90.68},
  {27.28,50.50},{74.30,96.40},{37.61,50.42},{70.69,106.23},
  {65.21,105.68},{59.51,96.35},{85.72,124.26},{68.29,90.02},
  {26.36,47.68},{79.02,107.46},{61.82,79.06},{12.44,40.21},
  {67.46,93.41},{74.45,95.69},{62.39,101.43},{40.92,76.28},
  {91.90,124.93},{88.86,116.67},{56.85,92.67},{81.09,111.36},
  {56.09,77.71},{40.53,61.71},{67.86,101.91},{63.20,94.65},
  {31.41,62.11},{79.61,101.83},{33.32,70.06},{91.68,114.80},
  {89.03,123.14},{89.69,135.65},{37.56,57.58},{97.65,124.36},
  {87.50,120.56},{23.61,43.56},{53.59,90.38},{13.68,27.00},
  {92.77,142.42},{79.97,95.35},{49.32,69.95},{ 8.45,31.33},
  {57.25,99.90},{86.61,91.37},{53.29,111.56},{86.31,124.69},
  {11.88,36.51},{ 9.14,20.15},{99.57,159.36},{ 6.12,35.23},
  {10.58,25.41},{70.37,101.96},{52.44,73.19},{ 4.59,36.48},
  {91.91,119.19},{ 2.21,26.61},{82.30,110.67},{77.81,114.88},
  {85.43,120.93},{31.16,46.24},{71.60,97.68},{50.43,97.09},
  {32.08,53.51},{80.72,120.18},{15.79,43.38},{89.43,120.66},
  {86.62,126.08},{71.40,106.75},{97.96,140.90},{72.58,115.59},
  {87.40,122.87},{17.73,25.54},{91.01,120.51},{68.14,100.61},
  {47.56,76.98},{ 0.17,30.13},{17.60,43.35},{44.43,68.59},
  {23.39,58.25},{44.67,63.18},{ 1.49, 6.99},{47.53,59.73},
  {92.72,139.16},{71.00,119.66},{ 3.23,25.45},{90.94,129.26},
  {84.62,121.43},{24.91,45.74},{77.20,103.91},{34.40,50.34},
  {65.07,84.03},{61.97,91.46},{17.00,48.85},{88.77,116.15},
  {11.65,29.84},{29.62,61.89},{44.19,80.67},{12.99,44.45},
  {59.13,90.89},{80.87,101.25},{ 0.62,49.37},{95.45,131.92},
  {21.49,53.63},{73.19,104.63},{47.94,75.73},{61.52,96.93},
  {77.57,110.03},{56.90,84.44},{71.63,106.43},{ 7.28,41.55},
  { 6.10,20.51},{55.83,88.97},{63.35,79.25},{21.40,33.97},
  {42.88,79.00},{99.78,129.69},{28.85,51.85},{29.17,56.19},
  {82.46,120.73},{39.16,75.27},{23.55,56.73},{91.77,151.17},
  {86.84,100.56},{95.11,135.84},{ 3.81,29.30},{ 3.01, 9.88},
  {91.61,131.55},{20.07,38.71},{78.58,106.18},{71.69,85.02},
  {58.34,81.29},{11.17,48.86},{92.10,123.10},{33.79,59.43},
  {41.90,85.35},{34.73,56.23},{15.52,29.19},{10.70,36.36},
  {16.63,44.55},{64.90,94.69},{56.40,72.86},{96.02,134.14},
  {94.06,135.66},{81.44,110.23},{61.28,82.70},{86.17,133.47},
  {10.26,44.22},{48.77,75.52},{87.55,117.57},{98.60,132.42},
  {83.15,124.33},{70.18,85.08},{37.69,52.66},{70.69,107.51},
  {23.17,40.86},{11.11,33.19},{ 2.60,16.37},{96.02,122.01},
  {63.31,90.15},{34.63,66.56},{55.82,90.79},{25.40,50.60},
  { 7.06,38.27},{12.53,21.48},{ 4.66,14.08},{14.07,38.83},
  {89.02,115.45},{56.75,78.71},{75.35,88.46},{10.74,32.40},
  {48.46,78.69},{50.88,90.85},{21.50,55.96},{64.18,106.00},
  {29.80,50.60},{36.22,54.69},{31.54,46.65},{44.07,52.18},
  {76.01,87.63},{79.40,94.40},{98.57,135.11},{73.75,86.73},
  {32.81,60.28},{94.83,127.77},{59.86,100.44},{91.17,114.51},
  {12.45,36.03},{96.12,120.33},{75.38,112.33},{96.21,128.60},
  {27.28,43.65},{39.84,79.21},{42.42,61.93},{ 3.14,18.36},
  {89.49,134.56},{ 8.81,23.46},{90.18,119.62},{20.01,54.51},
  {14.96,42.60},{73.66,108.71},{79.39,105.20},{53.14,89.57},
  {87.37,103.38},{75.70,124.08},{22.89,46.74},{32.28,75.99},
  {52.45,73.07},{ 9.29,33.95},{75.06,94.59},{58.17,95.66},
  {46.06,62.02},{76.49,105.19},{17.85,52.56},{69.27,107.40},
  {27.00,32.43},{63.55,95.03},{54.19,112.48},{ 1.77,-0.91},
  {91.14,131.90},{49.38,77.77},{57.64,87.83},{59.84,100.60},
  { 1.17,20.81},{70.60,112.33},{26.79,46.76},{75.93,103.25},
  {53.28,98.53},{52.44,73.11},{82.39,111.91},{84.95,113.72},
  {75.00,114.27},{57.56,84.28},{50.70,67.68},{26.36,69.76},
  {41.88,72.04},{ 2.29, 8.78},{29.33,69.36},{ 0.39, 9.25},
  {38.82,53.53},{35.39,63.67},{ 4.59,38.87},{ 7.21,34.25},
  {18.96,39.42},{30.84,60.42},{70.07,99.18},{97.73,143.94},
  {65.34,97.35},{93.44,125.63},{66.65,100.86},{39.62,69.03},
  {26.26,45.54},{75.41,117.77},{66.81,85.59},{18.88,39.74},
  {25.60,57.85},{89.71,128.71},{25.73,54.25},{ 6.42,35.83},
  {54.34,90.64},{30.92,52.50},{79.92,109.17},{37.04,48.19},
  {90.13,105.54},{ 1.86,15.53},{84.30,126.26},{47.55,88.77},
  {97.19,128.94},{72.28,101.30},{15.77,47.08},{75.83,108.56},
  {60.49,106.00},{50.72,91.64},{17.36,36.36},{22.38,65.07},
  {45.71,73.00},{18.96,38.13},{59.62,95.16},{ 3.62, 9.04},
  {14.39,46.96},{29.11,50.08},{ 6.08,40.14},{71.40,90.42},
  {93.40,121.75},{80.18,122.34},{41.58,70.11},{30.19,62.87},
  {15.58,39.65},{ 2.04,34.20},{13.30,27.91},{ 5.90,38.42},
  {86.92,99.01},{39.11,75.84},{52.97,94.99},{29.49,54.34},
  {92.40,141.60},{95.25,117.77},{89.83,118.20},{17.93,32.44},
  {67.51,108.68},{71.79,92.84},{26.96,30.39},{95.58,137.89},
  {37.41,75.87},{28.77,53.56},{31.51,60.71},{89.02,103.92},
  { 6.57,24.83},{46.65,60.05},{87.61,133.66},{55.43,91.77},
  {99.61,114.04},{ 8.58,24.28},{72.64,93.69},{64.98,84.64},
  {26.78,62.76},{48.30,89.07},{46.45,83.27},{65.05,86.62},
  {87.70,104.60},{52.55,75.05},{94.38,126.14},{49.67,60.46},
  {79.60,117.39},{84.91,110.25},{72.88,96.21},{24.20,50.59},
  {82.32,102.81},{35.32,51.30},{63.80,83.86},{90.49,112.62},
  {70.10,116.34},{40.18,66.98},{88.93,135.84},{49.86,96.62},
  { 6.19,35.19},{94.13,110.02},{92.73,127.53},{29.71,52.48},
  {28.99,37.23},{85.58,116.09},{97.50,141.54},{ 1.13,26.22},
  {95.21,117.79},{35.68,64.99},{90.78,123.59},{40.28,83.34},
  {93.53,120.60},{99.16,130.41},{69.71,103.90},{62.89,75.23},
  {95.35,157.36},{28.76,53.43},{18.23,37.25},{36.28,71.43},
  {38.14,61.35},{34.55,61.35},{28.16,39.07},{74.42,90.63},
  {39.54,69.77},{81.82,118.29},{36.13,58.44},{87.52,125.78},
  {59.17,95.21},{ 1.18,20.54},{28.90,69.59},{70.44,106.16},
  {16.27,34.53},{25.14,54.61},{26.25,46.75},{ 9.09,38.19},
  {46.65,69.63},{25.83,42.75},{86.86,137.20},{37.34,80.87},
  {76.91,109.10},{65.34,99.86},{54.88,74.35},{18.16,44.11},
  {51.86,77.14},{39.26,80.22},{ 9.96,23.45},{29.17,53.30},
  {47.53,69.06},{54.09,83.78},{99.01,106.97},{75.74,101.47},
  {91.20,130.12},{13.45,39.52},{45.13,73.46},{34.59,66.91},
  {85.52,108.74},{74.56,83.25},{ 2.84,21.61},{39.19,79.98},
  {99.60,136.33},{64.64,93.93},{81.40,112.90},{80.99,111.74},
  {27.12,60.72},{88.86,129.99},{72.75,107.24},{ 8.23,32.74},
  {26.54,72.28},{40.38,71.89},{25.78,55.94},{29.60,44.89},
  {96.50,126.32},{73.51,86.15},{55.44,71.67},{88.05,120.43},
  {98.23,124.87},{83.14,120.90},{12.94,40.30},{ 3.11,23.56},
  { 5.75,26.47},{ 3.61,14.32},{43.88,57.83},{67.04,99.97},
  {37.45,75.91},{ 9.11,29.62},{60.23,94.20},{71.27,121.40},
  {13.52,28.40},{81.99,126.95},{77.24,106.70},{76.76,120.98},
  {91.78,110.19},{57.18,76.57},{ 2.21,24.84},{44.33,74.56},
  {72.59,94.18},{45.75,61.53},{56.32,81.85},{41.52,65.65},
  {52.87,93.33},{38.56,54.99},{99.44,131.48},{15.62,50.77},
  { 6.17,47.76},{70.92,105.91},{55.79,80.31},{38.47,49.54},
  {29.95,54.48},{70.60,92.43},{30.62,65.87},{22.35,54.38},
  {76.54,100.85},{99.82,136.65},{62.91,102.27},{45.10,59.86},
  {56.19,92.69},{88.97,134.24},{30.38,59.80},{42.77,65.73},
  {59.61,81.77},{ 4.39,27.50},{10.08,14.46},{38.15,44.72},
  {73.02,106.18},{15.05,29.23},{57.12,88.48},{60.38,89.57},
  {47.78,83.80},{77.52,119.08},{74.17,107.35},{ 7.18,41.70},
  {89.65,135.86},{65.54,89.68},{41.46,66.37},{ 6.49,37.83},
  {47.11,77.42},{93.16,145.25},{29.22,59.79},{31.49,74.48},
  {49.95,81.42},{80.68,116.42},{42.77,71.65},{79.81,98.09},
  {11.49,36.53},{69.71,92.14},{98.61,137.83},{ 2.06,12.89},
  {19.59,52.47},{39.88,73.17},{36.54,59.25},{97.33,117.23},
  {33.73,71.77},{13.73,42.62},{30.33,80.15},{38.74,54.58},
  {13.51,22.00},{35.18,71.99},{76.01,114.80},{23.70,38.91},
  { 1.05,36.68},{56.02,91.15},{87.23,107.00},{89.94,119.06},
  {61.07,82.29},{57.11,77.86},{51.87,76.38},{26.32,42.12},
  {24.85,48.18},{16.42,45.70},{ 3.38,34.14},{ 2.15,29.78},
  {33.70,57.28},{ 5.49,15.96},{ 5.93,27.03},{35.60,61.48},
  {67.87,92.28},{73.38,112.27},{ 5.19,22.07},{14.63,49.33},
  {73.40,108.49},{96.35,136.61},{89.90,118.44},{75.21,105.21},
  {71.51,125.63},{76.28,86.34},{73.08,94.95},{37.44,67.60},
  {67.20,102.08},{40.97,69.34},{91.50,132.04},{ 1.45,23.90},
  { 3.77,35.09},{39.31,52.32},{46.32,90.70},{30.69,45.53},
  {42.62,80.56},{72.20,108.15},{14.53,42.16},{84.98,106.08},
  {70.98,117.10},{15.22,36.41},{56.72,94.78},{98.54,132.26},
  {91.57,126.73},{63.97,99.65},{83.61,113.56},{38.61,53.06},
  {42.91,80.55},{96.28,141.26},{53.92,77.85},{92.10,126.52},
  {98.60,113.91},{90.29,117.81},{31.26,56.93},{70.75,101.33},
  {51.87,79.32},{50.86,80.59},{56.39,75.72},{71.63,97.31},
  {42.90,69.19},{40.23,67.54},{39.88,66.03},{35.67,57.92},
  {86.43,124.36},{74.87,104.27},{44.42,93.21},{84.58,119.83},
  {90.52,115.12},{43.61,71.83},{ 5.44,27.81},{46.09,68.62}};
