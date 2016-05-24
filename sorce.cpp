#include<stdio.h>

int field[10][10] = {0};
int player = 1;


void InitializeField(){	//�Ֆʂ̏�����
	//�ǂ̐���(�X�F�ǁA�O�F��)
	for(int i = 0; i < 10; i++){
		field[0][i] = 9;
		field[i][0] = 9;
		field[9][i] = 9;
		field[i][9] = 9;
	}
	//�����΂̐ݒu�i�P�F���A�Q�F���j
	field[4][4] = 2;
	field[5][5] = 2;
	field[4][5] = 1;
	field[5][4] = 1;
}


void ShowField(){	//�Ֆʂ̕\��

	printf("  ");
	for(int i = 1; i < 9; i++){
		printf(" %d ",i);
	}
	printf("\n");

	for(int i = 1; i < 9; i++){
		printf("  ");
		printf("�\�\�\�\�\�\�\�\�\�\�\�\");
		printf("\n%d |",i);
		for(int j = 1; j < 9; j++){

			switch(field[i][j]){
			case 1:
				printf("��|");
				break;
			case 2:
				printf("��|");
				break;
			case 3:
				printf("��|");
				break;
			default:
				printf("  |");
			}
		}
		printf("\n");
	}
	printf("  ");
	printf("�\�\�\�\�\�\�\�\�\�\�\�\\n");
}


void Reverse(int y, int x){
	int dy = y;
	int dx = x;
	int count;

	field[y][x] = player;	//�u�����ꏊ�ɋ��u��
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			count = 0;
			dy = y;
			dx = x;
			while(field[dy + i][dx + j] == 3 - player){	//�G����t�]�ł����
				dy += i;
				dx += j;
				count++;
			}
			if(field[dy + i][dx + j] == player){//�Ōオ�����̋������
				dy = y;
				dx = x;
				while(count > 0){		//�t�]
					dy += i;
					dx += j;
					field[dy][dx] = player;
					count--;
				}
			}
		}
	}
	player = 3 - player;
}


void FieldPut(){//�Տ�ɒu���邩���肷��B�u������Reverse�֐��Ăяo��

	int x,y;
	int put_flug = 0;

	if(player == 1){
		puts("���̔Ԃł�");
	}else{
		puts("���̔Ԃł�");
	}
	do{
		puts("�u���ꏊ���w�肵�Ă�������");
		scanf("%d %d",&y,&x);
		if(field[y][x] == 3){
			Reverse(y,x);
			put_flug = 1;
		}else{
			puts("���̏ꏊ�͒u���܂���I");
		}
	}while(put_flug == 0);
}


int SearchReverse(int y, int x){//field[y][x]�ɒu����Ȃ灖�������
	int dy = y;
	int dx = x;
	int put_flag = 0;
	bool put_jadge = 0;

	if(field[y][x] == 0 || field[y][x] == 3){
		field[y][x] = 0;
		for(int i = -1; i < 2; i++){
			for(int j = -1; j < 2; j++){
				while(field[dy + i][dx + j] == 3 - player){	//�G����ǂ��܂ŋt�]�ł��邩
					dy += i;
					dx += j;
					put_flag = 1;
				}
				if(field[dy + i][dx + j] == player && put_flag == 1){	//�Ōオ�����̋������
					field[y][x] = 3;
					put_jadge = 1;
				}
				dy = y;
				dx = x;
				put_flag = 0;
			}
		}
	}
	return put_jadge;
}

void WinnerJudge(){
	int black_score = 0;
	int white_score = 0;
	for(int i = 1; i < 9; i++){
		for(int j = 1; j < 9; j++){
			if(field[i][j] == 1){
				black_score += 1;
			}else if(field[i][j] == 2){
				white_score += 1;
			}
		}
	}
	puts("���ʔ��\�I�I�I");
	printf("��: %d��\n��: %d��\n\n",black_score,white_score);
	if(black_score > white_score){
		puts("���̏����I�I");
	}else if(black_score < white_score){
		puts("���̏����I�I");
	}else{
		puts("���������I");
	}
}

void Play(){

	InitializeField();
	int put_judge = 0;
	int end_jadge = 0;

	printf("---------�I�Z���Q�[���I----------\n\n");
	while(1){
		for(int i = 1; i < 9; i++){
			for(int j = 1; j < 9; j++){
				put_judge += SearchReverse(i,j);
			}
		}
		ShowField();
		if(put_judge > 0){
			FieldPut();
			put_judge = 0;
		}else if(end_jadge == 1){
			puts("�ǂ�����u���Ȃ��̂ŏW�v���܂�");
			WinnerJudge();
			break;
		}else{
			if(player == 1){
				puts("���͒u���Ȃ������̂Ńp�X���܂���");
			}else{
				puts("���͒u���Ȃ������̂Ńp�X���܂���");
			}
			player = 3 - player;
			end_jadge = 1;
		}
	}
}


int main(){
	Play();
	return 0;
}