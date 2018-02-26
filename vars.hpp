#define VM_N 30
#define VM_M 21
#define VM_Scale 25
#define DB 100
#define VD_W VM_N * VM_Scale
#define VD_H VM_M * VM_Scale





struct snk {
	int x;
	int y;
};




int dir = 1, sh = 5;

int score = 0;

snk s[100];


int step = 300;


int MX, myMX;
