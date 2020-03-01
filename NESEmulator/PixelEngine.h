//
//  PixelEngine.h
//  NesEmulator
//
//  Created by JunMin Kim on 2020/02/27.
//  Copyright © 2020 JunMin Kim. All rights reserved.
//

#pragma once

#if defined(_WIN32) // WINDOWS specific includes ==============================================
    // Link to libraries
#ifndef __MINGW32__
    #pragma comment(lib, "user32.lib")        // Visual Studio Only
    #pragma comment(lib, "gdi32.lib")        // For other Windows Compilers please add
    #pragma comment(lib, "opengl32.lib")    // these libs to your linker input
    #pragma comment(lib, "gdiplus.lib")
#else
    // In Code::Blocks, Select C++14 in your build options, and add the
    // following libs to your linker: user32 gdi32 opengl32 gdiplus
    #if !defined _WIN32_WINNT
        #ifdef HAVE_MSMF
            #define _WIN32_WINNT 0x0600 // Windows Vista
        #else
            #define _WIN32_WINNT 0x0500 // Windows 2000
        #endif
    #endif
#endif
    // Include WinAPI
    #include <windows.h>
    #include <gdiplus.h>

    // OpenGL Extension
    #include <GL/gl.h>
    typedef BOOL(WINAPI wglSwapInterval_t) (int interval);
    static wglSwapInterval_t *wglSwapInterval;
#endif

#ifdef __linux__ // LINUX specific includes ==============================================
    #include <GL/gl.h>
    #include <GL/glx.h>
    #include <X11/X.h>
    #include <X11/Xlib.h>
    #include <png.h>
    typedef int(glSwapInterval_t) (Display *dpy, GLXDrawable drawable, int interval);
    static glSwapInterval_t *glSwapIntervalEXT;
#endif


#undef min
#undef max
#define UNUSED(x) (void)(x)

namespace PixelEngine
{
    struct Pixel
    {
        union
        {
            uint32_t n = 0xFF000000;
            struct
            {
                uint8_t r;    uint8_t g;    uint8_t b;    uint8_t a;
            };
        };

        Pixel();
        Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
        Pixel(uint32_t p);
        enum Mode { NORMAL, MASK, ALPHA, CUSTOM };

        bool operator==(const Pixel& p) const;
        bool operator!=(const Pixel& p) const;
    };

    // Some constants for symbolic naming of Pixels
    static const Pixel
        WHITE(255, 255, 255),
        GREY(192, 192, 192), DARK_GREY(128, 128, 128), VERY_DARK_GREY(64, 64, 64),
        RED(255, 0, 0), DARK_RED(128, 0, 0), VERY_DARK_RED(64, 0, 0),
        YELLOW(255, 255, 0), DARK_YELLOW(128, 128, 0), VERY_DARK_YELLOW(64, 64, 0),
        GREEN(0, 255, 0), DARK_GREEN(0, 128, 0), VERY_DARK_GREEN(0, 64, 0),
        CYAN(0, 255, 255), DARK_CYAN(0, 128, 128), VERY_DARK_CYAN(0, 64, 64),
        BLUE(0, 0, 255), DARK_BLUE(0, 0, 128), VERY_DARK_BLUE(0, 0, 64),
        MAGENTA(255, 0, 255), DARK_MAGENTA(128, 0, 128), VERY_DARK_MAGENTA(64, 0, 64),
        BLACK(0, 0, 0),
        BLANK(0, 0, 0, 0);

    enum rcode
    {
        FAIL = 0,
        OK = 1,
        NO_FILE = -1,
    };

    //==================================================================================

    template <class T>
    struct v2d_generic
    {
        T x = 0;
        T y = 0;

        inline v2d_generic() : x(0), y(0)                        {                                                      }
        inline v2d_generic(T _x, T _y) : x(_x), y(_y)            {                                                      }
        inline v2d_generic(const v2d_generic& v) : x(v.x), y(v.y){                                                      }
        inline T mag()                                           { return sqrt(x * x + y * y);                          }
        inline T mag2()                                             { return x * x + y * y; }
        inline v2d_generic  norm()                               { T r = 1 / mag(); return v2d_generic(x*r, y*r);       }
        inline v2d_generic  perp()                               { return v2d_generic(-y, x);                           }
        inline T dot(const v2d_generic& rhs)                     { return this->x * rhs.x + this->y * rhs.y;            }
        inline T cross(const v2d_generic& rhs)                   { return this->x * rhs.y - this->y * rhs.x;            }
        inline v2d_generic  operator +  (const v2d_generic& rhs) const { return v2d_generic(this->x + rhs.x, this->y + rhs.y);}
        inline v2d_generic  operator -  (const v2d_generic& rhs) const { return v2d_generic(this->x - rhs.x, this->y - rhs.y);}
        inline v2d_generic  operator *  (const T& rhs)           const { return v2d_generic(this->x * rhs, this->y * rhs);    }
        inline v2d_generic  operator /  (const T& rhs)           const { return v2d_generic(this->x / rhs, this->y / rhs);    }
        inline v2d_generic& operator += (const v2d_generic& rhs) { this->x += rhs.x; this->y += rhs.y; return *this;    }
        inline v2d_generic& operator -= (const v2d_generic& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this;    }
        inline v2d_generic& operator *= (const T& rhs)           { this->x *= rhs; this->y *= rhs; return *this;        }
        inline v2d_generic& operator /= (const T& rhs)           { this->x /= rhs; this->y /= rhs; return *this;        }
        inline T& operator [] (std::size_t i)                    { return *((T*)this + i);       /* <-- D'oh :( */        }
        inline operator v2d_generic<int>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
        inline operator v2d_generic<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
    };

    template<class T> inline v2d_generic<T> operator * (const float& lhs, const v2d_generic<T>& rhs) { return v2d_generic<T>(lhs * rhs.x, lhs * rhs.y); }
    template<class T> inline v2d_generic<T> operator * (const double& lhs, const v2d_generic<T>& rhs){ return v2d_generic<T>(lhs * rhs.x, lhs * rhs.y); }
    template<class T> inline v2d_generic<T> operator * (const int& lhs, const v2d_generic<T>& rhs)   { return v2d_generic<T>(lhs * rhs.x, lhs * rhs.y); }
    template<class T> inline v2d_generic<T> operator / (const float& lhs, const v2d_generic<T>& rhs) { return v2d_generic<T>(lhs / rhs.x, lhs / rhs.y); }
    template<class T> inline v2d_generic<T> operator / (const double& lhs, const v2d_generic<T>& rhs){ return v2d_generic<T>(lhs / rhs.x, lhs / rhs.y); }
    template<class T> inline v2d_generic<T> operator / (const int& lhs, const v2d_generic<T>& rhs)   { return v2d_generic<T>(lhs / rhs.x, lhs / rhs.y); }

    typedef v2d_generic<int> vi2d;
    typedef v2d_generic<float> vf2d;
    typedef v2d_generic<double> vd2d;

    //=============================================================

    struct HWButton
    {
        bool bPressed = false;    // Set once during the frame the event occurs
        bool bReleased = false;    // Set once during the frame the event occurs
        bool bHeld = false;        // Set true for all frames between pressed and released events
    };

    //=============================================================


    class ResourcePack
    {
    public:
        ResourcePack();
        ~ResourcePack();
        struct sEntry : public std::streambuf {
            uint32_t nID = 0, nFileOffset = 0, nFileSize = 0; uint8_t* data = nullptr; void _config() { this->setg((char*)data, (char*)data, (char*)(data + nFileSize)); }
        };

    public:
        PixelEngine::rcode AddToPack(std::string sFile);

    public:
        PixelEngine::rcode SavePack(std::string sFile);
        PixelEngine::rcode LoadPack(std::string sFile);
        PixelEngine::rcode ClearPack();

    public:
        PixelEngine::ResourcePack::sEntry GetStreamBuffer(std::string sFile);

    private:

        std::map<std::string, sEntry> mapFiles;
    };

    //=============================================================

    // A bitmap-like structure that stores a 2D array of Pixels
    class Sprite
    {
    public:
        Sprite();
        Sprite(std::string sImageFile);
        Sprite(std::string sImageFile, PixelEngine::ResourcePack *pack);
        Sprite(int32_t w, int32_t h);
        ~Sprite();

    public:
        PixelEngine::rcode LoadFromFile(std::string sImageFile, PixelEngine::ResourcePack *pack = nullptr);
        PixelEngine::rcode LoadFromPGESprFile(std::string sImageFile, PixelEngine::ResourcePack *pack = nullptr);
        PixelEngine::rcode SaveToPGESprFile(std::string sImageFile);

    public:
        int32_t width = 0;
        int32_t height = 0;
        enum Mode { NORMAL, PERIODIC };

    public:
        void SetSampleMode(PixelEngine::Sprite::Mode mode = PixelEngine::Sprite::Mode::NORMAL);
        Pixel GetPixel(int32_t x, int32_t y);
        bool  SetPixel(int32_t x, int32_t y, Pixel p);

        Pixel Sample(float x, float y);
        Pixel SampleBL(float u, float v);
        Pixel* GetData();

    private:
        Pixel *ProgramCounterolData = nullptr;
        Mode modeSample = Mode::NORMAL;

#ifdef PixelEngine_DBG_OVERDRAW
    public:
        static int nOverdrawCount;
#endif

    };

    //=============================================================

    enum Key
    {
        NONE,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        UP, DOWN, LEFT, RIGHT,
        SPACE, TAB, SHIFT, CTRL, INS, DEL, HOME, END, PGUP, PGDN,
        BACK, ESCAPE, RETURN, ENTER, PAUSE, SCROLL,
        NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
        NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL,
    };


    //=============================================================

    class PixelGameEngine
    {
    public:
        PixelGameEngine();

    public:
        PixelEngine::rcode    Construct(uint32_t screen_w, uint32_t screen_h, uint32_t pixel_w, uint32_t pixel_h, bool full_screen = false, bool vsync = false);
        PixelEngine::rcode    Start();

    public: // Override Interfaces
        // Called once on application startup, use to load your resources
        virtual bool OnUserCreate();
        // Called every frame, and provides you with a time per frame value
        virtual bool OnUserUpdate(float fElapsedTime);
        // Called once on application termination, so you can be a clean coder
        virtual bool OnUserDestroy();

    public: // Hardware Interfaces
        // Returns true if window is currently in focus
        bool IsFocused();
        // Get the state of a specific keyboard button
        HWButton GetKey(Key k);
        // Get the state of a specific mouse button
        HWButton GetMouse(uint32_t b);
        // Get Mouse X coordinate in "pixel" space
        int32_t GetMouseX();
        // Get Mouse Y coordinate in "pixel" space
        int32_t GetMouseY();
        // Get Mouse Wheel Delta
        int32_t GetMouseWheel();

    public: // Utility
        // Returns the width of the screen in "pixels"
        int32_t ScreenWidth();
        // Returns the height of the screen in "pixels"
        int32_t ScreenHeight();
        // Returns the width of the currently selected drawing target in "pixels"
        int32_t GetDrawTargetWidth();
        // Returns the height of the currently selected drawing target in "pixels"
        int32_t GetDrawTargetHeight();
        // Returns the currently active draw target
        Sprite* GetDrawTarget();

    public: // Draw Routines
        // Specify which Sprite should be the target of drawing functions, use nullptr
        // to specify the primary screen
        void SetDrawTarget(Sprite *target);
        // Change the pixel mode for different optimisations
        // PixelEngine::Pixel::NORMAL = No transparency
        // PixelEngine::Pixel::MASK   = Transparent if alpha is < 255
        // PixelEngine::Pixel::ALPHA  = Full transparency
        void SetPixelMode(Pixel::Mode m);
        Pixel::Mode GetPixelMode();
        // Use a custom blend function
        void SetPixelMode(std::function<PixelEngine::Pixel(const int x, const int y, const PixelEngine::Pixel& pSource, const PixelEngine::Pixel& pDest)> pixelMode);
        // Change the blend factor form between 0.0f to 1.0f;
        void SetPixelBlend(float fBlend);
        // Offset texels by sub-pixel amount (advanced, do not use)
        void SetSubPixelOffset(float ox, float oy);

        // Draws a single Pixel
        virtual bool Draw(int32_t x, int32_t y, Pixel p = PixelEngine::WHITE);
        // Draws a line from (x1,y1) to (x2,y2)
        void DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Pixel p = PixelEngine::WHITE, uint32_t pattern = 0xFFFFFFFF);
        // Draws a circle located at (x,y) with radius
        void DrawCircle(int32_t x, int32_t y, int32_t radius, Pixel p = PixelEngine::WHITE, uint8_t mask = 0xFF);
        // Fills a circle located at (x,y) with radius
        void FillCircle(int32_t x, int32_t y, int32_t radius, Pixel p = PixelEngine::WHITE);
        // Draws a rectangle at (x,y) to (x+w,y+h)
        void DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = PixelEngine::WHITE);
        // Fills a rectangle at (x,y) to (x+w,y+h)
        void FillRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = PixelEngine::WHITE);
        // Draws a triangle between points (x1,y1), (x2,y2) and (x3,y3)
        void DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p = PixelEngine::WHITE);
        // Flat fills a triangle between points (x1,y1), (x2,y2) and (x3,y3)
        void FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p = PixelEngine::WHITE);
        // Draws an entire sprite at location (x,y)
        void DrawSprite(int32_t x, int32_t y, Sprite *sprite, uint32_t scale = 1);
        // Draws an area of a sprite at location (x,y), where the
        // selected area is (ox,oy) to (ox+w,oy+h)
        void DrawPartialSprite(int32_t x, int32_t y, Sprite *sprite, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale = 1);
        // Draws a single line of text
        void DrawString(int32_t x, int32_t y, std::string sText, Pixel col = PixelEngine::WHITE, uint32_t scale = 1);
        // Clears entire draw target to Pixel
        void Clear(Pixel p);
        // Resize the primary screen sprite
        void SetScreenSize(int w, int h);

    public: // Branding
        std::string sAppName;

    private: // Inner mysterious workings
        Sprite        *pDefaultDrawTarget = nullptr;
        Sprite        *pDrawTarget = nullptr;
        Pixel::Mode    nPixelMode = Pixel::NORMAL;
        float        fBlendFactor = 1.0f;
        uint32_t    nScreenWidth = 256;
        uint32_t    nScreenHeight = 240;
        uint32_t    nPixelWidth = 4;
        uint32_t    nPixelHeight = 4;
        int32_t        nMousePosX = 0;
        int32_t        nMousePosY = 0;
        int32_t        nMouseWheelDelta = 0;
        int32_t        nMousePosXcache = 0;
        int32_t        nMousePosYcache = 0;
        int32_t        nMouseWheelDeltaCache = 0;
        int32_t        nWindowWidth = 0;
        int32_t        nWindowHeight = 0;
        int32_t        nViewX = 0;
        int32_t        nViewY = 0;
        int32_t        nViewW = 0;
        int32_t        nViewH = 0;
        bool        bFullScreen = false;
        float        fPixelX = 1.0f;
        float        fPixelY = 1.0f;
        float        fSubPixelOffsetX = 0.0f;
        float        fSubPixelOffsetY = 0.0f;
        bool        bHasInputFocus = false;
        bool        bHasMouseFocus = false;
        bool        bEnableVSYNC = false;
        float        fFrameTimer = 1.0f;
        int            nFrameCount = 0;
        Sprite        *fontSprite = nullptr;
        std::function<PixelEngine::Pixel(const int x, const int y, const PixelEngine::Pixel&, const PixelEngine::Pixel&)> funcPixelMode;

        static std::map<size_t, uint8_t> mapKeys;
        bool        pKeyNewState[256]{ 0 };
        bool        pKeyOldState[256]{ 0 };
        HWButton    pKeyboardState[256];

        bool        pMouseNewState[5]{ 0 };
        bool        pMouseOldState[5]{ 0 };
        HWButton    pMouseState[5];

#if defined(_WIN32)
        HDC            glDeviceContext = nullptr;
        HGLRC        glRenderContext = nullptr;
#endif

#if defined(__linux__)
        GLXContext    glDeviceContext = nullptr;
        GLXContext    glRenderContext = nullptr;
#endif
        GLuint        glBuffer;

        void        EngineThread();

        // If anything sets this flag to false, the engine
        // "should" shut down gracefully
        static std::atomic<bool> bAtomActive;

        // Common initialisation functions
        void PixelEngine_UpdateMouse(int32_t x, int32_t y);
        void PixelEngine_UpdateMouseWheel(int32_t delta);
        void PixelEngine_UpdateWindowSize(int32_t x, int32_t y);
        void PixelEngine_UpdateViewport();
        bool PixelEngine_OpenGLCreate();
        void PixelEngine_ConstructFontSheet();


#if defined(_WIN32)
        // Windows specific window handling
        HWND PixelEngine_hWnd = nullptr;
        HWND PixelEngine_WindowCreate();
        std::wstring wsAppName;
        static LRESULT CALLBACK PixelEngine_WindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif

#if defined(__linux__)
        // Non-Windows specific window handling
        Display*                PixelEngine_Display = nullptr;
        Window                    PixelEngine_WindowRoot;
        Window                    PixelEngine_Window;
        XVisualInfo*            PixelEngine_VisualInfo;
        Colormap                PixelEngine_ColourMap;
        XSetWindowAttributes    PixelEngine_SetWindowAttribs;
        Display*                PixelEngine_WindowCreate();
#endif

    };


    class PGEX
    {
        friend class PixelEngine::PixelGameEngine;
    protected:
        static PixelGameEngine* pge;
    };

    //=============================================================
}
