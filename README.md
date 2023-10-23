# Polygon collision detection

![Polygon creation and collision detection](https://github.com/RaduHaulica/Polygons/blob/69013f7135d3d9d19bb57c030015ac1126544b03/Polygons/assets/polygon%20collision%20detection.gif)

Drag the polygons around the screen. When a collision with another polygon is detected, the color of the convex hull turns red.

Collision detection is based on the Minkowski difference of the overlapping polygons (convex polygons are required for this, which is why the convex hull of the point set is computed). If the Minkowski difference of the convex hulls contains the origin, then the polygons overlap.

The blue polygons are a visual aid and represent the Minkowski differences of the polygons on the screen.

## How to use
Hold P and then click and drag around the screen to create points. Release the left mouse button to finish the point set, and a convex hull creation algorithm (Graham scan) will run automatically and enclose the point set in its hull.

Click inside a polygon and drag the point set + boundary around the screen. When a collision with another polygon is detected, the color of the convex hull turns red.
