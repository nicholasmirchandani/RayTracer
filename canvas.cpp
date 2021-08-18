#include "canvas.h"
#include <string>
#include <fstream>

canvas::canvas(int width, int height) {
    this->width = width;
    this->height = height;
    pixels = new color*[width]; // Default constructor called here for color, handles setting colors to (0,0,0,1)
    for(int i = 0; i < width; ++i) {
        pixels[i] = new color[height];
    }
}

canvas::~canvas() {
    for(int i = 0; i < width; ++i) {
        delete(pixels[i]);
    }
    delete(pixels);
}

std::string canvas::ToPPM() {
    std::string ppm = "P3\n" + std::to_string(width) + " " + std::to_string(height) + "\n255\n";
    int charsOnLine = 0;
    std::string charsToAdd = "";
    for(int j = 0; j < height; ++j) {
        for(int i = 0; i < width; ++i) {
            color curPixel = pixels[i][j];
            // change float from 0-1 to 0-255 int, with everything < 0 at 0 and everything > 1 at 255, rounding to the nearest integer
            int r = curPixel.r < 1 ? (int) (curPixel.r * 255 + 0.5f) : 255;
            int g = curPixel.g < 1 ? (int) (curPixel.g * 255 + 0.5f) : 255;
            int b = curPixel.b < 1 ? (int) (curPixel.b * 255 + 0.5f) : 255;

            r = r < 0 ? 0 : r;
            g = g < 0 ? 0 : g;
            b = b < 0 ? 0 : b;
            
            // This is the stupid slow code because it's exporting it all as a single string :(
            charsToAdd = std::to_string(r) + " " +
                         std::to_string(g) + " " +
                         std::to_string(b) + " ";
            
            //R, G, B for each pixel
            charsOnLine += charsToAdd.length();
            if(charsOnLine >= 70) {
                ppm = ppm + '\n';
                charsOnLine = 0;
            }
            ppm = ppm + charsToAdd;
        }
        // Newline at the end of each row
        ppm = ppm + '\n';
        charsOnLine = 0;
    }
    return ppm;
}

void canvas::writePPM(std::ofstream& os) {
    os << "P3\n" << std::to_string(width) << " " << std::to_string(height) << "\n255\n";
    int charsOnLine = 0;
    std::string charsToAdd = "";
    for(int j = 0; j < height; ++j) {
        for(int i = 0; i < width; ++i) {
            color curPixel = pixels[i][j];
            // change float from 0-1 to 0-255 int, with everything < 0 at 0 and everything > 1 at 255, rounding to the nearest integer
            int r = curPixel.r < 1 ? (int) (curPixel.r * 255 + 0.5f) : 255;
            int g = curPixel.g < 1 ? (int) (curPixel.g * 255 + 0.5f) : 255;
            int b = curPixel.b < 1 ? (int) (curPixel.b * 255 + 0.5f) : 255;

            r = r < 0 ? 0 : r;
            g = g < 0 ? 0 : g;
            b = b < 0 ? 0 : b;
            
            // This is the stupid slow code because it's exporting it all as a single string :(
            charsToAdd = std::to_string(r) + " " +
                         std::to_string(g) + " " +
                         std::to_string(b) + " ";
            
            //R, G, B for each pixel
            charsOnLine += charsToAdd.length();
            if(charsOnLine >= 70) {
                os << '\n';
                charsOnLine = 0;
            }
            os << charsToAdd;
        }
        // Newline at the end of each row
        os << '\n';
        charsOnLine = 0;
    }
}

color* canvas::operator[](int i) {
    return pixels[i];
}