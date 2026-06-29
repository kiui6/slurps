# Slurps (**WIP**)
Scripting sequential image processor CLI inspired by `sips`.

## Usage
Example:
```sh
slurps ./image1.png ./image2.jpg \
    --overlayColor 255:0:0:255   \
    --newWidthHeight 1024x1024   \
    --format icns                \
    --output ./processedImage<INDEX>.icns
```