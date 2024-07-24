/*
�̵���Ű��
dx, dy�� �Է� �ް� �̵���Ű��
�¿� ��Ī ���� ��Ī
��ȭ ȸ�� Ȯ��
������׷� ȭ���� ó�� ��� �߰�
ȭ�� ���� ó�� ��� �߰�.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h> // GUI ��� ����
#include <math.h>

///////////////////            
// ���� ���� �����
///////////////////
HWND  hwnd; //  ���� ȭ��(�ܺ�, ������)
HDC hdc; // ���� ȭ��(����, ����)


int oriH, oriW, tarH, tarW;
unsigned char** oriImage = NULL;
unsigned char** tarImage = NULL;
unsigned char** circle = NULL;

char filename[200];  // ���ϸ�

///////////////////
// �Լ� �����
///////////////////
// ���� �Լ���
void loadImage();
void saveImage();
void displayImage();
void printMenu();
void mallocOriImage();
void mallocTarImage();
void freeOriImage();
void freeTarImage();
// ����ó�� �Լ���
void equalImage();
void addImage();
void reverseImage();
void zoomOut();
void zoomIn();
void zoomIn2();
void rotate();
void rotate2();
void rotate3();
void movement();
void histoStretch();
void endIn();
void histoEqual();
void symmetry();
void verticalSymmetry();
void emboss();
void blurr();
void gaussian();
void shaping();
void edge();
void edge_Homogeneity();
void edge_char();
void Laplacian();
void draw_circle(int oriH, int oriW, int r);
void free_draw_circle();
void orImage();
void andImage();
void xorImage();
void notImage();
void posterizingImage();
void parabolicImage();
void binarizationImage();
void binarizationHalf();
void binarizationAverage();
int compare(const void* a, const void*);
void binarizationCenter();
void zoomIn3();
void gammaImage();



void printMenu() {
	puts("\n GrayScale Image Processing (RC 1)");

	puts("\n [�⺻ ���]\t\t[ȭ�� �� ó��]");
	puts("\n 1. ����\t\tK. ���Ͽ���");
	puts("\n 2. ����\t\tL. ���/��Ӱ�");
	puts("\n esc. ����\t\tM. ����");
	puts("\n [�������� ó��]\tN. orImage()");
	puts("\n 3. ��/�� ��Ī\t\tO. andImage()");
	puts("\n 4. ��/�� ��Ī\t\tP. xorImage()");
	puts("\n 5. ���\t\tQ. notImage()");
	puts("\n 6. Ȯ��(������)\tR. posterizingImage() / �����Ͷ���¡");
	puts("\n 7. Ȯ��(�����)\tS. parabolicImage()");
	puts("\n 8. ȸ��\t\tT. binarizationImage() / ����ȭ");
	puts("\n 9. ȸ��(����)\t\tU. ���� ����");
	puts("\n A. �̵�\t\tV. histoStretch");
	puts("\n [ȭ�� ���� ó��]\tW. and - in");
	puts("\n B. emboss / ������ ȿ��\tX. histoEqual");
	puts("\n C. blurr / ����");
	puts("\n D. gaussian / ����þ� ������ ���͸� ó��");
	puts("\n E. shaping / ������");
	puts("\n F. edge / ��輱 ó��");
	puts("\n G. edge_Homogeneity()");
	puts("\n H. edge_char()");
	puts("\n I. Laplacian()");
	puts("\n J. �缱�� ������()");
}



///////////////////
// ���� �ڵ��
///////////////////
void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);  // ����10��.  ����11(hwnd--> NULL)
	system("mode con:cols=200 lines=200");
	char key = 0;
	while (key != 27) { // 27 is the ASCII code for the ESC key
		printMenu();
		key = _getch();
		system("cls");
		switch (key) {
		case '1': loadImage(); break;
		case '2': saveImage(); break;
		case '3': symmetry(); break;
		case '4': verticalSymmetry(); break;
		case '5': zoomOut(); break;
		case '6': zoomIn(); break;
		case '7': zoomIn2(); break;
		case '8': rotate(); break;
		case '9': rotate2(); break;
		case 'A': case 'a': movement(); break;
		case 'B': case 'b': emboss(); break;
		case 'C': case 'c': blurr(); break;
		case 'D': case 'd': gaussian(); break;
		case 'E': case 'e': shaping(); break;
		case 'F': case 'f': edge(); break;
		case 'G': case 'g': edge_Homogeneity(); break;
		case 'H': case 'h': edge_char(); break;
		case 'I': case 'i': Laplacian(); break;
		case 'J': case 'j': zoomIn3(); break;
		case 'K': case 'k': equalImage(); break;
		case 'L': case 'l': Laplacian(); break;
		case 'M': case 'm': reverseImage(); break;
		case 'N': case 'n': orImage(); break;
		case 'O': case 'o': andImage(); break;
		case 'P': case 'p': xorImage(); break;
		case 'Q': case 'q': notImage(); break;
		case 'R': case 'r': posterizingImage(); break;
		case 'S': case 's': parabolicImage(); break;
		case 'T': case 't': binarizationImage(); break;
		case 'U': case 'u': gammaImage(); break;
		case 'V': case 'v': histoStretch(); break;
		case 'W': case 'w': endIn(); break;
		case 'X': case 'x': histoEqual(); break;
		case 27: freeOriImage(); freeTarImage(); break; // 27 is the ESC key
		}
	}
	puts("'ESC �Է°��� ���α׷��� �����մϴ�.'");
}

////////////////
/// �Լ� ���Ǻ�
////////////////
void mallocOriImage() {
	oriImage = (unsigned char**)malloc(sizeof(unsigned char*) * oriH);
	for (int i = 0; i < oriH; i++)
		oriImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * oriW);
}
void mallocTarImage() {
	tarImage = (unsigned char**)malloc(sizeof(unsigned char*) * tarH);
	for (int i = 0; i < tarH; i++)
		tarImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * tarW);
}
void freeOriImage() {
	if (oriImage == NULL)
		return;
	for (int i = 0; i < oriH; i++)
		free(oriImage[i]);
	free(oriImage);
	oriImage = NULL;
}
void freeTarImage() {
	if (tarImage == NULL)
		return;
	for (int i = 0; i < tarH; i++)
		free(tarImage[i]);
	free(tarImage);
	tarImage = NULL;
}
double** malloc_double(int h, int w) {
	double** memory;
	memory = (double**)malloc(sizeof(double*) * h);
	for (int i = 0; i < h; i++)
		memory[i] = (double*)malloc(sizeof(double) * w);
	return memory;
}
void free_double(double** memory, int h) {
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
	memory = NULL;
}
void loadImage() {
	char fullname[200] = "C:/Users/User/Desktop/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���ϸ�-->"); scanf("%s", tmpName);  // cat01, dog05, etc11
	strcat(fullname, tmpName);
	strcat(fullname, ".raw");
	strcpy(filename, fullname);

	//(�߿�!) ���������� ũ�⸦ �ľ�!
	FILE* rfp;
	rfp = fopen(filename, "rb");
	if (!rfp) {
		printf("���ϸ� Ʋ����~ \n");
		return;
	}
	fseek(rfp, 0L, SEEK_END); // ������ ������ �̵�
	long long fsize = ftell(rfp);
	fclose(rfp);
	// ���� ���� ũ��
	oriH = oriW = sqrt(fsize);
	// 2���� �޸� �Ҵ�
	freeOriImage();
	mallocOriImage();

	// ���� --> �޸�
	rfp = fopen(filename, "rb");
	for (int i = 0; i < oriH; i++)
		fread(oriImage[i], sizeof(unsigned char), oriW, rfp);
	fclose(rfp);
	equalImage();

}
void saveImage() {
	char fullname[200] = "C:/Users/User/Desktop/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���� ���ϸ�-->"); scanf("%s", tmpName);  // out01, out02 ....
	strcat(fullname, tmpName);
	strcat(fullname, "_512.raw");
	strcpy(filename, fullname);

	FILE* wfp;
	wfp = fopen(filename, "wb");
	// �޸� >> ����
	for (int i = 0; i < tarH; i++) {
		fwrite(tarImage[i], sizeof(unsigned char), tarW, wfp);
	}
	fclose(wfp);
	printf("%s �� �����", filename);
}
void displayImage() {
	system("CLS");
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			int px = tarImage[i][k];
			SetPixel(hdc, k + 700, i + 100, RGB(px, px, px));
		}
	}
}

/// <summary>
/// ���� ó��
/// </summary>
void equalImage() {
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k];
		}
	}
	///////////////////////////////
	displayImage();
}
void addImage() {
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	int value;
	printf("���� ��(-255~+255) :");  scanf("%d", &value);
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			int pixel = oriImage[i][k] + value;
			if (pixel > 255)
				pixel = 255;
			if (pixel < 0)
				pixel = 0;
			tarImage[i][k] = (unsigned char)pixel;
		}
	}
	///////////////////////////////
	displayImage();
}
void reverseImage() {  // ���� : 0>255, 1>254, 2>253..... 254>1, 255>0
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = 255 - oriImage[i][k];
		}
	}
	///////////////////////////////
	displayImage();
}
void zoomOut() {
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	int scale;
	printf("��� ����:"); scanf("%d", &scale);
	tarH = (int)(oriH / scale);
	tarW = (int)(oriW / scale);
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i / scale][k / scale] = oriImage[i][k];
		}
	}
	///////////////////////////////
	displayImage();
}
void zoomIn() {
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	int scale;
	printf("Ȯ�� ����:"); scanf("%d", &scale);
	tarH = (int)(oriH * scale);
	tarW = (int)(oriW * scale);
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�	
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i * scale][k * scale] = oriImage[i][k];
		}
	}
	///////////////////////////////
	displayImage();
}
void zoomIn2() {
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	int scale;
	printf("Ȯ�� ����:"); scanf("%d", &scale);
	tarH = (int)(oriH * scale);
	tarW = (int)(oriW * scale);
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�	
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tarImage[i][k] = oriImage[i / scale][k / scale];
		}
	}
	///////////////////////////////
	displayImage();
}
void rotate() {

	int angle;
	int tarX, tarY, oriX, oriY;
	double radian;

	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// ȸ�� ���� �Է� �ޱ�
	printf("ȸ�� ����: ");
	scanf("%d", &angle);
	// target x = cos * orix - sin * oriy
	// target y = sin * orix + cos * oriy
	radian = angle * 3.141592 / 180.0;

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			oriX = i;
			oriY = k;
			tarX = cos(radian) * oriX - sin(radian) * oriY;
			tarY = sin(radian) * oriX + cos(radian) * oriY;

			if (tarX >= 0 && tarX < tarH && 0 <= tarY && tarY < tarW)
				tarImage[tarX][tarY] = oriImage[oriX][oriY];
		}
	}
	///////////////////////////////
	displayImage();
}
void rotate2() {
	freeTarImage();
	int angle;
	printf("ȸ�� ����: ");
	scanf("%d", &angle);

	// ������ �������� ��ȯ
	double radian = angle * 3.141592 / 180.0;

	// ȸ�� ���� �߽���
	int Cx = oriW / 2;
	int Cy = oriH / 2;

	// ȸ���� �̹����� ũ�� ���
	tarW = abs(oriW * cos(radian)) + abs(oriH * sin(radian));
	tarH = abs(oriW * sin(radian)) + abs(oriH * cos(radian));

	// ��� ���� �޸� �Ҵ�
	mallocTarImage();

	int tarX, tarY, oriX, oriY;
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			// ȸ�� �� ��ǥ
			tarX = k;
			tarY = i;

			// �ӽ� input ������ ����
			// ��ȸ�� ��ȯ
			oriX = cos(radian) * (tarX - tarW / 2) + sin(radian) * (tarY - tarH / 2) + Cx;
			oriY = -sin(radian) * (tarX - tarW / 2) + cos(radian) * (tarY - tarH / 2) + Cy;

			// ���� �̹��� ���� ���� �ִ��� Ȯ��
			if ((0 <= oriX && oriX < oriW) && (0 <= oriY && oriY < oriH)) {
				tarImage[tarY][tarX] = oriImage[oriY][oriX];
			}
			else {
				tarImage[tarY][tarX] = 255; // ������ ����� ��� ���������� ä��
			}
		}
	}

	// �̹��� ��� �Լ�
	displayImage();
}
void rotate3() {
	freeTarImage();
	int angle;
	int tarX, tarY, oriX, oriY;
	int Cx, Cy;
	double radian;

	// ȸ�� ���� �Է� �ޱ�
	printf("ȸ�� ����: ");
	scanf("%d", &angle);

	// ���� �̹��� �߽� ��ǥ
	/*Cx = oriW / 2;
	Cy = oriH / 2;*/
	radian = angle * 3.141592 / 180.0; // ������ �������� ��ȯ

	// ��� ������ ũ�� ����
	/*tarW = oriW;
	tarH = oriH;*/
	tarW = (int)(oriH * (cos(90 - radian)) + oriW * (cos(radian)));
	tarH = (int)(oriH * (cos(radian)) + oriW * (cos(90 - radian)));

	Cx = tarW / 2;
	Cy = tarH / 2;

	// ��� ���� �޸� �Ҵ�
	mallocTarImage();

	// ȸ�� ��ȯ
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			// ��� �̹��������� ��ǥ
			tarX = k;
			tarY = i;

			// ���� �̹��������� ��ǥ ���
			oriX = (int)(cos(radian) * (tarX - Cx) + sin(radian) * (tarY - Cy) + Cx);
			oriY = (int)(-sin(radian) * (tarX - Cx) + cos(radian) * (tarY - Cy) + Cy);

			// ��ǥ�� ���� �̹��� ���� ���� �ִ��� Ȯ��
			if (oriX >= 0 && oriX < oriW && oriY >= 0 && oriY < oriH) {
				tarImage[tarY][tarX] = oriImage[oriY][oriX];
			}
			else {
				tarImage[tarY][tarX] = 255; // ������ ��� ��� �� ������ ����
			}
		}
	}

	displayImage();
}
void movement() {
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	int dx, dy;
	int mx, my;
	printf("�̵� x : ");  scanf("%d", &dx);
	printf("�̵� y : ");  scanf("%d", &dy);


	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			mx = dx + k;
			my = dy + i;
			if ((mx >= 0 && mx < oriH) && (my >= 0 && my < oriW)) {
				tarImage[my][mx] = oriImage[i][k];
			}

		}
	}
	///////////////////////////////
	displayImage();
}
void histoStretch() {
	/* ����*/
	int low, high;


	/* init */
	// ���� : new = (old - low ) / (high - low) * 255.0
	low = high = oriImage[0][0];
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			if (oriImage[i][k] < low) {
				low = oriImage[i][k];
			}
			if (oriImage[i][k] > high) {
				high = oriImage[i][k];
			}
		}
	}

	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����
	tarH = oriH;
	tarW = oriW;
	freeTarImage();
	mallocTarImage();

	/* algo*/
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = (double)(oriImage[i][k] - low) / (high - low) * 255.0;
		}
	}

	displayImage();
}
void endIn() {
	/* ����*/
	int low, high;


	/* init */
	// ���� : new = (old - low ) / (high - low) * 255.0
	low = high = oriImage[0][0];
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			if (oriImage[i][k] < low) {
				low = oriImage[i][k];
			}
			if (oriImage[i][k] > high) {
				high = oriImage[i][k];
			}
		}
	}

	// and - in �˰��� ����
	low = low + 50;
	high = high + 50;

	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����
	tarH = oriH;
	tarW = oriW;
	freeTarImage();
	mallocTarImage();

	/* algo*/
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			double newVal = (double)(oriImage[i][k] - low) /
				(high - low) * 255.0;
			if (newVal < 0.0)
				newVal = 0;
			if (newVal > 255.0)
				newVal = 255;

			tarImage[i][k] = newVal;
		}
	}

	displayImage();
}
void histoEqual() {
	/* ���� */
	int brightness[256] = { 0 };
	double tarBrightness[256] = { 0.0 };
	int brightnessSum[256] = { 0 };

	/* init */
	tarH = oriH;
	tarW = oriW;
	freeTarImage();
	mallocTarImage();

	/* logic */
	// 1�ܰ�
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			brightness[oriImage[i][k]]++;
		}
	}

	// 2�ܰ�
	brightnessSum[0] = brightness[0];
	for (int i = 1; i < 256; i++) {
		brightnessSum[i] = brightnessSum[i - 1] + brightness[i];
	}

	// 3�ܰ�
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < 256; i++) {
		tarBrightness[i] = brightnessSum[i] * (1.0 / (oriH * oriW)) * 255.0;
	}

	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = (unsigned char)tarBrightness[oriImage[i][k]];
		}
	}

	displayImage();
}
void symmetry() {

	int angle;
	int tarX, tarY, oriX, oriY;

	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// ȸ�� ���� �Է� �ޱ�
	/*printf("ȸ�� ����: ");
	scanf("%d", &angle);*/
	// oriX = cos * (tarX - Cx) + sin * (tarY - Cy) + Cx
	// oriY = -sin * (tarX - Cx) + cos * (tarY - Cy) + Cy
	// target y = sin * orix + cos * oriy
	//Cx = oriW / 2;
	//radian = 180 * 3.141592 / 180.0;

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tarY = i;
			tarX = k;
			tarImage[tarY][tarX] = oriImage[tarY][tarW - tarX];
		}
	}
	///////////////////////////////
	displayImage();
}
void verticalSymmetry() {
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;

	// ��� ���� �޸� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			int mirroredY = oriH - 1 - i; // Flip vertically

			if (mirroredY >= 0 && mirroredY < tarH) {
				tarImage[mirroredY][k] = oriImage[i][k];
			}
		}
	}
	///////////////////////////////
	displayImage();
}
void emboss() {
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	// const int MSIZE = 3; // ����ũ ũ��
	// �߿�! ����ũ �غ�
#define MSIZE 3   
	double mask[MSIZE][MSIZE] = {
		{  -1.0, 0.0,  0.0 },
		{  0.0, 0.0,  0.0 },
		{  0.0, 0.0, 1.0 } };
	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = malloc_double(oriH + 2, oriW + 2);
	tmpTarImage = malloc_double(tarH, tarW);
	// �ӽ� ��ʺ� �̹����� 127ä��� ��հ��� �� ������
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = 127.0;
		}
	}
	// ���� --> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}
	// ȸ�� ���� --> ����ũ�� �ܾ�鼭 ����
	double S = 0; // ������ ���� ����ũ ���� �հ�
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			S = 0.0; // ���� �ʱ�ȭ
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += mask[m][n] * tmpOriImage[i + m][k + n];
			tmpTarImage[i][k] = S;
		}
	}
	// Post Processing(�� ó��). ����ũ �հ谡 0�̸� 127������ ����
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tmpTarImage[i][k] += 127.0;
		}
	}
	// �ӽ� Ÿ�� --> Ÿ������
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];

			if (v < 0.0) {
				v = 0.0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}

	free_double(tmpOriImage, oriH + 2);
	free_double(tmpTarImage, tarH);
	///////////////////////////////
	displayImage();
}
void blurr() {
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	// const int MSIZE = 3; // ����ũ ũ��
	// �߿�! ����ũ �غ�
#define MSIZE 3   
	double mask[MSIZE][MSIZE] = {
		{  1.0 / 9, 1.0 / 9,  1.0 / 9 },
		{  1.0 / 9, 1.0 / 9,  1.0 / 9 },
		{  1.0 / 9, 1.0 / 9,  1.0 / 9 } };
	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = malloc_double(oriH + 2, oriW + 2);
	tmpTarImage = malloc_double(tarH, tarW);
	// �ӽ� ��ʺ� �̹����� 127ä��� ��հ��� �� ������
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = 127.0;
		}
	}
	// ���� --> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}
	// ȸ�� ���� --> ����ũ�� �ܾ�鼭 ����
	double S = 0; // ������ ���� ����ũ ������ �հ�

	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S += mask[m][n] * tmpOriImage[i + m][k + n];
				}
			}
			tmpTarImage[i][k] = S;
		}
	}
	// Post Processing(�� ó��). ����ũ �հ谡 0�̸� 127������ ����
	/*for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tmpTarImage[i][k] += 127.0;
		}
	}*/
	// �ӽ� Ÿ�� --> Ÿ������
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];

			if (v < 0.0) {
				v = 0.0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}

	free_double(tmpOriImage, oriH + 2);
	free_double(tmpTarImage, tarH);
	///////////////////////////////
	displayImage();
}
void gaussian() {
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	// const int MSIZE = 3; // ����ũ ũ��
	// �߿�! ����ũ �غ�
#define MSIZE 3   
	double mask[MSIZE][MSIZE] = {
		{  1.0 / 16.0, 1.0 / 8.0,  1.0 / 16.0 },
		{  1.0 / 8.0, 1.0 / 4.0,  1.0 / 8.0 },
		{  1.0 / 16.0, 1.0 / 8.0,  1.0 / 16.0 } };


	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = malloc_double(oriH + 2, oriW + 2);
	tmpTarImage = malloc_double(tarH, tarW);
	// �ӽ� ��ʺ� �̹����� 127ä��� ��հ��� �� ������
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = 127.0;
		}
	}
	// ���� --> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}
	// ȸ�� ���� --> ����ũ�� �ܾ�鼭 ����
	double S = 0; // ������ ���� ����ũ ������ �հ�

	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S += mask[m][n] * tmpOriImage[i + m][k + n];
				}
			}
			tmpTarImage[i][k] = S;
		}
	}
	// Post Processing(�� ó��). ����ũ �հ谡 0�̸� 127������ ����
	/*for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tmpTarImage[i][k] += 127.0;
		}
	}*/
	// �ӽ� Ÿ�� --> Ÿ������
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];

			if (v < 0.0) {
				v = 0.0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}

	free_double(tmpOriImage, oriH + 2);
	free_double(tmpTarImage, tarH);
	///////////////////////////////
	displayImage();
}
void shaping() {
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	// const int MSIZE = 3; // ����ũ ũ��
	// �߿�! ����ũ �غ�
#define MSIZE 3   
	//double mask[MSIZE][MSIZE] = {
	//	{  -1.0, -1.0,  -1.0 },
	//	{  -1.0, 9.0,  -1.0 },
	//	{  -1.0, -1.0, -1.0 } };
	double mask[MSIZE][MSIZE] = {
		{  0.0, -1.0,  0.0 },
		{  -1.0, 5.0,  -1.0 },
		{  0.0, -1.0, 0.0 } };


	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = malloc_double(oriH + 2, oriW + 2);
	tmpTarImage = malloc_double(tarH, tarW);
	// �ӽ� ��ʺ� �̹����� 127ä��� ��հ��� �� ������
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = 127.0;
		}
	}
	// ���� --> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}
	// ȸ�� ���� --> ����ũ�� �ܾ�鼭 ����
	double S = 0; // ������ ���� ����ũ ������ �հ�

	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S += mask[m][n] * tmpOriImage[i + m][k + n];
				}
			}
			tmpTarImage[i][k] = S;
		}
	}
	// Post Processing(�� ó��). ����ũ �հ谡 0�̸� 127������ ����
	/*for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tmpTarImage[i][k] += 127.0;
		}
	}*/
	// �ӽ� Ÿ�� --> Ÿ������
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];

			if (v < 0.0) {
				v = 0.0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}

	free_double(tmpOriImage, oriH + 2);
	free_double(tmpTarImage, tarH);
	///////////////////////////////
	displayImage();
}
void edge() {
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	// const int MSIZE = 3; // ����ũ ũ��
	// �߿�! ����ũ �غ�
#define MSIZE 3   
	double mask[MSIZE][MSIZE] = {
		{  0.0, 0.0,  0.0 },
		{ -1.0, 1.0,  0.0 },
		{  0.0, 0.0,  0.0 } };
	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = malloc_double(oriH + 2, oriW + 2);
	tmpTarImage = malloc_double(tarH, tarW);
	// �ӽ� ��ʺ� �̹����� 127ä��� ��հ��� �� ������
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = 127.0;
		}
	}
	// ���� --> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}
	// ȸ�� ���� --> ����ũ�� �ܾ�鼭 ����
	double S = 0; // ������ ���� ����ũ ������ �հ�

	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S += mask[m][n] * tmpOriImage[i + m][k + n];
				}
			}
			tmpTarImage[i][k] = S + 50;
		}
	}
	// Post Processing(�� ó��). ����ũ �հ谡 0�̸� 127������ ����
	/*for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tmpTarImage[i][k] += 127.0;
		}
	}*/
	// �ӽ� Ÿ�� --> Ÿ������
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];

			if (v < 0.0) {
				v = 0.0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}

	free_double(tmpOriImage, oriH + 2);
	free_double(tmpTarImage, tarH);
	///////////////////////////////
	displayImage();
}
void edge_Homogeneity() {
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	// const int MSIZE = 3; // ����ũ ũ��
	// �߿�! ����ũ �غ�
#define MSIZE 3 
	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = malloc_double(oriH + 2, oriW + 2);
	tmpTarImage = malloc_double(tarH, tarW);
	// ���� �̹��� ��� ȭ��
	double average = 0.0;
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			average = average + oriImage[i][k];
		}
	}
	average = average / (oriH * oriW);

	// �ӽ� ��ʺ� �̹����� 127ä��� ��հ��� �� ������
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = average;
		}
	}
	// ���� --> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}


	// ȸ�� ���� --> ����ũ�� �ܾ�鼭 ����
	double S = 0.0; // ������ ���� ����ũ ������ �հ�
	double tmp = 0.0;
	// �ݺ����� ������ tarH, tarW /  �迭[-1][-1] ���� ������ ����
	for (int i = 1; i < tarH - 1; i++) {
		for (int k = 1; k < tarW - 1; k++) {
			S = 0.0;
			for (int m = i - 1; m <= i + 1; m++) {
				for (int n = k - 1; n <= k + 1; n++) {
					tmp = abs(tmpOriImage[i][k] - tmpOriImage[m][n]);
					if (S < tmp) {
						S = tmp;
					}
				}
			}
			tmpTarImage[i][k] = S + 100;
		}
	}

	// Post Processing(�� ó��). ����ũ �հ谡 0�̸� 127������ ����
	/*for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tmpTarImage[i][k] += 127.0;
		}
	}*/
	// �ӽ� Ÿ�� --> Ÿ������
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];

			if (v < 0.0) {
				v = 0.0;
			}
			if (v < 110.0) {
				v = 0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			if (v > 200.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}

	free_double(tmpOriImage, oriH + 2);
	free_double(tmpTarImage, tarH);
	///////////////////////////////
	displayImage();
}
void edge_char() {
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	// const int MSIZE = 3; // ����ũ ũ��
	// �߿�! ����ũ �غ�
#define MSIZE 3 
	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = malloc_double(oriH + 2, oriW + 2);
	tmpTarImage = malloc_double(tarH, tarW);
	// ���� �̹��� ��� ȭ��
	double average = 0.0;
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			average = average + oriImage[i][k];
		}
	}
	average = average / (oriH * oriW);

	// �ӽ� ��ʺ� �̹����� 127ä��� ��հ��� �� ������
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = average;
		}
	}
	// ���� --> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}


	// ȸ�� ���� --> ����ũ�� �ܾ�鼭 ����
	double S = 0.0; // ������ ���� ����ũ ������ �հ�
	double tmp = 0.0;
	// �ݺ����� ������ tarH, tarW /  �迭[-1][-1] ���� ������ ����
	for (int i = 1; i < tarH - 1; i++) {
		for (int k = 1; k < tarW - 1; k++) {
			double maxDiff = 0.0;
			double centerPixel = tmpOriImage[i][k];
			for (int m = i - 1; m <= i + 1; m++) {
				for (int n = k - 1; n <= k + 1; n++) {
					if (m == i && n == k) continue; // �߾� �ȼ��� ����
					double diff = abs(centerPixel - tmpOriImage[m][n]);
					if (diff > maxDiff) {
						maxDiff = diff;
					}
				}
			}
			tmpTarImage[i][k] = maxDiff + 100;
		}
	}

	// Post Processing(�� ó��). ����ũ �հ谡 0�̸� 127������ ����
	/*for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tmpTarImage[i][k] += 127.0;
		}
	}*/
	// �ӽ� Ÿ�� --> Ÿ������
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];

			if (v < 0.0) {
				v = 0.0;
			}
			if (v < 110.0) {
				v = 0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			if (v > 200.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}

	free_double(tmpOriImage, oriH + 2);
	free_double(tmpTarImage, tarH);
	///////////////////////////////
	displayImage();
}
void Laplacian() {
	freeTarImage();
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	// const int MSIZE = 3; // ����ũ ũ��
	// �߿�! ����ũ �غ�
#define MSIZE 3   
	double mask[MSIZE][MSIZE] = {
		{  -1.0,-1.0,  -1.0 },
		{  -1.0, 8.0,  -1.0 },
		{  -1.0, -1.0, -1.0 } };
	// �ӽ� ����� �޸� �غ�
	double** tmpOriImage, ** tmpTarImage;
	tmpOriImage = malloc_double(oriH + 2, oriW + 2);
	tmpTarImage = malloc_double(tarH, tarW);
	// ���� �̹��� ��� ȭ��
	double average = 0.0;
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			average = average + oriImage[i][k];
		}
	}
	average = average / (oriH * oriW);

	// �ӽ� ��ʺ� �̹����� 127ä��� ��հ��� �� ������
	for (int i = 0; i < oriH + 2; i++) {
		for (int k = 0; k < oriW + 2; k++) {
			tmpOriImage[i][k] = average;
		}
	}
	// ���� --> �ӽ� ����
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmpOriImage[i + 1][k + 1] = oriImage[i][k];
		}
	}
	// ȸ�� ���� --> ����ũ�� �ܾ�鼭 ����
	double S = 0; // ������ ���� ����ũ ���� �հ�
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			S = 0.0; // ���� �ʱ�ȭ
			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += mask[m][n] * tmpOriImage[i + m][k + n];
			tmpTarImage[i][k] = S;
		}
	}
	// Post Processing(�� ó��). ����ũ �հ谡 0�̸� 127������ ����
	/*for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			tmpTarImage[i][k] += 127.0;
		}
	}*/
	// �ӽ� Ÿ�� --> Ÿ������
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			double v = tmpTarImage[i][k];

			if (v < 0.0) {
				v = 0.0;
			}
			if (v > 255.0) {
				v = 255.0;
			}
			tarImage[i][k] = v;
		}
	}

	free_double(tmpOriImage, oriH + 2);
	free_double(tmpTarImage, tarH);
	///////////////////////////////
	displayImage();
}
void draw_circle(int oriH, int oriW, int r) {
	free_draw_circle();
	circle = (unsigned char**)malloc(sizeof(unsigned char*) * oriH);
	for (int i = 0; i < oriH; i++) {
		if (circle != NULL) {
			circle[i] = (unsigned char*)malloc(sizeof(unsigned char) * oriW);
		}

	}


	// �ʱ� �迭 ���� 0���� ����
	for (int i = 0; i < oriH; i++) {
		for (int j = 0; j < oriW; j++) {
			circle[i][j] = 0;
		}
	}

	// �߽� ��ǥ ���
	int centerX = oriH / 2;
	int centerY = oriW / 2;

	// �� �׸���
	for (int x = 0; x < oriH; x++) {
		for (int y = 0; y < oriW; y++) {
			// ���� ������ ����
			int dx = x - centerX;
			int dy = y - centerY;
			if (dx * dx + dy * dy <= r * r) {
				circle[x][y] = 255;
			}
		}
	}
}
void free_draw_circle() {
	if (circle == NULL)
		return;
	for (int i = 0; i < tarH; i++)
		free(circle[i]);
	free(circle);
	circle = NULL;
}
void orImage() {
	/* ���� */

	/* init */
	tarH = oriH;
	tarW = oriW;
	mallocTarImage();		// ��� ���� �޸� �Ҵ�
	draw_circle(tarH, tarW, tarH / 2);

	/* �޼��� */
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k] | circle[i][k];
		}
	}


	displayImage();
	// 2���� �޸� ����
	free_draw_circle();
	freeTarImage();
}
void andImage() {
	/* ���� */

	/* init */
	tarH = oriH;
	tarW = oriW;
	mallocTarImage();		// ��� ���� �޸� �Ҵ�
	draw_circle(tarH, tarW, tarH / 2);

	/* �޼��� */
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k] & circle[i][k];
		}
	}

	displayImage();
	// 2���� �޸� ����
	free_draw_circle();
	freeTarImage();
}
void xorImage() {
	/* ���� */
	int ans;
	/* init */
	tarH = oriH;
	tarW = oriW;
	mallocTarImage();		// ��� ���� �޸� �Ҵ�
	draw_circle(tarH, tarW, tarH / 2);

	/* �޼��� */
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = oriImage[i][k] ^ circle[i][k];
		}
	}


	displayImage();
	// 2���� �޸� ����
	free_draw_circle();
	freeTarImage();
}
void notImage() {
	/* ���� */

	/* init */
	tarH = oriH;
	tarW = oriW;
	mallocTarImage();		// ��� ���� �޸� �Ҵ�

	/* �޼��� */
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = ~oriImage[i][k];
		}
	}

	displayImage();
	// 2���� �޸� ����
	freeTarImage();
}
void posterizingImage() {
	/* ���� */
	int level[8];
	int tmp;
	/* init */
	tarH = oriH;
	tarW = oriW;
	mallocTarImage();		// ��� ���� �޸� �Ҵ�

	for (int i = 0; i < 8; i++) {
		level[i] = i * 32;
	}

	/* �޼��� */
	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmp = oriImage[i][k] / 32;
			tarImage[i][k] = level[tmp];
		}
	}

	displayImage();
	// 2���� �޸� ����
	freeTarImage();
}
void parabolicImage() {
	// (�߿�!) ��� ������ ũ�⸦ ���� ---> �˰��� ����.
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	// tarImage[tarH][tarW] ũ��� �Ҵ�
	freeTarImage();
	mallocTarImage();

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = 255 * pow((oriImage[i][k] / 127) - 1, 2);
		}
	}
	///////////////////////////////
	displayImage();
}
void binarizationImage() {
	int ans;
	tarH = oriH;
	tarW = oriW;
	// ��� ���� �޸� �Ҵ�
	mallocTarImage();

	puts(" 1.128 / 2.��հ� / 3.�߾Ӱ�");
	scanf("%d", &ans);

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tarImage[i][k] = 255 - oriImage[i][k];
		}
	}

	switch (ans)
	{
	case 1: binarizationHalf(); break;
	case 2: binarizationAverage(); break;
	case 3: binarizationCenter(); break;
	default: loadImage(); break;
	}
	///////////////////////////////
	displayImage();
	// 2���� �޸� ����
	freeTarImage();
}
void binarizationHalf() {
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			if (tarImage[i][k] < 128) {
				tarImage[i][k] = 0;
			}
			else {
				tarImage[i][k] = 255;
			}
		}
	}
}
void binarizationAverage() {
	long long average = 0;
	long long sum = 0;
	// ��
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			sum += tarImage[i][k];
		}
	}
	// ���
	average = sum / tarH / tarW;
	return 0;

	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			if (tarImage[i][k] < average) {
				tarImage[i][k] = 0;
			}
			else {
				tarImage[i][k] = 255;
			}
		}
	}
}
int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}
void binarizationCenter() {
	int center = 0;
	unsigned char* arr;		// �ӽ� 1���� �迭 ����
	arr = (unsigned char*)malloc(sizeof(unsigned char) * (tarH * tarW));

	// �߾Ӱ� 
	int pos = 0;
	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			arr[pos] = tarImage[i][k];
		}
	}
	qsort(arr, (tarH * tarW), sizeof(char), compare);
	center = arr[(tarH * tarW) / 2];

	for (int i = 0; i < tarH; i++) {
		for (int k = 0; k < tarW; k++) {
			if (tarImage[i][k] < center) {
				tarImage[i][k] = 0;
			}
			else {
				tarImage[i][k] = 255;
			}
		}
	}
	free(arr);
}
void zoomIn3()
{
	freeTarImage();
	int scale;
	printf("�� �� Ȯ���Ͻðڽ��ϱ�? ");
	scanf("%d", &scale);
	tarH = (int)(oriH * scale);
	tarW = (int)(oriW * scale);
	mallocTarImage();

	for (int i = 0; i < tarH; i++)
	{
		for (int j = 0; j < tarW; j++)
		{
			tarImage[i][j] = oriImage[i / scale][j / scale];
		}
	}
	int e, f, n, x, y;;

	for (int i = 0; i < tarH - scale; i += scale)
	{
		for (int j = 0; j < tarW - scale; j += scale)
		{
			for (int k = 0; k < scale; k++)
			{
				for (int l = 0; l < scale; l++)
				{
					y = i + k;
					x = j + l;
					if ((!(y == i && x == j)) && (!(y == i && x == j + scale)) && (!(y == i + scale && x == j)) && (!(y == i + scale && x == j + scale)))
					{
						e = scale * tarImage[i][j] + l * (tarImage[i][j + scale] - tarImage[i][j]);
						f = scale * tarImage[i + scale][j] + l * (tarImage[i + scale][j + scale] - tarImage[i + scale][j]);
						n = (scale - k) * e + f * k;

						if (n < 0) n = 0;
						if (n > 255) n = 255;

						tarImage[y][x] = n;
					}
				}
			}
		}
	}

	// ���� ������
	/*for (int i = 0; i < tarH - 1; i++)
	{
		for (int j = 0; j < tarW - 1; j++)
		{
			int x = i % scale;
			int y = j % scale;
			int x1 = i / scale;
			int y1 = j / scale;
			int x2 = x1 + 1 < oriH ? x1 + 1 : x1;
			int y2 = y1 + 1 < oriW ? y1 + 1 : y1;

			float value = (oriImage[x1][y1] * (scale - x) * (scale - y) +
				oriImage[x2][y1] * x * (scale - y) +
				oriImage[x1][y2] * (scale - x) * y +
				oriImage[x2][y2] * x * y) / (scale * scale);

			tarImage[i][j] = (int)value;
		}
	}*/
	displayImage();
}
void gammaImage() {
	/* ���� */
	double ans = 0.0;
	double tmp = 0.0;
	/* init */
	tarH = oriH;
	tarW = oriW;
	mallocTarImage();		// ��� ���� �޸� �Ҵ�
	/* �޼��� */
	puts(" ���� ���� input ");
	scanf("%lf", &ans);

	// *** ��¥ ����ó�� �˰��� ****
	for (int i = 0; i < oriH; i++) {
		for (int k = 0; k < oriW; k++) {
			tmp = pow((double)oriImage[i][k], 1.0 / ans);
			if (tmp < 0) {
				tarImage[i][k] = 0;
			}
			else if (tmp > 255) {
				tarImage[i][k] = 255;
			}
			else {
				tarImage[i][k] = (unsigned char)tmp;
			}
		}
	}

	displayImage();
	// 2���� �޸� ����
	freeTarImage();
}