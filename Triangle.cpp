#include "Triangle.h"

double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double Triangle::area() {
    return heronArea(*this);
}

bool Triangle::is_zero_area() {
    return area() == 0.0;
}

bool Triangle::contains(const Point &p) {
    Triangle T1 = {a, b, p};
    Triangle T2 = {b, c, p};
    Triangle T3 = {c, a, p};

    double S_main = area();
    double S_sum = T1.area() + T2.area() + T3.area();

    return fabs(S_main - S_sum) < 1e-9;
}

vector<double> Triangle::is_point_inside(Point p) {
    vector<double> res_det;

    Point ab = {b.x - a.x, b.y - a.y};
    Point ap = {p.x - a.x, p.y - a.y};
    res_det.push_back(ab.x * ap.y - ab.y * ap.x);

    Point bc = {c.x - b.x, c.y - b.y};
    Point bp = {p.x - b.x, p.y - b.y};
    res_det.push_back(bc.x * bp.y - bc.y * bp.x);

    Point ca = {a.x - c.x, a.y - c.y};
    Point cp = {p.x - c.x, p.y - c.y};
    res_det.push_back(ca.x * cp.y - ca.y * cp.x);

    return res_det;
}

double heronArea(const Triangle &t) {
    double a = distance(t.a, t.b);
    double b = distance(t.b, t.c);
    double c = distance(t.c, t.a);
    double s = (a + b + c) / 2;

    return sqrt(s * (s - a) * (s - b) * (s - c));
}

bool check_triangle_side(double det) {
    return det == 0.0;
}

void clear_buffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool check_to_fail() {
    if (cin.fail()) {
        cout << "Помилка! Некоректне введення. Спробуйте ще раз." << endl;
        clear_buffer();
        return true;
    }
    return false;
}

void print_menu() {
    SetConsoleOutputCP(CP_UTF8);
    Triangle triangle;
    bool running = true;

    while (true) {
        cout << "\nВведіть координати трикутника (x1 y1 x2 y2 x3 y3):\u00A0";
        cin >> triangle.a.x >> triangle.a.y >> triangle.b.x >> triangle.b.y >> triangle.c.x >> triangle.c.y;

        if (check_to_fail()) {
            continue;
        }

        if ((triangle.a.x == triangle.b.x && triangle.a.y == triangle.b.y) ||
            (triangle.a.x == triangle.c.x && triangle.a.y == triangle.c.y) ||
            (triangle.b.x == triangle.c.x && triangle.b.y == triangle.c.y)) {
            cout << "Помилка! Дві або більше точки співпадають. Введіть координати це раз.";
            continue;
            }

        break;
    }

    clear_buffer();
    cout << "Координати трикутника введено успішно!\n" << endl;

    while (running) {
        vector<Point> points;
        string choice;

        cout << "Меню вибору:\n";
        cout << "1. Ввести координати трикутника\n";
        cout << "2. Ввести координати точок та перевірити їх положення (методом векторного множення)\n";
        cout << "3. Ввести координати точок та перевірити їх положення (методом розбиття на підтрикутники)\n";
        cout << "4. Вивести площу трикутника\n";
        cout << "5. Вийти\n";
        cout << "Ваш вибір:\u00A0";

        cin >> choice;
        clear_buffer();

        if (choice == "1") {
            while (true) {
                cout << "\nВведіть координати трикутника (x1 y1 x2 y2 x3 y3):\u00A0";
                cin >> triangle.a.x >> triangle.a.y >> triangle.b.x >> triangle.b.y >> triangle.c.x >> triangle.c.y;

                if (check_to_fail()) {
                    continue;
                }

                if ((triangle.a.x == triangle.b.x && triangle.a.y == triangle.b.y) ||
                    (triangle.a.x == triangle.c.x && triangle.a.y == triangle.c.y) ||
                    (triangle.b.x == triangle.c.x && triangle.b.y == triangle.c.y)) {
                    cout << "Помилка! Дві або більше точки співпадають. Введіть координати це раз.";
                    continue;
                }

                break;
            }

            clear_buffer();
            cout << "Координати трикутника введено успішно!\n" << endl;
        } else if (choice == "2" || choice == "3") {
            int numPoints;

            while (true) {
                cout << "\nСкільки точок ви хочете додати?\u00A0";
                cin >> numPoints;

                if (check_to_fail()) {
                    continue;
                }

                break;
            }

            clear_buffer();

            for (int i = 0; i < numPoints; i++) {
                while (true) {
                    Point point;
                    cout << "Введіть координати точки (x y):\u00A0";
                    cin >> point.x >> point.y;

                    if (check_to_fail()) {
                        continue;
                    }

                    points.push_back(point);
                    break;
                }
            }
            if (triangle.is_zero_area()) {
                cout << "Трикутник є виродженим!" << endl;
            }
            for (auto point: points) {
                if (choice == "2") {
                    vector<double> det = triangle.is_point_inside(point);
                    const vector<string> STRINGS = {"AB", "BC", "CA"};
                    bool on_side = false;

                    for (int i = 0; i < det.size(); i++) {
                        if (check_triangle_side(det[i])) {
                            cout << "Точка (" << point.x << ", " << point.y << ") лежить на стороні " << STRINGS[i] << endl;
                            on_side = true;
                        }
                    }
                    if (!on_side) {
                        bool sign_positive = (det[0] > 0 && det[1] > 0 && det[2] > 0);
                        bool sign_negative = (det[0] < 0 && det[1] < 0 && det[2] < 0);

                        if (sign_positive || sign_negative) {
                            cout << "Точка (" << point.x << ", " << point.y << ") знаходиться всередині трикутника" << endl;
                        } else {
                            cout << "Точка (" << point.x << ", " << point.y << ") знаходиться зовні трикутника" << endl;
                        }
                    }
                } else if (choice == "3") {
                    cout << "Точка (" << point.x << ", " << point.y << ") знаходиться "
                            << (triangle.contains(point) ? "всередині трикутника" : "зовні трикутника") << endl;
                }
            }
            cout << endl;
        } else if (choice == "4") {
            if (triangle.is_zero_area()) {
                cout << "\nТрикутник є виродженим!" << endl;
            } else {
                cout << "\nПлоща трикутника: " << triangle.area() << endl;
            }
        } else if (choice == "5") {
            running = false;
        } else {
            cout << "\nНевірний вибір. Спробуйте ще раз.\n";
        }
    }
}
