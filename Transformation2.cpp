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
    vector<Point> vertex = {p1, p2, p3, p4};
    Rect(Point pos1, Point pos2, Point pos3, Point pos4){
        vertex = {pos1, pos2, pos3, pos4};
    }

    Rect(){
        vertex = {Point(), Point(15, 0), Point(15, 15), Point(0, 15)};
    }

    void T(double dx, double dy){
        for (int i = 0; i < vertex.size(); i++)
            vertex[i] = Translate(vertex[i], dx, dy);
    }

    void Re(double theta){
        for (int i = 0; i < vertex.size(); i++)
            vertex[i] = Rotate(vertex[i], theta);
    }
    void M(Point pos){
        double ax = vertex[0].x - 760, ay = 390 - vertex[0].y;
        for (int i = 0; i < vertex.size(); i++){
            vertex[i] = Translate(vertex[i], pos.x - ax, pos.y - ay);
        }
    }
    void R(double theta){
        double ax = vertex[0].x - 760, ay = 390 - vertex[0].y;
        Point origin, coordinate;
        origin.x = 0; origin.y = 0;
        coordinate.x = ax; coordinate.y = ay;
        M(origin);
        Re(theta);
        M(coordinate);

    }
    void display(){
        for (int i = 0; i < vertex.size(); i++){
            cout << "(" << vertex[i%4].x - 760 << ", "<< " " << - vertex[i%4].y + 390 << ")" << endl;
        }
    }
};

void draw_rec(Rect r){
    for (int i = 0; i < r.vertex.size(); i++){
        Line l(r.vertex[i%4].x, r.vertex[i%4].y, r.vertex[(i+1)%4].x, r.vertex[(i+1)%4].y);
        l.imprint();
        }
}

int main(){
    initCanvas("Geometric Transformations", 1520, 780);

    Line xAxis(0, 390, 1520, 390);  // Draws the X-axis
    Line yAxis(760, 0, 760, 780);   // Draws the Y-axis
    xAxis.imprint();
    yAxis.imprint();

    Rect cr;
    double dx = 0, dy = 0, theta = 0;

    while (true){
        draw_rec(cr);
        cr.display();
        string com = "";
        cout << "Enter your command: ";
        cin >> com;

        if (com == "T"){
            cout << "Enter the distance to be translated: ";
            cin >> dx >> dy ;
            cr.T(dx, dy);
        }
        else if (com == "Re"){
            cout << "Enter the angle to be rotated about the origin: ";
            cin >> theta ;
            cr.Re(theta);
        }
        else if (com == "M"){
            Point pos;
            cout << "Enter the coordinates to go: " ;
            cin >> pos.x >> pos.y;
            cr.M(pos);
        }
        else if (com == "R"){
            cout << "Enter the angle to be rotated about its axis: ";
            cin >> theta ;
            cr.R(theta);
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
