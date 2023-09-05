#include <simplecpp>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
    Point(double p, double q){
        x=760+p;
        y=390-q;
    }
    Point(){
        x=760;
        y=390;
    }
};

vector<vector<double>> matMul(const vector<vector<double>>& a, const vector<vector<double>>& b) {
    int numRowsA = a.size();
    int numColsA = a[0].size();
    int numRowsB = b.size();
    int numColsB = b[0].size();

    vector<vector<double>> c(numRowsA, vector<double>(numColsB, 0.0));

    for (int i = 0; i < numRowsA; i++) {
        for (int j = 0; j < numColsB; j++) {
            for (int k = 0; k < numColsA; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

Point Translate(Point pos, double dx, double dy){
    vector<vector<double>> T = {{1, 0, dx}, {0, 1, dy}, {0, 0, 1}};
    vector<vector<double>> X = {{pos.x - 760}, {-pos.y + 390}, {1}};
    vector<vector<double>> xNew = matMul(T, X);
    return(Point (xNew[0][0], xNew[1][0]));
}

Point Rotate(Point pos, double theta){
    vector<vector<double>> R = {{cosine(theta), -sine(theta), 0},
                                {sine(theta), cosine(theta), 0},
                                {0, 0, 1}};
    vector<vector<double>> X = {{pos.x - 760}, {-pos.y + 390}, {1}};
    vector<vector<double>> xNew = matMul(R, X);
    return(Point (xNew[0][0], xNew[1][0]));
}

struct Rect {
    Point p1, p2, p3, p4;
    Rect(Point pos1, Point pos2, Point pos3, Point pos4){
        p1 = pos1;
        p2 = pos2;
        p3 = pos3;
        p4 = pos4;
    }

    Rect(){
        p1 = Point();
        p2 = Point(15, 0);
        p3 = Point(15, 15);
        p4 = Point(0, 15);
    }

    void T(double dx, double dy){
        p1 = Translate(p1, dx, dy);
        p2 = Translate(p2, dx, dy);
        p3 = Translate(p3, dx, dy);
        p4 = Translate(p4, dx, dy);
    }

    void R(double theta){
        p1 = Rotate(p1, theta);
        p2 = Rotate(p2, theta);
        p3 = Rotate(p3, theta);
        p4 = Rotate(p4, theta);
    }
};

void draw_rec(Rect r){
    Line l1(r.p1.x, r.p1.y, r.p2.x, r.p2.y);
    Line l2(r.p2.x, r.p2.y, r.p3.x, r.p3.y);
    Line l3(r.p3.x, r.p3.y, r.p4.x, r.p4.y);
    Line l4(r.p4.x, r.p4.y, r.p1.x, r.p1.y);

    l1.imprint();
    l2.imprint();
    l3.imprint();
    l4.imprint();
}

int main(){
    initCanvas("Geometric Transformations", 1520, 780);

    Line xAxis(0, 390, 1520, 390);  // Draws the X-axis
    Line yAxis(760, 0, 760, 780);   // Draws the Y-axis
    xAxis.imprint();
    yAxis.imprint();

    Rect cr;
    draw_rec(cr);   // Draws a rectangle on the orgin

    double dx = 0, dy = 0, theta = 0;

    while (true){
        string com = "";
        cout << "Enter your command: ";
        cin >> com;

        if (com == "T"){
            cout << "Enter the distance to be translated: ";
            cin >> dx >> dy ;
            cr.T(dx, dy);
            draw_rec(cr);
        }
        else if (com == "R"){
            cout << "Enter the angle to be rotated about the origin: ";
            cin >> theta ;
            cr.R(theta);
            draw_rec(cr);
        }
        else if (com == "X"){
            break;
        }
        else {
            cout << "Inappropriate command!" << endl;
        }
    }
    wait(2);
    return(0);
}
