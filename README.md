# Camera Calibration OpenCV4 C++17

Simplest application, generates the _calibration matrix_ and the _distortion coefficients_ from a set of images. The _calibration matrix_ is also called _intrinsics matrix_ and _camera matrix_.

* To find screen-to-world correspondences (which point in the space in the camera image corresponds to a point in the screen), an _extrinsics matrix_ is required. See the full calculation here: https://github.com/rodolfoap/screen2world-k. In such example, the _extrinsics matrix_ is calculated using a set of world-to-screen point correspondences.
* To find screen-to-world correspondences, another approach is proposed: See the full calculation here: https://github.com/rodolfoap/screen2world-d. In such example, the _extrinsics matrix_ is calculated by using a set of person detection boxes to calculate the distances to the camera. Knowing the camera bearing, world-to-screen points correspondences are automatically found, and the _extrinsics matrix_ is calculated in some steps.
* To find screen-to-world correspondences in a simple manner, another approach is proposed: See the full calculation here: https://github.com/rodolfoap/screen2world-h. In such example, In such example, an _homography matrix_ is calculated just by using a set of world-to-screen point correspondences. Therefore, the _intrinsics_ matrix (the one calculated with this application) is not needed.

## Build

```
mkdir -p build && pushd $_;
cmake ..
make
popd
```

## Usage

```
./calib
Usage: ./calib [IMAGES_PATH BOARD_SIZE NUMBER_OF_CORNERS_X NUMBER_OF_CORNERS_Y]

./calib data/ 0.025 5 7
# The images are in ./data
# Cells measure 2.5cm
# Board has 5x7 corners
```

## Sample output

```
Path: data/
Cell size: 0.025
Dimensions: 5x7
Reading file: "data/chess6.jpg"
Reading file: "data/chess2.jpg"
Reading file: "data/chess9.jpg"
Reading file: "data/chess10.jpg"
Reading file: "data/chess7.jpg"
Reading file: "data/chess13.jpg"
Reading file: "data/chess1.jpg"
Reading file: "data/chess11.jpg"
Reading file: "data/chess12.jpg"
Reading file: "data/chess8.jpg"
Reading file: "data/chess5.jpg"
Reading file: "data/chess3.jpg"
Reading file: "data/chess4.jpg"
Finding 2D corner points: ............. done.
Building 3D points matrix: ................................... done.

Results:
Number of applied images: 13
RMS error: 1.51126
Camera matrix (K):
[623.9883403197383, 0, 317.7871007629089;
 0, 622.5620313704134, 242.3263150538062;
 0, 0, 1]
Distortion coefficients (k1, k2, p1, p2, k3, ...):
[0.1693785505301569, -0.2542623714253436, -0.007367350113987782, 0.004785136023342617, 0.2114065564198191]
```

## Example generated YAML file

```
%YAML:1.0
---
camera_matrix: !!opencv-matrix
   rows: 3
   cols: 3
   dt: d
   data: [ 6.2398834031973831e+02, 0., 3.1778710076290895e+02, 0.,
       6.2256203137041337e+02, 2.4232631505380624e+02, 0., 0., 1. ]
distortion_coefficients: !!opencv-matrix
   rows: 5
   cols: 1
   dt: d
   data: [ 1.6937855053015685e-01, -2.5426237142534358e-01,
       -7.3673501139877818e-03, 4.7851360233426175e-03,
       2.1140655641981909e-01 ]
```
