#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

//5 chân tương ứng với 5 tầng ở cổng D
#define row_1 GPIO_Pin_0
#define row_2 GPIO_Pin_1
#define row_3 GPIO_Pin_2
#define row_4 GPIO_Pin_3
#define row_5 GPIO_Pin_4
//15 chân tương ứng với các cột từ 1 -> 15 ở cổng B
#define col_1 GPIO_Pin_0
#define col_2 GPIO_Pin_1
#define col_3 GPIO_Pin_2
#define col_4 GPIO_Pin_3
#define col_5 GPIO_Pin_4
#define col_6 GPIO_Pin_5
#define col_7 GPIO_Pin_6
#define col_8 GPIO_Pin_7
#define col_9 GPIO_Pin_8
#define col_10 GPIO_Pin_9
#define col_11 GPIO_Pin_10
#define col_12 GPIO_Pin_11
#define col_13 GPIO_Pin_12
#define col_14 GPIO_Pin_13
#define col_15 GPIO_Pin_14
//10 chân tướng ứng với các cột từ 16 -> 25 ở cổng C
#define col_16 GPIO_Pin_0
#define col_17 GPIO_Pin_1
#define col_18 GPIO_Pin_2
#define col_19 GPIO_Pin_3
#define col_20 GPIO_Pin_4
#define col_21 GPIO_Pin_5
#define col_22 GPIO_Pin_6
#define col_23 GPIO_Pin_7
#define col_24 GPIO_Pin_8
#define col_25 GPIO_Pin_9

//Sử dụng mảng 1 chiều có 5 phần tử để lưu 5 tầng của khối rubik
int row[5] = { row_1, row_2, row_3, row_4, row_5 };
//Sử dụng mảng 1 chiều có 25 phần tử để lưu 25 cột của khối rubik
int col[25] = { col_1, col_2, col_3, col_4, col_5, col_6, col_7, col_8, col_9,
		col_10, col_11, col_12, col_13, col_14, col_15, col_16, col_17, col_18,
		col_19, col_20, col_21, col_22, col_23, col_24, col_25 };
// Sử dụng mảng 2 chiều để lưu 25 cột của khối rubik
int rubik[5][5] = { col_1, col_2, col_3, col_4, col_5, col_6, col_7, col_8,
		col_9, col_10, col_11, col_12, col_13, col_14, col_15, col_16, col_17,
		col_18, col_19, col_20, col_21, col_22, col_23, col_24, col_25 };

/* Ham giu cham */
void Delay(__IO uint32_t nCount) {
	while (nCount--) {

	}
}

void clearRubik(); // Hàm tắt hết các led của khối rubik
void setRubik(); // Hàm bật tất cả led của khối rubik
//Các hàm hiệu ứng của khối rubik
void xoayXoay();
void luotSong();
void cayDua();
void textILoveU();
void lenXuong();
void traiPhai();
void truocSau();
void zeroToNine();

int main(void) {
	/* Khai bao struct de lam viec voi cong GPIO */
	GPIO_InitTypeDef CongB, CongC, CongD;

	/* Ket noi GPIOB voi clock va bat clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* Khoi tao cong B la output, chuan bi xuat du lieu ra chan 0 => 14 */
	CongB.GPIO_Pin = col_1 | col_2 | col_3 | col_4 | col_5 | col_6 | col_7
			| col_8 | col_9 | col_10 | col_11 | col_12 | col_13 | col_14
			| col_15;
	CongB.GPIO_Mode = GPIO_Mode_OUT;
	CongB.GPIO_OType = GPIO_OType_PP;
	CongB.GPIO_PuPd = GPIO_PuPd_NOPULL;
	CongB.GPIO_Speed = GPIO_Speed_100MHz;

	/* Ket noi GPIOC voi clock va bat clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* Khoi tao cong C la output, chuan bi xuat du lieu ra chan 0 => 9 */
	CongC.GPIO_Pin = col_16 | col_17 | col_18 | col_19 | col_20 | col_21
			| col_22 | col_23 | col_24 | col_25;
	CongC.GPIO_Mode = GPIO_Mode_OUT;
	CongC.GPIO_OType = GPIO_OType_PP;
	CongC.GPIO_PuPd = GPIO_PuPd_NOPULL;
	CongC.GPIO_Speed = GPIO_Speed_100MHz;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Khoi tao cong D la input, chuan bi xuat du lieu ra chan 0 => 4 */
	CongD.GPIO_Pin = row_1 | row_2 | row_3 | row_4 | row_5;
	CongD.GPIO_Mode = GPIO_Mode_OUT;
	CongD.GPIO_OType = GPIO_OType_PP;
	CongD.GPIO_PuPd = GPIO_PuPd_NOPULL;
	CongD.GPIO_Speed = GPIO_Speed_100MHz;

	/* Goi ham khoi tao cong */
	GPIO_Init(GPIOB, &CongB);
	GPIO_Init(GPIOC, &CongC);
	GPIO_Init(GPIOD, &CongD);

	while (1) {
		luotSong();
		xoayXoay();
		cayDua();
		textILoveU();
		zeroToNine();
		lenXuong();
		traiPhai();
		truocSau();
		clearRubik();
		setRubik();
		Delay(1000000);
		clearRubik();
	}
}

void xoayXoay() {
	//Lam sang den tu ngoai vao trong tang 1 va tang 5
	GPIO_SetBits(GPIOD, row_2 | row_3 | row_4 | row_5);
	GPIO_ResetBits(GPIOD, row_1 | row_5);

	int min, max, i, j;

	for (int var = 0; var < 3; var++) {
		min = max = 0;
		i = j = var;
		min = min + var, max = 4 - var;

		do {
			if (i == min && j == min) {
				GPIO_SetBits(GPIOB, rubik[i][j]);
				Delay(700000);
			}
			if (i < max && j == min) {
				i++;
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][j]);
				else
					GPIO_SetBits(GPIOC, rubik[i][j]);
				Delay(700000);
			} else if (i == max && j < max) {
				j++;
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][j]);
				else
					GPIO_SetBits(GPIOC, rubik[i][j]);
				Delay(700000);
			} else if (j == max && i > min) {
				i--;
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][j]);
				else
					GPIO_SetBits(GPIOC, rubik[i][j]);
				Delay(700000);
			} else if (i == min && j > min) {
				j--;
				if (j > min) {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][j]);
					else
						GPIO_SetBits(GPIOC, rubik[i][j]);
					Delay(700000);
				}
			}
		} while (i != min || j != min);
	}
	clearRubik();

//Hieu ung xoay hinh tru
	for (int i = 0; i < 5; i++)
		GPIO_ResetBits(GPIOD, row[i]);
	GPIO_SetBits(GPIOB,rubik[2][0] | rubik[0][2]);
	Delay(2000000);
	GPIO_SetBits(GPIOB,rubik[2][2]);
	Delay(2000000);
	GPIO_SetBits(GPIOB,rubik[2][4]);
	GPIO_SetBits(GPIOC,rubik[4][2]);
	Delay(2000000);
	GPIO_ResetBits(GPIOB,rubik[2][0] | rubik[0][2] | rubik[2][2] | rubik[2][4]);
	GPIO_ResetBits(GPIOC,rubik[4][2]);
	GPIO_SetBits(GPIOB,rubik[0][0] | rubik[1][1] | rubik[2][2]);
	GPIO_SetBits(GPIOC,rubik[3][3] | rubik[4][4]);
	Delay(2000000);
	GPIO_ResetBits(GPIOB,rubik[0][0] | rubik[1][1] | rubik[2][2]);
	GPIO_ResetBits(GPIOC,rubik[3][3] | rubik[4][4]);
	min = 0, max = 4;
	i = 0, j = 0;
	for (int loop = 0; loop < 12; loop++) {

		if (i == 0 && j == 0) {
			for (i = 0; i <= 4; i++) {
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][i]);
				else
					GPIO_SetBits(GPIOC, rubik[i][i]);
			}
			Delay(150000);
			for (i = 0; i <= 4; i++) {
				if (i < 3)
					GPIO_ResetBits(GPIOB, rubik[i][i]);
				else
					GPIO_ResetBits(GPIOC, rubik[i][i]);
			}
			i = 0;
			j = 2;
		}

		if (i == 0 && j == 2) {
			for (i = 0; i <= 4; i++) {
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][j]);
				else
					GPIO_SetBits(GPIOC, rubik[i][j]);
			}
			Delay(150000);
			for (i = 0; i <= 4; i++) {
				if (i < 3)
					GPIO_ResetBits(GPIOB, rubik[i][j]);
				else
					GPIO_ResetBits(GPIOC, rubik[i][j]);
			}
			i = 0;
			j = 4;
		}

		if (i == 0 && j == 4) {
			for (i = 0; i <= 4; i++) {
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][j - i]);
				else
					GPIO_SetBits(GPIOC, rubik[i][j - i]);
			}
			Delay(150000);
			for (i = 0; i <= 4; i++) {
				if (i < 3)
					GPIO_ResetBits(GPIOB, rubik[i][j - i]);
				else
					GPIO_ResetBits(GPIOC, rubik[i][j - i]);
			}
			i = 2;
			j = 4;
		}

		if (i == 2 && j == 4) {
			for (j = 4; j >= 0; j--) {
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][j]);
				else
					GPIO_SetBits(GPIOC, rubik[i][j]);
			}
			Delay(150000);
			for (j = 4; j >= 0; j--) {
				if (i < 3)
					GPIO_ResetBits(GPIOB, rubik[i][j]);
				else
					GPIO_ResetBits(GPIOC, rubik[i][j]);
			}
			j = 4;
			i = 4;
		}

		if (i == 4 && j == 4) {
			for (j = 4; j >= 0; j--) {
				if (j < 3)
					GPIO_SetBits(GPIOB, rubik[j][j]);
				else
					GPIO_SetBits(GPIOC, rubik[j][j]);
			}
			Delay(150000);
			for (j = 4; j >= 0; j--) {
				if (j < 3)
					GPIO_ResetBits(GPIOB, rubik[j][j]);
				else
					GPIO_ResetBits(GPIOC, rubik[j][j]);
			}
			i = 4;
			j = 2;
		}

		if (i == 4 && j == 2) {
			for (i = 4; i >= 0; i--) {
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][j]);
				else
					GPIO_SetBits(GPIOC, rubik[i][j]);
			}
			Delay(150000);
			for (i = 4; i >= 0; i--) {
				if (i < 3)
					GPIO_ResetBits(GPIOB, rubik[i][j]);
				else
					GPIO_ResetBits(GPIOC, rubik[i][j]);
			}
			i = 4;
			j = 0;
		}

		if (i == 4 && j == 0) {
			for (i = 4; i >= 0; i--) {
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][4 - i]);
				else
					GPIO_SetBits(GPIOC, rubik[i][4 - i]);
			}
			Delay(150000);
			for (i = 4; i >= 0; i--) {
				if (i < 3)
					GPIO_ResetBits(GPIOB, rubik[i][4 - i]);
				else
					GPIO_ResetBits(GPIOC, rubik[i][4 - i]);
			}
			i = 2;
			j = 0;
		}

		if (i == 2 && j == 0) {
			for (j = 0; j <= 4; j++) {
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][j]);
				else
					GPIO_SetBits(GPIOC, rubik[i][j]);
			}
			Delay(150000);
			for (j = 0; j <= 4; j++) {
				if (i < 3)
					GPIO_ResetBits(GPIOB, rubik[i][j]);
				else
					GPIO_ResetBits(GPIOC, rubik[i][j]);
			}

			i = 0;
			j = 0;
		}
	}

	//Hieu ung xoay chong chong
	for (int i = 0; i < 25; i++) {
		if (i < 15)
			GPIO_ResetBits(GPIOB, col[i]);
		else
			GPIO_ResetBits(GPIOC, col[i]);
	}
	GPIO_SetBits(GPIOD, row_1 | row_5);
	GPIO_ResetBits(GPIOD, row_1 | row_2 | row_3 | row_4 | row_5);

	int dem = 1;
	for (int loop = 0; loop < 8; loop++) {
		if (dem % 2 != 0) {
			for (int i = 0; i < 400; i++) {
				for (int j = 0; j < 5; j++) {
					if (dem == 1)
						GPIO_ResetBits(GPIOD, row[j]);
					else if (dem == 3)
						GPIO_ResetBits(GPIOD, row[4 - j]);

					for (int k = 0; k < 5; k++) {
						if (k < 3) {
							GPIO_SetBits(GPIOB, rubik[k][j]);
							Delay(100);
						} else {
							GPIO_SetBits(GPIOC, rubik[k][j]);
							Delay(100);
						}
					}

					for (int k = 0; k < 5; k++) {
						if (k < 3) {
							GPIO_ResetBits(GPIOB, rubik[k][j]);
							Delay(100);
						} else {
							GPIO_ResetBits(GPIOC, rubik[k][j]);
							Delay(100);
						}
					}

					if (dem == 1)
						GPIO_SetBits(GPIOD, row[j]);
					else if (dem == 3)
						GPIO_SetBits(GPIOD, row[4 - j]);
					Delay(100);
				}
				//Delay(100000);
			}
			//Delay(1000000);
			dem++;
		} else {

			if (dem == 2) {
				GPIO_ResetBits(GPIOD, row[2]);
				for (int j = 0; j < 25; j++) {
					if (j < 15) {
						GPIO_SetBits(GPIOB, col[j]);
					} else {
						GPIO_SetBits(GPIOC, col[j]);
					}
				}
				Delay(2000000);

				for (int j = 0; j < 25; j++) {
					if (j < 15) {
						GPIO_ResetBits(GPIOB, col[j]);
					} else {
						GPIO_ResetBits(GPIOC, col[j]);
					}
				}
				//Delay(1000000);

				dem++;
			} else if (dem == 4) {
				for (int j = 0; j < 5; j++)
					GPIO_ResetBits(GPIOD, row[j]);
				GPIO_SetBits(GPIOB, col_3 | col_8 | col_13);
				GPIO_SetBits(GPIOC, col_18 | col_23);
				Delay(2000000);

				GPIO_ResetBits(GPIOB, col_3 | col_8 | col_13);
				GPIO_ResetBits(GPIOC, col_18 | col_23);
				//Delay(1000000);

				for (int j = 0; j < 5; j++)
					GPIO_SetBits(GPIOD, row[j]);

				dem++;
			}
		}
		if (dem == 5)
			dem = 1;
	}
}

void luotSong() {

	//Lam sang den tu ngoai vao trong tang 1
	GPIO_SetBits(GPIOD, row_2 | row_3 | row_4 | row_5);
	GPIO_ResetBits(GPIOD, row_1);

	int min, max, i, j, i2, j2;

	for (int var = 0; var < 3; var++) {
		min = max = 0;
		i = j = var;
		min = min + var, max = 4 - var;

		do {
			if (i == min && j == min) {
				GPIO_SetBits(GPIOB, rubik[i][j]);
				Delay(700000);
			}
			if (i < max && j == min) {
				i++;
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][j]);
				else
					GPIO_SetBits(GPIOC, rubik[i][j]);
				Delay(700000);
			} else if (i == max && j < max) {
				j++;
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][j]);
				else
					GPIO_SetBits(GPIOC, rubik[i][j]);
				Delay(700000);
			} else if (j == max && i > min) {
				i--;
				if (i < 3)
					GPIO_SetBits(GPIOB, rubik[i][j]);
				else
					GPIO_SetBits(GPIOC, rubik[i][j]);
				Delay(700000);
			} else if (i == min && j > min) {
				j--;
				if (j > min) {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][j]);
					else
						GPIO_SetBits(GPIOC, rubik[i][j]);
					Delay(700000);
				}
			}
		} while (i != min || j != min);
	}

	for (i = 0; i < 25; i++) {
		if (i < 15)
			GPIO_ResetBits(GPIOB, col[i]);
		else
			GPIO_ResetBits(GPIOC, col[i]);
	}
	GPIO_SetBits(GPIOD, row_1);
	GPIO_ResetBits(GPIOD, row_1 | row_2 | row_3 | row_4 | row_5);

	//Luot song tu goc 25 = > goc 1
	for (int loop = 0; loop < 8; loop++) {
		for (int var = 8; var >= 0; var--) {

			if (var >= 4) {
				i = max = 4;
				j = var - max;
			} else {
				i = max = var;
				j = 0;
			}

			while (i <= max && j <= max) {
				if (i + j == var) {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][j]);
					else
						GPIO_SetBits(GPIOC, rubik[i][j]);
				}

				i--;
				j++;
			}
			Delay(120000);

			if (var >= 4) {
				i = max = 4;
				j = var - max;
			} else {
				i = max = var;
				j = 0;
			}

			while (i <= max && j <= max) {
				if (i + j == var) {
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][j]);
					else
						GPIO_ResetBits(GPIOC, rubik[i][j]);
				}

				i--;
				j++;
			}

			Delay(30000);
		}
	}

	clearRubik();
	min = 0;
	max = 4;
	i = j2 = max;
	i2 = j = min;
	int arr1[5], arr2[5], arr3[5], arr4[5];

	for (int var = 0; var < 96; var++) {

		GPIO_SetBits(GPIOD, row_1 | row_2 | row_3 | row_4 | row_5);

		for (int k = 0; k < 5; k++) {
			if (i == max && j < max)
				j++;
			else if (j == max && i > min)
				i--;
			else if (i == min && j > min)
				j--;
			else if (j == min && i < max)
				i++;

			if (i2 == max && j2 < max)
				j2++;
			else if (j2 == max && i2 > min)
				i2--;
			else if (i2 == min && j2 > min)
				j2--;
			else if (j2 == min && i2 < max)
				i2++;
			arr1[k] = i;
			arr2[k] = j;
			arr3[k] = i2;
			arr4[k] = j2;
			if (k == 4) {
				i = arr1[0];
				j = arr2[0];
				i2 = arr3[0];
				j2 = arr4[0];
			}
		}

		for (int loop = 0; loop < 10; loop++) {
			for (int k = 0; k < 5; k++) {
				GPIO_SetBits(GPIOD, row_1 | row_2 | row_3 | row_4 | row_5);
				GPIO_ResetBits(GPIOD, row[k]);
				if (arr1[k] < 3)
					GPIO_SetBits(GPIOB, rubik[arr1[k]][arr2[k]]);
				else
					GPIO_SetBits(GPIOC, rubik[arr1[k]][arr2[k]]);
				Delay(2000);
				if (arr3[k] < 3)
					GPIO_SetBits(GPIOB, rubik[arr3[k]][arr4[k]]);
				else
					GPIO_SetBits(GPIOC, rubik[arr3[k]][arr4[k]]);
				Delay(2000);
				if (arr1[k] < 3)
					GPIO_ResetBits(GPIOB, rubik[arr1[k]][arr2[k]]);
				else
					GPIO_ResetBits(GPIOC, rubik[arr1[k]][arr2[k]]);
				//Delay(1000);
				if (arr3[k] < 3)
					GPIO_ResetBits(GPIOB, rubik[arr3[k]][arr4[k]]);
				else
					GPIO_ResetBits(GPIOC, rubik[arr3[k]][arr4[k]]);
				//Delay(1000);
			}
		}

	}
}

void cayDua() {
	clearRubik();
	for (int i = 0; i < 5; i++) {
		GPIO_ResetBits(GPIOD, row[i]);
		GPIO_SetBits(GPIOB, rubik[2][2]);
		Delay(300000);
		GPIO_ResetBits(GPIOB, rubik[2][2]);

		GPIO_SetBits(GPIOD, row[i]);
	}

	GPIO_ResetBits(GPIOD, row[4]);
	GPIO_SetBits(GPIOB, rubik[1][1] | rubik[1][3]);
	GPIO_SetBits(GPIOC, rubik[3][1] | rubik[3][3]);
	GPIO_SetBits(GPIOB, rubik[1][2] | rubik[2][1] | rubik[2][3]);
	GPIO_SetBits(GPIOC, rubik[3][2]);
	Delay(300000);
	GPIO_ResetBits(GPIOB, rubik[1][1] | rubik[1][3]);
	GPIO_ResetBits(GPIOC, rubik[3][1] | rubik[3][3]);
	GPIO_ResetBits(GPIOB, rubik[1][2] | rubik[2][1] | rubik[2][3]);
	GPIO_ResetBits(GPIOC, rubik[3][2]);

	GPIO_SetBits(GPIOB,
			rubik[0][0] | rubik[0][4] | rubik[1][0] | rubik[2][0] | rubik[1][4]
					| rubik[2][4]);
	GPIO_SetBits(GPIOC, rubik[4][0] | rubik[4][4] | rubik[3][0] | rubik[3][4]);
	GPIO_SetBits(GPIOB, rubik[0][1] | rubik[0][2] | rubik[0][3]);
	GPIO_SetBits(GPIOC, rubik[4][1] | rubik[4][2] | rubik[4][3]);
	Delay(300000);
	//GPIO_ResetBits(GPIOB,rubik[0][0] | rubik[0][4]);
	//GPIO_ResetBits(GPIOC,rubik[4][0] | rubik[4][4]);
	GPIO_SetBits(GPIOD, row[4]);
	for (int i = 3; i >= 0; i--) {
		GPIO_ResetBits(GPIOD, row[i]);
		Delay(300000);
		GPIO_SetBits(GPIOD, row[i]);
	}

	GPIO_ResetBits(GPIOB,
			rubik[0][0] | rubik[0][4] | rubik[1][0] | rubik[2][0] | rubik[1][4]
					| rubik[2][4]);
	GPIO_ResetBits(GPIOC,
			rubik[4][0] | rubik[4][4] | rubik[3][0] | rubik[3][4]);
	GPIO_ResetBits(GPIOB, rubik[0][1] | rubik[0][2] | rubik[0][3]);
	GPIO_ResetBits(GPIOC, rubik[4][1] | rubik[4][2] | rubik[4][3]);

	for (int loop = 0; loop < 15; loop++) {
		int min = 2, max = 2;
		for (int i = 0; i < 3; i++) {
			GPIO_ResetBits(GPIOD, row[min] | row[max]);
			if (min == max) {
				if (min < 3)
					GPIO_SetBits(GPIOB, rubik[min][max]);
				else
					GPIO_SetBits(GPIOC, rubik[min][max]);
				Delay(350000);
				if (min < 3)
					GPIO_ResetBits(GPIOB, rubik[min][max]);
				else
					GPIO_ResetBits(GPIOC, rubik[min][max]);
			} else {
				if (min < 3)
					GPIO_SetBits(GPIOB, rubik[min][min] | rubik[min][max]);
				else
					GPIO_SetBits(GPIOC, rubik[min][min] | rubik[min][max]);

				if (max < 3)
					GPIO_SetBits(GPIOB, rubik[max][min] | rubik[max][max]);
				else
					GPIO_SetBits(GPIOC, rubik[max][min] | rubik[max][max]);
				Delay(350000);

				if (min < 3)
					GPIO_ResetBits(GPIOB, rubik[min][min] | rubik[min][max]);
				else
					GPIO_ResetBits(GPIOC, rubik[min][min] | rubik[min][max]);

				if (max < 3)
					GPIO_ResetBits(GPIOB, rubik[max][min] | rubik[max][max]);
				else
					GPIO_ResetBits(GPIOC, rubik[max][min] | rubik[max][max]);

			}
			GPIO_SetBits(GPIOD, row[min] | row[max]);
			min--;
			max++;
		}
	}

//	GPIO_SetBits(GPIOD, row_2 | row_3 | row_4 | row_5);
//	int min, max, i, j;
//	for (int loop = 0; loop < 5; loop++) {
//	for (int var = 2; var >= 0; var--) {
//
//		//min = max = 0;
//		i = j = var;
//		min = var , max = 4 - var;
//		//GPIO_ResetBits(GPIOD, row[min] | row[max]);
//		for(int r = min; r <= max; r++)
//			GPIO_ResetBits(GPIOD,row[r]);
//
//		do {
//
//			if (i == min && j == min) {
//				GPIO_SetBits(GPIOB, rubik[i][j]);
//				//Delay(400000);
//				//i--, j--;
//				//min--, max++;
//				//break;
//			}
//			if (i < max && j == min) {
//				i++;
//				if (i < 3)
//					GPIO_SetBits(GPIOB, rubik[i][j]);
//				else
//					GPIO_SetBits(GPIOC, rubik[i][j]);
//			} else if (i == max && j < max) {
//				j++;
//				if (i < 3)
//					GPIO_SetBits(GPIOB, rubik[i][j]);
//				else
//					GPIO_SetBits(GPIOC, rubik[i][j]);
//			} else if (j == max && i > min) {
//				i--;
//				if (i < 3)
//					GPIO_SetBits(GPIOB, rubik[i][j]);
//				else
//					GPIO_SetBits(GPIOC, rubik[i][j]);
//			} else if (i == min && j > min) {
//				j--;
//				if (j > min) {
//					if (i < 3)
//						GPIO_SetBits(GPIOB, rubik[i][j]);
//					else
//						GPIO_SetBits(GPIOC, rubik[i][j]);
//				}
//			}
//
//		} while (i != min || j != min);
//
//		Delay(350000);
//
//		for(int r = min; r <= max; r++)
//			GPIO_SetBits(GPIOD,row[r]);
//		clearRubikV2(min,max);
//	}
//	clearRubik();
//	}
}

void textILoveU()
{

	//Chu I
	for(int var = 0; var < 2; var++)
	{
		for(int loop = 0; loop < 100; loop++)
		{
			for(int i = 0; i < 5; i++)
			{
				GPIO_ResetBits(GPIOD,row[i]);
				if(i == 0 || i == 4)
				{
					for(int j = 0; j < 5; j++)
					{
						if(i < 3)
							GPIO_SetBits(GPIOB,rubik[i][j]);
						else GPIO_SetBits(GPIOC,rubik[i][j]);
						Delay(1000);
						if(4-i < 3)
							GPIO_SetBits(GPIOB,rubik[4-i][j]);
						else GPIO_SetBits(GPIOC,rubik[4-i][j]);
						Delay(1000);
						if(i < 3)
							GPIO_ResetBits(GPIOB,rubik[i][j]);
						else GPIO_ResetBits(GPIOC,rubik[i][j]);
						if(4-i < 3)
							GPIO_ResetBits(GPIOB,rubik[4-i][j]);
						else GPIO_ResetBits(GPIOC,rubik[4-i][j]);
					}
				} else {
					GPIO_SetBits(GPIOB,rubik[0][2]);
					GPIO_SetBits(GPIOC,rubik[4][2]);
					Delay(1000);
					GPIO_ResetBits(GPIOB,rubik[0][2]);
					GPIO_ResetBits(GPIOC,rubik[4][2]);
				}
				GPIO_SetBits(GPIOD,row[i]);
			}
		}
		Delay(2000000);
	}

	//Trai <3
	for(int var = 0; var < 2; var++)
	{
		for(int loop = 0; loop < 100; loop++)
		{
			GPIO_ResetBits(GPIOD,row[0]);
			GPIO_SetBits(GPIOB,rubik[0][2]);
			GPIO_SetBits(GPIOC,rubik[4][2]);
			Delay(1000);
			GPIO_ResetBits(GPIOB,rubik[0][2]);
			GPIO_ResetBits(GPIOC,rubik[4][2]);
			GPIO_SetBits(GPIOD,row[0]);
			GPIO_ResetBits(GPIOD,row[1]);
			GPIO_SetBits(GPIOB,rubik[0][1] | rubik[0][2] | rubik[0][3]);
			GPIO_SetBits(GPIOC,rubik[4][1] | rubik[4][2] | rubik[4][3]);
			Delay(1000);
			GPIO_ResetBits(GPIOB,rubik[0][1] | rubik[0][2] | rubik[0][3]);
			GPIO_ResetBits(GPIOC,rubik[4][1] | rubik[4][2] | rubik[4][3]);
			GPIO_SetBits(GPIOD,row[1]);
			for(int i = 2; i <= 3; i++)
			{
				GPIO_ResetBits(GPIOD,row[i]);
				for(int j = 0; j < 5; j++)
				{
					GPIO_SetBits(GPIOB,rubik[0][j]);
					GPIO_SetBits(GPIOC,rubik[4][j]);
					Delay(1000);
					GPIO_ResetBits(GPIOB,rubik[0][j]);
					GPIO_ResetBits(GPIOC,rubik[4][j]);
				}
				GPIO_ResetBits(GPIOD,row[i]);
			}
			GPIO_ResetBits(GPIOD,row[4]);
			GPIO_SetBits(GPIOB,rubik[0][1] | rubik[0][3]);
			GPIO_SetBits(GPIOC,rubik[4][1] | rubik[4][3]);
			Delay(1000);
			GPIO_ResetBits(GPIOB,rubik[0][1] | rubik[0][3]);
			GPIO_ResetBits(GPIOC,rubik[4][1] | rubik[4][3]);
			GPIO_SetBits(GPIOD,row[4]);
		}
		Delay(2000000);
	}

	//Chu U
	for(int var = 0; var < 2; var++)
	{
		for(int loop = 0; loop < 100; loop++)
		{
			for(int i = 0; i < 5; i++)
			{
				GPIO_ResetBits(GPIOD,row[i]);
				if(i == 0)
				{
					for(int j = 1; j <= 3; j++)
					{
						GPIO_SetBits(GPIOB,rubik[i][j]);
						GPIO_SetBits(GPIOC,rubik[4][j]);
						Delay(2000);
						GPIO_ResetBits(GPIOB,rubik[i][j]);
						GPIO_ResetBits(GPIOC,rubik[4][j]);
					}
				} else {
					GPIO_SetBits(GPIOB,rubik[0][0] | rubik[0][4]);
					GPIO_SetBits(GPIOC,rubik[4][0] | rubik[4][4]);
					Delay(2000);
					GPIO_ResetBits(GPIOB,rubik[0][0] | rubik[0][4]);
					GPIO_ResetBits(GPIOC,rubik[4][0] | rubik[4][4]);
				}
				GPIO_SetBits(GPIOD,row[i]);
			}
		}
		Delay(2000000);
	}
}

void lenXuong()
{
	clearRubik();
	for(int loop = 0; loop < 5; loop++)
	{
		for (int i = 0; i < 5; i++)
		{
			GPIO_ResetBits(GPIOD,row[i]);
			for (int j = 0; j < 25; j++)
			{
				if(j < 15)
					GPIO_SetBits(GPIOB,col[j]);
				else GPIO_SetBits(GPIOC,col[j]);
			}
			Delay(100000);

			for (int j = 0; j < 25; j++)
			{
				if(j < 15)
					GPIO_ResetBits(GPIOB,col[j]);
				else GPIO_ResetBits(GPIOC,col[j]);
			}

			GPIO_SetBits(GPIOD,row[i]);
			Delay(10000);
		}

		for (int i = 4; i >= 0; i--)
		{
			GPIO_ResetBits(GPIOD,row[i]);
			for (int j = 0; j < 25; j++)
			{
				if(j < 15)
					GPIO_SetBits(GPIOB,col[j]);
				else GPIO_SetBits(GPIOC,col[j]);
			}
			Delay(100000);

			for (int j = 0; j < 25; j++)
			{
				if(j < 15)
					GPIO_ResetBits(GPIOB,col[j]);
				else GPIO_ResetBits(GPIOC,col[j]);
			}
			GPIO_SetBits(GPIOD,row[i]);
			Delay(10000);
		}
	}

}

void traiPhai()
{
	clearRubik();
	for(int loop = 0; loop < 5; loop++)
	{
		GPIO_ResetBits(GPIOD,row[0] | row[1] | row[2] | row[3] | row[4]);

		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if(k < 3)
					GPIO_SetBits(GPIOB,rubik[k][j]);
				else GPIO_SetBits(GPIOC,rubik[k][j]);
			}
			Delay(100000);

			for (int k = 0; k < 5; k++)
			{
				if(k < 3)
					GPIO_ResetBits(GPIOB,rubik[k][j]);
				else GPIO_ResetBits(GPIOC,rubik[k][j]);
			}
			Delay(10000);
		}

		for (int j = 4; j >= 0; j--)
		{
			for (int k = 0; k < 5; k++)
			{
				if(k < 3)
					GPIO_SetBits(GPIOB,rubik[k][j]);
				else GPIO_SetBits(GPIOC,rubik[k][j]);
			}
			Delay(100000);

			for (int k = 0; k < 5; k++)
			{
				if(k < 3)
					GPIO_ResetBits(GPIOB,rubik[k][j]);
				else GPIO_ResetBits(GPIOC,rubik[k][j]);
			}
			Delay(10000);
		}

		GPIO_SetBits(GPIOD,row[0] | row[1] | row[2] | row[3] | row[4]);

	}
}

void truocSau()
{
	clearRubik();
	for(int loop = 0; loop < 5; loop++)
	{
		GPIO_ResetBits(GPIOD,row[0] | row[1] | row[2] | row[3] | row[4]);

		for (int j = 4; j >= 0; j--)
		{
			for (int k = 0; k < 5; k++)
			{
				if(j < 3)
					GPIO_SetBits(GPIOB,rubik[j][k]);
				else GPIO_SetBits(GPIOC,rubik[j][k]);
			}
			Delay(100000);

			for (int k = 0; k < 5; k++)
			{
				if(j < 3)
					GPIO_ResetBits(GPIOB,rubik[j][k]);
				else GPIO_ResetBits(GPIOC,rubik[j][k]);
			}
			Delay(10000);
		}

		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if(j < 3)
					GPIO_SetBits(GPIOB,rubik[j][k]);
				else GPIO_SetBits(GPIOC,rubik[j][k]);
			}
			Delay(100000);

			for (int k = 0; k < 5; k++)
			{
				if(j < 3)
					GPIO_ResetBits(GPIOB,rubik[j][k]);
				else GPIO_ResetBits(GPIOC,rubik[j][k]);
			}
			Delay(10000);
		}

		GPIO_SetBits(GPIOD,row[0] | row[1] | row[2] | row[3] | row[4]);

	}
}

void zeroToNine()
{
	clearRubik();
	//so 0
	for (int i = 0; i < 5; i++)
	{
		for (int c = 0; c < 100; c++)
		{
			for (int j = 0; j < 5; j++)
			{
				GPIO_ResetBits(GPIOD,row[j]);
				if (j == 0 || j == 4)
				{
					for (int k = 1; k <= 3; k++)
					{
						if (i < 3)
							GPIO_SetBits(GPIOB,rubik[i][k]);
						else GPIO_SetBits(GPIOC,rubik[i][k]);
						Delay(100);
						if (i < 3)
							GPIO_ResetBits(GPIOB,rubik[i][k]);
						else GPIO_ResetBits(GPIOC,rubik[i][k]);
					}
				} else {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][1] | rubik[i][3]);
					else GPIO_SetBits(GPIOC, rubik[i][1] | rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][1] | rubik[i][3]);
					else GPIO_ResetBits(GPIOC, rubik[i][1] | rubik[i][3]);
				}
				GPIO_SetBits(GPIOD,row[j]);
			}
		}
		Delay(100000);
	}

	//So 1
	for (int i = 0; i < 5; i++)
	{
		for (int c = 0; c < 100; c++)
		{
			for (int j = 0; j < 5; j++)
			{
				GPIO_ResetBits(GPIOD,row[j]);
				if (j == 2)
				{

					if (i < 3)
						GPIO_SetBits(GPIOB,rubik[i][1] | rubik[i][3]);
					else GPIO_SetBits(GPIOC,rubik[i][1] | rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB,rubik[i][1] | rubik[i][3]);
					else GPIO_ResetBits(GPIOC,rubik[i][1] | rubik[i][3]);
				} else if (j == 3) {
					if (i < 3)
						GPIO_SetBits(GPIOB,rubik[i][2] | rubik[i][3]);
					else GPIO_SetBits(GPIOC,rubik[i][2] | rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB,rubik[i][2] | rubik[i][3]);
					else GPIO_ResetBits(GPIOC,rubik[i][2] | rubik[i][3]);
				} else {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][3]);
					else GPIO_SetBits(GPIOC, rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][3]);
					else GPIO_ResetBits(GPIOC, rubik[i][3]);
				}
				GPIO_SetBits(GPIOD,row[j]);
			}
		}
		Delay(150000);
	}

	//So 2
	for (int i = 0; i < 5; i++)
	{
		for (int c = 0; c < 100; c++)
		{
			for (int j = 0; j < 5; j++)
			{
				GPIO_ResetBits(GPIOD,row[j]);
				if (j == 0 || j == 2 || j == 4)
				{
					for (int k = 1; k <= 3; k++)
					{
						if (i < 3)
							GPIO_SetBits(GPIOB,rubik[i][k]);
						else GPIO_SetBits(GPIOC,rubik[i][k]);
						Delay(100);
						if (i < 3)
							GPIO_ResetBits(GPIOB,rubik[i][k]);
						else GPIO_ResetBits(GPIOC,rubik[i][k]);
					}
				} else if (j == 1){
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][1]);
					else GPIO_SetBits(GPIOC, rubik[i][1]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][1]);
					else GPIO_ResetBits(GPIOC, rubik[i][1]);
				} else {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][3]);
					else GPIO_SetBits(GPIOC, rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][3]);
					else GPIO_ResetBits(GPIOC, rubik[i][3]);
				}
				GPIO_SetBits(GPIOD,row[j]);
			}
		}
		Delay(100000);
	}

	//So 3
	for (int i = 0; i < 5; i++)
	{
		for (int c = 0; c < 100; c++)
		{
			for (int j = 0; j < 5; j++)
			{
				GPIO_ResetBits(GPIOD,row[j]);
				if (j == 0 || j == 2 || j == 4)
				{
					for (int k = 1; k <= 3; k++)
					{
						if (i < 3)
							GPIO_SetBits(GPIOB,rubik[i][k]);
						else GPIO_SetBits(GPIOC,rubik[i][k]);
						Delay(100);
						if (i < 3)
							GPIO_ResetBits(GPIOB,rubik[i][k]);
						else GPIO_ResetBits(GPIOC,rubik[i][k]);
					}
				} else {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][3]);
					else GPIO_SetBits(GPIOC, rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][3]);
					else GPIO_ResetBits(GPIOC, rubik[i][3]);
				}
				GPIO_SetBits(GPIOD,row[j]);
			}
		}
		Delay(100000);
	}

	//So 4
	for (int i = 0; i < 5; i++)
	{
		for (int c = 0; c < 100; c++)
		{
			for (int j = 0; j < 5; j++)
			{
				GPIO_ResetBits(GPIOD,row[j]);
				if (j == 0 || j == 1)
				{
					if (i < 3)
						GPIO_SetBits(GPIOB,rubik[i][3]);
					else GPIO_SetBits(GPIOC,rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB,rubik[i][3]);
					else GPIO_ResetBits(GPIOC,rubik[i][3]);
				} else if (j == 2) {
					for (int k = 1; k <= 3; k++)
					{
						if (i < 3)
							GPIO_SetBits(GPIOB,rubik[i][k]);
						else GPIO_SetBits(GPIOC,rubik[i][k]);
						Delay(100);
						if (i < 3)
							GPIO_ResetBits(GPIOB,rubik[i][k]);
						else GPIO_ResetBits(GPIOC,rubik[i][k]);
					}
				} else {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][1] | rubik[i][3]);
					else GPIO_SetBits(GPIOC, rubik[i][1] | rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][1] | rubik[i][3]);
					else GPIO_ResetBits(GPIOC, rubik[i][1] | rubik[i][3]);
				}
				GPIO_SetBits(GPIOD,row[j]);
			}
		}
		Delay(100000);
	}

	//So 5
	for (int i = 0; i < 5; i++)
	{
		for (int c = 0; c < 100; c++)
		{
			for (int j = 0; j < 5; j++)
			{
				GPIO_ResetBits(GPIOD,row[j]);
				if (j == 0 || j == 2 || j == 4)
				{
					for (int k = 1; k <= 3; k++)
					{
						if (i < 3)
							GPIO_SetBits(GPIOB,rubik[i][k]);
						else GPIO_SetBits(GPIOC,rubik[i][k]);
						Delay(100);
						if (i < 3)
							GPIO_ResetBits(GPIOB,rubik[i][k]);
						else GPIO_ResetBits(GPIOC,rubik[i][k]);
					}
				} else if (j == 1){
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][3]);
					else GPIO_SetBits(GPIOC, rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][3]);
					else GPIO_ResetBits(GPIOC, rubik[i][3]);
				} else {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][1]);
					else GPIO_SetBits(GPIOC, rubik[i][1]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][1]);
					else GPIO_ResetBits(GPIOC, rubik[i][1]);
				}
				GPIO_SetBits(GPIOD,row[j]);
			}
		}
		Delay(100000);
	}

	//So 6
	for (int i = 0; i < 5; i++)
	{
		for (int c = 0; c < 100; c++)
		{
			for (int j = 0; j < 5; j++)
			{
				GPIO_ResetBits(GPIOD,row[j]);
				if (j == 0 || j == 2 || j == 4)
				{
					for (int k = 1; k <= 3; k++)
					{
						if (i < 3)
							GPIO_SetBits(GPIOB,rubik[i][k]);
						else GPIO_SetBits(GPIOC,rubik[i][k]);
						Delay(100);
						if (i < 3)
							GPIO_ResetBits(GPIOB,rubik[i][k]);
						else GPIO_ResetBits(GPIOC,rubik[i][k]);
					}
				} else if (j == 1){
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][1] | rubik[i][3] );
					else GPIO_SetBits(GPIOC, rubik[i][1] | rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][1] | rubik[i][3]);
					else GPIO_ResetBits(GPIOC, rubik[i][1] | rubik[i][3]);
				} else {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][1]);
					else GPIO_SetBits(GPIOC, rubik[i][1]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][1]);
					else GPIO_ResetBits(GPIOC, rubik[i][1]);
				}
				GPIO_SetBits(GPIOD,row[j]);
			}
		}
		Delay(100000);
	}

	//So 7
	for (int i = 0; i < 5; i++)
	{
		for (int c = 0; c < 100; c++)
		{
			for (int j = 0; j < 5; j++)
			{
				GPIO_ResetBits(GPIOD,row[j]);
				if (j == 4)
				{
					for (int k = 1; k <= 3; k++)
					{
						if (i < 3)
							GPIO_SetBits(GPIOB,rubik[i][k]);
						else GPIO_SetBits(GPIOC,rubik[i][k]);
						Delay(100);
						if (i < 3)
							GPIO_ResetBits(GPIOB,rubik[i][k]);
						else GPIO_ResetBits(GPIOC,rubik[i][k]);
					}
				} else {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][3]);
					else GPIO_SetBits(GPIOC, rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][3]);
					else GPIO_ResetBits(GPIOC, rubik[i][3]);
				}
				GPIO_SetBits(GPIOD,row[j]);
			}
		}
		Delay(100000);
	}

	//So 8
	for (int i = 0; i < 5; i++)
	{
		for (int c = 0; c < 100; c++)
		{
			for (int j = 0; j < 5; j++)
			{
				GPIO_ResetBits(GPIOD,row[j]);
				if (j == 0 || j == 2 || j == 4)
				{
					for (int k = 1; k <= 3; k++)
					{
						if (i < 3)
							GPIO_SetBits(GPIOB,rubik[i][k]);
						else GPIO_SetBits(GPIOC,rubik[i][k]);
						Delay(100);
						if (i < 3)
							GPIO_ResetBits(GPIOB,rubik[i][k]);
						else GPIO_ResetBits(GPIOC,rubik[i][k]);
					}
				} else {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][1] | rubik[i][3] );
					else GPIO_SetBits(GPIOC, rubik[i][1] | rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][1] | rubik[i][3]);
					else GPIO_ResetBits(GPIOC, rubik[i][1] | rubik[i][3]);
				}
				GPIO_SetBits(GPIOD,row[j]);
			}
		}
		Delay(100000);
	}

	//So 9
	for (int i = 0; i < 5; i++)
	{
		for (int c = 0; c < 100; c++)
		{
			for (int j = 0; j < 5; j++)
			{
				GPIO_ResetBits(GPIOD,row[j]);
				if (j == 0 || j == 2 || j == 4)
				{
					for (int k = 1; k <= 3; k++)
					{
						if (i < 3)
							GPIO_SetBits(GPIOB,rubik[i][k]);
						else GPIO_SetBits(GPIOC,rubik[i][k]);
						Delay(100);
						if (i < 3)
							GPIO_ResetBits(GPIOB,rubik[i][k]);
						else GPIO_ResetBits(GPIOC,rubik[i][k]);
					}
				} else if (j == 3){
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][1] | rubik[i][3] );
					else GPIO_SetBits(GPIOC, rubik[i][1] | rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][1] | rubik[i][3]);
					else GPIO_ResetBits(GPIOC, rubik[i][1] | rubik[i][3]);
				} else {
					if (i < 3)
						GPIO_SetBits(GPIOB, rubik[i][3]);
					else GPIO_SetBits(GPIOC, rubik[i][3]);
					Delay(100);
					if (i < 3)
						GPIO_ResetBits(GPIOB, rubik[i][3]);
					else GPIO_ResetBits(GPIOC, rubik[i][3]);
				}
				GPIO_SetBits(GPIOD,row[j]);
			}
		}
		Delay(100000);
	}
}


void clearRubik() {
	for (int i = 0; i < 5; i++)
		GPIO_SetBits(GPIOD, row[i]);
	for (int j = 0; j < 25; j++) {
		if (j < 15)
			GPIO_ResetBits(GPIOB, col[j]);
		else
			GPIO_ResetBits(GPIOC, col[j]);
	}
}

void setRubik()
{
	for (int i = 0; i < 5; i++)
		GPIO_ResetBits(GPIOD, row[i]);
	for (int j = 0; j < 25; j++) {
		if (j < 15)
			GPIO_SetBits(GPIOB, col[j]);
		else
			GPIO_SetBits(GPIOC, col[j]);
	}
}


// void clearRubikV2(int min, int max) {
// 	for (int i = min; i <= max; i++) {
// 		GPIO_SetBits(GPIOD, row[i]);
// 		for (int j = min; j <= max; j++) {
// 			if (i < 3)
// 				GPIO_ResetBits(GPIOB, rubik[i][j]);
// 			else
// 				GPIO_ResetBits(GPIOC, rubik[i][j]);
// 		}
// 	}
// }
