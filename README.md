# 🌟 Fract'ol

This README introduces **Fract'ol**, a high-performance fractal explorer designed for smooth, responsive real-time navigation of complex mathematical sets.

---

## Clone and Execute

Clone it recursively to get the minilibx submodule:

```
git clone --recursive https://github.com/Guirie92/fract-ol.git && cd fract-ol
```

To compile:
```
make
```

To execute:

```
./fractol <fractal_type> <julia_re> <julia_im>
```

Fractal types are "mandelbrot" and "burning" (burning ship), or "julia" (mandelbrot-julia)
type, at specified position (julia_re and julia_im).

For instance:

```
./fractol mandelbrot
```


## 🚀 Super Fast and Responsive: Progressive Rendering

The core goal of Fract'ol is to provide a **smooth, delay-free, 60 FPS experience** while navigating and zooming deeply into any fractal. Standard rendering can cause noticeable lag, especially when zooming or on lower-end devices. If, out of curiosity, you'd like to experience the navigation lag of implementations without progressive rendering, press the toggle **Progressive rendering (P/p)** on and off to see the difference.

To achieve superior performance and responsiveness, the application uses a **Progressive Rendering** implementation:

1.  **Low-Resolution Start:** Upon a new movement (pan or zoom), the image is first rendered at a low resolution to give immediate visual feedback.
2.  **Progressive Refinement:** In subsequent frames, the renderer progressively fills in the missing pixels, moving towards the full, high-resolution image.

### 💡 Time-Budgeted Execution

Most importantly, the rendering process is **time-budgeted**. Every frame, the application has a total time budget of **16 milliseconds (MS)** to maintain a smooth 60 Frames Per Second (FPS).

* **Render Budget:** I allocate **12 MS** of this budget to the fractal rendering job.
* **Adaptive Execution:** If the rendering job exceeds the 12 MS budget for the current frame, the execution is **halted immediately** and the job is automatically **resumed** on the very next frame.

This technique ensures the application's responsiveness is prioritized. A faster CPU will complete the render job in fewer frames, while a slower device remains perfectly responsive by ensuring no single render step causes a noticeable FPS hitch.

### ⚡ Multithreading Acceleration

For maximum speed, Fract'ol includes an optional **Multi-threading Mode (T/t)**. By utilizing multiple cores of your CPU, this feature speeds up the calculation process by a factor of **10 to 15 times**, allowing the progressive rendering to complete almost instantly.

---

## 🕹️ Controls and Features

All controls are accessible via the in-app help panel (**H/h**).

### Essential Navigation

* **ARROWS / DRAG:** Pan (move) the fractal.
* **WHEEL:** Zoom in/out.
* **R/r:** Recenter the view to the default starting position.
* **+/-:** Increase/Decrease Max Iterations (controls detail and rendering time). It defaults at 150 iterations, and you can go up to 5000.
* **Left click:** Toggle the julia version/mode of the current fractal at the mouse position (click again to go back).
* **1/2/3:** Switch between different fractal types (Mandelbrot, Burning Ship, and the Julia version of the actual fractal).

### Progressive & Speed Controls

* **P/p:** Toggle Progressive Rendering mode, on by default (Highly recommended for smooth navigation).
* **T/t:** Toggle Multi-threading mode (Highly recommended for speed).

### Color & Display

* **C/c:** Cycle through different color gradients.
* **V/v:** Toggle color depth/palette options.
* **F/f:** Switch screen size (default, 2K, 4K).

### ✨ Special Feature: Julia Live Preview

The **Julia Live Preview** is a unique feature designed to help you select your Julia constant `c`:

* **J/j:** Toggle the live preview. A **small second image** will appear in the bottom-left corner of the main window.
* **Real-time Update:** As you **move your cursor** across the main Mandelbrot view, the small preview window will instantly draw the resulting Julia fractal at your current cursor's coordinates (where `c` is the mouse position).
* **L-click:** Once you find a Julia shape you like in the preview, simply **Left-click** on that coordinate to instantly switch the main window to that Julia fractal at full size.


### 🔬 Core Fractals and Their Formulas

Fract'ol allows you to explore the two most famous families of fractals: 
the Mandelbrot set and the Julia sets (and Burning Ship as bonus).


### Mandelbrot Set

The Mandelbrot set is defined as the set of complex numbers `c` for which the sequence:

    z(n+1) = z(n)^2 + c
    with z(0) = 0

remains bounded (that is, it does not diverge to infinity).

In practice, a point `c` belongs to the Mandelbrot set if the magnitude `|z(n)|`
never exceeds a fixed limit (usually 2), even after many iterations.

The Mandelbrot set is a single, connected fractal with an infinitely detailed
boundary and is used as a reference to generate other fractals.

---

### Julia Sets

Julia sets are generated using the same recurrence formula:

    z(n+1) = z(n)^2 + c

but with different initial conditions:

- `c` is a fixed complex constant
- `z(0)` is the complex coordinate of the pixel being tested

Each value of `c` produces a different Julia set.

A key relationship between the two fractals is:

- If `c` belongs to the Mandelbrot set, the corresponding Julia set is connected.
- If `c` does not belong to the Mandelbrot set, the Julia set is disconnected
  (often referred to as "Julia dust").

---

### Burning Ship Fractal

The Burning Ship fractal is a variation of the Mandelbrot set.
It modifies the iteration by applying absolute values to the real and
imaginary parts before squaring:

    z(n+1) = ( |Re(z(n))| + i * |Im(z(n))| )^2 + c

This produces a fractal with sharp edges and a ship-like structure.

---

### Escape Time Algorithm

Fractal rendering is based on the *escape time* algorithm:

1. **Pixel mapping**  
   Each pixel `(x, y)` is mapped to a complex number, used either as `z(0)` or `c`
   depending on the fractal.

2. **Iteration**  
   The function `z = z^2 + c` (or a variant) is applied repeatedly.

3. **Escape condition**  
   Iteration stops when `|z|` exceeds a chosen threshold (commonly 2),
   or when a maximum number of iterations is reached.

4. **Coloring**  
   The number of iterations before escape is used to determine the pixel color,
   often with smoothing to produce continuous gradients.

---