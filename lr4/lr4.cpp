#include <iostream>
#include <complex>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>



        using namespace std;

        typedef complex<double> Complex;
        typedef vector<Complex> ComplexVector;

        // Функция для выполнения быстрого преобразования Фурье (FFT)
        ComplexVector fft(const ComplexVector & a, bool invert) {
            int n = a.size();
            if (n == 1) {
                return ComplexVector(1, a[0]);
            }

            ComplexVector a0(n / 2), a1(n / 2);
            for (int i = 0, j = 0; i < n; i += 2, ++j) {
                a0[j] = a[i];
                a1[j] = a[i + 1];
            }

            ComplexVector y0 = fft(a0, invert);
            ComplexVector y1 = fft(a1, invert);

            double angle = 2 * M_PI / n * (invert ? -1 : 1);
            Complex w(1), wn(cos(angle), sin(angle));
            ComplexVector y(n);

            for (int k = 0; k < n / 2; ++k) {
                y[k] = y0[k] + w * y1[k];
                y[k + n / 2] = y0[k] - w * y1[k];
                if (invert) {
                    y[k] /= 2;
                    y[k + n / 2] /= 2;
                }
                w *= wn;
            }

            return y;
        }

        // Функция для умножения больших целых чисел
        vector<int> multiplyLargeIntegers(const vector<int>&a, const vector<int>&b) {
            int n = 1;
            while (n < max(a.size(), b.size())) {
                n *= 2;
            }
            n *= 2;

            ComplexVector fa(n), fb(n);
            for (int i = 0; i < a.size(); ++i) {
                fa[i] = Complex(a[i], 0);
            }
            for (int i = 0; i < b.size(); ++i) {
                fb[i] = Complex(b[i], 0);
            }

            fa = fft(fa, false);
            fb = fft(fb, false);

            ComplexVector fc(n);
            for (int i = 0; i < n; ++i) {
                fc[i] = fa[i] * fb[i];
            }

            fc = fft(fc, true);

            vector<int> result(n);
            for (int i = 0; i < n; ++i) {
                result[i] = int(fc[i].real() + 0.5);
            }

            int carry = 0;
            for (int i = 0; i < n; ++i) {
                result[i] += carry;
                carry = result[i] / 10;
                result[i] %= 10;
            }

            while (result.size() > 1 && result.back() == 0) {
                result.pop_back();
            }

            return result;
        }

        // Функция для вывода большого целого числа
        void printLargeInteger(const vector<int>&num) {
            for (int i = num.size() - 1; i >= 0; --i) {
                cout << num[i];
            }
            cout << endl;
        }

        int main() {
          //  vector<int> a;  // Пример первого числа reverse
           // vector<int> b;     // Пример второго числа reverse
            string z, x;
            cin >> z;
            cin >> x;
            reverse(z.begin(), z.end());
            reverse(x.begin(), x.end());
            vector<int> a(z.begin(), z.end());
            vector<int> b(x.begin(), x.end());
            for (int i = 0; i < size(z); i++) {
                a[i] -= 0x30;
            }
            for (int i = 0; i < size(x); i++) {
                b[i] -= 0x30;
            }
            vector<int> result = multiplyLargeIntegers(a, b);

            cout << "result: ";
            printLargeInteger(result);

            return 0;
        }