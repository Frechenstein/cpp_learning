#include <GLFW/glfw3.h>
#include <complex>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

double xmin = -2.0, xmax = 1.0;
double ymin = -1.5, ymax = 1.5;
const int MAX_ITER = 1000;
double zoomFactor = 1.2;

unsigned char* pixels = new unsigned char[WIDTH * HEIGHT * 3];

void computeMandelbrot() {
    for (int py = 0; py < HEIGHT; ++py) {
        for (int px = 0; px < WIDTH; ++px) {
            double x0 = xmin + (xmax - xmin) * px / WIDTH;
            double y0 = ymin + (ymax - ymin) * py / HEIGHT;

            std::complex<double> c(x0, y0);
            std::complex<double> z(0);
            int iter = 0;
            while (abs(z) < 2.0 && iter < MAX_ITER) {
                z = z * z + c;
                ++iter;
            }

            int index = (py * WIDTH + px) * 3;
            pixels[index] = iter % 256;
            pixels[index + 1] = iter % 128;
            pixels[index + 2] = iter % 64;
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    double zoom = (yoffset > 0) ? 1.0 / zoomFactor : zoomFactor;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    double re = xmin + (xmax - xmin) * mouseX / WIDTH;
    double im = ymin + (ymax - ymin) * (HEIGHT - mouseY) / HEIGHT;

    xmin = re + (xmin - re) * zoom;
    xmax = re + (xmax - re) * zoom;
    ymin = im + (ymin - im) * zoom;
    ymax = im + (ymax - im) * zoom;

    computeMandelbrot();
}

/*
int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Mandelbrot GLFW", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetScrollCallback(window, scroll_callback);

    computeMandelbrot();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete[] pixels;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
*/