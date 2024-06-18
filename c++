#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<double> compute(const vector<double>& xi) {
    vector<double> yi;
    for (double x : xi) {
        yi.push_back(cos(x));
    }
    return yi;
}

double interpolate(const vector<double>& xi, const vector<double>& yi, double x) {
    int n = xi.size();
    vector<double> f = yi;

    for (int j = 1; j < n; ++j) {
        for (int i = n-1; i >= j; --i) {
            f[i] = (f[i] - f[i-1]) / (xi[i] - xi[i-j]);
        }
    }

    double result = f[n-1];
    for (int i = n-2; i >= 0; --i) {
        result = f[i] + (x - xi[i]) * result;
    }

    return result;
}

double error(const vector<double>& xi, const vector<double>& yi, double x) {
    int n = xi.size();
    double det = 1.0;

    for (int k = 0; k < n; ++k) {
        det *= (x - xi[k]);
    }

    return det;
}

int main() {
    vector<double> xi = { 0.1 * M_PI, 0.2 * M_PI, 0.3 * M_PI, 0.4 * M_PI };
    vector<double> yi = compute(xi);

    double x_star = 0.25 * M_PI;
    double result = interpolate(xi, yi, x_star);
    double err = error(xi, yi, x_star);

    cout << "Result at x* = " << x_star << ": " << result << endl;
    cout << "Error at x* = " << x_star << ": " << err << endl;

    return 0;
}
