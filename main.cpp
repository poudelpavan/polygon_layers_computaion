#include <iostream>
#include <stack>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
};

// A global point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
Point p0;

//generate random coordinate
Point generateCoord(int range_x, int range_y){
    Point a;
    a.x = rand()% range_x;
    a.y = rand()% range_y;
    return a;
}


//find outer layer
Point* outerLayer(Point* points, int n, int x_length, int y_length){
    Point* layer;
    Point left, right, top, bottom;
    left = points[0];
    right = points[0];
    top = points[0];
    bottom = points[0];
    for(int i = 1; i<n;i++){
        if(points[i].x < left.x){
            left.x = points[i].x;
            left.y = points[i].y;
        }
        if(points[i].y > top.y){
            top.x = points[i].x;
            top.y = points[i].y;
        }
        if(points[i].x > right.x){
            right.x = points[i].x;
            right.y = points[i].y;
        }
        if(points[i].y < bottom.y){
            bottom.x = points[i].x;
            bottom.y = points[i].y;
        }
    }
    int lcount = 0, tcount = 0, rcount = 0, bcount = 0;
    int* l = new int[y_length];
    int* t = new int[x_length];
    int* r = new int[y_length];
    int* b = new int[x_length];
    for(int i = 0; i < n; i++){
        if(points[i].x == left.x){
            l[lcount] = points[i].y;
            lcount++;
        }
        else if(points[i].y == top.y){
            t[tcount] = points[i].x;
            tcount++;
        }
        else if(points[i].x == right.x){
            r[rcount] = points[i].y;
            rcount++;
        }
        else if(points[i].y == bottom.y){
            b[bcount] = points[i].x;
            bcount++;
        }
    }
    sort(l, l + lcount);
    sort(t, t + tcount);
    sort(r, r + rcount, greater<int>());
    sort(b, b + bcount, greater<int>());
    int len = lcount + tcount + rcount + bcount;
    layer = new Point[len];
    for(int i = 0; i < lcount; i++){
        layer[i].x = left.x;
        layer[i].y = l[i];
    }
    for(int i = 0; i < tcount; i++){
        layer[i + lcount].x = t[i];
        layer[i + lcount].y = top.y;
    }
    for(int i = 0; i < rcount; i++){
        layer[i + lcount + tcount].x = left.x;
        layer[i + lcount + tcount].y = r[i];
    }
    for(int i = 0; i < bcount; i++){
        layer[i + lcount + tcount + rcount].x = b[i];
        layer[i + lcount + tcount + rcount].y = bottom.y;
    }
    return layer;
}
int* findExtremes(Point* points, int n){
    int* extreme = new int[4];
    extreme[0] = points[0].x;//left
    extreme[1] = points[0].y;//top
    extreme[2] = points[0].x;//right
    extreme[3] = points[0].y;//bottom
    for(int i = 1; i< n; i++){
        if(points[i].x < extreme[0]){
            extreme[0] = points[i].x;
        }
        if(points[i].y > extreme[1]){
            extreme[1] = points[i].y;
        }
        if(points[i].x > extreme[2]){
            extreme[2] = points[i].x;
        }
        if(points[i].y < extreme[3]){
            extreme[3] = points[i].y;
        }
    }
    return extreme;
}
int main() {
    int count = 0, tot_layers = 0, totalpoints = 0, n=0, tests = 0, space = 1;
    std::cout<<"----------------------------------------------------------------------"<<endl<<endl;
    std::cout << "\tLAYER COMPUTATION " << std::endl<<std::endl;
    std::cout<<"----------------------------------------------------------------------"<<endl<<endl;
    std::cout << "Enter the number of points: ";
    std::cin >> totalpoints;
    again:
    std::cout << "Select the grid space for initial configuration:"<<endl;
    std::cout << "1. Compact square (sqrt(n) * sqrt(n))"<<endl;
    std::cout << "2. Tight square ((sqrt(n)*2) * (sqrt(n)*2))"<<endl;
    std::cout << "3. Loose square ((sqrt(n)*3) * (sqrt(n)*3))"<<endl;
    std::cout << "4. Rectangle ((sqrt(n)/2) * (sqrt(n)*3))"<<endl;
    std::cout << "5. Rectangle ((3/2)(sqrt(n)) * ((4/3)sqrt(n))"<<endl;
    std::cout << "6. Rectangle ((3/2)(sqrt(n)) * (sqrt(n))"<<endl;
    std::cout << "Choose Option (1, 2, 3, 4, 5 or 6): ";
    std::cin >> space;
    if(space < 1 || space > 6){
        std::cout<<"Wrong choice"<<endl;
        goto again;
    }
    std::cout << "\nHow many tests do you want to perform: ";
    std::cin >> tests;
    std::cout<<"----------------------------------------------------------------------"<<endl;
    std::cout<<"\nTotal number of points: "<<totalpoints<<endl<<endl;
    std::cout <<"Tests \t\t\t layers (h)" << endl;
    std::cout<<"----------------------------------------------------------------------"<<endl;

/*
    int x[] = {100,500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
    double result[6][12];
    for(int y = 1; y < 7; y++){
        for(int z = 0; z < 12; z++){
            int count = 0, tot_layers = 0, totalpoints = x[z], n=0, tests = 20, space = y;
*/
            srand(time(0));


            while(count < tests) {
                n = totalpoints;
                int h = 0;

                int range_x = 0, range_y = 0;
                if(space < 4){
                    range_x = (int)(ceil (sqrt(n))) * space;
                    range_y = (int)(ceil (sqrt(n))) * space;
                }
                else if(space == 4){
                    range_x = (int)(ceil (sqrt(n))) / 2;
                    range_y = (int)(ceil (sqrt(n))) * 3;
                }
                else if(space == 5){
                    range_x = ((int)(ceil (sqrt(n))) * 3) / 2;
                    range_y = ((int)(ceil (sqrt(n))) * 4) / 3;
                }
                else if(space == 6){
                    range_x = ((int)(ceil (sqrt(n))) * 3) / 2;
                    range_y = (int)(ceil (sqrt(n)));
                }

                Point *points = new Point[n];
                Point **internals = new Point *[n];

                for (int i = 0; i < n; i++) {
                    internals[i] = new Point[n];
                }
                //std::cout << "The points are:" <<n<< endl;
                for (int i = 0; i < n; i++) {
                    label:
                    Point newpoint = generateCoord(range_x, range_y);
                    for (int j = i - 1; j >= 0; j--) {
                        if (points[j].x == newpoint.x && points[j].y == newpoint.y) {
                            goto label;
                        }
                    }
                    points[i].x = newpoint.x;
                    points[i].y = newpoint.y;
                    //std::cout << "(" << points[i].x << ", " << points[i].y << ") ";
                }
                //std::cout<<endl<<endl;
                int layers =0, nextSize = n;

                while(nextSize > 0){
                    internals[h] = new Point[nextSize];
                    for(int i = 0; i < nextSize; i++){
                        internals[h][i].x = points[i].x;
                        internals[h][i].y = points[i].y;
                    }
                    bool terminate = false;
                    int* extremes = findExtremes(internals[h], nextSize);
                    int left = extremes[0], top = extremes[1], right = extremes[2], bottom = extremes[3];
                    //std::cout<<"Layer "<<h<<" (Left, top, right, bottom): "<<left<<", "<<top<<", "<<right<<", "<<bottom<<endl;
                    if((right - left) < 2 || (top - bottom) < 2){
                        terminate = true;
                    }
                    int gridSpace[right + 1][top + 1];
                    int gridSize = (right - left + 1) * (top - bottom +1);
                    int layerPoints = 0;
                    for(int i = 0; i <= right; i++){
                        for(int j = 0; j <= top; j++){
                            gridSpace[i][j] = 0;
                        }
                    }
                    for(int i = 0; i < nextSize; i++){
                        gridSpace[internals[h][i].x][internals[h][i].y] = 1;
                    }
                    for(int i = bottom + 1; i < top; i++){
                        if(gridSpace[left][i] == 0){
                            int j = left + 1;
                            while((j < right) && gridSpace[j][i] == 0){
                                j++;
                            }
                            if((j < right) && gridSpace[j][i] == 1){
                                gridSpace[j][i] = 0;
                                gridSpace[left][i] = 1;
                            }
                        }
                    }
                    for(int i = left + 1; i < right; i++){
                        if(gridSpace[i][top] == 0){
                            int j = top - 1;
                            while((j > bottom) && gridSpace[i][j] == 0){
                                j--;
                            }
                            if((j > bottom) && gridSpace[i][j] == 1){
                                gridSpace[i][j] = 0;
                                gridSpace[i][top] = 1;
                            }
                        }
                    }
                    for(int i = bottom + 1; i < top; i++){
                        if(gridSpace[right][i] == 0){
                            int j = right - 1;
                            while((j > left) && gridSpace[j][i] == 0){
                                j--;
                            }
                            if((j > left) && gridSpace[j][i] == 1){
                                gridSpace[j][i] = 0;
                                gridSpace[right][i] = 1;
                            }
                        }
                    }
                    for(int i = left + 1; i < right; i++){
                        if(gridSpace[i][bottom] == 0){
                            int j = bottom + 1;
                            while((j < top) && gridSpace[i][j] == 0){
                                j++;
                            }
                            if((j < top) && gridSpace[i][j] == 1){
                                gridSpace[i][j] = 0;
                                gridSpace[i][bottom] = 1;
                            }
                        }
                    }

                    //std::cout<<"After movement, Layer "<<layers<<": ";
                    if(gridSpace[left][bottom] == 1){
                        layerPoints++;
                        //std::cout<<"("<<left<<", "<<bottom<<") ";
                    }
                    if(gridSpace[left][top] == 1){
                        layerPoints++;
                        //std::cout<<"("<<left<<", "<<top<<") ";
                    }
                    if(gridSpace[right][bottom] == 1){
                        layerPoints++;
                        //std::cout<<"("<<right<<", "<<bottom<<") ";
                    }
                    if(gridSpace[right][top] == 1){
                        layerPoints++;
                        //std::cout<<"("<<right<<", "<<top<<") ";
                    }
                    for(int i = left + 1; i < right; i++){
                        if(gridSpace[i][bottom] == 1){
                            layerPoints++;
                            //std::cout<<"("<<i<<", "<<bottom<<") ";
                        }
                        if(gridSpace[i][top] == 1){
                            layerPoints++;
                            //std::cout<<"("<<i<<", "<<top<<") ";
                        }
                    }
                    for(int j = bottom + 1; j < top; j++){
                        if(gridSpace[left][j] == 1){
                            layerPoints++;
                            //std::cout<<"("<<left<<", "<<j<<") ";
                        }
                        if(gridSpace[right][j] == 1){
                            layerPoints++;
                            //std::cout<<"("<<right<<", "<<j<<") ";
                        }
                    }


                    //std::cout<<endl;
                    //std::cout<<"Internal points: ";
                    nextSize = nextSize - layerPoints;
                    if(nextSize > 0) {
                        points = new Point[nextSize];
                        int k = 0;
                        for (int i = left + 1; i < right; i++) {
                            for (int j = bottom + 1; j < top; j++) {
                                if (gridSpace[i][j] == 1) {
                                    points[k].x = i;
                                    points[k].y = j;
                                    k++;
                                    //std::cout<<"("<<i<<", "<<j<<") ";
                                }
                            }
                        }
                        //std::cout<<endl;
                    }
                    if(terminate){
                        nextSize = 0;
                    }
                    layers++;
                    h++;
                }
                std::cout<<"Test "<<count + 1<<"\t\tNumber of Layers = "<<layers<<endl;
                tot_layers += layers;
                count++;
            }
//            result[y][z] = (double)tot_layers/(double)tests;
//        }

//    }



    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"\nAverage of "<< tests <<"\tLayers = "<<(double)tot_layers/(double)tests<<endl<<endl<<endl;
/*    std::cout<<"Points Size\t\tInitial configurations"<<endl;
    std::cout<<"\t1\t2\t3\t4\t5\t6"<<endl;
    for(int z = 0; z < 12; z++) {
        std::cout<<x[z];
        for (int y = 1; y < 7; y++) {
            std::cout<<"\t"<<result[y][z];
        }
        std::cout<<endl;
    }*/
    return 0;
}
