#include <bits/stdc++.h>
using namespace std;
int stats[8][8];

void showgame () {
    system("CLS");
    cout << endl;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << stats[i][j] << " ";
        }
        cout << endl;
    }

    return;
}

int updateuppercolumn(int player, int y, int x) {
    int gotpoint = 0;

    // check column;
    int anotherplayer = 2;
    if (player == 2) {
        anotherplayer = 1;
    }


    if ( y >= 2 &&  stats [y - 1][x] == anotherplayer) {
        int run = 1 ;
        int flag = -1 ;


        for(int mark = y - 1; run == 1 && mark >= 0 ; mark--) {
            if (stats[mark][x] != 0) {
                if ( stats[mark][x] == player) {
                    gotpoint = 1;
                    flag = mark;
                    run = 0;
                }
            } else {
                run = 0;
            }
        }

        if (flag != -1) {
            for (int p = y; p >= flag; p--) {
                stats[p][x] = player;
            }
        }


        
    }

    return gotpoint;

}

int updatelowercolumn(int player, int y, int x) {
    int gotpoint = 0;
    int flag = 0;
    int run = 1;


    // find the first similar slot within the same column and save it as flag;
    for (int i = y + 1; i < 8 && run == 1; i++) {
        if (stats[i][x] == player) {
            flag = i;
            run = 0;
        }
    }

    // temp change;
    stats[y][x] = player;
    
    if ( run == 0 ) {
        gotpoint = updateuppercolumn(player, flag, x);

    }

    if (gotpoint != 1) {
        stats[y][x] = 0;

    }


    return gotpoint;







}

int updaterightrow (int player, int y, int x) {
    int gotpoint = 0;
    int flag = -1;
    int run = 1;

    int anotherplayer = 2;
    if (player == 2) {
        anotherplayer = 1;
    }


    if ( x <= 5 && stats[y][x+1] == anotherplayer) {
        for (int i = x +1; i < 8 && run == 1; i++){
            if ( stats[y][i] != 0) {
                if (stats[y][i] == player) {
                    flag = i;
                    gotpoint = 1;
                    run = 0;

                }


            } else {
                run = 0;
            }
        }
    }

    if ( flag != -1) {
        for (int j = x; j <= flag; j ++) {
            stats [y][j] = player;
        }
    }




    return gotpoint;



}

int updateleftrow (int player, int y, int x) {
    int gotpoint = 0;
    int flag = -1;
    int run = 1;


    stats[y][x] = player;

    if (x >= 2){    
        for ( int i = x - 1; i >= 0 && run == 1; i--) {
            if ( stats[y][i] != 0) {
                if (stats[y][i] == player) {

                    flag = i;
                    gotpoint = updaterightrow(player, y, flag);
                    run = 0;
                }
            }




        }
    }

    if (gotpoint == 0) {
        stats[y][x] = 0;
    }






    return gotpoint;
}

int updatezigzagupper(int player, int y , int x, int typex) {
    int gotpoint = 0;
    int flag_y = -1;
    int run = 1;

    int anotherplayer = 2;
    if (player == 2) {
        anotherplayer = 1;
    }


    if ( typex == 1) {
        // ---------- condition check;
        if  (x <= 5  && y >= 2 && stats[y-1][x+1] == anotherplayer) {
            int xcounter = x + 1;
            int ycounter = y - 1;
            while ( run == 1 && xcounter < 8 && ycounter >= 0) {
                if( stats[ycounter][xcounter] != 0) {
                    if ( stats[ycounter][xcounter] == player){
                        flag_y = ycounter;
                        gotpoint = 1;
                        run = 0;
                    }

                } else {
                    run = 0;
                }
                xcounter++;
                ycounter--;
            }
        }

    if (flag_y != -1) {
        for ( int j = y; j >= flag_y; j--) {
            stats[j][x] = player;
            x++;
        }

    }

    } else {
        cout << (y >= 2 && x >= 2 && stats[y-1][x-1] == anotherplayer) << endl;
        if  (y >= 2 && x >= 2 && stats[y-1][x-1] == anotherplayer) {
            
            int xcounter = x - 1;
            int ycounter = y - 1;
            while ( run == 1 && ycounter >= 0 && xcounter >= 0) {
                if( stats[ycounter][xcounter] != 0) {
                    if ( stats[ycounter][xcounter] == player){
                        flag_y = ycounter;
                        gotpoint = 1;
                        run = 0;
                    }

                } else {
                    run = 0;
                }
                xcounter--;
                ycounter--;
            }
        }

    if (flag_y != -1) {
        for ( int j = y; j >= flag_y; j--) {
            stats[j][x] = player;
            x--;
        }

    }
        


    }

    return gotpoint;



}

int updatezigzaglower(int player, int y , int x, int typex) {
    int gotpoint = 0;
    int flag_y = -1;
    int run = 1;

    stats[y][x] = player;

    if ( typex == 1) {
        if (x >= 2 && y <= 5) {
            int xcounter = x - 1;
            int ycounter = y + 1;
            while ( run == 1 && ycounter < 8 && xcounter >= 0) {
                if( stats[ycounter][xcounter] != 0) {
                    if ( stats[ycounter][xcounter] == player){
                        flag_y = ycounter;
                        gotpoint = 1;
                        run = 0;
                    }

                } else {
                    run = 0;
                }
                xcounter--;
                ycounter++;
            }

            if (flag_y != -1) {
                gotpoint = updatezigzagupper(player, ycounter - 1, xcounter + 1, 1);
            }
            
        }
    } else {
        if (y <= 5 && x <= 5) {
            int xcounter = x + 1;
            int ycounter = y + 1;
            while ( run == 1 && xcounter < 8 && ycounter < 8) {
                if( stats[ycounter][xcounter] != 0) {
                    if ( stats[ycounter][xcounter] == player){
                        flag_y = ycounter;
                        gotpoint = 1;
                        run = 0;
                    }

                } else {
                    run = 0;
                }
                xcounter++;
                ycounter++;
            }

            if (flag_y != -1) {
                gotpoint = updatezigzagupper(player, ycounter - 1, xcounter - 1, 2);
            }
        }

    }


    if (gotpoint == 0) {
        stats[y][x] = 0;
    }
    
    
    
    
    
    return gotpoint; 
}



/*

int validmove (int player, int x, int y) {
    int ret = update  (player, x, y);



    // check if the slot if full or not;


    if (ret == 0) {
        stats[y][x] = 0 ;

        if ( player == 1) {
            // invalid move error;
            cout << "invalid move;" << endl;
            //bluemove ();
        } else {
            // invalid move error;
            cout << "invalid move;" << endl;
            //redmove();
        }
    }


}

*/


void bluemove () {
    int x, y;
    
    cout << "BLUE | --" << endl;
    cout << "x : ";
    cin >> x;
    cout << endl;

    cout << "y : ";
    cin >> y;
    cout << endl;

    x--;
    y --;

    int uc = updateuppercolumn(1, y , x);
    int lc = updatelowercolumn(1, y , x);
    int rr = updaterightrow(1, y , x);
    int lr = updateleftrow(1, y , x);
    int zigu1 = updatezigzagupper(1, y , x, 1);
    int zigu2 = updatezigzagupper(1, y , x, 2);
    int zigl1 = updatezigzaglower(1, y , x, 1);
    int zigl2 = updatezigzaglower(1, y , x, 2);
    if (uc+lc+rr+lr+zigu1+zigu2+zigl1+zigl2 > 0){
        stats[y][x] = 1;
    }
    if (stats[y][x] == 0) {
        showgame();
        cout << "Invalid move: Try again! " << endl;
        bluemove();
    }

    return;

}



void redmove () {
    int x, y;
    
    cout << "RED | --" << endl;
    cout << "x : ";
    cin >> x;
    cout << endl;

    cout << "y : ";
    cin >> y;
    cout << endl;

    x --;
    y --;

    int uc = updateuppercolumn(2, y , x);
    int lc = updatelowercolumn(2, y , x);
    int rr = updaterightrow(2, y , x);
    int lr = updateleftrow(2, y , x);
    int zigu1 = updatezigzagupper(2, y , x, 1);
    int zigu2 = updatezigzagupper(2, y , x, 2);
    int zigl1 = updatezigzaglower(2, y , x, 1);
    int zigl2 = updatezigzaglower(2, y , x, 2);
    if (uc+lc+rr+lr+zigu1+zigu2+zigl1+zigl2 > 0){
        stats[y][x] = 2;
    }

    if (stats[y][x] == 0) {
        showgame();
        cout << "Invalid move: Try again! " << endl;
        redmove();
    }

    return;

}



int main () {
    // 1 = blue, 2 = red;
    stats[3][3] = 1;
    stats[4][4] = 1;
    
    stats[3][4] = 2;
    stats[4][3] = 2;

    int game = 64;

    while (game--) {
        showgame();
        if ( game % 2 == 0){
            bluemove ();
        } else {
            redmove ();
        }
    }

    cout <<"Game over" << endl;


    
    





}
