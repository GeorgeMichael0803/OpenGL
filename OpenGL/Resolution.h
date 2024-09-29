#ifndef RESOLUTION_H
#define RESOLUTION_H

struct Resolution
{
    int width = 1280;
    int height = 768;
    float fov = 45.0f;

    Resolution(int _width, int _height) 
    {
        width = _width;
        height = _height;
        
    }

    Resolution(int _width, int _height , float _fov) 
    {
        width = _width;
        height = _height;
        fov = _fov;
    }
};

#endif // RESOLUTION_H
