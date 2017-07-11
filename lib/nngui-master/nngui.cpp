/*
    src/popup.cpp -- Simple popup widget which is attached to another given
    window (can be nested)

    Original NanoGUI was developed by Wenzel Jakob <wenzel@inf.ethz.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    nnGUI was improved by Dalerank <dalerankn8@gmail.com>

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nngui.h>
#include <assert.h>
#include <regex>
#include <iostream>
#include <numeric>
#include <thread>

#ifdef NNGUI_SDL
    #include <SDL.h>
    #include <SDL_opengl.h>
#elif defined NNGUI_GLFW
    #if defined(__APPLE__)
        #define GLFW_INCLUDE_GLCOREARB
    #else
        #define GL_GLEXT_PROTOTYPES
    #endif
    #include <GLFW/glfw3.h>
    //#include <GL/glext.h>
#endif

#ifdef _WIN32
    #include <windows.h>
    #include <commdlg.h>
#else
    #include <locale.h>
    #include <signal.h>
    #include <sys/dir.h>
#endif

#define NVG_PI 3.14159265358979323846264338327f

#ifdef __APPLE__
#define SYSTEM_COMMAND_MOD GLFW_MOD_SUPER
#else
#define SYSTEM_COMMAND_MOD GLFW_MOD_CONTROL
#endif

#ifdef NNGUI_GLFW
  #ifdef __APPLE__
  #define SYSTEM_COMMAND_MOD GLFW_MOD_SUPER
  #else
  #define SYSTEM_COMMAND_MOD GLFW_MOD_CONTROL
  #endif

  #define MOUSE_BUTTON_LEFT GLFW_MOUSE_BUTTON_LEFT
  #define MOUSE_BUTTON_RIGHT GLFW_MOUSE_BUTTON_RIGHT
  #define MOUSE_BUTTON_PRESS GLFW_PRESS
  #define MOUSE_BUTTON_RELEASE GLFW_RELEASE
  #define KEYBOARD_KEY_DOWN GLFW_PRESS
  #define KEYBOARD_KEY_LEFT GLFW_KEY_LEFT
  #define KEYBOARD_KEY_LSHIFT GLFW_MOD_SHIFT
  #define KEYBOARD_KEY_RIGHT GLFW_KEY_RIGHT
  #define KEYBOARD_KEY_HOME GLFW_KEY_HOME
  #define KEYBOARD_KEY_END GLFW_KEY_END
  #define KEYBOARD_KEY_BACKSPACE GLFW_KEY_BACKSPACE
  #define KEYBOARD_KEY_DELETE GLFW_KEY_DELETE
  #define KEYBOARD_KEY_RETURN GLFW_KEY_ENTER
  #define KEYBOARD_KEY_RCTRL SYSTEM_COMMAND_MOD
  #define KEYBOARD_KEY_A GLFW_KEY_A
  #define KEYBOARD_KEY_C GLFW_KEY_C
  #define KEYBOARD_KEY_V GLFW_KEY_V
  #define KEYBOARD_KEY_X GLFW_KEY_X

  #define __getTime glfwGetTime
  #define __showWindow glfwShowWindow
  #define __hideWindow glfwHideWindow
  #define __setWindowTitle glfwSetWindowTitle
  #define __setWindowSize glfwSetWindowSize
  #define __getWindowSize glfwGetWindowSize
  #define __getFramebufferSize glfwGetFramebufferSize
#elif NNGUI_SDL
  #ifdef __APPLE__
  #define SYSTEM_COMMAND_MOD SDLK_APPLICATION
  #else
  #define SYSTEM_COMMAND_MOD SDLK_RCTRL
  #endif

  #define MOUSE_BUTTON_LEFT SDL_BUTTON_LEFT
  #define MOUSE_BUTTON_PRESS SDL_MOUSEBUTTONDOWN
  #define MOUSE_BUTTON_RELEASE SDL_MOUSEBUTTONUP
  #define KEYBOARD_KEY_DOWN SDL_KEYDOWN
  #define KEYBOARD_KEY_LEFT SDLK_LEFT
  #define KEYBOARD_KEY_LSHIFT SDLK_LSHIFT
  #define KEYBOARD_KEY_RIGHT SDLK_RIGHT
  #define KEYBOARD_KEY_HOME SDLK_HOME
  #define KEYBOARD_KEY_END SDLK_END
  #define KEYBOARD_KEY_BACKSPACE SDLK_BACKSPACE
  #define KEYBOARD_KEY_DELETE SDLK_DELETE
  #define KEYBOARD_KEY_RETURN SDLK_RETURN
  #define KEYBOARD_KEY_RCTRL SYSTEM_COMMAND_MOD
  #define KEYBOARD_KEY_A SDLK_a
  #define KEYBOARD_KEY_C SDLK_c
  #define KEYBOARD_KEY_V SDLK_v
  #define KEYBOARD_KEY_X SDLK_x
  #define __getTime SDL_GetTicks
  #define __showWindow SDL_ShowWindow
  #define __hideWindow SDL_HideWindow
  #define __setWindowTitle SDL_SetWindowTitle
  #define __setWindowSize SDL_SetWindowSize
  #define __getWindowSize SDL_GetWindowSize
  #define __getFramebufferSize SDL_GetWindowSize
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#endif

typedef struct NVGcontext NVGcontext;

struct NVGcolor {
    union {
        float rgba[4];
        struct {
            float r,g,b,a;
        };
    };
};
typedef struct NVGcolor NVGcolor;

struct NVGpaint {
    float xform[6];
    float extent[2];
    float radius;
    float feather;
    NVGcolor innerColor;
    NVGcolor outerColor;
    int image;
};
typedef struct NVGpaint NVGpaint;

enum NVGwinding {
    NVG_CCW = 1,			// Winding for solid shapes
    NVG_CW = 2,				// Winding for holes
};

enum NVGsolidity {
    NVG_SOLID = 1,			// CCW
    NVG_HOLE = 2,			// CW
};

enum NVGlineCap {
    NVG_BUTT,
    NVG_ROUND,
    NVG_SQUARE,
    NVG_BEVEL,
    NVG_MITER,
};

enum NVGalign {
    // Horizontal align
    NVG_ALIGN_LEFT 		= 1<<0,	// Default, align text horizontally to left.
    NVG_ALIGN_CENTER 	= 1<<1,	// Align text horizontally to center.
    NVG_ALIGN_RIGHT 	= 1<<2,	// Align text horizontally to right.
    // Vertical align
    NVG_ALIGN_TOP 		= 1<<3,	// Align text vertically to top.
    NVG_ALIGN_MIDDLE	= 1<<4,	// Align text vertically to middle.
    NVG_ALIGN_BOTTOM	= 1<<5,	// Align text vertically to bottom.
    NVG_ALIGN_BASELINE	= 1<<6, // Default, align text vertically to baseline.
};

struct NVGglyphPosition {
    const char* str;	// Position of the glyph in the input string.
    float x;			// The x-coordinate of the logical glyph position.
    float minx, maxx;	// The bounds of the glyph shape.
};
typedef struct NVGglyphPosition NVGglyphPosition;

struct NVGtextRow {
    const char* start;	// Pointer to the input text where the row starts.
    const char* end;	// Pointer to the input text where the row ends (one past the last character).
    const char* next;	// Pointer to the beginning of the next row.
    float width;		// Logical width of the row.
    float minx, maxx;	// Actual bounds of the row. Logical with and bounds can differ because of kerning and some parts over extending.
};
typedef struct NVGtextRow NVGtextRow;

enum NVGimageFlags {
    NVG_IMAGE_GENERATE_MIPMAPS	= 1<<0,     // Generate mipmaps during creation of the image.
    NVG_IMAGE_REPEATX			= 1<<1,		// Repeat image in X direction.
    NVG_IMAGE_REPEATY			= 1<<2,		// Repeat image in Y direction.
    NVG_IMAGE_FLIPY				= 1<<3,		// Flips (inverses) image in Y direction when rendered.
    NVG_IMAGE_PREMULTIPLIED		= 1<<4,		// Image data has premultiplied alpha.
};

void nvgBeginFrame(NVGcontext* ctx, int windowWidth, int windowHeight, float devicePixelRatio);
void nvgCancelFrame(NVGcontext* ctx);
void nvgEndFrame(NVGcontext* ctx);
NVGcolor nvgRGB(unsigned char r, unsigned char g, unsigned char b);
NVGcolor nvgRGBf(float r, float g, float b);
NVGcolor nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
NVGcolor nvgRGBAf(float r, float g, float b, float a);
NVGcolor nvgLerpRGBA(NVGcolor c0, NVGcolor c1, float u);
NVGcolor nvgTransRGBA(NVGcolor c0, unsigned char a);
NVGcolor nvgTransRGBAf(NVGcolor c0, float a);
NVGcolor nvgHSL(float h, float s, float l);
NVGcolor nvgHSLA(float h, float s, float l, unsigned char a);
void nvgSave(NVGcontext* ctx);
void nvgRestore(NVGcontext* ctx);
NVGcontext* nvgCreateX(bool debug);
void nvgDeleteX(NVGcontext*);
void nvgReset(NVGcontext* ctx);
void nvgStrokeColor(NVGcontext* ctx, NVGcolor color);
void nvgStrokePaint(NVGcontext* ctx, NVGpaint paint);
void nvgFillColor(NVGcontext* ctx, NVGcolor color);
void nvgFillPaint(NVGcontext* ctx, NVGpaint paint);
void nvgMiterLimit(NVGcontext* ctx, float limit);
void nvgStrokeWidth(NVGcontext* ctx, float size);
void nvgLineCap(NVGcontext* ctx, int cap);
void nvgLineJoin(NVGcontext* ctx, int join);
void nvgGlobalAlpha(NVGcontext* ctx, float alpha);
void nvgResetTransform(NVGcontext* ctx);
void nvgTransform(NVGcontext* ctx, float a, float b, float c, float d, float e, float f);
void nvgTranslate(NVGcontext* ctx, float x, float y);
void nvgRotate(NVGcontext* ctx, float angle);
void nvgSkewX(NVGcontext* ctx, float angle);
void nvgSkewY(NVGcontext* ctx, float angle);
void nvgScale(NVGcontext* ctx, float x, float y);
void nvgCurrentTransform(NVGcontext* ctx, float* xform);
void nvgTransformIdentity(float* dst);
void nvgTransformTranslate(float* dst, float tx, float ty);
void nvgTransformScale(float* dst, float sx, float sy);
void nvgTransformRotate(float* dst, float a);
void nvgTransformSkewX(float* dst, float a);
void nvgTransformSkewY(float* dst, float a);
void nvgTransformMultiply(float* dst, const float* src);
void nvgTransformPremultiply(float* dst, const float* src);
int nvgTransformInverse(float* dst, const float* src);
void nvgTransformPoint(float* dstx, float* dsty, const float* xform, float srcx, float srcy);
float nvgDegToRad(float deg);
float nvgRadToDeg(float rad);
int nvgCreateImage(NVGcontext* ctx, const char* filename, int imageFlags);
int nvgCreateImageMem(NVGcontext* ctx, int imageFlags, unsigned char* data, int ndata);
int nvgCreateImageRGBA(NVGcontext* ctx, int w, int h, int imageFlags, const unsigned char* data);
void nvgUpdateImage(NVGcontext* ctx, int image, const unsigned char* data);
void nvgImageSize(NVGcontext* ctx, int image, int* w, int* h);
void nvgDeleteImage(NVGcontext* ctx, int image);
NVGpaint nvgLinearGradient(NVGcontext* ctx, float sx, float sy, float ex, float ey,
                           NVGcolor icol, NVGcolor ocol);
NVGpaint nvgBoxGradient(NVGcontext* ctx, float x, float y, float w, float h,
                        float r, float f, NVGcolor icol, NVGcolor ocol);
NVGpaint nvgRadialGradient(NVGcontext* ctx, float cx, float cy, float inr, float outr,
                           NVGcolor icol, NVGcolor ocol);
NVGpaint nvgImagePattern(NVGcontext* ctx, float ox, float oy, float ex, float ey,
                         float angle, int image, float alpha);
void nvgScissor(NVGcontext* ctx, float x, float y, float w, float h);
void nvgIntersectScissor(NVGcontext* ctx, float x, float y, float w, float h);
void nvgResetScissor(NVGcontext* ctx);
void nvgBeginPath(NVGcontext* ctx);
void nvgMoveTo(NVGcontext* ctx, float x, float y);
void nvgLineTo(NVGcontext* ctx, float x, float y);
void nvgBezierTo(NVGcontext* ctx, float c1x, float c1y, float c2x, float c2y, float x, float y);
void nvgQuadTo(NVGcontext* ctx, float cx, float cy, float x, float y);
void nvgArcTo(NVGcontext* ctx, float x1, float y1, float x2, float y2, float radius);
void nvgClosePath(NVGcontext* ctx);
void nvgPathWinding(NVGcontext* ctx, int dir);
void nvgArc(NVGcontext* ctx, float cx, float cy, float r, float a0, float a1, int dir);
void nvgRect(NVGcontext* ctx, float x, float y, float w, float h);
void nvgRoundedRect(NVGcontext* ctx, float x, float y, float w, float h, float r);
void nvgEllipse(NVGcontext* ctx, float cx, float cy, float rx, float ry);
void nvgCircle(NVGcontext* ctx, float cx, float cy, float r);
void nvgFill(NVGcontext* ctx);
void nvgStroke(NVGcontext* ctx);
int nvgCreateFont(NVGcontext* ctx, const char* name, const char* filename);
int nvgCreateFontMem(NVGcontext* ctx, const char* name, unsigned char* data, int ndata, int freeData);
int nvgFindFont(NVGcontext* ctx, const char* name);
void nvgFontSize(NVGcontext* ctx, float size);
void nvgFontBlur(NVGcontext* ctx, float blur);
void nvgTextLetterSpacing(NVGcontext* ctx, float spacing);
void nvgTextLineHeight(NVGcontext* ctx, float lineHeight);
void nvgTextAlign(NVGcontext* ctx, int align);
void nvgFontFaceId(NVGcontext* ctx, int font);
void nvgFontFace(NVGcontext* ctx, const char* font);
float nvgText(NVGcontext* ctx, float x, float y, const char* string, const char* end);
void nvgTextBox(NVGcontext* ctx, float x, float y, float breakRowWidth, const char* string, const char* end);
float nvgTextBounds(NVGcontext* ctx, float x, float y, const char* string, const char* end, float* bounds);
void nvgTextBoxBounds(NVGcontext* ctx, float x, float y, float breakRowWidth, const char* string, const char* end, float* bounds);
int nvgTextGlyphPositions(NVGcontext* ctx, float x, float y, const char* string, const char* end, NVGglyphPosition* positions, int maxPositions);
void nvgTextMetrics(NVGcontext* ctx, float* ascender, float* descender, float* lineh);
int nvgTextBreakLines(NVGcontext* ctx, const char* string, const char* end, float breakRowWidth, NVGtextRow* rows, int maxRows);

//
// Internal Render API
enum NVGtexture {
    NVG_TEXTURE_ALPHA = 0x01,
    NVG_TEXTURE_RGBA = 0x02,
};

struct NVGscissor {
    float xform[6];
    float extent[2];
};
typedef struct NVGscissor NVGscissor;

struct NVGvertex {
    float x,y,u,v;
};
typedef struct NVGvertex NVGvertex;

struct NVGpath {
    int first;
    int count;
    unsigned char closed;
    int nbevel;
    NVGvertex* fill;
    int nfill;
    NVGvertex* stroke;
    int nstroke;
    int winding;
    int convex;
};
typedef struct NVGpath NVGpath;

struct NVGparams {
    void* userPtr;
    int edgeAntiAlias;
    int (*renderCreate)(void* uptr);
    int (*renderCreateTexture)(void* uptr, int type, int w, int h, int imageFlags, const unsigned char* data);
    int (*renderDeleteTexture)(void* uptr, int image);
    int (*renderUpdateTexture)(void* uptr, int image, int x, int y, int w, int h, const unsigned char* data);
    int (*renderGetTextureSize)(void* uptr, int image, int* w, int* h);
    void (*renderViewport)(void* uptr, int width, int height);
    void (*renderCancel)(void* uptr);
    void (*renderFlush)(void* uptr);
    void (*renderFill)(void* uptr, NVGpaint* paint, NVGscissor* scissor, float fringe, const float* bounds, const NVGpath* paths, int npaths);
    void (*renderStroke)(void* uptr, NVGpaint* paint, NVGscissor* scissor, float fringe, float strokeWidth, const NVGpath* paths, int npaths);
    void (*renderTriangles)(void* uptr, NVGpaint* paint, NVGscissor* scissor, const NVGvertex* verts, int nverts);
    void (*renderDelete)(void* uptr);
};
typedef struct NVGparams NVGparams;

// Constructor and destructor, called by the render back-end.
NVGcontext* nvgCreateInternal(NVGparams* params);
void nvgDeleteInternal(NVGcontext* ctx);
NVGparams* nvgInternalParams(NVGcontext* ctx);

// Debug function to dump cached path data.
void nvgDebugDumpPathCache(NVGcontext* ctx);

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#define NVG_NOTUSED(v) for (;;) { (void)(1 ? (void)0 : ( (void)(v) ) ); break; }
#if defined(NNGUI_SDL)
#ifndef GL_GLEXT_PROTOTYPES
#ifdef WIN32
  PFNGLACTIVETEXTUREPROC glActiveTexture;
#else
  typedef void (GLAPIENTRY *PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint* arrays);
  typedef void (GLAPIENTRY *PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint* arrays);
  typedef void (GLAPIENTRY * PFNGLBINDVERTEXARRAYPROC) (GLuint array);
  typedef GLuint (GLAPIENTRY * PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint program, const GLchar* uniformBlockName);
  typedef void (GLAPIENTRY * PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
  typedef void (GLAPIENTRY * PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
  typedef void (GLAPIENTRY * PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
  typedef void (GLAPIENTRY * PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
  typedef void (GLAPIENTRY * PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint* arrays);
  typedef void (GLAPIENTRY * PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint* renderbuffers);
  typedef void (GLAPIENTRY * PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
  typedef void (GLAPIENTRY * PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint* framebuffers);
  typedef void (GLAPIENTRY * PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
  typedef GLenum (GLAPIENTRY * PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
  typedef void (GLAPIENTRY * PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, const GLuint* renderbuffers);
  typedef void (GLAPIENTRY * PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
  typedef void (GLAPIENTRY * PFNGLGENERATEMIPMAPPROC) (GLenum target);
  typedef void (GLAPIENTRY * PFNGLBINDBUFFERRANGEPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
#endif
  #ifndef GL_UNIFORM_BUFFER
  #define GL_UNIFORM_BUFFER 0x8A11
  #endif

  #ifndef GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT
  #define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
  #endif

  PFNGLCREATESHADERPROC glCreateShader;
  PFNGLSHADERSOURCEPROC glShaderSource ;
  PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv ;
  PFNGLCOMPILESHADERPROC glCompileShader ;
  PFNGLGETSHADERIVPROC glGetShaderiv ;
  PFNGLUSEPROGRAMPROC glUseProgram ;
  PFNGLUNIFORM1IPROC glUniform1i ;
  PFNGLUNIFORM1FPROC glUniform1f ;
  PFNGLUNIFORM2IPROC glUniform2i ;
  PFNGLUNIFORM2FPROC glUniform2f ;
  PFNGLUNIFORM3FPROC glUniform3f ;
  PFNGLUNIFORM4FPROC glUniform4f ;
  PFNGLUNIFORM4FVPROC glUniform4fv ;
  PFNGLCREATEPROGRAMPROC glCreateProgram ;
  PFNGLATTACHSHADERPROC glAttachShader ;
  PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog ;
  PFNGLLINKPROGRAMPROC glLinkProgram ;
  PFNGLGETPROGRAMIVPROC glGetProgramiv ;
  PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog ;
  PFNGLGENVERTEXARRAYSPROC glGenVertexArrays ;
  PFNGLBINDVERTEXARRAYPROC glBindVertexArray ;
  PFNGLBINDBUFFERPROC glBindBuffer ;
  PFNGLGETATTRIBLOCATIONPROC  glGetAttribLocation ;
  PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation ;
  PFNGLGENBUFFERSPROC  glGenBuffers ;
  PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
  PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
  PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;
  PFNGLBUFFERDATAPROC  glBufferData ;
  PFNGLDISABLEVERTEXATTRIBARRAYPROC  glDisableVertexAttribArray ;
  PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray ;
  PFNGLGETBUFFERSUBDATAPROC  glGetBufferSubData ;
  PFNGLVERTEXATTRIBPOINTERPROC  glVertexAttribPointer ;
  PFNGLDELETEBUFFERSPROC  glDeleteBuffers ;
  PFNGLBINDFRAMEBUFFERPROC  glBindFramebuffer ;
  PFNGLBINDRENDERBUFFERPROC  glBindRenderbuffer ;
  PFNGLRENDERBUFFERSTORAGEPROC  glRenderbufferStorage ;
  PFNGLDELETEVERTEXARRAYSPROC  glDeleteVertexArrays ;
  PFNGLDELETEPROGRAMPROC  glDeleteProgram ;
  PFNGLDELETESHADERPROC  glDeleteShader ;
  PFNGLGENRENDERBUFFERSPROC  glGenRenderbuffers ;
  PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC  glRenderbufferStorageMultisample ;
  PFNGLGENFRAMEBUFFERSPROC  glGenFramebuffers ;
  PFNGLFRAMEBUFFERRENDERBUFFERPROC  glFramebufferRenderbuffer ;
  PFNGLCHECKFRAMEBUFFERSTATUSPROC  glCheckFramebufferStatus ;
  PFNGLDELETERENDERBUFFERSPROC  glDeleteRenderbuffers ;
  PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer ;

  PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
  PFNGLBINDBUFFERRANGEPROC glBindBufferRange;
  PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate;
  PFNGLUNIFORM2FVPROC glUniform2fv;
#endif
#endif

#if defined(NNGUI_GLFW)

#if !defined(APIENTRY)
#  if defined(_WIN32)
#    define APIENTRY _stdcall
#  else
#    define APIENTRY
#  endif
#endif

#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_GENERATE_MIPMAP                0x8191
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_INCR_WRAP 0x8507
#define GL_DECR_WRAP 0x8508
#define GL_TEXTURE0 0x84C0
#define GL_ARRAY_BUFFER 0x8892
#define GL_STREAM_DRAW 0x88E0

typedef char GLchar;
typedef unsigned int GLenum;
typedef ptrdiff_t GLsizeiptr;

#ifdef WIN3
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC)(GLenum type);
PFNGLCREATESHADERPROC glCreateShader = nullptr;
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;

typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;

typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC)();
PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;

typedef void (APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;

typedef void (APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint shader);
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;

typedef void (APIENTRYP PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint* params);
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;

typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
PFNGLATTACHSHADERPROC glAttachShader = nullptr;

typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar* name);
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;

typedef void (APIENTRYP PFNGLLINKPROGRAMPROC)(GLuint program);
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;

typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint* params);
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;

typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC)(GLuint program);
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;

typedef void (APIENTRYP PFNGLDELETESHADERPROC)(GLuint shader);
PFNGLDELETESHADERPROC glDeleteShader = nullptr;

typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar* name);
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;

typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
PFNGLGENBUFFERSPROC glGenBuffers = nullptr;

typedef void (APIENTRYP PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat* value);
PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;

typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = nullptr;

typedef void (APIENTRYP PFNGLUSEPROGRAMPROC)(GLuint program);
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;

typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum texture);
PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;

typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;

typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
PFNGLBUFFERDATAPROC glBufferData = nullptr;

typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;

typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;

typedef void (APIENTRYP PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
PFNGLUNIFORM1IPROC glUniform1i = nullptr;

typedef void (APIENTRYP PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat* value);
PFNGLUNIFORM2FVPROC glUniform2fv = nullptr;

typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;

typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint* buffers);
PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
#endif

#endif

NAMESPACE_BEGIN(nngui)

extern uint8_t entypo_ttf[];
extern uint32_t entypo_ttf_size;

extern uint8_t roboto_bold_ttf[];
extern uint32_t roboto_bold_ttf_size;

extern uint8_t roboto_regular_ttf[];
extern uint32_t roboto_regular_ttf_size;
    
Popup::Popup(Widget *parent, Window *parentWindow)
    : Window(parent, ""), mParentWindow(parentWindow),
      mAnchorPos(Vec2i::Zero()), mAnchorHeight(30) {
}

void Popup::performLayout(NVGcontext *ctx) {
    if (mLayout || mChildren.size() != 1) {
        Widget::performLayout(ctx);
    } else {
        mChildren[0]->setPosition(Vec2i::Zero());
        mChildren[0]->setSize(mSize);
        mChildren[0]->performLayout(ctx);
    }
}

void Popup::refreshRelativePlacement() {
    mParentWindow->refreshRelativePlacement();
    mVisible &= mParentWindow->visibleRecursive();
    mPos = mParentWindow->position() + mAnchorPos - Vec2i(0, mAnchorHeight);
}

void Popup::draw(NVGcontext* ctx) {
    refreshRelativePlacement();

    if (!mVisible)
        return;

    int ds = mTheme->mWindowDropShadowSize, cr = mTheme->mWindowCornerRadius;

    /* Draw a drop shadow */
    NVGpaint shadowPaint = nvgBoxGradient(
        ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr*2, ds*2,
        mTheme->mDropShadow, mTheme->mTransparent);

    nvgBeginPath(ctx);
    nvgRect(ctx, mPos.x()-ds,mPos.y()-ds, mSize.x()+2*ds, mSize.y()+2*ds);
    nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr);
    nvgPathWinding(ctx, NVG_HOLE);
    nvgFillPaint(ctx, shadowPaint);
    nvgFill(ctx);

    /* Draw window */
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr);

    nvgMoveTo(ctx, mPos.x()-15,mPos.y()+mAnchorHeight);
    nvgLineTo(ctx, mPos.x()+1,mPos.y()+mAnchorHeight-15);
    nvgLineTo(ctx, mPos.x()+1,mPos.y()+mAnchorHeight+15);

    nvgFillColor(ctx, mTheme->mWindowPopup);
    nvgFill(ctx);

    Widget::draw(ctx);
}

/***************************** Context menu **************************************/


ContextMenu::ContextMenu(Widget *parent)
 : Window(parent)
{

}

/***************************** Slider *********************************************/

Slider::Slider(Widget *parent)
    : Widget(parent), mValue(0.0f), mHighlightedRange(std::make_pair(0.f, 0.f)) {
    mHighlightColor = Color(255, 80, 80, 70);
}

Vec2i Slider::preferredSize(NVGcontext *) const {
    return Vec2i(70, 12);
}

bool Slider::mouseDragEvent(const Vec2i &p, const Vec2i & /* rel */,
                            int /* button */, int /* modifiers */) {
    if (!mEnabled)
        return false;
    mValue = std::min(std::max((p.x() - mPos.x()) / (float) mSize.x(), (float) 0.0f), (float) 1.0f);
    if (mCallback)
        mCallback(mValue);
    return true;
}

bool Slider::mouseButtonEvent(const Vec2i &p, int /* button */, bool down, int /* modifiers */) {
    if (!mEnabled)
        return false;
    mValue = std::min(std::max((p.x() - mPos.x()) / (float) mSize.x(), (float) 0.0f), (float) 1.0f);
    if (mCallback)
        mCallback(mValue);
    if (mFinalCallback && !down)
        mFinalCallback(mValue);
    return true;
}

void Slider::draw(NVGcontext* ctx) {
    Vec2f center = mPos.cast<float>() + mSize.cast<float>() * 0.5f;
    Vec2f knobPos(mPos.x() + mValue * mSize.x(), center.y() + 0.5f);
    float kr = (int)(mSize.y()*0.5f);
    NVGpaint bg = nvgBoxGradient(ctx,
        mPos.x(), center.y() - 3 + 1, mSize.x(), 6, 3, 3, Color(0, mEnabled ? 32 : 10), Color(0, mEnabled ? 128 : 210));

    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x(), center.y() - 3 + 1, mSize.x(), 6, 2);
    nvgFillPaint(ctx, bg);
    nvgFill(ctx);

    if (mHighlightedRange.second != mHighlightedRange.first) {
        nvgBeginPath(ctx);
        nvgRoundedRect(ctx, mPos.x() + mHighlightedRange.first * mSize.x(), center.y() - 3 + 1, mSize.x() * (mHighlightedRange.second-mHighlightedRange.first), 6, 2);
        nvgFillColor(ctx, mHighlightColor);
        nvgFill(ctx);
    }

    NVGpaint knobShadow = nvgRadialGradient(ctx,
        knobPos.x(), knobPos.y(), kr-3, kr+3, Color(0, 64), mTheme->mTransparent);

    nvgBeginPath(ctx);
    nvgRect(ctx, knobPos.x() - kr - 5, knobPos.y() - kr - 5, kr*2+10, kr*2+10+3);
    nvgCircle(ctx, knobPos.x(), knobPos.y(), kr);
    nvgPathWinding(ctx, NVG_HOLE);
    nvgFillPaint(ctx, knobShadow);
    nvgFill(ctx);

    NVGpaint knob = nvgLinearGradient(ctx,
        mPos.x(), center.y() - kr, mPos.x(), center.y() + kr,
        mTheme->mBorderLight, mTheme->mBorderMedium);
    NVGpaint knobReverse = nvgLinearGradient(ctx,
        mPos.x(), center.y() - kr, mPos.x(), center.y() + kr,
        mTheme->mBorderMedium,
        mTheme->mBorderLight);

    nvgBeginPath(ctx);
    nvgCircle(ctx, knobPos.x(), knobPos.y(), kr*mKnobRadiusKoeff.outter);
    nvgStrokeColor(ctx, mTheme->mBorderDark);
    nvgFillPaint(ctx, knob);
    nvgStroke(ctx);
    nvgFill(ctx);
    nvgBeginPath(ctx);
    nvgCircle(ctx, knobPos.x(), knobPos.y(), kr*mKnobRadiusKoeff.inner);
    nvgFillColor(ctx, Color(150, mEnabled ? 255 : 100));
    nvgStrokePaint(ctx, knobReverse);
    nvgStroke(ctx);
    nvgFill(ctx);
}

/****************************** Button ***********************************************/

Button::Button(Widget *parent, const std::string &caption, int icon)
    : Widget(parent), mCaption(caption), mIcon(icon),
      mIconPosition(IconPosition::LeftCentered), mPushed(false),
      mFlags(NormalButton), mBackgroundColor(Color(0, 0)),
      mTextColor(Color(0, 0)) { }

Vec2i Button::preferredSize(NVGcontext *ctx) const {
    int fontSize = mFontSize == -1 ? mTheme->mButtonFontSize : mFontSize;
    nvgFontSize(ctx, fontSize);
    nvgFontFace(ctx, "sans-bold");
    float tw = nvgTextBounds(ctx, 0,0, mCaption.c_str(), nullptr, nullptr);
    float iw = 0.0f, ih = fontSize;

    if (mIcon) {
        if (nvgIsFontIcon(mIcon)) {
            ih *= 1.5f;
            nvgFontFace(ctx, "icons");
            nvgFontSize(ctx, ih);
            iw = nvgTextBounds(ctx, 0, 0, __nngui_utf8(mIcon).data(), nullptr, nullptr)
                + mSize.y() * 0.15f;
        } else {
            int w, h;
            ih *= 0.9f;
            nvgImageSize(ctx, mIcon, &w, &h);
            iw = w * ih / h;
        }
    }
    return Vec2i((int)(tw + iw) + 20, fontSize + 10);
}

bool Button::mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers)
{
    Widget::mouseButtonEvent(p, button, down, modifiers);
    /* Temporarily increase the reference count of the button in case the
       button causes the parent window to be destructed */
    ref<Button> self = this;

    if (button == MOUSE_BUTTON_LEFT && mEnabled) {
        bool pushedBackup = mPushed;
        if (down) {
            if (mFlags & RadioButton) {
                if (mButtonGroup.empty()) {
                    for (auto widget : parent()->children()) {
                        Button *b = dynamic_cast<Button *>(widget);
                        if (b != this && b && (b->flags() & RadioButton) && b->mPushed) {
                            b->mPushed = false;
                            if (b->mChangeCallback)
                                b->mChangeCallback(false);
                        }
                    }
                } else {
                    for (auto b : mButtonGroup) {
                        if (b != this && (b->flags() & RadioButton) && b->mPushed) {
                            b->mPushed = false;
                            if (b->mChangeCallback)
                                b->mChangeCallback(false);
                        }
                    }
                }
            }
            if (mFlags & PopupButton) {
                for (auto widget : parent()->children()) {
                    Button *b = dynamic_cast<Button *>(widget);
                    if (b != this && b && (b->flags() & PopupButton) && b->mPushed) {
                        b->mPushed = false;
                        if(b->mChangeCallback)
                            b->mChangeCallback(false);
                    }
                }
            }
            if (mFlags & ToggleButton)
                mPushed = !mPushed;
            else
                mPushed = true;
        } else if (mPushed) {
            if (contains(p) && mCallback)
                mCallback();
            if (mFlags & NormalButton)
                mPushed = false;
        }
        if (pushedBackup != mPushed && mChangeCallback)
            mChangeCallback(mPushed);

        return true;
    }
    return false;
}

void Button::draw(NVGcontext *ctx) {
    Widget::draw(ctx);

    NVGcolor gradTop = mTheme->mButtonGradientTopUnfocused;
    NVGcolor gradBot = mTheme->mButtonGradientBotUnfocused;

    if (mPushed) {
        gradTop = mTheme->mButtonGradientTopPushed;
        gradBot = mTheme->mButtonGradientBotPushed;
    } else if (mMouseFocus && mEnabled) {
        gradTop = mTheme->mButtonGradientTopFocused;
        gradBot = mTheme->mButtonGradientBotFocused;
    }

    nvgBeginPath(ctx);

    nvgRoundedRect(ctx, mPos.x() + 1, mPos.y() + 1.0f, mSize.x() - 2,
                   mSize.y() - 2, mTheme->mButtonCornerRadius - 1);

    if (mBackgroundColor.a() != 0) {
        nvgFillColor(ctx, mBackgroundColor.withAlpha(1.f));
        nvgFill(ctx);
        if (mPushed) {
            gradTop.a = gradBot.a = 0.8f;
        } else {
            double v = 1 - mBackgroundColor.a();
            gradTop.a = gradBot.a = mEnabled ? v : v * .5f + .5f;
        }
    }

    NVGpaint bg = nvgLinearGradient(ctx, mPos.x(), mPos.y(), mPos.x(),
                                    mPos.y() + mSize.y(), gradTop, gradBot);

    nvgFillPaint(ctx, bg);
    nvgFill(ctx);

    if (mTheme->mButtonHaveLigthBorder)
    {
        nvgBeginPath(ctx);
        nvgRoundedRect(ctx, mPos.x() + 0.5f, mPos.y() + (mPushed ? 0.5f : 1.5f), mSize.x() - 1,
                       mSize.y() - 1 - (mPushed ? 0.0f : 1.0f), mTheme->mButtonCornerRadius);
        nvgStrokeColor(ctx, mTheme->mBorderLight);
        nvgStroke(ctx);
    }

    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x() + 0.5f, mPos.y() + 0.5f, mSize.x() - 1,
                   mSize.y() - 2, mTheme->mButtonCornerRadius);
    nvgStrokeColor(ctx, mTheme->mBorderDark);
    nvgStroke(ctx);

    int fontSize = mFontSize == -1 ? mTheme->mButtonFontSize : mFontSize;
    nvgFontSize(ctx, fontSize);
    nvgFontFace(ctx, "sans-bold");
    float tw = nvgTextBounds(ctx, 0,0, mCaption.c_str(), nullptr, nullptr);

    Vec2f center = mPos.cast<float>() + mSize.cast<float>() * 0.5f;
    Vec2f textPos(center.x() - tw * 0.5f, center.y() - 1);
    NVGcolor textColor =
        mTextColor.a() == 0 ? mTheme->mTextColor : mTextColor;

    if (!mEnabled)
        textColor = mTheme->mDisabledTextColor;

    if (mIcon) {
        auto icon = __nngui_utf8(mIcon);

        float iw, ih = fontSize;
        if (nvgIsFontIcon(mIcon)) {
            ih *= 1.5f;
            nvgFontSize(ctx, ih);
            nvgFontFace(ctx, "icons");
            iw = nvgTextBounds(ctx, 0, 0, icon.data(), nullptr, nullptr);
        } else {
            int w, h;
            ih *= 0.9f;
            nvgImageSize(ctx, mIcon, &w, &h);
            iw = w * ih / h;
        }
        if (mCaption != "")
            iw += mSize.y() * 0.15f;
        nvgFillColor(ctx, textColor);
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        Vec2f iconPos = center;
        iconPos.ry() -= 1;

        if (mIconPosition == IconPosition::LeftCentered) {
            iconPos.rx() -= (tw + iw) * 0.5f;
            textPos.rx() += iw * 0.5f;
        } else if (mIconPosition == IconPosition::RightCentered) {
            textPos.rx() -= iw * 0.5f;
            iconPos.rx() += tw * 0.5f;
        } else if (mIconPosition == IconPosition::Left) {
            iconPos.rx() = mPos.x() + 8;
        } else if (mIconPosition == IconPosition::Right) {
            iconPos.rx() = mPos.x() + mSize.x() - iw - 8;
        }

        if (nvgIsFontIcon(mIcon)) {
            nvgText(ctx, iconPos.x(), iconPos.y()+1, icon.data(), nullptr);
        } else {
            NVGpaint imgPaint = nvgImagePattern(ctx,
                    iconPos.x(), iconPos.y() - ih/2, iw, ih, 0, mIcon, mEnabled ? 0.5f : 0.25f);

            nvgFillPaint(ctx, imgPaint);
            nvgFill(ctx);
        }
    }

    nvgFontSize(ctx, fontSize);
    nvgFontFace(ctx, "sans-bold");
    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    nvgFillColor(ctx, mTheme->mTextColorShadow);
    nvgText(ctx, textPos.x(), textPos.y(), mCaption.c_str(), nullptr);
    nvgFillColor(ctx, textColor);
    nvgText(ctx, textPos.x(), textPos.y() + 1, mCaption.c_str(), nullptr);
}

Button::Button(Widget* parent, const std::string& caption,
               const std::function<void ()>& callback, int icon)
  : Button( parent, caption, icon )
{
  setCallback( callback );
}

/******************************** PopupButton **********************************************/

PopupButton::PopupButton(Widget *parent, const std::string &caption,
                         int buttonIcon, int chevronIcon)
    : Button(parent, caption, buttonIcon), mChevronIcon(chevronIcon)
{
    setFlags(Flags::ToggleButton | Flags::PopupButton);

    Window *parentWindow = window();
    mPopup = &parentWindow->parent()->add<Popup>(window());
    mPopup->setSize(Vec2i(320, 250));
}

Vec2i PopupButton::preferredSize(NVGcontext *ctx) const {
    return Button::preferredSize(ctx) + Vec2i(15, 0);
}

void PopupButton::draw(NVGcontext* ctx) {
    if (!mEnabled && mPushed)
        mPushed = false;

    mPopup->setVisible(mPushed);
    Button::draw(ctx);

    if (mChevronIcon) {
        auto icon = __nngui_utf8(mChevronIcon);
        NVGcolor textColor =
            mTextColor.a() == 0 ? mTheme->mTextColor : mTextColor;

        nvgFontSize(ctx, (mFontSize < 0 ? mTheme->mButtonFontSize : mFontSize) * 1.5f);
        nvgFontFace(ctx, "icons");
        nvgFillColor(ctx, mEnabled ? textColor : mTheme->mDisabledTextColor);
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);

        float iw = nvgTextBounds(ctx, 0, 0, icon.data(), nullptr, nullptr);
        Vec2f iconPos(mPos.x() + mSize.x() - iw - 8,
                         mPos.y() + mSize.y() * 0.5f - 1);

        nvgText(ctx, iconPos.x(), iconPos.y(), icon.data(), nullptr);
    }
}

void PopupButton::performLayout(NVGcontext *ctx) {
    Widget::performLayout(ctx);

    const Window *parentWindow = window();

    mPopup->setAnchorPos(Vec2i(parentWindow->width() + 15,
        absolutePosition().y() - parentWindow->position().y() + mSize.y() /2));
}

/**************************************** Checkbox ***********************************/

CheckBox::CheckBox(Widget *parent, const std::string &caption,
                   const std::function<void(bool) > &callback)
    : Widget(parent), mCaption(caption), mPushed(false), mChecked(false),
      mCallback(callback) { }

bool CheckBox::mouseButtonEvent(const Vec2i &p, int button, bool down,
                                int modifiers)
{
    Widget::mouseButtonEvent(p, button, down, modifiers);
    if (!mEnabled)
        return false;

    if (button == MOUSE_BUTTON_LEFT )
    {
        if (down)
        {
            mPushed = true;
        }
        else if (mPushed)
        {
            if (contains(p))
            {
                mChecked = !mChecked;
                if (mCallback)
                    mCallback(mChecked);
            }
            mPushed = false;
        }
        return true;
    }
    return false;
}

Vec2i CheckBox::preferredSize(NVGcontext *ctx) const {
    if (mFixedSize != Vec2i::Zero())
        return mFixedSize;
    nvgFontSize(ctx, fontSize());
    nvgFontFace(ctx, "sans");
    return Vec2i(
        nvgTextBounds(ctx, 0, 0, mCaption.c_str(), nullptr, nullptr) +
            1.7f * fontSize(),
        fontSize() * 1.3f);
}

void CheckBox::draw(NVGcontext *ctx) {
    Widget::draw(ctx);

    nvgFontSize(ctx, fontSize());
    nvgFontFace(ctx, "sans");
    nvgFillColor(ctx,
                 mEnabled ? mTheme->mTextColor : mTheme->mDisabledTextColor);
    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    nvgText(ctx, mPos.x() + 1.2f * mSize.y() + 5, mPos.y() + mSize.y() * 0.5f,
            mCaption.c_str(), nullptr);

    NVGpaint bg = nvgBoxGradient(ctx, mPos.x() + 1.5f, mPos.y() + 1.5f,
                                 mSize.y() - 2.0f, mSize.y() - 2.0f, 3, 3,
                                 mPushed ? Color(0, 100) : Color(0, 32),
                                 Color(0, 0, 0, 180));

    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x() + 1.0f, mPos.y() + 1.0f, mSize.y() - 2.0f,
                   mSize.y() - 2.0f, 3);
    nvgFillPaint(ctx, bg);
    nvgFill(ctx);

    if (mChecked) {
        nvgFontSize(ctx, 1.8 * mSize.y());
        nvgFontFace(ctx, "icons");
        nvgFillColor(ctx, mEnabled ? mTheme->mIconColor
                                   : mTheme->mDisabledTextColor);
        nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
        nvgText(ctx, mPos.x() + mSize.y() * 0.5f + 1,
                mPos.y() + mSize.y() * 0.5f, __nngui_utf8(ENTYPO_ICON_CHECK).data(),
                nullptr);
    }
}

/********************************* MessageDialog **********************************/

MessageDialog::MessageDialog(Widget *parent, Type type, const std::string &title,
              const std::string &message,
              const std::string &buttonText,
              const std::string &altButtonText, bool altButton) : Window(parent, title)
{
    setLayout(new BoxLayout(Orientation::Vertical,
                            Alignment::Middle, 10, 10));
    setModal(true);

    Widget *panel1 = new Widget(this);
    panel1->setLayout(new BoxLayout(Orientation::Horizontal,
                                    Alignment::Middle, 10, 15));
    int icon = 0;
    switch (type) {
        case Type::Information: icon = ENTYPO_ICON_CIRCLED_INFO; break;
        case Type::Question: icon = ENTYPO_ICON_CIRCLED_HELP; break;
        case Type::Warning: icon = ENTYPO_ICON_WARNING; break;
    }
    Label *iconLabel = new Label(panel1, std::string(__nngui_utf8(icon).data()), "icons");
    iconLabel->setFontSize(50);
    mMessageLabel = new Label(panel1, message);
    mMessageLabel->setFixedWidth(200);
    Widget *panel2 = new Widget(this);
    panel2->setLayout(new BoxLayout(Orientation::Horizontal,
                                    Alignment::Middle, 0, 15));

    if (altButton) {
        Button *button = new Button(panel2, altButtonText, ENTYPO_ICON_CIRCLED_CROSS);
        button->setCallback([&] { if (mCallback) mCallback(1); dispose(); });
    }
    Button *button = new Button(panel2, buttonText, ENTYPO_ICON_CHECK);
    button->setCallback([&] { if (mCallback) mCallback(0); dispose(); });
    center();
    requestFocus();
}

/**************************************** Window *****************************************/

Window::Window(Widget *parent, const std::string &title)
    : Widget(parent), mTitle(title), mButtonPanel(nullptr), mModal(false), mDrag(false) { }

Vec2i Window::preferredSize(NVGcontext *ctx) const
{
    if (mButtonPanel)
        mButtonPanel->setVisible(false);
    Vec2i result = Widget::preferredSize(ctx);
    if (mButtonPanel)
        mButtonPanel->setVisible(true);

    nvgFontSize(ctx, 18.0f);
    nvgFontFace(ctx, "sans-bold");
    float bounds[4];
    nvgTextBounds(ctx, 0, 0, mTitle.c_str(), nullptr, bounds);

    return result.cwiseMax(bounds[2]-bounds[0] + 20, bounds[3]-bounds[1]);
}

Widget *Window::buttonPanel() {
    if (!mButtonPanel) {
        mButtonPanel = new Widget(this);
        mButtonPanel->setLayout(new BoxLayout(Orientation::Horizontal, Alignment::Middle, 0, 4));
    }
    return mButtonPanel;
}

void Window::performLayout(NVGcontext *ctx)
{
    if (!mButtonPanel) {
        Widget::performLayout(ctx);
    } else {
        mButtonPanel->setVisible(false);
        Widget::performLayout(ctx);
        for (auto w : mButtonPanel->children()) {
            w->setFixedSize(Vec2i(22, 22));
            w->setFontSize(15);
        }
        mButtonPanel->setVisible(true);
        mButtonPanel->setSize(Vec2i(width(), 22));
        mButtonPanel->setPosition(Vec2i(width() - (mButtonPanel->preferredSize(ctx).x() + 5), 3));
        mButtonPanel->performLayout(ctx);
    }
}

void Window::draw(NVGcontext *ctx) {
    int ds = mTheme->mWindowDropShadowSize, cr = mTheme->mWindowCornerRadius;
    int hh = mTheme->mWindowHeaderHeight;

    /* Draw window */
    nvgSave(ctx);
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr);

    nvgFillColor(ctx, mMouseFocus ? mTheme->mWindowFillFocused
                                  : mTheme->mWindowFillUnfocused);
    nvgFill(ctx);

    /* Draw a drop shadow */
    NVGpaint shadowPaint = nvgBoxGradient(
        ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr*2, ds*2,
        mTheme->mDropShadow, mTheme->mTransparent);

    nvgBeginPath(ctx);
    nvgRect(ctx, mPos.x()-ds,mPos.y()-ds, mSize.x()+2*ds, mSize.y()+2*ds);
    nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr);
    nvgPathWinding(ctx, NVG_HOLE);
    nvgFillPaint(ctx, shadowPaint);
    nvgFill(ctx);

    if (!mTitle.empty()) {
        /* Draw header */
        NVGpaint headerPaint = nvgLinearGradient(
            ctx, mPos.x(), mPos.y(), mPos.x(),
            mPos.y() + hh,
            mTheme->mWindowHeaderGradientTop,
            mTheme->mWindowHeaderGradientBot);

        nvgBeginPath(ctx);
        nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), hh, cr);

        nvgFillPaint(ctx, headerPaint);
        nvgFill(ctx);

        nvgBeginPath(ctx);
        nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), hh, cr);
        nvgStrokeColor(ctx, mTheme->mWindowHeaderSepTop);
        nvgScissor(ctx, mPos.x(), mPos.y(), mSize.x(), 0.5f);
        nvgStroke(ctx);
        nvgResetScissor(ctx);

        nvgBeginPath(ctx);
        nvgMoveTo(ctx, mPos.x() + 0.5f, mPos.y() + hh - 1.5f);
        nvgLineTo(ctx, mPos.x() + mSize.x() - 0.5f, mPos.y() + hh - 1.5);
        nvgStrokeColor(ctx, mTheme->mWindowHeaderSepBot);
        nvgStroke(ctx);

        nvgFontSize(ctx, 18.0f);
        nvgFontFace(ctx, "sans-bold");
        nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

        nvgFontBlur(ctx, 2);
        nvgFillColor(ctx, mTheme->mDropShadow);
        nvgText(ctx, mPos.x() + mSize.x() / 2,
                mPos.y() + hh / 2, mTitle.c_str(), nullptr);

        nvgFontBlur(ctx, 0);
        nvgFillColor(ctx, mFocused ? mTheme->mWindowTitleFocused
                                   : mTheme->mWindowTitleUnfocused);
        nvgText(ctx, mPos.x() + mSize.x() / 2, mPos.y() + hh / 2 - 1,
                mTitle.c_str(), nullptr);
    }

    nvgRestore(ctx);
    Widget::draw(ctx);
}

void Window::dispose() {
    Widget *widget = this;
    while (widget->parent())
        widget = widget->parent();
    ((Screen *) widget)->disposeWindow(this);
}

void Window::center() {
    Widget *widget = this;
    while (widget->parent())
        widget = widget->parent();
    ((Screen *) widget)->centerWindow(this);
}

bool Window::mouseDragEvent(const Vec2i &, const Vec2i &rel,
                            int button, int /* modifiers */) {
    if (mDrag && (button & (1 << MOUSE_BUTTON_LEFT)) != 0) {
        mPos += rel;
        mPos = mPos.cwiseMax(Vec2i::Zero());
        mPos = mPos.cwiseMin(parent()->size() - mSize);
        return true;
    }
    return false;
}

bool Window::mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers) {
    if (Widget::mouseButtonEvent(p, button, down, modifiers))
        return true;
    if (button == MOUSE_BUTTON_LEFT)
    {
        mDrag = down && (p.y() - mPos.y()) < mTheme->mWindowHeaderHeight;
        return true;
    }
    return false;
}

bool Window::scrollEvent(const Vec2i &p, const Vec2f &rel) {
    Widget::scrollEvent(p, rel);
    return true;
}

void Window::refreshRelativePlacement() {
    /* Overridden in \ref Popup */
}

/********************************** Widget *****************************************/

Widget::Widget(Widget *parent)
    : mParent(nullptr), mTheme(nullptr), mLayout(nullptr),
      mPos(Vec2i::Zero()), mSize(Vec2i::Zero()),
      mFixedSize(Vec2i::Zero()), mVisible(true), mEnabled(true),
      mFocused(false), mMouseFocus(false), mTooltip(""), mFontSize(-1.0f),
      mCursor(Cursor::Arrow) {
    if (parent) {
        parent->addChild(this);
        mTheme = parent->mTheme;
    }
}

Widget::~Widget() {
    for (auto child : mChildren) {
        if (child)
            child->decRef();
    }
}

int Widget::fontSize() const {
    return mFontSize < 0 ? mTheme->mStandardFontSize : mFontSize;
}

Vec2i Widget::preferredSize(NVGcontext *ctx) const {
    if (mLayout)
        return mLayout->preferredSize(ctx, this);
    else
        return mSize;
}

void Widget::performLayout(NVGcontext *ctx) {
    if (mLayout) {
        mLayout->performLayout(ctx, this);
    } else {
        for (auto c : mChildren) {
            Vec2i pref = c->preferredSize(ctx), fix = c->fixedSize();
            c->setSize(Vec2i(
                fix.x() ? fix.x() : pref.x(),
                fix.y() ? fix.y() : pref.y()
            ));
            c->performLayout(ctx);
        }
    }
}

Widget *Widget::findWidget(const Vec2i &p) {
    for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it) {
        Widget *child = *it;
        if (child->visible() && child->contains(p - mPos))
            return child->findWidget(p - mPos);
    }
    return contains(p) ? this : nullptr;
}

bool Widget::mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers) {
    for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it) {
        Widget *child = *it;
        if (child->visible() && child->contains(p - mPos) &&
            child->mouseButtonEvent(p - mPos, button, down, modifiers))
            return true;
    }
    if (button == MOUSE_BUTTON_LEFT && down && !mFocused)
        requestFocus();
    if (button == MOUSE_BUTTON_RIGHT && !down && mFocused)
    {
        if (mContextCallback)
            mContextCallback(p, this);
    }
    return false;
}

bool Widget::mouseMotionEvent(const Vec2i &p, const Vec2i &rel, int button, int modifiers) {
    for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it) {
        Widget *child = *it;
        if (!child->visible())
            continue;
        bool contained = child->contains(p - mPos), prevContained = child->contains(p - mPos - rel);
        if (contained != prevContained)
            child->mouseEnterEvent(p, contained);
        if ((contained || prevContained) &&
            child->mouseMotionEvent(p - mPos, rel, button, modifiers))
            return true;
    }
    return false;
}

bool Widget::scrollEvent(const Vec2i &p, const Vec2f &rel) {
    for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it) {
        Widget *child = *it;
        if (!child->visible())
            continue;
        if (child->contains(p - mPos) && child->scrollEvent(p - mPos, rel))
            return true;
    }
    return false;
}

bool Widget::mouseDragEvent(const Vec2i &, const Vec2i &, int, int) {
    return false;
}

bool Widget::mouseEnterEvent(const Vec2i &, bool enter) {
    mMouseFocus = enter;
    return false;
}

bool Widget::focusEvent(bool focused) {
    mFocused = focused;
    return false;
}

bool Widget::keyboardEvent(int, int, int, int) {
    return false;
}

bool Widget::keyboardCharacterEvent(unsigned int) {
    return false;
}

void Widget::addChild(Widget *widget) {
    mChildren.push_back(widget);
    widget->incRef();
    widget->setParent(this);
}

void Widget::removeChild(const Widget *widget) {
    for(auto it=mChildren.begin(); it != mChildren.end(); )
        if ( *it == widget) it = mChildren.erase(it);
        else ++it;
    widget->decRef();
}

void Widget::removeChild(int index) {
    Widget *widget = mChildren[index];
    mChildren.erase(mChildren.begin() + index);
    widget->decRef();
}

Window *Widget::window() {
    Widget *widget = this;
    while (true) {
        if (!widget)
            throw std::runtime_error(
                "Widget:internal error (could not find parent window)");
        Window *window = dynamic_cast<Window *>(widget);
        if (window)
            return window;
        widget = widget->parent();
    }
}

void Widget::requestFocus() {
    Widget *widget = this;
    while (widget->parent())
        widget = widget->parent();
    ((Screen *) widget)->updateFocus(this);
}

void Widget::draw(NVGcontext *ctx) {
    #if NANOGUI_SHOW_WIDGET_BOUNDS
        nvgStrokeWidth(ctx, 1.0f);
        nvgBeginPath(ctx);
        nvgRect(ctx, mPos.x() - 0.5f, mPos.y() - 0.5f, mSize.x() + 1, mSize.y() + 1);
        nvgStrokeColor(ctx, nvgRGBA(255, 0, 0, 255));
        nvgStroke(ctx);
    #endif

    if (mChildren.empty())
        return;

    nvgTranslate(ctx, mPos.x(), mPos.y());
    for (auto child : mChildren)
        if (child->visible())
            child->draw(ctx);
    nvgTranslate(ctx, -mPos.x(), -mPos.y());
}

/*********************************** Combobox **************************************/

ComboBox::ComboBox(Widget *parent) : PopupButton(parent), mSelectedIndex(0) {
}

ComboBox::ComboBox(Widget *parent, const std::vector<std::string> &items)
    : PopupButton(parent), mSelectedIndex(0) {
    setItems(items);
}

ComboBox::ComboBox(Widget *parent, const std::vector<std::string> &items, const std::vector<std::string> &itemsShort)
    : PopupButton(parent), mSelectedIndex(0) {
    setItems(items, itemsShort);
}

void ComboBox::setSelectedIndex(int idx) {
    if (mItemsShort.empty())
        return;
    const std::vector<Widget *> &children = popup()->children();
    ((Button *) children[mSelectedIndex])->setPushed(false);
    ((Button *) children[idx])->setPushed(true);
    mSelectedIndex = idx;
    setCaption(mItemsShort[idx]);
}

void ComboBox::setItems(const std::vector<std::string> &items, const std::vector<std::string> &itemsShort) {
    assert(items.size() == itemsShort.size());
    mItems = items;
    mItemsShort = itemsShort;
    if (mSelectedIndex < 0 || mSelectedIndex >= (int) items.size())
        mSelectedIndex = 0;
    while (mPopup->childCount() != 0)
        mPopup->removeChild(mPopup->childCount()-1);
    mPopup->setLayout(new GroupLayout(10));
    int index = 0;
    for (const auto &str: items) {
        Button *button = new Button(mPopup, str);
        button->setFlags(Button::RadioButton);
        button->setCallback([&, index] {
            mSelectedIndex = index;
            setCaption(mItemsShort[index]);
            setPushed(false);
            popup()->setVisible(false);
            if (mCallback)
                mCallback(index);
        });
        index++;
    }
    setSelectedIndex(mSelectedIndex);
}

/******************************* ColorWheel ****************************************************/

ColorWheel::ColorWheel(Widget *parent, const Color& rgb)
    : Widget(parent), mDragRegion(None) {
    setColor(rgb);
}

Vec2i ColorWheel::preferredSize(NVGcontext *) const {
    return Vec2i(100, 100.);
}

void ColorWheel::draw(NVGcontext *ctx) {
    Widget::draw(ctx);

    if (!mVisible)
        return;

    float x = mPos.x(),
          y = mPos.y(),
          w = mSize.x(),
          h = mSize.y();

    NVGcontext* vg = ctx;

    int i;
    float r0, r1, ax,ay, bx,by, cx,cy, aeps, r;
    float hue = mHue;
    NVGpaint paint;

    nvgSave(vg);

    cx = x + w*0.5f;
    cy = y + h*0.5f;
    r1 = (w < h ? w : h) * 0.5f - 5.0f;
    r0 = r1 * .75f;

    aeps = 0.5f / r1;   // half a pixel arc length in radians (2pi cancels out).

    for (i = 0; i < 6; i++) {
        float a0 = (float)i / 6.0f * NVG_PI * 2.0f - aeps;
        float a1 = (float)(i+1.0f) / 6.0f * NVG_PI * 2.0f + aeps;
        nvgBeginPath(vg);
        nvgArc(vg, cx,cy, r0, a0, a1, NVG_CW);
        nvgArc(vg, cx,cy, r1, a1, a0, NVG_CCW);
        nvgClosePath(vg);
        ax = cx + cosf(a0) * (r0+r1)*0.5f;
        ay = cy + sinf(a0) * (r0+r1)*0.5f;
        bx = cx + cosf(a1) * (r0+r1)*0.5f;
        by = cy + sinf(a1) * (r0+r1)*0.5f;
        paint = nvgLinearGradient(vg, ax, ay, bx, by,
                                  nvgHSLA(a0 / (NVG_PI * 2), 1.0f, 0.55f, 255),
                                  nvgHSLA(a1 / (NVG_PI * 2), 1.0f, 0.55f, 255));
        nvgFillPaint(vg, paint);
        nvgFill(vg);
    }

    nvgBeginPath(vg);
    nvgCircle(vg, cx,cy, r0-0.5f);
    nvgCircle(vg, cx,cy, r1+0.5f);
    nvgStrokeColor(vg, nvgRGBA(0,0,0,64));
    nvgStrokeWidth(vg, 1.0f);
    nvgStroke(vg);

    // Selector
    nvgSave(vg);
    nvgTranslate(vg, cx,cy);
    nvgRotate(vg, hue*NVG_PI*2);

    // Marker on
    float u = std::max(r1/50, 1.5f);
          u = std::min(u, 4.f);
    nvgStrokeWidth(vg, u);
    nvgBeginPath(vg);
    nvgRect(vg, r0-1,-2*u,r1-r0+2,4*u);
    nvgStrokeColor(vg, nvgRGBA(255,255,255,192));
    nvgStroke(vg);

    paint = nvgBoxGradient(vg, r0-3,-5,r1-r0+6,10, 2,4, nvgRGBA(0,0,0,128), nvgRGBA(0,0,0,0));
    nvgBeginPath(vg);
    nvgRect(vg, r0-2-10,-4-10,r1-r0+4+20,8+20);
    nvgRect(vg, r0-2,-4,r1-r0+4,8);
    nvgPathWinding(vg, NVG_HOLE);
    nvgFillPaint(vg, paint);
    nvgFill(vg);

    // Center triangle
    r = r0 - 6;
    ax = cosf(120.0f/180.0f*NVG_PI) * r;
    ay = sinf(120.0f/180.0f*NVG_PI) * r;
    bx = cosf(-120.0f/180.0f*NVG_PI) * r;
    by = sinf(-120.0f/180.0f*NVG_PI) * r;
    nvgBeginPath(vg);
    nvgMoveTo(vg, r,0);
    nvgLineTo(vg, ax, ay);
    nvgLineTo(vg, bx, by);
    nvgClosePath(vg);
    paint = nvgLinearGradient(vg, r, 0, ax, ay, nvgHSLA(hue, 1.0f, 0.5f, 255),
                              nvgRGBA(255, 255, 255, 255));
    nvgFillPaint(vg, paint);
    nvgFill(vg);
    paint = nvgLinearGradient(vg, (r + ax) * 0.5f, (0 + ay) * 0.5f, bx, by,
                              nvgRGBA(0, 0, 0, 0), nvgRGBA(0, 0, 0, 255));
    nvgFillPaint(vg, paint);
    nvgFill(vg);
    nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 64));
    nvgStroke(vg);

    // Select circle on triangle
    float sx = r*(1 - mWhite - mBlack) + ax*mWhite + bx*mBlack;
    float sy =                           ay*mWhite + by*mBlack;

    nvgStrokeWidth(vg, u);
    nvgBeginPath(vg);
    nvgCircle(vg, sx,sy,2*u);
    nvgStrokeColor(vg, nvgRGBA(255,255,255,192));
    nvgStroke(vg);

    nvgRestore(vg);

    nvgRestore(vg);
}

bool ColorWheel::mouseButtonEvent(const Vec2i &p, int button, bool down,
                                  int modifiers) {
    Widget::mouseButtonEvent(p, button, down, modifiers);
    /*if (!mEnabled || button != GLFW_MOUSE_BUTTON_1)
        return false;*/

    if (down) {
        mDragRegion = adjustPosition(p);
        return mDragRegion != None;
    } else {
        mDragRegion = None;
        return true;
    }
}

bool ColorWheel::mouseDragEvent(const Vec2i &p, const Vec2i &,
                                int, int) {
    return adjustPosition(p, mDragRegion) != None;
}

ColorWheel::Region ColorWheel::adjustPosition(const Vec2i &p, Region consideredRegions) {
    float x = p.x() - mPos.x(),
          y = p.y() - mPos.y(),
          w = mSize.x(),
          h = mSize.y();

    float cx = w*0.5f;
    float cy = h*0.5f;
    float r1 = (w < h ? w : h) * 0.5f - 5.0f;
    float r0 = r1 * .75f;

    x -= cx;
    y -= cy;

    float mr = std::sqrt(x*x + y*y);

    if ((consideredRegions & OuterCircle) &&
        ((mr >= r0 && mr <= r1) || (consideredRegions == OuterCircle))) {
        if (!(consideredRegions & OuterCircle))
            return None;
        mHue = std::atan(y / x);
        if (x < 0)
            mHue += NVG_PI;
        mHue /= 2*NVG_PI;

        if (mCallback)
            mCallback(color());

        return OuterCircle;
    }

    /*float r = r0 - 6;

    float ax = std::cos( 120.0f/180.0f*NVG_PI) * r;
    float ay = std::sin( 120.0f/180.0f*NVG_PI) * r;
    float bx = std::cos(-120.0f/180.0f*NVG_PI) * r;
    float by = std::sin(-120.0f/180.0f*NVG_PI) * r;

    //TODO UNIMPLEMENTED
    typedef Eigen::Matrix<float,2,2>        Matrix2f;

    Eigen::Matrix<float, 2, 3> triangle;
    triangle << ax,bx,r,
                ay,by,0;
    triangle = Eigen::Rotation2D<float>(mHue * 2 * NVG_PI).matrix() * triangle;

    Matrix2f T;
    T << triangle(0,0) - triangle(0,2), triangle(0,1) - triangle(0,2),
         triangle(1,0) - triangle(1,2), triangle(1,1) - triangle(1,2);
    Vector2f pos { x - triangle(0,2), y - triangle(1,2) };

    Vector2f bary = T.colPivHouseholderQr().solve(pos);
    float l0 = bary[0], l1 = bary[1], l2 = 1 - l0 - l1;
    bool triangleTest = l0 >= 0 && l0 <= 1.f && l1 >= 0.f && l1 <= 1.f &&
                        l2 >= 0.f && l2 <= 1.f;

    if ((consideredRegions & InnerTriangle) &&
        (triangleTest || consideredRegions == InnerTriangle)) {
        if (!(consideredRegions & InnerTriangle))
            return None;
        l0 = std::min(std::max(0.f, l0), 1.f);
        l1 = std::min(std::max(0.f, l1), 1.f);
        l2 = std::min(std::max(0.f, l2), 1.f);
        float sum = l0 + l1 + l2;
        l0 /= sum;
        l1 /= sum;
        mWhite = l0;
        mBlack = l1;
        if (mCallback)
            mCallback(color());
        return InnerTriangle;
    } */

    return None;
}

Color ColorWheel::hue2rgb(float h) const {
    float s = 1., v = 1.;

    if (h < 0) h += 1;

    int i = int(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    float r = 0, g = 0, b = 0;
    switch (i % 6) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    return { r, g, b, 1.f };
}

Color ColorWheel::color() const {
    Color rgb    = hue2rgb(mHue);
    Color black  { 0.f, 0.f, 0.f, 1.f };
    Color white  { 1.f, 1.f, 1.f, 1.f };
    return rgb * (1 - mWhite - mBlack) + black * mBlack + white * mWhite;
}

void ColorWheel::setColor(const Color &rgb) {
    float r = rgb.r(), g = rgb.g(), b = rgb.b();

    float max = std::max(std::max(r, g), b);
    float min = std::min(std::min(r, g), b);
    float l = (max + min) / 2;

    if (max == min) {
        mHue = 0.;
        mBlack = 1. - l;
        mWhite = l;
    } else {
        float d = max - min, h;
        /* float s = l > 0.5 ? d / (2 - max - min) : d / (max + min); */
        if (max == r)
            h = (g - b) / d + (g < b ? 6 : 0);
        else if (max == g)
            h = (b - r) / d + 2;
        else
            h = (r - g) / d + 4;
        h /= 6;

        mHue = h;

       /* Eigen::Matrix<float, 4, 3> M;
        M.topLeftCorner<3, 1>() = hue2rgb(h).head<3>();
        M(3, 0) = 1.;
        M.col(1) = Vector4f{ 0., 0., 0., 1. };
        M.col(2) = Vector4f{ 1., 1., 1., 1. };

        Vector4f rgb4 = rgb.withAlpha(1);
        Vector3f bary = M.colPivHouseholderQr().solve(rgb4);

        mBlack = bary[1];
        mWhite = bary[2];*/
    }
}

/****************************************** ColorPicker ********************************/

ColorPicker::ColorPicker(Widget *parent, const Color& color) : PopupButton(parent, "") {
    setBackgroundColor(color);
    Popup *popup = this->popup();
    popup->setLayout(new GroupLayout());

    mColorWheel = new ColorWheel(popup);
    mPickButton = new Button(popup, "Pick");
    mPickButton->setFixedSize(Vec2i(100, 25));

    PopupButton::setChangeCallback([&](bool) {
        setColor(backgroundColor());
        mCallback(backgroundColor());
    });

    mColorWheel->setCallback([&](const Color &value) {
        mPickButton->setBackgroundColor(value);
        mPickButton->setTextColor(value.contrastingColor());
        mCallback(value);
    });

    mPickButton->setCallback([&]() {
        Color value = mColorWheel->color();
        setPushed(false);
        setColor(value);
        mCallback(value);
    });
}

Color ColorPicker::color() const {
    return backgroundColor();
}

void ColorPicker::setColor(const Color& color) {
    /* Ignore setColor() calls when the user is currently editing */
    if (!mPushed) {
        Color fg = color.contrastingColor();
        setBackgroundColor(color);
        setTextColor(fg);
        mColorWheel->setColor(color);
        mPickButton->setBackgroundColor(color);
        mPickButton->setTextColor(fg);
    }
}

/********************************** ImageView ***************************/

ImageView::ImageView(Widget *parent, int img, SizePolicy policy)
    : Widget(parent), mImage(img), mPolicy(policy) {}

Vec2i ImageView::preferredSize(NVGcontext *ctx) const {
    if (!mImage)
        return Vec2i(0, 0);
    int w,h;
    nvgImageSize(ctx, mImage, &w, &h);
    return Vec2i(w, h);
}

void ImageView::draw(NVGcontext* ctx) {
    if (!mImage)
        return;
    Vec2i p = mPos;
    Vec2i s = Widget::size();

    int w, h;
    nvgImageSize(ctx, mImage, &w, &h);

    if (mPolicy == SizePolicy::Fixed) {
        if (s.x() < w) {
            h = (int) std::round(h * (float) s.x() / w);
            w = s.x();
        }

        if (s.y() < h) {
            w = (int) std::round(w * (float) s.y() / h);
            h = s.y();
        }
    } else {    // mPolicy == Expand
        // expand to width
        h = (int) std::round(h * (float) s.x() / w);
        w = s.x();

        // shrink to height, if necessary
        if (s.y() < h) {
            w = (int) std::round(w * (float) s.y() / h);
            h = s.y();
        }
    }

    NVGpaint imgPaint = nvgImagePattern(ctx, p.x(), p.y(), w, h, 0, mImage, 1.0);

    nvgBeginPath(ctx);
    nvgRect(ctx, p.x(), p.y(), w, h);
    nvgFillPaint(ctx, imgPaint);
    nvgFill(ctx);
}

/**************************************** ImagePanel ********************************/

ImagePanel::ImagePanel(Widget *parent)
    : Widget(parent), mThumbSize(64), mSpacing(10), mMargin(10),
      mMouseIndex(-1) {}

Vec2i ImagePanel::gridSize() const
{
    int nCols = 1 + std::max(0,
        (int) ((mSize.x() - 2 * mMargin - mThumbSize) /
        (float) (mThumbSize + mSpacing)));
    int nRows = ((int) mImages.size() + nCols - 1) / nCols;
    return Vec2i(nCols, nRows);
}

int ImagePanel::indexForPosition(const Vec2i &p) const {
    Vec2f pp = (p.cast<float>() - Vec2f::Constant(mMargin)) /
                  (float)(mThumbSize + mSpacing);
    float iconRegion = mThumbSize / (float)(mThumbSize + mSpacing);
    bool overImage = pp.x() - std::floor(pp.x()) < iconRegion &&
                    pp.y() - std::floor(pp.y()) < iconRegion;
    Vec2i gridPos = pp.cast<int>(), grid = gridSize();
    overImage &= ((gridPos.x() >= 0 && gridPos.y() >= 0) &&
                  (gridPos.x() < grid.x() && gridPos.y() < grid.y()));
    return overImage ? (gridPos.x() + gridPos.y() * grid.x()) : -1;
}

bool ImagePanel::mouseMotionEvent(const Vec2i &p, const Vec2i & /* rel */,
                              int /* button */, int /* modifiers */) {
    mMouseIndex = indexForPosition(p);
    return true;
}

bool ImagePanel::mouseButtonEvent(const Vec2i &p, int /* button */, bool down,
                                  int /* modifiers */) {
    int index = indexForPosition(p);
    if (index >= 0 && mCallback && down)
        mCallback(index);
    return true;
}

Vec2i ImagePanel::preferredSize(NVGcontext *) const {
    Vec2i grid = gridSize();
    return Vec2i(
        grid.x() * mThumbSize + (grid.x() - 1) * mSpacing + 2*mMargin,
        grid.y() * mThumbSize + (grid.y() - 1) * mSpacing + 2*mMargin
    );
}

void ImagePanel::draw(NVGcontext* ctx) {
    Vec2i grid = gridSize();

    for (size_t i=0; i<mImages.size(); ++i) {
        Vec2i p = mPos + Vec2i::Constant(mMargin) +
            Vec2i((int) i % grid.x(), (int) i / grid.x()) * (mThumbSize + mSpacing);
        int imgw, imgh;

        nvgImageSize(ctx, mImages[i].first, &imgw, &imgh);
        float iw, ih, ix, iy;
        if (imgw < imgh) {
            iw = mThumbSize;
            ih = iw * (float)imgh / (float)imgw;
            ix = 0;
            iy = -(ih - mThumbSize) * 0.5f;
        } else {
            ih = mThumbSize;
            iw = ih * (float)imgw / (float)imgh;
            ix = -(iw - mThumbSize) * 0.5f;
            iy = 0;
        }

        NVGpaint imgPaint = nvgImagePattern(
            ctx, p.x() + ix, p.y()+ iy, iw, ih, 0, mImages[i].first,
            mMouseIndex == (int)i ? 1.0 : 0.7);

        nvgBeginPath(ctx);
        nvgRoundedRect(ctx, p.x(), p.y(), mThumbSize, mThumbSize, 5);
        nvgFillPaint(ctx, imgPaint);
        nvgFill(ctx);

        NVGpaint shadowPaint =
            nvgBoxGradient(ctx, p.x() - 1, p.y(), mThumbSize + 2, mThumbSize + 2, 5, 3,
                           nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0));
        nvgBeginPath(ctx);
        nvgRect(ctx, p.x()-5,p.y()-5, mThumbSize+10,mThumbSize+10);
        nvgRoundedRect(ctx, p.x(),p.y(), mThumbSize,mThumbSize, 6);
        nvgPathWinding(ctx, NVG_HOLE);
        nvgFillPaint(ctx, shadowPaint);
        nvgFill(ctx);

        nvgBeginPath(ctx);
        nvgRoundedRect(ctx, p.x()+0.5f,p.y()+0.5f, mThumbSize-1,mThumbSize-1, 4-0.5f);
        nvgStrokeWidth(ctx, 1.0f);
        nvgStrokeColor(ctx, nvgRGBA(255,255,255,80));
        nvgStroke(ctx);
    }
}

/*********************************** Layouts *********************************************/

BoxLayout::BoxLayout(Orientation orientation, Alignment alignment,
          int margin, int spacing)
    : mOrientation(orientation), mAlignment(alignment), mMargin(margin),
      mSpacing(spacing) {
}

Vec2i BoxLayout::preferredSize(NVGcontext *ctx, const Widget *widget) const {
    Vec2i size = Vec2i::Constant(2*mMargin);

    if (dynamic_cast<const Window *>(widget))
        size.seq(1) += widget->theme()->mWindowHeaderHeight - mMargin/2;

    bool first = true;
    int axis1 = (int) mOrientation, axis2 = ((int) mOrientation + 1)%2;
    for (auto w : widget->children()) {
        if (!w->visible())
            continue;
        if (first)
            first = false;
        else
            size.seq(axis1) += mSpacing;

        Vec2i ps = w->preferredSize(ctx), fs = w->fixedSize();
        Vec2i targetSize(
            fs.x() ? fs.x() : ps.x(),
            fs.y() ? fs.y() : ps.y()
        );

        size.seq(axis1) += targetSize.seq(axis1);
        size.seq(axis2) = std::max(size.seq(axis2), targetSize.seq(axis2) + 2*mMargin);
        first = false;
    }
    return size;
}

void BoxLayout::performLayout(NVGcontext *ctx, Widget *widget) const {
    Vec2i fs_w = widget->fixedSize();
    Vec2i containerSize(
        fs_w.x() ? fs_w.x() : widget->width(),
        fs_w.y() ? fs_w.y() : widget->height()
    );

    int axis1 = (int) mOrientation, axis2 = ((int) mOrientation + 1)%2;
    int position = mMargin;

    if (dynamic_cast<Window *>(widget))
        position += widget->theme()->mWindowHeaderHeight - mMargin/2;

    bool first = true;
    for (auto w : widget->children()) {
        if (!w->visible())
            continue;
        if (first)
            first = false;
        else
            position += mSpacing;

        Vec2i ps = w->preferredSize(ctx), fs = w->fixedSize();
        Vec2i targetSize(
            fs.x() ? fs.x() : ps.x(),
            fs.y() ? fs.y() : ps.y()
        );
        Vec2i pos = Vec2i::Zero();
        pos.seq(axis1) = position;

        switch (mAlignment) {
            case Alignment::Minimum:
                pos.seq(axis2) = mMargin;
                break;
            case Alignment::Middle:
                pos.seq(axis2) = (containerSize.seq(axis2) - targetSize.seq(axis2)) / 2;
                break;
            case Alignment::Maximum:
                pos.seq(axis2) = containerSize.seq(axis2) - targetSize.seq(axis2) - mMargin;
                break;
            case Alignment::Fill:
                pos.seq(axis2) = mMargin;
                targetSize.seq(axis2) = fs.seq(axis2) ? fs.seq(axis2) : containerSize.seq(axis2);
                break;
        }

        w->setPosition(pos);
        w->setSize(targetSize);
        w->performLayout(ctx);
        position += targetSize.seq(axis1);
    }
}

Vec2i GroupLayout::preferredSize(NVGcontext *ctx, const Widget *widget) const {
    int height = mMargin, width = 2*mMargin;

    const Window *window = dynamic_cast<const Window *>(widget);
    if (window && !window->title().empty())
        height += widget->theme()->mWindowHeaderHeight - mMargin/2;

    bool first = true, indent = false;
    for (auto c : widget->children()) {
        if (!c->visible())
            continue;
        const Label *label = dynamic_cast<const Label *>(c);
        if (!first)
            height += (label == nullptr) ? mSpacing : mGroupSpacing;
        first = false;

        Vec2i ps = c->preferredSize(ctx), fs = c->fixedSize();
        Vec2i targetSize(
            fs.x() ? fs.x() : ps.x(),
            fs.y() ? fs.y() : ps.y()
        );

        bool indentCur = indent && label == nullptr;
        height += targetSize.y();
        width = std::max(width, targetSize.x() + 2*mMargin + (indentCur ? mGroupIndent : 0));

        if (label)
            indent = !label->caption().empty();
    }
    height += mMargin;
    return Vec2i(width, height);
}

void GroupLayout::performLayout(NVGcontext *ctx, Widget *widget) const {
    int height = mMargin, availableWidth =
        (widget->fixedWidth() ? widget->fixedWidth() : widget->width()) - 2*mMargin;

    const Window *window = dynamic_cast<const Window *>(widget);
    if (window && !window->title().empty())
        height += widget->theme()->mWindowHeaderHeight - mMargin/2;

    bool first = true, indent = false;
    for (auto c : widget->children()) {
        if (!c->visible())
            continue;
        const Label *label = dynamic_cast<const Label *>(c);
        if (!first)
            height += (label == nullptr) ? mSpacing : mGroupSpacing;
        first = false;

        bool indentCur = indent && label == nullptr;
        Vec2i ps = Vec2i(availableWidth - (indentCur ? mGroupIndent : 0),
                               c->preferredSize(ctx).y());
        Vec2i fs = c->fixedSize();

        Vec2i targetSize(
            fs.x() ? fs.x() : ps.x(),
            fs.y() ? fs.y() : ps.y()
        );

        c->setPosition(Vec2i(mMargin + (indentCur ? mGroupIndent : 0), height));
        c->setSize(targetSize);
        c->performLayout(ctx);

        height += targetSize.y();

        if (label)
            indent = !label->caption().empty();
    }
}

Vec2i GridLayout::preferredSize(NVGcontext *ctx,
                                   const Widget *widget) const {
    /* Compute minimum row / column sizes */
    std::vector<int> grid[2];
    computeLayout(ctx, widget, grid);

    Vec2i size(
        2*mMargin + std::accumulate(grid[0].begin(), grid[0].end(), 0)
         + std::max((int) grid[0].size() - 1, 0) * mSpacing.x(),
        2*mMargin + std::accumulate(grid[1].begin(), grid[1].end(), 0)
         + std::max((int) grid[1].size() - 1, 0) * mSpacing.y()
    );

    if (dynamic_cast<const Window *>(widget))
        size.ry() += widget->theme()->mWindowHeaderHeight - mMargin/2;

    return size;
}

void GridLayout::computeLayout(NVGcontext *ctx, const Widget *widget, std::vector<int> *grid) const {
    int axis1 = (int) mOrientation, axis2 = (axis1 + 1) % 2;
    size_t numChildren = widget->children().size(), visibleChildren = 0;
    for (auto w : widget->children())
        visibleChildren += w->visible() ? 1 : 0;

    Vec2i dim;
    dim.seq(axis1) = mResolution;
    dim.seq(axis2) = (int) ((visibleChildren + mResolution - 1) / mResolution);

    grid[axis1].clear(); grid[axis1].resize(dim.seq(axis1), 0);
    grid[axis2].clear(); grid[axis2].resize(dim.seq(axis2), 0);

    size_t child = 0;
    for (int i2 = 0; i2 < dim.seq(axis2); i2++) {
        for (int i1 = 0; i1 < dim.seq(axis1); i1++) {
            Widget *w = nullptr;
            do {
                if (child >= numChildren)
                    return;
                w = widget->children()[child++];
            } while (!w->visible());

            Vec2i ps = w->preferredSize(ctx);
            Vec2i fs = w->fixedSize();
            Vec2i targetSize(
                fs.x() ? fs.x() : ps.x(),
                fs.y() ? fs.y() : ps.y()
            );

            grid[axis1][i1] = std::max(grid[axis1][i1], targetSize.seq(axis1));
            grid[axis2][i2] = std::max(grid[axis2][i2], targetSize.seq(axis2));
        }
    }
}

void GridLayout::performLayout(NVGcontext *ctx, Widget *widget) const {
    Vec2i fs_w = widget->fixedSize();
    Vec2i containerSize(
        fs_w.x() ? fs_w.x() : widget->width(),
        fs_w.y() ? fs_w.y() : widget->height()
    );

    /* Compute minimum row / column sizes */
    std::vector<int> grid[2];
    computeLayout(ctx, widget, grid);
    int dim[2] = { (int) grid[0].size(), (int) grid[1].size() };

    Vec2i extra = Vec2i::Zero();
    if (dynamic_cast<Window *>(widget))
        extra.ry() += widget->theme()->mWindowHeaderHeight - mMargin / 2;

    /* Strech to size provided by \c widget */
    for (int i = 0; i < 2; i++) {
        int gridSize = 2 * mMargin + extra.seq(i);
        for (int s : grid[i]) {
            gridSize += s;
            if (i+1 < dim[i])
                gridSize += mSpacing.seq(i);
        }

        if (gridSize < containerSize.seq(i)) {
            /* Re-distribute remaining space evenly */
            int gap = containerSize.seq(i) - gridSize;
            int g = gap / dim[i];
            int rest = gap - g * dim[i];
            for (int j = 0; j < dim[i]; ++j)
                grid[i][j] += g;
            for (int j = 0; rest > 0 && j < dim[i]; --rest, ++j)
                grid[i][j] += 1;
        }
    }

    int axis1 = (int) mOrientation, axis2 = (axis1 + 1) % 2;
    Vec2i start = Vec2i::Constant(mMargin) + extra;

    size_t numChildren = widget->children().size();
    size_t child = 0;

    Vec2i pos = start;
    for (int i2 = 0; i2 < dim[axis2]; i2++) {
        pos.seq(axis1) = start.seq(axis1);
        for (int i1 = 0; i1 < dim[axis1]; i1++) {
            Widget *w = nullptr;
            do {
                if (child >= numChildren)
                    return;
                w = widget->children()[child++];
            } while (!w->visible());

            Vec2i ps = w->preferredSize(ctx);
            Vec2i fs = w->fixedSize();
            Vec2i targetSize(
                fs.x() ? fs.x() : ps.x(),
                fs.y() ? fs.y() : ps.y()
            );

            Vec2i itemPos(pos);
            for (int j = 0; j < 2; j++) {
                int axis = (axis1 + j) % 2;
                int item = j == 0 ? i1 : i2;
                Alignment align = alignment(axis, item);

                switch (align) {
                    case Alignment::Minimum:
                        break;
                    case Alignment::Middle:
                        itemPos.seq(axis) += (grid[axis][item] - targetSize.seq(axis)) / 2;
                        break;
                    case Alignment::Maximum:
                        itemPos.seq(axis) += grid[axis][item] - targetSize.seq(axis);
                        break;
                    case Alignment::Fill:
                        targetSize.seq(axis) = fs.seq(axis) ? fs.seq(axis) : grid[axis][item];
                        break;
                }
            }
            w->setPosition(itemPos);
            w->setSize(targetSize);
            w->performLayout(ctx);
            pos.seq(axis1) += grid[axis1][i1] + mSpacing.seq(axis1);
        }
        pos.seq(axis2) += grid[axis2][i2] + mSpacing.seq(axis2);
    }
}

AdvancedGridLayout::AdvancedGridLayout(const std::vector<int> &cols, const std::vector<int> &rows)
 : mCols(cols), mRows(rows) {
    mColStretch.resize(mCols.size(), 0);
    mRowStretch.resize(mRows.size(), 0);
}

Vec2i AdvancedGridLayout::preferredSize(NVGcontext *ctx, const Widget *widget) const {
    /* Compute minimum row / column sizes */
    std::vector<int> grid[2];
    computeLayout(ctx, widget, grid);

    Vec2i size(
        std::accumulate(grid[0].begin(), grid[0].end(), 0),
        std::accumulate(grid[1].begin(), grid[1].end(), 0));

    Vec2i extra = Vec2i::Constant(2 * mMargin);
    if (dynamic_cast<const Window *>(widget))
        extra.ry() += widget->theme()->mWindowHeaderHeight - mMargin/2;

    return size+extra;
}

void AdvancedGridLayout::performLayout(NVGcontext *ctx, Widget *widget) const {
    std::vector<int> grid[2];
    computeLayout(ctx, widget, grid);

    grid[0].insert(grid[0].begin(), mMargin);
    if (dynamic_cast<const Window *>(widget))
        grid[1].insert(grid[1].begin(), widget->theme()->mWindowHeaderHeight + mMargin/2);
    else
        grid[1].insert(grid[1].begin(), mMargin);

    for (int axis=0; axis<2; ++axis) {
        for (size_t i=1; i<grid[axis].size(); ++i)
            grid[axis][i] += grid[axis][i-1];

        for (Widget *w : widget->children()) {
            Anchor anchor = this->anchor(w);
            if (!w->visible())
                continue;

            int itemPos = grid[axis][anchor.pos[axis]];
            int cellSize  = grid[axis][anchor.pos[axis] + anchor.size[axis]] - itemPos;
            int ps = w->preferredSize(ctx).seq(axis), fs = w->fixedSize().seq(axis);
            int targetSize = fs ? fs : ps;

            switch (anchor.align[axis]) {
                case Alignment::Minimum:
                    break;
                case Alignment::Middle:
                    itemPos += (cellSize - targetSize) / 2;
                    break;
                case Alignment::Maximum:
                    itemPos += cellSize - targetSize;
                    break;
                case Alignment::Fill:
                    targetSize = fs ? fs : cellSize;
                    break;
            }

            Vec2i pos = w->position(), size = w->size();
            pos.seq(axis) = itemPos;
            size.seq(axis) = targetSize;
            w->setPosition(pos);
            w->setSize(size);
            w->performLayout(ctx);
        }
    }
}

void AdvancedGridLayout::computeLayout(NVGcontext *ctx, const Widget *widget,
                                       std::vector<int> *_grid) const {
    Vec2i fs_w = widget->fixedSize();
    Vec2i containerSize(
        fs_w.x() ? fs_w.x() : widget->width(),
        fs_w.y() ? fs_w.y() : widget->height()
    );

    Vec2i extra = Vec2i::Constant(2 * mMargin);
    if (dynamic_cast<const Window *>(widget))
        extra.ry() += widget->theme()->mWindowHeaderHeight - mMargin/2;

    containerSize -= extra;

    for (int axis=0; axis<2; ++axis) {
        std::vector<int> &grid = _grid[axis];
        const std::vector<int> &sizes = axis == 0 ? mCols : mRows;
        const std::vector<float> &stretch = axis == 0 ? mColStretch : mRowStretch;
        grid = sizes;

        for (int phase = 0; phase < 2; ++phase) {
            for (auto pair : mAnchor) {
                const Widget *w = pair.first;
                if (!w->visible())
                    continue;
                const Anchor &anchor = pair.second;
                if ((anchor.size[axis] == 1) != (phase == 0))
                    continue;
                int ps = w->preferredSize(ctx).seq(axis), fs = w->fixedSize().seq(axis);
                int targetSize = fs ? fs : ps;

                if (anchor.pos[axis] + anchor.size[axis] > (int) grid.size())
                    throw std::runtime_error(
                        "Advanced grid layout: widget is out of bounds: " +
                        (std::string) anchor);

                int currentSize = 0;
                float totalStretch = 0;
                for (int i = anchor.pos[axis];
                     i < anchor.pos[axis] + anchor.size[axis]; ++i) {
                    if (sizes[i] == 0 && anchor.size[axis] == 1)
                        grid[i] = std::max(grid[i], targetSize);
                    currentSize += grid[i];
                    totalStretch += stretch[i];
                }
                if (targetSize <= currentSize)
                    continue;
                if (totalStretch == 0)
                    throw std::runtime_error(
                        "Advanced grid layout: no space to place widget: " +
                        (std::string) anchor);
                float amt = (targetSize - currentSize) / totalStretch;
                for (int i = anchor.pos[axis];
                     i < anchor.pos[axis] + anchor.size[axis]; ++i) {
                    grid[i] += (int) std::round(amt * stretch[i]);
                }
            }
        }

        int currentSize = std::accumulate(grid.begin(), grid.end(), 0);
        float totalStretch = std::accumulate(stretch.begin(), stretch.end(), 0.0f);
        if (currentSize >= containerSize.seq(axis) || totalStretch == 0)
            continue;
        float amt = (containerSize.seq(axis) - currentSize) / totalStretch;
        for (size_t i = 0; i<grid.size(); ++i)
            grid[i] += (int) std::round(amt * stretch[i]);
    }
}


/*************************************** Graph **************************************/

Graph::Graph(Widget *parent, const std::string &caption)
    : Widget(parent), mCaption(caption) {
    mBackgroundColor = Color(20, 128);
    mForegroundColor = Color(255, 192, 0, 128);
    mTextColor = Color(240, 192);
}

Vec2i Graph::preferredSize(NVGcontext *) const {
    return Vec2i(180, 45);
}

void Graph::draw(NVGcontext *ctx) {
    Widget::draw(ctx);

    nvgBeginPath(ctx);
    nvgRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y());
    nvgFillColor(ctx, mBackgroundColor);
    nvgFill(ctx);

    if (mValues.size() < 2)
        return;

    nvgBeginPath(ctx);
    nvgMoveTo(ctx, mPos.x(), mPos.y()+mSize.y());
    for (size_t i = 0; i < (size_t) mValues.size(); i++) {
        float value = mValues[i];
        float vx = mPos.x() + i * mSize.x() / (float) (mValues.size() - 1);
        float vy = mPos.y() + (1-value) * mSize.y();
        nvgLineTo(ctx, vx, vy);
    }

    nvgLineTo(ctx, mPos.x() + mSize.x(), mPos.y() + mSize.y());
    nvgStrokeColor(ctx, Color(100, 255));
    nvgStroke(ctx);
    nvgFillColor(ctx, mForegroundColor);
    nvgFill(ctx);

    nvgFontFace(ctx, "sans");

    if (!mCaption.empty()) {
        nvgFontSize(ctx, 14.0f);
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgFillColor(ctx, mTextColor);
        nvgText(ctx, mPos.x() + 3, mPos.y() + 1, mCaption.c_str(), NULL);
    }

    if (!mHeader.empty()) {
        nvgFontSize(ctx, 18.0f);
        nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
        nvgFillColor(ctx, mTextColor);
        nvgText(ctx, mPos.x() + mSize.x() - 3, mPos.y() + 1, mHeader.c_str(), NULL);
    }

    if (!mFooter.empty()) {
        nvgFontSize(ctx, 15.0f);
        nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM);
        nvgFillColor(ctx, mTextColor);
        nvgText(ctx, mPos.x() + mSize.x() - 3, mPos.y() + mSize.y() - 1, mFooter.c_str(), NULL);
    }

    nvgBeginPath(ctx);
    nvgRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y());
    nvgStrokeColor(ctx, Color(100, 255));
    nvgStroke(ctx);
}

/**************************************** Theme *****************************************/

Theme::Theme(NVGcontext *ctx) {
    mStandardFontSize                 = 16;
    mButtonFontSize                   = 20;
    mTextBoxFontSize                  = 20;
    mWindowCornerRadius               = 2;
    mWindowHeaderHeight               = 30;
    mWindowDropShadowSize             = 10;
    mButtonCornerRadius               = 2;

    mButtonHaveLigthBorder            = true;

    mDropShadow                       = Color(0, 128);
    mTransparent                      = Color(0, 0);
    mBorderDark                       = Color(29, 255);
    mBorderLight                      = Color(92, 255);
    mBorderMedium                     = Color(35, 255);
    mTextColor                        = Color(255, 160);
    mDisabledTextColor                = Color(255, 80);
    mTextColorShadow                  = Color(0, 160);
    mIconColor                        = mTextColor;

    mButtonGradientTopFocused         = Color(64, 255);
    mButtonGradientBotFocused         = Color(48, 255);
    mButtonGradientTopUnfocused       = Color(74, 255);
    mButtonGradientBotUnfocused       = Color(58, 255);
    mButtonGradientTopPushed          = Color(41, 255);
    mButtonGradientBotPushed          = Color(29, 255);

    /* Window-related */
    mWindowFillUnfocused              = Color(43, 230);
    mWindowFillFocused                = Color(45, 230);
    mWindowTitleUnfocused             = Color(220, 160);
    mWindowTitleFocused               = Color(255, 190);

    mWindowHeaderGradientTop          = mButtonGradientTopUnfocused;
    mWindowHeaderGradientBot          = mButtonGradientBotUnfocused;
    mWindowHeaderSepTop               = mBorderLight;
    mWindowHeaderSepBot               = mBorderDark;

    mWindowPopup                      = Color(50, 255);
    mWindowPopupTransparent           = Color(50, 0);

    mFontNormal = nvgCreateFontMem(ctx, "sans", roboto_regular_ttf,
                                   roboto_regular_ttf_size, 0);
    mFontBold = nvgCreateFontMem(ctx, "sans-bold", roboto_bold_ttf,
                                 roboto_bold_ttf_size, 0);
    mFontIcons = nvgCreateFontMem(ctx, "icons", entypo_ttf,
                                  entypo_ttf_size, 0);
    if (mFontNormal == -1 || mFontBold == -1 || mFontIcons == -1)
        throw std::runtime_error("Could not load fonts!");
}

/**************************** Vscrollpanel *******************************************/

VScrollPanel::VScrollPanel(Widget *parent)
    : Widget(parent), mChildPreferredHeight(0), mScroll(0.0f) { }

void VScrollPanel::performLayout(NVGcontext *ctx) {
    Widget::performLayout(ctx);

    if (mChildren.empty())
        return;
    Widget *child = mChildren[0];
    mChildPreferredHeight = child->preferredSize(ctx).y();
    child->setPosition(Vec2i(0, 0));
    child->setSize(Vec2i(mSize.x()-12, mChildPreferredHeight));
}

Vec2i VScrollPanel::preferredSize(NVGcontext *ctx) const {
    if (mChildren.empty())
        return Vec2i::Zero();
    return mChildren[0]->preferredSize(ctx) + Vec2i(12, 0);
}

bool VScrollPanel::mouseDragEvent(const Vec2i &, const Vec2i &rel,
                            int, int) {
    if (mChildren.empty())
        return false;

    float scrollh = height() *
        std::min(1.0f, height() / (float)mChildPreferredHeight);

    mScroll = std::max((float) 0.0f, std::min((float) 1.0f,
                 mScroll + rel.y() / (float)(mSize.y() - 8 - scrollh)));
    return true;
}

bool VScrollPanel::scrollEvent(const Vec2i &/* p */, const Vec2f &rel) {
    float scrollAmount = rel.y() * (mSize.y() / 20.0f);
    float scrollh = height() *
        std::min(1.0f, height() / (float)mChildPreferredHeight);

    mScroll = std::max((float) 0.0f, std::min((float) 1.0f,
            mScroll - scrollAmount / (float)(mSize.y() - 8 - scrollh)));
    return true;
}

bool VScrollPanel::mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers) {
    if (mChildren.empty())
        return false;
    int shift = (int) (mScroll*(mChildPreferredHeight - mSize.y()));
    return mChildren[0]->mouseButtonEvent(p + Vec2i(0, shift), button, down, modifiers);
}

bool VScrollPanel::mouseMotionEvent(const Vec2i &p, const Vec2i &rel, int button, int modifiers) {
    if (mChildren.empty())
        return false;
    int shift = (int) (mScroll*(mChildPreferredHeight - mSize.y()));
    return mChildren[0]->mouseMotionEvent(p + Vec2i(0, shift), rel, button, modifiers);
}

void VScrollPanel::draw(NVGcontext *ctx) {
    if (mChildren.empty())
        return;
    Widget *child = mChildren[0];
    mChildPreferredHeight = child->preferredSize(ctx).y();
    float scrollh = height() *
        std::min(1.0f, height() / (float) mChildPreferredHeight);

    nvgSave(ctx);
    nvgTranslate(ctx, mPos.x(), mPos.y());
    nvgScissor(ctx, 0, 0, mSize.x(), mSize.y());
    nvgTranslate(ctx, 0, -mScroll*(mChildPreferredHeight - mSize.y()));
    if (child->visible())
        child->draw(ctx);
    nvgRestore(ctx);

    NVGpaint paint = nvgBoxGradient(
        ctx, mPos.x() + mSize.x() - 12 + 1, mPos.y() + 4 + 1, 8,
        mSize.y() - 8, 3, 4, Color(0, 32), Color(0, 92));
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x() + mSize.x() - 12, mPos.y() + 4, 8,
                   mSize.y() - 8, 3);
    nvgFillPaint(ctx, paint);
    nvgFill(ctx);

    paint = nvgBoxGradient(
        ctx, mPos.x() + mSize.x() - 12 - 1,
        mPos.y() + 4 + (mSize.y() - 8 - scrollh) * mScroll - 1, 8, scrollh,
        3, 4, Color(220, 100), Color(128, 100));

    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x() + mSize.x() - 12 + 1,
                   mPos.x() + 4 + 1 + (mSize.y() - 8 - scrollh) * mScroll, 8 - 2,
                   scrollh - 2, 2);
    nvgFillPaint(ctx, paint);
    nvgFill(ctx);
}

/*********************************** Progressbar **************************************/

ProgressBar::ProgressBar(Widget *parent)
    : Widget(parent), mValue(0.0f) {}

Vec2i ProgressBar::preferredSize(NVGcontext *) const
{
    return Vec2i(70, 12);
}

void ProgressBar::draw(NVGcontext* ctx)
{
    Widget::draw(ctx);

    NVGpaint paint = nvgBoxGradient(
        ctx, mPos.x() + 1, mPos.y() + 1,
        mSize.x()-2, mSize.y(), 3, 4, Color(0, 32), Color(0, 92));
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), 3);
    nvgFillPaint(ctx, paint);
    nvgFill(ctx);

    float value = std::min(std::max(0.0f, mValue), 1.0f);
    int barPos = (int) std::round((mSize.x() - 2) * value);

    paint = nvgBoxGradient(
        ctx, mPos.x(), mPos.y(),
        barPos+1.5f, mSize.y()-1, 3, 4,
        Color(220, 100), Color(128, 100));

    nvgBeginPath(ctx);
    nvgRoundedRect(
        ctx, mPos.x()+1, mPos.y()+1,
        barPos, mSize.y()-2, 3);
    nvgFillPaint(ctx, paint);
    nvgFill(ctx);
}

/******************************** Textbox **************************************************/

TextBox::TextBox(Widget *parent,const std::string &value)
    : Widget(parent),
      mEditable(false),
      mCommitted(true),
      mValue(value),
      mDefaultValue(""),
      mAlignment(Alignment::Center),
      mUnits(""),
      mFormat(""),
      mUnitsImage(-1),
      mValidFormat(true),
      mValueTemp(value),
      mCursorPos(-1),
      mSelectionPos(-1),
      mMousePos(Vec2i(-1,-1)),
      mMouseDownPos(Vec2i(-1,-1)),
      mMouseDragPos(Vec2i(-1,-1)),
      mMouseDownModifier(0),
      mTextOffset(0),
      mLastClick(0) {
    mFontSize = mTheme->mTextBoxFontSize;
}

void TextBox::setEditable(bool editable) {
    mEditable = editable;
    setCursor(editable ? Cursor::IBeam : Cursor::Arrow);
}

Vec2i TextBox::preferredSize(NVGcontext *ctx) const {
    Vec2i size(0, fontSize() * 1.4f);

    float uw = 0;
    if (mUnitsImage > 0) {
        int w, h;
        nvgImageSize(ctx, mUnitsImage, &w, &h);
        float uh = size.y() * 0.4f;
        uw = w * uh / h;
    } else if (!mUnits.empty()) {
        uw = nvgTextBounds(ctx, 0, 0, mUnits.c_str(), nullptr, nullptr);
    }

    float ts = nvgTextBounds(ctx, 0, 0, mValue.c_str(), nullptr, nullptr);
    size.rx() = size.y() + ts + uw;
    return size;
}

void TextBox::draw(NVGcontext* ctx) {
    Widget::draw(ctx);

    NVGpaint bg = nvgBoxGradient(ctx,
        mPos.x() + 1, mPos.y() + 1 + 1.0f, mSize.x() - 2, mSize.y() - 2,
        3, 4, Color(255, 32), Color(32, 32));
    NVGpaint fg1 = nvgBoxGradient(ctx,
        mPos.x() + 1, mPos.y() + 1 + 1.0f, mSize.x() - 2, mSize.y() - 2,
        3, 4, Color(150, 32), Color(32, 32));
    NVGpaint fg2 = nvgBoxGradient(ctx,
        mPos.x() + 1, mPos.y() + 1 + 1.0f, mSize.x() - 2, mSize.y() - 2,
        3, 4, nvgRGBA(255, 0, 0, 100), nvgRGBA(255, 0, 0, 50));

    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x() + 1, mPos.y() + 1 + 1.0f, mSize.x() - 2,
                   mSize.y() - 2, 3);

    if(mEditable && focused())
        mValidFormat ? nvgFillPaint(ctx, fg1) : nvgFillPaint(ctx, fg2);
    else
        nvgFillPaint(ctx, bg);

    nvgFill(ctx);

    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, mPos.x() + 0.5f, mPos.y() + 0.5f, mSize.x() - 1,
                   mSize.y() - 1, 2.5f);
    nvgStrokeColor(ctx, Color(0, 48));
    nvgStroke(ctx);

    nvgFontSize(ctx, fontSize());
    nvgFontFace(ctx, "sans");
    Vec2i drawPos(mPos.x(), mPos.y() + mSize.y() * 0.5f + 1);

    float xSpacing = mSize.y() * 0.3f;

    float unitWidth = 0;

    if (mUnitsImage > 0) {
        int w, h;
        nvgImageSize(ctx, mUnitsImage, &w, &h);
        float unitHeight = mSize.y() * 0.4f;
        unitWidth = w * unitHeight / h;
        NVGpaint imgPaint = nvgImagePattern(
            ctx, mPos.x() + mSize.x() - xSpacing - unitWidth,
            drawPos.y() - unitHeight * 0.5f, unitWidth, unitHeight, 0,
            mUnitsImage, mEnabled ? 0.7f : 0.35f);
        nvgBeginPath(ctx);
        nvgRect(ctx, mPos.x() + mSize.x() - xSpacing - unitWidth,
                drawPos.y() - unitHeight * 0.5f, unitWidth, unitHeight);
        nvgFillPaint(ctx, imgPaint);
        nvgFill(ctx);
        unitWidth += 2;
    } else if (!mUnits.empty()) {
        unitWidth = nvgTextBounds(ctx, 0, 0, mUnits.c_str(), nullptr, nullptr);
        nvgFillColor(ctx, Color(255, mEnabled ? 64 : 32));
        nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_MIDDLE);
        nvgText(ctx, mPos.x() + mSize.x() - xSpacing, drawPos.y(),
                mUnits.c_str(), nullptr);
        unitWidth += 2;
    }

    switch (mAlignment) {
        case Alignment::Left:
            nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
            drawPos.rx() += xSpacing;
            break;
        case Alignment::Right:
            nvgTextAlign(ctx, NVG_ALIGN_RIGHT | NVG_ALIGN_MIDDLE);
            drawPos.rx() += mSize.x() - unitWidth - xSpacing;
            break;
        case Alignment::Center:
            nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
            drawPos.rx() += mSize.x() * 0.5f;
            break;
    }

    nvgFontSize(ctx, fontSize());
    nvgFillColor(ctx,
                 mEnabled ? mTheme->mTextColor : mTheme->mDisabledTextColor);

    // clip visible text area
    float clipX = mPos.x() + xSpacing - 1.0f;
    float clipY = mPos.y() + 1.0f;
    float clipWidth = mSize.x() - unitWidth - 2 * xSpacing + 2.0f;
    float clipHeight = mSize.y() - 3.0f;
    nvgScissor(ctx, clipX, clipY, clipWidth, clipHeight);

    Vec2i oldDrawPos(drawPos);
    drawPos.rx() += mTextOffset;

    if (mCommitted) {
        nvgText(ctx, drawPos.x(), drawPos.y(), mValue.c_str(), nullptr);
    } else {
        const int maxGlyphs = 1024;
        NVGglyphPosition glyphs[maxGlyphs];
        float textBound[4];
        nvgTextBounds(ctx, drawPos.x(), drawPos.y(), mValueTemp.c_str(),
                      nullptr, textBound);
        float lineh = textBound[3] - textBound[1];

        // find cursor positions
        int nglyphs =
            nvgTextGlyphPositions(ctx, drawPos.x(), drawPos.y(),
                                  mValueTemp.c_str(), nullptr, glyphs, maxGlyphs);
        updateCursor(ctx, textBound[2], glyphs, nglyphs);

        // compute text offset
        int prevCPos = mCursorPos > 0 ? mCursorPos - 1 : 0;
        int nextCPos = mCursorPos < nglyphs ? mCursorPos + 1 : nglyphs;
        float prevCX = cursorIndex2Position(prevCPos, textBound[2], glyphs, nglyphs);
        float nextCX = cursorIndex2Position(nextCPos, textBound[2], glyphs, nglyphs);

        if (nextCX > clipX + clipWidth)
            mTextOffset -= nextCX - (clipX + clipWidth) + 1;
        if (prevCX < clipX)
            mTextOffset += clipX - prevCX + 1;

        drawPos.rx() = oldDrawPos.x() + mTextOffset;

        // draw text with offset
        nvgText(ctx, drawPos.x(), drawPos.y(), mValueTemp.c_str(), nullptr);
        nvgTextBounds(ctx, drawPos.x(), drawPos.y(), mValueTemp.c_str(),
                      nullptr, textBound);

        // recompute cursor positions
        nglyphs = nvgTextGlyphPositions(ctx, drawPos.x(), drawPos.y(),
                mValueTemp.c_str(), nullptr, glyphs, maxGlyphs);

        if (mCursorPos > -1) {
            if (mSelectionPos > -1) {
                float caretx = cursorIndex2Position(mCursorPos, textBound[2],
                                                    glyphs, nglyphs);
                float selx = cursorIndex2Position(mSelectionPos, textBound[2],
                                                  glyphs, nglyphs);

                if (caretx > selx)
                    std::swap(caretx, selx);

                // draw selection
                nvgBeginPath(ctx);
                nvgFillColor(ctx, nvgRGBA(255, 255, 255, 80));
                nvgRect(ctx, caretx, drawPos.y() - lineh * 0.5f, selx - caretx,
                        lineh);
                nvgFill(ctx);
            }

            float caretx = cursorIndex2Position(mCursorPos, textBound[2], glyphs, nglyphs);

            // draw cursor
            nvgBeginPath(ctx);
            nvgMoveTo(ctx, caretx, drawPos.y() - lineh * 0.5f);
            nvgLineTo(ctx, caretx, drawPos.y() + lineh * 0.5f);
            nvgStrokeColor(ctx, nvgRGBA(255, 192, 0, 255));
            nvgStrokeWidth(ctx, 1.0f);
            nvgStroke(ctx);
        }
    }

    nvgResetScissor(ctx);
}

bool TextBox::mouseButtonEvent(const Vec2i &p, int button, bool down,
                               int modifiers)
{
    Widget::mouseButtonEvent(p, button, down, modifiers);

    if (mEditable && focused() && button == MOUSE_BUTTON_LEFT)
    {
        if (down)
        {
            mMouseDownPos = p;
            mMouseDownModifier = modifiers;

            double time = __getTime();
            if (time - mLastClick < 0.25) {
                /* Double-click: select all text */
                mSelectionPos = 0;
                mCursorPos = (int) mValueTemp.size();
                mMouseDownPos = Vec2i(-1, 1);
            }
            mLastClick = time;
        } else {
            mMouseDownPos = Vec2i(-1, -1);
            mMouseDragPos = Vec2i(-1, -1);
        }
        return true;
    }

    return false;
}

bool TextBox::mouseMotionEvent(const Vec2i &p, const Vec2i & /* rel */,
                               int /* button */, int /* modifiers */) {
    if (mEditable && focused()) {
        mMousePos = p;
        return true;
    }
    return false;
}

bool TextBox::mouseDragEvent(const Vec2i &p, const Vec2i &/* rel */,
                             int /* button */, int /* modifiers */) {
    if (mEditable && focused()) {
        mMouseDragPos = p;
        return true;
    }
    return false;
}

bool TextBox::mouseEnterEvent(const Vec2i &p, bool enter) {
    Widget::mouseEnterEvent(p, enter);
    return false;
}

bool TextBox::focusEvent(bool focused) {
    Widget::focusEvent(focused);

    std::string backup = mValue;

    if (mEditable) {
        if (focused) {
            mValueTemp = mValue;
            mCommitted = false;
            mCursorPos = 0;
        } else {
            if (mValidFormat) {
                if (mValueTemp == "")
                    mValue = mDefaultValue;
                else
                    mValue = mValueTemp;
            }

            if (mCallback && !mCallback(mValue))
                mValue = backup;

            mValidFormat = true;
            mCommitted = true;
            mCursorPos = -1;
            mSelectionPos = -1;
            mTextOffset = 0;
        }

        mValidFormat = (mValueTemp == "") || checkFormat(mValueTemp, mFormat);
    }

    return true;
}

bool TextBox::keyboardEvent(int key, int /* scancode */, int action, int modifiers)
{
    if (mEditable && focused()) {
        if (action == KEYBOARD_KEY_DOWN /*|| action == GLFW_REPEAT*/)
        {
            if (key == KEYBOARD_KEY_LEFT )
            {
                if (modifiers == KEYBOARD_KEY_LSHIFT)
                {
                    if (mSelectionPos == -1)
                        mSelectionPos = mCursorPos;
                } else {
                    mSelectionPos = -1;
                }

                if (mCursorPos > 0)
                    mCursorPos--;
            } else if (key == KEYBOARD_KEY_RIGHT) {
                if (modifiers == KEYBOARD_KEY_LSHIFT) {
                    if (mSelectionPos == -1)
                        mSelectionPos = mCursorPos;
                } else {
                    mSelectionPos = -1;
                }

                if (mCursorPos < (int) mValueTemp.length())
                    mCursorPos++;
            } else if (key == KEYBOARD_KEY_HOME) {
                if (modifiers == KEYBOARD_KEY_LSHIFT) {
                    if (mSelectionPos == -1)
                        mSelectionPos = mCursorPos;
                } else {
                    mSelectionPos = -1;
                }

                mCursorPos = 0;
            } else if (key == KEYBOARD_KEY_END) {
                if (modifiers == KEYBOARD_KEY_LSHIFT) {
                    if (mSelectionPos == -1)
                        mSelectionPos = mCursorPos;
                } else {
                    mSelectionPos = -1;
                }

                mCursorPos = (int) mValueTemp.size();
            } else if (key == KEYBOARD_KEY_BACKSPACE) {
                if (!deleteSelection()) {
                    if (mCursorPos > 0) {
                        mValueTemp.erase(mValueTemp.begin() + mCursorPos - 1);
                        mCursorPos--;
                    }
                }
            } else if (key == KEYBOARD_KEY_DELETE) {
                if (!deleteSelection()) {
                    if (mCursorPos < (int) mValueTemp.length())
                        mValueTemp.erase(mValueTemp.begin() + mCursorPos);
                }
            }
            else if (key == KEYBOARD_KEY_RETURN)
            {
                if (!mCommitted)
                    focusEvent(false);
            }
            else if (key == KEYBOARD_KEY_A && modifiers == KEYBOARD_KEY_RCTRL)
            {
                mCursorPos = (int) mValueTemp.length();
                mSelectionPos = 0;
            }
            else if (key == KEYBOARD_KEY_X && modifiers == KEYBOARD_KEY_RCTRL)
            {
                copySelection();
                deleteSelection();
            }
            else if (key == KEYBOARD_KEY_C && modifiers == KEYBOARD_KEY_RCTRL)
            {
                copySelection();
            }
            else if (key == KEYBOARD_KEY_V && modifiers == KEYBOARD_KEY_RCTRL)
            {
                deleteSelection();
                pasteFromClipboard();
            }

            mValidFormat =
                (mValueTemp == "") || checkFormat(mValueTemp, mFormat);
        }

        return true;
    }

    return false;
}

bool TextBox::keyboardCharacterEvent(unsigned int codepoint) {
    if (mEditable && focused()) {
        std::ostringstream convert;
        convert << (char) codepoint;

        deleteSelection();
        mValueTemp.insert(mCursorPos, convert.str());
        mCursorPos++;

        mValidFormat = (mValueTemp == "") || checkFormat(mValueTemp, mFormat);

        return true;
    }

    return false;
}

bool TextBox::checkFormat(const std::string &input, const std::string &format) {
    if (format.empty())
        return true;
    std::regex regex(format);
    return regex_match(input, regex);
}

bool TextBox::copySelection()
{
    if (mSelectionPos > -1) {

        int begin = mCursorPos;
        int end = mSelectionPos;

        if (begin > end)
            std::swap(begin, end);
#ifdef NNGUI_GLFW
        Screen *sc = dynamic_cast<Screen *>(this->window()->parent());
        glfwSetClipboardString(sc->window(),
                               mValueTemp.substr(begin, end).c_str());
#elif defined NNGUI_SDL
        SDL_SetClipboardText( mValueTemp.substr(begin, end).c_str());
#endif
        return true;
    }

    return false;
}

void TextBox::pasteFromClipboard()
{
#ifdef NNGUI_GLFW
    Screen *sc = dynamic_cast<Screen *>(this->window()->parent());
    std::string str(glfwGetClipboardString(sc->window()));
#elif defined NNGUI_SDL
    std::string str( SDL_GetClipboardText() );
#endif

    mValueTemp.insert(mCursorPos, str);
}

bool TextBox::deleteSelection()
{
    if (mSelectionPos > -1) {
        int begin = mCursorPos;
        int end = mSelectionPos;

        if (begin > end)
            std::swap(begin, end);

        if (begin == end - 1)
            mValueTemp.erase(mValueTemp.begin() + begin);
        else
            mValueTemp.erase(mValueTemp.begin() + begin,
                             mValueTemp.begin() + end);

        mCursorPos = begin;
        mSelectionPos = -1;
        return true;
    }

    return false;
}

void TextBox::updateCursor(NVGcontext *, float lastx,
                           const NVGglyphPosition *glyphs, int size)
                           {
    // handle mouse cursor events
    if (mMouseDownPos.x() != -1) {
        if (mMouseDownModifier == KEYBOARD_KEY_LSHIFT) {
            if (mSelectionPos == -1)
                mSelectionPos = mCursorPos;
        } else
            mSelectionPos = -1;

        mCursorPos =
            position2CursorIndex(mMouseDownPos.x(), lastx, glyphs, size);

        mMouseDownPos = Vec2i(-1, -1);
    } else if (mMouseDragPos.x() != -1) {
        if (mSelectionPos == -1)
            mSelectionPos = mCursorPos;

        mCursorPos =
            position2CursorIndex(mMouseDragPos.x(), lastx, glyphs, size);
    } else {
        // set cursor to last character
        if (mCursorPos == -2)
            mCursorPos = size;
    }

    if (mCursorPos == mSelectionPos)
        mSelectionPos = -1;
}

float TextBox::cursorIndex2Position(int index, float lastx,
                                    const NVGglyphPosition *glyphs, int size) {
    float pos = 0;
    if (index == size)
        pos = lastx; // last character
    else
        pos = glyphs[index].x;

    return pos;
}

int TextBox::position2CursorIndex(float posx, float lastx,
                                  const NVGglyphPosition *glyphs, int size) {
    int mCursorId = 0;
    float caretx = glyphs[mCursorId].x;
    for (int j = 1; j < size; j++) {
        if (std::abs(caretx - posx) > std::abs(glyphs[j].x - posx)) {
            mCursorId = j;
            caretx = glyphs[mCursorId].x;
        }
    }
    if (std::abs(caretx - posx) > std::abs(lastx - posx))
        mCursorId = size;

    return mCursorId;
}

/************************************** Label **************************************/

Label::Label(Widget *parent, const std::string &caption, const std::string &font, int fontSize)
    : Widget(parent), mCaption(caption), mFont(font) {
    mFontSize = fontSize < 0 ? mTheme->mStandardFontSize : fontSize;
    mColor = mTheme->mTextColor;
}

Vec2i Label::preferredSize(NVGcontext *ctx) const {
    if (mCaption == "")
        return Vec2i::Zero();
    nvgFontFace(ctx, mFont.c_str());
    nvgFontSize(ctx, fontSize());
    if (mFixedSize.x() > 0) {
        float bounds[4];
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgTextBoxBounds(ctx, mPos.x(), mPos.y(), mFixedSize.x(), mCaption.c_str(), nullptr, bounds);
        return Vec2i(
            mFixedSize.x(), (bounds[3]-bounds[1])
        );
    } else {
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        return Vec2i(
            nvgTextBounds(ctx, 0, 0, mCaption.c_str(), nullptr, nullptr),
            mTheme->mStandardFontSize
        );
    }
}

void Label::draw(NVGcontext *ctx)
{
    Widget::draw(ctx);
    nvgFontFace(ctx, mFont.c_str());
    nvgFontSize(ctx, fontSize());
    nvgFillColor(ctx, mColor);
    if (mFixedSize.x() > 0) {
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgTextBox(ctx, mPos.x(), mPos.y(), mFixedSize.x(), mCaption.c_str(), nullptr);
    } else {
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        nvgText(ctx, mPos.x(), mPos.y() + mSize.y() * 0.5f, mCaption.c_str(), nullptr);
    }
}

/*********************************************** Screen *********************************************/

static bool __glInit = false;

std::map<Screen::ParentWindowPtr, Screen *> __nngui_screens;

static void __initGl(Screen::ParentWindowPtr window)
{
   if( !__glInit )
   {
    __glInit = true;

#ifdef NNGUI_SDL
    #define ASSIGNGLFUNCTION(type,name) name = (type)SDL_GL_GetProcAddress( #name );
#elif defined NNGUI_GLFW
    #define ASSIGNGLFUNCTION(type,name) name = (type)glfwGetProcAddress( #name );
#endif

#ifndef GL_GLEXT_PROTOTYPES
#ifdef WIN32
    ASSIGNGLFUNCTION(PFNGLACTIVETEXTUREPROC,glActiveTexture)
#endif
    ASSIGNGLFUNCTION(PFNGLCREATESHADERPROC,glCreateShader)
    ASSIGNGLFUNCTION(PFNGLSHADERSOURCEPROC,glShaderSource)
    ASSIGNGLFUNCTION(PFNGLUNIFORMMATRIX4FVPROC,glUniformMatrix4fv)
    ASSIGNGLFUNCTION(PFNGLCOMPILESHADERPROC,glCompileShader)
    ASSIGNGLFUNCTION(PFNGLGETSHADERIVPROC,glGetShaderiv)
    ASSIGNGLFUNCTION(PFNGLUSEPROGRAMPROC,glUseProgram)
    ASSIGNGLFUNCTION(PFNGLUNIFORM1IPROC,glUniform1i)
    ASSIGNGLFUNCTION(PFNGLUNIFORM1FPROC,glUniform1f)
    ASSIGNGLFUNCTION(PFNGLUNIFORM2IPROC,glUniform2i)
    ASSIGNGLFUNCTION(PFNGLUNIFORM2FPROC,glUniform2f)
    ASSIGNGLFUNCTION(PFNGLUNIFORM3FPROC,glUniform3f)
    ASSIGNGLFUNCTION(PFNGLUNIFORM4FPROC,glUniform4f)
    ASSIGNGLFUNCTION(PFNGLUNIFORM4FVPROC,glUniform4fv)
    ASSIGNGLFUNCTION(PFNGLCREATEPROGRAMPROC,glCreateProgram)
    ASSIGNGLFUNCTION(PFNGLATTACHSHADERPROC,glAttachShader)
    ASSIGNGLFUNCTION(PFNGLGETSHADERINFOLOGPROC,glGetShaderInfoLog)
    ASSIGNGLFUNCTION(PFNGLGETUNIFORMBLOCKINDEXPROC,glGetUniformBlockIndex)
    ASSIGNGLFUNCTION(PFNGLUNIFORMBLOCKBINDINGPROC,glUniformBlockBinding)
    ASSIGNGLFUNCTION(PFNGLBINDATTRIBLOCATIONPROC,glBindAttribLocation)
    ASSIGNGLFUNCTION(PFNGLLINKPROGRAMPROC,glLinkProgram)
    ASSIGNGLFUNCTION(PFNGLGETPROGRAMIVPROC,glGetProgramiv)
    ASSIGNGLFUNCTION(PFNGLGENVERTEXARRAYSPROC,glGenVertexArrays)
    ASSIGNGLFUNCTION(PFNGLGETPROGRAMINFOLOGPROC,glGetProgramInfoLog)
    ASSIGNGLFUNCTION(PFNGLBINDVERTEXARRAYPROC,glBindVertexArray)
    ASSIGNGLFUNCTION(PFNGLBINDBUFFERPROC,glBindBuffer)
    ASSIGNGLFUNCTION(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation)
    ASSIGNGLFUNCTION(PFNGLGETUNIFORMLOCATIONPROC,glGetUniformLocation)
    ASSIGNGLFUNCTION(PFNGLGENBUFFERSPROC, glGenBuffers)
    ASSIGNGLFUNCTION(PFNGLBUFFERDATAPROC, glBufferData)
    ASSIGNGLFUNCTION(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray)
    ASSIGNGLFUNCTION(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray)
    ASSIGNGLFUNCTION(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData)
    ASSIGNGLFUNCTION(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer)
    ASSIGNGLFUNCTION(PFNGLDELETEBUFFERSPROC, glDeleteBuffers)
    ASSIGNGLFUNCTION(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer)
    ASSIGNGLFUNCTION(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer)
    ASSIGNGLFUNCTION(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage)
    ASSIGNGLFUNCTION(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays)
    ASSIGNGLFUNCTION(PFNGLDELETEPROGRAMPROC, glDeleteProgram)
    ASSIGNGLFUNCTION(PFNGLDELETESHADERPROC, glDeleteShader)
    ASSIGNGLFUNCTION(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers)
    ASSIGNGLFUNCTION(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC, glRenderbufferStorageMultisample)
    ASSIGNGLFUNCTION(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers)
    ASSIGNGLFUNCTION(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer)
    ASSIGNGLFUNCTION(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus)
    ASSIGNGLFUNCTION(PFNGLDELETERENDERBUFFERSPROC, glDeleteRenderbuffers)
    ASSIGNGLFUNCTION(PFNGLBLITFRAMEBUFFERPROC, glBlitFramebuffer)

    ASSIGNGLFUNCTION(PFNGLGENERATEMIPMAPPROC,glGenerateMipmap)
    ASSIGNGLFUNCTION(PFNGLBINDBUFFERRANGEPROC,glBindBufferRange)
    ASSIGNGLFUNCTION(PFNGLSTENCILOPSEPARATEPROC,glStencilOpSeparate)
    ASSIGNGLFUNCTION(PFNGLUNIFORM2FVPROC,glUniform2fv)
#else
    glfwMakeContextCurrent(window);
#ifdef WIN32
    ASSIGNGLFUNCTION(PFNGLACTIVETEXTUREPROC,glActiveTexture)
    ASSIGNGLFUNCTION(PFNGLCREATESHADERPROC,glCreateShader)
    ASSIGNGLFUNCTION(PFNGLSHADERSOURCEPROC,glShaderSource)
    //ASSIGNGLFUNCTION(PFNGLUNIFORMMATRIX4FVPROC,glUniformMatrix4fv)
    ASSIGNGLFUNCTION(PFNGLCOMPILESHADERPROC,glCompileShader)
    ASSIGNGLFUNCTION(PFNGLGETSHADERIVPROC,glGetShaderiv)
    ASSIGNGLFUNCTION(PFNGLUSEPROGRAMPROC,glUseProgram)
    ASSIGNGLFUNCTION(PFNGLUNIFORM1IPROC,glUniform1i)
    //ASSIGNGLFUNCTION(PFNGLUNIFORM1FPROC,glUniform1f)
    //ASSIGNGLFUNCTION(PFNGLUNIFORM2IPROC,glUniform2i)
    //ASSIGNGLFUNCTION(PFNGLUNIFORM2FPROC,glUniform2f)
    //ASSIGNGLFUNCTION(PFNGLUNIFORM3FPROC,glUniform3f)
    //ASSIGNGLFUNCTION(PFNGLUNIFORM4FPROC,glUniform4f)
    ASSIGNGLFUNCTION(PFNGLUNIFORM4FVPROC,glUniform4fv)
    ASSIGNGLFUNCTION(PFNGLCREATEPROGRAMPROC,glCreateProgram)
    ASSIGNGLFUNCTION(PFNGLATTACHSHADERPROC,glAttachShader)
    ASSIGNGLFUNCTION(PFNGLGETSHADERINFOLOGPROC,glGetShaderInfoLog)
    //ASSIGNGLFUNCTION(PFNGLGETUNIFORMBLOCKINDEXPROC,glGetUniformBlockIndex)
    //ASSIGNGLFUNCTION(PFNGLUNIFORMBLOCKBINDINGPROC,glUniformBlockBinding)
    ASSIGNGLFUNCTION(PFNGLBINDATTRIBLOCATIONPROC,glBindAttribLocation)
    ASSIGNGLFUNCTION(PFNGLLINKPROGRAMPROC,glLinkProgram)
    ASSIGNGLFUNCTION(PFNGLGETPROGRAMIVPROC,glGetProgramiv)
    //ASSIGNGLFUNCTION(PFNGLGENVERTEXARRAYSPROC,glGenVertexArrays)
    ASSIGNGLFUNCTION(PFNGLGETPROGRAMINFOLOGPROC,glGetProgramInfoLog)
    //ASSIGNGLFUNCTION(PFNGLBINDVERTEXARRAYPROC,glBindVertexArray)
    ASSIGNGLFUNCTION(PFNGLBINDBUFFERPROC,glBindBuffer)
    //ASSIGNGLFUNCTION(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation)
    ASSIGNGLFUNCTION(PFNGLGETUNIFORMLOCATIONPROC,glGetUniformLocation)
    ASSIGNGLFUNCTION(PFNGLGENBUFFERSPROC, glGenBuffers)
    ASSIGNGLFUNCTION(PFNGLBUFFERDATAPROC, glBufferData)
    ASSIGNGLFUNCTION(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray)
    ASSIGNGLFUNCTION(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray)
    //ASSIGNGLFUNCTION(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData)
    ASSIGNGLFUNCTION(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer)
    ASSIGNGLFUNCTION(PFNGLDELETEBUFFERSPROC, glDeleteBuffers)
    //ASSIGNGLFUNCTION(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer)
    //ASSIGNGLFUNCTION(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer)
    //ASSIGNGLFUNCTION(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage)
    //ASSIGNGLFUNCTION(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays)
    ASSIGNGLFUNCTION(PFNGLDELETEPROGRAMPROC, glDeleteProgram)
    ASSIGNGLFUNCTION(PFNGLDELETESHADERPROC, glDeleteShader)
    //ASSIGNGLFUNCTION(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers)
    //ASSIGNGLFUNCTION(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC, glRenderbufferStorageMultisample)
    //ASSIGNGLFUNCTION(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers)
    //ASSIGNGLFUNCTION(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer)
    //ASSIGNGLFUNCTION(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus)
    //ASSIGNGLFUNCTION(PFNGLDELETERENDERBUFFERSPROC, glDeleteRenderbuffers)
    //ASSIGNGLFUNCTION(PFNGLBLITFRAMEBUFFERPROC, glBlitFramebuffer)

    //ASSIGNGLFUNCTION(PFNGLGENERATEMIPMAPPROC,glGenerateMipmap)
    //ASSIGNGLFUNCTION(PFNGLBINDBUFFERRANGEPROC,glBindBufferRange)
    ASSIGNGLFUNCTION(PFNGLSTENCILOPSEPARATEPROC,glStencilOpSeparate)
    ASSIGNGLFUNCTION(PFNGLUNIFORM2FVPROC,glUniform2fv)
#endif
#endif
   }
}

Screen::Screen(ParentWindowPtr window, const Vec2i&, const std::string &caption,
               bool, bool)
    : Widget(nullptr), _window(nullptr), mNVGContext(nullptr), mCaption(caption)  
{
    __initGl(window);
    initialize(window);
}

#ifdef NNGUI_SDL
void Screen::onEvent(SDL_Event& event)
{
    auto it = __nngui_screens.find(_window);
    if (it == __nngui_screens.end())
       return;

    if (!mProcessEvents)
        return;

    switch (event.type)
    {
    case SDL_MOUSEMOTION:
    {
      if (!mProcessEvents)
         return;
      cursorPosCallbackEvent(event.motion.x, event.motion.y);
    }
    break;

    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    {
      if (!mProcessEvents)
        return;

      SDL_Keymod mods = SDL_GetModState();
      mouseButtonCallbackEvent(event.button.button, event.button.type, mods);
    }
    break;

    case SDL_KEYDOWN:
    case SDL_KEYUP:
    {
      if (!mProcessEvents)
        return;

      SDL_Keymod mods = SDL_GetModState();
      keyCallbackEvent(event.key.keysym.mod, event.key.keysym.scancode, event.key.state, mods);
    }
    break;

    case SDL_TEXTINPUT:
    {
      if (!mProcessEvents)
        return;
      charCallbackEvent(event.text.text[0]);
    }
    break;
    }
}
#endif

void Screen::initialize(ParentWindowPtr window)
{
    _window = window;

    __getWindowSize(window, &mSize.rx(), &mSize.ry());
    __getFramebufferSize(window, &mFBSize.rx(), &mFBSize.ry());

#ifdef NDEBUG
    mNVGContext = nvgCreateX(false);
#else
    mNVGContext = nvgCreateX(true);
#endif
    if (mNVGContext == nullptr)
        throw std::runtime_error("Could not initialize NanoVG!");

    mVisible = true;
    mTheme = new Theme(mNVGContext);
    mMousePos = Vec2i::Zero();
    mMouseState = mModifiers = 0;
    mDragActive = false;
    mLastInteraction = __getTime();
    mProcessEvents = true;
    mBackground = Color(0.3f, 0.3f, 0.32f, 1.f);
    __nngui_screens[_window] = this;
}

Screen::~Screen()
{
    __nngui_screens.erase(_window);
    if (mNVGContext)
        nvgDeleteX(mNVGContext);
}

void Screen::setVisible(bool visible)
{
    if (mVisible != visible)
     {
        mVisible = visible;

        if (visible)
            __showWindow(_window);
        else
            __hideWindow(_window);
    }
}

void Screen::setCaption(const std::string &caption)
{
    if (caption != mCaption)
    {
        __setWindowTitle( _window, caption.c_str());
        mCaption = caption;
    }
}

void Screen::setSize(const Vec2i &size)
{
    Widget::setSize(size);
    __setWindowSize(_window, size.x(), size.y());
}

void Screen::drawAll()
{
    drawContents();
    drawWidgets();
}

void Screen::drawWidgets()
{
    if (!mVisible)
        return;

    __getFramebufferSize( _window, &mFBSize.rx(), &mFBSize.ry());
    __getWindowSize( _window, &mSize.rx(), &mSize.ry());
    glViewport(0, 0, mFBSize.x(), mFBSize.y());

    /* Calculate pixel ratio for hi-dpi devices. */
    mPixelRatio = (float) mFBSize.x() / (float) mSize.x();
    nvgBeginFrame(mNVGContext, mSize.x(), mSize.y(), mPixelRatio);

    draw(mNVGContext);

    double elapsed = __getTime() - mLastInteraction;

    if (elapsed > 0.5f) {
        /* Draw tooltips */
        const Widget *widget = findWidget(mMousePos);
        if (widget && !widget->tooltip().empty()) {
            int tooltipWidth = 150;

            float bounds[4];
            nvgFontFace(mNVGContext, "sans");
            nvgFontSize(mNVGContext, 15.0f);
            nvgTextAlign(mNVGContext, NVG_ALIGN_CENTER | NVG_ALIGN_TOP);
            nvgTextLineHeight(mNVGContext, 1.1f);
            Vec2i pos = widget->absolutePosition() +
                           Vec2i(widget->width() / 2, widget->height() + 10);

            nvgTextBoxBounds(mNVGContext, pos.x(), pos.y(), tooltipWidth,
                             widget->tooltip().c_str(), nullptr, bounds);

            nvgGlobalAlpha(mNVGContext,
                           std::min(1.0, 2 * (elapsed - 0.5f)) * 0.8);

            nvgBeginPath(mNVGContext);
            nvgFillColor(mNVGContext, Color(0, 255));
            int h = (bounds[2] - bounds[0]) / 2;
            nvgRoundedRect(mNVGContext, bounds[0] - 4 - h, bounds[1] - 4,
                           (int) (bounds[2] - bounds[0]) + 8,
                           (int) (bounds[3] - bounds[1]) + 8, 3);

            int px = (int) ((bounds[2] + bounds[0]) / 2) - h;
            nvgMoveTo(mNVGContext, px, bounds[1] - 10);
            nvgLineTo(mNVGContext, px + 7, bounds[1] + 1);
            nvgLineTo(mNVGContext, px - 7, bounds[1] + 1);
            nvgFill(mNVGContext);

            nvgFillColor(mNVGContext, Color(255, 255));
            nvgFontBlur(mNVGContext, 0.0f);
            nvgTextBox(mNVGContext, pos.x() - h, pos.y(), tooltipWidth,
                       widget->tooltip().c_str(), nullptr);
        }
    }

    nvgEndFrame(mNVGContext);
}

bool Screen::keyboardEvent(int key, int scancode, int action, int modifiers) {
    if (mFocusPath.size() > 0) {
        for (auto it = mFocusPath.rbegin() + 1; it != mFocusPath.rend(); ++it)
            if ((*it)->focused() && (*it)->keyboardEvent(key, scancode, action, modifiers))
                return true;
    }

    return false;
}

bool Screen::keyboardCharacterEvent(unsigned int codepoint) {
    if (mFocusPath.size() > 0) {
        for (auto it = mFocusPath.rbegin() + 1; it != mFocusPath.rend(); ++it)
            if ((*it)->focused() && (*it)->keyboardCharacterEvent(codepoint))
                return true;
    }
    return false;
}

bool Screen::cursorPosCallbackEvent(double x, double y) {
    if (!mayProcessEvents())
        return false;

    Vec2i p((int) x, (int) y);
    bool ret = false;
    mLastInteraction = __getTime();
    try {
        p -= Vec2i(1, 2);

        if (!mDragActive) {
            /*Widget *widget = findWidget(p);
            if (widget != nullptr && widget->cursor() != mCursor) {
                mCursor = widget->cursor();
                glfwSetCursor(mGLFWWindow, mCursors[(int) mCursor]);
            }*/
        } else {
            ret = mDragWidget->mouseDragEvent(
                p - mDragWidget->parent()->absolutePosition(), p - mMousePos,
                mMouseState, mModifiers);
        }

        if (!ret)
            ret = mouseMotionEvent(p, p - mMousePos, mMouseState, mModifiers);

        mMousePos = p;

        return ret;
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
        abort();
    }

    return false;
}

bool Screen::mouseButtonCallbackEvent(int button, int action, int modifiers) {
    if (!mayProcessEvents())
        return false;

    mModifiers = modifiers;
    mLastInteraction = __getTime();
    try {
        if (mFocusPath.size() > 1) {
            const Window *window =
                dynamic_cast<Window *>(mFocusPath[mFocusPath.size() - 2]);
            if (window && window->modal()) {
                if (!window->contains(mMousePos))
                    return false;
            }
        }

        if (action == MOUSE_BUTTON_PRESS)
            mMouseState |= 1 << button;
        else
            mMouseState &= ~(1 << button);

        auto dropWidget = findWidget(mMousePos);
        if (mDragActive && action == MOUSE_BUTTON_RELEASE &&
            dropWidget != mDragWidget)
            mDragWidget->mouseButtonEvent(
                mMousePos - mDragWidget->parent()->absolutePosition(), button,
                false, mModifiers);

        /*if (dropWidget != nullptr && dropWidget->cursor() != mCursor) {
            mCursor = dropWidget->cursor();
            glfwSetCursor(mGLFWWindow, mCursors[(int) mCursor]);
        }*/

        if (action == MOUSE_BUTTON_PRESS && button == MOUSE_BUTTON_LEFT) {
            mDragWidget = findWidget(mMousePos);
            if (mDragWidget == this)
                mDragWidget = nullptr;
            mDragActive = mDragWidget != nullptr;
            if (!mDragActive)
                updateFocus(nullptr);
        } else {
            mDragActive = false;
            mDragWidget = nullptr;
        }

        return mouseButtonEvent(mMousePos, button, action == MOUSE_BUTTON_PRESS,
                                mModifiers);
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
        abort();
    }

    return false;
}

bool Screen::keyCallbackEvent(int key, int scancode, int action, int mods)
{
    if (!mayProcessEvents())
        return false;

    mLastInteraction = __getTime();
    try {
        return keyboardEvent(key, scancode, action, mods);
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
        abort();
    }
}

bool Screen::charCallbackEvent(unsigned int codepoint)
 {
    if (!mayProcessEvents())
        return false;

    mLastInteraction = __getTime();
    try {
        return keyboardCharacterEvent(codepoint);
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what()
                  << std::endl;
        abort();
    }
}

bool Screen::dropCallbackEvent(int count, const char **filenames)
{
    if (!mayProcessEvents())
        return false;

    std::vector<std::string> arg(count);
    for (int i = 0; i < count; ++i)
        arg[i] = filenames[i];
    return dropEvent(arg);
}

bool Screen::scrollCallbackEvent(double x, double y)
{
    if (!mayProcessEvents())
        return false;

    mLastInteraction = __getTime();
    try {
        if (mFocusPath.size() > 1) {
            const Window *window =
                dynamic_cast<Window *>(mFocusPath[mFocusPath.size() - 2]);
            if (window && window->modal()) {
                if (!window->contains(mMousePos))
                    return false;
            }
        }
        return scrollEvent(mMousePos, Vec2f(x, y));
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what()
                  << std::endl;
        abort();
    }

    return false;
}

bool Screen::resizeCallbackEvent(int, int)
{
    if (!mayProcessEvents())
        return false;

    Vec2i fbSize, size;
    __getFramebufferSize( _window, &fbSize.rx(), &fbSize.ry());
    __getWindowSize(_window, &size.rx(), &size.ry());

    if (mFBSize == Vec2i(0, 0) || size == Vec2i(0, 0))
        return false;

    mFBSize = fbSize;
    mSize = size;
    mLastInteraction = __getTime();

    try {
        return resizeEvent(mSize);
    } catch (const std::exception &e) {
        std::cerr << "Caught exception in event handler: " << e.what()
                  << std::endl;
        abort();
    }
}

void Screen::updateFocus(Widget *widget) {
    for (auto w: mFocusPath) {
        if (!w->focused())
            continue;
        w->focusEvent(false);
    }
    mFocusPath.clear();
    Widget *window = nullptr;
    while (widget) {
        mFocusPath.push_back(widget);
        if (dynamic_cast<Window *>(widget))
            window = widget;
        widget = widget->parent();
    }
    for (auto it = mFocusPath.rbegin(); it != mFocusPath.rend(); ++it)
        (*it)->focusEvent(true);

    if (window)
        moveWindowToFront((Window *) window);
}

void Screen::disposeWindow(Window *window) {
    auto it=mFocusPath.begin();
    for(; it != mFocusPath.end(); ++it)
    {
        if (*it == window)
                break;
    }

    if (it != mFocusPath.end())
        mFocusPath.clear();

    if (mDragWidget == window)
        mDragWidget = nullptr;
    removeChild(window);
}

void Screen::centerWindow(Window *window) {
    if (window->size() == Vec2i::Zero()) {
        window->setSize(window->preferredSize(mNVGContext));
        window->performLayout(mNVGContext);
    }
    window->setPosition((mSize - window->size()) / 2);
}

void Screen::moveWindowToFront(Window *window) {
    for (auto it=mChildren.begin(); it != mChildren.end();)
    {
        if(*it == window) it = mChildren.erase(it);
        else ++it;
    }
    mChildren.push_back(window);
    /* Brute force topological sort (no problem for a few windows..) */
    bool changed = false;
    do {
        size_t baseIndex = 0;
        for (size_t index = 0; index < mChildren.size(); ++index)
            if (mChildren[index] == window)
                baseIndex = index;
        changed = false;
        for (size_t index = 0; index < mChildren.size(); ++index) {
            Popup *pw = dynamic_cast<Popup *>(mChildren[index]);
            if (pw && pw->parentWindow() == window && index < baseIndex) {
                moveWindowToFront(pw);
                changed = true;
                break;
            }
        }
    } while (changed);
}

void Screen::performLayout(NVGcontext* ctx)
{
  Widget::performLayout(ctx);
}

void Screen::performLayout()
{
  Widget::performLayout(mNVGContext);
}

/****************************************  Stuff ****************************************/

#if !defined(_WIN32)
    #include <locale.h>
    #include <signal.h>
    #include <sys/dir.h>
#endif

std::array<char, 8> __nngui_utf8(int c) {
    std::array<char, 8> seq;
    int n = 0;
    if (c < 0x80) n = 1;
    else if (c < 0x800) n = 2;
    else if (c < 0x10000) n = 3;
    else if (c < 0x200000) n = 4;
    else if (c < 0x4000000) n = 5;
    else if (c <= 0x7fffffff) n = 6;
    seq[n] = '\0';
    switch (n) {
        case 6: seq[5] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x4000000;
        case 5: seq[4] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x200000;
        case 4: seq[3] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x10000;
        case 3: seq[2] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x800;
        case 2: seq[1] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0xc0;
        case 1: seq[0] = c;
    }
    return seq;
}

int __nanogui_get_image(NVGcontext *ctx, const std::string &name, uint8_t *data, uint32_t size) {
    static std::map<std::string, int> iconCache;
    auto it = iconCache.find(name);
    if (it != iconCache.end())
        return it->second;
    int iconID = nvgCreateImageMem(ctx, 0, data, size);
    if (iconID == 0)
        throw std::runtime_error("Unable to load resource data.");
    iconCache[name] = iconID;
    return iconID;
}

std::vector<std::pair<int, std::string>>
loadImageDirectory(NVGcontext *ctx, const std::string &path) {
    std::vector<std::pair<int, std::string> > result;
#if !defined(_WIN32)
    DIR *dp = opendir(path.c_str());
    if (!dp)
        throw std::runtime_error("Could not open image directory!");
    struct dirent *ep;
    while ((ep = readdir(dp))) {
        const char *fname = ep->d_name;
#else
    WIN32_FIND_DATA ffd;
    std::string searchPath = path + "/*.*";
    HANDLE handle = FindFirstFileA(searchPath.c_str(), &ffd);
    if (handle == INVALID_HANDLE_VALUE)
        throw std::runtime_error("Could not open image directory!");
    do {
        const char *fname = ffd.cFileName;
#endif
        if (strstr(fname, "png") == nullptr)
            continue;
        std::string fullName = path + "/" + std::string(fname);
        int img = nvgCreateImage(ctx, fullName.c_str(), 0);
        if (img == 0)
            throw std::runtime_error("Could not open image data!");
        result.push_back(
            std::make_pair(img, fullName.substr(0, fullName.length() - 4)));
#if !defined(_WIN32)
    }
    closedir(dp);
#else
    } while (FindNextFileA(handle, &ffd) != 0);
    FindClose(handle);
#endif
    return result;
}

#if !defined(__APPLE__)
std::string file_dialog(const std::vector<std::pair<std::string, std::string>> &filetypes, bool save) {
#define FILE_DIALOG_MAX_BUFFER 1024
#ifdef _WIN32
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    char tmp[FILE_DIALOG_MAX_BUFFER];
    ofn.lpstrFile = tmp;
    ZeroMemory(tmp, FILE_DIALOG_MAX_BUFFER);
    ofn.nMaxFile = FILE_DIALOG_MAX_BUFFER;
    ofn.nFilterIndex = 1;

    std::string filter;

    if (!save && filetypes.size() > 1) {
        filter.append("Supported file types (");
        for (size_t i = 0; i < filetypes.size(); ++i) {
            filter.append("*.");
            filter.append(filetypes[i].first);
            if (i + 1 < filetypes.size())
                filter.append(";");
        }
        filter.append(")");
        filter.push_back('\0');
        for (size_t i = 0; i < filetypes.size(); ++i) {
            filter.append("*.");
            filter.append(filetypes[i].first);
            if (i + 1 < filetypes.size())
                filter.append(";");
        }
        filter.push_back('\0');
    }
    for (auto pair: filetypes) {
        filter.append(pair.second);
        filter.append(" (*.");
        filter.append(pair.first);
        filter.append(")");
        filter.push_back('\0');
        filter.append("*.");
        filter.append(pair.first);
        filter.push_back('\0');
    }
    filter.push_back('\0');
    ofn.lpstrFilter = filter.data();

    if (save) {
        ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
        if (GetSaveFileNameA(&ofn) == FALSE)
            return "";
    } else {
        ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        if (GetOpenFileNameA(&ofn) == FALSE)
            return "";
    }
    return std::string(ofn.lpstrFile);
#else
    char buffer[FILE_DIALOG_MAX_BUFFER];
    std::string cmd = "/usr/bin/zenity --file-selection ";
    if (save)
        cmd += "--save ";
    cmd += "--file-filter=\"";
    for (auto pair: filetypes)
        cmd += "\"*." + pair.first +  "\" ";
    cmd += "\"";
    FILE *output = popen(cmd.c_str(), "r");
    if (output == nullptr)
        throw std::runtime_error("popen() failed -- could not launch zenity!");
    while (fgets(buffer, FILE_DIALOG_MAX_BUFFER, output) != NULL)
        ;
    pclose(output);
    std::string result(buffer);
    //result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
    return result;
#endif
}
#endif

Screen* __nngui_findScreen(Screen::ParentWindowPtr w)
{
    auto it = __nngui_screens.find(w);
    if (it == __nngui_screens.end())
        return nullptr;

    return it->second;
}

NAMESPACE_END(nanogui)

/******************************** nvg implementation ************************************/

//
// Copyright (c) 2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

/* Allow enforcing the GL2 implementation of NanoVG */
#define NANOVG_GL2_IMPLEMENTATION

#ifdef NNGUI_SDL
#include <SDL.h>
#endif


// Create flags
enum NVGcreateFlags {
        // Flag indicating if geometry based anti-aliasing is used (may not be needed when using MSAA).
        NVG_ANTIALIAS 		= 1<<0,
        // Flag indicating if strokes should be drawn using stencil buffer. The rendering will be a little
        // slower, but path overlaps (i.e. self-intersecting or sharp turns) will be drawn just once.
        NVG_STENCIL_STROKES	= 1<<1,
        // Flag indicating that additional debug checks are done.
        NVG_DEBUG               = 1<<2,
};

#if defined NANOVG_GL2_IMPLEMENTATION
#  define NANOVG_GL2 1
#  define NANOVG_GL_IMPLEMENTATION 1
#elif defined NANOVG_GL3_IMPLEMENTATION
#  define NANOVG_GL3 1
#  define NANOVG_GL_IMPLEMENTATION 1
#if !defined(NANOVG_GL_NO_UNIFORMBUFFER)
#  define NANOVG_GL_USE_UNIFORMBUFFER 1
#endif
#elif defined NANOVG_GLES2_IMPLEMENTATION
#  define NANOVG_GLES2 1
#  define NANOVG_GL_IMPLEMENTATION 1
#elif defined NANOVG_GLES3_IMPLEMENTATION
#  define NANOVG_GLES3 1
#  define NANOVG_GL_IMPLEMENTATION 1
#endif

#define NANOVG_GL_USE_STATE_FILTER (1)

// Creates NanoVG contexts for different OpenGL (ES) versions.
// Flags should be combination of the create flags above.

#if defined NANOVG_GL2

NVGcontext* nvgCreateGL2(int flags);
void nvgDeleteGL2(NVGcontext* ctx);

#endif

#if defined NANOVG_GL3

NVGcontext* nvgCreateGL3(int flags);
void nvgDeleteGL3(NVGcontext* ctx);

#endif

#if defined NANOVG_GLES2

NVGcontext* nvgCreateGLES2(int flags);
void nvgDeleteGLES2(NVGcontext* ctx);

#endif

#if defined NANOVG_GLES3

NVGcontext* nvgCreateGLES3(int flags);
void nvgDeleteGLES3(NVGcontext* ctx);

#endif

NVGcontext* nvgCreateX(bool debug)
{
    int flags = NVG_STENCIL_STROKES | NVG_ANTIALIAS;
    if (debug)
        flags |= NVG_DEBUG;
#if defined NANOVG_GL2
    return nvgCreateGL2(flags);
#elif defined NANOVG_GL3
    return nvgCreateGL3(flags);
#elif defined NANOVG_GLES2
    return nvgCreateGL2ES(flags);
#elif defined NANOVG_GLES3
    return nvgCreateGL3ES(flags);
#endif
}

void nvgDeleteX(NVGcontext* ctx)
{
#if defined NANOVG_GL2
    return nvgDeleteGL2(ctx);
#elif defined NANOVG_GL3
    return nvgDeleteGL3(ctx);
#elif defined NANOVG_GLES2
    return nvgDeleteGL2ES(ctx);
#elif defined NANOVG_GLES3
    return nvgDeleteGL3ES(ctx);
#endif
}

// These are additional flags on top of NVGimageFlags.
enum NVGimageFlagsGL {
        NVG_IMAGE_NODELETE			= 1<<16,	// Do not delete GL texture handle.
};

int nvglCreateImageFromHandle(NVGcontext* ctx, GLuint textureId, int w, int h, int flags);
GLuint nvglImageHandle(NVGcontext* ctx, int image);

#ifdef NANOVG_GL_IMPLEMENTATION
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

enum GLNVGuniformLoc {
        GLNVG_LOC_VIEWSIZE,
        GLNVG_LOC_TEX,
        GLNVG_LOC_FRAG,
        GLNVG_MAX_LOCS
};

enum GLNVGshaderType {
        NSVG_SHADER_FILLGRAD,
        NSVG_SHADER_FILLIMG,
        NSVG_SHADER_SIMPLE,
        NSVG_SHADER_IMG
};

#if NANOVG_GL_USE_UNIFORMBUFFER
enum GLNVGuniformBindings {
        GLNVG_FRAG_BINDING = 0,
};
#endif

struct GLNVGshader {
        GLuint prog;
        GLuint frag;
        GLuint vert;
        GLint loc[GLNVG_MAX_LOCS];
};
typedef struct GLNVGshader GLNVGshader;

struct GLNVGtexture {
        int id;
        GLuint tex;
        int width, height;
        int type;
        int flags;
};
typedef struct GLNVGtexture GLNVGtexture;

enum GLNVGcallType {
        GLNVG_NONE = 0,
        GLNVG_FILL,
        GLNVG_CONVEXFILL,
        GLNVG_STROKE,
        GLNVG_TRIANGLES,
};

struct GLNVGcall {
        int type;
        int image;
        int pathOffset;
        int pathCount;
        int triangleOffset;
        int triangleCount;
        int uniformOffset;
};
typedef struct GLNVGcall GLNVGcall;

struct GLNVGpath {
        int fillOffset;
        int fillCount;
        int strokeOffset;
        int strokeCount;
};
typedef struct GLNVGpath GLNVGpath;

struct GLNVGfragUniforms {
        #if NANOVG_GL_USE_UNIFORMBUFFER
                float scissorMat[12]; // matrices are actually 3 vec4s
                float paintMat[12];
                struct NVGcolor innerCol;
                struct NVGcolor outerCol;
                float scissorExt[2];
                float scissorScale[2];
                float extent[2];
                float radius;
                float feather;
                float strokeMult;
                float strokeThr;
                int texType;
                int type;
        #else
                // note: after modifying layout or size of uniform array,
                // don't forget to also update the fragment shader source!
                #define NANOVG_GL_UNIFORMARRAY_SIZE 11
                union {
                        struct {
                                float scissorMat[12]; // matrices are actually 3 vec4s
                                float paintMat[12];
                                struct NVGcolor innerCol;
                                struct NVGcolor outerCol;
                                float scissorExt[2];
                                float scissorScale[2];
                                float extent[2];
                                float radius;
                                float feather;
                                float strokeMult;
                                float strokeThr;
                                float texType;
                                float type;
                        };
                        float uniformArray[NANOVG_GL_UNIFORMARRAY_SIZE][4];
                };
        #endif
};
typedef struct GLNVGfragUniforms GLNVGfragUniforms;

struct GLNVGcontext {
        GLNVGshader shader;
        GLNVGtexture* textures;
        float view[2];
        int ntextures;
        int ctextures;
        int textureId;
        GLuint vertBuf;
#if defined NANOVG_GL3
        GLuint vertArr;
#endif
#if NANOVG_GL_USE_UNIFORMBUFFER
        GLuint fragBuf;
#endif
        int fragSize;
        int flags;

        // Per frame buffers
        GLNVGcall* calls;
        int ccalls;
        int ncalls;
        GLNVGpath* paths;
        int cpaths;
        int npaths;
        struct NVGvertex* verts;
        int cverts;
        int nverts;
        unsigned char* uniforms;
        int cuniforms;
        int nuniforms;

        // cached state
        #if NANOVG_GL_USE_STATE_FILTER
        GLuint boundTexture;
        GLuint stencilMask;
        GLenum stencilFunc;
        GLint stencilFuncRef;
        GLuint stencilFuncMask;
        #endif
};
typedef struct GLNVGcontext GLNVGcontext;

static int glnvg__maxi(int a, int b) { return a > b ? a : b; }

#ifdef NANOVG_GLES2
static unsigned int glnvg__nearestPow2(unsigned int num)
{
        unsigned n = num > 0 ? num - 1 : 0;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        n++;
        return n;
}
#endif

static void glnvg__bindTexture(GLNVGcontext* gl, GLuint tex)
{
#if NANOVG_GL_USE_STATE_FILTER
        if (gl->boundTexture != tex) {
                gl->boundTexture = tex;
                glBindTexture(GL_TEXTURE_2D, tex);
        }
#else
        glBindTexture(GL_TEXTURE_2D, tex);
#endif
}

static void glnvg__stencilMask(GLNVGcontext* gl, GLuint mask)
{
#if NANOVG_GL_USE_STATE_FILTER
        if (gl->stencilMask != mask) {
                gl->stencilMask = mask;
                glStencilMask(mask);
        }
#else
        glStencilMask(mask);
#endif
}

static void glnvg__stencilFunc(GLNVGcontext* gl, GLenum func, GLint ref, GLuint mask)
{
#if NANOVG_GL_USE_STATE_FILTER
        if ((gl->stencilFunc != func) ||
                (gl->stencilFuncRef != ref) ||
                (gl->stencilFuncMask != mask)) {

                gl->stencilFunc = func;
                gl->stencilFuncRef = ref;
                gl->stencilFuncMask = mask;
                glStencilFunc(func, ref, mask);
        }
#else
        glStencilFunc(func, ref, mask);
#endif
}

static GLNVGtexture* glnvg__allocTexture(GLNVGcontext* gl)
{
        GLNVGtexture* tex = NULL;
        int i;

        for (i = 0; i < gl->ntextures; i++) {
                if (gl->textures[i].id == 0) {
                        tex = &gl->textures[i];
                        break;
                }
        }
        if (tex == NULL) {
                if (gl->ntextures+1 > gl->ctextures) {
                        GLNVGtexture* textures;
                        int ctextures = glnvg__maxi(gl->ntextures+1, 4) +  gl->ctextures/2; // 1.5x Overallocate
                        textures = (GLNVGtexture*)realloc(gl->textures, sizeof(GLNVGtexture)*ctextures);
                        if (textures == NULL) return NULL;
                        gl->textures = textures;
                        gl->ctextures = ctextures;
                }
                tex = &gl->textures[gl->ntextures++];
        }

        memset(tex, 0, sizeof(*tex));
        tex->id = ++gl->textureId;

        return tex;
}

static GLNVGtexture* glnvg__findTexture(GLNVGcontext* gl, int id)
{
        int i;
        for (i = 0; i < gl->ntextures; i++)
                if (gl->textures[i].id == id)
                        return &gl->textures[i];
        return NULL;
}

static int glnvg__deleteTexture(GLNVGcontext* gl, int id)
{
        int i;
        for (i = 0; i < gl->ntextures; i++) {
                if (gl->textures[i].id == id) {
                        if (gl->textures[i].tex != 0 && (gl->textures[i].flags & NVG_IMAGE_NODELETE) == 0)
                                glDeleteTextures(1, &gl->textures[i].tex);
                        memset(&gl->textures[i], 0, sizeof(gl->textures[i]));
                        return 1;
                }
        }
        return 0;
}

static void glnvg__dumpShaderError(GLuint shader, const char* name, const char* type)
{
        GLchar str[512+1];
        GLsizei len = 0;
        glGetShaderInfoLog(shader, 512, &len, str);
        if (len > 512) len = 512;
        str[len] = '\0';
        printf("Shader %s/%s error:\n%s\n", name, type, str);
}

static void glnvg__dumpProgramError(GLuint prog, const char* name)
{
        GLchar str[512+1];
        GLsizei len = 0;
        glGetProgramInfoLog(prog, 512, &len, str);
        if (len > 512) len = 512;
        str[len] = '\0';
        printf("Program %s error:\n%s\n", name, str);
}

static void glnvg__checkError(GLNVGcontext* gl, const char* str)
{
        GLenum err;
        if ((gl->flags & NVG_DEBUG) == 0) return;
        err = glGetError();
        if (err != GL_NO_ERROR) {
                printf("Error %08x after %s\n", err, str);
                return;
        }
}

static int glnvg__createShader(GLNVGshader* shader, const char* name, const char* header, const char* opts, const char* vshader, const char* fshader)
{
  GLint status;
  GLuint prog, vert, frag;
  const char* str[3];
  str[0] = header;
  str[1] = opts != NULL ? opts : "";

  memset(shader, 0, sizeof(*shader));

  prog = glCreateProgram();
  vert = glCreateShader(GL_VERTEX_SHADER);
  frag = glCreateShader(GL_FRAGMENT_SHADER);
  str[2] = vshader;
  glShaderSource(vert, 3, str, 0);
  str[2] = fshader;
  glShaderSource(frag, 3, str, 0);

  glCompileShader(vert);
  glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
          glnvg__dumpShaderError(vert, name, "vert");
          return 0;
  }

  glCompileShader(frag);
  glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
          glnvg__dumpShaderError(frag, name, "frag");
          return 0;
  }

  glAttachShader(prog, vert);
  glAttachShader(prog, frag);

  glBindAttribLocation(prog, 0, "vertex");
  glBindAttribLocation(prog, 1, "tcoord");

  glLinkProgram(prog);
  glGetProgramiv(prog, GL_LINK_STATUS, &status);
  if (status != GL_TRUE) {
          glnvg__dumpProgramError(prog, name);
          return 0;
  }

  shader->prog = prog;
  shader->vert = vert;
  shader->frag = frag;

  return 1;
}

static void glnvg__deleteShader(GLNVGshader* shader)
{
  if (shader->prog != 0)
          glDeleteProgram(shader->prog);
  if (shader->vert != 0)
          glDeleteShader(shader->vert);
  if (shader->frag != 0)
          glDeleteShader(shader->frag);
}

static void glnvg__getUniforms(GLNVGshader* shader)
{
        shader->loc[GLNVG_LOC_VIEWSIZE] = glGetUniformLocation(shader->prog, "viewSize");
        shader->loc[GLNVG_LOC_TEX] = glGetUniformLocation(shader->prog, "tex");

#if NANOVG_GL_USE_UNIFORMBUFFER
        shader->loc[GLNVG_LOC_FRAG] = glGetUniformBlockIndex(shader->prog, "frag");
#else
        shader->loc[GLNVG_LOC_FRAG] = glGetUniformLocation(shader->prog, "frag");
#endif
}

static int glnvg__renderCreate(void* uptr)
{
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        int align = 4;

        // TODO: mediump float may not be enough for GLES2 in iOS.
        // see the following discussion: https://github.com/memononen/nanovg/issues/46
        static const char* shaderHeader =
#if defined NANOVG_GL2
                "#define NANOVG_GL2 1\n"
#elif defined NANOVG_GL3
                "#version 150 core\n"
                "#define NANOVG_GL3 1\n"
#elif defined NANOVG_GLES2
                "#version 100\n"
                "#define NANOVG_GL2 1\n"
#elif defined NANOVG_GLES3
                "#version 300 es\n"
                "#define NANOVG_GL3 1\n"
#endif

#if NANOVG_GL_USE_UNIFORMBUFFER
        "#define USE_UNIFORMBUFFER 1\n"
#else
        "#define UNIFORMARRAY_SIZE 11\n"
#endif
        "\n";

        static const char* fillVertShader =
                "#ifdef NANOVG_GL3\n"
                "	uniform vec2 viewSize;\n"
                "	in vec2 vertex;\n"
                "	in vec2 tcoord;\n"
                "	out vec2 ftcoord;\n"
                "	out vec2 fpos;\n"
                "#else\n"
                "	uniform vec2 viewSize;\n"
                "	attribute vec2 vertex;\n"
                "	attribute vec2 tcoord;\n"
                "	varying vec2 ftcoord;\n"
                "	varying vec2 fpos;\n"
                "#endif\n"
                "void main(void) {\n"
                "	ftcoord = tcoord;\n"
                "	fpos = vertex;\n"
                "	gl_Position = vec4(2.0*vertex.x/viewSize.x - 1.0, 1.0 - 2.0*vertex.y/viewSize.y, 0, 1);\n"
                "}\n";

        static const char* fillFragShader =
                "#ifdef GL_ES\n"
                "#if defined(GL_FRAGMENT_PRECISION_HIGH) || defined(NANOVG_GL3)\n"
                " precision highp float;\n"
                "#else\n"
                " precision mediump float;\n"
                "#endif\n"
                "#endif\n"
                "#ifdef NANOVG_GL3\n"
                "#ifdef USE_UNIFORMBUFFER\n"
                "	layout(std140) uniform frag {\n"
                "		mat3 scissorMat;\n"
                "		mat3 paintMat;\n"
                "		vec4 innerCol;\n"
                "		vec4 outerCol;\n"
                "		vec2 scissorExt;\n"
                "		vec2 scissorScale;\n"
                "		vec2 extent;\n"
                "		float radius;\n"
                "		float feather;\n"
                "		float strokeMult;\n"
                "		float strokeThr;\n"
                "		int texType;\n"
                "		int type;\n"
                "	};\n"
                "#else\n" // NANOVG_GL3 && !USE_UNIFORMBUFFER
                "	uniform vec4 frag[UNIFORMARRAY_SIZE];\n"
                "#endif\n"
                "	uniform sampler2D tex;\n"
                "	in vec2 ftcoord;\n"
                "	in vec2 fpos;\n"
                "	out vec4 outColor;\n"
                "#else\n" // !NANOVG_GL3
                "	uniform vec4 frag[UNIFORMARRAY_SIZE];\n"
                "	uniform sampler2D tex;\n"
                "	varying vec2 ftcoord;\n"
                "	varying vec2 fpos;\n"
                "#endif\n"
                "#ifndef USE_UNIFORMBUFFER\n"
                "	#define scissorMat mat3(frag[0].xyz, frag[1].xyz, frag[2].xyz)\n"
                "	#define paintMat mat3(frag[3].xyz, frag[4].xyz, frag[5].xyz)\n"
                "	#define innerCol frag[6]\n"
                "	#define outerCol frag[7]\n"
                "	#define scissorExt frag[8].xy\n"
                "	#define scissorScale frag[8].zw\n"
                "	#define extent frag[9].xy\n"
                "	#define radius frag[9].z\n"
                "	#define feather frag[9].w\n"
                "	#define strokeMult frag[10].x\n"
                "	#define strokeThr frag[10].y\n"
                "	#define texType int(frag[10].z)\n"
                "	#define type int(frag[10].w)\n"
                "#endif\n"
                "\n"
                "float sdroundrect(vec2 pt, vec2 ext, float rad) {\n"
                "	vec2 ext2 = ext - vec2(rad,rad);\n"
                "	vec2 d = abs(pt) - ext2;\n"
                "	return min(max(d.x,d.y),0.0) + length(max(d,0.0)) - rad;\n"
                "}\n"
                "\n"
                "// Scissoring\n"
                "float scissorMask(vec2 p) {\n"
                "	vec2 sc = (abs((scissorMat * vec3(p,1.0)).xy) - scissorExt);\n"
                "	sc = vec2(0.5,0.5) - sc * scissorScale;\n"
                "	return clamp(sc.x,0.0,1.0) * clamp(sc.y,0.0,1.0);\n"
                "}\n"
                "#ifdef EDGE_AA\n"
                "// Stroke - from [0..1] to clipped pyramid, where the slope is 1px.\n"
                "float strokeMask() {\n"
                "	return min(1.0, (1.0-abs(ftcoord.x*2.0-1.0))*strokeMult) * min(1.0, ftcoord.y);\n"
                "}\n"
                "#endif\n"
                "\n"
                "void main(void) {\n"
                "   vec4 result;\n"
                "	float scissor = scissorMask(fpos);\n"
                "#ifdef EDGE_AA\n"
                "	float strokeAlpha = strokeMask();\n"
                "#else\n"
                "	float strokeAlpha = 1.0;\n"
                "#endif\n"
                "	if (type == 0) {			// Gradient\n"
                "		// Calculate gradient color using box gradient\n"
                "		vec2 pt = (paintMat * vec3(fpos,1.0)).xy;\n"
                "		float d = clamp((sdroundrect(pt, extent, radius) + feather*0.5) / feather, 0.0, 1.0);\n"
                "		vec4 color = mix(innerCol,outerCol,d);\n"
                "		// Combine alpha\n"
                "		color *= strokeAlpha * scissor;\n"
                "		result = color;\n"
                "	} else if (type == 1) {		// Image\n"
                "		// Calculate color fron texture\n"
                "		vec2 pt = (paintMat * vec3(fpos,1.0)).xy / extent;\n"
                "#ifdef NANOVG_GL3\n"
                "		vec4 color = texture(tex, pt);\n"
                "#else\n"
                "		vec4 color = texture2D(tex, pt);\n"
                "#endif\n"
                "		if (texType == 1) color = vec4(color.xyz*color.w,color.w);"
                "		if (texType == 2) color = vec4(color.x);"
                "		// Apply color tint and alpha.\n"
                "		color *= innerCol;\n"
                "		// Combine alpha\n"
                "		color *= strokeAlpha * scissor;\n"
                "		result = color;\n"
                "	} else if (type == 2) {		// Stencil fill\n"
                "		result = vec4(1,1,1,1);\n"
                "	} else if (type == 3) {		// Textured tris\n"
                "#ifdef NANOVG_GL3\n"
                "		vec4 color = texture(tex, ftcoord);\n"
                "#else\n"
                "		vec4 color = texture2D(tex, ftcoord);\n"
                "#endif\n"
                "		if (texType == 1) color = vec4(color.xyz*color.w,color.w);"
                "		if (texType == 2) color = vec4(color.x);"
                "		color *= scissor;\n"
                "		result = color * innerCol;\n"
                "	}\n"
                "#ifdef EDGE_AA\n"
                "	if (strokeAlpha < strokeThr) discard;\n"
                "#endif\n"
                "#ifdef NANOVG_GL3\n"
                "	outColor = result;\n"
                "#else\n"
                "	gl_FragColor = result;\n"
                "#endif\n"
                "}\n";

        glnvg__checkError(gl, "init");

        if (gl->flags & NVG_ANTIALIAS) {
                if (glnvg__createShader(&gl->shader, "shader", shaderHeader, "#define EDGE_AA 1\n", fillVertShader, fillFragShader) == 0)
                        return 0;
        } else {
                if (glnvg__createShader(&gl->shader, "shader", shaderHeader, NULL, fillVertShader, fillFragShader) == 0)
                        return 0;
        }

        glnvg__checkError(gl, "uniform locations");
        glnvg__getUniforms(&gl->shader);

        // Create dynamic vertex array
#if defined NANOVG_GL3
        glGenVertexArrays(1, &gl->vertArr);
#endif
        glGenBuffers(1, &gl->vertBuf);

#if NANOVG_GL_USE_UNIFORMBUFFER
        // Create UBOs
        glUniformBlockBinding(gl->shader.prog, gl->shader.loc[GLNVG_LOC_FRAG], GLNVG_FRAG_BINDING);
        glGenBuffers(1, &gl->fragBuf);
        glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &align);
#endif
        gl->fragSize = sizeof(GLNVGfragUniforms) + align - sizeof(GLNVGfragUniforms) % align;

        glnvg__checkError(gl, "create done");

        glFinish();

        return 1;
}

static int glnvg__renderCreateTexture(void* uptr, int type, int w, int h, int imageFlags, const unsigned char* data)
{
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        GLNVGtexture* tex = glnvg__allocTexture(gl);

        if (tex == NULL) return 0;

#ifdef NANOVG_GLES2
        // Check for non-power of 2.
        if (glnvg__nearestPow2(w) != (unsigned int)w || glnvg__nearestPow2(h) != (unsigned int)h) {
                // No repeat
                if ((imageFlags & NVG_IMAGE_REPEATX) != 0 || (imageFlags & NVG_IMAGE_REPEATY) != 0) {
                        printf("Repeat X/Y is not supported for non power-of-two textures (%d x %d)\n", w, h);
                        imageFlags &= ~(NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
                }
                // No mips.
                if (imageFlags & NVG_IMAGE_GENERATE_MIPMAPS) {
                        printf("Mip-maps is not support for non power-of-two textures (%d x %d)\n", w, h);
                        imageFlags &= ~NVG_IMAGE_GENERATE_MIPMAPS;
                }
        }
#endif

        glGenTextures(1, &tex->tex);
        tex->width = w;
        tex->height = h;
        tex->type = type;
        tex->flags = imageFlags;
        glnvg__bindTexture(gl, tex->tex);

        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
#ifndef NANOVG_GLES2
        glPixelStorei(GL_UNPACK_ROW_LENGTH, tex->width);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
#endif

#if defined (NANOVG_GL2)
        // GL 1.4 and later has support for generating mipmaps using a tex parameter.
        if (imageFlags & NVG_IMAGE_GENERATE_MIPMAPS) {
                glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        }
#endif

        if (type == NVG_TEXTURE_RGBA)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else
#if defined(NANOVG_GLES2)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, w, h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
#elif defined(NANOVG_GLES3)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);
#else
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);
#endif

        if (imageFlags & NVG_IMAGE_GENERATE_MIPMAPS) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        } else {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (imageFlags & NVG_IMAGE_REPEATX)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        else
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

        if (imageFlags & NVG_IMAGE_REPEATY)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        else
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
#ifndef NANOVG_GLES2
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
#endif

        // The new way to build mipmaps on GLES and GL3
#if !defined(NANOVG_GL2)
        if (imageFlags & NVG_IMAGE_GENERATE_MIPMAPS) {
                glGenerateMipmap(GL_TEXTURE_2D);
        }
#endif

        glnvg__checkError(gl, "create tex");
        glnvg__bindTexture(gl, 0);

        return tex->id;
}


static int glnvg__renderDeleteTexture(void* uptr, int image)
{
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        return glnvg__deleteTexture(gl, image);
}

static int glnvg__renderUpdateTexture(void* uptr, int image, int x, int y, int w, int h, const unsigned char* data)
{
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        GLNVGtexture* tex = glnvg__findTexture(gl, image);

        if (tex == NULL) return 0;
        glnvg__bindTexture(gl, tex->tex);

        glPixelStorei(GL_UNPACK_ALIGNMENT,1);

#ifndef NANOVG_GLES2
        glPixelStorei(GL_UNPACK_ROW_LENGTH, tex->width);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, x);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, y);
#else
        // No support for all of skip, need to update a whole row at a time.
        if (tex->type == NVG_TEXTURE_RGBA)
                data += y*tex->width*4;
        else
                data += y*tex->width;
        x = 0;
        w = tex->width;
#endif

        if (tex->type == NVG_TEXTURE_RGBA)
                glTexSubImage2D(GL_TEXTURE_2D, 0, x,y, w,h, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else
#ifdef NANOVG_GLES2
                glTexSubImage2D(GL_TEXTURE_2D, 0, x,y, w,h, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
#else
                glTexSubImage2D(GL_TEXTURE_2D, 0, x,y, w,h, GL_RED, GL_UNSIGNED_BYTE, data);
#endif

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
#ifndef NANOVG_GLES2
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
#endif

        glnvg__bindTexture(gl, 0);

        return 1;
}

static int glnvg__renderGetTextureSize(void* uptr, int image, int* w, int* h)
{
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        GLNVGtexture* tex = glnvg__findTexture(gl, image);
        if (tex == NULL) return 0;
        *w = tex->width;
        *h = tex->height;
        return 1;
}

static void glnvg__xformToMat3x4(float* m3, float* t)
{
        m3[0] = t[0];
        m3[1] = t[1];
        m3[2] = 0.0f;
        m3[3] = 0.0f;
        m3[4] = t[2];
        m3[5] = t[3];
        m3[6] = 0.0f;
        m3[7] = 0.0f;
        m3[8] = t[4];
        m3[9] = t[5];
        m3[10] = 1.0f;
        m3[11] = 0.0f;
}

static NVGcolor glnvg__premulColor(NVGcolor c)
{
        c.r *= c.a;
        c.g *= c.a;
        c.b *= c.a;
        return c;
}

static int glnvg__convertPaint(GLNVGcontext* gl, GLNVGfragUniforms* frag, NVGpaint* paint,
                                                           NVGscissor* scissor, float width, float fringe, float strokeThr)
{
        GLNVGtexture* tex = NULL;
        float invxform[6];

        memset(frag, 0, sizeof(*frag));

        frag->innerCol = glnvg__premulColor(paint->innerColor);
        frag->outerCol = glnvg__premulColor(paint->outerColor);

        if (scissor->extent[0] < -0.5f || scissor->extent[1] < -0.5f) {
                memset(frag->scissorMat, 0, sizeof(frag->scissorMat));
                frag->scissorExt[0] = 1.0f;
                frag->scissorExt[1] = 1.0f;
                frag->scissorScale[0] = 1.0f;
                frag->scissorScale[1] = 1.0f;
        } else {
                nvgTransformInverse(invxform, scissor->xform);
                glnvg__xformToMat3x4(frag->scissorMat, invxform);
                frag->scissorExt[0] = scissor->extent[0];
                frag->scissorExt[1] = scissor->extent[1];
                frag->scissorScale[0] = sqrtf(scissor->xform[0]*scissor->xform[0] + scissor->xform[2]*scissor->xform[2]) / fringe;
                frag->scissorScale[1] = sqrtf(scissor->xform[1]*scissor->xform[1] + scissor->xform[3]*scissor->xform[3]) / fringe;
        }

        memcpy(frag->extent, paint->extent, sizeof(frag->extent));
        frag->strokeMult = (width*0.5f + fringe*0.5f) / fringe;
        frag->strokeThr = strokeThr;

        if (paint->image != 0) {
                tex = glnvg__findTexture(gl, paint->image);
                if (tex == NULL) return 0;
                if ((tex->flags & NVG_IMAGE_FLIPY) != 0) {
                        float flipped[6];
                        nvgTransformScale(flipped, 1.0f, -1.0f);
                        nvgTransformMultiply(flipped, paint->xform);
                        nvgTransformInverse(invxform, flipped);
                } else {
                        nvgTransformInverse(invxform, paint->xform);
                }
                frag->type = NSVG_SHADER_FILLIMG;

                if (tex->type == NVG_TEXTURE_RGBA)
                        frag->texType = (tex->flags & NVG_IMAGE_PREMULTIPLIED) ? 0 : 1;
                else
                        frag->texType = 2;
//		printf("frag->texType = %d\n", frag->texType);
        } else {
                frag->type = NSVG_SHADER_FILLGRAD;
                frag->radius = paint->radius;
                frag->feather = paint->feather;
                nvgTransformInverse(invxform, paint->xform);
        }

        glnvg__xformToMat3x4(frag->paintMat, invxform);

        return 1;
}

static GLNVGfragUniforms* nvg__fragUniformPtr(GLNVGcontext* gl, int i);

static void glnvg__setUniforms(GLNVGcontext* gl, int uniformOffset, int image)
{
#if NANOVG_GL_USE_UNIFORMBUFFER
        glBindBufferRange(GL_UNIFORM_BUFFER, GLNVG_FRAG_BINDING, gl->fragBuf, uniformOffset, sizeof(GLNVGfragUniforms));
#else
        GLNVGfragUniforms* frag = nvg__fragUniformPtr(gl, uniformOffset);
        glUniform4fv(gl->shader.loc[GLNVG_LOC_FRAG], NANOVG_GL_UNIFORMARRAY_SIZE, &(frag->uniformArray[0][0]));
#endif

        if (image != 0) {
                GLNVGtexture* tex = glnvg__findTexture(gl, image);
                glnvg__bindTexture(gl, tex != NULL ? tex->tex : 0);
                glnvg__checkError(gl, "tex paint tex");
        } else {
                glnvg__bindTexture(gl, 0);
        }
}

static void glnvg__renderViewport(void* uptr, int width, int height)
{
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        gl->view[0] = (float)width;
        gl->view[1] = (float)height;
}

static void glnvg__fill(GLNVGcontext* gl, GLNVGcall* call)
{
        GLNVGpath* paths = &gl->paths[call->pathOffset];
        int i, npaths = call->pathCount;

        // Draw shapes
        glEnable(GL_STENCIL_TEST);
        glnvg__stencilMask(gl, 0xff);
        glnvg__stencilFunc(gl, GL_ALWAYS, 0, 0xff);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

        // set bindpoint for solid loc
        glnvg__setUniforms(gl, call->uniformOffset, 0);
        glnvg__checkError(gl, "fill simple");

        glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_INCR_WRAP);
        glStencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_DECR_WRAP);
        glDisable(GL_CULL_FACE);
        for (i = 0; i < npaths; i++)
                glDrawArrays(GL_TRIANGLE_FAN, paths[i].fillOffset, paths[i].fillCount);
        glEnable(GL_CULL_FACE);

        // Draw anti-aliased pixels
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

        glnvg__setUniforms(gl, call->uniformOffset + gl->fragSize, call->image);
        glnvg__checkError(gl, "fill fill");

        if (gl->flags & NVG_ANTIALIAS) {
                glnvg__stencilFunc(gl, GL_EQUAL, 0x00, 0xff);
                glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
                // Draw fringes
                for (i = 0; i < npaths; i++)
                        glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);
        }

        // Draw fill
        glnvg__stencilFunc(gl, GL_NOTEQUAL, 0x0, 0xff);
        glStencilOp(GL_ZERO, GL_ZERO, GL_ZERO);
        glDrawArrays(GL_TRIANGLES, call->triangleOffset, call->triangleCount);

        glDisable(GL_STENCIL_TEST);
}

static void glnvg__convexFill(GLNVGcontext* gl, GLNVGcall* call)
{
        GLNVGpath* paths = &gl->paths[call->pathOffset];
        int i, npaths = call->pathCount;

        glnvg__setUniforms(gl, call->uniformOffset, call->image);
        glnvg__checkError(gl, "convex fill");

        for (i = 0; i < npaths; i++)
                glDrawArrays(GL_TRIANGLE_FAN, paths[i].fillOffset, paths[i].fillCount);
        if (gl->flags & NVG_ANTIALIAS) {
                // Draw fringes
                for (i = 0; i < npaths; i++)
                        glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);
        }
}

static void glnvg__stroke(GLNVGcontext* gl, GLNVGcall* call)
{
        GLNVGpath* paths = &gl->paths[call->pathOffset];
        int npaths = call->pathCount, i;

        if (gl->flags & NVG_STENCIL_STROKES) {

                glEnable(GL_STENCIL_TEST);
                glnvg__stencilMask(gl, 0xff);

                // Fill the stroke base without overlap
                glnvg__stencilFunc(gl, GL_EQUAL, 0x0, 0xff);
                glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
                glnvg__setUniforms(gl, call->uniformOffset + gl->fragSize, call->image);
                glnvg__checkError(gl, "stroke fill 0");
                for (i = 0; i < npaths; i++)
                        glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);

                // Draw anti-aliased pixels.
                glnvg__setUniforms(gl, call->uniformOffset, call->image);
                glnvg__stencilFunc(gl, GL_EQUAL, 0x00, 0xff);
                glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
                for (i = 0; i < npaths; i++)
                        glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);

                // Clear stencil buffer.
                glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
                glnvg__stencilFunc(gl, GL_ALWAYS, 0x0, 0xff);
                glStencilOp(GL_ZERO, GL_ZERO, GL_ZERO);
                glnvg__checkError(gl, "stroke fill 1");
                for (i = 0; i < npaths; i++)
                        glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);
                glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

                glDisable(GL_STENCIL_TEST);

//		glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset + gl->fragSize), paint, scissor, strokeWidth, fringe, 1.0f - 0.5f/255.0f);

        } else {
                glnvg__setUniforms(gl, call->uniformOffset, call->image);
                glnvg__checkError(gl, "stroke fill");
                // Draw Strokes
                for (i = 0; i < npaths; i++)
                        glDrawArrays(GL_TRIANGLE_STRIP, paths[i].strokeOffset, paths[i].strokeCount);
        }
}

static void glnvg__triangles(GLNVGcontext* gl, GLNVGcall* call)
{
        glnvg__setUniforms(gl, call->uniformOffset, call->image);
        glnvg__checkError(gl, "triangles fill");

        glDrawArrays(GL_TRIANGLES, call->triangleOffset, call->triangleCount);
}

static void glnvg__renderCancel(void* uptr) {
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        gl->nverts = 0;
        gl->npaths = 0;
        gl->ncalls = 0;
        gl->nuniforms = 0;
}

static void glnvg__renderFlush(void* uptr)
{
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        int i;

        if (gl->ncalls > 0) {

                // Setup require GL state.
                glUseProgram(gl->shader.prog);

                glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                glFrontFace(GL_CCW);
                glEnable(GL_BLEND);
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_SCISSOR_TEST);
                glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
                glStencilMask(0xffffffff);
                glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
                glStencilFunc(GL_ALWAYS, 0, 0xffffffff);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, 0);
                #if NANOVG_GL_USE_STATE_FILTER
                gl->boundTexture = 0;
                gl->stencilMask = 0xffffffff;
                gl->stencilFunc = GL_ALWAYS;
                gl->stencilFuncRef = 0;
                gl->stencilFuncMask = 0xffffffff;
                #endif

#if NANOVG_GL_USE_UNIFORMBUFFER
                // Upload ubo for frag shaders
                glBindBuffer(GL_UNIFORM_BUFFER, gl->fragBuf);
                glBufferData(GL_UNIFORM_BUFFER, gl->nuniforms * gl->fragSize, gl->uniforms, GL_STREAM_DRAW);
#endif

                // Upload vertex data
#if defined NANOVG_GL3
                glBindVertexArray(gl->vertArr);
#endif
                glBindBuffer(GL_ARRAY_BUFFER, gl->vertBuf);
                glBufferData(GL_ARRAY_BUFFER, gl->nverts * sizeof(NVGvertex), gl->verts, GL_STREAM_DRAW);
                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(NVGvertex), (const GLvoid*)(size_t)0);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(NVGvertex), (const GLvoid*)(0 + 2*sizeof(float)));

                // Set view and texture just once per frame.
                glUniform1i(gl->shader.loc[GLNVG_LOC_TEX], 0);
                glUniform2fv(gl->shader.loc[GLNVG_LOC_VIEWSIZE], 1, gl->view);

#if NANOVG_GL_USE_UNIFORMBUFFER
                glBindBuffer(GL_UNIFORM_BUFFER, gl->fragBuf);
#endif

                for (i = 0; i < gl->ncalls; i++) {
                        GLNVGcall* call = &gl->calls[i];
                        if (call->type == GLNVG_FILL)
                                glnvg__fill(gl, call);
                        else if (call->type == GLNVG_CONVEXFILL)
                                glnvg__convexFill(gl, call);
                        else if (call->type == GLNVG_STROKE)
                                glnvg__stroke(gl, call);
                        else if (call->type == GLNVG_TRIANGLES)
                                glnvg__triangles(gl, call);
                }

                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);
#if defined NANOVG_GL3
                glBindVertexArray(0);
#endif
                glDisable(GL_CULL_FACE);
                        glBindBuffer(GL_ARRAY_BUFFER, 0);
                glUseProgram(0);
                glnvg__bindTexture(gl, 0);
        }

        // Reset calls
        gl->nverts = 0;
        gl->npaths = 0;
        gl->ncalls = 0;
        gl->nuniforms = 0;
}

static int glnvg__maxVertCount(const NVGpath* paths, int npaths)
{
        int i, count = 0;
        for (i = 0; i < npaths; i++) {
                count += paths[i].nfill;
                count += paths[i].nstroke;
        }
        return count;
}

static GLNVGcall* glnvg__allocCall(GLNVGcontext* gl)
{
        GLNVGcall* ret = NULL;
        if (gl->ncalls+1 > gl->ccalls) {
                GLNVGcall* calls;
                int ccalls = glnvg__maxi(gl->ncalls+1, 128) + gl->ccalls/2; // 1.5x Overallocate
                calls = (GLNVGcall*)realloc(gl->calls, sizeof(GLNVGcall) * ccalls);
                if (calls == NULL) return NULL;
                gl->calls = calls;
                gl->ccalls = ccalls;
        }
        ret = &gl->calls[gl->ncalls++];
        memset(ret, 0, sizeof(GLNVGcall));
        return ret;
}

static int glnvg__allocPaths(GLNVGcontext* gl, int n)
{
        int ret = 0;
        if (gl->npaths+n > gl->cpaths) {
                GLNVGpath* paths;
                int cpaths = glnvg__maxi(gl->npaths + n, 128) + gl->cpaths/2; // 1.5x Overallocate
                paths = (GLNVGpath*)realloc(gl->paths, sizeof(GLNVGpath) * cpaths);
                if (paths == NULL) return -1;
                gl->paths = paths;
                gl->cpaths = cpaths;
        }
        ret = gl->npaths;
        gl->npaths += n;
        return ret;
}

static int glnvg__allocVerts(GLNVGcontext* gl, int n)
{
        int ret = 0;
        if (gl->nverts+n > gl->cverts) {
                NVGvertex* verts;
                int cverts = glnvg__maxi(gl->nverts + n, 4096) + gl->cverts/2; // 1.5x Overallocate
                verts = (NVGvertex*)realloc(gl->verts, sizeof(NVGvertex) * cverts);
                if (verts == NULL) return -1;
                gl->verts = verts;
                gl->cverts = cverts;
        }
        ret = gl->nverts;
        gl->nverts += n;
        return ret;
}

static int glnvg__allocFragUniforms(GLNVGcontext* gl, int n)
{
        int ret = 0, structSize = gl->fragSize;
        if (gl->nuniforms+n > gl->cuniforms) {
                unsigned char* uniforms;
                int cuniforms = glnvg__maxi(gl->nuniforms+n, 128) + gl->cuniforms/2; // 1.5x Overallocate
                uniforms = (unsigned char*)realloc(gl->uniforms, structSize * cuniforms);
                if (uniforms == NULL) return -1;
                gl->uniforms = uniforms;
                gl->cuniforms = cuniforms;
        }
        ret = gl->nuniforms * structSize;
        gl->nuniforms += n;
        return ret;
}

static GLNVGfragUniforms* nvg__fragUniformPtr(GLNVGcontext* gl, int i)
{
        return (GLNVGfragUniforms*)&gl->uniforms[i];
}

static void glnvg__vset(NVGvertex* vtx, float x, float y, float u, float v)
{
        vtx->x = x;
        vtx->y = y;
        vtx->u = u;
        vtx->v = v;
}

static void glnvg__renderFill(void* uptr, NVGpaint* paint, NVGscissor* scissor, float fringe,
                                                          const float* bounds, const NVGpath* paths, int npaths)
{
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        GLNVGcall* call = glnvg__allocCall(gl);
        NVGvertex* quad;
        GLNVGfragUniforms* frag;
        int i, maxverts, offset;

        if (call == NULL) return;

        call->type = GLNVG_FILL;
        call->pathOffset = glnvg__allocPaths(gl, npaths);
        if (call->pathOffset == -1) goto error;
        call->pathCount = npaths;
        call->image = paint->image;

        if (npaths == 1 && paths[0].convex)
                call->type = GLNVG_CONVEXFILL;

        // Allocate vertices for all the paths.
        maxverts = glnvg__maxVertCount(paths, npaths) + 6;
        offset = glnvg__allocVerts(gl, maxverts);
        if (offset == -1) goto error;

        for (i = 0; i < npaths; i++) {
                GLNVGpath* copy = &gl->paths[call->pathOffset + i];
                const NVGpath* path = &paths[i];
                memset(copy, 0, sizeof(GLNVGpath));
                if (path->nfill > 0) {
                        copy->fillOffset = offset;
                        copy->fillCount = path->nfill;
                        memcpy(&gl->verts[offset], path->fill, sizeof(NVGvertex) * path->nfill);
                        offset += path->nfill;
                }
                if (path->nstroke > 0) {
                        copy->strokeOffset = offset;
                        copy->strokeCount = path->nstroke;
                        memcpy(&gl->verts[offset], path->stroke, sizeof(NVGvertex) * path->nstroke);
                        offset += path->nstroke;
                }
        }

        // Quad
        call->triangleOffset = offset;
        call->triangleCount = 6;
        quad = &gl->verts[call->triangleOffset];
        glnvg__vset(&quad[0], bounds[0], bounds[3], 0.5f, 1.0f);
        glnvg__vset(&quad[1], bounds[2], bounds[3], 0.5f, 1.0f);
        glnvg__vset(&quad[2], bounds[2], bounds[1], 0.5f, 1.0f);

        glnvg__vset(&quad[3], bounds[0], bounds[3], 0.5f, 1.0f);
        glnvg__vset(&quad[4], bounds[2], bounds[1], 0.5f, 1.0f);
        glnvg__vset(&quad[5], bounds[0], bounds[1], 0.5f, 1.0f);

        // Setup uniforms for draw calls
        if (call->type == GLNVG_FILL) {
                call->uniformOffset = glnvg__allocFragUniforms(gl, 2);
                if (call->uniformOffset == -1) goto error;
                // Simple shader for stencil
                frag = nvg__fragUniformPtr(gl, call->uniformOffset);
                memset(frag, 0, sizeof(*frag));
                frag->strokeThr = -1.0f;
                frag->type = NSVG_SHADER_SIMPLE;
                // Fill shader
                glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset + gl->fragSize), paint, scissor, fringe, fringe, -1.0f);
        } else {
                call->uniformOffset = glnvg__allocFragUniforms(gl, 1);
                if (call->uniformOffset == -1) goto error;
                // Fill shader
                glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset), paint, scissor, fringe, fringe, -1.0f);
        }

        return;

error:
        // We get here if call alloc was ok, but something else is not.
        // Roll back the last call to prevent drawing it.
        if (gl->ncalls > 0) gl->ncalls--;
}

static void glnvg__renderStroke(void* uptr, NVGpaint* paint, NVGscissor* scissor, float fringe,
                                                                float strokeWidth, const NVGpath* paths, int npaths)
{
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        GLNVGcall* call = glnvg__allocCall(gl);
        int i, maxverts, offset;

        if (call == NULL) return;

        call->type = GLNVG_STROKE;
        call->pathOffset = glnvg__allocPaths(gl, npaths);
        if (call->pathOffset == -1) goto error;
        call->pathCount = npaths;
        call->image = paint->image;

        // Allocate vertices for all the paths.
        maxverts = glnvg__maxVertCount(paths, npaths);
        offset = glnvg__allocVerts(gl, maxverts);
        if (offset == -1) goto error;

        for (i = 0; i < npaths; i++) {
                GLNVGpath* copy = &gl->paths[call->pathOffset + i];
                const NVGpath* path = &paths[i];
                memset(copy, 0, sizeof(GLNVGpath));
                if (path->nstroke) {
                        copy->strokeOffset = offset;
                        copy->strokeCount = path->nstroke;
                        memcpy(&gl->verts[offset], path->stroke, sizeof(NVGvertex) * path->nstroke);
                        offset += path->nstroke;
                }
        }

        if (gl->flags & NVG_STENCIL_STROKES) {
                // Fill shader
                call->uniformOffset = glnvg__allocFragUniforms(gl, 2);
                if (call->uniformOffset == -1) goto error;

                glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset), paint, scissor, strokeWidth, fringe, -1.0f);
                glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset + gl->fragSize), paint, scissor, strokeWidth, fringe, 1.0f - 0.5f/255.0f);

        } else {
                // Fill shader
                call->uniformOffset = glnvg__allocFragUniforms(gl, 1);
                if (call->uniformOffset == -1) goto error;
                glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset), paint, scissor, strokeWidth, fringe, -1.0f);
        }

        return;

error:
        // We get here if call alloc was ok, but something else is not.
        // Roll back the last call to prevent drawing it.
        if (gl->ncalls > 0) gl->ncalls--;
}

static void glnvg__renderTriangles(void* uptr, NVGpaint* paint, NVGscissor* scissor,
                                                                   const NVGvertex* verts, int nverts)
{
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        GLNVGcall* call = glnvg__allocCall(gl);
        GLNVGfragUniforms* frag;

        if (call == NULL) return;

        call->type = GLNVG_TRIANGLES;
        call->image = paint->image;

        // Allocate vertices for all the paths.
        call->triangleOffset = glnvg__allocVerts(gl, nverts);
        if (call->triangleOffset == -1) goto error;
        call->triangleCount = nverts;

        memcpy(&gl->verts[call->triangleOffset], verts, sizeof(NVGvertex) * nverts);

        // Fill shader
        call->uniformOffset = glnvg__allocFragUniforms(gl, 1);
        if (call->uniformOffset == -1) goto error;
        frag = nvg__fragUniformPtr(gl, call->uniformOffset);
        glnvg__convertPaint(gl, frag, paint, scissor, 1.0f, 1.0f, -1.0f);
        frag->type = NSVG_SHADER_IMG;

        return;

error:
        // We get here if call alloc was ok, but something else is not.
        // Roll back the last call to prevent drawing it.
        if (gl->ncalls > 0) gl->ncalls--;
}

static void glnvg__renderDelete(void* uptr)
{
        GLNVGcontext* gl = (GLNVGcontext*)uptr;
        int i;
        if (gl == NULL) return;

        glnvg__deleteShader(&gl->shader);

#if NANOVG_GL3
#if NANOVG_GL_USE_UNIFORMBUFFER
        if (gl->fragBuf != 0)
                glDeleteBuffers(1, &gl->fragBuf);
#endif
        if (gl->vertArr != 0)
                glDeleteVertexArrays(1, &gl->vertArr);
#endif
        if (gl->vertBuf != 0)
                glDeleteBuffers(1, &gl->vertBuf);

        for (i = 0; i < gl->ntextures; i++) {
                if (gl->textures[i].tex != 0 && (gl->textures[i].flags & NVG_IMAGE_NODELETE) == 0)
                        glDeleteTextures(1, &gl->textures[i].tex);
        }
        free(gl->textures);

        free(gl->paths);
        free(gl->verts);
        free(gl->uniforms);
        free(gl->calls);

        free(gl);
}


#if defined NANOVG_GL2
NVGcontext* nvgCreateGL2(int flags)
#elif defined NANOVG_GL3
NVGcontext* nvgCreateGL3(int flags)
#elif defined NANOVG_GLES2
NVGcontext* nvgCreateGLES2(int flags)
#elif defined NANOVG_GLES3
NVGcontext* nvgCreateGLES3(int flags)
#endif
{
        NVGparams params;
        NVGcontext* ctx = NULL;
        GLNVGcontext* gl = (GLNVGcontext*)malloc(sizeof(GLNVGcontext));
        if (gl == NULL) goto error;
        memset(gl, 0, sizeof(GLNVGcontext));

        memset(&params, 0, sizeof(params));
        params.renderCreate = glnvg__renderCreate;
        params.renderCreateTexture = glnvg__renderCreateTexture;
        params.renderDeleteTexture = glnvg__renderDeleteTexture;
        params.renderUpdateTexture = glnvg__renderUpdateTexture;
        params.renderGetTextureSize = glnvg__renderGetTextureSize;
        params.renderViewport = glnvg__renderViewport;
        params.renderCancel = glnvg__renderCancel;
        params.renderFlush = glnvg__renderFlush;
        params.renderFill = glnvg__renderFill;
        params.renderStroke = glnvg__renderStroke;
        params.renderTriangles = glnvg__renderTriangles;
        params.renderDelete = glnvg__renderDelete;
        params.userPtr = gl;
        params.edgeAntiAlias = flags & NVG_ANTIALIAS ? 1 : 0;

        gl->flags = flags;

        ctx = nvgCreateInternal(&params);
        if (ctx == NULL) goto error;

        return ctx;

error:
        // 'gl' is freed by nvgDeleteInternal.
        if (ctx != NULL) nvgDeleteInternal(ctx);
        return NULL;
}

#if defined NANOVG_GL2
void nvgDeleteGL2(NVGcontext* ctx)
#elif defined NANOVG_GL3
void nvgDeleteGL3(NVGcontext* ctx)
#elif defined NANOVG_GLES2
void nvgDeleteGLES2(NVGcontext* ctx)
#elif defined NANOVG_GLES3
void nvgDeleteGLES3(NVGcontext* ctx)
#endif
{
        nvgDeleteInternal(ctx);
}

int nvglCreateImageFromHandle(NVGcontext* ctx, GLuint textureId, int w, int h, int imageFlags)
{
        GLNVGcontext* gl = (GLNVGcontext*)nvgInternalParams(ctx)->userPtr;
        GLNVGtexture* tex = glnvg__allocTexture(gl);

        if (tex == NULL) return 0;

        tex->type = NVG_TEXTURE_RGBA;
        tex->tex = textureId;
        tex->flags = imageFlags;
        tex->width = w;
        tex->height = h;

        return tex->id;
}

GLuint nvglImageHandle(NVGcontext* ctx, int image)
{
        GLNVGcontext* gl = (GLNVGcontext*)nvgInternalParams(ctx)->userPtr;
        GLNVGtexture* tex = glnvg__findTexture(gl, image);
        return tex->tex;
}

#endif

#include <stdio.h>
#include <math.h>
#define FONTSTASH_IMPLEMENTATION
#include "fontstash.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifdef _MSC_VER
#pragma warning(disable: 4100)  // unreferenced formal parameter
#pragma warning(disable: 4127)  // conditional expression is constant
#pragma warning(disable: 4204)  // nonstandard extension used : non-constant aggregate initializer
#pragma warning(disable: 4706)  // assignment within conditional expression
#endif

#define NVG_INIT_FONTIMAGE_SIZE  512
#define NVG_MAX_FONTIMAGE_SIZE   2048
#define NVG_MAX_FONTIMAGES       4

#define NVG_INIT_COMMANDS_SIZE 256
#define NVG_INIT_POINTS_SIZE 128
#define NVG_INIT_PATHS_SIZE 16
#define NVG_INIT_VERTS_SIZE 256
#define NVG_MAX_STATES 32

#define NVG_KAPPA90 0.5522847493f	// Length proportional to radius of a cubic bezier handle for 90deg arcs.

#define NVG_COUNTOF(arr) (sizeof(arr) / sizeof(0[arr]))

enum NVGcommands {
    NVG_MOVETO = 0,
    NVG_LINETO = 1,
    NVG_BEZIERTO = 2,
    NVG_CLOSE = 3,
    NVG_WINDING = 4,
};

enum NVGpointFlags
{
    NVG_PT_CORNER = 0x01,
    NVG_PT_LEFT = 0x02,
    NVG_PT_BEVEL = 0x04,
    NVG_PR_INNERBEVEL = 0x08,
};

struct NVGstate {
    NVGpaint fill;
    NVGpaint stroke;
    float strokeWidth;
    float miterLimit;
    int lineJoin;
    int lineCap;
    float alpha;
    float xform[6];
    NVGscissor scissor;
    float fontSize;
    float letterSpacing;
    float lineHeight;
    float fontBlur;
    int textAlign;
    int fontId;
};
typedef struct NVGstate NVGstate;

struct NVGpoint {
    float x,y;
    float dx, dy;
    float len;
    float dmx, dmy;
    unsigned char flags;
};
typedef struct NVGpoint NVGpoint;

struct NVGpathCache {
    NVGpoint* points;
    int npoints;
    int cpoints;
    NVGpath* paths;
    int npaths;
    int cpaths;
    NVGvertex* verts;
    int nverts;
    int cverts;
    float bounds[4];
};
typedef struct NVGpathCache NVGpathCache;

struct NVGcontext {
    NVGparams params;
    float* commands;
    int ccommands;
    int ncommands;
    float commandx, commandy;
    NVGstate states[NVG_MAX_STATES];
    int nstates;
    NVGpathCache* cache;
    float tessTol;
    float distTol;
    float fringeWidth;
    float devicePxRatio;
    struct FONScontext* fs;
    int fontImages[NVG_MAX_FONTIMAGES];
    int fontImageIdx;
    int drawCallCount;
    int fillTriCount;
    int strokeTriCount;
    int textTriCount;
};

static float nvg__sqrtf(float a) { return sqrtf(a); }
static float nvg__modf(float a, float b) { return fmodf(a, b); }
static float nvg__sinf(float a) { return sinf(a); }
static float nvg__cosf(float a) { return cosf(a); }
static float nvg__tanf(float a) { return tanf(a); }
static float nvg__atan2f(float a,float b) { return atan2f(a, b); }
static float nvg__acosf(float a) { return acosf(a); }

static int nvg__mini(int a, int b) { return a < b ? a : b; }
static int nvg__maxi(int a, int b) { return a > b ? a : b; }
static int nvg__clampi(int a, int mn, int mx) { return a < mn ? mn : (a > mx ? mx : a); }
static float nvg__minf(float a, float b) { return a < b ? a : b; }
static float nvg__maxf(float a, float b) { return a > b ? a : b; }
static float nvg__absf(float a) { return a >= 0.0f ? a : -a; }
static float nvg__signf(float a) { return a >= 0.0f ? 1.0f : -1.0f; }
static float nvg__clampf(float a, float mn, float mx) { return a < mn ? mn : (a > mx ? mx : a); }
static float nvg__cross(float dx0, float dy0, float dx1, float dy1) { return dx1*dy0 - dx0*dy1; }

static float nvg__normalize(float *x, float* y)
{
    float d = nvg__sqrtf((*x)*(*x) + (*y)*(*y));
    if (d > 1e-6f) {
        float id = 1.0f / d;
        *x *= id;
        *y *= id;
    }
    return d;
}


static void nvg__deletePathCache(NVGpathCache* c)
{
    if (c == NULL) return;
    if (c->points != NULL) free(c->points);
    if (c->paths != NULL) free(c->paths);
    if (c->verts != NULL) free(c->verts);
    free(c);
}

static NVGpathCache* nvg__allocPathCache(void)
{
    NVGpathCache* c = (NVGpathCache*)malloc(sizeof(NVGpathCache));
    if (c == NULL) goto error;
    memset(c, 0, sizeof(NVGpathCache));

    c->points = (NVGpoint*)malloc(sizeof(NVGpoint)*NVG_INIT_POINTS_SIZE);
    if (!c->points) goto error;
    c->npoints = 0;
    c->cpoints = NVG_INIT_POINTS_SIZE;

    c->paths = (NVGpath*)malloc(sizeof(NVGpath)*NVG_INIT_PATHS_SIZE);
    if (!c->paths) goto error;
    c->npaths = 0;
    c->cpaths = NVG_INIT_PATHS_SIZE;

    c->verts = (NVGvertex*)malloc(sizeof(NVGvertex)*NVG_INIT_VERTS_SIZE);
    if (!c->verts) goto error;
    c->nverts = 0;
    c->cverts = NVG_INIT_VERTS_SIZE;

    return c;
error:
    nvg__deletePathCache(c);
    return NULL;
}

static void nvg__setDevicePixelRatio(NVGcontext* ctx, float ratio)
{
    ctx->tessTol = 0.25f / ratio;
    ctx->distTol = 0.01f / ratio;
    ctx->fringeWidth = 1.0f / ratio;
    ctx->devicePxRatio = ratio;
}

NVGcontext* nvgCreateInternal(NVGparams* params)
{
    FONSparams fontParams;
    NVGcontext* ctx = (NVGcontext*)malloc(sizeof(NVGcontext));
    int i;
    if (ctx == NULL) goto error;
    memset(ctx, 0, sizeof(NVGcontext));

    ctx->params = *params;
    for (i = 0; i < NVG_MAX_FONTIMAGES; i++)
        ctx->fontImages[i] = 0;

    ctx->commands = (float*)malloc(sizeof(float)*NVG_INIT_COMMANDS_SIZE);
    if (!ctx->commands) goto error;
    ctx->ncommands = 0;
    ctx->ccommands = NVG_INIT_COMMANDS_SIZE;

    ctx->cache = nvg__allocPathCache();
    if (ctx->cache == NULL) goto error;

    nvgSave(ctx);
    nvgReset(ctx);

    nvg__setDevicePixelRatio(ctx, 1.0f);

    if (ctx->params.renderCreate(ctx->params.userPtr) == 0) goto error;

    // Init font rendering
    memset(&fontParams, 0, sizeof(fontParams));
    fontParams.width = NVG_INIT_FONTIMAGE_SIZE;
    fontParams.height = NVG_INIT_FONTIMAGE_SIZE;
    fontParams.flags = FONS_ZERO_TOPLEFT;
    fontParams.renderCreate = NULL;
    fontParams.renderUpdate = NULL;
    fontParams.renderDraw = NULL;
    fontParams.renderDelete = NULL;
    fontParams.userPtr = NULL;
    ctx->fs = fonsCreateInternal(&fontParams);
    if (ctx->fs == NULL) goto error;

    // Create font texture
    ctx->fontImages[0] = ctx->params.renderCreateTexture(ctx->params.userPtr, NVG_TEXTURE_ALPHA, fontParams.width, fontParams.height, 0, NULL);
    if (ctx->fontImages[0] == 0) goto error;
    ctx->fontImageIdx = 0;

    return ctx;

error:
    nvgDeleteInternal(ctx);
    return 0;
}

NVGparams* nvgInternalParams(NVGcontext* ctx)
{
    return &ctx->params;
}

void nvgDeleteInternal(NVGcontext* ctx)
{
    int i;
    if (ctx == NULL) return;
    if (ctx->commands != NULL) free(ctx->commands);
    if (ctx->cache != NULL) nvg__deletePathCache(ctx->cache);

    if (ctx->fs)
        fonsDeleteInternal(ctx->fs);

    for (i = 0; i < NVG_MAX_FONTIMAGES; i++) {
        if (ctx->fontImages[i] != 0) {
            nvgDeleteImage(ctx, ctx->fontImages[i]);
            ctx->fontImages[i] = 0;
        }
    }

    if (ctx->params.renderDelete != NULL)
        ctx->params.renderDelete(ctx->params.userPtr);

    free(ctx);
}

// Begin drawing a new frame
// Calls to nanovg drawing API should be wrapped in nvgBeginFrame() & nvgEndFrame()
// nvgBeginFrame() defines the size of the window to render to in relation currently
// set viewport (i.e. glViewport on GL backends). Device pixel ration allows to
// control the rendering on Hi-DPI devices.
// For example, GLFW returns two dimension for an opened window: window size and
// frame buffer size. In that case you would set windowWidth/Height to the window size
// devicePixelRatio to: frameBufferWidth / windowWidth.
void nvgBeginFrame(NVGcontext* ctx, int windowWidth, int windowHeight, float devicePixelRatio)
{
/*	printf("Tris: draws:%d  fill:%d  stroke:%d  text:%d  TOT:%d\n",
        ctx->drawCallCount, ctx->fillTriCount, ctx->strokeTriCount, ctx->textTriCount,
        ctx->fillTriCount+ctx->strokeTriCount+ctx->textTriCount);*/

    ctx->nstates = 0;
    nvgSave(ctx);
    nvgReset(ctx);

    nvg__setDevicePixelRatio(ctx, devicePixelRatio);

    ctx->params.renderViewport(ctx->params.userPtr, windowWidth, windowHeight);

    ctx->drawCallCount = 0;
    ctx->fillTriCount = 0;
    ctx->strokeTriCount = 0;
    ctx->textTriCount = 0;
}

// Cancels drawing the current frame.
void nvgCancelFrame(NVGcontext* ctx)
{
    ctx->params.renderCancel(ctx->params.userPtr);
}

// Ends drawing flushing remaining render state.
void nvgEndFrame(NVGcontext* ctx)
{
    ctx->params.renderFlush(ctx->params.userPtr);
    if (ctx->fontImageIdx != 0) {
        int fontImage = ctx->fontImages[ctx->fontImageIdx];
        int i, j, iw, ih;
        // delete images that smaller than current one
        if (fontImage == 0)
            return;
        nvgImageSize(ctx, fontImage, &iw, &ih);
        for (i = j = 0; i < ctx->fontImageIdx; i++) {
            if (ctx->fontImages[i] != 0) {
                int nw, nh;
                nvgImageSize(ctx, ctx->fontImages[i], &nw, &nh);
                if (nw < iw || nh < ih)
                    nvgDeleteImage(ctx, ctx->fontImages[i]);
                else
                    ctx->fontImages[j++] = ctx->fontImages[i];
            }
        }
        // make current font image to first
        ctx->fontImages[j++] = ctx->fontImages[0];
        ctx->fontImages[0] = fontImage;
        ctx->fontImageIdx = 0;
        // clear all images after j
        for (i = j; i < NVG_MAX_FONTIMAGES; i++)
            ctx->fontImages[i] = 0;
    }
}

// Returns a color value from red, green, blue values. Alpha will be set to 255 (1.0f).
NVGcolor nvgRGB(unsigned char r, unsigned char g, unsigned char b)
{
    return nvgRGBA(r,g,b,255);
}

// Returns a color value from red, green, blue values. Alpha will be set to 1.0f.
NVGcolor nvgRGBf(float r, float g, float b)
{
    return nvgRGBAf(r,g,b,1.0f);
}

// Returns a color value from red, green, blue and alpha values.
NVGcolor nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    NVGcolor color;
    // Use longer initialization to suppress warning.
    color.r = r / 255.0f;
    color.g = g / 255.0f;
    color.b = b / 255.0f;
    color.a = a / 255.0f;
    return color;
}

// Returns a color value from red, green, blue and alpha values.
NVGcolor nvgRGBAf(float r, float g, float b, float a)
{
    NVGcolor color;
    // Use longer initialization to suppress warning.
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

// Sets transparency of a color value.
NVGcolor nvgTransRGBA(NVGcolor c, unsigned char a)
{
    c.a = a / 255.0f;
    return c;
}

// Sets transparency of a color value.
NVGcolor nvgTransRGBAf(NVGcolor c, float a)
{
    c.a = a;
    return c;
}

// Linearly interpolates from color c0 to c1, and returns resulting color value.
NVGcolor nvgLerpRGBA(NVGcolor c0, NVGcolor c1, float u)
{
    int i;
    float oneminu;
    NVGcolor cint;

    u = nvg__clampf(u, 0.0f, 1.0f);
    oneminu = 1.0f - u;
    for( i = 0; i <4; i++ )
    {
        cint.rgba[i] = c0.rgba[i] * oneminu + c1.rgba[i] * u;
    }

    return cint;
}

// Returns color value specified by hue, saturation and lightness.
// HSL values are all in range [0..1], alpha will be set to 255.
NVGcolor nvgHSL(float h, float s, float l)
{
    return nvgHSLA(h,s,l,255);
}

static float nvg__hue(float h, float m1, float m2)
{
    if (h < 0) h += 1;
    if (h > 1) h -= 1;
    if (h < 1.0f/6.0f)
        return m1 + (m2 - m1) * h * 6.0f;
    else if (h < 3.0f/6.0f)
        return m2;
    else if (h < 4.0f/6.0f)
        return m1 + (m2 - m1) * (2.0f/3.0f - h) * 6.0f;
    return m1;
}

// Returns color value specified by hue, saturation and lightness and alpha.
// HSL values are all in range [0..1], alpha in range [0..255]
NVGcolor nvgHSLA(float h, float s, float l, unsigned char a)
{
    float m1, m2;
    NVGcolor col;
    h = nvg__modf(h, 1.0f);
    if (h < 0.0f) h += 1.0f;
    s = nvg__clampf(s, 0.0f, 1.0f);
    l = nvg__clampf(l, 0.0f, 1.0f);
    m2 = l <= 0.5f ? (l * (1 + s)) : (l + s - l * s);
    m1 = 2 * l - m2;
    col.r = nvg__clampf(nvg__hue(h + 1.0f/3.0f, m1, m2), 0.0f, 1.0f);
    col.g = nvg__clampf(nvg__hue(h, m1, m2), 0.0f, 1.0f);
    col.b = nvg__clampf(nvg__hue(h - 1.0f/3.0f, m1, m2), 0.0f, 1.0f);
    col.a = a/255.0f;
    return col;
}


static NVGstate* nvg__getState(NVGcontext* ctx)
{
    return &ctx->states[ctx->nstates-1];
}

// Sets the transform to identity matrix.
void nvgTransformIdentity(float* t)
{
    t[0] = 1.0f; t[1] = 0.0f;
    t[2] = 0.0f; t[3] = 1.0f;
    t[4] = 0.0f; t[5] = 0.0f;
}

// Sets the transform to translation matrix matrix.
void nvgTransformTranslate(float* t, float tx, float ty)
{
    t[0] = 1.0f; t[1] = 0.0f;
    t[2] = 0.0f; t[3] = 1.0f;
    t[4] = tx; t[5] = ty;
}

// Sets the transform to scale matrix.
void nvgTransformScale(float* t, float sx, float sy)
{
    t[0] = sx; t[1] = 0.0f;
    t[2] = 0.0f; t[3] = sy;
    t[4] = 0.0f; t[5] = 0.0f;
}

// Sets the transform to rotate matrix. Angle is specified in radians.
void nvgTransformRotate(float* t, float a)
{
    float cs = nvg__cosf(a), sn = nvg__sinf(a);
    t[0] = cs; t[1] = sn;
    t[2] = -sn; t[3] = cs;
    t[4] = 0.0f; t[5] = 0.0f;
}

// Sets the transform to skew-x matrix. Angle is specified in radians.
void nvgTransformSkewX(float* t, float a)
{
    t[0] = 1.0f; t[1] = 0.0f;
    t[2] = nvg__tanf(a); t[3] = 1.0f;
    t[4] = 0.0f; t[5] = 0.0f;
}

// Sets the transform to skew-y matrix. Angle is specified in radians.
void nvgTransformSkewY(float* t, float a)
{
    t[0] = 1.0f; t[1] = nvg__tanf(a);
    t[2] = 0.0f; t[3] = 1.0f;
    t[4] = 0.0f; t[5] = 0.0f;
}

// Sets the transform to the result of multiplication of two transforms, of A = A*B.
void nvgTransformMultiply(float* t, const float* s)
{
    float t0 = t[0] * s[0] + t[1] * s[2];
    float t2 = t[2] * s[0] + t[3] * s[2];
    float t4 = t[4] * s[0] + t[5] * s[2] + s[4];
    t[1] = t[0] * s[1] + t[1] * s[3];
    t[3] = t[2] * s[1] + t[3] * s[3];
    t[5] = t[4] * s[1] + t[5] * s[3] + s[5];
    t[0] = t0;
    t[2] = t2;
    t[4] = t4;
}

// Sets the transform to the result of multiplication of two transforms, of A = B*A.
void nvgTransformPremultiply(float* t, const float* s)
{
    float s2[6];
    memcpy(s2, s, sizeof(float)*6);
    nvgTransformMultiply(s2, t);
    memcpy(t, s2, sizeof(float)*6);
}

// Sets the destination to inverse of specified transform.
// Returns 1 if the inverse could be calculated, else 0.
int nvgTransformInverse(float* inv, const float* t)
{
    double invdet, det = (double)t[0] * t[3] - (double)t[2] * t[1];
    if (det > -1e-6 && det < 1e-6) {
        nvgTransformIdentity(inv);
        return 0;
    }
    invdet = 1.0 / det;
    inv[0] = (float)(t[3] * invdet);
    inv[2] = (float)(-t[2] * invdet);
    inv[4] = (float)(((double)t[2] * t[5] - (double)t[3] * t[4]) * invdet);
    inv[1] = (float)(-t[1] * invdet);
    inv[3] = (float)(t[0] * invdet);
    inv[5] = (float)(((double)t[1] * t[4] - (double)t[0] * t[5]) * invdet);
    return 1;
}

// Transform a point by given transform.
void nvgTransformPoint(float* dx, float* dy, const float* t, float sx, float sy)
{
    *dx = sx*t[0] + sy*t[2] + t[4];
    *dy = sx*t[1] + sy*t[3] + t[5];
}

// Converts degrees to radians and vice versa.
float nvgDegToRad(float deg) { return deg / 180.0f * NVG_PI; }
float nvgRadToDeg(float rad) { return rad / NVG_PI * 180.0f; }

static void nvg__setPaintColor(NVGpaint* p, NVGcolor color)
{
    memset(p, 0, sizeof(*p));
    nvgTransformIdentity(p->xform);
    p->radius = 0.0f;
    p->feather = 1.0f;
    p->innerColor = color;
    p->outerColor = color;
}


// Pushes and saves the current render state into a state stack.
// A matching nvgRestore() must be used to restore the state.
void nvgSave(NVGcontext* ctx)
{
    if (ctx->nstates >= NVG_MAX_STATES)
        return;
    if (ctx->nstates > 0)
        memcpy(&ctx->states[ctx->nstates], &ctx->states[ctx->nstates-1], sizeof(NVGstate));
    ctx->nstates++;
}

// Pops and restores current render state.
void nvgRestore(NVGcontext* ctx)
{
    if (ctx->nstates <= 1)
        return;
    ctx->nstates--;
}

// Resets current render state to default values. Does not affect the render state stack.
void nvgReset(NVGcontext* ctx)
{
    NVGstate* state = nvg__getState(ctx);
    memset(state, 0, sizeof(*state));

    nvg__setPaintColor(&state->fill, nvgRGBA(255,255,255,255));
    nvg__setPaintColor(&state->stroke, nvgRGBA(0,0,0,255));
    state->strokeWidth = 1.0f;
    state->miterLimit = 10.0f;
    state->lineCap = NVG_BUTT;
    state->lineJoin = NVG_MITER;
    state->alpha = 1.0f;
    nvgTransformIdentity(state->xform);

    state->scissor.extent[0] = -1.0f;
    state->scissor.extent[1] = -1.0f;

    state->fontSize = 16.0f;
    state->letterSpacing = 0.0f;
    state->lineHeight = 1.0f;
    state->fontBlur = 0.0f;
    state->textAlign = NVG_ALIGN_LEFT | NVG_ALIGN_BASELINE;
    state->fontId = 0;
}

// State setting
void nvgStrokeWidth(NVGcontext* ctx, float width)
{
    NVGstate* state = nvg__getState(ctx);
    state->strokeWidth = width;
}

// Sets the miter limit of the stroke style.
// Miter limit controls when a sharp corner is beveled.
void nvgMiterLimit(NVGcontext* ctx, float limit)
{
    NVGstate* state = nvg__getState(ctx);
    state->miterLimit = limit;
}

// Sets how the end of the line (cap) is drawn,
// Can be one of: NVG_BUTT (default), NVG_ROUND, NVG_SQUARE.
void nvgLineCap(NVGcontext* ctx, int cap)
{
    NVGstate* state = nvg__getState(ctx);
    state->lineCap = cap;
}

// Sets how sharp path corners are drawn.
// Can be one of NVG_MITER (default), NVG_ROUND, NVG_BEVEL.
void nvgLineJoin(NVGcontext* ctx, int join)
{
    NVGstate* state = nvg__getState(ctx);
    state->lineJoin = join;
}

// Sets the transparency applied to all rendered shapes.
// Already transparent paths will get proportionally more transparent as well.
void nvgGlobalAlpha(NVGcontext* ctx, float alpha)
{
    NVGstate* state = nvg__getState(ctx);
    state->alpha = alpha;
}

// Premultiplies current coordinate system by specified matrix.
// The parameters are interpreted as matrix as follows:
//   [a c e]
//   [b d f]
//   [0 0 1]
void nvgTransform(NVGcontext* ctx, float a, float b, float c, float d, float e, float f)
{
    NVGstate* state = nvg__getState(ctx);
    float t[6] = { a, b, c, d, e, f };
    nvgTransformPremultiply(state->xform, t);
}

// Resets current transform to a identity matrix.
void nvgResetTransform(NVGcontext* ctx)
{
    NVGstate* state = nvg__getState(ctx);
    nvgTransformIdentity(state->xform);
}

// Translates current coordinate system.
void nvgTranslate(NVGcontext* ctx, float x, float y)
{
    NVGstate* state = nvg__getState(ctx);
    float t[6];
    nvgTransformTranslate(t, x,y);
    nvgTransformPremultiply(state->xform, t);
}

// Translates current coordinate system.
void nvgRotate(NVGcontext* ctx, float angle)
{
    NVGstate* state = nvg__getState(ctx);
    float t[6];
    nvgTransformRotate(t, angle);
    nvgTransformPremultiply(state->xform, t);
}

// Skews the current coordinate system along X axis. Angle is specified in radians.
void nvgSkewX(NVGcontext* ctx, float angle)
{
    NVGstate* state = nvg__getState(ctx);
    float t[6];
    nvgTransformSkewX(t, angle);
    nvgTransformPremultiply(state->xform, t);
}

// Skews the current coordinate system along Y axis. Angle is specified in radians.
void nvgSkewY(NVGcontext* ctx, float angle)
{
    NVGstate* state = nvg__getState(ctx);
    float t[6];
    nvgTransformSkewY(t, angle);
    nvgTransformPremultiply(state->xform, t);
}

// Scales the current coordinate system.
void nvgScale(NVGcontext* ctx, float x, float y)
{
    NVGstate* state = nvg__getState(ctx);
    float t[6];
    nvgTransformScale(t, x,y);
    nvgTransformPremultiply(state->xform, t);
}

// Stores the top part (a-f) of the current transformation matrix in to the specified buffer.
//   [a c e]
//   [b d f]
//   [0 0 1]
// There should be space for 6 floats in the return buffer for the values a-f.
void nvgCurrentTransform(NVGcontext* ctx, float* xform)
{
    NVGstate* state = nvg__getState(ctx);
    if (xform == NULL) return;
    memcpy(xform, state->xform, sizeof(float)*6);
}

// Sets current stroke style to a solid color.
void nvgStrokeColor(NVGcontext* ctx, NVGcolor color)
{
    NVGstate* state = nvg__getState(ctx);
    nvg__setPaintColor(&state->stroke, color);
}

// Sets current stroke style to a paint, which can be a one of the gradients or a pattern.
void nvgStrokePaint(NVGcontext* ctx, NVGpaint paint)
{
    NVGstate* state = nvg__getState(ctx);
    state->stroke = paint;
    nvgTransformMultiply(state->stroke.xform, state->xform);
}

// Sets current fill style to a solid color.
void nvgFillColor(NVGcontext* ctx, NVGcolor color)
{
    NVGstate* state = nvg__getState(ctx);
    nvg__setPaintColor(&state->fill, color);
}

// Sets current fill style to a paint, which can be a one of the gradients or a pattern.
void nvgFillPaint(NVGcontext* ctx, NVGpaint paint)
{
    NVGstate* state = nvg__getState(ctx);
    state->fill = paint;
    nvgTransformMultiply(state->fill.xform, state->xform);
}

// Creates image by loading it from the disk from specified file name.
// Returns handle to the image.
int nvgCreateImage(NVGcontext* ctx, const char* filename, int imageFlags)
{
    int w, h, n, image;
    unsigned char* img;
    stbi_set_unpremultiply_on_load(1);
    stbi_convert_iphone_png_to_rgb(1);
    img = stbi_load(filename, &w, &h, &n, 4);
    if (img == NULL) {
//		printf("Failed to load %s - %s\n", filename, stbi_failure_reason());
        return 0;
    }
    image = nvgCreateImageRGBA(ctx, w, h, imageFlags, img);
    stbi_image_free(img);
    return image;
}

// Creates image by loading it from the specified chunk of memory.
// Returns handle to the image.
int nvgCreateImageMem(NVGcontext* ctx, int imageFlags, unsigned char* data, int ndata)
{
    int w, h, n, image;
    unsigned char* img = stbi_load_from_memory(data, ndata, &w, &h, &n, 4);
    if (img == NULL) {
//		printf("Failed to load %s - %s\n", filename, stbi_failure_reason());
        return 0;
    }
    image = nvgCreateImageRGBA(ctx, w, h, imageFlags, img);
    stbi_image_free(img);
    return image;
}

// Creates image from specified image data.
// Returns handle to the image.
int nvgCreateImageRGBA(NVGcontext* ctx, int w, int h, int imageFlags, const unsigned char* data)
{
    return ctx->params.renderCreateTexture(ctx->params.userPtr, NVG_TEXTURE_RGBA, w, h, imageFlags, data);
}

// Updates image data specified by image handle.
void nvgUpdateImage(NVGcontext* ctx, int image, const unsigned char* data)
{
    int w, h;
    ctx->params.renderGetTextureSize(ctx->params.userPtr, image, &w, &h);
    ctx->params.renderUpdateTexture(ctx->params.userPtr, image, 0,0, w,h, data);
}

// Returns the dimensions of a created image.
void nvgImageSize(NVGcontext* ctx, int image, int* w, int* h)
{
    ctx->params.renderGetTextureSize(ctx->params.userPtr, image, w, h);
}

// Deletes created image.
void nvgDeleteImage(NVGcontext* ctx, int image)
{
    ctx->params.renderDeleteTexture(ctx->params.userPtr, image);
}

// Creates and returns a linear gradient. Parameters (sx,sy)-(ex,ey) specify the start and end coordinates
// of the linear gradient, icol specifies the start color and ocol the end color.
// The gradient is transformed by the current transform when it is passed to nvgFillPaint() or nvgStrokePaint().
NVGpaint nvgLinearGradient(NVGcontext* ctx,
                                  float sx, float sy, float ex, float ey,
                                  NVGcolor icol, NVGcolor ocol)
{
    NVGpaint p;
    float dx, dy, d;
    const float large = 1e5;
    NVG_NOTUSED(ctx);
    memset(&p, 0, sizeof(p));

    // Calculate transform aligned to the line
    dx = ex - sx;
    dy = ey - sy;
    d = sqrtf(dx*dx + dy*dy);
    if (d > 0.0001f) {
        dx /= d;
        dy /= d;
    } else {
        dx = 0;
        dy = 1;
    }

    p.xform[0] = dy; p.xform[1] = -dx;
    p.xform[2] = dx; p.xform[3] = dy;
    p.xform[4] = sx - dx*large; p.xform[5] = sy - dy*large;

    p.extent[0] = large;
    p.extent[1] = large + d*0.5f;

    p.radius = 0.0f;

    p.feather = nvg__maxf(1.0f, d);

    p.innerColor = icol;
    p.outerColor = ocol;

    return p;
}

// Creates and returns a radial gradient. Parameters (cx,cy) specify the center, inr and outr specify
// the inner and outer radius of the gradient, icol specifies the start color and ocol the end color.
// The gradient is transformed by the current transform when it is passed to nvgFillPaint() or nvgStrokePaint().
NVGpaint nvgRadialGradient(NVGcontext* ctx,
                                  float cx, float cy, float inr, float outr,
                                  NVGcolor icol, NVGcolor ocol)
{
    NVGpaint p;
    float r = (inr+outr)*0.5f;
    float f = (outr-inr);
    NVG_NOTUSED(ctx);
    memset(&p, 0, sizeof(p));

    nvgTransformIdentity(p.xform);
    p.xform[4] = cx;
    p.xform[5] = cy;

    p.extent[0] = r;
    p.extent[1] = r;

    p.radius = r;

    p.feather = nvg__maxf(1.0f, f);

    p.innerColor = icol;
    p.outerColor = ocol;

    return p;
}

// Creates and returns a box gradient. Box gradient is a feathered rounded rectangle, it is useful for rendering
// drop shadows or highlights for boxes. Parameters (x,y) define the top-left corner of the rectangle,
// (w,h) define the size of the rectangle, r defines the corner radius, and f feather. Feather defines how blurry
// the border of the rectangle is. Parameter icol specifies the inner color and ocol the outer color of the gradient.
// The gradient is transformed by the current transform when it is passed to nvgFillPaint() or nvgStrokePaint().
NVGpaint nvgBoxGradient(NVGcontext* ctx,
                               float x, float y, float w, float h, float r, float f,
                               NVGcolor icol, NVGcolor ocol)
{
    NVGpaint p;
    NVG_NOTUSED(ctx);
    memset(&p, 0, sizeof(p));

    nvgTransformIdentity(p.xform);
    p.xform[4] = x+w*0.5f;
    p.xform[5] = y+h*0.5f;

    p.extent[0] = w*0.5f;
    p.extent[1] = h*0.5f;

    p.radius = r;

    p.feather = nvg__maxf(1.0f, f);

    p.innerColor = icol;
    p.outerColor = ocol;

    return p;
}

// Creates and returns an image patter. Parameters (ox,oy) specify the left-top location of the image pattern,
// (ex,ey) the size of one image, angle rotation around the top-left corner, image is handle to the image to render.
// The gradient is transformed by the current transform when it is passed to nvgFillPaint() or nvgStrokePaint().
NVGpaint nvgImagePattern(NVGcontext* ctx,
                                float cx, float cy, float w, float h, float angle,
                                int image, float alpha)
{
    NVGpaint p;
    NVG_NOTUSED(ctx);
    memset(&p, 0, sizeof(p));

    nvgTransformRotate(p.xform, angle);
    p.xform[4] = cx;
    p.xform[5] = cy;

    p.extent[0] = w;
    p.extent[1] = h;

    p.image = image;

    p.innerColor = p.outerColor = nvgRGBAf(1,1,1,alpha);

    return p;
}

// Sets the current scissor rectangle.
// The scissor rectangle is transformed by the current transform.
void nvgScissor(NVGcontext* ctx, float x, float y, float w, float h)
{
    NVGstate* state = nvg__getState(ctx);

    w = nvg__maxf(0.0f, w);
    h = nvg__maxf(0.0f, h);

    nvgTransformIdentity(state->scissor.xform);
    state->scissor.xform[4] = x+w*0.5f;
    state->scissor.xform[5] = y+h*0.5f;
    nvgTransformMultiply(state->scissor.xform, state->xform);

    state->scissor.extent[0] = w*0.5f;
    state->scissor.extent[1] = h*0.5f;
}

static void nvg__isectRects(float* dst,
                            float ax, float ay, float aw, float ah,
                            float bx, float by, float bw, float bh)
{
    float minx = nvg__maxf(ax, bx);
    float miny = nvg__maxf(ay, by);
    float maxx = nvg__minf(ax+aw, bx+bw);
    float maxy = nvg__minf(ay+ah, by+bh);
    dst[0] = minx;
    dst[1] = miny;
    dst[2] = nvg__maxf(0.0f, maxx - minx);
    dst[3] = nvg__maxf(0.0f, maxy - miny);
}

// Intersects current scissor rectangle with the specified rectangle.
// The scissor rectangle is transformed by the current transform.
// Note: in case the rotation of previous scissor rect differs from
// the current one, the intersection will be done between the specified
// rectangle and the previous scissor rectangle transformed in the current
// transform space. The resulting shape is always rectangle.
void nvgIntersectScissor(NVGcontext* ctx, float x, float y, float w, float h)
{
    NVGstate* state = nvg__getState(ctx);
    float pxform[6], invxorm[6];
    float rect[4];
    float ex, ey, tex, tey;

    // If no previous scissor has been set, set the scissor as current scissor.
    if (state->scissor.extent[0] < 0) {
        nvgScissor(ctx, x, y, w, h);
        return;
    }

    // Transform the current scissor rect into current transform space.
    // If there is difference in rotation, this will be approximation.
    memcpy(pxform, state->scissor.xform, sizeof(float)*6);
    ex = state->scissor.extent[0];
    ey = state->scissor.extent[1];
    nvgTransformInverse(invxorm, state->xform);
    nvgTransformMultiply(pxform, invxorm);
    tex = ex*nvg__absf(pxform[0]) + ey*nvg__absf(pxform[2]);
    tey = ex*nvg__absf(pxform[1]) + ey*nvg__absf(pxform[3]);

    // Intersect rects.
    nvg__isectRects(rect, pxform[4]-tex,pxform[5]-tey,tex*2,tey*2, x,y,w,h);

    nvgScissor(ctx, rect[0], rect[1], rect[2], rect[3]);
}

// Reset and disables scissoring.
void nvgResetScissor(NVGcontext* ctx)
{
    NVGstate* state = nvg__getState(ctx);
    memset(state->scissor.xform, 0, sizeof(state->scissor.xform));
    state->scissor.extent[0] = -1.0f;
    state->scissor.extent[1] = -1.0f;
}

static int nvg__ptEquals(float x1, float y1, float x2, float y2, float tol)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return dx*dx + dy*dy < tol*tol;
}

static float nvg__distPtSeg(float x, float y, float px, float py, float qx, float qy)
{
    float pqx, pqy, dx, dy, d, t;
    pqx = qx-px;
    pqy = qy-py;
    dx = x-px;
    dy = y-py;
    d = pqx*pqx + pqy*pqy;
    t = pqx*dx + pqy*dy;
    if (d > 0) t /= d;
    if (t < 0) t = 0;
    else if (t > 1) t = 1;
    dx = px + t*pqx - x;
    dy = py + t*pqy - y;
    return dx*dx + dy*dy;
}

static void nvg__appendCommands(NVGcontext* ctx, float* vals, int nvals)
{
    NVGstate* state = nvg__getState(ctx);
    int i;

    if (ctx->ncommands+nvals > ctx->ccommands) {
        float* commands;
        int ccommands = ctx->ncommands+nvals + ctx->ccommands/2;
        commands = (float*)realloc(ctx->commands, sizeof(float)*ccommands);
        if (commands == NULL) return;
        ctx->commands = commands;
        ctx->ccommands = ccommands;
    }

    if ((int)vals[0] != NVG_CLOSE && (int)vals[0] != NVG_WINDING) {
        ctx->commandx = vals[nvals-2];
        ctx->commandy = vals[nvals-1];
    }

    // transform commands
    i = 0;
    while (i < nvals) {
        int cmd = (int)vals[i];
        switch (cmd) {
        case NVG_MOVETO:
            nvgTransformPoint(&vals[i+1],&vals[i+2], state->xform, vals[i+1],vals[i+2]);
            i += 3;
            break;
        case NVG_LINETO:
            nvgTransformPoint(&vals[i+1],&vals[i+2], state->xform, vals[i+1],vals[i+2]);
            i += 3;
            break;
        case NVG_BEZIERTO:
            nvgTransformPoint(&vals[i+1],&vals[i+2], state->xform, vals[i+1],vals[i+2]);
            nvgTransformPoint(&vals[i+3],&vals[i+4], state->xform, vals[i+3],vals[i+4]);
            nvgTransformPoint(&vals[i+5],&vals[i+6], state->xform, vals[i+5],vals[i+6]);
            i += 7;
            break;
        case NVG_CLOSE:
            i++;
            break;
        case NVG_WINDING:
            i += 2;
            break;
        default:
            i++;
        }
    }

    memcpy(&ctx->commands[ctx->ncommands], vals, nvals*sizeof(float));

    ctx->ncommands += nvals;
}


static void nvg__clearPathCache(NVGcontext* ctx)
{
    ctx->cache->npoints = 0;
    ctx->cache->npaths = 0;
}

static NVGpath* nvg__lastPath(NVGcontext* ctx)
{
    if (ctx->cache->npaths > 0)
        return &ctx->cache->paths[ctx->cache->npaths-1];
    return NULL;
}

static void nvg__addPath(NVGcontext* ctx)
{
    NVGpath* path;
    if (ctx->cache->npaths+1 > ctx->cache->cpaths) {
        NVGpath* paths;
        int cpaths = ctx->cache->npaths+1 + ctx->cache->cpaths/2;
        paths = (NVGpath*)realloc(ctx->cache->paths, sizeof(NVGpath)*cpaths);
        if (paths == NULL) return;
        ctx->cache->paths = paths;
        ctx->cache->cpaths = cpaths;
    }
    path = &ctx->cache->paths[ctx->cache->npaths];
    memset(path, 0, sizeof(*path));
    path->first = ctx->cache->npoints;
    path->winding = NVG_CCW;

    ctx->cache->npaths++;
}

static NVGpoint* nvg__lastPoint(NVGcontext* ctx)
{
    if (ctx->cache->npoints > 0)
        return &ctx->cache->points[ctx->cache->npoints-1];
    return NULL;
}

static void nvg__addPoint(NVGcontext* ctx, float x, float y, int flags)
{
    NVGpath* path = nvg__lastPath(ctx);
    NVGpoint* pt;
    if (path == NULL) return;

    if (path->count > 0 && ctx->cache->npoints > 0) {
        pt = nvg__lastPoint(ctx);
        if (nvg__ptEquals(pt->x,pt->y, x,y, ctx->distTol)) {
            pt->flags |= flags;
            return;
        }
    }

    if (ctx->cache->npoints+1 > ctx->cache->cpoints) {
        NVGpoint* points;
        int cpoints = ctx->cache->npoints+1 + ctx->cache->cpoints/2;
        points = (NVGpoint*)realloc(ctx->cache->points, sizeof(NVGpoint)*cpoints);
        if (points == NULL) return;
        ctx->cache->points = points;
        ctx->cache->cpoints = cpoints;
    }

    pt = &ctx->cache->points[ctx->cache->npoints];
    memset(pt, 0, sizeof(*pt));
    pt->x = x;
    pt->y = y;
    pt->flags = (unsigned char)flags;

    ctx->cache->npoints++;
    path->count++;
}

static void nvg__closePath(NVGcontext* ctx)
{
    NVGpath* path = nvg__lastPath(ctx);
    if (path == NULL) return;
    path->closed = 1;
}

static void nvg__pathWinding(NVGcontext* ctx, int winding)
{
    NVGpath* path = nvg__lastPath(ctx);
    if (path == NULL) return;
    path->winding = winding;
}

static float nvg__getAverageScale(float *t)
{
    float sx = sqrtf(t[0]*t[0] + t[2]*t[2]);
    float sy = sqrtf(t[1]*t[1] + t[3]*t[3]);
    return (sx + sy) * 0.5f;
}

static NVGvertex* nvg__allocTempVerts(NVGcontext* ctx, int nverts)
{
    if (nverts > ctx->cache->cverts) {
        NVGvertex* verts;
        int cverts = (nverts + 0xff) & ~0xff; // Round up to prevent allocations when things change just slightly.
        verts = (NVGvertex*)realloc(ctx->cache->verts, sizeof(NVGvertex)*cverts);
        if (verts == NULL) return NULL;
        ctx->cache->verts = verts;
        ctx->cache->cverts = cverts;
    }

    return ctx->cache->verts;
}

static float nvg__triarea2(float ax, float ay, float bx, float by, float cx, float cy)
{
    float abx = bx - ax;
    float aby = by - ay;
    float acx = cx - ax;
    float acy = cy - ay;
    return acx*aby - abx*acy;
}

static float nvg__polyArea(NVGpoint* pts, int npts)
{
    int i;
    float area = 0;
    for (i = 2; i < npts; i++) {
        NVGpoint* a = &pts[0];
        NVGpoint* b = &pts[i-1];
        NVGpoint* c = &pts[i];
        area += nvg__triarea2(a->x,a->y, b->x,b->y, c->x,c->y);
    }
    return area * 0.5f;
}

static void nvg__polyReverse(NVGpoint* pts, int npts)
{
    NVGpoint tmp;
    int i = 0, j = npts-1;
    while (i < j) {
        tmp = pts[i];
        pts[i] = pts[j];
        pts[j] = tmp;
        i++;
        j--;
    }
}


static void nvg__vset(NVGvertex* vtx, float x, float y, float u, float v)
{
    vtx->x = x;
    vtx->y = y;
    vtx->u = u;
    vtx->v = v;
}

static void nvg__tesselateBezier(NVGcontext* ctx,
                                 float x1, float y1, float x2, float y2,
                                 float x3, float y3, float x4, float y4,
                                 int level, int type)
{
    float x12,y12,x23,y23,x34,y34,x123,y123,x234,y234,x1234,y1234;
    float dx,dy,d2,d3;

    if (level > 10) return;

    x12 = (x1+x2)*0.5f;
    y12 = (y1+y2)*0.5f;
    x23 = (x2+x3)*0.5f;
    y23 = (y2+y3)*0.5f;
    x34 = (x3+x4)*0.5f;
    y34 = (y3+y4)*0.5f;
    x123 = (x12+x23)*0.5f;
    y123 = (y12+y23)*0.5f;

    dx = x4 - x1;
    dy = y4 - y1;
    d2 = nvg__absf(((x2 - x4) * dy - (y2 - y4) * dx));
    d3 = nvg__absf(((x3 - x4) * dy - (y3 - y4) * dx));

    if ((d2 + d3)*(d2 + d3) < ctx->tessTol * (dx*dx + dy*dy)) {
        nvg__addPoint(ctx, x4, y4, type);
        return;
    }

/*	if (nvg__absf(x1+x3-x2-x2) + nvg__absf(y1+y3-y2-y2) + nvg__absf(x2+x4-x3-x3) + nvg__absf(y2+y4-y3-y3) < ctx->tessTol) {
        nvg__addPoint(ctx, x4, y4, type);
        return;
    }*/

    x234 = (x23+x34)*0.5f;
    y234 = (y23+y34)*0.5f;
    x1234 = (x123+x234)*0.5f;
    y1234 = (y123+y234)*0.5f;

    nvg__tesselateBezier(ctx, x1,y1, x12,y12, x123,y123, x1234,y1234, level+1, 0);
    nvg__tesselateBezier(ctx, x1234,y1234, x234,y234, x34,y34, x4,y4, level+1, type);
}

static void nvg__flattenPaths(NVGcontext* ctx)
{
    NVGpathCache* cache = ctx->cache;
//	NVGstate* state = nvg__getState(ctx);
    NVGpoint* last;
    NVGpoint* p0;
    NVGpoint* p1;
    NVGpoint* pts;
    NVGpath* path;
    int i, j;
    float* cp1;
    float* cp2;
    float* p;
    float area;

    if (cache->npaths > 0)
        return;

    // Flatten
    i = 0;
    while (i < ctx->ncommands) {
        int cmd = (int)ctx->commands[i];
        switch (cmd) {
        case NVG_MOVETO:
            nvg__addPath(ctx);
            p = &ctx->commands[i+1];
            nvg__addPoint(ctx, p[0], p[1], NVG_PT_CORNER);
            i += 3;
            break;
        case NVG_LINETO:
            p = &ctx->commands[i+1];
            nvg__addPoint(ctx, p[0], p[1], NVG_PT_CORNER);
            i += 3;
            break;
        case NVG_BEZIERTO:
            last = nvg__lastPoint(ctx);
            if (last != NULL) {
                cp1 = &ctx->commands[i+1];
                cp2 = &ctx->commands[i+3];
                p = &ctx->commands[i+5];
                nvg__tesselateBezier(ctx, last->x,last->y, cp1[0],cp1[1], cp2[0],cp2[1], p[0],p[1], 0, NVG_PT_CORNER);
            }
            i += 7;
            break;
        case NVG_CLOSE:
            nvg__closePath(ctx);
            i++;
            break;
        case NVG_WINDING:
            nvg__pathWinding(ctx, (int)ctx->commands[i+1]);
            i += 2;
            break;
        default:
            i++;
        }
    }

    cache->bounds[0] = cache->bounds[1] = 1e6f;
    cache->bounds[2] = cache->bounds[3] = -1e6f;

    // Calculate the direction and length of line segments.
    for (j = 0; j < cache->npaths; j++) {
        path = &cache->paths[j];
        pts = &cache->points[path->first];

        // If the first and last points are the same, remove the last, mark as closed path.
        p0 = &pts[path->count-1];
        p1 = &pts[0];
        if (nvg__ptEquals(p0->x,p0->y, p1->x,p1->y, ctx->distTol)) {
            path->count--;
            p0 = &pts[path->count-1];
            path->closed = 1;
        }

        // Enforce winding.
        if (path->count > 2) {
            area = nvg__polyArea(pts, path->count);
            if (path->winding == NVG_CCW && area < 0.0f)
                nvg__polyReverse(pts, path->count);
            if (path->winding == NVG_CW && area > 0.0f)
                nvg__polyReverse(pts, path->count);
        }

        for(i = 0; i < path->count; i++) {
            // Calculate segment direction and length
            p0->dx = p1->x - p0->x;
            p0->dy = p1->y - p0->y;
            p0->len = nvg__normalize(&p0->dx, &p0->dy);
            // Update bounds
            cache->bounds[0] = nvg__minf(cache->bounds[0], p0->x);
            cache->bounds[1] = nvg__minf(cache->bounds[1], p0->y);
            cache->bounds[2] = nvg__maxf(cache->bounds[2], p0->x);
            cache->bounds[3] = nvg__maxf(cache->bounds[3], p0->y);
            // Advance
            p0 = p1++;
        }
    }
}

static int nvg__curveDivs(float r, float arc, float tol)
{
    float da = acosf(r / (r + tol)) * 2.0f;
    return nvg__maxi(2, (int)ceilf(arc / da));
}

static void nvg__chooseBevel(int bevel, NVGpoint* p0, NVGpoint* p1, float w,
                            float* x0, float* y0, float* x1, float* y1)
{
    if (bevel) {
        *x0 = p1->x + p0->dy * w;
        *y0 = p1->y - p0->dx * w;
        *x1 = p1->x + p1->dy * w;
        *y1 = p1->y - p1->dx * w;
    } else {
        *x0 = p1->x + p1->dmx * w;
        *y0 = p1->y + p1->dmy * w;
        *x1 = p1->x + p1->dmx * w;
        *y1 = p1->y + p1->dmy * w;
    }
}

static NVGvertex* nvg__roundJoin(NVGvertex* dst, NVGpoint* p0, NVGpoint* p1,
                                        float lw, float rw, float lu, float ru, int ncap, float fringe)
{
    int i, n;
    float dlx0 = p0->dy;
    float dly0 = -p0->dx;
    float dlx1 = p1->dy;
    float dly1 = -p1->dx;
    NVG_NOTUSED(fringe);

    if (p1->flags & NVG_PT_LEFT) {
        float lx0,ly0,lx1,ly1,a0,a1;
        nvg__chooseBevel(p1->flags & NVG_PR_INNERBEVEL, p0, p1, lw, &lx0,&ly0, &lx1,&ly1);
        a0 = atan2f(-dly0, -dlx0);
        a1 = atan2f(-dly1, -dlx1);
        if (a1 > a0) a1 -= NVG_PI*2;

        nvg__vset(dst, lx0, ly0, lu,1); dst++;
        nvg__vset(dst, p1->x - dlx0*rw, p1->y - dly0*rw, ru,1); dst++;

        n = nvg__clampi((int)ceilf(((a0 - a1) / NVG_PI) * ncap), 2, ncap);
        for (i = 0; i < n; i++) {
            float u = i/(float)(n-1);
            float a = a0 + u*(a1-a0);
            float rx = p1->x + cosf(a) * rw;
            float ry = p1->y + sinf(a) * rw;
            nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;
            nvg__vset(dst, rx, ry, ru,1); dst++;
        }

        nvg__vset(dst, lx1, ly1, lu,1); dst++;
        nvg__vset(dst, p1->x - dlx1*rw, p1->y - dly1*rw, ru,1); dst++;

    } else {
        float rx0,ry0,rx1,ry1,a0,a1;
        nvg__chooseBevel(p1->flags & NVG_PR_INNERBEVEL, p0, p1, -rw, &rx0,&ry0, &rx1,&ry1);
        a0 = atan2f(dly0, dlx0);
        a1 = atan2f(dly1, dlx1);
        if (a1 < a0) a1 += NVG_PI*2;

        nvg__vset(dst, p1->x + dlx0*rw, p1->y + dly0*rw, lu,1); dst++;
        nvg__vset(dst, rx0, ry0, ru,1); dst++;

        n = nvg__clampi((int)ceilf(((a1 - a0) / NVG_PI) * ncap), 2, ncap);
        for (i = 0; i < n; i++) {
            float u = i/(float)(n-1);
            float a = a0 + u*(a1-a0);
            float lx = p1->x + cosf(a) * lw;
            float ly = p1->y + sinf(a) * lw;
            nvg__vset(dst, lx, ly, lu,1); dst++;
            nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;
        }

        nvg__vset(dst, p1->x + dlx1*rw, p1->y + dly1*rw, lu,1); dst++;
        nvg__vset(dst, rx1, ry1, ru,1); dst++;

    }
    return dst;
}

static NVGvertex* nvg__bevelJoin(NVGvertex* dst, NVGpoint* p0, NVGpoint* p1,
                                        float lw, float rw, float lu, float ru, float fringe)
{
    float rx0,ry0,rx1,ry1;
    float lx0,ly0,lx1,ly1;
    float dlx0 = p0->dy;
    float dly0 = -p0->dx;
    float dlx1 = p1->dy;
    float dly1 = -p1->dx;
    NVG_NOTUSED(fringe);

    if (p1->flags & NVG_PT_LEFT) {
        nvg__chooseBevel(p1->flags & NVG_PR_INNERBEVEL, p0, p1, lw, &lx0,&ly0, &lx1,&ly1);

        nvg__vset(dst, lx0, ly0, lu,1); dst++;
        nvg__vset(dst, p1->x - dlx0*rw, p1->y - dly0*rw, ru,1); dst++;

        if (p1->flags & NVG_PT_BEVEL) {
            nvg__vset(dst, lx0, ly0, lu,1); dst++;
            nvg__vset(dst, p1->x - dlx0*rw, p1->y - dly0*rw, ru,1); dst++;

            nvg__vset(dst, lx1, ly1, lu,1); dst++;
            nvg__vset(dst, p1->x - dlx1*rw, p1->y - dly1*rw, ru,1); dst++;
        } else {
            rx0 = p1->x - p1->dmx * rw;
            ry0 = p1->y - p1->dmy * rw;

            nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;
            nvg__vset(dst, p1->x - dlx0*rw, p1->y - dly0*rw, ru,1); dst++;

            nvg__vset(dst, rx0, ry0, ru,1); dst++;
            nvg__vset(dst, rx0, ry0, ru,1); dst++;

            nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;
            nvg__vset(dst, p1->x - dlx1*rw, p1->y - dly1*rw, ru,1); dst++;
        }

        nvg__vset(dst, lx1, ly1, lu,1); dst++;
        nvg__vset(dst, p1->x - dlx1*rw, p1->y - dly1*rw, ru,1); dst++;

    } else {
        nvg__chooseBevel(p1->flags & NVG_PR_INNERBEVEL, p0, p1, -rw, &rx0,&ry0, &rx1,&ry1);

        nvg__vset(dst, p1->x + dlx0*lw, p1->y + dly0*lw, lu,1); dst++;
        nvg__vset(dst, rx0, ry0, ru,1); dst++;

        if (p1->flags & NVG_PT_BEVEL) {
            nvg__vset(dst, p1->x + dlx0*lw, p1->y + dly0*lw, lu,1); dst++;
            nvg__vset(dst, rx0, ry0, ru,1); dst++;

            nvg__vset(dst, p1->x + dlx1*lw, p1->y + dly1*lw, lu,1); dst++;
            nvg__vset(dst, rx1, ry1, ru,1); dst++;
        } else {
            lx0 = p1->x + p1->dmx * lw;
            ly0 = p1->y + p1->dmy * lw;

            nvg__vset(dst, p1->x + dlx0*lw, p1->y + dly0*lw, lu,1); dst++;
            nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;

            nvg__vset(dst, lx0, ly0, lu,1); dst++;
            nvg__vset(dst, lx0, ly0, lu,1); dst++;

            nvg__vset(dst, p1->x + dlx1*lw, p1->y + dly1*lw, lu,1); dst++;
            nvg__vset(dst, p1->x, p1->y, 0.5f,1); dst++;
        }

        nvg__vset(dst, p1->x + dlx1*lw, p1->y + dly1*lw, lu,1); dst++;
        nvg__vset(dst, rx1, ry1, ru,1); dst++;
    }

    return dst;
}

static NVGvertex* nvg__buttCapStart(NVGvertex* dst, NVGpoint* p,
                                           float dx, float dy, float w, float d, float aa)
{
    float px = p->x - dx*d;
    float py = p->y - dy*d;
    float dlx = dy;
    float dly = -dx;
    nvg__vset(dst, px + dlx*w - dx*aa, py + dly*w - dy*aa, 0,0); dst++;
    nvg__vset(dst, px - dlx*w - dx*aa, py - dly*w - dy*aa, 1,0); dst++;
    nvg__vset(dst, px + dlx*w, py + dly*w, 0,1); dst++;
    nvg__vset(dst, px - dlx*w, py - dly*w, 1,1); dst++;
    return dst;
}

static NVGvertex* nvg__buttCapEnd(NVGvertex* dst, NVGpoint* p,
                                           float dx, float dy, float w, float d, float aa)
{
    float px = p->x + dx*d;
    float py = p->y + dy*d;
    float dlx = dy;
    float dly = -dx;
    nvg__vset(dst, px + dlx*w, py + dly*w, 0,1); dst++;
    nvg__vset(dst, px - dlx*w, py - dly*w, 1,1); dst++;
    nvg__vset(dst, px + dlx*w + dx*aa, py + dly*w + dy*aa, 0,0); dst++;
    nvg__vset(dst, px - dlx*w + dx*aa, py - dly*w + dy*aa, 1,0); dst++;
    return dst;
}


static NVGvertex* nvg__roundCapStart(NVGvertex* dst, NVGpoint* p,
                                            float dx, float dy, float w, int ncap, float aa)
{
    int i;
    float px = p->x;
    float py = p->y;
    float dlx = dy;
    float dly = -dx;
    NVG_NOTUSED(aa);
    for (i = 0; i < ncap; i++) {
        float a = i/(float)(ncap-1)*NVG_PI;
        float ax = cosf(a) * w, ay = sinf(a) * w;
        nvg__vset(dst, px - dlx*ax - dx*ay, py - dly*ax - dy*ay, 0,1); dst++;
        nvg__vset(dst, px, py, 0.5f,1); dst++;
    }
    nvg__vset(dst, px + dlx*w, py + dly*w, 0,1); dst++;
    nvg__vset(dst, px - dlx*w, py - dly*w, 1,1); dst++;
    return dst;
}

static NVGvertex* nvg__roundCapEnd(NVGvertex* dst, NVGpoint* p,
                                          float dx, float dy, float w, int ncap, float aa)
{
    int i;
    float px = p->x;
    float py = p->y;
    float dlx = dy;
    float dly = -dx;
    NVG_NOTUSED(aa);
    nvg__vset(dst, px + dlx*w, py + dly*w, 0,1); dst++;
    nvg__vset(dst, px - dlx*w, py - dly*w, 1,1); dst++;
    for (i = 0; i < ncap; i++) {
        float a = i/(float)(ncap-1)*NVG_PI;
        float ax = cosf(a) * w, ay = sinf(a) * w;
        nvg__vset(dst, px, py, 0.5f,1); dst++;
        nvg__vset(dst, px - dlx*ax + dx*ay, py - dly*ax + dy*ay, 0,1); dst++;
    }
    return dst;
}


static void nvg__calculateJoins(NVGcontext* ctx, float w, int lineJoin, float miterLimit)
{
    NVGpathCache* cache = ctx->cache;
    int i, j;
    float iw = 0.0f;

    if (w > 0.0f) iw = 1.0f / w;

    // Calculate which joins needs extra vertices to append, and gather vertex count.
    for (i = 0; i < cache->npaths; i++) {
        NVGpath* path = &cache->paths[i];
        NVGpoint* pts = &cache->points[path->first];
        NVGpoint* p0 = &pts[path->count-1];
        NVGpoint* p1 = &pts[0];
        int nleft = 0;

        path->nbevel = 0;

        for (j = 0; j < path->count; j++) {
            float dlx0, dly0, dlx1, dly1, dmr2, cross, limit;
            dlx0 = p0->dy;
            dly0 = -p0->dx;
            dlx1 = p1->dy;
            dly1 = -p1->dx;
            // Calculate extrusions
            p1->dmx = (dlx0 + dlx1) * 0.5f;
            p1->dmy = (dly0 + dly1) * 0.5f;
            dmr2 = p1->dmx*p1->dmx + p1->dmy*p1->dmy;
            if (dmr2 > 0.000001f) {
                float scale = 1.0f / dmr2;
                if (scale > 600.0f) {
                    scale = 600.0f;
                }
                p1->dmx *= scale;
                p1->dmy *= scale;
            }

            // Clear flags, but keep the corner.
            p1->flags = (p1->flags & NVG_PT_CORNER) ? NVG_PT_CORNER : 0;

            // Keep track of left turns.
            cross = p1->dx * p0->dy - p0->dx * p1->dy;
            if (cross > 0.0f) {
                nleft++;
                p1->flags |= NVG_PT_LEFT;
            }

            // Calculate if we should use bevel or miter for inner join.
            limit = nvg__maxf(1.01f, nvg__minf(p0->len, p1->len) * iw);
            if ((dmr2 * limit*limit) < 1.0f)
                p1->flags |= NVG_PR_INNERBEVEL;

            // Check to see if the corner needs to be beveled.
            if (p1->flags & NVG_PT_CORNER) {
                if ((dmr2 * miterLimit*miterLimit) < 1.0f || lineJoin == NVG_BEVEL || lineJoin == NVG_ROUND) {
                    p1->flags |= NVG_PT_BEVEL;
                }
            }

            if ((p1->flags & (NVG_PT_BEVEL | NVG_PR_INNERBEVEL)) != 0)
                path->nbevel++;

            p0 = p1++;
        }

        path->convex = (nleft == path->count) ? 1 : 0;
    }
}


static int nvg__expandStroke(NVGcontext* ctx, float w, int lineCap, int lineJoin, float miterLimit)
{
    NVGpathCache* cache = ctx->cache;
    NVGvertex* verts;
    NVGvertex* dst;
    int cverts, i, j;
    float aa = ctx->fringeWidth;
    int ncap = nvg__curveDivs(w, NVG_PI, ctx->tessTol);	// Calculate divisions per half circle.

    nvg__calculateJoins(ctx, w, lineJoin, miterLimit);

    // Calculate max vertex usage.
    cverts = 0;
    for (i = 0; i < cache->npaths; i++) {
        NVGpath* path = &cache->paths[i];
        int loop = (path->closed == 0) ? 0 : 1;
        if (lineJoin == NVG_ROUND)
            cverts += (path->count + path->nbevel*(ncap+2) + 1) * 2; // plus one for loop
        else
            cverts += (path->count + path->nbevel*5 + 1) * 2; // plus one for loop
        if (loop == 0) {
            // space for caps
            if (lineCap == NVG_ROUND) {
                cverts += (ncap*2 + 2)*2;
            } else {
                cverts += (3+3)*2;
            }
        }
    }

    verts = nvg__allocTempVerts(ctx, cverts);
    if (verts == NULL) return 0;

    for (i = 0; i < cache->npaths; i++) {
        NVGpath* path = &cache->paths[i];
        NVGpoint* pts = &cache->points[path->first];
        NVGpoint* p0;
        NVGpoint* p1;
        int s, e, loop;
        float dx, dy;

        path->fill = 0;
        path->nfill = 0;

        // Calculate fringe or stroke
        loop = (path->closed == 0) ? 0 : 1;
        dst = verts;
        path->stroke = dst;

        if (loop) {
            // Looping
            p0 = &pts[path->count-1];
            p1 = &pts[0];
            s = 0;
            e = path->count;
        } else {
            // Add cap
            p0 = &pts[0];
            p1 = &pts[1];
            s = 1;
            e = path->count-1;
        }

        if (loop == 0) {
            // Add cap
            dx = p1->x - p0->x;
            dy = p1->y - p0->y;
            nvg__normalize(&dx, &dy);
            if (lineCap == NVG_BUTT)
                dst = nvg__buttCapStart(dst, p0, dx, dy, w, -aa*0.5f, aa);
            else if (lineCap == NVG_BUTT || lineCap == NVG_SQUARE)
                dst = nvg__buttCapStart(dst, p0, dx, dy, w, w-aa, aa);
            else if (lineCap == NVG_ROUND)
                dst = nvg__roundCapStart(dst, p0, dx, dy, w, ncap, aa);
        }

        for (j = s; j < e; ++j) {
            if ((p1->flags & (NVG_PT_BEVEL | NVG_PR_INNERBEVEL)) != 0) {
                if (lineJoin == NVG_ROUND) {
                    dst = nvg__roundJoin(dst, p0, p1, w, w, 0, 1, ncap, aa);
                } else {
                    dst = nvg__bevelJoin(dst, p0, p1, w, w, 0, 1, aa);
                }
            } else {
                nvg__vset(dst, p1->x + (p1->dmx * w), p1->y + (p1->dmy * w), 0,1); dst++;
                nvg__vset(dst, p1->x - (p1->dmx * w), p1->y - (p1->dmy * w), 1,1); dst++;
            }
            p0 = p1++;
        }

        if (loop) {
            // Loop it
            nvg__vset(dst, verts[0].x, verts[0].y, 0,1); dst++;
            nvg__vset(dst, verts[1].x, verts[1].y, 1,1); dst++;
        } else {
            // Add cap
            dx = p1->x - p0->x;
            dy = p1->y - p0->y;
            nvg__normalize(&dx, &dy);
            if (lineCap == NVG_BUTT)
                dst = nvg__buttCapEnd(dst, p1, dx, dy, w, -aa*0.5f, aa);
            else if (lineCap == NVG_BUTT || lineCap == NVG_SQUARE)
                dst = nvg__buttCapEnd(dst, p1, dx, dy, w, w-aa, aa);
            else if (lineCap == NVG_ROUND)
                dst = nvg__roundCapEnd(dst, p1, dx, dy, w, ncap, aa);
        }

        path->nstroke = (int)(dst - verts);

        verts = dst;
    }

    return 1;
}

static int nvg__expandFill(NVGcontext* ctx, float w, int lineJoin, float miterLimit)
{
    NVGpathCache* cache = ctx->cache;
    NVGvertex* verts;
    NVGvertex* dst;
    int cverts, convex, i, j;
    float aa = ctx->fringeWidth;
    int fringe = w > 0.0f;

    nvg__calculateJoins(ctx, w, lineJoin, miterLimit);

    // Calculate max vertex usage.
    cverts = 0;
    for (i = 0; i < cache->npaths; i++) {
        NVGpath* path = &cache->paths[i];
        cverts += path->count + path->nbevel + 1;
        if (fringe)
            cverts += (path->count + path->nbevel*5 + 1) * 2; // plus one for loop
    }

    verts = nvg__allocTempVerts(ctx, cverts);
    if (verts == NULL) return 0;

    convex = cache->npaths == 1 && cache->paths[0].convex;

    for (i = 0; i < cache->npaths; i++) {
        NVGpath* path = &cache->paths[i];
        NVGpoint* pts = &cache->points[path->first];
        NVGpoint* p0;
        NVGpoint* p1;
        float rw, lw, woff;
        float ru, lu;

        // Calculate shape vertices.
        woff = 0.5f*aa;
        dst = verts;
        path->fill = dst;

        if (fringe) {
            // Looping
            p0 = &pts[path->count-1];
            p1 = &pts[0];
            for (j = 0; j < path->count; ++j) {
                if (p1->flags & NVG_PT_BEVEL) {
                    float dlx0 = p0->dy;
                    float dly0 = -p0->dx;
                    float dlx1 = p1->dy;
                    float dly1 = -p1->dx;
                    if (p1->flags & NVG_PT_LEFT) {
                        float lx = p1->x + p1->dmx * woff;
                        float ly = p1->y + p1->dmy * woff;
                        nvg__vset(dst, lx, ly, 0.5f,1); dst++;
                    } else {
                        float lx0 = p1->x + dlx0 * woff;
                        float ly0 = p1->y + dly0 * woff;
                        float lx1 = p1->x + dlx1 * woff;
                        float ly1 = p1->y + dly1 * woff;
                        nvg__vset(dst, lx0, ly0, 0.5f,1); dst++;
                        nvg__vset(dst, lx1, ly1, 0.5f,1); dst++;
                    }
                } else {
                    nvg__vset(dst, p1->x + (p1->dmx * woff), p1->y + (p1->dmy * woff), 0.5f,1); dst++;
                }
                p0 = p1++;
            }
        } else {
            for (j = 0; j < path->count; ++j) {
                nvg__vset(dst, pts[j].x, pts[j].y, 0.5f,1);
                dst++;
            }
        }

        path->nfill = (int)(dst - verts);
        verts = dst;

        // Calculate fringe
        if (fringe) {
            lw = w + woff;
            rw = w - woff;
            lu = 0;
            ru = 1;
            dst = verts;
            path->stroke = dst;

            // Create only half a fringe for convex shapes so that
            // the shape can be rendered without stenciling.
            if (convex) {
                lw = woff;	// This should generate the same vertex as fill inset above.
                lu = 0.5f;	// Set outline fade at middle.
            }

            // Looping
            p0 = &pts[path->count-1];
            p1 = &pts[0];

            for (j = 0; j < path->count; ++j) {
                if ((p1->flags & (NVG_PT_BEVEL | NVG_PR_INNERBEVEL)) != 0) {
                    dst = nvg__bevelJoin(dst, p0, p1, lw, rw, lu, ru, ctx->fringeWidth);
                } else {
                    nvg__vset(dst, p1->x + (p1->dmx * lw), p1->y + (p1->dmy * lw), lu,1); dst++;
                    nvg__vset(dst, p1->x - (p1->dmx * rw), p1->y - (p1->dmy * rw), ru,1); dst++;
                }
                p0 = p1++;
            }

            // Loop it
            nvg__vset(dst, verts[0].x, verts[0].y, lu,1); dst++;
            nvg__vset(dst, verts[1].x, verts[1].y, ru,1); dst++;

            path->nstroke = (int)(dst - verts);
            verts = dst;
        } else {
            path->stroke = NULL;
            path->nstroke = 0;
        }
    }

    return 1;
}

// Clears the current path and sub-paths.
void nvgBeginPath(NVGcontext* ctx)
{
    ctx->ncommands = 0;
    nvg__clearPathCache(ctx);
}

// Starts new sub-path with specified point as first point.
void nvgMoveTo(NVGcontext* ctx, float x, float y)
{
    float vals[] = { NVG_MOVETO, x, y };
    nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

// Adds line segment from the last point in the path to the specified point.
void nvgLineTo(NVGcontext* ctx, float x, float y)
{
    float vals[] = { NVG_LINETO, x, y };
    nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

// Adds cubic bezier segment from last point in the path via two control points to the specified point.
void nvgBezierTo(NVGcontext* ctx, float c1x, float c1y, float c2x, float c2y, float x, float y)
{
    float vals[] = { NVG_BEZIERTO, c1x, c1y, c2x, c2y, x, y };
    nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

// Adds quadratic bezier segment from last point in the path via a control point to the specified point.
void nvgQuadTo(NVGcontext* ctx, float cx, float cy, float x, float y)
{
    float x0 = ctx->commandx;
    float y0 = ctx->commandy;
    float vals[] = { NVG_BEZIERTO,
        x0 + 2.0f/3.0f*(cx - x0), y0 + 2.0f/3.0f*(cy - y0),
        x + 2.0f/3.0f*(cx - x), y + 2.0f/3.0f*(cy - y),
        x, y };
    nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

// Adds an arc segment at the corner defined by the last path point, and two specified points.
void nvgArcTo(NVGcontext* ctx, float x1, float y1, float x2, float y2, float radius)
{
    float x0 = ctx->commandx;
    float y0 = ctx->commandy;
    float dx0,dy0, dx1,dy1, a, d, cx,cy, a0,a1;
    int dir;

    if (ctx->ncommands == 0) {
        return;
    }

    // Handle degenerate cases.
    if (nvg__ptEquals(x0,y0, x1,y1, ctx->distTol) ||
        nvg__ptEquals(x1,y1, x2,y2, ctx->distTol) ||
        nvg__distPtSeg(x1,y1, x0,y0, x2,y2) < ctx->distTol*ctx->distTol ||
        radius < ctx->distTol) {
        nvgLineTo(ctx, x1,y1);
        return;
    }

    // Calculate tangential circle to lines (x0,y0)-(x1,y1) and (x1,y1)-(x2,y2).
    dx0 = x0-x1;
    dy0 = y0-y1;
    dx1 = x2-x1;
    dy1 = y2-y1;
    nvg__normalize(&dx0,&dy0);
    nvg__normalize(&dx1,&dy1);
    a = nvg__acosf(dx0*dx1 + dy0*dy1);
    d = radius / nvg__tanf(a/2.0f);

//	printf("a=%f° d=%f\n", a/NVG_PI*180.0f, d);

    if (d > 10000.0f) {
        nvgLineTo(ctx, x1,y1);
        return;
    }

    if (nvg__cross(dx0,dy0, dx1,dy1) > 0.0f) {
        cx = x1 + dx0*d + dy0*radius;
        cy = y1 + dy0*d + -dx0*radius;
        a0 = nvg__atan2f(dx0, -dy0);
        a1 = nvg__atan2f(-dx1, dy1);
        dir = NVG_CW;
//		printf("CW c=(%f, %f) a0=%f° a1=%f°\n", cx, cy, a0/NVG_PI*180.0f, a1/NVG_PI*180.0f);
    } else {
        cx = x1 + dx0*d + -dy0*radius;
        cy = y1 + dy0*d + dx0*radius;
        a0 = nvg__atan2f(-dx0, dy0);
        a1 = nvg__atan2f(dx1, -dy1);
        dir = NVG_CCW;
//		printf("CCW c=(%f, %f) a0=%f° a1=%f°\n", cx, cy, a0/NVG_PI*180.0f, a1/NVG_PI*180.0f);
    }

    nvgArc(ctx, cx, cy, radius, a0, a1, dir);
}

// Closes current sub-path with a line segment.
void nvgClosePath(NVGcontext* ctx)
{
    float vals[] = { NVG_CLOSE };
    nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

// Sets the current sub-path winding, see NVGwinding and NVGsolidity.
void nvgPathWinding(NVGcontext* ctx, int dir)
{
    float vals[] = { NVG_WINDING, (float)dir };
    nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

// Creates new circle arc shaped sub-path. The arc center is at cx,cy, the arc radius is r,
// and the arc is drawn from angle a0 to a1, and swept in direction dir (NVG_CCW, or NVG_CW).
// Angles are specified in radians.
void nvgArc(NVGcontext* ctx, float cx, float cy, float r, float a0, float a1, int dir)
{
    float a = 0, da = 0, hda = 0, kappa = 0;
    float dx = 0, dy = 0, x = 0, y = 0, tanx = 0, tany = 0;
    float px = 0, py = 0, ptanx = 0, ptany = 0;
    float vals[3 + 5*7 + 100];
    int i, ndivs, nvals;
    int move = ctx->ncommands > 0 ? NVG_LINETO : NVG_MOVETO;

    // Clamp angles
    da = a1 - a0;
    if (dir == NVG_CW) {
        if (nvg__absf(da) >= NVG_PI*2) {
            da = NVG_PI*2;
        } else {
            while (da < 0.0f) da += NVG_PI*2;
        }
    } else {
        if (nvg__absf(da) >= NVG_PI*2) {
            da = -NVG_PI*2;
        } else {
            while (da > 0.0f) da -= NVG_PI*2;
        }
    }

    // Split arc into max 90 degree segments.
    ndivs = nvg__maxi(1, nvg__mini((int)(nvg__absf(da) / (NVG_PI*0.5f) + 0.5f), 5));
    hda = (da / (float)ndivs) / 2.0f;
    kappa = nvg__absf(4.0f / 3.0f * (1.0f - nvg__cosf(hda)) / nvg__sinf(hda));

    if (dir == NVG_CCW)
        kappa = -kappa;

    nvals = 0;
    for (i = 0; i <= ndivs; i++) {
        a = a0 + da * (i/(float)ndivs);
        dx = nvg__cosf(a);
        dy = nvg__sinf(a);
        x = cx + dx*r;
        y = cy + dy*r;
        tanx = -dy*r*kappa;
        tany = dx*r*kappa;

        if (i == 0) {
            vals[nvals++] = (float)move;
            vals[nvals++] = x;
            vals[nvals++] = y;
        } else {
            vals[nvals++] = NVG_BEZIERTO;
            vals[nvals++] = px+ptanx;
            vals[nvals++] = py+ptany;
            vals[nvals++] = x-tanx;
            vals[nvals++] = y-tany;
            vals[nvals++] = x;
            vals[nvals++] = y;
        }
        px = x;
        py = y;
        ptanx = tanx;
        ptany = tany;
    }

    nvg__appendCommands(ctx, vals, nvals);
}

// Creates new rectangle shaped sub-path.
void nvgRect(NVGcontext* ctx, float x, float y, float w, float h)
{
    float vals[] = {
        NVG_MOVETO, x,y,
        NVG_LINETO, x,y+h,
        NVG_LINETO, x+w,y+h,
        NVG_LINETO, x+w,y,
        NVG_CLOSE
    };
    nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

// Creates new rounded rectangle shaped sub-path.
void nvgRoundedRect(NVGcontext* ctx, float x, float y, float w, float h, float r)
{
    if (r < 0.1f) {
        nvgRect(ctx, x,y,w,h);
        return;
    }
    else {
        float rx = nvg__minf(r, nvg__absf(w)*0.5f) * nvg__signf(w), ry = nvg__minf(r, nvg__absf(h)*0.5f) * nvg__signf(h);
        float vals[] = {
            NVG_MOVETO, x, y+ry,
            NVG_LINETO, x, y+h-ry,
            NVG_BEZIERTO, x, y+h-ry*(1-NVG_KAPPA90), x+rx*(1-NVG_KAPPA90), y+h, x+rx, y+h,
            NVG_LINETO, x+w-rx, y+h,
            NVG_BEZIERTO, x+w-rx*(1-NVG_KAPPA90), y+h, x+w, y+h-ry*(1-NVG_KAPPA90), x+w, y+h-ry,
            NVG_LINETO, x+w, y+ry,
            NVG_BEZIERTO, x+w, y+ry*(1-NVG_KAPPA90), x+w-rx*(1-NVG_KAPPA90), y, x+w-rx, y,
            NVG_LINETO, x+rx, y,
            NVG_BEZIERTO, x+rx*(1-NVG_KAPPA90), y, x, y+ry*(1-NVG_KAPPA90), x, y+ry,
            NVG_CLOSE
        };
        nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
    }
}

// Creates new ellipse shaped sub-path.
void nvgEllipse(NVGcontext* ctx, float cx, float cy, float rx, float ry)
{
    float vals[] = {
        NVG_MOVETO, cx-rx, cy,
        NVG_BEZIERTO, cx-rx, cy+ry*NVG_KAPPA90, cx-rx*NVG_KAPPA90, cy+ry, cx, cy+ry,
        NVG_BEZIERTO, cx+rx*NVG_KAPPA90, cy+ry, cx+rx, cy+ry*NVG_KAPPA90, cx+rx, cy,
        NVG_BEZIERTO, cx+rx, cy-ry*NVG_KAPPA90, cx+rx*NVG_KAPPA90, cy-ry, cx, cy-ry,
        NVG_BEZIERTO, cx-rx*NVG_KAPPA90, cy-ry, cx-rx, cy-ry*NVG_KAPPA90, cx-rx, cy,
        NVG_CLOSE
    };
    nvg__appendCommands(ctx, vals, NVG_COUNTOF(vals));
}

// Creates new circle shaped sub-path.
void nvgCircle(NVGcontext* ctx, float cx, float cy, float r)
{
    nvgEllipse(ctx, cx,cy, r,r);
}

void nvgDebugDumpPathCache(NVGcontext* ctx)
{
    const NVGpath* path;
    int i, j;

    printf("Dumping %d cached paths\n", ctx->cache->npaths);
    for (i = 0; i < ctx->cache->npaths; i++) {
        path = &ctx->cache->paths[i];
        printf(" - Path %d\n", i);
        if (path->nfill) {
            printf("   - fill: %d\n", path->nfill);
            for (j = 0; j < path->nfill; j++)
                printf("%f\t%f\n", path->fill[j].x, path->fill[j].y);
        }
        if (path->nstroke) {
            printf("   - stroke: %d\n", path->nstroke);
            for (j = 0; j < path->nstroke; j++)
                printf("%f\t%f\n", path->stroke[j].x, path->stroke[j].y);
        }
    }
}

// Fills the current path with current fill style.
void nvgFill(NVGcontext* ctx)
{
    NVGstate* state = nvg__getState(ctx);
    const NVGpath* path;
    NVGpaint fillPaint = state->fill;
    int i;

    nvg__flattenPaths(ctx);
    if (ctx->params.edgeAntiAlias)
        nvg__expandFill(ctx, ctx->fringeWidth, NVG_MITER, 2.4f);
    else
        nvg__expandFill(ctx, 0.0f, NVG_MITER, 2.4f);

    // Apply global alpha
    fillPaint.innerColor.a *= state->alpha;
    fillPaint.outerColor.a *= state->alpha;

    ctx->params.renderFill(ctx->params.userPtr, &fillPaint, &state->scissor, ctx->fringeWidth,
                           ctx->cache->bounds, ctx->cache->paths, ctx->cache->npaths);

    // Count triangles
    for (i = 0; i < ctx->cache->npaths; i++) {
        path = &ctx->cache->paths[i];
        ctx->fillTriCount += path->nfill-2;
        ctx->fillTriCount += path->nstroke-2;
        ctx->drawCallCount += 2;
    }
}

// Fills the current path with current stroke style.
void nvgStroke(NVGcontext* ctx)
{
    NVGstate* state = nvg__getState(ctx);
    float scale = nvg__getAverageScale(state->xform);
    float strokeWidth = nvg__clampf(state->strokeWidth * scale, 0.0f, 200.0f);
    NVGpaint strokePaint = state->stroke;
    const NVGpath* path;
    int i;

    if (strokeWidth < ctx->fringeWidth) {
        // If the stroke width is less than pixel size, use alpha to emulate coverage.
        // Since coverage is area, scale by alpha*alpha.
        float alpha = nvg__clampf(strokeWidth / ctx->fringeWidth, 0.0f, 1.0f);
        strokePaint.innerColor.a *= alpha*alpha;
        strokePaint.outerColor.a *= alpha*alpha;
        strokeWidth = ctx->fringeWidth;
    }

    // Apply global alpha
    strokePaint.innerColor.a *= state->alpha;
    strokePaint.outerColor.a *= state->alpha;

    nvg__flattenPaths(ctx);

    if (ctx->params.edgeAntiAlias)
        nvg__expandStroke(ctx, strokeWidth*0.5f + ctx->fringeWidth*0.5f, state->lineCap, state->lineJoin, state->miterLimit);
    else
        nvg__expandStroke(ctx, strokeWidth*0.5f, state->lineCap, state->lineJoin, state->miterLimit);

    ctx->params.renderStroke(ctx->params.userPtr, &strokePaint, &state->scissor, ctx->fringeWidth,
                             strokeWidth, ctx->cache->paths, ctx->cache->npaths);

    // Count triangles
    for (i = 0; i < ctx->cache->npaths; i++) {
        path = &ctx->cache->paths[i];
        ctx->strokeTriCount += path->nstroke-2;
        ctx->drawCallCount++;
    }
}

// Add fonts
// Creates font by loading it from the disk from specified file name.
// Returns handle to the font.
int nvgCreateFont(NVGcontext* ctx, const char* name, const char* path)
{
    return fonsAddFont(ctx->fs, name, path);
}

// Creates image by loading it from the specified memory chunk.
// Returns handle to the font.
int nvgCreateFontMem(NVGcontext* ctx, const char* name, unsigned char* data, int ndata, int freeData)
{
    return fonsAddFontMem(ctx->fs, name, data, ndata, freeData);
}

// Finds a loaded font of specified name, and returns handle to it, or -1 if the font is not found.
int nvgFindFont(NVGcontext* ctx, const char* name)
{
    if (name == NULL) return -1;
    return fonsGetFontByName(ctx->fs, name);
}

// State setting
// Sets the font size of current text style.
void nvgFontSize(NVGcontext* ctx, float size)
{
    NVGstate* state = nvg__getState(ctx);
    state->fontSize = size;
}

// Sets the blur of current text style.
void nvgFontBlur(NVGcontext* ctx, float blur)
{
    NVGstate* state = nvg__getState(ctx);
    state->fontBlur = blur;
}

// Sets the letter spacing of current text style.
void nvgTextLetterSpacing(NVGcontext* ctx, float spacing)
{
    NVGstate* state = nvg__getState(ctx);
    state->letterSpacing = spacing;
}

// Sets the proportional line height of current text style. The line height is specified as multiple of font size.
void nvgTextLineHeight(NVGcontext* ctx, float lineHeight)
{
    NVGstate* state = nvg__getState(ctx);
    state->lineHeight = lineHeight;
}

// Sets the text align of current text style, see NVGalign for options.
void nvgTextAlign(NVGcontext* ctx, int align)
{
    NVGstate* state = nvg__getState(ctx);
    state->textAlign = align;
}

// Sets the font face based on specified id of current text style.
void nvgFontFaceId(NVGcontext* ctx, int font)
{
    NVGstate* state = nvg__getState(ctx);
    state->fontId = font;
}

// Sets the font face based on specified name of current text style.
void nvgFontFace(NVGcontext* ctx, const char* font)
{
    NVGstate* state = nvg__getState(ctx);
    state->fontId = fonsGetFontByName(ctx->fs, font);
}

static float nvg__quantize(float a, float d)
{
    return ((int)(a / d + 0.5f)) * d;
}

static float nvg__getFontScale(NVGstate* state)
{
    return nvg__minf(nvg__quantize(nvg__getAverageScale(state->xform), 0.01f), 4.0f);
}

static void nvg__flushTextTexture(NVGcontext* ctx)
{
    int dirty[4];

    if (fonsValidateTexture(ctx->fs, dirty)) {
        int fontImage = ctx->fontImages[ctx->fontImageIdx];
        // Update texture
        if (fontImage != 0) {
            int iw, ih;
            const unsigned char* data = fonsGetTextureData(ctx->fs, &iw, &ih);
            int x = dirty[0];
            int y = dirty[1];
            int w = dirty[2] - dirty[0];
            int h = dirty[3] - dirty[1];
            ctx->params.renderUpdateTexture(ctx->params.userPtr, fontImage, x,y, w,h, data);
        }
    }
}

static int nvg__allocTextAtlas(NVGcontext* ctx)
{
    int iw, ih;
    nvg__flushTextTexture(ctx);
    if (ctx->fontImageIdx >= NVG_MAX_FONTIMAGES-1)
        return 0;
    // if next fontImage already have a texture
    if (ctx->fontImages[ctx->fontImageIdx+1] != 0)
        nvgImageSize(ctx, ctx->fontImages[ctx->fontImageIdx+1], &iw, &ih);
    else { // calculate the new font image size and create it.
        nvgImageSize(ctx, ctx->fontImages[ctx->fontImageIdx], &iw, &ih);
        if (iw > ih)
            ih *= 2;
        else
            iw *= 2;
        if (iw > NVG_MAX_FONTIMAGE_SIZE || ih > NVG_MAX_FONTIMAGE_SIZE)
            iw = ih = NVG_MAX_FONTIMAGE_SIZE;
        ctx->fontImages[ctx->fontImageIdx+1] = ctx->params.renderCreateTexture(ctx->params.userPtr, NVG_TEXTURE_ALPHA, iw, ih, 0, NULL);
    }
    ++ctx->fontImageIdx;
    fonsResetAtlas(ctx->fs, iw, ih);
    return 1;
}

static void nvg__renderText(NVGcontext* ctx, NVGvertex* verts, int nverts)
{
    NVGstate* state = nvg__getState(ctx);
    NVGpaint paint = state->fill;

    // Render triangles.
    paint.image = ctx->fontImages[ctx->fontImageIdx];

    // Apply global alpha
    paint.innerColor.a *= state->alpha;
    paint.outerColor.a *= state->alpha;

    ctx->params.renderTriangles(ctx->params.userPtr, &paint, &state->scissor, verts, nverts);

    ctx->drawCallCount++;
    ctx->textTriCount += nverts/3;
}

// Draws text string at specified location. If end is specified only the sub-string up to the end is drawn.
float nvgText(NVGcontext* ctx, float x, float y, const char* string, const char* end)
{
    NVGstate* state = nvg__getState(ctx);
    FONStextIter iter, prevIter;
    FONSquad q;
    NVGvertex* verts;
    float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
    float invscale = 1.0f / scale;
    int cverts = 0;
    int nverts = 0;

    if (end == NULL)
        end = string + strlen(string);

    if (state->fontId == FONS_INVALID) return x;

    fonsSetSize(ctx->fs, state->fontSize*scale);
    fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
    fonsSetBlur(ctx->fs, state->fontBlur*scale);
    fonsSetAlign(ctx->fs, state->textAlign);
    fonsSetFont(ctx->fs, state->fontId);

    cverts = nvg__maxi(2, (int)(end - string)) * 6; // conservative estimate.
    verts = nvg__allocTempVerts(ctx, cverts);
    if (verts == NULL) return x;

    fonsTextIterInit(ctx->fs, &iter, x*scale, y*scale, string, end);
    prevIter = iter;
    while (fonsTextIterNext(ctx->fs, &iter, &q)) {
        float c[4*2];
        if (iter.prevGlyphIndex == -1) { // can not retrieve glyph?
            if (!nvg__allocTextAtlas(ctx))
                break; // no memory :(
            if (nverts != 0) {
                nvg__renderText(ctx, verts, nverts);
                nverts = 0;
            }
            iter = prevIter;
            fonsTextIterNext(ctx->fs, &iter, &q); // try again
            if (iter.prevGlyphIndex == -1) // still can not find glyph?
                break;
        }
        prevIter = iter;
        // Transform corners.
        nvgTransformPoint(&c[0],&c[1], state->xform, q.x0*invscale, q.y0*invscale);
        nvgTransformPoint(&c[2],&c[3], state->xform, q.x1*invscale, q.y0*invscale);
        nvgTransformPoint(&c[4],&c[5], state->xform, q.x1*invscale, q.y1*invscale);
        nvgTransformPoint(&c[6],&c[7], state->xform, q.x0*invscale, q.y1*invscale);
        // Create triangles
        if (nverts+6 <= cverts) {
            nvg__vset(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
            nvg__vset(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
            nvg__vset(&verts[nverts], c[2], c[3], q.s1, q.t0); nverts++;
            nvg__vset(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
            nvg__vset(&verts[nverts], c[6], c[7], q.s0, q.t1); nverts++;
            nvg__vset(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
        }
    }

    // TODO: add back-end bit to do this just once per frame.
    nvg__flushTextTexture(ctx);

    nvg__renderText(ctx, verts, nverts);

    return iter.x;
}

// Draws multi-line text string at specified location wrapped at the specified width. If end is specified only the sub-string up to the end is drawn.
// White space is stripped at the beginning of the rows, the text is split at word boundaries or when new-line characters are encountered.
// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
void nvgTextBox(NVGcontext* ctx, float x, float y, float breakRowWidth, const char* string, const char* end)
{
    NVGstate* state = nvg__getState(ctx);
    NVGtextRow rows[2];
    int nrows = 0, i;
    int oldAlign = state->textAlign;
    int haling = state->textAlign & (NVG_ALIGN_LEFT | NVG_ALIGN_CENTER | NVG_ALIGN_RIGHT);
    int valign = state->textAlign & (NVG_ALIGN_TOP | NVG_ALIGN_MIDDLE | NVG_ALIGN_BOTTOM | NVG_ALIGN_BASELINE);
    float lineh = 0;

    if (state->fontId == FONS_INVALID) return;

    nvgTextMetrics(ctx, NULL, NULL, &lineh);

    state->textAlign = NVG_ALIGN_LEFT | valign;

    while ((nrows = nvgTextBreakLines(ctx, string, end, breakRowWidth, rows, 2))) {
        for (i = 0; i < nrows; i++) {
            NVGtextRow* row = &rows[i];
            if (haling & NVG_ALIGN_LEFT)
                nvgText(ctx, x, y, row->start, row->end);
            else if (haling & NVG_ALIGN_CENTER)
                nvgText(ctx, x + breakRowWidth*0.5f - row->width*0.5f, y, row->start, row->end);
            else if (haling & NVG_ALIGN_RIGHT)
                nvgText(ctx, x + breakRowWidth - row->width, y, row->start, row->end);
            y += lineh * state->lineHeight;
        }
        string = rows[nrows-1].next;
    }

    state->textAlign = oldAlign;
}

// Calculates the glyph x positions of the specified text. If end is specified only the sub-string will be used.
// Measured values are returned in local coordinate space.
int nvgTextGlyphPositions(NVGcontext* ctx, float x, float y, const char* string, const char* end, NVGglyphPosition* positions, int maxPositions)
{
    NVGstate* state = nvg__getState(ctx);
    float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
    float invscale = 1.0f / scale;
    FONStextIter iter, prevIter;
    FONSquad q;
    int npos = 0;

    if (state->fontId == FONS_INVALID) return 0;

    if (end == NULL)
        end = string + strlen(string);

    if (string == end)
        return 0;

    fonsSetSize(ctx->fs, state->fontSize*scale);
    fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
    fonsSetBlur(ctx->fs, state->fontBlur*scale);
    fonsSetAlign(ctx->fs, state->textAlign);
    fonsSetFont(ctx->fs, state->fontId);

    fonsTextIterInit(ctx->fs, &iter, x*scale, y*scale, string, end);
    prevIter = iter;
    while (fonsTextIterNext(ctx->fs, &iter, &q)) {
        if (iter.prevGlyphIndex < 0 && nvg__allocTextAtlas(ctx)) { // can not retrieve glyph?
            iter = prevIter;
            fonsTextIterNext(ctx->fs, &iter, &q); // try again
        }
        prevIter = iter;
        positions[npos].str = iter.str;
        positions[npos].x = iter.x * invscale;
        positions[npos].minx = nvg__minf(iter.x, q.x0) * invscale;
        positions[npos].maxx = nvg__maxf(iter.nextx, q.x1) * invscale;
        npos++;
        if (npos >= maxPositions)
            break;
    }

    return npos;
}

enum NVGcodepointType {
    NVG_SPACE,
    NVG_NEWLINE,
    NVG_CHAR,
};

// Breaks the specified text into lines. If end is specified only the sub-string will be used.
// White space is stripped at the beginning of the rows, the text is split at word boundaries or when new-line characters are encountered.
// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
int nvgTextBreakLines(NVGcontext* ctx, const char* string, const char* end, float breakRowWidth, NVGtextRow* rows, int maxRows)
{
    NVGstate* state = nvg__getState(ctx);
    float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
    float invscale = 1.0f / scale;
    FONStextIter iter, prevIter;
    FONSquad q;
    int nrows = 0;
    float rowStartX = 0;
    float rowWidth = 0;
    float rowMinX = 0;
    float rowMaxX = 0;
    const char* rowStart = NULL;
    const char* rowEnd = NULL;
    const char* wordStart = NULL;
    float wordStartX = 0;
    float wordMinX = 0;
    const char* breakEnd = NULL;
    float breakWidth = 0;
    float breakMaxX = 0;
    int type = NVG_SPACE, ptype = NVG_SPACE;
    unsigned int pcodepoint = 0;

    if (maxRows == 0) return 0;
    if (state->fontId == FONS_INVALID) return 0;

    if (end == NULL)
        end = string + strlen(string);

    if (string == end) return 0;

    fonsSetSize(ctx->fs, state->fontSize*scale);
    fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
    fonsSetBlur(ctx->fs, state->fontBlur*scale);
    fonsSetAlign(ctx->fs, state->textAlign);
    fonsSetFont(ctx->fs, state->fontId);

    breakRowWidth *= scale;

    fonsTextIterInit(ctx->fs, &iter, 0, 0, string, end);
    prevIter = iter;
    while (fonsTextIterNext(ctx->fs, &iter, &q)) {
        if (iter.prevGlyphIndex < 0 && nvg__allocTextAtlas(ctx)) { // can not retrieve glyph?
            iter = prevIter;
            fonsTextIterNext(ctx->fs, &iter, &q); // try again
        }
        prevIter = iter;
        switch (iter.codepoint) {
            case 9:			// \t
            case 11:		// \v
            case 12:		// \f
            case 32:		// space
            case 0x00a0:	// NBSP
                type = NVG_SPACE;
                break;
            case 10:		// \n
                type = pcodepoint == 13 ? NVG_SPACE : NVG_NEWLINE;
                break;
            case 13:		// \r
                type = pcodepoint == 10 ? NVG_SPACE : NVG_NEWLINE;
                break;
            case 0x0085:	// NEL
                type = NVG_NEWLINE;
                break;
            default:
                type = NVG_CHAR;
                break;
        }

        if (type == NVG_NEWLINE) {
            // Always handle new lines.
            rows[nrows].start = rowStart != NULL ? rowStart : iter.str;
            rows[nrows].end = rowEnd != NULL ? rowEnd : iter.str;
            rows[nrows].width = rowWidth * invscale;
            rows[nrows].minx = rowMinX * invscale;
            rows[nrows].maxx = rowMaxX * invscale;
            rows[nrows].next = iter.next;
            nrows++;
            if (nrows >= maxRows)
                return nrows;
            // Set null break point
            breakEnd = rowStart;
            breakWidth = 0.0;
            breakMaxX = 0.0;
            // Indicate to skip the white space at the beginning of the row.
            rowStart = NULL;
            rowEnd = NULL;
            rowWidth = 0;
            rowMinX = rowMaxX = 0;
        } else {
            if (rowStart == NULL) {
                // Skip white space until the beginning of the line
                if (type == NVG_CHAR) {
                    // The current char is the row so far
                    rowStartX = iter.x;
                    rowStart = iter.str;
                    rowEnd = iter.next;
                    rowWidth = iter.nextx - rowStartX; // q.x1 - rowStartX;
                    rowMinX = q.x0 - rowStartX;
                    rowMaxX = q.x1 - rowStartX;
                    wordStart = iter.str;
                    wordStartX = iter.x;
                    wordMinX = q.x0 - rowStartX;
                    // Set null break point
                    breakEnd = rowStart;
                    breakWidth = 0.0;
                    breakMaxX = 0.0;
                }
            } else {
                float nextWidth = iter.nextx - rowStartX;

                // track last non-white space character
                if (type == NVG_CHAR) {
                    rowEnd = iter.next;
                    rowWidth = iter.nextx - rowStartX;
                    rowMaxX = q.x1 - rowStartX;
                }
                // track last end of a word
                if (ptype == NVG_CHAR && type == NVG_SPACE) {
                    breakEnd = iter.str;
                    breakWidth = rowWidth;
                    breakMaxX = rowMaxX;
                }
                // track last beginning of a word
                if (ptype == NVG_SPACE && type == NVG_CHAR) {
                    wordStart = iter.str;
                    wordStartX = iter.x;
                    wordMinX = q.x0 - rowStartX;
                }

                // Break to new line when a character is beyond break width.
                if (type == NVG_CHAR && nextWidth > breakRowWidth) {
                    // The run length is too long, need to break to new line.
                    if (breakEnd == rowStart) {
                        // The current word is longer than the row length, just break it from here.
                        rows[nrows].start = rowStart;
                        rows[nrows].end = iter.str;
                        rows[nrows].width = rowWidth * invscale;
                        rows[nrows].minx = rowMinX * invscale;
                        rows[nrows].maxx = rowMaxX * invscale;
                        rows[nrows].next = iter.str;
                        nrows++;
                        if (nrows >= maxRows)
                            return nrows;
                        rowStartX = iter.x;
                        rowStart = iter.str;
                        rowEnd = iter.next;
                        rowWidth = iter.nextx - rowStartX;
                        rowMinX = q.x0 - rowStartX;
                        rowMaxX = q.x1 - rowStartX;
                        wordStart = iter.str;
                        wordStartX = iter.x;
                        wordMinX = q.x0 - rowStartX;
                    } else {
                        // Break the line from the end of the last word, and start new line from the beginning of the new.
                        rows[nrows].start = rowStart;
                        rows[nrows].end = breakEnd;
                        rows[nrows].width = breakWidth * invscale;
                        rows[nrows].minx = rowMinX * invscale;
                        rows[nrows].maxx = breakMaxX * invscale;
                        rows[nrows].next = wordStart;
                        nrows++;
                        if (nrows >= maxRows)
                            return nrows;
                        rowStartX = wordStartX;
                        rowStart = wordStart;
                        rowEnd = iter.next;
                        rowWidth = iter.nextx - rowStartX;
                        rowMinX = wordMinX;
                        rowMaxX = q.x1 - rowStartX;
                        // No change to the word start
                    }
                    // Set null break point
                    breakEnd = rowStart;
                    breakWidth = 0.0;
                    breakMaxX = 0.0;
                }
            }
        }

        pcodepoint = iter.codepoint;
        ptype = type;
    }

    // Break the line from the end of the last word, and start new line from the beginning of the new.
    if (rowStart != NULL) {
        rows[nrows].start = rowStart;
        rows[nrows].end = rowEnd;
        rows[nrows].width = rowWidth * invscale;
        rows[nrows].minx = rowMinX * invscale;
        rows[nrows].maxx = rowMaxX * invscale;
        rows[nrows].next = end;
        nrows++;
    }

    return nrows;
}

// Measures the specified text string. Parameter bounds should be a pointer to float[4],
// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
// Returns the horizontal advance of the measured text (i.e. where the next character should drawn).
// Measured values are returned in local coordinate space.
float nvgTextBounds(NVGcontext* ctx, float x, float y, const char* string, const char* end, float* bounds)
{
    NVGstate* state = nvg__getState(ctx);
    float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
    float invscale = 1.0f / scale;
    float width;

    if (state->fontId == FONS_INVALID) return 0;

    fonsSetSize(ctx->fs, state->fontSize*scale);
    fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
    fonsSetBlur(ctx->fs, state->fontBlur*scale);
    fonsSetAlign(ctx->fs, state->textAlign);
    fonsSetFont(ctx->fs, state->fontId);

    width = fonsTextBounds(ctx->fs, x*scale, y*scale, string, end, bounds);
    if (bounds != NULL) {
        // Use line bounds for height.
        fonsLineBounds(ctx->fs, y*scale, &bounds[1], &bounds[3]);
        bounds[0] *= invscale;
        bounds[1] *= invscale;
        bounds[2] *= invscale;
        bounds[3] *= invscale;
    }
    return width * invscale;
}

// Measures the specified multi-text string. Parameter bounds should be a pointer to float[4],
// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
// Measured values are returned in local coordinate space.
void nvgTextBoxBounds(NVGcontext* ctx, float x, float y, float breakRowWidth, const char* string, const char* end, float* bounds)
{
    NVGstate* state = nvg__getState(ctx);
    NVGtextRow rows[2];
    float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
    float invscale = 1.0f / scale;
    int nrows = 0, i;
    int oldAlign = state->textAlign;
    int haling = state->textAlign & (NVG_ALIGN_LEFT | NVG_ALIGN_CENTER | NVG_ALIGN_RIGHT);
    int valign = state->textAlign & (NVG_ALIGN_TOP | NVG_ALIGN_MIDDLE | NVG_ALIGN_BOTTOM | NVG_ALIGN_BASELINE);
    float lineh = 0, rminy = 0, rmaxy = 0;
    float minx, miny, maxx, maxy;

    if (state->fontId == FONS_INVALID) {
        if (bounds != NULL)
            bounds[0] = bounds[1] = bounds[2] = bounds[3] = 0.0f;
        return;
    }

    nvgTextMetrics(ctx, NULL, NULL, &lineh);

    state->textAlign = NVG_ALIGN_LEFT | valign;

    minx = maxx = x;
    miny = maxy = y;

    fonsSetSize(ctx->fs, state->fontSize*scale);
    fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
    fonsSetBlur(ctx->fs, state->fontBlur*scale);
    fonsSetAlign(ctx->fs, state->textAlign);
    fonsSetFont(ctx->fs, state->fontId);
    fonsLineBounds(ctx->fs, 0, &rminy, &rmaxy);
    rminy *= invscale;
    rmaxy *= invscale;

    while ((nrows = nvgTextBreakLines(ctx, string, end, breakRowWidth, rows, 2))) {
        for (i = 0; i < nrows; i++) {
            NVGtextRow* row = &rows[i];
            float rminx, rmaxx, dx = 0;
            // Horizontal bounds
            if (haling & NVG_ALIGN_LEFT)
                dx = 0;
            else if (haling & NVG_ALIGN_CENTER)
                dx = breakRowWidth*0.5f - row->width*0.5f;
            else if (haling & NVG_ALIGN_RIGHT)
                dx = breakRowWidth - row->width;
            rminx = x + row->minx + dx;
            rmaxx = x + row->maxx + dx;
            minx = nvg__minf(minx, rminx);
            maxx = nvg__maxf(maxx, rmaxx);
            // Vertical bounds.
            miny = nvg__minf(miny, y + rminy);
            maxy = nvg__maxf(maxy, y + rmaxy);

            y += lineh * state->lineHeight;
        }
        string = rows[nrows-1].next;
    }

    state->textAlign = oldAlign;

    if (bounds != NULL) {
        bounds[0] = minx;
        bounds[1] = miny;
        bounds[2] = maxx;
        bounds[3] = maxy;
    }
}

// Returns the vertical metrics based on the current text style.
// Measured values are returned in local coordinate space.
void nvgTextMetrics(NVGcontext* ctx, float* ascender, float* descender, float* lineh)
{
    NVGstate* state = nvg__getState(ctx);
    float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
    float invscale = 1.0f / scale;

    if (state->fontId == FONS_INVALID) return;

    fonsSetSize(ctx->fs, state->fontSize*scale);
    fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
    fonsSetBlur(ctx->fs, state->fontBlur*scale);
    fonsSetAlign(ctx->fs, state->textAlign);
    fonsSetFont(ctx->fs, state->fontId);

    fonsVertMetrics(ctx->fs, ascender, descender, lineh);
    if (ascender != NULL)
        *ascender *= invscale;
    if (descender != NULL)
        *descender *= invscale;
    if (lineh != NULL)
        *lineh *= invscale;
}

struct NVGLUframebuffer {
    NVGcontext* ctx;
    GLuint fbo;
    GLuint rbo;
    GLuint texture;
    int image;
};
typedef struct NVGLUframebuffer NVGLUframebuffer;

// Helper function to create GL frame buffer to render to.
void nvgluBindFramebuffer(NVGLUframebuffer* fb);
NVGLUframebuffer* nvgluCreateFramebuffer(NVGcontext* ctx, int w, int h, int imageFlags);
void nvgluDeleteFramebuffer(NVGLUframebuffer* fb);

#ifdef NANOVG_GL_IMPLEMENTATION

#if defined(NANOVG_GL3) || defined(NANOVG_GLES2) || defined(NANOVG_GLES3)
// FBO is core in OpenGL 3>.
#	define NANOVG_FBO_VALID 1
#elif defined(NANOVG_GL2)
// On OS X including glext defines FBO on GL2 too.
#	ifdef __APPLE__
#		include <OpenGL/glext.h>
#		define NANOVG_FBO_VALID 1
#	endif
#endif

static GLint defaultFBO = -1;

NVGLUframebuffer* nvgluCreateFramebuffer(NVGcontext* ctx, int w, int h, int imageFlags)
{
#ifdef NANOVG_FBO_VALID
    GLint defaultFBO;
    GLint defaultRBO;
    NVGLUframebuffer* fb = NULL;

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &defaultRBO);

    fb = (NVGLUframebuffer*)malloc(sizeof(NVGLUframebuffer));
    if (fb == NULL) goto error;
    memset(fb, 0, sizeof(NVGLUframebuffer));

    fb->image = nvgCreateImageRGBA(ctx, w, h, imageFlags | NVG_IMAGE_FLIPY | NVG_IMAGE_PREMULTIPLIED, NULL);
    fb->texture = nvglImageHandle(ctx, fb->image);
    fb->ctx = ctx;

    // frame buffer object
    glGenFramebuffers(1, &fb->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fb->fbo);

    // render buffer object
    glGenRenderbuffers(1, &fb->rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, fb->rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, w, h);

    // combine all
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb->texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fb->rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) goto error;

    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, defaultRBO);
    return fb;
error:
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, defaultRBO);
    nvgluDeleteFramebuffer(fb);
    return NULL;
#else
    NVG_NOTUSED(ctx);
    NVG_NOTUSED(w);
    NVG_NOTUSED(h);
    NVG_NOTUSED(imageFlags);
    return NULL;
#endif
}

void nvgluBindFramebuffer(NVGLUframebuffer* fb)
{
#ifdef NANOVG_FBO_VALID
    if (defaultFBO == -1) glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, fb != NULL ? fb->fbo : defaultFBO);
#else
    NVG_NOTUSED(fb);
#endif
}

void nvgluDeleteFramebuffer(NVGLUframebuffer* fb)
{
#ifdef NANOVG_FBO_VALID
    if (fb == NULL) return;
    if (fb->fbo != 0)
        glDeleteFramebuffers(1, &fb->fbo);
    if (fb->rbo != 0)
        glDeleteRenderbuffers(1, &fb->rbo);
    if (fb->image >= 0)
        nvgDeleteImage(fb->ctx, fb->image);
    fb->ctx = NULL;
    fb->fbo = 0;
    fb->rbo = 0;
    fb->texture = 0;
    fb->image = -1;
    free(fb);
#else
    NVG_NOTUSED(fb);
#endif
}

#endif
