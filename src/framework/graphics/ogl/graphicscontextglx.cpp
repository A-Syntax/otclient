/*
 * Copyright (c) 2010-2013 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "graphicscontextglx.h"

GraphicsContextGLX::GraphicsContextGLX() :
    GraphicsContext("GLX"), m_window(dynamic_cast<X11Window&>(g_window))
{
    m_fbConfig = 0;
    m_glxContext = 0;
}

void GraphicsContextGLX::create()
{
    if(!glXQueryExtension(m_window.getDisplay(), NULL, NULL))
        g_logger.fatal("GLX not supported");

    static int attrList[] = {
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DOUBLEBUFFER, True,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        None
    };

    int nelements;
    m_fbConfig = glXChooseFBConfig(m_window.getDisplay(), m_window.getScreen(), attrList, &nelements);
    if(!m_fbConfig)
        g_logger.fatal("Couldn't choose RGBA, double buffered fbconfig");

    m_window.setVisual(glXGetVisualFromFBConfig(m_window.getDisplay(), *m_fbConfig));
    if(!m_window.getDisplay())
        g_logger.fatal("Couldn't choose RGBA, double buffered visual");

    m_window.setRootWindow(RootWindow(m_window.getDisplay(), m_window.getVisual()->screen));

    m_glxContext = glXCreateContext(m_window.getDisplay(), m_window.getVisual(), NULL, True);

    if(!m_glxContext)
        g_logger.fatal("Unable to create GLX context");

    if(!glXIsDirect(m_window.getDisplay(), m_glxContext))
        g_logger.warning("GL direct rendering is not possible");
}

void GraphicsContextGLX::destroy()
{
    if(m_glxContext) {
        glXMakeCurrent(m_window.getDisplay(), None, NULL);
        glXDestroyContext(m_window.getDisplay(), m_glxContext);
        m_glxContext = 0;
    }
}

void GraphicsContextGLX::restore()
{
    if(!glXMakeCurrent(m_window.getDisplay(), m_window.getWindow(), m_glxContext))
        g_logger.fatal("Unable to set GLX context on X11 window");
}

bool GraphicsContextGLX::isExtensionSupported(const char *ext)
{
    const char *exts = glXQueryExtensionsString(m_window.getDisplay(), m_window.getScreen());
    if(strstr(exts, ext))
        return true;
    return false;
}

void *GraphicsContextGLX::getExtensionProcAddress(const char *ext)
{
    return (void *)glXGetProcAddressARB((const GLubyte*)ext);
}

void GraphicsContextGLX::swapBuffers()
{
    glXSwapBuffers(m_window.getDisplay(), m_window.getWindow());
}

void GraphicsContextGLX::setVerticalSync(bool enable)
{
    typedef GLint (*glSwapIntervalProc)(GLint);
    glSwapIntervalProc glSwapInterval = NULL;

    if(isExtensionSupported("GLX_MESA_swap_control"))
        glSwapInterval = (glSwapIntervalProc)getExtensionProcAddress("glXSwapIntervalMESA");
    else if(isExtensionSupported("GLX_SGI_swap_control"))
        glSwapInterval = (glSwapIntervalProc)getExtensionProcAddress("glXSwapIntervalSGI");

    if(glSwapInterval)
        glSwapInterval(enable ? 1 : 0);
}