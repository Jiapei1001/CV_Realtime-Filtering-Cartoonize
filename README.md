# Computer Vision_Realtime-Filtering
Realtime Filtering for images or video streams

## Summary
This project explores several types of filtering methods. These filters can be applied to an image or a video frame. The filter rendering happens in realtime. 

Some of the high level steps are: **opening, capturing, manipulating, and writing images**. User can always get the latest result after a selected filtering type. User can type different keys for a selection of filters. In addition to these filters, user can also type 's' to save the rendered image, or type 'q' to exit.

This project is built on top of OpenCV library. It explores some modules including core functionality, image processing, etc.

**Instructions**

```
cd /bin
cmake ..
make
./imgDisplay
./vidDisplay
```

## Custom Extensions
**Sketch & X-ray**
<div>
  <img width="560" alt="dog_pencil" src="https://user-images.githubusercontent.com/20607583/152029097-d707e8fe-9575-44fc-879d-f3e4a81ec871.jpg">
  <img width="300" alt="dog_original" src="https://user-images.githubusercontent.com/20607583/152029146-44ebc5ab-5d93-4acf-8fbd-6ccb06e51318.jpg">
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




