#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <conio.h>

void Threshold(unsigned char *, FILE *);
void ResizeImg(unsigned char *, FILE *);

int main(void)
{
	HDC hdc = GetWindowDC(GetForegroundWindow());

	FILE *fp = fopen("LENA256.raw", "rb");
	if (fp == NULL) {
		printf("lena.raw 파일을 열 수 없습니다.");
		exit(1);
	}
	
	unsigned char *imgp1 = (unsigned char*)malloc(256 * 256); //65536
	unsigned char *imgp2 = (unsigned char *)malloc(256 * 256);
	unsigned char *imgp3 = (unsigned char *)malloc(128 * 128);

	
	fread(imgp1, 1, 256 * 256, fp);
	
	fclose(fp);

	int r, c;
	for (r = 0; r < 256 ; r++) {
		for (c = 0; c < 256; c++) {
				int red = imgp1[r * 256 + c];
				int green = imgp1[r * 256 + c];
				int blue = imgp1[r * 256 + c];
				SetPixel(hdc, c, r, RGB(red, green, blue));
			}	
		}
	
//	Threshold(imgp2, imgp1);
	ResizeImg(imgp3, imgp1);
	
	getchar();
	return 0;
}

void Threshold(unsigned char *imgp, FILE *fp){
	
	HDC hdc = GetWindowDC(GetForegroundWindow());
	
	int r,c;
	int sum;
	FILE *fpT;
	
	fpT =  fopen("LENA256_BW.raw", "w+b");
	fp = fopen("LENA256.raw", "rb");
	
	if (fpT == NULL) {
		printf("lena_bw.raw 파일을 열 수 없습니다.");
		exit(1);
	}
	
	fread(imgp, 1, 256 * 256, fp);
	
	for(r = 0; r<256; r++){
		for(c = 0; c<256; c++){
			sum += imgp[r * 256 + c];
		}
	}
	
	int T = sum / (256 * 256);
	
	for(r = 0; r<256; r++){
		for(c = 0; c<256; c++){
			if(imgp[r * 256 + c] > T){
				imgp[r * 256 + c] = 255;
			} else if(imgp[r * 256 + c] < T){
				imgp[r * 256 + c] = 0;
			}
		}
	}
	
	fwrite(imgp, 1, 256 * 256, fpT);
	fread(imgp, 1, 256 * 256, fpT);
	
	printf("파일저장 성공\n");
	fclose(fpT);
	
	
	for (r = 0; r < 256 ; r++) {
		for (c = 0; c < 256; c++) {
			int red = imgp[r * 256 + c];
			int green = imgp[r * 256 + c];
			int blue = imgp[r * 256 + c];
			SetPixel(hdc, c, r, RGB(red, green, blue));
		}
	}
}

void ResizeImg(unsigned char *imgp, FILE *fp){
	
	HDC hdc = GetWindowDC(GetForegroundWindow());
	
	unsigned char *tmp = (unsigned char *)malloc(256 * 256);
	
	fp = fopen("LENA256.raw", "rb");
	FILE *fpR =  fopen("LENA128.raw", "w+b");
	
	if (fpR == NULL) {
		printf("lena.raw 파일을 열 수 없습니다.");
		exit(1);
	}
	
	fread(tmp, 1, 256 * 256, fp);
	
	int r,c;
	int re;
	for(r=0; r<256; r++){
		for(c=0; c<256; c++){
					int re = (r * 256 + c) * 0.5;
					imgp[re] = tmp[r * 256 + c];
		}
	}
	fwrite(imgp, 1, 128 * 128, fpR);
	fclose(fpR);
	
	for (r = 0; r < 256; r++) {
		for (c = 0; c < 128; c++) {
			int red = imgp[r * 128 + c];
			int green = imgp[r * 128 + c];
			int blue = imgp[r * 128 + c];
			SetPixel(hdc, c, r/2, RGB(red, green, blue));
		}
	}
}
