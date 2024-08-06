#include <iostream>
#include "libppm.h"
#include <cstdint>

using namespace std;

struct image_t* S1_smoothen(struct image_t *input_image)
{
	struct image_t* smooth_img = new struct image_t;
	//uint8_t*** s_pixels;
	int height = input_image->height;
	int width = input_image->width;
	smooth_img->height = height;
	smooth_img->width = width;
	uint8_t*** pixels = input_image->image_pixels;
	uint8_t*** smooth = smooth_img->image_pixels;
	smooth_img->image_pixels = new uint8_t**[height];
	for(int i = 0; i < image->height; i++)
			{
				smooth_img->image_pixels[i] = new uint8_t*[width];
				for(int j = 0; j < image->width; j++)
					smooth_img->image_pixels[i][j] = new uint8_t[3];
			}

		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				for(int k=0;k<3;k++){
					if(i==0 && j==0){
						smooth_img->image_pixels[i][j][k] += pixels[i][j][k]+pixels[i][j+1][k]+pixels[i+1][j][k]+pixels[i+1][j+1][k]/4;
					}
					else if(i==0 && j==width-1){
						smooth_img->image_pixels[i][j][k] += pixels[i][j][k]+pixels[i+1][j][k]+pixels[i][j-1][k]+pixels[i+1][j-1][k]/4;
					}
					else if(i==height-1 && j==0){
						smooth_img->image_pixels[i][j][k] += pixels[i][j][k]+pixels[i-1][j][k]+pixels[i][j+1][k]+pixels[i-1][j+1][k]/4;
					}
					else if(i==height-1 && j==width-1){
						smooth_img->image_pixels[i][j][k] += pixels[i][j][k]+pixels[i-1][j][k]+pixels[i][j-1][k]+pixels[i-1][j-1][k]/4;
					}
					else if(i==0 ){
						smooth_img->image_pixels[i][j][k] += pixels[i][j][k]+pixels[i][j-1][k]+pixels[i][j+1][k]+pixels[i+1][j][k]+pixels[i+1][j-1][k]+pixels[i+1][j+1][k]/6;
					}
					else if(i==height-1){
						smooth_img->image_pixels[i][j][k] += pixels[i][j][k]+pixels[i][j-1][k]+pixels[i][j+1][k]+pixels[i-1][j][k]+pixels[i-1][j-1][k]+pixels[i-1][j+1][k]/6;
					}
					else if(j==0){
						smooth_img->image_pixels[i][j][k] += pixels[i][j][k]+pixels[i-1][j][k]+pixels[i+1][j][k]+pixels[i][j+1][k]+pixels[i-1][j+1][k]+pixels[i+1][j+1][k]/6;
					}
					else if(j==width-1){
						smooth_img->image_pixels[i][j][k] += pixels[i][j][k]+pixels[i-1][j][k]+pixels[i+1][j][k]+pixels[i][j+1][k]+pixels[i-1][j+1][k]+pixels[i+1][j+1][k]/6;
					}
				else{
					smooth_img->image_pixels[i][j][k]+= (pixels[i][j][k]+pixels[i-1][j][k]+pixels[i+1][j][k]+pixels[i][j+1][k]+pixels[i][j-1][k]
														+pixels[i-1][j-1][k]+pixels[i-1][j+1][k]+pixels[i+1][j-1][k]+pixels[i+1][j+1][k])/9;
				}

			}
		}
	}

	return smooth_img;
}

struct image_t* S2_find_details(struct image_t *input_image, struct image_t *smoothened_image)
{
	struct image_t* detail_img = new struct image_t;
	int height = input_image->height;
	int width = input_image->width;
	uint8_t*** pixels = input_image->image_pixels;
	uint8_t*** s_pixels = smoothened_image->image_pixels;
	detail_img->height = height;
	detail_img->width = width;
	detail_img->image_pixels = new uint8_t**[height];
	for(int i=0;i<height;i++){
			detail_img->image_pixels[i] = new uint8_t*[width];
			for(int j=0;j<width;j++){
				detail_img->image_pixels[i][j] = new uint8_t[3];
				for(int k=0;k<3;k++){
					detail_img->image_pixels[i][j][k] = pixels[i][j][k]- s_pixels[i][j][k];
				}
			}
	}

	return detail_img;
}

struct image_t* S3_sharpen(struct image_t *input_image, struct image_t *details_image)
{
	struct image_t* sharp = new struct image_t;
	int height = input_image->height;
	int width = input_image->width;
	uint8_t*** pixels = input_image->image_pixels;
	uint8_t*** s_pixels = details_image->image_pixels;
	sharp->height = height;
	sharp->width = width;
	sharp->image_pixels = new uint8_t**[height];
	for(int i = 0; i < image->height; i++)
				{
					smooth_img->image_pixels[i] = new uint8_t*[image->width];
					for(int j = 0; j < image->width; j++)
						smooth_img->image_pixels[i][j] = new uint8_t[3];
				}
	for(int i=0;i<height;i++){
			sharp->image_pixels[i] = new uint8_t*[width];
			for(int j=0;j<width;j++){
				sharp->image_pixels[i][j] = new uint8_t[3];
				for(int k=0;k<3;k++){
					sharp->image_pixels[i][j][k] = pixels[i][j][k] + s_pixels[i][j][k];
					}
				}
		}

	return sharp;
}

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		cout << "usage: ./a.out <path-to-original-image> <path-to-transformed-image>\n\n";
		exit(0);
	}
	struct image_t *input_image = read_ppm_file(argv[1]);
	struct image_t *smoothened_image = S1_smoothen(input_image);
	struct image_t *details_image = S2_find_details(input_image, smoothened_image);
	struct image_t *sharpened_image = S3_sharpen(input_image, details_image);
	write_ppm_file(argv[2], sharpened_image);
	
	return 0;
}
