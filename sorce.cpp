#include<stdio.h>

int field[10][10] = {0};
int player = 1;


void InitializeField(){	//盤面の初期化
	//壁の生成(９：壁、０：空)
	for(int i = 0; i < 10; i++){
		field[0][i] = 9;
		field[i][0] = 9;
		field[9][i] = 9;
		field[i][9] = 9;
	}
	//初期石の設置（１：黒、２：白）
	field[4][4] = 2;
	field[5][5] = 2;
	field[4][5] = 1;
	field[5][4] = 1;
}


void ShowField(){	//盤面の表示

	printf("  ");
	for(int i = 1; i < 9; i++){
		printf(" %d ",i);
	}
	printf("\n");

	for(int i = 1; i < 9; i++){
		printf("  ");
		printf("――――――――――――");
		printf("\n%d |",i);
		for(int j = 1; j < 9; j++){

			switch(field[i][j]){
			case 1:
				printf("○|");
				break;
			case 2:
				printf("●|");
				break;
			case 3:
				printf("＊|");
				break;
			default:
				printf("  |");
			}
		}
		printf("\n");
	}
	printf("  ");
	printf("――――――――――――\n");
}


void Reverse(int y, int x){
	int dy = y;
	int dx = x;
	int count;

	field[y][x] = player;	//置いた場所に駒を置く
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			count = 0;
			dy = y;
			dx = x;
			while(field[dy + i][dx + j] == 3 - player){	//敵駒を逆転できる個数
				dy += i;
				dx += j;
				count++;
			}
			if(field[dy + i][dx + j] == player){//最後が自分の駒だったら
				dy = y;
				dx = x;
				while(count > 0){		//逆転
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


void FieldPut(){//盤上に置けるか判定する。置けたらReverse関数呼び出し

	int x,y;
	int put_flug = 0;

	if(player == 1){
		puts("黒の番です");
	}else{
		puts("白の番です");
	}
	do{
		puts("置く場所を指定してください");
		scanf("%d %d",&y,&x);
		if(field[y][x] == 3){
			Reverse(y,x);
			put_flug = 1;
		}else{
			puts("その場所は置けません！");
		}
	}while(put_flug == 0);
}


int SearchReverse(int y, int x){//field[y][x]に置けるなら＊をいれる
	int dy = y;
	int dx = x;
	int put_flag = 0;
	bool put_jadge = 0;

	if(field[y][x] == 0 || field[y][x] == 3){
		field[y][x] = 0;
		for(int i = -1; i < 2; i++){
			for(int j = -1; j < 2; j++){
				while(field[dy + i][dx + j] == 3 - player){	//敵駒をどこまで逆転できるか
					dy += i;
					dx += j;
					put_flag = 1;
				}
				if(field[dy + i][dx + j] == player && put_flag == 1){	//最後が自分の駒だったら
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
	puts("結果発表！！！");
	printf("黒: %d個\n白: %d個\n\n",black_score,white_score);
	if(black_score > white_score){
		puts("黒の勝ち！！");
	}else if(black_score < white_score){
		puts("白の勝ち！！");
	}else{
		puts("引き分け！");
	}
}

void Play(){

	InitializeField();
	int put_judge = 0;
	int end_jadge = 0;

	printf("---------オセロゲーム！----------\n\n");
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
			puts("どちらも置けないので集計します");
			WinnerJudge();
			break;
		}else{
			if(player == 1){
				puts("黒は置けなかったのでパスしました");
			}else{
				puts("白は置けなかったのでパスしました");
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