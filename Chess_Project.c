    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>
    #include <math.h>
    #include <time.h>

/// Function prototypes
    void game_execution (void); // Main function which runs the hot game
    void defining_board(void);  // No longer necessary please ignore
    void save_file(void);       // Main save file function which includes many functinos

    int black_king_check_for_surroundings(int Board[8][8]);
    int white_king_check_for_surroundings(int Board[8][8]);

    int white_checkmate_controller(void);
    int black_checkmate_controller(void);


    int is_valid_move_white(int TR, int TC, int IR, int IC, int z[8][8]);
    int is_valid_move_black(int TR, int TC, int IR, int IC, int z[8][8]);
    void print_board(int x[8][8]); //tahta basam fonksiyonu prototipi

    int horizontal_check_b( void );
    int vertical_check_b( void );
    int crosswise_check_b( void );

    int horizontal_check_w( void );
    int vertical_check_w( void );
    int crosswise_check_w( void );

    int stopwatch_of_white ( void ); // Countdowns for white, white gets disqualified if it ends
    int stopwatch_of_black ( void ); // Countdowns for black, black gets disqualified if it ends
    int row, column;
    void write_file(FILE* fptr,int board[row][column]); //Opens a .txt file and writes the current board matrix to it
    void read_file(int board_read[8][8]); //Reads previously saved games
    void list_games(void); //Lists previously saved games


    int IC = 0; //Baslangic kolonu
    int IR = 0; //Baslangic satiri
    int TC = 0; //Hedef kolon
    int TR = 0; //Hedef satir
    int a = 0; //siranin kimde oldugunu secen sayi
    int aa = 0;
    int choice = 0; //Ana menudeki secim
    int board[8][8];
    int previous_board1[8][8];
    int previous_board2[8][8];

/// Global variables.
    int iCounterForWhite = 40; //Beyazin kalan suresi (saniye)
    int iCounterForBlack = 40; //Siyahin kalan suresi (saniye)

    board[8][8] = {{-1,-2,-3,-4,-5,-3,-2,-1,},       /* Original chess board array. */
                       {-6,-6,-6,-6,-6,-6,-6,-6,},
                        {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                        {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                        {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                        {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                        {6, 6, 6, 6, 6, 6 ,6, 6,},
                        {1 ,2, 3, 4, 5, 3 ,2, 1}};


    previous_board1[8][8] =    {{-1,-2,-3,-4,-5,-3,-2,-1,}, /*Chess board array synchronized with the original board. */
                                {-6,-6,-6,-6,-6,-6,-6,-6,},
                                {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                                {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                                {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                                {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                                {6, 6, 6, 6, 6, 6 ,6, 6,},
                                {1 ,2, 3, 4, 5, 3 ,2, 1}};

    previous_board2[8][8] =     {{-1,-2,-3,-4,-5,-3,-2,-1,}, /*Previous chess board array before an execution of a move. */
                                {-6,-6,-6,-6,-6,-6,-6,-6,},
                                {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                                {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                                {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                                {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,},
                                {6, 6, 6, 6, 6, 6 ,6, 6,},
                                {1 ,2, 3, 4, 5, 3 ,2, 1}};

        int main(){

        system("chcp 65001");

        while(!(aa == 's')){

        system("cls"); //cleans the console

        printf("1.Start New Game\n");
        printf("2.Load Game\n");
        printf("3. Exit Game\n");

        scanf("%d", &choice);
        system("cls");

        if(choice==1){

            game_execution();
        }
        else if(choice==2){

                printf("Please Enter The Name Of Game You Want To Continue.\n\n");

                list_games();
                int new_board[8][8] = {0};
                read_file(new_board);

                int i,j;
                for(i=0; i<8; i++){
                    for(j=0; j<8; j++){

                        board[i][j] = new_board[i][j];
                        previous_board1[i][j] = new_board[i][j];
                        previous_board2[i][j] = new_board[i][j];
                    }
                    j=0;
                }

                game_execution();

        }
        else if(choice==3){
            return 0;
        }
        else{
           printf("invalid entry");
        }

    }

    return 0;
}




/// FUNCTION DEFINITIONS

//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////



/// Main game function
void game_execution(void){

        aa = 0;

            printf("WELCOME TO CHESS GAME!!!\n\n\n");
            printf("PRESS 's' TO SAVE GAME ANYTIME DURING GAME\n\n");
            printf("PRESS 'm' TO SAVE GAME AND EXIT TO MAIN MANU ANYTIME DURING GAME\n\n");
            printf("PRESS ENTER TO START\n\n\n\n");

            getchar();
            getchar();

            //Her hamle sonrasý tahta baþtan tahta çizme fonksiyonu
            while(1){



        //beyazin sirasiysa
        while(a%2 == 0){

        system("cls");

        //tahta basma fonksiyonu
        print_board(board);

        stopwatch_of_white();

        if(iCounterForWhite==0)break;

        aa = getch();

        //If user types 's' during countdown the game gets saved and returns 0 to main function
        if (aa == 's'){

        save_file();

        return 0;

        }

        //If user types 'm' during countdown game gets saved and navigates user to main menu
        else if(aa == 'm'){

            save_file();
            break;

        }


        //Kullanicidan hamle bilgilerinin alinmasi
        printf("Enter your move:\n");

        scanf("%d%d%d%d", &IR, &IC, &TR, &TC);

        //Eger gecerli hamle girilmisse
        if(is_valid_move_white(TR, TC, IR, IC, board)){

            switch(board[IR][IC])

            {
            //oynanacak tas kale ise
            case 1:

                board[TR][TC] = 1;
                board[IR][IC] = 0;
                a += 1;
                break;

            //oynanacak tas at ise
            case 2:

                board[TR][TC] = 2;
                board[IR][IC] = 0;
                a += 1;
                break;

            //oynanacak tas fil ise
            case 3:

                board[TR][TC] = 3;
                board[IR][IC] = 0;
                a += 1;
                break;

            //oynanacak tas vezir ise
            case 4:

                board[TR][TC] = 4;
                board[IR][IC] = 0;
                a += 1;
                break;

            //oynanacak tas kral ise
            case 5:

                board[TR][TC] = 5;
                board[IR][IC] = 0;
                a += 1;
                break;

            //oynanacak tas piyon ise
            case 6:

                board[TR][TC] = 6;
                board[IR][IC] = 0;
                a += 1;
                break;
            default:
                break;
            }

        }else {

            printf("invalid move!");
            sleep(1);
        }
/* Variables for constructing the loop. */
        int p;
        int t;

        for (p = 0; p <= 7; p++){                                             /* Updating the one move delayed board in order to redo a move if necessary.*/
            for (t = 0; t <= 7; t++){
                previous_board2[p][t] = previous_board1[p][t];
                previous_board1[p][t] = board[p][t];
        }
    }

        if (!white_king_check_for_surroundings(board)){                       /* Checking if the King is still being checked after a move is played. */
            printf("Invalid move, white king is still in check !!!\n\n");     /* If not, then the move is not valid. */
            sleep(3);
            int i, j;                                                         /* Variables for constructing the loop. */
            for (i= 0; i <= 7; i++){
                for (j = 0; j <= 7; j++){
                    board[i][j] = previous_board2[i][j];                     /* If the move is not valid, undo the move by synchronizing with previous board. */
                    previous_board1[i][j] = previous_board2[i][j];

                }

                j=0;
            }

            a = 2;                                                            /* White's turn again in order to submit a valid function. */
        }

        if (!black_checkmate_controller()){                                   /* Announce checkmate if necessary. */
            printf("Checkmate\n\n");
        }









    }

        if(iCounterForWhite==0){
            sleep(4);
            break;
        }

        if(aa == 'm')break;

        system("cls");


        //siyahin sirasiysa
        while (a%2 == 1){

        system("cls");

        //tahta basma fonksiyonu
        print_board(board);

        stopwatch_of_black();

        if(iCounterForBlack==0)break;

        aa = getch();


        //If user types 's' during countdown the game gets saved and returns 0 to main function
        if (aa == 's'){

        save_file();

        return 0;

        }

        //If user types 'm' during countdown game gets saved and navigates user to main menu
        else if(aa == 'm'){

            save_file();
            break;

        }

        //Kullanicidan hamle bilgilerinin alinmasi
        printf("Enter your move:\n");

        scanf("%d%d%d%d", &IR, &IC, &TR, &TC);

        //Eger gecerli hamle girilmisse
        if(is_valid_move_black(TR, TC, IR, IC, board)){

            switch(board[IR][IC])

            {

            //oynanacak tas kale ise
            case -1:

                board[TR][TC] = -1;
                board[IR][IC] = 0;
                a += 1;
                break;

            //oynanacak tas at ise
            case -2:

                board[TR][TC] = -2;
                board[IR][IC] = 0;
                a += 1;
                break;
            case -3:

                board[TR][TC] = -3;
                board[IR][IC] = 0;
                a += 1;
                break;

            //oynanacak tas kral ise
            case -4:

                board[TR][TC] = -4;
                board[IR][IC] = 0;
                a += 1;
                break;

            //oynanacak tas sah ise
            case -5:

                board[TR][TC] = -5;
                board[IR][IC] = 0;
                a += 1;
                break;

            //oynanacak tas piyon ise
            case -6:

                board[TR][TC] = -6;
                board[IR][IC] = 0;


                a += 1;
                break;


            default:
                break;
            }

        }else {

            printf("invalid move!");
            sleep(1);
        }
/* Variables for constructing the loop. */
        int p;
        int t;

        for (p = 0; p <= 7; p++){                                             /* Updating the one move delayed board in order to redo a move if necessary.*/
            for (t = 0; t <= 7; t++){
                previous_board2[p][t] = previous_board1[p][t];
                previous_board1[p][t] = board[p][t];
        }
    }



        if (!black_king_check_for_surroundings(board)){                        /* Checking if the King is still being checked after a move is played. */
            printf("Invalid move, black king is still in check !!!\n\n");      /* If not, then the move is not valid. */
            sleep(3);
            int i, j;                                                           /* Variables for constructing the loop. */
            for (i= 0; i <= 7; i++){
                for (j = 0; j <= 7; j++){
                    board[i][j] = previous_board2[i][j];                       /* If the move is not valid, undo the move by synchronizing with previous board. */
                    previous_board1[i][j] = previous_board2[i][j];

                }
            j=0;

            }


            a = 3;                                                              /* Black's turn again in order to submit a valid function. */
        }
        if (!white_checkmate_controller()){
            printf("Checkmate\n\n");                                            /* Announce checkmate if necessary. */
        }

    }



        if(iCounterForBlack == 0){
            sleep(4);
            break;
        }


        system("cls");

    }


}



//tahta basma fonksiyonu

void print_board(int x[8][8]){

                printf(" \t");

            for (int i=0; i<8;i++)

            printf(" %d ",i);
            printf("\n\n");

            for (int row = 0,p=0;row<8;row++,p++)
            {
                printf(" %d\t",p);
                for (int col = 0;col<8;col++)
                {
                    switch (x[row][col])
                    {

                        case 0:
                            printf(" \u2610 ");
                            break;
                        case -1:
                            printf(" \u2656 ");
                            break;
                        case -2:
                            printf(" \u2658 ");
                            break;
                        case -3:
                            printf(" \u2657 ");
                            break;
                        case -4:
                            printf(" \u2655 ");
                            break;
                        case -5:
                            printf(" \u2654 ");
                            break;
                        case -6:
                            printf(" \u2659 ");
                            break;
                        case 1:
                            printf(" \u265c ");
                            break;
                        case 2:
                            printf(" \u265e ");
                            break;
                        case 3:
                            printf(" \u265d ");
                            break;
                        case 4:
                            printf(" \u265b ");
                            break;
                        case 5:
                            printf(" \u265a ");
                            break;
                        case 6:
                            printf(" \u2659 ");
                            break;
                        default:
                            break;
                    }
                }
                printf("\n");
            }
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//beyazin yapmak istedigi hamlenin gecerlilik kontrolu

int is_valid_move_white(int TR, int TC, int IR, int IC, int z[8][8]){
        //Hedef kare ve baslangic karesinin tahtada olup olmadigi kontrolu
        if(TR <= 7 && TC <= 7 && IR <= 7 && IC <= 7 && TR >= 0 && TC >= 0 && IR >= 0 && IC >= 0){

            //Piyon icin fonksiyon
            if (z[IR][IC] == 6){

                //Eger baslangictaysa
                if (IR == 6){

                    //Eger hedef kare bossa ve menzildeyse
                    if (((TR - IR) < 0 && (TR-IR) >= -2) && ( TR < IR ) && z [TR][TC] == 0 && (IC == TC)){

                            //Eger 2 birimlik hamle yapilmissa ama hemen ondeki kare doluysa
                            if((TR-IR) == -2 && z[TR+1][TC] != 0){


                                return 0;

                            }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //Eger hedef kare bos degilse ve hedef kare komsu capraz karelerden biriyse ve hedef karedeki tas diger oyuncuya aitse
                    else if ((TR-IR == -1) && (z[TR][TC]) < 0 && (abs(TC-IC) == 1)){

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //Baslangictaysa ve gerekli kosullar saglanmamissa
                    else{


                        return 0;

                    }
                }

                //Baslangicta degilse ve hedef kare bossa ve menzildeyse
                else if (((TR-IR) == -1) && z [TR][TC] == 0 && (IC == TC)){

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                //Baslangicta degilse ve hedef kare bos degilse ve menzildeyse
                else if ((TR-IR == -1) && z[TR][TC] < 0 && ((abs(TC-IC) == 1))){

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                else{

                        return 0;

                    }
        }

            //Kral icin fonksiyon
            else if (z[IR][IC] == 5){



                    //Mevcut kare hedef kare secilmisse
                    if(abs(TR-IR) == 0 && abs(TC-IC) == 0){


                        return 0;

                    }

                    //Hedef kare menzildeyse dost bulunmuyorsa
                    else if(z[TR][TC] <= 0 && abs(TR-IR) <= 1 && abs(TC-IC) <= 1){

                        //Hamlenin uygulanmasi
                        return 1;

                    }
                    /* Castling King side */
                    else if (z[7][5] == 0 && z[7][6] == 0 && z[7][7] == 1){
                        z[7][7] = 0;
                        z[7][5] = 1;
                        return 1;
                    }
                    /* Castling Queen side */
                    else if (z[7][3] == 0 && z[7][2] == 0 && z[7][1] == 0 && z[7][0] == 1){
                        z[7][0] = 0;
                        z[7][3] = 1;
                        return 1;
                    }


                //Kral hareketi icin gerekli kosullar saglanmamissa
                else{


                return 0;

                }

        }

            //Vezir icin fonksiyon
            else if (z[IR][IC] == 4){

                //Yatay hareket
                //Hedef karede dost olup olmadigi kontrolu ve hareketin yatay olup olmadigi kontrolu
                if(z[TR][TC] <= 0 && TR == IR && TC != IC){

                    //Saga dogru hareket

                    if(TC>IC){

                        //Hedef kareye kadarki yolun temizligi kontrolu
                        for(int q = IC + 1; q < TC; q++){

                            if(z[IR][q] != 0){


                                return 0;


                            }

                        }

                        //Sah cekme kontrol
                        if (crosswise_check_b() == 0 || vertical_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }


                        //Hamlenin uygulanmasi
                        return 1;


                    }

                    //Sola dogru hareket
                    else if(TC<IC){

                        //Hedef kareye kadarki yolun temizligi kontrolu
                        for(int m = IC - 1; m > TC; m--){

                            if(z[IR][m] != 0){


                                return 0;

                            }

                        }

                        /* Check control */
                        if (crosswise_check_b() == 0 || vertical_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }


                        //Hamlenin uygulanmasi
                        return 1;



                    }

                }

                //Dikey hareket
                //Hedef karede dost olup olmadigi kontrolu  ve hareketin dikey olup olmadigi kontrolu
                else if(z[TR][TC] <= 0 && TC == IC && TR != IR){


                    //Asagi dogru hareket
                    if(TR>IR){

                        //Hedef kareye kadarki yolun temizligi kontrolu
                        for(int t = IR + 1; t < TR; t++){

                            if(z[t][IC] != 0){


                                return 0;

                            }

                        }

                         /* Check control */
                        if (crosswise_check_b() == 0 || horizontal_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }


                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //Yukari dogru hareket
                    else if(TR<IR){

                        //Hedef kareye kadarki yolun temizligi kontrolu
                        for(int y = IR - 1; y > TR; y--){

                            if(z[y][IC] != 0){


                                return 0;

                            }

                        }

                         /* Check control */
                        if (crosswise_check_b() == 0 || horizontal_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }


                        //Hamlenin uygulanmasi
                        return 1;

                    }

                }

                //Hedef karede dost olup olmadigi kontrolu  ve hareketin capraz olup olmadigi kontrolu
                else if(z[TR][TC] <= 0 && TC != IC && TR != IR && (abs(TR-IR) == abs(TC-IC))){


                    //hareket sag yukari capraz ise
                    if (TC>IC && TR<IR){

                        int u;
                        int r;

                        for(r = IR - 1, u = IC +1; r > TR, u < TC; r--, u++){

                            if(z[r][u] != 0){


                                return 0;

                            }

                        }

                         /* Check control */
                        if (crosswise_check_b() == 0 || /*vertical_check_w() == 0 ||*/ horizontal_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //hareket sol yukari capraz ise
                    else if (TR<IR && TC<IC) {

                        int u;
                        int r;

                        for(r = IR - 1, u = IC - 1; r > TR, u > TC; r--, u--){

                            if(z[r][u] != 0){


                                return 0;

                            }

                        }

                        /* Check control */
                        if (crosswise_check_b() == 0 || vertical_check_b() == 0 || horizontal_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }


                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //hareket sol asagi capraz ise
                    else if (TC<IC && TR>IR) {

                        int u;
                        int r;

                        for(r = IR + 1, u = IC - 1; r < TR, u > TC; r++, u--){

                            if(z[r][u] != 0){


                                return 0;

                            }

                        }

                         /* Check control */
                        if (crosswise_check_b() == 0 || vertical_check_b() == 0 || horizontal_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //hareket sag asagi capraz ise
                    else if (TR>IR && TC>IC) {

                        int u;
                        int r;

                        for(r = IR + 1, u = IC + 1; r < TR, u < TC; r++, u++){

                            if(z[r][u] != 0){


                                return 0;

                            }

                        }

                         /* Check control */
                        if (crosswise_check_b() == 0 || vertical_check_b() == 0 || horizontal_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }


                        //Hamlenin uygulanmasi
                        return 1;

                    }

                }

                //Hareket icin kosullar saglanmamissa
                else {


                    return 0;


                    }

        }

            //Fil icin fonksiyon
            else if (z[IR][IC] == 3){

                    //Hedef karede dost olup olmadigi kontrolu  ve hareketin capraz olup olmadigi kontrolu
                    if(z[TR][TC] <= 0 && TC != IC && TR != IR && (abs(TR-IR) == abs(TC-IC))){


                    //hareket sag yukari capraz ise
                    if (TC>IC && TR<IR){

                        int u;
                        int r;

                        for(r = IR - 1, u = IC +1; r > TR, u < TC; r--, u++){

                            if(z[r][u] != 0){


                                return 0;

                            }

                        }

                         /* Check control */
                        if (crosswise_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //hareket sol yukari capraz ise
                    else if (TR<IR && TC<IC) {

                        int u;
                        int r;

                        for(r = IR - 1, u = IC - 1; r > TR, u > TC; r--, u--){

                            if(z[r][u] != 0){


                                return 0;

                            }

                        }

                         /* Check control */
                        if (crosswise_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //hareket sol asagi capraz ise
                    else if (TC<IC && TR>IR) {

                        int u;
                        int r;

                        for(r = IR + 1, u = IC - 1; r < TR, u > TC; r++, u--){

                            if(z[r][u] != 0){


                                return 0;

                            }

                        }

                        /* Check control */
                        if (crosswise_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //hareket sag asagi capraz ise
                    else if (TR>IR && TC>IC) {

                        int u;
                        int r;

                        for(r = IR + 1, u = IC + 1; r < TR, u < TC; r++, u++){

                            if(z[r][u] != 0){


                                return 0;

                            }

                        }

                        /* Check control */
                        if (crosswise_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                }

                else {


                    return 0;

                }

        }

            //At icin fonksiyon
            else if (z[IR][IC] == 2){

                //hedef karenin atin menzilindeki 4 kareden biri olup olmaigi kontrolu
                if (z[TR][TC] <=0 && (((abs(TR-IR) == 1) && (abs(TC-IC) == 2)) || ((abs(TR-IR) == 2) && (abs(TC-IC) == 1)))){

                    return 1;

                }

                else{


                    return 0;

                }



        }

            //Kale icin fonksiyon
            else if (z[IR][IC] == 1){

                //Yatay hareket
                //Hedef karede dost olup olmadigi kontrolu ve hareketin yatay olup olmadigi kontrolu
                if(z[TR][TC] <= 0 && TR == IR && TC != IC){

                    //Saga dogru hareket
                    if(TC>IC){

                        //Hedef kareye kadarki yolun temizligi kontrolu
                        for(int q = IC + 1; q < TC; q++){

                            if(z[IR][q] != 0){


                                return 0;


                            }

                        }

                         /* Check control */
                        if (vertical_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //Sola dogru hareket
                    else if(TC<IC){

                        //Hedef kareye kadarki yolun temizligi kontrolu
                        for(int m = IC - 1; m > TC; m--){

                            if(z[IR][m] != 0){


                                return 0;

                            }

                        }

                         /* Check control */
                        if (vertical_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                }

                //Dikey hareket
                //Hedef karede dost olup olmadigi kontrolu ve hareketin dikey olup olmadigi kontrolu
                else if(z[TR][TC] <= 0 && TC == IC && TR != IR){

                    //Asagi dogru hareket
                    if(TR>IR){

                        //Hedef kareye kadarki yolun temizligi kontrolu
                        for(int t = IR + 1; t < TR; t++){

                            if(z[t][IC] != 0){


                                return 0;

                            }

                        }

                         /* Check control */
                        if (horizontal_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //Yukari dogru hareket
                    else if(TR<IR){

                        //Hedef kareye kadarki yolun temizligi kontrolu
                        for(int y = IR - 1; y > TR; y--){

                            if(z[y][IC] != 0){


                                return 0;

                            }

                        }

                        /* Check control */
                        if (horizontal_check_b() == 0){
                            printf("\nBlack King is in check !!\n");
                            sleep(3);
                        }


                        //Hamlenin uygulanmasi
                        return 1;

                    }

                }

                //Hareket icin kosullar saglanmamissa
                else {


                    return 0;


                    }

            }

            //secilen tas beyaz degilse
            else{

                return 0;
            }

        }

        //Hedef kare ve baslangic karesi tahtada degilse
        else {


            return 0;

        }

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int is_valid_move_black(int TR, int TC, int IR, int IC, int z[8][8]){






        //Hedef karenin tahtada olup olmadigi kontrolu
        if(TR <= 7 && TC <= 7 && IR <= 7 && IC <= 7 && TR >= 0 && TC >= 0 && IR >= 0 && IC >= 0){






                //Piyon icin fonksiyon
                if (z[IR][IC] == -6){





                //Eger baslangictaysa
                        if (IR == 1){


                    //Eger hedef kare bossa ve menzildeyse
                            if (((TR - IR) > 0 && (TR-IR) <= 2) && ( TR > IR ) && z [TR][TC] == 0 && (IC == TC)){

                         //Eger 2 birimlik hamle yapýlmýssa ama hemen ondeki kare doluysa
                                    if((TR-IR) == 2 && z[TR-1][TC] != 0){


                                        return 0;

                                    }

                            //Hamlenin uygulanmasi



                                return 1;



                            }

                        //Eger hedef kare bos degilse ve hedef kare komsu capraz karelerden biriyse ve hedef karedeki tas diger oyuncuya aitse
                            else if ((TR-IR == 1) && (z[TR][TC]) > 0 && (abs(TC-IC) == 1)){


                            //Hamlenin uygulanmasi
                                return 1;




                            }

                        //Baslangictaysa ve gerekli kosullar saglanmamissa
                            else{


                                return 0;

                            }

                        }


                    //Baslangicta degilse ve hedef kare bossa ve menzildeyse
                        else if (((TR-IR) == 1) && z [TR][TC] == 0 && (IC == TC)){

                             //Hamlenin uygulanmasi
                                return 1;

                        }
                    //Baslangicta degilse ve hedef kare bos degilse ve menzildeyse
                        else if ((TR-IR == 1) && z[TR][TC] > 0 && ((abs(TC-IC) == 1))){

                            //Hamlenin uygulanmasi
                                return 1;

                        }


                        //Baslangicta degilse ve gerekli kosullar saglanmamissa
                        else{


                                return 0;
                        }




            }



            //Kral icin fonksiyon
            else if (z[IR][IC] == -5){



                    //Mevcut kare hedef kare secilmisse
                    if(abs(TR-IR) == 0 && abs(TC-IC) == 0){


                        return 0;
                    }

                    //Hedef kare menzildeyse
                    else if(z[TR][TC] >= 0 && abs(TR-IR) <= 1 && abs(TC-IC) <= 1){

                            return 1;

                    }
                    /* Castling King side */
                    else if (z[0][5] == 0 && z[0][6] == 0 && z[0][7] == -1){
                        z[0][7] = 0;
                        z[0][5] = -1;
                        return 1;
                    }
                    /* Castling Queen side */
                    else if (z[0][3] == 0 && z[0][2] == 0 && z[0][1] == 0 && z[0][0] == -1){
                        z[0][0] = 0;
                        z[0][3] = -1;
                        return 1;
                    }





        }

            //Vezir icin fonksiyon
            else if (z[IR][IC] == -4){

                //Yatay hareket
                //Hedef karede dost olup olmadigi kontrolu ve hareketin yatay olup olmadigi kontrolu
                if(z[TR][TC] >= 0 && TR == IR && TC != IR){

                    //Saga dogru hareket
                    if(TC>IC){

                        //Yolda engel olup olmadigi kontrolu
                        for(int q = IC + 1; q < TC; q++){

                            if(z[IR][q] != 0){


                                return 0;
                            }

                        }

                            /* Check control */
                           if (crosswise_check_w() == 0 || vertical_check_w() == 0){
                               printf("\nWhite King is in check !!\n");
                               sleep(3);
                            }


                            //Hamlenin uygulanmasi
                            return 1;


                    }

                    //Sola dogru hareket
                    if(TC<IC){

                        //Yolda engel olup olmadigi kontrolu
                        for(int m = IC - 1; m > TC; m--){

                            if(z[IR][m] != 0){


                                return 0;
                            }

                        }

                             /* Check control */
                           if (crosswise_check_w() == 0 || vertical_check_w() == 0){
                                printf("\nWhite King is in check !!\n");
                                sleep(3);
                           }

                            //Hamlenin uygulanmasi
                            return 1;

                    }
                }

                //Dikey hareket
                //Hedef karede dost olup olmadigi kontrolu  ve hareketin dikey olup olmadigi kontrolu
                else if(z[TR][TC] >= 0 && TC == IC && TR != IR){

                    //Yukari dogru hareket
                    if(TR>IR){

                        //Yolda engel olup olmadigi kontrolu
                        for(int t = IR + 1; t < TR; t++){

                            if(z[t][IC] != 0){


                                return 0;
                            }

                        }

                             /* Check control */
                            if (crosswise_check_w() == 0 || horizontal_check_w() == 0){
                                printf("\nWhite King is in check !!\n");
                                sleep(3);
                            }

                            //Hamlenin uygulanmasi
                            return 1;

                    }

                    //Asagi dogru hareket
                    else if(TR<IR){

                        //Yolda engel olup olmadigi kontrolu
                        for(int y = IR - 1; y > TR; y--){

                            if(z[y][IC] != 0){


                                return 0;
                            }

                        }

                             /* Check control */
                            if (crosswise_check_w() == 0 || horizontal_check_w() == 0){
                                printf("\nWhite King is in check !!\n");
                                sleep(3);
                            }

                            //Hamlenin uygulanmasi
                            return 1;


                    }

                }

                //Hedef karede dost olup olmadigi kontrolu  ve hareketin capraz olup olmadigi kontrolu
                else if(z[TR][TC] >= 0 && TC != IC && TR != IR && (abs(TR-IR) == abs(TC-IC))){


                    //hareket sag yukari capraz ise
                    if (TC>IC && TR<IR){

                        int u;
                        int r;

                        for(r = IR - 1, u = IC +1; r > TR, u < TC; r--, u++){

                            if(z[r][u] != 0){


                                return 0;
                            }

                        }

                         /* Check control */
                            if (crosswise_check_w() == 0 || horizontal_check_w() == 0 || vertical_check_w() == 0){
                                printf("\nWhite King is in check !!\n");
                                sleep(3);
                            }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //hareket sol yukari capraz ise
                    else if (TR<IR && TC<IC) {

                        int u;
                        int r;

                        for(r = IR - 1, u = IC - 1; r > TR, u > TC; r--, u--){

                            if(z[r][u] != 0){


                                return 0;
                            }

                        }
                         /* Check control */
                        if (crosswise_check_w() == 0 || horizontal_check_w() == 0 || vertical_check_w() == 0){
                            printf("\nWhite King is in check !!\n");
                            sleep(3);
                        }
                        //Hamlenin uygulanmasi
                        return 1;


                    }

                    //hareket sol asagi capraz ise
                    else if (TC<IC && TR>IR) {

                        int u;
                        int r;

                        for(r = IR + 1, u = IC - 1; r < TR, u > TC; r++, u--){

                            if(z[r][u] != 0){


                                return 0;
                            }

                        }
                         /* Check control */
                        if (crosswise_check_w() == 0 || horizontal_check_w() == 0 || vertical_check_w() == 0){

                            printf("\nWhite King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;



                    }

                    //hareket sag asagi capraz ise
                    else if (TR>IR && TC>IC) {

                        int u;
                        int r;

                        for(r = IR + 1, u = IC + 1; r < TR, u < TC; r++, u++){

                            if(z[r][u] != 0){


                                return 0;
                            }

                        }

                        if (crosswise_check_w() == 0 || horizontal_check_w() == 0 || vertical_check_w() == 0){
                            printf("\nWhite King is in check !!\n");
                            sleep(3);
                       }

                        //Hamlenin uygulanmasi
                        return 1;



                    }

                }

                //Hareket icin kosullar saglanmamissa
                else{


            return 0;

                }


        }

            //Fil icin fonksiyon
            else if (z[IR][IC] == -3){

                    //Hedef karede dost olup olmadigi kontrolu  ve hareketin capraz olup olmadigi kontrolu
                    if(z[TR][TC] >= 0 && TC != IC && TR != IR && (abs(TR-IR) == abs(TC-IC))){


                    //hareket sag yukari capraz ise
                    if (TC>IC && TR<IR){

                        int u;
                        int r;

                        for(r = IR - 1, u = IC +1; r > TR, u < TC; r--, u++){

                            if(z[r][u] != 0){


                                return 0;
                            }

                        }
                         /* Check control */
                        if (crosswise_check_w() == 0 || horizontal_check_w() == 0 || vertical_check_w() == 0){
                            printf("\nWhite King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //hareket sol yukari capraz ise
                    else if (TR<IR && TC<IC) {

                        int u;
                        int r;

                        for(r = IR - 1, u = IC - 1; r > TR, u > TC; r--, u--){

                            if(z[r][u] != 0){


                                return 0;
                            }

                        }
                         /* Check control */
                        if (crosswise_check_w() == 0 || horizontal_check_w() == 0 || vertical_check_w() == 0){
                            printf("\nWhite King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;


                    }

                    //hareket sol asagi capraz ise
                    else if (TC<IC && TR>IR) {

                        int u;
                        int r;

                        for(r = IR + 1, u = IC - 1; r < TR, u > TC; r++, u--){

                            if(z[r][u] != 0){


                                return 0;
                            }

                        }
                         /* Check control */
                        if (crosswise_check_w() == 0 || horizontal_check_w() == 0 || vertical_check_w() == 0){
                            printf("\nWhite King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;

                    }

                    //hareket sag asagi capraz ise
                    else if (TR>IR && TC>IC) {

                        int u;
                        int r;

                        for(r = IR + 1, u = IC + 1; r < TR, u < TC; r++, u++){

                            if(z[r][u] != 0){


                                return 0;
                            }

                        }
                         /* Check control */
                        if (crosswise_check_w() == 0 || horizontal_check_w() == 0 || vertical_check_w() == 0){
                            printf("\nWhite King is in check !!\n");
                            sleep(3);
                        }

                        //Hamlenin uygulanmasi
                        return 1;


                    }

                }

                else {


                    return 0;
                }


        }

            //At icin fonksiyon
            else if (z[IR][IC] == -2){

                //hedef karenin atin menzilindeki 4 kareden biri olup olmaigi kontrolu
                if (z[TR][TC] >=0 && (((abs(TR-IR) == 1) && (abs(TC-IC) == 2)) || ((abs(TR-IR) == 2) && (abs(TC-IC) == 1)))){

                        return 1;
                }

                else{


                    return 0;
                }

        }

            //Kale icin fonksiyon
            else if (z[IR][IC] == -1){

                //Yatay hareket
                //Hedef karede dost olup olmadigi kontrolu ve hareketin yatay olup olmadigi kontrolu
                if(z[TR][TC] >= 0 && TR == IR){

                    //Saga dogru hareket
                    if(TC>IC){

                        //Yolda engel olup olmadigi kontrolu
                        for(int q = IC + 1; q < TC; z++){

                            if(z[IR][q] != 0){


                                return 0;
                            }

                        }

                         /* Check control */
                        if (vertical_check_w() == 0){
                            printf("\nWhite King is in check !!\n");
                            sleep(3);
                        }

                            //Hamlenin uygulanmasi
                            return 1;
                    }

                    //Sola dogru hareket
                    if(TC<IC){

                        //Yolda engel olup olmadigi kontrolu
                        for(int m = IC - 1; m > TC; m--){

                            if(z[IR][m] != 0){


                                return 0;
                            }

                        }
                         /* Check control */
                        if (vertical_check_w() == 0){
                            printf("\nWhite King is in check !!\n");
                            sleep(3);
                        }


                            //Hamlenin uygulanmasý
                            return 1;
                    }
                }

                //Dikey hareket
                //Hedef karede dost olup olmadigi kontrolu  ve hareketin dikey olup olmadigi kontrolu
                else if(z[TR][TC] <= 0 && TC == IC){

                    //Yukari dogru hareket
                    if(TR>IR){

                        //Yolda engel olup olmadigi kontrolu
                        for(int t = IR + 1; t < TR; t++){

                            if(z[t][IC] != 0){


                                return 0;
                            }

                        }
                         /* Check control */
                        if (horizontal_check_w() == 0){
                            printf("\nWhite King is in check !!\n");
                            sleep(3);
                        }


                            //Hamlenin uygulanmasi
                            return 1;



                    }

                    //Asagi dogru hareket
                    else if(TR<IR){

                        //Yolda engel olup olmadigi kontrolu
                        for(int y = IR - 1; y > TR; y--){

                            if(z[y][IC] != 0){


                                return 0;
                            }

                        }
                         /* Check control */
                        if (horizontal_check_w() == 0){
                            printf("\nWhite King is in check !!\n");
                            sleep(3);
                        }

                            //Hamlenin uygulanmasi
                            return 1;


                    }

                }

                //Hareket icin kosullar saglanmamissa
                else{


            return 0;

                }

        }

        //secilen tas siyah degilse
        else{

            return 0;
        }



    }

        //Hedef kare ve baslangic karesi tahtada degilse
        else {


            return 0;

            }

    }
 /// Check functions for black king
int vertical_check_b( void ){ /* Scanning the squares vertically. */
    /* Loop variables */
    int h;
    int k;

    /* Scanning through vertically upwards. */
    for (h = TR - 1; h >= 0; h--){
        if (board[h][TC] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][TC] != 0 && board[h][TC] != -5)   /* If there is piece on the way other than black king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    /* Scanning through vertically downwards. */
    for (h = TR + 1; h <= 7; h++){
        if (board[h][TC] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][TC] != 0 && board[h][TC] != -5)   /* If there is piece on the way other than black king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    return 1; /* If none of the loops returned 0, there is no check */
}


int horizontal_check_b( void ){ /* Scanning the squares horizontally. */
    /* Loop variables. */
    int h;
    int k;
    // Checking horizontally leftwards.
    for (k = TC - 1; k >= 0; k--){
        if (board[TR][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[TR][k] != 0 && board[TR][k] != -5)   /* If there is piece on the way other than black king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;;
    }

    // Checking horizontally rightwards.
    for (k = TC + 1; k <= 7; k++){
        if (board[TR][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[TR][k] != 0 && board[TR][k] != -5)   /* If there is piece on the way other than black king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }
    return 1; /* If none of the loops returned 0, there is no check */
}


int crosswise_check_b( void ){ /* Scanning the squares diagonally. */
    /* Loop variables. */
    int h;
    int k;

    // Checking crosswise left-upwards
    for (h = TR - 1, k = TC - 1; h >= 0, k >= 0; h--, k--){
        if (board[h][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][k] != 0 && board[h][k] != -5)    /* If there is piece on the way other than black king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    // Checking crosswise right-upwards
    for (h = TR - 1, k = TC +1 ; h >= 0, k <= 7; h--, k++){
        if (board[h][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][k] != 0 && board[h][k] != -5)    /* If there is piece on the way other than black king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    // Checking crosswise left-downwards
    for (h = TR + 1, k = TC - 1; h <= 7, k >= 0; h++, k--){
        if (board[h][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][k] != 0 && board[h][k] != -5)    /* If there is piece on the way other than black king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    // Checking crosswise right-downwards
    for (h = TR + 1, k = TC + 1; h <= 7, k <= 7; h++, k++){
        if (board[h][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][k] != 0 && board[h][k] != -5)    /* If there is piece on the way other than black king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    return 1;  /* If none of the loops returned 0, there is no check */
}


/// Check functions for white king
int vertical_check_w( void ){ /* Scanning the squares vertically. */
    /* Loop variables */
    int h;
    int k;

    // Checking vertically upwards.
    for (h = TR - 1; h >= 0; h--){
        if (board[h][TC] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][TC] != 0 && board[h][TC] != 5)    /* If there is piece on the way other than white king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    // Checking vertically downwards.
    for (h = TR + 1; h <= 7; h++){
        if (board[h][TC] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][TC] != 0 && board[h][TC] != 5)    /* If there is piece on the way other than white king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    return 1;
}


int horizontal_check_w( void ){
    /* Loop variables */
    int h;
    int k;

    // Checking horizontally leftwards.
    for (k = TC - 1; k >= 0; k--){
        if (board[TR][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[TR][k] != 0 && board[TR][k] != 5)    /* If there is piece on the way other than white king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    // Checking horizontally rightwards.
    for (k = TC + 1; k <= 7; k++){
        if (board[TR][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[TR][k] != 0 && board[TR][k] != 5)    /* If there is piece on the way other than white king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    return 1;
}


int crosswise_check_w( void ){
    /* Loop variables */
    int h;
    int k;

    // Checking crosswise left-upwards
    for (h = TR - 1, k = TC - 1; h >= 0, k >= 0; h--, k--){
        if (board[h][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][k] != 0 && board[h][k] != 5)    /* If there is piece on the way other than white king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    // Checking crosswise right-upwards
    for (h = TR - 1, k = TC +1 ; h >= 0, k <= 7; h--, k++){
        if (board[h][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][k] != 0 && board[h][k] != 5)    /* If there is piece on the way other than white king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    // Checking crosswise left-downwards
    for (h = TR + 1, k = TC - 1; h <= 7, k >= 0; h++, k--){
        if (board[h][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][k] != 0 && board[h][k] != 5)    /* If there is piece on the way other than white king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    // Checking crosswise right-downwards
    for (h = TR + 1, k = TC + 1; h <= 7, k <= 7; h++, k++){
        if (board[h][k] == 0)                              /* If there are no pieces on the way, continue scanning. */
            continue;
        else if (board[h][k] != 0 && board[h][k] != 5)    /* If there is piece on the way other than white king, finish scanning. Meaning there is no check. */
            break;
        else                                                /* If you encounter with the king directly, announce check. */
            return 0;
    }

    return 1; /* If none of the loops returned 0, there is no check */
}




/// Function that analyzes whether the King is still in check or not.
int black_king_check_for_surroundings(int Board[8][8]){
/* Loop variables for scanning. */
    int h; // Equivalent row where king exists.
    int k; // Equivalent column where king exists.
    int m;
    int n;
/* Loop variables for tracking the King */
    int i, j;
    for (i = 0; i <= 7; i++){                /* Tracking the King's current coordinates on the board. */
        for (j = 0; j <= 7; j++){
            if (board[i][j] == -5){
                h = i;
                k = j;
            }
        }
    }







    // Scanning the right side of the King.
    for (n = k+1; n <= 7; n++){
        if ( Board[h][n] == 0)                              /* If there is no piece on the way, continue. */
            continue;
        else if (Board[h][n] < 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[h][n] == 4 || Board[h][n] == 1){    /* If there is Queen or Rook on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;

    }



    // Scanning the left side of the King.

    for ( n = k-1; n >= 0; n--){
        if ( Board[h][n] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[h][n] < 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[h][n] == 4 || Board[h][n] == 1){    /* If there is Queen or Rook on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;
        }



    // Scanning the bottom side of the King.
    for ( m = h+1; m <= 7; m++){
        if (Board[m][k] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[m][k] < 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[m][k] == 4 || Board[m][k] == 1){    /* If there is Queen or Rook on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;
        }


   // Scanning the up side of the King.

     for ( m = h-1; m >= 0; m--){
        if (Board[m][k] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[m][k] < 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[m][k] == 4 || Board[m][k] == 1){    /* If there is Queen or Rook on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;
        }


    // Scanning the diagonal sides of the King.

    for ( m = h+1, n = k-1; m <= 7, n >= 0; m++, n-- ){
        if (Board[m][n] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[m][n] < 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[m][n] == 4 || Board[m][n] == 3){    /* If there is Queen or Bishop on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;
        }

    // Scanning the diagonal sides of the King.

    for ( m = h-1, n = k-1; m >= 0 , n >= 0; m--, n-- ){
        if (Board[m][n] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[m][n] < 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[m][n] == 4 || Board[m][n] == 3){    /* If there is Queen or Bishop on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;
        }

    // Scanning the diagonal sides of the King.

    for ( m = h+1, n = k+1; m <= 7, n <= 7; m++, n++ ){
        if (Board[m][n] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[m][n] < 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[m][n] == 4 || Board[m][n] == 3){    /* If there is Queen or Bishop on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;
        }

    // Scanning the diagonal sides of the King.

    for ( m = h-1, n = k+1; m >= 0 , n <= 7; m--, n++ ){
        if (Board[m][n] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[m][n] < 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[m][n] == 4 || Board[m][n] == 3){    /* If there is Queen or Bishop on the way, it means the King is still being checked. */
            return 0;

        }
        else
            break;
        }
    return 1; /* The King is not in check if it doesn't return 0. */




    }
/// Function that analyzes whether the King is still in check or not.
int white_king_check_for_surroundings(int Board[8][8]){
/* Loop variables for scanning. */
    int h; // Equivalent row where king exists.
    int k; // Equivalent column where king exists.
    int m;
    int n;
/* Loop variables for tracking the King */
    int i, j;
    for (i = 0; i <= 7; i++){           /* Tracking the King's current coordinates on the board. */
        for (j = 0; j <= 7; j++){
            if (board[i][j] == 5){
                h = i;
                k = j;
            }
        }
    }






    // Scanning the right side of the King.
    for (n = k+1; n <= 7; n++){
        if ( Board[h][n] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[h][n] > 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[h][n] == -4 || Board[h][n] == -1){    /* If there is Queen or Rook on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;

    }



    // Scanning the left side of the King.

    for ( n = k-1; n >= 0; n--){
        if ( Board[h][n] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[h][n] > 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[h][n] == -4 || Board[h][n] == -1){    /* If there is Queen or Rook on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;
        }



    // Scanning the bottom side of the King.
    for ( m = h+1; m <= 7; m++){
        if (Board[m][k] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[m][k] > 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[m][k] == -4 || Board[m][k] == -1){    /* If there is Queen or Rook on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;
        }


    // Scanning the up side of the King.

     for ( m = h-1; m >= 0; m--){
        if (Board[m][k] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[m][k] > 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[m][k] == -4 || Board[m][k] == -1){    /* If there is Queen or Rook on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;
        }

/*
    // Scanning the diagonal sides of the King.

    for ( m = h+1, n = k-1; m <= 7, n >= 0; m++, n-- ){
        if (Board[m][n] == 0)                               // If there is no piece on the way, continue. //
            continue;
        else if (Board[m][n] > 0)                            // If there is an ally piece on the way, it prevents the King from check. //
            break;
        else if (Board[m][n] == -4 || Board[m][n] == -3){    // If there is Queen or Bishop on the way, it means the King is still being checked. //

            return 0;

        }
        else
            break;
        } */

   // Scanning the diagonal sides of the King.

    for ( m = h-1, n = k-1; m >= 0 , n >= 0; m--, n-- ){
        if (Board[m][n] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[m][n] > 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[m][n] == -4 || Board[m][n] == -3){    /* If there is Queen or Bishop on the way, it means the King is still being checked. */

            return 0;

        }
        else
            break;
        }
/*
    // Scanning the diagonal sides of the King.

    for ( m = h+1, n = k+1; m <= 7, n <= 7; m++, n++ ){
        if (Board[m][n] == 0)                               // If there is no piece on the way, continue. //
            continue;
        else if (Board[m][n] > 0)                            // If there is an ally piece on the way, it prevents the King from check. //
            break;
        else if (Board[m][n] == -4 || Board[m][n] == -3)
            return 0;

        else
            break;
        } */

    // Scanning the diagonal sides of the King.

    for ( m = h-1, n = k+1; m >= 0 , n <= 7; m--, n++ ){
        if (Board[m][n] == 0)                               /* If there is no piece on the way, continue. */
            continue;
        else if (Board[m][n] > 0)                            /* If there is an ally piece on the way, it prevents the King from check. */
            break;
        else if (Board[m][n] == -4 || Board[m][n] == -3){    /* If there is Queen or Bishop on the way, it means the King is still being checked. */
            return 0;

        }
        else
            break;
        }
        return 1; /* The King is not in check if it doesn't return 0. */






    }


/// Function that examines if there is a checkmate after every move.
int black_checkmate_controller(void){

    int i, j, m, n;                                            /* Variables that corresponds the upcoming random moves. */
    int check_counter = 1;                                     /* Counter of how many times the possible moves ended up with check. */
    int possible_move_counter = -1;                            /* Counter of all possible valid moves. */
    int fake_board[8][8] = {-1,-2,-3,-4,-5,-3,-2,-1,           /* A test board for executing possible moves. */
                       -6,-6,-6,-6,-6,-6,-6,-6,
                        0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                        0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                        0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                        0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                        6, 6, 6, 6, 6, 6 ,6, 6,
                        1 ,2, 3, 4, 5, 3 ,2, 1};




    /// Applying all possible combinations of moves to the board.
    for (i = 0; i <= 7; i++){
        for (j= 0; j <= 7; j++){
            for (m = 0; m <= 7; m++){
                for (n = 0; n <= 7; n++){

                        if (is_valid_move_black(i, j, m, n, fake_board)){          /* Filtering out the invalid moves. */
                                possible_move_counter = possible_move_counter + 1; /* Calculating the number of all possible valid moves. */





                                switch(fake_board[m][n])                           /* Executing the moves to the test board one by one. */

                                {
                                //If the piece is Rook.
                                case -1:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = -1;

                                    break;

                                //If the piece is Knight.
                                case -2:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = -2;

                                    break;

                                //If the piece is Bishop.
                                case -3:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = -3;

                                    break;

                               //If the piece is Queen.
                                case -4:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = -4;

                                    break;

                                //If the piece is King.
                                case -5:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = -5;

                                    break;

                                //If the piece is Pawn.
                                case -6:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = -6;

                                    break;

                                default:
                                    break;
                                }







                                if (!black_king_check_for_surroundings(fake_board)){      /* After executing a valid move, checking if the King is still being checked. */
                                    check_counter = check_counter + 1;                    /* Counting the number of moves including checks. */
                                }

                                int v, w;                                                 /* Synchronizing the test board to the original board in order to reuse next move. */
                                    for (v = 0; v <= 7; v++){
                                        for (w = 0; w <= 7; w++){
                                            fake_board[v][w] = board[v][w];
                                        }
                                    }






                        }




                }


            }


        }


    }

    if (check_counter != possible_move_counter){         /* If the number of all valid moves are equal to number of checks, it means King can not escape and it is checkmate. */

        return 1;
    }
    else {

        return 0; /* Checkmate */
    }


}

/// Function that examines if there is a checkmate after every move.
int white_checkmate_controller(void){

    int i, j, m, n;                                            /* Variables that corresponds the upcoming random moves. */
    int check_counter = 1;                                     /* Counter of how many times the possible moves ended up with check. */
    int possible_move_counter = -1;                            /* Counter of all possible valid moves. */
    int fake_board[8][8] = {-1,-2,-3,-4,-5,-3,-2,-1,           /* A test board for executing possible moves. */
                       -6,-6,-6,-6,-6,-6,-6,-6,
                        0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                        0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                        0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                        0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
                        6, 6, 6, 6, 6, 6 ,6, 6,
                        1 ,2, 3, 4, 5, 3 ,2, 1};




 /// Applying all possible combinations of moves to the board.
    for (i = 0; i <= 7; i++){
        for (j= 0; j <= 7; j++){
            for (m = 0; m <= 7; m++){
                for (n = 0; n <= 7; n++){

                        if (is_valid_move_white(i, j, m, n, fake_board)){          /* Filtering out the invalid moves. */
                                possible_move_counter = possible_move_counter + 1; /* Calculating the number of all possible valid moves. */






                                switch(fake_board[m][n])                           /* Executing the moves to the test board one by one. */

                                {
                                //If the piece is Rook.
                                case 1:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = 1;

                                    break;

                                //If the piece is Knight.
                                case 2:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = 2;

                                    break;

                               //If the piece is Bishop.
                                case 3:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = 3;

                                    break;

                                //If the piece is Queen.
                                case 4:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = 4;

                                    break;

                                //If the piece is King.
                                case 5:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = 5;

                                    break;

                                //If the piece is Pawn.
                                case 6:

                                    fake_board[m][n] = 0;
                                    fake_board[i][j] = 6;

                                    break;

                                default:
                                    break;
                                }







                                if (!white_king_check_for_surroundings(fake_board)){      /* After executing a valid move, checking if the King is still being checked. */
                                    check_counter = check_counter + 1;                    /* Counting the number of moves including checks. */
                                }

                                int v, w;                                                 /* Synchronizing the test board to the original board in order to reuse next move. */
                                    for (v = 0; v <= 7; v++){
                                        for (w = 0; w <= 7; w++){
                                            fake_board[v][w] = board[v][w];
                                        }
                                    }






                        }




                }


            }


        }


    }

    if (check_counter != possible_move_counter){         /* If the number of all valid moves are equal to number of checks, it means King can not escape and it is checkmate. */
        return 1;
    }
    else {

        return 0; /* Checkmate */
    }


}

//Beyazin stopwatch fonksiyonu
int stopwatch_of_white( void ){

    while (iCounterForWhite > 0)
    {
        printf("\n\n\n\t%d seconds left of White\n", iCounterForWhite);
        iCounterForWhite --;
        printf("\n\tWhite's turn\n");
        if(kbhit()) break;
        printf("\tPress enter to stop the watch");
        sleep(1);
        system("cls");
        print_board(board);
    }

    if(iCounterForWhite > 0){

        //sira siyaha gecer
        return 1;
    }
        printf("White disqualified\n");
        return 0;
}

//Siyahin stopwatch fonksiyonu
int stopwatch_of_black( void ){

    while (iCounterForBlack > 0)
    {
        printf("\n\n\n\t%d seconds left of Black\n", iCounterForBlack);
        iCounterForBlack--;
        printf("\n\tBlack's turn\n");
        if(kbhit()) break;
        printf("\tPress enter to stop the watch");
        sleep(1);
        system("cls");
        print_board(board);
    }

    if(iCounterForBlack > 0){

        //sira beyaza gecer
        return 1;
    }
        printf("Black disqualified\n");
        return 0;
}

void write_file(FILE* fptr, int board[8][8]){

    for(int z=0; z<8; z++){
        for(int x=0; x<8; x++){

            fprintf(fptr, "%d ", board[z][x]);
        }
        fprintf(fptr,"\n");
    }
}

void save_games(FILE* fptr,char* name){
    fseek(fptr,0,SEEK_END);
    fprintf(fptr,"%s\n",name);
}

void list_games(){
    FILE* fptr = fopen("filenames.txt","r");
    fseek(fptr,0,SEEK_SET);
    while(!feof(fptr)){
        char name[50];
        fscanf(fptr,"%s\n",name);
        printf("%s\n",name);
    }
    fclose(fptr);
}



void read_file(int board_read[8][8]){
    char filename[50];
    scanf("%s",filename);
    FILE* fptr = fopen(filename,"r");
    char buffer;
    int i = 0;

    while(i < 8){
        int j = 0;
        while(j < 8){
            fscanf(fptr,"%d",&board_read[i][j]);
            buffer = fgetc(fptr);
            j++;
        }
        buffer = fgetc(fptr);
        i++;
    }

}

void save_file(void){
            struct tm *local, *gm;
        time_t t;



        t=time(NULL);
        local = localtime(&t);
        int day = local->tm_mday;
        int month = local->tm_mon+1;
        int year = local->tm_year + 1900;
        int second = local->tm_sec;
        int min = local->tm_min;
        int hour = local->tm_hour;

        char date[20];
        sprintf(date,"%d%d%d",day,month,year);

        char time[20];
        sprintf(time,"%d%d%d",hour,min,second);


        char filename[50];
        strcpy(filename,date);
        strcat(filename,"_");
        strcat(filename,time);
        strcat(filename, ".txt");



        FILE* fptr_filenames = fopen("filenames.txt","a+");
        FILE* fptr = fopen(filename,"w");
        write_file(fptr,board);
        save_games(fptr_filenames,filename);

}
