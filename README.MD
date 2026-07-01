# Slurps (**WIP**)
Sequential scripting image processor CLI for MacOS inspired by `sips`.

Minimal OS Requirement: **`MacOS 10.9`** 

## Usage
Slurps command is built from a chain of subsequent operations.

These operations are executed in the order they're written in.

Example:
```sh
slurps ./image1.png ./image2.jpg \
    --overlayColor 255:0:0:87    \
    --resampleMode nearest       \
    --newWidthHeight 1024x1024   \
    --format icns                \
    --output ./processedImage{COUNT}.icns
```