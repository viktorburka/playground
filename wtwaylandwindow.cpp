#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#include "wtwaylandwindow.h"
#include "cttempfile.h"

static wl_display * m_display = 0;
static wl_registry * registry = 0;
static wl_compositor *compositor = 0;
static wl_surface *surface = 0;
static wl_shell *shell = 0;
static wl_shell_surface *shell_surface = 0;
struct wl_shm *shm = 0;
struct wl_buffer *buffer = 0;
struct wl_shm_pool *pool = 0;
struct wl_callback *frame_callback = 0;

void* shm_data = 0;

void surface_ping(void *data, struct wl_shell_surface *shell_surface,
                  uint32_t serial)
{
    (void)data;
    (void)shell_surface;
    (void)serial;
    wl_shell_surface_pong(shell_surface, serial);
    //fprintf(stderr, "Pinged and ponged\n");
}

void surface_configure(void *data, struct wl_shell_surface *shell_surface,
                       uint32_t edges, int32_t width, int32_t height)
{
    (void)data;
    (void)shell_surface;
    (void)edges;
    (void)width;
    (void)height;
    fprintf(stdout, "edges: %u, width: %d, height: %d\n", edges, width, height);
}

void surface_popup_done(void *data, struct wl_shell_surface *shell_surface)
{
    (void)data;
    (void)shell_surface;
}

static wl_shell_surface_listener shell_surface_listener = {
    surface_ping,
    surface_configure,
    surface_popup_done
};

void announce_pixel_format(void *data,
                           struct wl_shm *wl_shm,
                           uint32_t format)
{
    (void)data;
    (void)wl_shm;
    switch (format) {
        case WL_SHM_FORMAT_ARGB8888: fprintf(stderr, "Possible shmem format %s\n", "ARGB8888"); break;
        case WL_SHM_FORMAT_XRGB8888: fprintf(stderr, "Possible shmem format %s\n", "XRGB8888"); break;
        case WL_SHM_FORMAT_RGB565:   fprintf(stderr, "Possible shmem format %s\n", "RGB565"); break;
        default: fprintf(stderr, "Possible shmem format %s\n", "other format"); break;
    }
}

static wl_shm_listener shm_listener = {
    announce_pixel_format
};

void announce_global_object(void *data,
                            struct wl_registry *registry,
                            uint32_t id,
                            const char *interface,
                            uint32_t version)
{
    (void)data;
    (void)version;

    fprintf(stdout, "announce interace: %s\n", interface);

    if (strcmp(interface, "wl_compositor") == 0) {
        compositor = (wl_compositor*)wl_registry_bind(registry, id,
                                                      &wl_compositor_interface, 1);
    } else if (strcmp(interface, "wl_shell") == 0) {
        shell = (wl_shell *)wl_registry_bind(registry, id,
                                             &wl_shell_interface, 1);
    } else if (strcmp(interface, "wl_shm") == 0) {
        shm = (wl_shm *)wl_registry_bind(registry, id,
                                         &wl_shm_interface, 1);
        wl_shm_add_listener(shm, &shm_listener, NULL);
    }
}

void remove_registry(void *data,
                     struct wl_registry *wl_registry,
                     uint32_t name)
{
    (void)data;
    (void)wl_registry;
    fprintf(stdout, "Implement: remove interace: %d\n", name);
    abort();
}

static wl_registry_listener registry_listener = {
    announce_global_object,
    remove_registry
};

static void paint()
{
    uint32_t redPixel = 0x00FF0000; // XRGB red
    uint32_t* pixel = (uint32_t*)shm_data;
    int size = WtWaylandWindow::windowWidth * WtWaylandWindow::windowHeight;
    for (int i = 0; i < size; ++i) {
        *pixel++ = redPixel;
    }
}

static void done(void *data, struct wl_callback *callback, uint32_t time);

static const struct wl_callback_listener frame_callback_listener = {
    done
};

static void done(void *data, struct wl_callback *callback, uint32_t time)
{
    (void)time;
    fprintf(stdout, "data = %p\n", data);
    fprintf(stdout, "callback = %p\n", callback);

    // call destroy since its been destroyed by the compositor by this point
    wl_callback_destroy(frame_callback);

    paint();
    wl_surface_damage(surface, 0, 0,
                      WtWaylandWindow::windowWidth,
                      WtWaylandWindow::windowHeight);

    frame_callback = wl_surface_frame(surface);
    wl_callback_add_listener(frame_callback, &frame_callback_listener, NULL);
    wl_surface_attach(surface, buffer, 0, 0);
    wl_surface_commit(surface);
}

int WtWaylandWindow::windowWidth  = 0;
int WtWaylandWindow::windowHeight = 0;

WtWaylandWindow::WtWaylandWindow(int width, int height)
    : m_mappedFile(0)
{
    int status = 0;

    windowWidth = width;
    windowHeight = height;

    m_display = wl_display_connect(NULL);
    if (m_display == NULL) {
        fprintf(stderr, "Error connecting to the Wayland display: %m\n");
        exit(1);
    }

    fprintf(stdout, "created display %p\n", m_display);

    registry = wl_display_get_registry(m_display);
    wl_registry_add_listener(registry, &registry_listener, NULL);

    fprintf(stdout, "created registry %p\n", registry);

    // block and wait until all requests are delivered to the server
    // and then events dispatched on the client
    status = wl_display_roundtrip(m_display);
    if (status == -1) {
        fprintf(stderr, "Failed processing pending requests from the server: %m\n");
        exit(1);
    }

    fprintf(stdout, "created compositor %p\n", compositor);

    surface = wl_compositor_create_surface(compositor);
    if (!surface) {
        fprintf(stderr, "Can't create surface: %m\n");
        exit(1);
    }

    fprintf(stdout, "created surface %p\n", surface);

    shell_surface = wl_shell_get_shell_surface(shell, surface);
    if (!shell_surface) {
        fprintf(stderr, "Can't create shell surface: %m\n");
        exit(1);
    }

    fprintf(stdout, "created shell_surface %p\n", shell_surface);

    wl_shell_surface_set_toplevel(shell_surface);
    wl_shell_surface_add_listener(shell_surface,
                                  &shell_surface_listener, NULL);

    frame_callback = wl_surface_frame(surface);
    fprintf(stdout, "frame_callback = %p\n", frame_callback);
    wl_callback_add_listener(frame_callback, &frame_callback_listener, NULL);

    const char *path = getenv("XDG_RUNTIME_DIR");
    if (!path) {
        fprintf(stderr, "Environment variable XDG_RUNTIME_DIR is not set\n");
        exit(1);
    }

    int shm_size = windowWidth * windowHeight * 4;
    std::string dirPath(path);

    m_mappedFile = new CtTempFile(dirPath + "/wtwindow-buffer-XXXXXX");
    fprintf(stdout, "Path: %s\n", m_mappedFile->filePath().c_str());

    if (!m_mappedFile->create(shm_size)) {
        fprintf(stderr, "Failed opening temp file %s: %s\n",
                m_mappedFile->filePath().c_str(),
                m_mappedFile->errorMessage().c_str());
        exit(1);
    }

    shm_data = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED,
                          m_mappedFile->descriptor(), 0);
    if (shm_data == MAP_FAILED) {
        fprintf(stderr, "mmap failed: %m\n");
        m_mappedFile->close();
        exit(1);
    }

    fprintf(stdout, "shm_data = %p\n", shm_data);

    pool = wl_shm_create_pool(shm, m_mappedFile->descriptor(), shm_size);
    buffer = wl_shm_pool_create_buffer(pool, 0,
                                       windowWidth, windowHeight,
                                       windowWidth * 4,
                                       WL_SHM_FORMAT_XRGB8888);

    fprintf(stdout, "pool = %p\n", pool);
    fprintf(stdout, "buff = %p\n", buffer);

    wl_shm_pool_destroy(pool);

    wl_surface_attach(surface, buffer, 0, 0);
    wl_surface_commit(surface);
}

WtWaylandWindow::~WtWaylandWindow()
{
    if (m_display) {
        wl_display_disconnect(m_display); // This should internally call free on display
        m_display = 0;
    }
}

wl_display* WtWaylandWindow::display() const
{
    return m_display;
}
