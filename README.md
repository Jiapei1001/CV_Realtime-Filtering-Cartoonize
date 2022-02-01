# Computer Vision_Realtime-Filtering
Realtime Filtering for images or video streams

## Summary
This project explores several types of filtering methods. These filters can be applied to an image or a video frame, and render in realtime. It is built on top of OpenCV library, and explores some modules including core functionality, image processing, etc.

Some of the high level steps are: **opening, capturing, manipulating, and writing images**. User can always get the latest result after a selected filtering type. User can type different keys for a selection of filters. In addition to these filters, user can also type 's' to save the rendered image, or type 'q' to exit.


## Custom Extensions
**Sketch & X-ray**
<div>
  <img width="560" alt="dog_pencil" src="https://user-images.githubusercontent.com/20607583/152029097-d707e8fe-9575-44fc-879d-f3e4a81ec871.jpg">
  <img width="260" alt="dog_original" src="https://user-images.githubusercontent.com/20607583/152029146-44ebc5ab-5d93-4acf-8fbd-6ccb06e51318.jpg">
</div>
<br/><br/>

**Lightening spotted mask**
<div>
  <img width="560" alt="dog_green_dot_contour" src="https://user-images.githubusercontent.com/20607583/152029445-34427c03-6db8-4287-a695-ccf2ef4f2fd6.jpg">
  <img width="300" alt="dog_original" src="https://user-images.githubusercontent.com/20607583/152029146-44ebc5ab-5d93-4acf-8fbd-6ccb06e51318.jpg">
</div>
<br/><br/>

**X-ray Light blue mask**
<div>
  <img width="560" alt="dog_blue_mask" src="https://user-images.githubusercontent.com/20607583/152029512-58be5c89-32fc-47f3-862a-ca9bc5f1cdf2.jpg">
  <img width="300" alt="dog_original" src="https://user-images.githubusercontent.com/20607583/152029146-44ebc5ab-5d93-4acf-8fbd-6ccb06e51318.jpg">
</div>
<br/><br/>

**Distorted Dots mask**
<div>
  <img width="560" alt="dog_gabor_kernel_texture" src="https://user-images.githubusercontent.com/20607583/152029684-9da95463-52e3-496c-873e-8ac8f22f123e.jpg">
  <img width="300" alt="dog_original" src="https://user-images.githubusercontent.com/20607583/152029146-44ebc5ab-5d93-4acf-8fbd-6ccb06e51318.jpg">
</div>
<br/><br/>


## Core
**Grayscale**
<div>
  <img width="560" alt="grayscale" src="https://user-images.githubusercontent.com/20607583/152030425-38309d26-2e20-4f11-9fd3-bd13d8dc5944.jpg">
  <img width="300" alt="original" src="https://user-images.githubusercontent.com/20607583/152030445-c6201588-bb55-493a-a89d-27ff425fbad9.jpg">
</div>
<br/><br/>

**Alternative Grayscale**
<div>
  <img width="560" alt="custom grayscale" src="https://user-images.githubusercontent.com/20607583/152031139-b2030dc3-4975-46c2-87a6-5ad746e79e5f.jpg">
  <img width="300" alt="original" src="https://user-images.githubusercontent.com/20607583/152030445-c6201588-bb55-493a-a89d-27ff425fbad9.jpg">
</div>
<br/><br/>

**Gaussian Blur**
<div>
  <img width="560" alt="blur" src="https://user-images.githubusercontent.com/20607583/152031232-c9de262b-7952-441b-a111-6207839ddac7.jpg">
  <img width="300" alt="original" src="https://user-images.githubusercontent.com/20607583/152030445-c6201588-bb55-493a-a89d-27ff425fbad9.jpg">
</div>
<br/><br/>

**Sobel X**
<div>
  <img width="560" alt="sobel_X" src="https://user-images.githubusercontent.com/20607583/152031339-ace11682-e743-4471-ade4-1fba06aba412.jpg">
  <img width="300" alt="original1" src="https://user-images.githubusercontent.com/20607583/152031353-b7e85939-865a-4349-b67b-d734faac1d4e.jpg">
</div>
<br/><br/>


**Sobel Y**
<div>
  <img width="560" alt="sobel_Y" src="https://user-images.githubusercontent.com/20607583/152031454-5b2bba14-8acf-4aa4-8df0-1e8391445658.jpg">
  <img width="300" alt="original1" src="https://user-images.githubusercontent.com/20607583/152031353-b7e85939-865a-4349-b67b-d734faac1d4e.jpg">
</div>
<br/><br/>

**Gradient Magnitude**
<div>
  <img width="560" alt="gradient magnitude" src="https://user-images.githubusercontent.com/20607583/152031544-cb4234a8-0c43-4d8b-827b-50e3a318ddb4.jpg">
  <img width="300" alt="original1" src="https://user-images.githubusercontent.com/20607583/152031353-b7e85939-865a-4349-b67b-d734faac1d4e.jpg">
</div>
<br/><br/>

**Blur and Quantize**
<div>
  <img width="560" alt="blur_quantize" src="https://user-images.githubusercontent.com/20607583/152031631-8b5e240a-abee-4543-927e-564a43d2f24e.jpg">
  <img width="300" alt="original2" src="https://user-images.githubusercontent.com/20607583/152031640-d53186d1-3dd6-46d3-b0db-f6a841c29221.jpg">
</div>
<br/><br/>

**Cartoonization**
<div>
  <img width="560" alt="cartoonization" src="https://user-images.githubusercontent.com/20607583/152031726-9d7171a2-9257-4921-b6dd-2a6275498f3a.jpg">
  <img width="300" alt="original2" src="https://user-images.githubusercontent.com/20607583/152031640-d53186d1-3dd6-46d3-b0db-f6a841c29221.jpg">
</div>
<br/><br/>

**Invert**
<div>
  <img width="560" alt="invert" src="https://user-images.githubusercontent.com/20607583/152031803-025e2b2c-c799-48b3-bd79-d03cba8ceb0c.jpg">
  <img width="300" alt="original2" src="https://user-images.githubusercontent.com/20607583/152031640-d53186d1-3dd6-46d3-b0db-f6a841c29221.jpg">
</div>
<br/><br/>



## Build Instructions
```
cd /bin
cmake ..
make
./imgDisplay
./vidDisplay
```


### Acknowledgements

https://docs.opencv.org/4.5.5/

Stack Overflow, Medium, Youtube

